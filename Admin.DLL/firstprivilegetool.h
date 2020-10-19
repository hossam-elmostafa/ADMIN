// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// _Security wrapper class

class _Security : public COleDispatchDriver
{
public:
	_Security();
	~_Security();

	_Security(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Security(const _Security& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	short ShowLogScreen(LPCTSTR AppCode, BOOL ShowMessageFlag, BOOL LanguageFlag);
	void ShowUsersScreen(LPCTSTR ApplicationCode, BOOL ShowMessageFlag, BOOL LanguageFlag);
	void WriteLogHistory(short ApplicationCode, long UserID, LPCTSTR ScreenTag, const VARIANT& RecordID, LPCTSTR ActionName);
	long ShowLogHistory(short ApplicationCode, BOOL Lang);
	void TerminateUser();
	long ShowUsersLogHistory(short ApplicationCode, BOOL Lang);
};
/////////////////////////////////////////////////////////////////////////////
// _Priv wrapper class

class _Priv : public COleDispatchDriver
{
public:
	_Priv();
	~_Priv();

	_Priv(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Priv(const _Priv& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void MenuBuild(LPCTSTR AppCode, long MenuHandle);
	void ShowMenusItem(LPCTSTR MyAppCode, BOOL ShowMessageFlag, BOOL LanguageFlag);
	void ShowMenusDetails(LPCTSTR MyAppCode, BOOL ShowMessageFlag, BOOL LanguageFlag);
	BOOL UserVerify(LPCTSTR AppID, short UserNumber, long MenuID);
	short FieldVerify(LPCTSTR AppID, short UserNumber, LPCTSTR TableName, LPCTSTR FieldName, BSTR* FieldCaption, BOOL Lang, LPCTSTR LinkTableName);
	VARIANT ButtonsVerify(LPCTSTR AppID, short UserNumber, LPCTSTR TableName, LPCTSTR LinkTableName);
	CString GetUserLoginName(long UserID);
	CString GetUserFullName(long UserID);
};
/////////////////////////////////////////////////////////////////////////////
// _SetUp wrapper class

class _SetUp : public COleDispatchDriver
{
public:
	_SetUp() ;
	~_SetUp();

	_SetUp(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_SetUp(const _SetUp& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetSystemDBName();
	short GetApplicationDBType();
	long ShowSetup(LPCTSTR dbName, LPCTSTR Login, LPCTSTR Password, BOOL ShowMessageFlag, BOOL Lang);
	CString GetApplicationDataBaseName();
	CString GetApplicationReports();
	CString GetSystemDBLoginName();
	CString GetApplicationDBLoginName();
	CString GetApplicationDBPassword();
	CString GetSystemDBPassword();
	CString GetApplicationHelpPath();
	CString GetOraclePassword();
	BOOL IsParametersOK();
	CString GetDatabaseDateStyle();
	CString GetSQLServerUserID();
	CString GetSQLServerCatalog();
	CString GetSQLServerMachineName();
	CString GetSQLServerPassword();
	CString GetOracleUserID();
	CString GetOracleDataSource();
	CString GetServerName();
	short GetProtocolType();
};
