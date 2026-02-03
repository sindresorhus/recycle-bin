#define _WIN32_IE _WIN32_IE_IE70

#include "progress.h"

#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include <versionhelpers.h>
#include <initguid.h>
#include <shlobj.h>

static void printError(HRESULT hr) {
	wchar_t *message = NULL;

	DWORD length = FormatMessageW(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR)&message,
		0,
		NULL
	);

	if (length > 0 && message != NULL) {
		// Remove trailing newline if present.
		while (length > 0 && (message[length - 1] == L'\n' || message[length - 1] == L'\r')) {
			message[--length] = L'\0';
		}

		fwprintf(stderr, L"error: %ls\n", message);
		LocalFree(message);
	} else {
		fwprintf(stderr, L"error: 0x%08lX\n", (unsigned long)hr);
	}
}

#define CHECK(result) if (FAILED(result)) {\
	printError(result);\
	return 1;\
}
#define CHECK_OBJ(obj, result) if (FAILED(result)) {\
	printError(result);\
	obj->lpVtbl->Release(obj);\
	return 1;\
}

// Resolve subst virtual drive paths to their real paths.
// Without this, IFileOperation silently fails to recycle files on subst drives
// because Windows has no Recycle Bin associated with virtual drives.
static wchar_t *resolveSubstPath(const wchar_t *path) {
	if (path[0] == L'\0' || path[1] != L':') {
		return NULL;
	}

	wchar_t drive[3] = {path[0], L':', L'\0'};
	wchar_t target[MAX_PATH];

	DWORD length = QueryDosDeviceW(drive, target, MAX_PATH);

	if (length == 0) {
		return NULL;
	}

	// Subst drives have a target starting with "\??\".
	// Regular drives return "\Device\..." instead.
	if (wcsncmp(target, L"\\??\\", 4) != 0) {
		return NULL;
	}

	const wchar_t *realPrefix = target + 4;
	size_t prefixLength = wcslen(realPrefix);
	const wchar_t *rest = path + 2; // Skip "X:"
	size_t restLength = wcslen(rest);

	wchar_t *resolved = malloc((prefixLength + restLength + 1) * sizeof(wchar_t));

	wmemcpy(resolved, realPrefix, prefixLength);
	wmemcpy(resolved + prefixLength, rest, restLength + 1);

	return resolved;
}

static void freeIdListArray(PCIDLIST_ABSOLUTE *list, int count) {
	if (list == NULL) {
		return;
	}

	for (int i = 0; i < count; i++) {
		if (list[i] != NULL) {
			ILFree((PIDLIST_ABSOLUTE)list[i]);
		}
	}

	free(list);
}

int wmain(int argc, wchar_t **argv) {
	if (argc == 2) {
		if (wcscmp(argv[1], L"--version") == 0) {
			puts("2.1.0");
			return 0;
		}

		if (wcscmp(argv[1], L"--help") == 0) {
			puts("\n  Move files and folders to the recycle bin\n\n  Usage: recycle-bin <path> [...]\n\n  Created by Sindre Sorhus");
			return 0;
		}
	} else if (argc == 1) {
		puts("Specify at least one path");
		return 1;
	}

	int count = argc - 1;
	wchar_t **files = argv + 1;

	CHECK(CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE));

	IFileOperation *op;

	CHECK(CoCreateInstance(
		&CLSID_FileOperation,
		NULL,
		CLSCTX_ALL,
		&IID_IFileOperation,
		(void**)&op
	));

	if (IsWindows8OrGreater()) {
		CHECK_OBJ(op, op->lpVtbl->SetOperationFlags(
			op,
			FOFX_ADDUNDORECORD |
			FOFX_RECYCLEONDELETE |
			FOF_NOERRORUI |
			FOF_NOCONFIRMATION |
			FOF_SILENT |
			FOFX_EARLYFAILURE
		));
	} else {
		CHECK_OBJ(op, op->lpVtbl->SetOperationFlags(
			op,
			FOF_NO_UI |
			FOF_ALLOWUNDO |
			FOF_NOERRORUI |
			FOF_SILENT |
			FOFX_EARLYFAILURE
		));
	}

	PCIDLIST_ABSOLUTE *list = calloc((size_t)count, sizeof(*list));

	if (list == NULL) {
		printError(E_OUTOFMEMORY);
		op->lpVtbl->Release(op);
		return 1;
	}

	IShellItemArray *items = NULL;
	int exitCode = 0;

	for (int i = 0; i < count; i++) {
		int len = GetFullPathName(files[i], 0, NULL, NULL);

		if (len == 0) {
			printError(HRESULT_FROM_WIN32(GetLastError()));
			exitCode = 1;
			goto cleanup;
		}

		wchar_t *buf = malloc((len + 1) * sizeof(wchar_t));

		if (buf == NULL) {
			printError(E_OUTOFMEMORY);
			exitCode = 1;
			goto cleanup;
		}

		if (GetFullPathName(files[i], len, buf, NULL) == 0) {
			printError(HRESULT_FROM_WIN32(GetLastError()));
			free(buf);
			exitCode = 1;
			goto cleanup;
		}

		// Resolve chained subst drives (e.g., Y: -> X: -> C:).
		// We keep resolving until we reach a real (non-subst) drive.
		wchar_t *current = buf;
		wchar_t *resolved;

		while ((resolved = resolveSubstPath(current)) != NULL) {
			if (current != buf) {
				free(current);
			}

			current = resolved;
		}

		list[i] = ILCreateFromPath(current);

		if (list[i] == NULL) {
			printError(HRESULT_FROM_WIN32(GetLastError()));
			if (current != buf) {
				free(current);
			}

			free(buf);
			exitCode = 1;
			goto cleanup;
		}

		if (current != buf) {
			free(current);
		}

		free(buf);
	}

	DWORD cookie;
	HRESULT result = SHCreateShellItemArrayFromIDLists(count, list, &items);

	if (FAILED(result)) {
		printError(result);
		exitCode = 1;
		goto cleanup;
	}

	result = op->lpVtbl->Advise(op, &progressSink, &cookie);

	if (FAILED(result)) {
		printError(result);
		exitCode = 1;
		goto cleanup;
	}

	result = op->lpVtbl->DeleteItems(op, (IUnknown*)items);

	if (FAILED(result)) {
		printError(result);
		exitCode = 1;
		goto cleanup;
	}

	result = op->lpVtbl->PerformOperations(op);

	if (FAILED(result)) {
		printError(result);
		exitCode = 1;
		goto cleanup;
	}

	BOOL aborted = FALSE;
	op->lpVtbl->GetAnyOperationsAborted(op, &aborted);

	if (aborted) {
		fwprintf(stderr, L"error: operation was aborted\n");
		exitCode = 1;
	}

cleanup:
	if (items != NULL) {
		items->lpVtbl->Release(items);
	}

	op->lpVtbl->Release(op);
	freeIdListArray(list, count);
	return exitCode;
}
