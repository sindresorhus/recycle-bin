#define _WIN32_IE _WIN32_IE_IE70

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

int delete_files(int count, wchar_t **files) {
	size_t len = count;

	for (int i = 1; i < count; i++) {
		len += wcslen(files[i]);
	}

	wchar_t *from = malloc(len * sizeof(wchar_t));

	int pos = 0;

	for (int i = 1; i < count; i++) {
		wcscpy(&from[pos], files[i]);
		pos += wcslen(files[i]) + 1;
	}

	from[pos] = '\0';

	assert(++pos == len && "position/length mismatch");

	SHFILEOPSTRUCTW op;

	op.hwnd = NULL;
	op.wFunc = FO_DELETE;
	op.pFrom = from;
	op.pTo = NULL;
	op.fFlags = FOF_ALLOWUNDO | FOF_NO_UI;

	int ret = SHFileOperationW(&op);

	free(from);

	return ret;
}

int delete_files_new(int count, wchar_t **files) {
	CHECK(CoInitializeEx(NULL, COINIT_MULTITHREADED));

	IFileOperation *op;

	CHECK(CoCreateInstance(
		&CLSID_FileOperation,
		NULL,
		CLSCTX_ALL,
		&IID_IFileOperation,
		(void**)&op
	));

	CHECK_OBJ(op, op->lpVtbl->SetOperationFlags(
		op,
		FOFX_ADDUNDORECORD |
		FOFX_RECYCLEONDELETE |
		FOF_NOERRORUI |
		FOF_SILENT |
		FOFX_EARLYFAILURE
	));

	PCIDLIST_ABSOLUTE list[count - 1];

	for (int i = 1; i < count; i++) {
		for (wchar_t *chr = files[i]; *chr; chr++) {
			if (*chr == L'/') {
				*chr = L'\\';
			}
		}

		list[i - 1] = ILCreateFromPath(files[i]);
	}

	IShellItemArray *items;

	CHECK_OBJ(op, SHCreateShellItemArrayFromIDLists(count - 1, list, &items));
	CHECK_OBJ(op, op->lpVtbl->DeleteItems(op, (IUnknown*)items));
	CHECK_OBJ(op, op->lpVtbl->PerformOperations(op));

	return op->lpVtbl->Release(op);
}

int wmain(int argc, wchar_t **argv) {
	if (argc == 2) {
		if (wcscmp(argv[1], L"--version") == 0) {
			puts("1.0.2");
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

	if (IsWindows8OrGreater()) {
		return delete_files_new(argc, argv);
	}

	return delete_files(argc, argv);
}
