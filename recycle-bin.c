#define _WIN32_IE _WIN32_IE_IE70

#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include <versionhelpers.h>
#include <initguid.h>
#include <shlobj.h>
#include <unknwn.h>

#define CHECK(result) if (FAILED(result)) {\
	return result;\
}
#define CHECK_OBJ(obj, result) if (FAILED(result)) {\
	obj->lpVtbl->Release(obj);\
	return result;\
}

HRESULT STDMETHODCALLTYPE QueryInterface(IFileOperationProgressSink *this, REFIID riid, void **ppv) {
	if (IsEqualIID(riid, &IID_IUnknown) || IsEqualIID(riid, &IID_IFileOperationProgressSink)) {
		*ppv = this;

		return S_OK;
	}

	*ppv = NULL;

	return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE AddRef(IFileOperationProgressSink *this) {
	return S_OK;
}

ULONG STDMETHODCALLTYPE Release(IFileOperationProgressSink *this) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE StartOperations(IFileOperationProgressSink *this) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE FinishOperations(IFileOperationProgressSink *this, HRESULT hrResult) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PreRenameItem(IFileOperationProgressSink *this, DWORD dwFlags, IShellItem *psiItem, LPCWSTR pszNewName) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PostRenameItem(IFileOperationProgressSink *this, DWORD dwFlags, IShellItem *psiItem, LPCWSTR pszNewName, HRESULT hrRename, IShellItem *psiNewlyCreated) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PreMoveItem(IFileOperationProgressSink *this, DWORD dwFlags, IShellItem *psiItem, IShellItem *psiDestinationFolder, LPCWSTR pszNewName) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PostMoveItem(
	IFileOperationProgressSink *this,
	DWORD dwFlags,
	IShellItem *psiItem,
	IShellItem *psiDestinationFolder,
	LPCWSTR pszNewName,
	HRESULT hrMove,
	IShellItem *psiNewlyCreated
) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PreCopyItem(
	IFileOperationProgressSink *this,
	DWORD dwFlags,
	IShellItem *psiItem,
	IShellItem *psiDestinationFolder,
	LPCWSTR pszNewName
) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PostCopyItem(
	IFileOperationProgressSink *this,
	DWORD dwFlags,
	IShellItem *psiItem,
	IShellItem *psiDestinationFolder,
	LPCWSTR pszNewName,
	HRESULT hrCopy,
	IShellItem *psiNewlyCreated
) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PreDeleteItem(
	IFileOperationProgressSink *this,
	DWORD dwFlags,
	IShellItem *psiItem
) {
	if (dwFlags & TSF_DELETE_RECYCLE_IF_POSSIBLE) {
		return S_OK;
	}

	return E_ABORT;
}

HRESULT STDMETHODCALLTYPE PostDeleteItem(
	IFileOperationProgressSink *this,
	DWORD dwFlags,
	IShellItem *psiItem,
	HRESULT hrDelete,
	IShellItem *psiNewlyCreated
) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PreNewItem(
	IFileOperationProgressSink *this,
	DWORD dwFlags,
	IShellItem *psiDestinationFolder,
	LPCWSTR pszNewName
) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PostNewItem(
	IFileOperationProgressSink *this,
	DWORD dwFlags,
	IShellItem *psiDestinationFolder,
	LPCWSTR pszNewName,
	LPCWSTR pszTemplateName,
	DWORD dwFileAttributes,
	HRESULT hrNew,
	IShellItem *psiNewItem
) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE UpdateProgress(
	IFileOperationProgressSink *this,
	UINT iWorkTotal,
	UINT iWorkSoFar
) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE ResetTimer(
	IFileOperationProgressSink *this
) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PauseTimer(
	IFileOperationProgressSink *this
) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE ResumeTimer(
	IFileOperationProgressSink *this
) {
	return S_OK;
}

static IFileOperationProgressSinkVtbl IFileOperationProgressSink_Vtbl = {
	QueryInterface,
	AddRef,
	Release,
	StartOperations,
	FinishOperations,
	PreRenameItem,
	PostRenameItem,
	PreMoveItem,
	PostMoveItem,
	PreCopyItem,
	PostCopyItem,
	PreDeleteItem,
	PostDeleteItem,
	PreNewItem,
	PostNewItem,
	UpdateProgress,
	ResetTimer,
	PauseTimer,
	ResumeTimer
};

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

	int count = argc - 1;
	wchar_t **files = argv + 1;

	CHECK(CoInitializeEx(NULL, COINIT_MULTITHREADED));

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

	IFileOperationProgressSink *progressSink = (IFileOperationProgressSink*)GlobalAlloc(GMEM_FIXED, sizeof(IFileOperationProgressSink));
	DWORD cookie;
	progressSink->lpVtbl = &IFileOperationProgressSink_Vtbl;

	CHECK_OBJ(op, op->lpVtbl->Advise(op, progressSink, &cookie));
	CHECK_OBJ(op, SHCreateShellItemArrayFromIDLists(count, list, &items));
	CHECK_OBJ(op, op->lpVtbl->DeleteItems(op, (IUnknown*)items));
	CHECK_OBJ(op, op->lpVtbl->PerformOperations(op));

	return op->lpVtbl->Release(op);
}
