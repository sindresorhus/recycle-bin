// detroit.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "edge_i.c"
const CLSID CLSID_Detour = { 0xf5353c58, 0xcfd9, 0x4204, { 0x8d, 0x92, 0xd2, 0x74, 0xc7, 0x57, 0x8b, 0x53 } };

class Detour : public IDetour
{
public:
    // IUnknown
    ULONG __stdcall AddRef();
    ULONG __stdcall Release();
    HRESULT __stdcall QueryInterface(REFIID riid, void** ppv);
 
    // IDetour
	HRESULT __stdcall StartOperations(){ return S_OK; }
    HRESULT __stdcall FinishOperations(
         HRESULT hrResult){ return S_OK; }

    HRESULT __stdcall PreRenameItem(
         DWORD dwFlags,
         IShellItem *psiItem,
         LPCWSTR pszNewName){ return S_OK; }

    HRESULT __stdcall PostRenameItem(
         DWORD dwFlags,
         IShellItem *psiItem,
         LPCWSTR pszNewName,
         HRESULT hrRename,
         IShellItem *psiNewlyCreated){ return S_OK; }

    HRESULT __stdcall PreMoveItem(
         DWORD dwFlags,
         IShellItem *psiItem,
         IShellItem *psiDestinationFolder,
         LPCWSTR pszNewName){ return S_OK; }

    HRESULT __stdcall PostMoveItem(
         DWORD dwFlags,
         IShellItem *psiItem,
         IShellItem *psiDestinationFolder,
          LPCWSTR pszNewName,
         HRESULT hrMove,
         IShellItem *psiNewlyCreated){ return S_OK; }

    HRESULT __stdcall PreCopyItem(
         DWORD dwFlags,
         IShellItem *psiItem,
         IShellItem *psiDestinationFolder,
        LPCWSTR pszNewName){ return S_OK; }

    HRESULT __stdcall PostCopyItem(
         DWORD dwFlags,
         IShellItem *psiItem,
         IShellItem *psiDestinationFolder,
          LPCWSTR pszNewName,
         HRESULT hrCopy,
         IShellItem *psiNewlyCreated){ return S_OK; }

    HRESULT __stdcall PreDeleteItem(
         DWORD dwFlags,
         IShellItem *psiItem);

    HRESULT __stdcall PostDeleteItem(
         DWORD dwFlags,
         IShellItem *psiItem,
         HRESULT hrDelete,
         IShellItem *psiNewlyCreated){ return S_OK; }

    HRESULT __stdcall PreNewItem(
         DWORD dwFlags,
         IShellItem *psiDestinationFolder,
        LPCWSTR pszNewName){ return S_OK; }

    HRESULT __stdcall PostNewItem(
         DWORD dwFlags,
         IShellItem *psiDestinationFolder,
          LPCWSTR pszNewName,
          LPCWSTR pszTemplateName,
         DWORD dwFileAttributes,
         HRESULT hrNew,
         IShellItem *psiNewItem){ return S_OK; }

    HRESULT __stdcall UpdateProgress(
         UINT iWorkTotal,
         UINT iWorkSoFar){ return S_OK; }

    HRESULT __stdcall ResetTimer(){ return S_OK; }

    HRESULT __stdcall PauseTimer(){ return S_OK; }

    HRESULT __stdcall ResumeTimer(){ return S_OK; }

    HRESULT __stdcall CreateUnit(REFCLSID rclsid, REFIID riid, LPVOID *ppUnk);



    Detour() : m_cRef(1) { }
    ~Detour() {
    }
 
private:
    ULONG m_cRef;
};
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
  if (rclsid !=  CLSID_Detour) {
  	 return CLASS_E_CLASSNOTAVAILABLE;	
 
  }
 
  IUnknown *pUnknown = NULL;
  if (rclsid == CLSID_Detour) {
    pUnknown = new Detour();
  }
 
  HRESULT hr = pUnknown->QueryInterface(riid, ppv);
  if (FAILED(hr)) {
    delete pUnknown;
  }
 
  return hr;
  
}

///////////////////////////////////////////////////////////////////////////////////
 
ULONG __stdcall Detour::AddRef() {
  return ++m_cRef;
}
 
///////////////////////////////////////////////////////////////////////////////////
 
ULONG __stdcall Detour::Release() {
  if (--m_cRef != 0)
    return m_cRef;
  delete this;
  return 0;
}
 
///////////////////////////////////////////////////////////////////////////////////
 
HRESULT __stdcall Detour::QueryInterface(REFIID riid, void **ppv) {
 
  if (riid == IID_IUnknown) {
    *ppv = (IUnknown *)this;
  } else if (riid == IID_IDetour) {
    *ppv = (IDetour *)this;
  } else if (riid == IID_IFileOperationProgressSink) {
    *ppv = dynamic_cast<IFileOperationProgressSink *>(this);
	if(*ppv == NULL) MessageBox(NULL,L"zcd",NULL,0);
  } else {
    *ppv = NULL;
    return E_NOINTERFACE;
  }
  AddRef();
  return S_OK;
}
 
///////////////////////////////////////////////////////////////////////////////////

HRESULT __stdcall Detour::CreateUnit(REFCLSID rclsid, REFIID riid, LPVOID *ppUnk) {

    return S_OK;

//  return E_NOINTERFACE;
}
 
     HRESULT __stdcall Detour::PreDeleteItem(
         DWORD dwFlags,
         IShellItem *psiItem)
	 {
			if( (dwFlags & TSF_DELETE_RECYCLE_IF_POSSIBLE) != 0)
			return S_OK;
			else
			return E_NOINTERFACE;
	 }
