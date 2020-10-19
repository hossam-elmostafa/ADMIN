 // ADMNObj.cpp : Implementation of CADMNObj
#include "stdafx.h"
#include "ADMN.h"
#include "ADMNObj.h"
#include "Category.h"
#include "ADMNapp.h"
#include "ToolsListener.h"
#include "HandOver.h"
#include "DocLib.h"

#define	SILENTPOLYDBRECORDSET				4

/////////////////////////////////////////////////////////////////////////////
// CADMNObj
UINT m_unCurMenuID;
int CADMNObj::m_nCurrentDBEngine=DB_NOTDEFINED;
BOOL CADMNObj::m_bHijri =FALSE;
BOOL CADMNObj::m_bRejectQtyInMRS=FALSE;
BOOL CADMNObj::m_bUseManulSerialInOrders = FALSE;
BOOL CADMNObj::m_bGeneratePartNumFromQut = FALSE;
BOOL gbApplyScreenSetting=TRUE;

CString CADMNObj::m_strConnection="";
CString CADMNObj::m_strStaticDataPath="";
CString CADMNObj::m_strStaticSystemPath="";
CString CADMNObj::m_strUserFullName="";
CString CADMNObj::m_strLoginUserName="";
CString CADMNObj::m_lEmployeeDept="";
CString CADMNObj::m_strHelpFileName="";
long CADMNObj::m_User = 0;
CString CADMNObj::m_strCurrentProfile = "";
CString strConnection="";
CFile sqlReportFile=NULL;
BOOL bFirstTime=false;
CString GlstrVersionNo = "1.0.0";
IFirstDesktopPtr	gpFirstDesktopObj;
IRegHandlePtr		gpRegHandle;
CADMNObj::CADMNObj()
{
	gpRegHandle = NULL;
	m_strScreenDefauls = "";
	m_strHOLinkedDocScreenDefauls="";
	m_strLibrarySubsScreenDefauls="";
	m_rcFormRect.SetRect(0,0,0,0);

	m_MapMenuIDTOTags.RemoveAll();
	m_bModalPolyDb			=FALSE;
	m_bLockModalFlag		=FALSE;
	m_bArabic				=FALSE;
	m_bModalEnv				=FALSE;
	extern CADMNApp theApp;
	theApp.SetADMNObj(this);
	m_nStatus				=NORMAL_MODE;
	m_bRecodingEnabled		=FALSE;
	m_pADMNSYSPolyDb			=new _DB;
	m_pCategoryList			=new CObList;
	m_lpParent = 0;
	m_nCodeID=-1;

	HRESULT hr =m_pNotepadeObj.CreateInstance(__uuidof(FNotepadObj));
	if(hr!=0)
	{
		MessageBox(NULL,"Cannot initialize Notpad object","Prompt",0);
		return;
	}
}

CADMNObj::~CADMNObj()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	try
	{
		CloseAll();
		if (m_pADMNSYSPolyDb)
			delete m_pADMNSYSPolyDb;
		if (m_pCategoryList)
			delete m_pCategoryList;
	}
	catch(...)
	{

	}

	try
	{
		if(m_pNotepadeObj)
		{
			m_pNotepadeObj.Release();
			m_pNotepadeObj=NULL;
		}
	}
	catch(...)
	{
		AfxMessageBox("~CADMNObj");
	}
}

void CADMNObj::Remove(CCategory * pCategory)
{
	try
	{
		POSITION position=m_pCategoryList->Find((CObject*)pCategory);
		if(position)
			m_pCategoryList->RemoveAt( position );
	}
	catch(...)
	{
		return;
	}

}

CCategory *CADMNObj::MakeCategory()
{
	CWaitCursor wc;
	CCategory *pCategory=new CCategory(m_strDataPath,m_pParentWnd,this,m_pADMNSYSPolyDb);
	m_pCategoryList->AddTail(pCategory);
	pCategory->SetFormRect(m_rcFormRect);
	pCategory->SetMenuID(m_unCurMenuID);
	return pCategory;
}

STDMETHODIMP CADMNObj::CloseAll()
{
	while(!m_pCategoryList->IsEmpty())
	{
		CCategory * pCategory=(CCategory *)m_pCategoryList->RemoveHead();
		try
		{
			if(AfxIsValidAddress(pCategory,sizeof(CCategory)))//this line added because of the rubbish data of calling the screen from module
			{
				pCategory->GetMyCCategory()->OnScreenExit();
				delete pCategory;
			}
		}
		catch(...)
		{
		}
	}
	return S_OK;
}

STDMETHODIMP CADMNObj::SetParent(long pParent)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_pParentWnd=(CWnd*)pParent;
	m_lpParent= pParent;

	return S_OK;
}

STDMETHODIMP CADMNObj::Initialize(int nAppCode, BSTR bstrProfile,long lUserID, BSTR bstrODBC, long lLanguage, BSTR bstrInitModule)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	
	m_AppCode = nAppCode;
	m_Connection.SetApplicationCode(m_AppCode);
	CString strProfile = CString (bstrProfile);
	m_strInitModule = CString (bstrInitModule);
	m_strODBC = CString (bstrODBC);
	m_bArabic = lLanguage;
	m_User = lUserID;
	if (strProfile != "")
	{
		m_strCurrentProfile = strProfile;
	}
	HRESULT hr = S_OK;
	try
	{
		SetSystemPath();
		CreateConnectionString();
		long lRetVal=0;
		lRetVal = m_pADMNSYSPolyDb->DBInit(DB_ACCESS,m_strSystemPath,m_strSystemPath,m_AppCode,-1,m_strHelpFileName,m_strODBC,m_strCurrentProfile);
		m_strLoginUserName = m_Connection.m_pPrivConnection->GetUserLoginName(m_User);
		m_strUserFullName  = m_Connection.m_pPrivConnection->GetUserFullName(m_User);
	}
	catch(...)
	{
		hr = S_FALSE;
	}

	return hr;
}

STDMETHODIMP CADMNObj::SetSystemPath()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_Connection.m_pSetupConnection->SetApplicationInfo(m_AppCode,m_strCurrentProfile);
	m_strSystemPath = m_Connection.m_pSetupConnection->GetSystemDBName();
	m_strServerName = m_Connection.m_pSetupConnection->GetSQLServerMachineName();

	m_strStaticSystemPath = m_strSystemPath;
	return S_OK;
}

STDMETHODIMP CADMNObj::SetLanguage(BOOL bArabic)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	m_bArabic=bArabic;
	return S_OK;
}

STDMETHODIMP CADMNObj::GetLanguage(BOOL *bArabic)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	*bArabic=m_bArabic;
	return S_OK;
}

BOOL CADMNObj::IsArabic()
{
	return m_bArabic;
}

int CADMNObj::DoFunction(int nCurrentCard,CString strTableName,int nStatus,BOOL bModal,CString strCriteria,CString strComesFrom,CString strScreenDefauls,CString strReturnBrowseValue)
{
	int nRetVal=0;

	m_strScreenDefauls = strScreenDefauls;
	if (strScreenDefauls != "")
	{
		m_strHOLinkedDocScreenDefauls = strScreenDefauls;
		m_strLibrarySubsScreenDefauls = strScreenDefauls;
	}

	CWaitCursor wc;
	ATOM ThisScreenAtom=FindAtom(strTableName);
	if(ThisScreenAtom)
		DeleteAtom(ThisScreenAtom);
	
	strTableName.MakeUpper();
	m_nStatus=nStatus;
	
	if (nCurrentCard == -1) // means Related record selected event
		SetFastSearchCriteria(strCriteria.AllocSysString());
	
	if(m_nStatus==NORMAL_MODE || bModal)
	{
		m_bModalPolyDb=TRUE;
		m_bLockModalFlag=TRUE;
	}

	if (strTableName=="CMN_HOSUBJTYPE")
		HandOverSubjectType();

	else if (strTableName=="HO_O")
		OpenedHandOver();

	else if (strTableName=="HO_C")
		ClosedHandOver();

	else if (strTableName=="CMN_HOLINKDOC")
		ShowHandOverLinkedDocument(strCriteria,strComesFrom,m_strHOLinkedDocScreenDefauls);

	else if (strTableName=="VWCPMS_TOCTMPLT")
		ShowDocumentTemplates();

	else if (strTableName=="VWCPMS_TNDRLIB")
		ShowDocumentLibrary();

	else if (strTableName=="VWCPMS_TNDRLIBSBCNTNT")
		ShowLibrarySubs(strCriteria,strComesFrom,m_strLibrarySubsScreenDefauls);

	m_strScreenDefauls = "";
	m_bModalPolyDb=FALSE;
	m_bLockModalFlag=FALSE;
	m_nStatus=NORMAL_MODE;
	if(ThisScreenAtom)
	{
		AddAtom(strTableName);
	}
	wc.Restore();
	wc.~CWaitCursor();

	return nRetVal;
}

STDMETHODIMP CADMNObj::DoFunction(int nCurrentCard,BSTR bstrTableName,int nStatus,BOOL bModal,BSTR bstrWhereClause)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	USES_CONVERSION;
	CString strTableName=OLE2T(bstrTableName);
	CString strWhereClause=OLE2T(bstrWhereClause);
	
	DoFunction(nCurrentCard,strTableName,nStatus,bModal,strWhereClause);

	return S_OK;
}

IRegHandlePtr CADMNObj::GetDBRegHandle()
{
	if (gpRegHandle)
		return gpRegHandle;

	if (m_strConnection == "")
		AfxMessageBox("RegHandle needs a connection string");

	gpRegHandle.CreateInstance(__uuidof(RegHandle));//create instance from registry handle
	gpRegHandle->SetSettingMode(WM_DB); 
	gpRegHandle->SetProfileName("ADMN");
	gpRegHandle->SetConnectionString(m_strConnection.AllocSysString());

	return gpRegHandle;
}
 
CString CADMNObj::GetScreenDefauls()
{
	return m_strScreenDefauls;
}

void CADMNObj::SetLibrarySubsScreenDefauls(CString strScreenDefauls)
{
	m_strLibrarySubsScreenDefauls = strScreenDefauls;
}

void CADMNObj::SetHOLinkedDocScreenDefauls(CString strScreenDefauls)
{
	m_strHOLinkedDocScreenDefauls = strScreenDefauls;
}

void CADMNObj::SetScreenDefauls(CString strScreenDefauls)
{
	m_strScreenDefauls = strScreenDefauls;
}

BOOL CADMNObj::IsModalPolyDb()
{
	return m_bModalPolyDb;
};

STDMETHODIMP CADMNObj::SetModal(BOOL bModalVal)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	m_bModalEnv = bModalVal;
	return S_OK;
}

long CADMNObj::DBInit(long lAppCode, CString strODBC,_DB *pADMNPolyDb,CToolsListener* pToolsListener,BOOL bExtended)
{
	CWaitCursor wc;
	long lRetVal=0;
	pADMNPolyDb->SetCalendarType(m_bHijri);
	if(!bExtended)
		lRetVal = pADMNPolyDb->DBInit(m_nCurrentDBEngine,strConnection, m_strStaticSystemPath,lAppCode,m_User,m_strHelpFileName,strODBC,m_strCurrentProfile);
	else
		lRetVal = pADMNPolyDb->DBInitEx(strConnection);


	if(lRetVal<= 0)
	{
		MessageBox(NULL,"Cannot initialize connecteion\n\rPlease review your connection setting","Prompt",0);
		return -1;
	}
	try
	{
		if(pToolsListener != NULL)
			pToolsListener->SetToolsParam(m_User,m_nCurrentDBEngine,strConnection.GetBuffer(0),m_strStaticSystemPath,GetCurrentProfile());
	}
	catch (_com_error& e) 
	{
		_bstr_t bstrSource(e.Source());
		_bstr_t bstrDescription(e.Description());
		CString strErrior;
		strErrior.Format("Code = %08lx\n Code meaning = %s\nSource = %s\nDescription = %s\n", e.Error(),e.ErrorMessage(),(LPCTSTR) bstrSource,(LPCTSTR) bstrDescription);
	}
	return lRetVal;
}

void CADMNObj::FireCloseAll()
{
	CloseAll();
}
void CADMNObj::CreateConnectionString()
{
	int nDatabaseType = m_Connection.m_pSetupConnection->GetApplicationDBType();
	m_bHijri = m_Connection.m_pSetupConnection->GetHijriState();
	m_nCurrentDBEngine= nDatabaseType ;
	CString strOldConnection = strConnection;
	switch(m_nCurrentDBEngine)
	{
	case DB_ORACLE:							
		{
			CString strServiceName,strUserName,strPassWord,strProvider;
			strServiceName = m_Connection.m_pSetupConnection->GetOracleDataSource();
			strUserName = m_Connection.m_pSetupConnection->GetOracleUserID();
			strPassWord = m_Connection.m_pSetupConnection->GetOraclePassword();
			short sVer =m_Connection.m_pSetupConnection->GetOracleVersion();
			if(sVer==7)
				strConnection.Format("Provider=MSDAORA.1;Password=%s;User ID=%s;Data Source=%s;Persist Security Info=True",strPassWord,strUserName,strServiceName);
			else
				strConnection.Format("Provider=OraOLEDB.Oracle.1;Password=%s;User ID=%s;Data Source=%s;Persist Security Info=True",strPassWord,strUserName,strServiceName);

			m_strPaneText.Format("Oracle : %s/%s",strUserName,strServiceName);
			m_strDB = strUserName;
		}
		break;
	case DB_SQLSERVER:
		{
			CString strDBUserID,strCatalogName,strPassWord,strServerName;
			strDBUserID=m_Connection.m_pSetupConnection->GetSQLServerUserID();
			strPassWord=m_Connection.m_pSetupConnection->GetSQLServerPassword();
			strServerName=m_Connection.m_pSetupConnection->GetSQLServerMachineName();
			strCatalogName=m_Connection.m_pSetupConnection->GetSQLServerCatalog();
			strConnection.Format("Provider=SQLOLEDB.1;Persist Security Info=True;User ID=%s;Password=%s;Initial Catalog=%s;Data Source=%s;Workstation ID=%s",strDBUserID,strPassWord,strCatalogName,strServerName,m_strUserFullName);
			m_strPaneText.Format("SQL Server : %s/%s/%s",strDBUserID,strServerName,strCatalogName);
			m_strDB = strCatalogName;
			m_strDBUser = strDBUserID;
		}
		break;
	case DB_ACCESS:
		{			
			m_strStaticDataPath = m_Connection.m_pSetupConnection->GetApplicationDataBaseName();
			//strConnection.Format("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=%s;Jet OLEDB:Database Password=First2000",m_strStaticDataPath);
			strConnection = m_strStaticDataPath;
			m_strPaneText.Format("Access");
		}
		break;
	}	
	
	if(m_strConnection == strConnection && m_strConnection !="")
		return;
	m_strConnection= strConnection;
	m_pADMNSYSPolyDb->CloseConnection();
}

STDMETHODIMP CADMNObj::GetConnectionString(BSTR *bstrConnection)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	*bstrConnection = m_strConnection.AllocSysString();
	return S_OK;
}

STDMETHODIMP CADMNObj::GetUserName(BSTR *bstrName)
{
	CString strData;
	strData.Format("%s >>> %s",m_strLoginUserName,m_strUserFullName);
	*bstrName = strData.AllocSysString();
	return S_OK;
}

_bstr_t CADMNObj::ShowNotepad (_bstr_t bstrValue,_bstr_t bstrEnCaption,enum TextStyle nStyle,int nType,BOOL bLocked,COLORREF bkColor)
{
	if(m_pNotepadeObj ==NULL) 
	{
		HRESULT hr =m_pNotepadeObj.CreateInstance(__uuidof(FNotepadObj));
		if(hr)
			return "";
	}
	try
	{
		return m_pNotepadeObj->ShowNotepad (bstrValue,bstrEnCaption,nStyle,nType,bLocked,RGB(255,255,255));
	}
	catch(_com_error &e)
	{
		_bstr_t str_t = e.Description();
		return "";
	}
}

BOOL CADMNObj::IsAdminUser(int nUserID)
{
	return m_Connection.m_pSecurityConnection->IsAdminUser(nUserID);
}

STDMETHODIMP CADMNObj::ShowScreenFromAttachment(BSTR bstrAttachmentFile)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	return S_OK;
}


BOOL CADMNObj::PrepareBeforeOpenAttachmet(CString strScreenTag,CString strCriteria,CString strSubject)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	return TRUE;
}

STDMETHODIMP CADMNObj::SetFormRect(int nLeft, int nTop, int nRight, int nBottom)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_rcFormRect.CopyRect(CRect(nLeft, nTop, nRight, nBottom));

	if(m_pCategoryList)
	{
		for (int nCounter=0;nCounter < m_pCategoryList->GetCount();nCounter ++)
		{
			
			try
			{
				POSITION pos = m_pCategoryList->FindIndex(nCounter);
				CCategory * pCategory=(CCategory *)m_pCategoryList->GetNext(pos);
				pCategory->SetFormRect(m_rcFormRect);
				pCategory->GetMyCCategory()->MovePolydbForm();
			}
			catch(...)
			{
			}
			
		}
	}

	return S_OK;
}

STDMETHODIMP CADMNObj::ActivateForm(BSTR bstrFormID,BOOL bByTag, int nSkipNo,BOOL bActivateLoadedScreen)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	CString strFormID(bstrFormID);

	CCategory* pListCategory;
	int nItemFound = 0;
	if(m_pCategoryList)
	{
		int lCount=m_pCategoryList->GetCount();
		for (int nCounter=0;nCounter < m_pCategoryList->GetCount();nCounter ++)
		{
			POSITION pos = m_pCategoryList->FindIndex(nCounter);
			CCategory * pCategory=(CCategory *)m_pCategoryList->GetNext(pos);

			if (bByTag)
			{
				if (pCategory->GetMyCCategory()->GetFormTag() == strFormID)
				{
					// Get List Category
					if (nItemFound == 0)
						pListCategory = pCategory;

					if (nItemFound == nSkipNo)
					{
						if (bActivateLoadedScreen)
						{
							if (nSkipNo == 1)
							{
								// Get Current KeyValue Criteria from List Screen
								CString strCriteria = pListCategory->GetMyCCategory()->GetSelectedRecordCriteria();
								// Move to the correct record in 1:Many screen
								pCategory->GetMyCCategory()->FindRecord(strCriteria);
							}
								//Get FastSearch member here and move to this record
							pCategory->GetMyCCategory()->BringWindowToTop();
						}
						return true;
					}
					nItemFound++;	
				}
			}
			else // Called from EXE 
			{
				if (pCategory->GetMyCCategory()->GetScreenCaption() == strFormID)
				{
					pCategory->GetMyCCategory()->BringWindowToTop();
					return true;
				}
			}
		}
	}

	return false;
}

STDMETHODIMP CADMNObj::SetFastSearchCriteria(BSTR bstrCriteria)
{
	m_strFastSearchCriteria = bstrCriteria;
	return S_OK;
}

STDMETHODIMP CADMNObj::GetUserID()
{
	return m_User;
}

bool CADMNObj::IsMenuEnabled(long lMenuID)
{
	CString str;
	str.Format("%ld",m_AppCode);
	return m_Connection.m_pPrivConnection->MenuVerify(str, m_User,lMenuID);
}

HRESULT CADMNObj::SetCurrentMenuItemID(UINT unMenuID)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	m_unCurMenuID=unMenuID;

	return S_OK;
}

STDMETHODIMP CADMNObj::GetDBType()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	short sRetVal= m_Connection.m_pSetupConnection->GetApplicationDBType();
	return sRetVal;
}

STDMETHODIMP CADMNObj::SetRegHandleDB(LPDISPATCH lpRegHandleDB)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())

	gpRegHandle = (IRegHandlePtr)lpRegHandleDB;
	return S_OK;
}

STDMETHODIMP CADMNObj::HandOverSubjectType()
{
	CCategory *pCategory=MakeCategory();
	if(pCategory==NULL)
		return S_FALSE;
	
	CHandOver *pHandOver=new CHandOver(pCategory);
	pHandOver->SubjectType();
	return S_OK;
}

STDMETHODIMP CADMNObj::OpenedHandOver()
{
	CCategory *pCategory=MakeCategory();
	if(pCategory==NULL)
		return S_FALSE;
	
	CHandOver *pHandOver=new CHandOver(pCategory);
	pHandOver->OpenedHandOver();
	return S_OK;
}

STDMETHODIMP CADMNObj::ClosedHandOver()
{
	CCategory *pCategory=MakeCategory();
	if(pCategory==NULL)
		return S_FALSE;
	
	CHandOver *pHandOver=new CHandOver(pCategory);
	pHandOver->ClosedHandOver();
	return S_OK;
}

void CADMNObj::ShowHandOverLinkedDocument(CString strCriteria,CString strComesFrom,CString strScreenDefauls)
{
	CCategory *pCategory=MakeCategory();
	if(pCategory==NULL)
		return ;
	
	CHandOver *pHandOver=new CHandOver(pCategory);
	pHandOver->ShowHandOverLinkedDocument(strCriteria,strComesFrom,strScreenDefauls);
	return;
}

STDMETHODIMP CADMNObj::ShowDocumentLibrary()
{
	CCategory *pCategory=MakeCategory();
	if(pCategory==NULL)
		return S_FALSE;
	
	CDocLib *pDocLib=new CDocLib(pCategory);
	pDocLib->ShowDocumentLibrary();
	return S_OK;
}

STDMETHODIMP CADMNObj::ShowDocumentTemplates()
{
	CCategory *pCategory=MakeCategory();
	if(pCategory==NULL)
		return S_FALSE;
	
	CDocLib *pDocLib=new CDocLib(pCategory);
	pDocLib->ShowDocumentTemplates();
	return S_OK;
}

void CADMNObj::ShowLibrarySubs(CString strCriteria,CString strComesFrom,CString strScreenDefauls)
{
	CCategory *pCategory=MakeCategory();
	if(pCategory==NULL)
		return ;
	
	CDocLib *pHandOver=new CDocLib(pCategory);
	pHandOver->ShowLibrarySubs(strCriteria,strComesFrom,strScreenDefauls);
	return;
}

STDMETHODIMP CADMNObj::GenerateTender(BSTR bstrTemplate,BSTR bstrTenderNo,BSTR bstrOutputFileName)
{
	CCategory *pCategory=MakeCategory();
	if(pCategory==NULL)
		return S_FALSE;
	
	CDocLib *pDocLib=new CDocLib(pCategory);
	pDocLib->GenerateTender(bstrTemplate,bstrTenderNo,bstrOutputFileName);
	return S_OK;
}

STDMETHODIMP CADMNObj::GenerateContract(BSTR bstrTemplate,BSTR bstrContractNo,BSTR bstrOutputFileName)
{
	CCategory *pCategory=MakeCategory();
	if(pCategory==NULL)
		return S_FALSE;
	
	CDocLib *pDocLib=new CDocLib(pCategory);
	pDocLib->GenerateContract(bstrTemplate,bstrContractNo,bstrOutputFileName);
	return S_OK;
}

STDMETHODIMP CADMNObj::ShowTenderTree(BSTR bstrTenderNo,BOOL bLocked)
{
	CCategory *pCategory=MakeCategory();
	if(pCategory==NULL)
		return S_FALSE;
	
	CDocLib *pDocLib=new CDocLib(pCategory);
	pDocLib->ShowTenderTree(bstrTenderNo,bLocked);
	return S_OK;
}

STDMETHODIMP CADMNObj::ShowContractTree(BSTR bstrContractNo,BOOL bLocked)
{
	CCategory *pCategory=MakeCategory();
	if(pCategory==NULL)
		return S_FALSE;
	
	CDocLib *pDocLib=new CDocLib(pCategory);
	pDocLib->ShowContractTree(bstrContractNo,bLocked);
	return S_OK;
}
