
// ADMNObj.h : Declaration of the CADMNObj

#ifndef __ADMNOBJ_H_
#define __ADMNOBJ_H_

#include "resource.h"       // main symbols
#include <atlwin.h>
#include "stdio.h"

/////////////////////////////////////////////////////////////////////////////
// CADMNObj
#include "CMNObjBase.h"
class CDongleListen;
class ATL_NO_VTABLE CADMNObj : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CADMNObj, &CLSID_ADMNObj>,
	public IDispatchImpl<IADMNObj, &IID_IADMNObj, &LIBID_ADMNLib>,
	CCMNObjBase
{
public:
	CADMNObj();
	~CADMNObj();
	void	UpdateFirstSysByAllowDuplicateItems(BOOL AllowDuplicateItems,BOOL AllowDuplicateMRItems);
	CString ReadLFAValidation(CString strApp,CString strTag,CString strLinkName,CString strField);
	void UpdateLFAValidation(_DB * pdb,CString strApp,CString strTag,CString strLinkName,CString strField,CString strValidation);
DECLARE_REGISTRY_RESOURCEID(IDR_ADMNOBJ)

BEGIN_COM_MAP(CADMNObj)
	COM_INTERFACE_ENTRY(IADMNObj)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()

// IADMNObj
public:
	CRect m_rcFormRect	;
	STDMETHOD(SetRegHandleDB)(LPDISPATCH lpRegHandleDB);
	STDMETHOD(DoFunction)(int nCurrentCard,BSTR bstrTableName,int nStatus,BOOL bModal,BSTR bstrWhereClause);
	STDMETHOD(ActivateForm)(BSTR bstrFormID,BOOL bByTag, int nSkipNo,BOOL bActivateLoadedScreen);
	STDMETHOD(GetConnectionString)(/*[out]*/ BSTR* bstrConnection);
	STDMETHOD(SetFastSearchCriteria)(BSTR bstrCriteria);
	STDMETHOD(SetModal)(BOOL bModalVal);
	STDMETHOD(CloseAll)();
	STDMETHOD(SetLanguage)(BOOL bArabic);
	STDMETHOD(GetLanguage)(BOOL *bArabic);
	STDMETHOD(Initialize)(int nAppCode, BSTR bstrProfile,long lUserID, BSTR bstrODBC, long lLanguage, BSTR bstrInitModule);
	STDMETHOD(SetParent)(long pParent);
	STDMETHOD(GetUserID)();
	STDMETHOD(SetCurrentMenuItemID)(UINT unMenuID);
	STDMETHOD(GetDBType)();
	STDMETHOD(SetFormRect)(int nLeft, int nTop, int nRight, int nBottom);
	STDMETHOD(ShowScreenFromAttachment)(BSTR bstrAttachmentFile);
	STDMETHOD(GetUserName)(BSTR* bstrName);

	STDMETHOD(SetSystemPath)();
	STDMETHOD(HandOverSubjectType)();
	STDMETHOD(OpenedHandOver)();
	STDMETHOD(ClosedHandOver)();
	STDMETHOD(ShowDocumentLibrary)();
	STDMETHOD(ShowDocumentTemplates)();
	STDMETHOD(GenerateTender)(BSTR bstrTemplate,BSTR bstrTenderNo,BSTR bstrOutputFileName);
	STDMETHOD(GenerateContract)(BSTR bstrTemplate,BSTR bstrContractNo,BSTR bstrOutputFileName);
	STDMETHOD(ShowTenderTree)(BSTR bstrTenderNo,BOOL bLocked);
	STDMETHOD(ShowContractTree)(BSTR bstrContractNo,BOOL bLocked);
	STDMETHOD(ShowReportsInfo)();


public:
	IRegHandlePtr GetDBRegHandle();
	
	CString ViewExcelEvaluationSheet(CString strTemplateFileName,CString strEnquiryCode,CString strCurrency);
	bool IsMenuEnabled(long lMenuID);
	void ShowHandOverLinkedDocument(CString strCriteria,CString strComesFrom,CString strScreenDefauls);
	void ShowLibrarySubs(CString strCriteria,CString strComesFrom,CString strScreenDefauls);

	int		ShowLoginScreen();
	BOOL	IsAdminUser(int nUserID);
	void	LoadSystemPolicy();
	void	ShowSummaryTransactions(CString &strWhereClause);
	void	AnalysisShowMonthlyClosing();
	void	FreeMRSVars();
	void	FireCloseAll();
	void	Remove(CCategory * pCategory);
	BOOL 	IsArabic();
	BOOL 	IsHijri(){return m_bHijri;};
	CString GetFastSearchCriteria()
	{
		return m_strFastSearchCriteria;
	};
	
	CString GetInitModule()
	{
		return m_strInitModule;
	};

	long GetAppCode()
	{
		return m_AppCode;
	};

	int DoFunction(int nCurrentCard,CString strTableName,int nStatus=NORMAL_MODE,BOOL bModal=FALSE,CString strCriteria = "",CString strComesFrom="",CString strScreenDefauls="",CString strReturnBrowseValue="");

	void TransactionPurchasingComparisonSheetQuoteAddExpense(CString strSQL);
	UINT DefineApplicationSetup();
	UINT DefineSetupScreen();
	UINT DefineUserScreen();
	UINT DefineMenuScreen(long lMenuHandle);
	UINT DefineUsersList();
	void DefineFieldsPriv();
	BOOL IsModalPolyDb();
	CString GetScreenDefauls();
	void SetHOLinkedDocScreenDefauls(CString strScreenDefauls);
	void SetLibrarySubsScreenDefauls(CString strScreenDefauls);
	void SetScreenDefauls(CString strScreenDefauls);
	BOOL ValidateDongle();
	static long DBInit(long lAppCode, CString strODBC, _DB	*pADMNPolyDb,CToolsListener* pToolsListener,BOOL bExtended=FALSE);
	long GetParent(){return m_lpParent;};
	BOOL GetRecodingStatus(){return m_bRecodingEnabled;}
	_bstr_t ShowNotepad (_bstr_t bstrValue,_bstr_t bstrEnCaption,enum TextStyle nStyle,int nType,BOOL bLocked,COLORREF bkColor);


	void SetModalPollyDB(BOOL bStatus){if(!m_bLockModalFlag)m_bModalPolyDb = bStatus;};
	CString GetDataPath(){return m_strDataPath;};
	CString GetSystemPath()	{return m_strSystemPath;};
	CString GetServerName()	{return m_strServerName;};
	CString GetODBC()	{return m_strODBC;};
	
	//static short GetUserID(){return m_User;};
	void CheckForUser(CString strUserFullName);
	int GetDisplayStatus(){	return m_nStatus;}
	CString GetReplicationLocationID();
	//CString ConvertToTafkeet(double dValue,CString strUnit,CString strSubUnit);
	static CString GetCurrentProfile(){	return m_strCurrentProfile;};

protected:
	CCategory *MakeCategory();
	void CreateConnectionString();
	BOOL PrepareBeforeOpenAttachmet(CString strScreenTag,CString strCriteria,CString strSubject);

protected:
	CString				m_strFastSearchCriteria;
	CString				m_strDataPath,
						m_strSystemPath,
						m_strServerName,
						m_strPaneText;
	CWinApp				*m_pADMNApp;
	CWnd				*m_pParentWnd;
	CString				m_strScreenDefauls, m_strHOLinkedDocScreenDefauls,m_strLibrarySubsScreenDefauls;

	BOOL				m_bModalPolyDb,
						m_bLockModalFlag,
						m_bArabic,
						m_bModalEnv;
	BOOL				m_bRecodingEnabled,
						m_bWaitingForExportedMenuID;
	CString				m_strODBC;
	CDongleListen		*m_DongleListen;
	int					m_nCodeID,
						m_nAppCode,
						m_nStatus;
	long				m_lpParent;

	_DB					*m_pADMNSYSPolyDb;
	CObList				*m_pCategoryList;
	static				CString m_strStaticDataPath;
	static				CString m_strStaticSystemPath;
	
	_FNotepadObjPtr		m_pNotepadeObj;

public:
	CConnection			m_Connection;
	long				m_AppCode;
	static int			m_nCurrentDBEngine;
	static BOOL			m_bHijri,
						m_bRejectQtyInMRS,
						m_bUseManulSerialInOrders,
						m_bGeneratePartNumFromQut;
	static CString		m_strConnection;
	static CString		m_strUserFullName;
	static CString		m_strLoginUserName;
	static CString		m_lEmployeeDept;
	static CString		m_strHelpFileName;
	static CString		m_strCurrentProfile;
	static long			m_lEmployeeBudget,
						m_lEmpSetting,
						m_User;
	CString 			m_strDept,
						m_strInitModule,
						m_strDB,
						m_strDBUser;
	
	CMapStringToString	m_MapMenuIDTOTags;
};

#endif
