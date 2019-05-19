

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Fri May 24 00:17:54 2019
 */
/* Compiler settings for edge.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __edge_h_h__
#define __edge_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IDetour_FWD_DEFINED__
#define __IDetour_FWD_DEFINED__
typedef interface IDetour IDetour;
#endif 	/* __IDetour_FWD_DEFINED__ */


/* header files for imported files */
#include "unknwn.h"
#include "Shobjidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IDetour_INTERFACE_DEFINED__
#define __IDetour_INTERFACE_DEFINED__

/* interface IDetour */
/* [uuid][object] */ 


EXTERN_C const IID IID_IDetour;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C5F45CBC-4439-418C-A9F9-05AC67525E43")
    IDetour : public IFileOperationProgressSink
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE StartOperations( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE FinishOperations( 
            /* [in] */ HRESULT hrResult) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PreRenameItem( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [string][unique][in] */ LPCWSTR pszNewName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PostRenameItem( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [string][in] */ LPCWSTR pszNewName,
            /* [in] */ HRESULT hrRename,
            /* [in] */ IShellItem *psiNewlyCreated) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PreMoveItem( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [string][unique][in] */ LPCWSTR pszNewName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PostMoveItem( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [string][unique][in] */ LPCWSTR pszNewName,
            /* [in] */ HRESULT hrMove,
            /* [in] */ IShellItem *psiNewlyCreated) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PreCopyItem( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [string][unique][in] */ LPCWSTR pszNewName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PostCopyItem( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [string][unique][in] */ LPCWSTR pszNewName,
            /* [in] */ HRESULT hrCopy,
            /* [in] */ IShellItem *psiNewlyCreated) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PreDeleteItem( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PostDeleteItem( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ HRESULT hrDelete,
            /* [in] */ IShellItem *psiNewlyCreated) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PreNewItem( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [string][unique][in] */ LPCWSTR pszNewName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PostNewItem( 
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [string][unique][in] */ LPCWSTR pszNewName,
            /* [string][unique][in] */ LPCWSTR pszTemplateName,
            /* [in] */ DWORD dwFileAttributes,
            /* [in] */ HRESULT hrNew,
            /* [in] */ IShellItem *psiNewItem) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UpdateProgress( 
            /* [in] */ UINT iWorkTotal,
            /* [in] */ UINT iWorkSoFar) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResetTimer( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE PauseTimer( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ResumeTimer( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE CreateUnit( 
            /* [in] */ REFCLSID rclsid,
            /* [in] */ REFIID riid,
            /* [retval][iid_is][out] */ LPVOID *ppUnk) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IDetourVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IDetour * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IDetour * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IDetour * This);
        
        HRESULT ( STDMETHODCALLTYPE *StartOperations )( 
            IDetour * This);
        
        HRESULT ( STDMETHODCALLTYPE *FinishOperations )( 
            IDetour * This,
            /* [in] */ HRESULT hrResult);
        
        HRESULT ( STDMETHODCALLTYPE *PreRenameItem )( 
            IDetour * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [string][unique][in] */ LPCWSTR pszNewName);
        
        HRESULT ( STDMETHODCALLTYPE *PostRenameItem )( 
            IDetour * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [string][in] */ LPCWSTR pszNewName,
            /* [in] */ HRESULT hrRename,
            /* [in] */ IShellItem *psiNewlyCreated);
        
        HRESULT ( STDMETHODCALLTYPE *PreMoveItem )( 
            IDetour * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [string][unique][in] */ LPCWSTR pszNewName);
        
        HRESULT ( STDMETHODCALLTYPE *PostMoveItem )( 
            IDetour * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [string][unique][in] */ LPCWSTR pszNewName,
            /* [in] */ HRESULT hrMove,
            /* [in] */ IShellItem *psiNewlyCreated);
        
        HRESULT ( STDMETHODCALLTYPE *PreCopyItem )( 
            IDetour * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [string][unique][in] */ LPCWSTR pszNewName);
        
        HRESULT ( STDMETHODCALLTYPE *PostCopyItem )( 
            IDetour * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [string][unique][in] */ LPCWSTR pszNewName,
            /* [in] */ HRESULT hrCopy,
            /* [in] */ IShellItem *psiNewlyCreated);
        
        HRESULT ( STDMETHODCALLTYPE *PreDeleteItem )( 
            IDetour * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem);
        
        HRESULT ( STDMETHODCALLTYPE *PostDeleteItem )( 
            IDetour * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ HRESULT hrDelete,
            /* [in] */ IShellItem *psiNewlyCreated);
        
        HRESULT ( STDMETHODCALLTYPE *PreNewItem )( 
            IDetour * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [string][unique][in] */ LPCWSTR pszNewName);
        
        HRESULT ( STDMETHODCALLTYPE *PostNewItem )( 
            IDetour * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [string][unique][in] */ LPCWSTR pszNewName,
            /* [string][unique][in] */ LPCWSTR pszTemplateName,
            /* [in] */ DWORD dwFileAttributes,
            /* [in] */ HRESULT hrNew,
            /* [in] */ IShellItem *psiNewItem);
        
        HRESULT ( STDMETHODCALLTYPE *UpdateProgress )( 
            IDetour * This,
            /* [in] */ UINT iWorkTotal,
            /* [in] */ UINT iWorkSoFar);
        
        HRESULT ( STDMETHODCALLTYPE *ResetTimer )( 
            IDetour * This);
        
        HRESULT ( STDMETHODCALLTYPE *PauseTimer )( 
            IDetour * This);
        
        HRESULT ( STDMETHODCALLTYPE *ResumeTimer )( 
            IDetour * This);
        
        HRESULT ( STDMETHODCALLTYPE *StartOperations )( 
            IDetour * This);
        
        HRESULT ( STDMETHODCALLTYPE *FinishOperations )( 
            IDetour * This,
            /* [in] */ HRESULT hrResult);
        
        HRESULT ( STDMETHODCALLTYPE *PreRenameItem )( 
            IDetour * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [string][unique][in] */ LPCWSTR pszNewName);
        
        HRESULT ( STDMETHODCALLTYPE *PostRenameItem )( 
            IDetour * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [string][in] */ LPCWSTR pszNewName,
            /* [in] */ HRESULT hrRename,
            /* [in] */ IShellItem *psiNewlyCreated);
        
        HRESULT ( STDMETHODCALLTYPE *PreMoveItem )( 
            IDetour * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [string][unique][in] */ LPCWSTR pszNewName);
        
        HRESULT ( STDMETHODCALLTYPE *PostMoveItem )( 
            IDetour * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [string][unique][in] */ LPCWSTR pszNewName,
            /* [in] */ HRESULT hrMove,
            /* [in] */ IShellItem *psiNewlyCreated);
        
        HRESULT ( STDMETHODCALLTYPE *PreCopyItem )( 
            IDetour * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [string][unique][in] */ LPCWSTR pszNewName);
        
        HRESULT ( STDMETHODCALLTYPE *PostCopyItem )( 
            IDetour * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [string][unique][in] */ LPCWSTR pszNewName,
            /* [in] */ HRESULT hrCopy,
            /* [in] */ IShellItem *psiNewlyCreated);
        
        HRESULT ( STDMETHODCALLTYPE *PreDeleteItem )( 
            IDetour * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem);
        
        HRESULT ( STDMETHODCALLTYPE *PostDeleteItem )( 
            IDetour * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiItem,
            /* [in] */ HRESULT hrDelete,
            /* [in] */ IShellItem *psiNewlyCreated);
        
        HRESULT ( STDMETHODCALLTYPE *PreNewItem )( 
            IDetour * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [string][unique][in] */ LPCWSTR pszNewName);
        
        HRESULT ( STDMETHODCALLTYPE *PostNewItem )( 
            IDetour * This,
            /* [in] */ DWORD dwFlags,
            /* [in] */ IShellItem *psiDestinationFolder,
            /* [string][unique][in] */ LPCWSTR pszNewName,
            /* [string][unique][in] */ LPCWSTR pszTemplateName,
            /* [in] */ DWORD dwFileAttributes,
            /* [in] */ HRESULT hrNew,
            /* [in] */ IShellItem *psiNewItem);
        
        HRESULT ( STDMETHODCALLTYPE *UpdateProgress )( 
            IDetour * This,
            /* [in] */ UINT iWorkTotal,
            /* [in] */ UINT iWorkSoFar);
        
        HRESULT ( STDMETHODCALLTYPE *ResetTimer )( 
            IDetour * This);
        
        HRESULT ( STDMETHODCALLTYPE *PauseTimer )( 
            IDetour * This);
        
        HRESULT ( STDMETHODCALLTYPE *ResumeTimer )( 
            IDetour * This);
        
        HRESULT ( STDMETHODCALLTYPE *CreateUnit )( 
            IDetour * This,
            /* [in] */ REFCLSID rclsid,
            /* [in] */ REFIID riid,
            /* [retval][iid_is][out] */ LPVOID *ppUnk);
        
        END_INTERFACE
    } IDetourVtbl;

    interface IDetour
    {
        CONST_VTBL struct IDetourVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IDetour_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IDetour_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IDetour_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IDetour_StartOperations(This)	\
    ( (This)->lpVtbl -> StartOperations(This) ) 

#define IDetour_FinishOperations(This,hrResult)	\
    ( (This)->lpVtbl -> FinishOperations(This,hrResult) ) 

#define IDetour_PreRenameItem(This,dwFlags,psiItem,pszNewName)	\
    ( (This)->lpVtbl -> PreRenameItem(This,dwFlags,psiItem,pszNewName) ) 

#define IDetour_PostRenameItem(This,dwFlags,psiItem,pszNewName,hrRename,psiNewlyCreated)	\
    ( (This)->lpVtbl -> PostRenameItem(This,dwFlags,psiItem,pszNewName,hrRename,psiNewlyCreated) ) 

#define IDetour_PreMoveItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName)	\
    ( (This)->lpVtbl -> PreMoveItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName) ) 

#define IDetour_PostMoveItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName,hrMove,psiNewlyCreated)	\
    ( (This)->lpVtbl -> PostMoveItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName,hrMove,psiNewlyCreated) ) 

#define IDetour_PreCopyItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName)	\
    ( (This)->lpVtbl -> PreCopyItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName) ) 

#define IDetour_PostCopyItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName,hrCopy,psiNewlyCreated)	\
    ( (This)->lpVtbl -> PostCopyItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName,hrCopy,psiNewlyCreated) ) 

#define IDetour_PreDeleteItem(This,dwFlags,psiItem)	\
    ( (This)->lpVtbl -> PreDeleteItem(This,dwFlags,psiItem) ) 

#define IDetour_PostDeleteItem(This,dwFlags,psiItem,hrDelete,psiNewlyCreated)	\
    ( (This)->lpVtbl -> PostDeleteItem(This,dwFlags,psiItem,hrDelete,psiNewlyCreated) ) 

#define IDetour_PreNewItem(This,dwFlags,psiDestinationFolder,pszNewName)	\
    ( (This)->lpVtbl -> PreNewItem(This,dwFlags,psiDestinationFolder,pszNewName) ) 

#define IDetour_PostNewItem(This,dwFlags,psiDestinationFolder,pszNewName,pszTemplateName,dwFileAttributes,hrNew,psiNewItem)	\
    ( (This)->lpVtbl -> PostNewItem(This,dwFlags,psiDestinationFolder,pszNewName,pszTemplateName,dwFileAttributes,hrNew,psiNewItem) ) 

#define IDetour_UpdateProgress(This,iWorkTotal,iWorkSoFar)	\
    ( (This)->lpVtbl -> UpdateProgress(This,iWorkTotal,iWorkSoFar) ) 

#define IDetour_ResetTimer(This)	\
    ( (This)->lpVtbl -> ResetTimer(This) ) 

#define IDetour_PauseTimer(This)	\
    ( (This)->lpVtbl -> PauseTimer(This) ) 

#define IDetour_ResumeTimer(This)	\
    ( (This)->lpVtbl -> ResumeTimer(This) ) 


#define IDetour_StartOperations(This)	\
    ( (This)->lpVtbl -> StartOperations(This) ) 

#define IDetour_FinishOperations(This,hrResult)	\
    ( (This)->lpVtbl -> FinishOperations(This,hrResult) ) 

#define IDetour_PreRenameItem(This,dwFlags,psiItem,pszNewName)	\
    ( (This)->lpVtbl -> PreRenameItem(This,dwFlags,psiItem,pszNewName) ) 

#define IDetour_PostRenameItem(This,dwFlags,psiItem,pszNewName,hrRename,psiNewlyCreated)	\
    ( (This)->lpVtbl -> PostRenameItem(This,dwFlags,psiItem,pszNewName,hrRename,psiNewlyCreated) ) 

#define IDetour_PreMoveItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName)	\
    ( (This)->lpVtbl -> PreMoveItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName) ) 

#define IDetour_PostMoveItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName,hrMove,psiNewlyCreated)	\
    ( (This)->lpVtbl -> PostMoveItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName,hrMove,psiNewlyCreated) ) 

#define IDetour_PreCopyItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName)	\
    ( (This)->lpVtbl -> PreCopyItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName) ) 

#define IDetour_PostCopyItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName,hrCopy,psiNewlyCreated)	\
    ( (This)->lpVtbl -> PostCopyItem(This,dwFlags,psiItem,psiDestinationFolder,pszNewName,hrCopy,psiNewlyCreated) ) 

#define IDetour_PreDeleteItem(This,dwFlags,psiItem)	\
    ( (This)->lpVtbl -> PreDeleteItem(This,dwFlags,psiItem) ) 

#define IDetour_PostDeleteItem(This,dwFlags,psiItem,hrDelete,psiNewlyCreated)	\
    ( (This)->lpVtbl -> PostDeleteItem(This,dwFlags,psiItem,hrDelete,psiNewlyCreated) ) 

#define IDetour_PreNewItem(This,dwFlags,psiDestinationFolder,pszNewName)	\
    ( (This)->lpVtbl -> PreNewItem(This,dwFlags,psiDestinationFolder,pszNewName) ) 

#define IDetour_PostNewItem(This,dwFlags,psiDestinationFolder,pszNewName,pszTemplateName,dwFileAttributes,hrNew,psiNewItem)	\
    ( (This)->lpVtbl -> PostNewItem(This,dwFlags,psiDestinationFolder,pszNewName,pszTemplateName,dwFileAttributes,hrNew,psiNewItem) ) 

#define IDetour_UpdateProgress(This,iWorkTotal,iWorkSoFar)	\
    ( (This)->lpVtbl -> UpdateProgress(This,iWorkTotal,iWorkSoFar) ) 

#define IDetour_ResetTimer(This)	\
    ( (This)->lpVtbl -> ResetTimer(This) ) 

#define IDetour_PauseTimer(This)	\
    ( (This)->lpVtbl -> PauseTimer(This) ) 

#define IDetour_ResumeTimer(This)	\
    ( (This)->lpVtbl -> ResumeTimer(This) ) 

#define IDetour_CreateUnit(This,rclsid,riid,ppUnk)	\
    ( (This)->lpVtbl -> CreateUnit(This,rclsid,riid,ppUnk) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IDetour_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


