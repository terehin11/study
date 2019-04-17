

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Apr 11 17:33:24 2019
 */
/* Compiler settings for Component.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
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

#ifndef __Component_i_h__
#define __Component_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IComponentClass_FWD_DEFINED__
#define __IComponentClass_FWD_DEFINED__
typedef interface IComponentClass IComponentClass;

#endif 	/* __IComponentClass_FWD_DEFINED__ */


#ifndef __ComponentClass_FWD_DEFINED__
#define __ComponentClass_FWD_DEFINED__

#ifdef __cplusplus
typedef class ComponentClass ComponentClass;
#else
typedef struct ComponentClass ComponentClass;
#endif /* __cplusplus */

#endif 	/* __ComponentClass_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IComponentClass_INTERFACE_DEFINED__
#define __IComponentClass_INTERFACE_DEFINED__

/* interface IComponentClass */
/* [unique][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IComponentClass;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C3B731C9-55E5-429A-BB3B-BACC9BAADC5A")
    IComponentClass : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Add( 
            /* [in] */ DOUBLE value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Remove( 
            /* [in] */ DOUBLE value) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetData( 
            /* [retval][out] */ SAFEARRAY * *_array) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Count( 
            /* [retval][out] */ ULONG *pVal) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_Mean( 
            /* [retval][out] */ DOUBLE *pVal) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IComponentClassVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IComponentClass * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IComponentClass * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IComponentClass * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IComponentClass * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IComponentClass * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IComponentClass * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IComponentClass * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Add )( 
            IComponentClass * This,
            /* [in] */ DOUBLE value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Remove )( 
            IComponentClass * This,
            /* [in] */ DOUBLE value);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetData )( 
            IComponentClass * This,
            /* [retval][out] */ SAFEARRAY * *_array);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Count )( 
            IComponentClass * This,
            /* [retval][out] */ ULONG *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Mean )( 
            IComponentClass * This,
            /* [retval][out] */ DOUBLE *pVal);
        
        END_INTERFACE
    } IComponentClassVtbl;

    interface IComponentClass
    {
        CONST_VTBL struct IComponentClassVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IComponentClass_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IComponentClass_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IComponentClass_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IComponentClass_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IComponentClass_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IComponentClass_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IComponentClass_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IComponentClass_Add(This,value)	\
    ( (This)->lpVtbl -> Add(This,value) ) 

#define IComponentClass_Remove(This,value)	\
    ( (This)->lpVtbl -> Remove(This,value) ) 

#define IComponentClass_GetData(This,_array)	\
    ( (This)->lpVtbl -> GetData(This,_array) ) 

#define IComponentClass_get_Count(This,pVal)	\
    ( (This)->lpVtbl -> get_Count(This,pVal) ) 

#define IComponentClass_get_Mean(This,pVal)	\
    ( (This)->lpVtbl -> get_Mean(This,pVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IComponentClass_INTERFACE_DEFINED__ */



#ifndef __ComponentLib_LIBRARY_DEFINED__
#define __ComponentLib_LIBRARY_DEFINED__

/* library ComponentLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_ComponentLib;

EXTERN_C const CLSID CLSID_ComponentClass;

#ifdef __cplusplus

class DECLSPEC_UUID("D742843C-95B8-43F9-9FBB-CE04EEB3488A")
ComponentClass;
#endif
#endif /* __ComponentLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  LPSAFEARRAY_UserSize(     unsigned long *, unsigned long            , LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserMarshal(  unsigned long *, unsigned char *, LPSAFEARRAY * ); 
unsigned char * __RPC_USER  LPSAFEARRAY_UserUnmarshal(unsigned long *, unsigned char *, LPSAFEARRAY * ); 
void                      __RPC_USER  LPSAFEARRAY_UserFree(     unsigned long *, LPSAFEARRAY * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


