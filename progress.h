#include <initguid.h>
#include <shlobj.h>

HRESULT STDMETHODCALLTYPE QueryInterface(
    IFileOperationProgressSink *this,
    REFIID riid,
    void **ppv
) {
	if (riid == &IID_IUnknown || riid == &IID_IFileOperationProgressSink) {
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

HRESULT STDMETHODCALLTYPE FinishOperations(
    IFileOperationProgressSink *this,
    HRESULT hrResult
) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PreRenameItem(
    IFileOperationProgressSink *this,
    DWORD dwFlags,
    IShellItem *psiItem,
    LPCWSTR pszNewName
) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PostRenameItem(
    IFileOperationProgressSink *this,
    DWORD dwFlags,
    IShellItem *psiItem,
    LPCWSTR pszNewName,
    HRESULT hrRename,
    IShellItem *psiNewlyCreated
) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PreMoveItem(
    IFileOperationProgressSink *this,
    DWORD dwFlags,
    IShellItem *psiItem,
    IShellItem *psiDestinationFolder,
    LPCWSTR pszNewNam
) {
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

HRESULT STDMETHODCALLTYPE ResetTimer(IFileOperationProgressSink *this) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE PauseTimer(IFileOperationProgressSink *this) {
	return S_OK;
}

HRESULT STDMETHODCALLTYPE ResumeTimer(IFileOperationProgressSink *this) {
	return S_OK;
}

static IFileOperationProgressSinkVtbl progressSinkVtbl = {
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

static IFileOperationProgressSink progressSink = { &progressSinkVtbl };
