#define _WIN32_IE _WIN32_IE_IE70

#include "progress.h"

#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include <versionhelpers.h>
#include <initguid.h>
#include <shlobj.h>

#define CHECK(result) if (FAILED(result)) {\
	return result;\
}
#define CHECK_OBJ(obj, result) if (FAILED(result)) {\
	obj->lpVtbl->Release(obj);\
	return result;\
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

int wmain(int argc, wchar_t **argv) {
	if (argc == 2) {
		if (wcscmp(argv[1], L"--version") == 0) {
			puts("2.0.0");
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

	PCIDLIST_ABSOLUTE list[count];

	for (int i = 0; i < count; i++) {
		int len = GetFullPathName(files[i], 0, NULL, NULL);

		if (len == 0) {
			op->lpVtbl->Release(op);

			return 1;
		}

		wchar_t *buf = malloc((len + 1) * sizeof(wchar_t));

		GetFullPathName(files[i], len, buf, NULL);

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

		if (current != buf) {
			free(current);
		}

		free(buf);
	}

	IShellItemArray *items;
	DWORD cookie;

	CHECK_OBJ(op, SHCreateShellItemArrayFromIDLists(count, list, &items));
	CHECK_OBJ(op, op->lpVtbl->Advise(op, &progressSink, &cookie));
	CHECK_OBJ(op, op->lpVtbl->DeleteItems(op, (IUnknown*)items));
	CHECK_OBJ(op, op->lpVtbl->PerformOperations(op));

	return op->lpVtbl->Release(op);
}
