 // ADMN.cpp : Implementation of DLL Exports.


// Note: Proxy/Stub Information
//		To build a separate proxy/stub DLL, 
//		run nmake -f ADMNps.mk in the project directory.

#include "stdafx.h"
#include "resource.h"
#include "initguid.h"
#include "ADMN.h"

#include "ADMN_i.c"
#include "ADMNObj.h"
#include "ADMNapp.h"


#ifdef	_DEBUG
#define	new	DEBUG_NEW
#endif

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
	OBJECT_ENTRY(CLSID_ADMNObj, CADMNObj)
END_OBJECT_MAP()


CADMNApp theApp;

BOOL CADMNApp::InitInstance()
{
	AfxEnableControlContainer();
	_Module.Init(ObjectMap, m_hInstance);
	SetADMNObj(NULL);
	return CWinApp::InitInstance();
}

int CADMNApp::ExitInstance()
{
	_Module.Term();
	return CWinApp::ExitInstance();
}

long CADMNApp::GetAppCode()
{
	return m_pADMNobj->GetAppCode();
}

CString CADMNApp::GetAppODBC()
{
	return m_pADMNobj->GetODBC();
}


/////////////////////////////////////////////////////////////////////////////
// Used to determine whether the DLL can be unloaded by OLE

STDAPI DllCanUnloadNow(void)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return (AfxDllCanUnloadNow()==S_OK && _Module.GetLockCount()==0) ? S_OK : S_FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// Returns a class factory to create an object of the requested type

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	return _Module.GetClassObject(rclsid, riid, ppv);
}

/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	// registers object, typelib and all interfaces in typelib
	return _Module.RegisterServer(TRUE);
}

/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	_Module.UnregisterServer();
	return S_OK;
}


