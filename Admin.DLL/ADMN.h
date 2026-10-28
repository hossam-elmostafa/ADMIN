/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Wed Oct 01 20:57:02 2025
 */
/* Compiler settings for ADMN.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
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

#ifndef __ADMN_h__
#define __ADMN_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IADMNObj_FWD_DEFINED__
#define __IADMNObj_FWD_DEFINED__
typedef interface IADMNObj IADMNObj;
#endif 	/* __IADMNObj_FWD_DEFINED__ */


#ifndef __ADMNObj_FWD_DEFINED__
#define __ADMNObj_FWD_DEFINED__

#ifdef __cplusplus
typedef class ADMNObj ADMNObj;
#else
typedef struct ADMNObj ADMNObj;
#endif /* __cplusplus */

#endif 	/* __ADMNObj_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IADMNObj_INTERFACE_DEFINED__
#define __IADMNObj_INTERFACE_DEFINED__

/* interface IADMNObj */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IADMNObj;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("51FA7D21-82F3-11D2-A9BC-444553540000")
    IADMNObj : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetParent( 
            long pParent) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Initialize( 
            int nAppCode,
            BSTR bstrProfile,
            long lUserID,
            BSTR bstrODBC,
            long lLanguage,
            BSTR bstrInitModule) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetLanguage( 
            BOOL bArabic) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CloseAll( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetModal( 
            BOOL bModalVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetConnectionString( 
            /* [out] */ BSTR __RPC_FAR *bstrConnection) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetUserName( 
            BSTR __RPC_FAR *bstrName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetLanguage( 
            /* [retval][out] */ BOOL __RPC_FAR *bArabic) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowScreenFromAttachment( 
            BSTR bstrAttachmentFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFormRect( 
            int nLeft,
            int nTop,
            int nRight,
            int nBottom) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ActivateForm( 
            BSTR bstrFormID,
            BOOL bByTag,
            int nSkipNo,
            BOOL bActivateLoadedScreen) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetFastSearchCriteria( 
            BSTR bstrCriteria) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetUserID( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DoFunction( 
            int nCurrentCard,
            BSTR bstrTableName,
            int nStatus,
            BOOL bModal,
            BSTR bstrWhereClause) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCurrentMenuItemID( 
            UINT unMenuID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetDBType( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetRegHandleDB( 
            LPDISPATCH lpRegHandleDB) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE HandOverSubjectType( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OpenedHandOver( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClosedHandOver( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowDocumentLibrary( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowDocumentTemplates( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GenerateTender( 
            BSTR bstrTemplate,
            BSTR bstrTenderNo,
            BSTR bstrOutputFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GenerateContract( 
            BSTR bstrTemplate,
            BSTR bstrContractNo,
            BSTR bstrOutputFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowTenderTree( 
            BSTR bstrTenderNo,
            BOOL bLocked) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowContractTree( 
            BSTR bstrContractNo,
            BOOL bLocked) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowReportsInfo( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IADMNObjVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IADMNObj __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IADMNObj __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IADMNObj __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IADMNObj __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IADMNObj __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IADMNObj __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IADMNObj __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetParent )( 
            IADMNObj __RPC_FAR * This,
            long pParent);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Initialize )( 
            IADMNObj __RPC_FAR * This,
            int nAppCode,
            BSTR bstrProfile,
            long lUserID,
            BSTR bstrODBC,
            long lLanguage,
            BSTR bstrInitModule);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetLanguage )( 
            IADMNObj __RPC_FAR * This,
            BOOL bArabic);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CloseAll )( 
            IADMNObj __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetModal )( 
            IADMNObj __RPC_FAR * This,
            BOOL bModalVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetConnectionString )( 
            IADMNObj __RPC_FAR * This,
            /* [out] */ BSTR __RPC_FAR *bstrConnection);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetUserName )( 
            IADMNObj __RPC_FAR * This,
            BSTR __RPC_FAR *bstrName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetLanguage )( 
            IADMNObj __RPC_FAR * This,
            /* [retval][out] */ BOOL __RPC_FAR *bArabic);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowScreenFromAttachment )( 
            IADMNObj __RPC_FAR * This,
            BSTR bstrAttachmentFile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFormRect )( 
            IADMNObj __RPC_FAR * This,
            int nLeft,
            int nTop,
            int nRight,
            int nBottom);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ActivateForm )( 
            IADMNObj __RPC_FAR * This,
            BSTR bstrFormID,
            BOOL bByTag,
            int nSkipNo,
            BOOL bActivateLoadedScreen);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetFastSearchCriteria )( 
            IADMNObj __RPC_FAR * This,
            BSTR bstrCriteria);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetUserID )( 
            IADMNObj __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *DoFunction )( 
            IADMNObj __RPC_FAR * This,
            int nCurrentCard,
            BSTR bstrTableName,
            int nStatus,
            BOOL bModal,
            BSTR bstrWhereClause);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetCurrentMenuItemID )( 
            IADMNObj __RPC_FAR * This,
            UINT unMenuID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetDBType )( 
            IADMNObj __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *SetRegHandleDB )( 
            IADMNObj __RPC_FAR * This,
            LPDISPATCH lpRegHandleDB);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *HandOverSubjectType )( 
            IADMNObj __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *OpenedHandOver )( 
            IADMNObj __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ClosedHandOver )( 
            IADMNObj __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowDocumentLibrary )( 
            IADMNObj __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowDocumentTemplates )( 
            IADMNObj __RPC_FAR * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GenerateTender )( 
            IADMNObj __RPC_FAR * This,
            BSTR bstrTemplate,
            BSTR bstrTenderNo,
            BSTR bstrOutputFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GenerateContract )( 
            IADMNObj __RPC_FAR * This,
            BSTR bstrTemplate,
            BSTR bstrContractNo,
            BSTR bstrOutputFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowTenderTree )( 
            IADMNObj __RPC_FAR * This,
            BSTR bstrTenderNo,
            BOOL bLocked);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowContractTree )( 
            IADMNObj __RPC_FAR * This,
            BSTR bstrContractNo,
            BOOL bLocked);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *ShowReportsInfo )( 
            IADMNObj __RPC_FAR * This);
        
        END_INTERFACE
    } IADMNObjVtbl;

    interface IADMNObj
    {
        CONST_VTBL struct IADMNObjVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IADMNObj_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IADMNObj_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IADMNObj_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IADMNObj_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IADMNObj_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IADMNObj_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IADMNObj_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IADMNObj_SetParent(This,pParent)	\
    (This)->lpVtbl -> SetParent(This,pParent)

#define IADMNObj_Initialize(This,nAppCode,bstrProfile,lUserID,bstrODBC,lLanguage,bstrInitModule)	\
    (This)->lpVtbl -> Initialize(This,nAppCode,bstrProfile,lUserID,bstrODBC,lLanguage,bstrInitModule)

#define IADMNObj_SetLanguage(This,bArabic)	\
    (This)->lpVtbl -> SetLanguage(This,bArabic)

#define IADMNObj_CloseAll(This)	\
    (This)->lpVtbl -> CloseAll(This)

#define IADMNObj_SetModal(This,bModalVal)	\
    (This)->lpVtbl -> SetModal(This,bModalVal)

#define IADMNObj_GetConnectionString(This,bstrConnection)	\
    (This)->lpVtbl -> GetConnectionString(This,bstrConnection)

#define IADMNObj_GetUserName(This,bstrName)	\
    (This)->lpVtbl -> GetUserName(This,bstrName)

#define IADMNObj_GetLanguage(This,bArabic)	\
    (This)->lpVtbl -> GetLanguage(This,bArabic)

#define IADMNObj_ShowScreenFromAttachment(This,bstrAttachmentFile)	\
    (This)->lpVtbl -> ShowScreenFromAttachment(This,bstrAttachmentFile)

#define IADMNObj_SetFormRect(This,nLeft,nTop,nRight,nBottom)	\
    (This)->lpVtbl -> SetFormRect(This,nLeft,nTop,nRight,nBottom)

#define IADMNObj_ActivateForm(This,bstrFormID,bByTag,nSkipNo,bActivateLoadedScreen)	\
    (This)->lpVtbl -> ActivateForm(This,bstrFormID,bByTag,nSkipNo,bActivateLoadedScreen)

#define IADMNObj_SetFastSearchCriteria(This,bstrCriteria)	\
    (This)->lpVtbl -> SetFastSearchCriteria(This,bstrCriteria)

#define IADMNObj_GetUserID(This)	\
    (This)->lpVtbl -> GetUserID(This)

#define IADMNObj_DoFunction(This,nCurrentCard,bstrTableName,nStatus,bModal,bstrWhereClause)	\
    (This)->lpVtbl -> DoFunction(This,nCurrentCard,bstrTableName,nStatus,bModal,bstrWhereClause)

#define IADMNObj_SetCurrentMenuItemID(This,unMenuID)	\
    (This)->lpVtbl -> SetCurrentMenuItemID(This,unMenuID)

#define IADMNObj_GetDBType(This)	\
    (This)->lpVtbl -> GetDBType(This)

#define IADMNObj_SetRegHandleDB(This,lpRegHandleDB)	\
    (This)->lpVtbl -> SetRegHandleDB(This,lpRegHandleDB)

#define IADMNObj_HandOverSubjectType(This)	\
    (This)->lpVtbl -> HandOverSubjectType(This)

#define IADMNObj_OpenedHandOver(This)	\
    (This)->lpVtbl -> OpenedHandOver(This)

#define IADMNObj_ClosedHandOver(This)	\
    (This)->lpVtbl -> ClosedHandOver(This)

#define IADMNObj_ShowDocumentLibrary(This)	\
    (This)->lpVtbl -> ShowDocumentLibrary(This)

#define IADMNObj_ShowDocumentTemplates(This)	\
    (This)->lpVtbl -> ShowDocumentTemplates(This)

#define IADMNObj_GenerateTender(This,bstrTemplate,bstrTenderNo,bstrOutputFileName)	\
    (This)->lpVtbl -> GenerateTender(This,bstrTemplate,bstrTenderNo,bstrOutputFileName)

#define IADMNObj_GenerateContract(This,bstrTemplate,bstrContractNo,bstrOutputFileName)	\
    (This)->lpVtbl -> GenerateContract(This,bstrTemplate,bstrContractNo,bstrOutputFileName)

#define IADMNObj_ShowTenderTree(This,bstrTenderNo,bLocked)	\
    (This)->lpVtbl -> ShowTenderTree(This,bstrTenderNo,bLocked)

#define IADMNObj_ShowContractTree(This,bstrContractNo,bLocked)	\
    (This)->lpVtbl -> ShowContractTree(This,bstrContractNo,bLocked)

#define IADMNObj_ShowReportsInfo(This)	\
    (This)->lpVtbl -> ShowReportsInfo(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_SetParent_Proxy( 
    IADMNObj __RPC_FAR * This,
    long pParent);


void __RPC_STUB IADMNObj_SetParent_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_Initialize_Proxy( 
    IADMNObj __RPC_FAR * This,
    int nAppCode,
    BSTR bstrProfile,
    long lUserID,
    BSTR bstrODBC,
    long lLanguage,
    BSTR bstrInitModule);


void __RPC_STUB IADMNObj_Initialize_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_SetLanguage_Proxy( 
    IADMNObj __RPC_FAR * This,
    BOOL bArabic);


void __RPC_STUB IADMNObj_SetLanguage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_CloseAll_Proxy( 
    IADMNObj __RPC_FAR * This);


void __RPC_STUB IADMNObj_CloseAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_SetModal_Proxy( 
    IADMNObj __RPC_FAR * This,
    BOOL bModalVal);


void __RPC_STUB IADMNObj_SetModal_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_GetConnectionString_Proxy( 
    IADMNObj __RPC_FAR * This,
    /* [out] */ BSTR __RPC_FAR *bstrConnection);


void __RPC_STUB IADMNObj_GetConnectionString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_GetUserName_Proxy( 
    IADMNObj __RPC_FAR * This,
    BSTR __RPC_FAR *bstrName);


void __RPC_STUB IADMNObj_GetUserName_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_GetLanguage_Proxy( 
    IADMNObj __RPC_FAR * This,
    /* [retval][out] */ BOOL __RPC_FAR *bArabic);


void __RPC_STUB IADMNObj_GetLanguage_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_ShowScreenFromAttachment_Proxy( 
    IADMNObj __RPC_FAR * This,
    BSTR bstrAttachmentFile);


void __RPC_STUB IADMNObj_ShowScreenFromAttachment_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_SetFormRect_Proxy( 
    IADMNObj __RPC_FAR * This,
    int nLeft,
    int nTop,
    int nRight,
    int nBottom);


void __RPC_STUB IADMNObj_SetFormRect_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_ActivateForm_Proxy( 
    IADMNObj __RPC_FAR * This,
    BSTR bstrFormID,
    BOOL bByTag,
    int nSkipNo,
    BOOL bActivateLoadedScreen);


void __RPC_STUB IADMNObj_ActivateForm_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_SetFastSearchCriteria_Proxy( 
    IADMNObj __RPC_FAR * This,
    BSTR bstrCriteria);


void __RPC_STUB IADMNObj_SetFastSearchCriteria_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_GetUserID_Proxy( 
    IADMNObj __RPC_FAR * This);


void __RPC_STUB IADMNObj_GetUserID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_DoFunction_Proxy( 
    IADMNObj __RPC_FAR * This,
    int nCurrentCard,
    BSTR bstrTableName,
    int nStatus,
    BOOL bModal,
    BSTR bstrWhereClause);


void __RPC_STUB IADMNObj_DoFunction_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_SetCurrentMenuItemID_Proxy( 
    IADMNObj __RPC_FAR * This,
    UINT unMenuID);


void __RPC_STUB IADMNObj_SetCurrentMenuItemID_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_GetDBType_Proxy( 
    IADMNObj __RPC_FAR * This);


void __RPC_STUB IADMNObj_GetDBType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_SetRegHandleDB_Proxy( 
    IADMNObj __RPC_FAR * This,
    LPDISPATCH lpRegHandleDB);


void __RPC_STUB IADMNObj_SetRegHandleDB_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_HandOverSubjectType_Proxy( 
    IADMNObj __RPC_FAR * This);


void __RPC_STUB IADMNObj_HandOverSubjectType_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_OpenedHandOver_Proxy( 
    IADMNObj __RPC_FAR * This);


void __RPC_STUB IADMNObj_OpenedHandOver_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_ClosedHandOver_Proxy( 
    IADMNObj __RPC_FAR * This);


void __RPC_STUB IADMNObj_ClosedHandOver_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_ShowDocumentLibrary_Proxy( 
    IADMNObj __RPC_FAR * This);


void __RPC_STUB IADMNObj_ShowDocumentLibrary_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_ShowDocumentTemplates_Proxy( 
    IADMNObj __RPC_FAR * This);


void __RPC_STUB IADMNObj_ShowDocumentTemplates_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_GenerateTender_Proxy( 
    IADMNObj __RPC_FAR * This,
    BSTR bstrTemplate,
    BSTR bstrTenderNo,
    BSTR bstrOutputFileName);


void __RPC_STUB IADMNObj_GenerateTender_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_GenerateContract_Proxy( 
    IADMNObj __RPC_FAR * This,
    BSTR bstrTemplate,
    BSTR bstrContractNo,
    BSTR bstrOutputFileName);


void __RPC_STUB IADMNObj_GenerateContract_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_ShowTenderTree_Proxy( 
    IADMNObj __RPC_FAR * This,
    BSTR bstrTenderNo,
    BOOL bLocked);


void __RPC_STUB IADMNObj_ShowTenderTree_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_ShowContractTree_Proxy( 
    IADMNObj __RPC_FAR * This,
    BSTR bstrContractNo,
    BOOL bLocked);


void __RPC_STUB IADMNObj_ShowContractTree_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IADMNObj_ShowReportsInfo_Proxy( 
    IADMNObj __RPC_FAR * This);


void __RPC_STUB IADMNObj_ShowReportsInfo_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IADMNObj_INTERFACE_DEFINED__ */



#ifndef __ADMNLib_LIBRARY_DEFINED__
#define __ADMNLib_LIBRARY_DEFINED__

/* library ADMNLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ADMNLib;

EXTERN_C const CLSID CLSID_ADMNObj;

#ifdef __cplusplus

class DECLSPEC_UUID("F4E06E56-62AB-4732-AF44-9E24CD9F0C66")
ADMNObj;
#endif
#endif /* __ADMNLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
