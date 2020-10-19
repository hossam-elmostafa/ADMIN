// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// _Security properties

/////////////////////////////////////////////////////////////////////////////
// _Security operations
_Priv::_Priv()
{
	CreateDispatch("FirstPrivilegeTool.Priv");
}

_Priv::~_Priv()
{
	ReleaseDispatch();
}

_Security::_Security()
{
	CreateDispatch("FirstPrivilegeTool.Security");
}

_Security::~_Security()
{
	ReleaseDispatch();
}

_SetUp::_SetUp()
{
	CreateDispatch("FirstPrivilegeTool.Setup");
}

_SetUp::~_SetUp()
{
	ReleaseDispatch();
}

short _Security::ShowLogScreen(LPCTSTR AppCode, BOOL ShowMessageFlag, BOOL LanguageFlag)
{
	short result;
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL VTS_BOOL;
	InvokeHelper(0x60030000, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
		AppCode, ShowMessageFlag, LanguageFlag);
	return result;
}

void _Security::ShowUsersScreen(LPCTSTR ApplicationCode, BOOL ShowMessageFlag, BOOL LanguageFlag)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL VTS_BOOL;
	InvokeHelper(0x60030005, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ApplicationCode, ShowMessageFlag, LanguageFlag);
}

void _Security::WriteLogHistory(short ApplicationCode, long UserID, LPCTSTR ScreenTag, const VARIANT& RecordID, LPCTSTR ActionName)
{
	static BYTE parms[] =
		VTS_I2 VTS_I4 VTS_BSTR VTS_VARIANT VTS_BSTR;
	InvokeHelper(0x60030007, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ApplicationCode, UserID, ScreenTag, &RecordID, ActionName);
}

long _Security::ShowLogHistory(short ApplicationCode, BOOL Lang)
{
	long result;
	static BYTE parms[] =
		VTS_I2 VTS_BOOL;
	InvokeHelper(0x60030008, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		ApplicationCode, Lang);
	return result;
}

void _Security::TerminateUser()
{
	InvokeHelper(0x60030009, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long _Security::ShowUsersLogHistory(short ApplicationCode, BOOL Lang)
{
	long result;
	static BYTE parms[] =
		VTS_I2 VTS_BOOL;
	InvokeHelper(0x6003000a, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		ApplicationCode, Lang);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _Priv properties

/////////////////////////////////////////////////////////////////////////////
// _Priv operations

void _Priv::MenuBuild(LPCTSTR AppCode, long MenuHandle)
{
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x60030000, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 AppCode, MenuHandle);
}

void _Priv::ShowMenusItem(LPCTSTR MyAppCode, BOOL ShowMessageFlag, BOOL LanguageFlag)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL VTS_BOOL;
	InvokeHelper(0x60030001, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MyAppCode, ShowMessageFlag, LanguageFlag);
}

void _Priv::ShowMenusDetails(LPCTSTR MyAppCode, BOOL ShowMessageFlag, BOOL LanguageFlag)
{
	static BYTE parms[] =
		VTS_BSTR VTS_BOOL VTS_BOOL;
	InvokeHelper(0x6003000a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 MyAppCode, ShowMessageFlag, LanguageFlag);
}

BOOL _Priv::UserVerify(LPCTSTR AppID, short UserNumber, long MenuID)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR VTS_I2 VTS_I4;
	InvokeHelper(0x6003000b, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		AppID, UserNumber, MenuID);
	return result;
}

short _Priv::FieldVerify(LPCTSTR AppID, short UserNumber, LPCTSTR TableName, LPCTSTR FieldName, BSTR* FieldCaption, BOOL Lang, LPCTSTR LinkTableName)
{
	short result;
	static BYTE parms[] =
		VTS_BSTR VTS_I2 VTS_BSTR VTS_BSTR VTS_PBSTR VTS_BOOL VTS_BSTR;
	InvokeHelper(0x6003000c, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
		AppID, UserNumber, TableName, FieldName, FieldCaption, Lang, LinkTableName);
	return result;
}

VARIANT _Priv::ButtonsVerify(LPCTSTR AppID, short UserNumber, LPCTSTR TableName, LPCTSTR LinkTableName)
{
	VARIANT result;
	static BYTE parms[] =
		VTS_BSTR VTS_I2 VTS_BSTR VTS_BSTR;
	InvokeHelper(0x6003000d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms,
		AppID, UserNumber, TableName, LinkTableName);
	return result;
}

CString _Priv::GetUserLoginName(long UserID)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6003000e, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		UserID);
	return result;
}

CString _Priv::GetUserFullName(long UserID)
{
	CString result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6003000f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		UserID);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// _SetUp properties

/////////////////////////////////////////////////////////////////////////////
// _SetUp operations

CString _SetUp::GetSystemDBName()
{
	CString result;
	InvokeHelper(0x60030000, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

short _SetUp::GetApplicationDBType()
{
	short result;
	InvokeHelper(0x60030001, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
	return result;
}

long _SetUp::ShowSetup(LPCTSTR dbName, LPCTSTR Login, LPCTSTR Password, BOOL ShowMessageFlag, BOOL Lang)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_BSTR VTS_BSTR VTS_BOOL VTS_BOOL;
	InvokeHelper(0x60030002, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		dbName, Login, Password, ShowMessageFlag, Lang);
	return result;
}

CString _SetUp::GetApplicationDataBaseName()
{
	CString result;
	InvokeHelper(0x60030006, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _SetUp::GetApplicationReports()
{
	CString result;
	InvokeHelper(0x60030007, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _SetUp::GetSystemDBLoginName()
{
	CString result;
	InvokeHelper(0x60030008, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _SetUp::GetApplicationDBLoginName()
{
	CString result;
	InvokeHelper(0x60030009, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _SetUp::GetApplicationDBPassword()
{
	CString result;
	InvokeHelper(0x6003000a, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _SetUp::GetSystemDBPassword()
{
	CString result;
	InvokeHelper(0x6003000b, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _SetUp::GetApplicationHelpPath()
{
	CString result;
	InvokeHelper(0x6003000c, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _SetUp::GetOraclePassword()
{
	CString result;
	InvokeHelper(0x6003000d, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL _SetUp::IsParametersOK()
{
	BOOL result;
	InvokeHelper(0x6003000e, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString _SetUp::GetDatabaseDateStyle()
{
	CString result;
	InvokeHelper(0x6003000f, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _SetUp::GetSQLServerUserID()
{
	CString result;
	InvokeHelper(0x60030010, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _SetUp::GetSQLServerCatalog()
{
	CString result;
	InvokeHelper(0x60030011, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _SetUp::GetSQLServerMachineName()
{
	CString result;
	InvokeHelper(0x60030012, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _SetUp::GetSQLServerPassword()
{
	CString result;
	InvokeHelper(0x60030013, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _SetUp::GetOracleUserID()
{
	CString result;
	InvokeHelper(0x60030014, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _SetUp::GetOracleDataSource()
{
	CString result;
	InvokeHelper(0x60030015, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString _SetUp::GetServerName()
{
	CString result;
	InvokeHelper(0x60030016, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

short _SetUp::GetProtocolType()
{
	short result;
	InvokeHelper(0x60030017, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
	return result;
}
