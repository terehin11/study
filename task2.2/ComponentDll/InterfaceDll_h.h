

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Thu Apr 04 15:54:01 2019
 */
/* Compiler settings for InterfaceDll.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.00.0603 
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

#ifndef __InterfaceDll_h_h__
#define __InterfaceDll_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICollection_FWD_DEFINED__
#define __ICollection_FWD_DEFINED__
typedef interface ICollection ICollection;

#endif 	/* __ICollection_FWD_DEFINED__ */


#ifndef __IEnumerator_FWD_DEFINED__
#define __IEnumerator_FWD_DEFINED__
typedef interface IEnumerator IEnumerator;

#endif 	/* __IEnumerator_FWD_DEFINED__ */


#ifndef __CList_FWD_DEFINED__
#define __CList_FWD_DEFINED__

#ifdef __cplusplus
typedef class CList CList;
#else
typedef struct CList CList;
#endif /* __cplusplus */

#endif 	/* __CList_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_InterfaceDll_0000_0000 */
/* [local] */ 


enum ObjectType
    {
        otInt	= 0,
        otDouble	= ( otInt + 1 ) ,
        otArray	= ( otDouble + 1 ) 
    } ;
struct ObjectArray
    {
    struct Object *Data;
    unsigned int Count;
    } ;
struct Object
    {
    enum ObjectType Type;
    /* [switch_is] */ /* [switch_type] */ union 
        {
        /* [case()] */ int Int;
        /* [case()] */ double Double;
        /* [case()] */ struct ObjectArray *Array;
        } 	Value;
    } ;


extern RPC_IF_HANDLE __MIDL_itf_InterfaceDll_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_InterfaceDll_0000_0000_v0_0_s_ifspec;

#ifndef __ICollection_INTERFACE_DEFINED__
#define __ICollection_INTERFACE_DEFINED__

/* interface ICollection */
/* [uuid][object] */ 


EXTERN_C const IID IID_ICollection;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BAE1D3B7-6DC9-4B0B-AE41-0B805DA2BD6E")
    ICollection : public IUnknown
    {
    public:
        virtual HRESULT __stdcall Add( 
            struct Object obj) = 0;
        
        virtual HRESULT __stdcall Remove( 
            struct Object obj) = 0;
        
        virtual HRESULT __stdcall GetCount( 
            unsigned int *count) = 0;
        
        virtual HRESULT __stdcall ToArray( 
            struct ObjectArray **arr) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICollectionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICollection * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICollection * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICollection * This);
        
        HRESULT ( __stdcall *Add )( 
            ICollection * This,
            struct Object obj);
        
        HRESULT ( __stdcall *Remove )( 
            ICollection * This,
            struct Object obj);
        
        HRESULT ( __stdcall *GetCount )( 
            ICollection * This,
            unsigned int *count);
        
        HRESULT ( __stdcall *ToArray )( 
            ICollection * This,
            struct ObjectArray **arr);
        
        END_INTERFACE
    } ICollectionVtbl;

    interface ICollection
    {
        CONST_VTBL struct ICollectionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICollection_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICollection_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICollection_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICollection_Add(This,obj)	\
    ( (This)->lpVtbl -> Add(This,obj) ) 

#define ICollection_Remove(This,obj)	\
    ( (This)->lpVtbl -> Remove(This,obj) ) 

#define ICollection_GetCount(This,count)	\
    ( (This)->lpVtbl -> GetCount(This,count) ) 

#define ICollection_ToArray(This,arr)	\
    ( (This)->lpVtbl -> ToArray(This,arr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICollection_INTERFACE_DEFINED__ */


#ifndef __IEnumerator_INTERFACE_DEFINED__
#define __IEnumerator_INTERFACE_DEFINED__

/* interface IEnumerator */
/* [uuid][object] */ 


EXTERN_C const IID IID_IEnumerator;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("DDD1F943-4473-45AC-BBB3-71EDDCCFEA16")
    IEnumerator : public IUnknown
    {
    public:
        virtual HRESULT __stdcall Reset( void) = 0;
        
        virtual HRESULT __stdcall MoveNext( 
            int *result) = 0;
        
        virtual HRESULT __stdcall GetCurrent( 
            struct Object *obj) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEnumeratorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEnumerator * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEnumerator * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEnumerator * This);
        
        HRESULT ( __stdcall *Reset )( 
            IEnumerator * This);
        
        HRESULT ( __stdcall *MoveNext )( 
            IEnumerator * This,
            int *result);
        
        HRESULT ( __stdcall *GetCurrent )( 
            IEnumerator * This,
            struct Object *obj);
        
        END_INTERFACE
    } IEnumeratorVtbl;

    interface IEnumerator
    {
        CONST_VTBL struct IEnumeratorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEnumerator_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEnumerator_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEnumerator_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEnumerator_Reset(This)	\
    ( (This)->lpVtbl -> Reset(This) ) 

#define IEnumerator_MoveNext(This,result)	\
    ( (This)->lpVtbl -> MoveNext(This,result) ) 

#define IEnumerator_GetCurrent(This,obj)	\
    ( (This)->lpVtbl -> GetCurrent(This,obj) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEnumerator_INTERFACE_DEFINED__ */



#ifndef __MyComLib_LIBRARY_DEFINED__
#define __MyComLib_LIBRARY_DEFINED__

/* library MyComLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_MyComLib;

EXTERN_C const CLSID CLSID_CList;

#ifdef __cplusplus

class DECLSPEC_UUID("BAEFF6E6-637D-484B-9C90-A1167664C6CC")
CList;
#endif
#endif /* __MyComLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


