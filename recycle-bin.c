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
		list[i] = ILCreateFromPath(buf);

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
