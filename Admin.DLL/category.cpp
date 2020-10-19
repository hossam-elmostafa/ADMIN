#include "stdafx.h"
#include "ADMN.h"
#include "ADMNobj.h"
#include "ADMNapp.h"
#include "IO.h"

#ifdef	_DEBUG
#define	new	DEBUG_NEW
#endif

#define	MAIN_NEW_NONEMPTY_RECORD_NAVIGATE	-1
#define	MAIN_NEW_RECORD						0
#define	GRID_FREE_NAVIGATE					0
#define	GRID_NEW_EMPTY_RECORD_NAVIGATE		1
#define	GRID_NEW_NONEMPTY_RECORD_NAVIGATE	2
#define	SILENTPOLYDBRECORDSET				4
#define	SILENTPOLYDBRECORDSETF				5
#define CM_SETPANTEXT						WM_USER+1000
#define	LIST_FORM		3
#define	UNLOAD			11

BOOL bReturnFromEvent = FALSE;


BEGIN_EVENTSINK_MAP(CCategory, CCmdTarget)
    //{{AFX_EVENTSINK_MAP(CAboutDlg)
	ON_EVENT(CCategory, -1, 0x1  , OnEventMFieldChanged, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I4 VTS_I2 VTS_I2)
	ON_EVENT(CCategory, -1, 0x2  , OnEventSFieldChanged, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_I2)
	ON_EVENT(CCategory, -1, 0x3  , SGFieldChanged,VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4)
	ON_EVENT(CCategory, -1, 0x4  , OnEventBrowsingAddNewItem, VTS_BSTR VTS_BSTR VTS_BSTR VTS_DISPATCH)
	ON_EVENT(CCategory, -1, 0x5  , OnBrowsingSelectedItem, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_DISPATCH)
	ON_EVENT(CCategory, -1, 0x6  , OnBrowsingEditItemSelected, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_DISPATCH)
	ON_EVENT(CCategory, -1, 0x7  , OnBrowsingChangePosition, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(CCategory, -1, 0x8  , OnTreeNodeSelected, VTS_BSTR VTS_BSTR)
	ON_EVENT(CCategory, -1, 0xa  , OnCustomButtonClicked, VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_VARIANT VTS_BSTR VTS_BSTR VTS_I4 VTS_DISPATCH)
	ON_EVENT(CCategory, -1, 0xb  , OnEventToolBarButtonClicked,VTS_BSTR VTS_BSTR VTS_I2 VTS_VARIANT VTS_I2 VTS_BSTR)
	ON_EVENT(CCategory, -1, 0xc  , OnEventToolBarButtonClickedDone,VTS_BSTR VTS_BSTR VTS_I2 VTS_VARIANT VTS_I2 VTS_BSTR)
	ON_EVENT(CCategory, -1, 0xd  , OnEventMainSubReposition,VTS_BSTR VTS_I4 VTS_I2 VTS_BSTR)
	ON_EVENT(CCategory, -1, 0xe  , OnGridRowReposition,VTS_BSTR VTS_I2 VTS_I4 VTS_BSTR VTS_BSTR)
	ON_EVENT(CCategory, -1, 0xf  , OnBrowsableCustomButtonClicked,VTS_BSTR VTS_BSTR VTS_VARIANT VTS_I2 VTS_BSTR VTS_DISPATCH)
	ON_EVENT(CCategory, -1, 0x10  , OnBeforeBrowseButtonClick,VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(CCategory, -1, 0x11  ,OnBrowsingToolBarButtonClicked,VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_I4 VTS_VARIANT VTS_DISPATCH VTS_BOOL)
	ON_EVENT(CCategory, -1, 1	  ,RangeNotify,VTS_BSTR VTS_BSTR VTS_BSTR)
	ON_EVENT(CCategory, -1, 0x16 ,BrowseDuplicatedValue,VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_PBOOL)
	ON_EVENT(CCategory, -1, 0x13 ,OnScreenReady,VTS_BSTR)	
	ON_EVENT(CCategory, -1, 0x19 ,SendReport,VTS_PBSTR VTS_PBSTR VTS_PBSTR VTS_PBSTR)
	ON_EVENT(CCategory, -1, 0x1a		 /* Event24 */,OnReletedRecordSelected ,VTS_BSTR VTS_BSTR VTS_BSTR)		

	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

INTERFACE_IMPL(CCategory,EventSink)
CCategory::CCategory(CString DbPath, CWnd* pParentWnd,CADMNObj *pADMNobj,_DB *pADMNSYSPolyDb)
{
	m_unCurMenuID = 0;
	m_rcFormRect.SetRect(0,0,0,0);
	m_pCommonCategory=NULL;
	m_pParentWnd=pParentWnd;
	m_pADMNPolyDb = new _DB;
	m_pADMNSYSPolyDb = pADMNSYSPolyDb;
	m_pObject=m_pADMNPolyDb->m_lpDispatch;
	m_strDbPath=DbPath;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	m_pADMNobj=pADMNobj;
	m_User= m_pADMNobj->m_User;
	m_strDBName = m_pADMNobj->m_strDB;
	m_strDBUser = m_pADMNobj->m_strDBUser;
	m_nEngine = m_pADMNobj->m_nCurrentDBEngine;
	m_strConnection = m_pADMNobj->m_strConnection;
	m_strSystemPath=pADMNobj->GetSystemPath();
	m_strServerName=pADMNobj->GetServerName();
	m_strODBC = pADMNobj->GetODBC();

	EstablishConnectionWithEventSrc();
	m_pToolsListener = new CToolsListener();

	m_lAppCode=m_pADMNobj->GetAppCode();
	long RetVal=0;
	try
	{
		RetVal = m_pADMNobj->DBInit(m_lAppCode,m_strODBC,m_pADMNPolyDb,m_pToolsListener,FALSE);
	}

	catch(CException *e)
	{
		e->ReportError();
		delete m_pADMNPolyDb;
		m_pADMNPolyDb = NULL;
		return;
	}	
}

CCategory::CCategory(CCategory*pCategory)
{
	m_pCommonCategory=NULL;
	m_pParentWnd=pCategory->m_pParentWnd;
	m_pADMNPolyDb = new _DB;
	m_pObject=m_pADMNPolyDb->m_lpDispatch;
	m_strDbPath=pCategory->m_strDbPath;	
	m_pADMNobj=pCategory->m_pADMNobj;
	m_strSystemPath=pCategory->m_strSystemPath;
	m_lAppCode = m_pADMNobj->GetAppCode();
	EstablishConnectionWithEventSrc();
	long RetVal =0;
	try
	{
		m_pToolsListener = new CToolsListener();
		RetVal = m_pADMNobj->DBInit(m_lAppCode,m_strODBC,m_pADMNPolyDb,m_pToolsListener);
	}
	catch (...)
	{
		delete m_pADMNPolyDb;
		m_pADMNPolyDb = NULL;
		return;
	}
}

CCategory::~CCategory()
{
	try
	{
		m_DaoRecSet.Close();
		EndConnectionWithEventSrc();
		if(m_pADMNPolyDb)
		{
			m_pADMNPolyDb->FormDoAction(-1,UNLOAD);
			delete m_pADMNPolyDb;
			m_pADMNPolyDb =NULL;
		}
		if(m_pCommonCategory)
		{
			ATOM ThisScreenAtom=FindAtom(m_pCommonCategory->GetFormTag());
			if(ThisScreenAtom)
				ATOM atomRetVal=DeleteAtom(ThisScreenAtom);
			delete m_pCommonCategory;
		}
		if(m_pToolsListener)
		{
			delete m_pToolsListener;
			m_pToolsListener = NULL;
		}
		m_pCommonCategory=NULL;
		m_pADMNobj->Remove(this);
	}
	catch(...)
	{
		return;
	}
}

CString CCategory::GetFirstSysDBPath()
{
	return m_strSystemPath;
}

_DB *CCategory::GetADMNPolyDB()
{
	return m_pADMNPolyDb;
}

_DB *CCategory::GetADMNSYSPolyDB()
{
	return m_pADMNSYSPolyDb;
}

long CCategory::GetParentHWnd()
{
	if(m_pParentWnd == NULL)
		return 0;


	try
	{
		HWND hWnd=m_pParentWnd->GetSafeHwnd();
		return (long)(DWORD)hWnd;
	}
	catch(...)
	{
		return m_pADMNobj->GetParent();
	}
}

void CCategory::SetPaneText(int nPos,char* pText,BOOL bState)
{
	UINT message=CM_SETPANTEXT;
	LPARAM lParam = (LPARAM)pText;
	m_pParentWnd->SendMessage( message, 0, lParam );
}


void CCategory::OnEventSFieldChanged(LPCTSTR Form_Tag, LPCTSTR Field_Name, LPCTSTR old_value, LPCTSTR New_Value, LPCTSTR full_record, long Record_Position, short grid_edit_mode)
{	
	m_pCommonCategory->WaitCursor();
	if(bReturnFromEvent)
		return;

	CString strFormTag=m_pCommonCategory->GetFormTag();
		if(strFormTag=="")
		strFormTag=Form_Tag;
	CString strTag=strFormTag;
	strTag.MakeUpper();
	CString strFieldName=Field_Name;
	strFieldName.MakeUpper();
	CString strNewVal=New_Value;
	strNewVal.MakeUpper();
	if(m_pCommonCategory)
		m_pCommonCategory->EventSFieldChanged(strTag,Field_Name,old_value,New_Value,full_record,Record_Position,grid_edit_mode);

	// Manage Synchronous Changes 
	if(!m_pCommonCategory->ValidateOnRecordStatus())
		return;
	//-------------------------------------------------
	if(grid_edit_mode ==GRID_NEW_NONEMPTY_RECORD_NAVIGATE)
		return;
	
	AdjustRelatedTables(strTag,Field_Name,old_value, New_Value,grid_edit_mode);	
}

void CCategory::AdjustRelatedTables(CString strTag,CString strField_Name,CString strOld_value, CString strNew_Value, short grid_edit_mode)
{
	if(strOld_value=="")
		return;
	if(AskForRelatedTables(strTag,strField_Name))
	{
	
		if(grid_edit_mode != GRID_NEW_NONEMPTY_RECORD_NAVIGATE)
		{
			int nRet=0;
			CString FeedBackSql;
			CPolyDbRecordset DaoRecset(PDBRS_LOAD_FROM_SYS_DB);
			
			CString FSAString = "SELECT * FROM vwFSA WHERE BROWSINGTABLE =";
			CString LFAString = "SELECT * FROM vwLFA WHERE BROWSINGTABLE=";
			CString FullSqlString;
			FullSqlString.Format("%s '%s' AND DATAFIELDNAME <> BROWSINGRETFIELD AND APPLICATIONCODE = %ld AND DATAFIELDNAME <> BROWSINGRETFIELD",FSAString,strTag,m_lAppCode);
			// strTag is made equal to the table name
			DaoRecset.Open(AFX_DAO_USE_DEFAULT_TYPE,FullSqlString);
			BOOL bCheckForRule=TRUE;
			BOOL bRecodeTable;
			if(!DaoRecset.IsEOF())
			{
				DaoRecset.MoveFirst();
				while(!DaoRecset.IsEOF())
				{
					CString TableName;
					CString strUpdateStatement;
					CString FieldName;
					DaoRecset.GetFieldValue("TableName",TableName);
					bRecodeTable = GetTableRecodingStatus(TableName);
					if(bRecodeTable)
					{
						DaoRecset.GetFieldValue("DataFieldName",FieldName);
						if(bCheckForRule)
						{						
							CString strValidationRule;
							strValidationRule.Format("SELECT %s FROM %s WHERE %s ='%s'",FieldName,TableName ,FieldName,strOld_value);
							CPolyDbRecordset DaoRecsetValidation;
							DaoRecsetValidation.Open(AFX_DAO_USE_DEFAULT_TYPE,strValidationRule);
							if(!DaoRecsetValidation.IsEOF())
							{
								bCheckForRule=FALSE;							
								if(m_pADMNobj->GetRecodingStatus())
									if(!IsArabic())
										nRet = MessageBox(NULL,"This field is related with other tables\nAre you sure you want to recoded it ?","Prompt",MB_YESNO | MB_ICONEXCLAMATION |MB_TASKMODAL);
									else
										nRet = MessageBox(NULL,"åÐÇ ÇáÍÞá ãÑÊÈØ ÈÈíÇäÇÊ ÃÎÑí .åá ÊÑÛÈ Ýí ÊÚÏíá ÔÇãá ááÞíãÉ¿","ÊäÈíå",MB_YESNO | MB_ICONEXCLAMATION |MB_TASKMODAL);

								else
								{
									if(!IsArabic())
										MessageBox(NULL,"This field is related with other tables\nYou can't recode it","Prompt",MB_OK | MB_ICONHAND |MB_TASKMODAL);
									else
										MessageBox(NULL,"åÐÇ ÇáÍÞá ãÑÊÈØ ÈÈíÇäÇÊ ÃÎÑí .åá ÊÑÛÈ Ýí ÊÚÏíá ÔÇãá ááÞíãÉ¿","ÊäÈíå",MB_YESNO |MB_RIGHT| MB_ICONEXCLAMATION |MB_TASKMODAL);
									nRet=IDNO;
								}
								if(nRet != IDYES)
								{
									_DB *m_PollyDb = GetADMNPolyDB();
									m_PollyDb->FormSetField(strTag,strField_Name,strOld_value,-1);
									return;
								}
								
								strUpdateStatement.Format("UpdateRelated '%s','%s','%s','%s'",TableName ,FieldName,strNew_Value,strOld_value);
								try
								{
									m_pCommonCategory->ExecuteSQL(strUpdateStatement);
								}
								catch(...)
								{
								}
								DaoRecsetValidation.Close();
								
							}
							else
								DaoRecsetValidation.Close();						
						}
					
					else
					{
						strUpdateStatement.Format("UpdateRelated '%s','%s','%s','%s'",TableName ,FieldName,strNew_Value,strOld_value);
						try
						{
							m_pCommonCategory->ExecuteSQL(strUpdateStatement);
						}
						catch(...)
						{
						}
					}
					}
				DaoRecset.MoveNext();
				}
			}

			FullSqlString.Format("%s '%s' AND APPLICATIONCODE = %ld AND DATAFIELDNAME <> BROWSINGRETFIELD",LFAString,strTag,m_lAppCode);
			DaoRecset.Open(AFX_DAO_USE_DEFAULT_TYPE,FullSqlString);
			if(!DaoRecset.IsEOF())
			{
				DaoRecset.MoveFirst();
				while(!DaoRecset.IsEOF())
				{
					CString TableName;
					CString strUpdateStatement;
					CString FieldName;
					DaoRecset.GetFieldValue("LINKNAME",TableName);

					DaoRecset.GetFieldValue("DATAFIELDNAME",FieldName);
					if(bCheckForRule)
					{						
						CString strValidationRule;
						strValidationRule.Format("SELECT %s FROM %s WHERE %s ='%s'",FieldName,TableName ,FieldName,strOld_value);
						CPolyDbRecordset DaoRecsetValidation;
						DaoRecsetValidation.Open(AFX_DAO_USE_DEFAULT_TYPE,strValidationRule);
						if(!DaoRecsetValidation.IsEOF())
						{
							bCheckForRule=FALSE;
							DaoRecsetValidation.Close();
							if(m_pADMNobj->GetRecodingStatus())
								if(!IsArabic())
									nRet = MessageBox(NULL,"This field is related with other tables\nAre you sure you want to recoded it?","Prompt",MB_YESNO | MB_ICONEXCLAMATION |MB_TASKMODAL);
								else
									nRet = MessageBox(NULL,"åÐÇ ÇáÍÞá ãÑÊÈØ ÈÈíÇäÇÊ ÃÎÑí .åá ÊÑÛÈ Ýí ÊÚÏíá ÔÇãá ááÞíãÉ¿","ÊäÈíå",MB_YESNO | MB_ICONEXCLAMATION |MB_TASKMODAL);							
							else
							{
								if(!IsArabic())
									MessageBox(NULL,"This field is related with other tables\nAre you sure you want to recoded it?","Prompt",MB_YESNO | MB_ICONEXCLAMATION |MB_TASKMODAL);
								else
									MessageBox(NULL,"åÐÇ ÇáÍÞá ãÑÊÈØ ÈÈíÇäÇÊ ÃÎÑí .åá ÊÑÛÈ Ýí ÊÚÏíá ÔÇãá ááÞíãÉ¿","ÊäÈíå",MB_YESNO | MB_ICONEXCLAMATION |MB_TASKMODAL);
								nRet=IDNO;
							}
							if(nRet != IDYES)
							{
								_DB *PollyDb = GetADMNPolyDB();
								PollyDb->FormSetField(strTag,strField_Name,strOld_value,-1);
								DaoRecset.Close();
								return;
							}


							strUpdateStatement.Format("UpdateRelated '%s','%s','%s','%s'",TableName ,FieldName,strNew_Value,strOld_value);
							try
							{
								m_pCommonCategory->ExecuteSQL(strUpdateStatement);
							}
							catch(...)
							{
							}
						}
						else
							DaoRecsetValidation.Close();						
					}
					else
					{
						strUpdateStatement.Format("UpdateRelated '%s','%s','%s','%s'",TableName ,FieldName,strNew_Value,strOld_value);
						try
						{
							m_pCommonCategory->ExecuteSQL(strUpdateStatement);
						}
						catch(...)
						{
						}
					}
					DaoRecset.MoveNext();
				}
			}								
			DaoRecset.Close();
		}
	}

}

void CCategory::OnEventMFieldChanged(LPCTSTR Form_Tag, LPCTSTR Field_Name, LPCTSTR old_value, LPCTSTR New_Value, LPCTSTR full_record, long Main_Position, long Details_Position, short grid_edit_mode,int EditMode_Area)
{
	m_pCommonCategory->WaitCursor();
	if(bReturnFromEvent)
		return;
	CString strFormTag=m_pCommonCategory->GetFormTag();
	if(strFormTag=="")
		strFormTag=Form_Tag;
	if(m_pCommonCategory)
		m_pCommonCategory->SubFieldChanged(Form_Tag, Field_Name, old_value, New_Value, full_record, Main_Position, Details_Position, grid_edit_mode);

	// Manage Synchronous Changes 
	if (Main_Position != MAIN_NEW_NONEMPTY_RECORD_NAVIGATE) // execlude AddNew
		if(!m_pCommonCategory->ValidateOnRecordStatus())
			return;
	//-------------------------------------------------
	if(Main_Position == MAIN_NEW_NONEMPTY_RECORD_NAVIGATE || Main_Position == MAIN_NEW_RECORD)
		return;

	AdjustRelatedTables(strFormTag,Field_Name,old_value, New_Value,grid_edit_mode);
}

void CCategory::OnEventBrowsingAddNewItem(LPCTSTR Form_Tag, LPCTSTR Table_Name, LPCTSTR Criteria,LPDISPATCH ListRecordset)
{
	m_pCommonCategory->WaitCursor();
	if(bReturnFromEvent)
		return;

	m_pCommonCategory->FillListRecordSet(ListRecordset);
	if(CCommonCategory::m_nShowPos==-1)
	{
		try
		{
			m_pADMNPolyDb->FormDoAction(LIST_FORM,UNLOAD);
		}
		catch(...)
		{
		}
		return;
	}

	// TO INVOKE ADD NEW IN POLYDB - AAZMY
	CCommonCategory::m_nShowPos = -1;

	if(m_pCommonCategory && m_pCommonCategory->m_bHasListWindow)
	{
		CString strFormTag=m_pCommonCategory->GetFormTag();
		if(strFormTag=="")
			strFormTag=Form_Tag;
		m_pADMNobj->DoFunction(m_pCommonCategory->m_nCurrentCard,strFormTag,ADD_NEW_MODE,m_pCommonCategory->IsModalScreen(),"",m_pCommonCategory->m_strComesFrom);
	}
	else
		m_pADMNobj->DoFunction(m_pCommonCategory->m_nCurrentCard,Table_Name,ADD_NEW_MODE,(m_pCommonCategory==NULL)?TRUE:m_pCommonCategory->IsModalScreen());
}

void CCategory::SGFieldChanged(LPCTSTR Form_Tag, LPCTSTR Panel_Tag, LPCTSTR Field_Name, LPCTSTR Old_Value, LPCTSTR New_Value, LPCTSTR Full_Record, long Record_Position)
{
	m_pCommonCategory->WaitCursor();
	if(bReturnFromEvent)
		return;
	OnEventSFieldChanged(Form_Tag,Field_Name,Old_Value,New_Value,Full_Record,Record_Position,-1);
}

void CCategory::OnEventToolBarButtonClicked(LPCTSTR Button_Name, LPCTSTR Form_Tag, short Seleted_Tab, const VARIANT& Full_Record, short Toolbar_ID,LPCTSTR subForm_Tag)
{	
	if(bReturnFromEvent)
		return;
	CString strButton_Name = Button_Name;
	CString strFormTag=m_pCommonCategory->GetFormTag();
	if(strFormTag=="")
		strFormTag=Form_Tag;
	CString strForm_Tag = strFormTag;
	strButton_Name.MakeUpper();
	if(strButton_Name=="NEXT" || strButton_Name=="PREVIOUS")
		return;

	if(strButton_Name == "DELETE" || strButton_Name == "SAVE")
	{
		// Manage Synchronous Changes 
		if(!m_pCommonCategory->ValidateOnRecordStatus())
			return;
		//-------------------------------------------------
	}
	if(strButton_Name=="DELETE")
	{
		CString strConfirmDeleteStr;
		if(!m_pADMNobj->IsArabic())
			strConfirmDeleteStr.LoadString(ID_DELETE_CONFIRM_MSG);
		else 
			strConfirmDeleteStr.LoadString(ID_DELETE_CONFIRM_MSGARABIC);
	}

	SAFEARRAY *pSAFEARRAY=V_ARRAY(&Full_Record);
	VARIANT* pVar=(VARIANT*)(pSAFEARRAY->pvData);

	int nLoops=0;
	nLoops = pSAFEARRAY->rgsabound->cElements;
	if(nLoops == 1)
		nLoops++;	
	m_pCommonCategory->m_bCancelOperation=TRUE;
	m_pCommonCategory->m_nNumberOfUnDeletedRecords = 0;
	if(!m_pCommonCategory)
		m_pCommonCategory->m_bCancelOperation=FALSE;
	int nLoop =0;	
	for(nLoop =0;nLoop < nLoops -1;nLoop++)
	{
		BSTR str=V_BSTR(&pVar[nLoop]);
		CString strFullRecord(str);
		if(m_pCommonCategory)
			m_pCommonCategory->ConfirmToolBarButtonClicked(strForm_Tag ,Seleted_Tab,strButton_Name ,strFullRecord,nLoop,Toolbar_ID);
	}
	if(m_pCommonCategory->m_bCancelOperation)
	{
		short nShort=0;
		m_pADMNPolyDb->HandleActionEx(-1,TRUE,nShort);
	}
	if(m_pCommonCategory->m_nNumberOfUnDeletedRecords > 0)
	{
		CString strMessge;
		if(!IsArabic())
		{
			strMessge.Format("Undeleted %d Record(s) related with other tables",m_pCommonCategory->m_nNumberOfUnDeletedRecords);
			MessageBox(NULL,strMessge,"Prompt",MB_OK | MB_ICONEXCLAMATION |MB_TASKMODAL);
		}
		else
		{
			strMessge.Format("ÚÏÏ ÇáÓÌáÇÊ ÇáÛíÑ ãÍÐæÝÉ %d",m_pCommonCategory->m_nNumberOfUnDeletedRecords);
			MessageBox(NULL,strMessge,"ÊäÈíå",MB_OK| MB_RIGHT | MB_ICONEXCLAMATION |MB_TASKMODAL);
		}

	}
  //	MOVED TO OnEventToolBarButtonClickedDone BY AAZMY, AALI
//	if(strButton_Name==EXITNAME)
//		m_pCommonCategory->ActivateListWindow();
}

void CCategory::OnEventToolBarButtonClickedDone(LPCTSTR Button_Name, LPCTSTR Form_Tag, short Seleted_Tab, const VARIANT& Full_Record, short Toolbar_ID,LPCTSTR subForm_Tag)
{
	m_pCommonCategory->WaitCursor();
	if(bReturnFromEvent)
		return;
	CString strButton_Name = Button_Name;
	CString strFormTag=m_pCommonCategory->GetFormTag();
	if(strFormTag=="")
		strFormTag=Form_Tag;
	CString strForm_Tag = strFormTag;
	strButton_Name.MakeUpper();
	if(strButton_Name=="EXIT")
	{
		if(m_pCommonCategory)
			m_pCommonCategory->ConfirmToolBarButtonClickedDone(strForm_Tag ,Seleted_Tab,strButton_Name ,"",0,Toolbar_ID);
		if(m_pCommonCategory->m_bSubWindowScreen == TRUE)// One to one state or one to many without list
		{
			ATOM ThisScreenAtom=FindAtom(strForm_Tag);
			if(ThisScreenAtom)
			{
				ATOM atomRetVal=DeleteAtom(ThisScreenAtom);
				m_pCommonCategory->m_bSubWindowScreen = FALSE;
			}
			
			m_pCommonCategory->OnScreenExit();
			//	NEXT LINE ONLY MOVED HERE BY AAZMY, AALI
			m_pCommonCategory->ActivateListWindow();
			delete this;
		}
		else
		{
			m_pCommonCategory->m_bMainSubBrowsing=FALSE;
			m_pCommonCategory->m_bEditMode=TRUE;
		}
		return;
	}

	if(strButton_Name=="NEXT" || strButton_Name=="PREVIOUS" || strButton_Name == "REFRESH")
	{
		m_pCommonCategory->SetStartedTXNStatus();
	}
	
	if(strButton_Name!="NEXT" && strButton_Name!="PREVIOUS")
	{
		m_pCommonCategory->ConfirmToolBarButtonClickedDone(strForm_Tag ,Seleted_Tab,strButton_Name ,"",0,Toolbar_ID);
		return;
	}
		

	SAFEARRAY *pSAFEARRAY=V_ARRAY(&Full_Record);
	VARIANT* pVar=(VARIANT*)(pSAFEARRAY->pvData);

	int nLoops=0;
	nLoops = pSAFEARRAY->rgsabound->cElements;

	if(nLoops == 1)
		nLoops++;	
	if(Toolbar_ID == 0)
	{			
		int nLoop =0;
		for(nLoop =0;nLoop < nLoops -1;nLoop++)
		{
			BSTR str=V_BSTR(&pVar[nLoop]);
			CString strFullRecord(str);
			if(m_pCommonCategory)
				m_pCommonCategory->ConfirmToolBarButtonClicked(strForm_Tag ,Seleted_Tab,strButton_Name ,strFullRecord,nLoop,Toolbar_ID);
		}
	}	

}

void CCategory::OnEventMainSubReposition(LPCTSTR Form_Tag, long Main_Position, short Seleted_Tab,LPCTSTR subForm_Tag)
{
	m_pCommonCategory->WaitCursor();
	if(bReturnFromEvent)
		return;
	if(Main_Position==-1)
		return;

	CString strFormTag=m_pCommonCategory->GetFormTag();
	if(strFormTag=="")
		strFormTag=Form_Tag;
	strFormTag.MakeUpper();
	
	CString strSubFormTag = subForm_Tag;
	if(m_pCommonCategory)
		m_pCommonCategory->MainSubReposition(strFormTag, Main_Position ,Seleted_Tab,strSubFormTag);

}
	
	
void CCategory::OnBrowsingSelectedItem(LPCTSTR Form_Tag, LPCTSTR Full_Recoed, LPCTSTR Table, LPCTSTR Return_Value ,LPCTSTR pszBrowsingField , LPCTSTR Criteria,long AbsolutePosition,LPDISPATCH ListRecordset)
{
	m_pCommonCategory->WaitCursor();
	CString strForm_Tag = Form_Tag;
	CString strBrowseField = pszBrowsingField;
	if(bReturnFromEvent)
		return;

	if(strForm_Tag.Left(3) == "ALL")
	{
		CString strCriteria;
		strCriteria.Format("WHERE (%s='%s')",strBrowseField ,Return_Value);
		SetFastSearchCriteria(strCriteria);
	}
	else
		m_pCommonCategory->FillListRecordSet(ListRecordset);

	CString strFormTag=m_pCommonCategory->GetFormTag();
	if(strFormTag=="")
		strFormTag=Form_Tag;
	if(m_pCommonCategory)
	{
		if(m_pCommonCategory->m_bHasListWindow)// && *Return_Value==0)
		{
			m_pCommonCategory->SetCurrentPos(AbsolutePosition);
			m_pCommonCategory->m_bMainSubBrowsing=TRUE;
			DoFunction(m_pCommonCategory->m_nCurrentCard,strFormTag,EDIT_MODE,false,"",m_pCommonCategory->m_strComesFrom,"",CString(Return_Value));
			return;
		}
		m_pCommonCategory->UpdateAfterBrowse(strFormTag, Full_Recoed, Table, Return_Value,pszBrowsingField,Criteria);
		if(m_pCommonCategory->IsModalScreen())
		m_pADMNPolyDb->FormDoAction(LIST_FORM,UNLOAD);
	}
}

void CCategory::OnBrowsingEditItemSelected(LPCTSTR Form_Tag, LPCTSTR Full_Record, LPCTSTR Table , LPCTSTR Criteria,long AbsolutePosition,LPDISPATCH ListRecordset)
{
	if(bReturnFromEvent)
		return;

	CString strNewBuild;
	CString strTable = Table;
	strTable.MakeUpper();
	strNewBuild.Format("SELECT * FROM %s ",Table);
	m_pCommonCategory->WaitCursor();
	m_pCommonCategory->SetCurrentPos(AbsolutePosition);
	m_pCommonCategory->FillListRecordSet(ListRecordset);
	
	m_pADMNobj->DoFunction(m_pCommonCategory->m_nCurrentCard,Table,EDIT_MODE,TRUE);
}

void CCategory::OnBrowsingChangePosition(LPCTSTR Form_Tag, LPCTSTR Full_Recoed, LPCTSTR Table, LPCTSTR Return_Value, LPCTSTR Criteria)
{
	m_pCommonCategory->WaitCursor();
	if(bReturnFromEvent)
		return;
}

void CCategory::OnTreeNodeSelected(LPCTSTR Table_Name, LPCTSTR Field_Value)
{
	m_pCommonCategory->WaitCursor();
}

void CCategory::OnBrowsableCustomButtonClicked(LPCTSTR Form_Tag, LPCTSTR Table, const VARIANT& Record, short CustomButtonID , LPCTSTR Criteria,LPDISPATCH ListRecordset)
{
	m_pCommonCategory->WaitCursor();
	if(bReturnFromEvent)
		return;
	CString strFormTag=m_pCommonCategory->GetFormTag();
	if(strFormTag=="")
		strFormTag=Form_Tag;
	if(m_pCommonCategory)
		m_pCommonCategory->OnBrowsableCustomButtonClicked(strFormTag, Record, CustomButtonID);
}

void CCategory::OnBeforeBrowseButtonClick(LPCTSTR Form_Tag,LPCTSTR Link_Tag, LPCTSTR FieldName, LPCTSTR CellContent, LPCTSTR BrowsingTable, LPCTSTR BrowsingSQL, LPCTSTR BrowsingField, LPCTSTR BrowsingRetField, LPCTSTR Full_Record)
{
	m_pCommonCategory->WaitCursor();
	if(bReturnFromEvent)
		return;
	CMenu* pMenu = m_pParentWnd->GetMenu();
	CString strID;
	CString strForm_Tag=Form_Tag;
	CString strFieldName =FieldName;
	CString strBrowsingTable= BrowsingTable;
	CString strReturnValue=CellContent;
	CString strBrowsingSQL=BrowsingSQL;
	CString strLink_Tag = Link_Tag;
	m_pADMNobj->m_MapMenuIDTOTags.Lookup(strBrowsingTable,strID);
	UINT ui = pMenu->GetMenuState(atol(strID.GetBuffer(NULL)),MF_BYCOMMAND);
//	CString strName;
//	pMenu->GetMenuString(atol(strID.GetBuffer(NULL)),strName,MF_BYCOMMAND);
	if(ui & MF_DISABLED != 0)
	{
		m_pCommonCategory->FormEnableButton(BROWSABLE,BASETOOLBAR,NEW_BUTTONNAME,FALSE,FALSE);
		m_pCommonCategory->FormEnableButton(BROWSABLE,BASETOOLBAR,DELETE_BUTTONNAME,FALSE,FALSE);
		m_pCommonCategory->FormEnableButton(BROWSABLE,BASETOOLBAR,EDIT_BUTTONNAME,FALSE,FALSE);
	}
}

void CCategory::OnBrowsingToolBarButtonClicked(LPCTSTR List_Tag, LPCTSTR Button_Key, LPCTSTR Table_Name, LPCTSTR Criteria, long AbsolutePosition, const VARIANT& Record, LPDISPATCH ListRecordset , BOOL bCustomButton)
{
	m_pCommonCategory->WaitCursor();
	if(bReturnFromEvent)
		return;
	if(m_pCommonCategory==NULL)
		return;
	CString strFormTag=m_pCommonCategory->GetFormTag();
	CString strListFormTag=List_Tag;

	CString strTable_Name = Table_Name;
	strTable_Name.MakeUpper();
	if(strFormTag=="")
		strFormTag=List_Tag;
	CString strButton_Key=Button_Key;
	strButton_Key.MakeUpper();
	if(strButton_Key=="DELETE")
	{
		if(m_pCommonCategory)
		{
			if(Record.vt == VT_EMPTY)
				return;
			SAFEARRAY *pSAFEARRAY=V_ARRAY(&Record);
			VARIANT* pVar=(VARIANT*)(pSAFEARRAY->pvData);
			int nLoops=0;
			nLoops = pSAFEARRAY->rgsabound->cElements;
			if(nLoops == 1)
				nLoops++;	
			int nLoop =0;
			for(nLoop =0;nLoop < nLoops -1;nLoop++)
			{
				BSTR str;
				str=V_BSTR(&pVar[nLoop]);
				CString strFullRecord(str);
				m_pCommonCategory->ConfirmToolBarButtonClicked(strTable_Name,0,strButton_Key,strFullRecord,nLoop,0);
			}
			if(m_pCommonCategory->m_nNumberOfUnDeletedRecords > 0)
			{
				CString strMessge;
				if(!IsArabic())
				{
					strMessge.Format("Undeleted %d Record(s) related with other tables",m_pCommonCategory->m_nNumberOfUnDeletedRecords);
					MessageBox(NULL,strMessge,"Prompt",MB_OK | MB_ICONEXCLAMATION |MB_TASKMODAL);
				}
				else
				{
					strMessge.Format("ÚÏÏ ÇáÓÌáÇÊ ÇáÛíÑ ãÍÐæÝÉ %d",m_pCommonCategory->m_nNumberOfUnDeletedRecords);
					MessageBox(NULL,strMessge,"ÊäÈíå",MB_OK| MB_RIGHT | MB_ICONEXCLAMATION |MB_TASKMODAL);
				}
				m_pCommonCategory->m_nNumberOfUnDeletedRecords = 0;

			}

		
		}
	}
	else if(strButton_Key=="EXIT")
	{
		if(m_pCommonCategory)
		{
			ATOM ThisScreenAtom=FindAtom(strListFormTag);
			if(ThisScreenAtom)
				ATOM atomRetVal=DeleteAtom(ThisScreenAtom);

			m_pCommonCategory->OnScreenExit();
			if(!m_pCommonCategory->IsModalScreen())
				delete this;
			//Delete the current instance of category if parentmanage has finished		
		}
	}

	else if(strButton_Key=="EDIT")
	{
		OnBrowsingEditItemSelected(	List_Tag, "", Table_Name, Criteria,AbsolutePosition,ListRecordset);
	}

	else
	{
		CString strRecordKeys="";
		CString strItem="";
		SAFEARRAY *pSAFEARRAY=V_ARRAY(&Record);
		VARIANT* pVar=(VARIANT*)(pSAFEARRAY->pvData);

		int nLoops=0;
		nLoops = pSAFEARRAY->rgsabound->cElements;

		if(nLoops == 1)
			nLoops++;	
		int nLoop =0;

		long lAffectedRec=0;
		bool bAns = IDYES;
		if(m_pCommonCategory)
			bAns = m_pCommonCategory->BeforeButtonClicked(strButton_Key,List_Tag);

		if (bAns)
		{
			for(nLoop =0;nLoop < nLoops -1;nLoop++)
			{
				BSTR str=V_BSTR(&pVar[nLoop]);
				CString strFullRecord(str);
				if (OnCustomButtonClicked(List_Tag, strButton_Key, "", strFullRecord,COleVariant(""), Table_Name, Criteria, AbsolutePosition, ListRecordset))
					lAffectedRec++;
			}
		}
		if(m_pCommonCategory && lAffectedRec != 0)
			m_pCommonCategory->AfterButtonClicked(strButton_Key,List_Tag,lAffectedRec);

	}
}

void CCategory::RangeNotify(LPCTSTR Form_Tag, LPCTSTR Mask1_Text, LPCTSTR Mask2_Text)
{
	m_pCommonCategory->WaitCursor();
	if(bReturnFromEvent)
		return;
}
void CCategory::BrowseDuplicatedValue(LPCTSTR strFormTag, LPCTSTR strFieldName, LPCTSTR strBrowsingTable, LPCTSTR strBrowsingRetField, LPCTSTR strBrowsingValue, BOOL* bShowList)
{
	m_pCommonCategory->WaitCursor();
	CString strTag = strFormTag;
}
void CCategory::OnScreenReady(LPCTSTR FormTag)
{
	m_pCommonCategory->WaitCursor();
	m_pCommonCategory->OnScreenReady(FormTag);
	m_pCommonCategory->SetStartedTXNStatus();
}

void CCategory::SendReport(BSTR* strTo, BSTR* strCc, BSTR* strSubject, BSTR* strBody)
{
	m_pCommonCategory->OnSendReport(strTo, strCc, strSubject, strBody);
}

void CCategory::AddNewBar(LPDISPATCH Bar, BOOL bActionCompleted, long UserID)
{

}
void CCategory::DeleteBar(LPDISPATCH Bar, BOOL bActionCompleted, long UserID)
{

}
void CCategory::ChangeBar(LPDISPATCH OldBar, LPDISPATCH NewBar, BOOL bActionCompleted, long UserID)
{

}

void CCategory::UnloadPlan(BOOL bActionCompleted)
{

}

void CCategory::PlanChange(short nRows, LPCTSTR StartDate, LPCTSTR EndDate, long PlanStyle, BOOL bActionCompleted, long UserID)
{

}

void CCategory::NodeSelected(const VARIANT& TableName, LPCTSTR ReturnValue, long UserID)
{

}

void CCategory::RangeEnterd(LPCTSTR Form_Tag, LPCTSTR Mask1, LPCTSTR Mask2)
{

}

BOOL CCategory::AskForRelatedTables(LPCTSTR TableName, LPCTSTR Field_name)
{
	BOOL bRetVal;
	CString strField_name = Field_name;
	if(strField_name =="")
		Field_name = GetTableKey(TableName);
	CString FeedBackSql;
	CPolyDbRecordset DaoRecset(PDBRS_LOAD_FROM_SYS_DB);
	CString FSAString = "SELECT * FROM vwFSA WHERE BROWSINGTABLE =";
	CString LFAString = "SELECT * FROM vwLFA WHERE BROWSINGTABLE=";
	CString FullSqlString;
	
	FullSqlString.Format("%s '%s' AND BROWSINGRETFIELD ='%s' AND APPLICATIONCODE =%ld AND DATAFIELDNAME <> BROWSINGRETFIELD",FSAString,TableName,Field_name,m_lAppCode);
	DaoRecset.Open(AFX_DAO_USE_DEFAULT_TYPE,FullSqlString);
	if(DaoRecset.IsEOF())
	{
		FullSqlString.Format("%s '%s' AND BROWSINGRETFIELD='%s' AND APPLICATIONCODE =%ld AND DATAFIELDNAME <> BROWSINGRETFIELD",LFAString,TableName,Field_name,m_lAppCode);
		DaoRecset.Open(AFX_DAO_USE_DEFAULT_TYPE,FullSqlString);
		if(DaoRecset.IsEOF())
			bRetVal=FALSE;
		else
			bRetVal=TRUE;			
	}
	else
		bRetVal=TRUE;
	DaoRecset.Close();
	return bRetVal;
}


CString CCategory::GetDbPath()
{
	return m_strDbPath;
}

CString CCategory::GetScreenDefauls()
{
	return m_pADMNobj->GetScreenDefauls();
}

BOOL CCategory::IsModalPolyDb()
{
	return m_pADMNobj->IsModalPolyDb();
}

void CCategory::SetModalPollyDB(BOOL bStatus)
{
	m_pADMNobj->SetModalPollyDB(bStatus);
}

long CCategory::OnCustomButtonClicked(LPCTSTR Form_Tag, LPCTSTR Field_Name, LPCTSTR Field_Caption, LPCTSTR Master_Full_Recoed,const VARIANT& Details_Full_Recoed, LPCTSTR Table_Name, LPCTSTR Criteria, long AbsolutePosition, LPDISPATCH ListRecordset)
{
	m_pCommonCategory->WaitCursor();
	if(bReturnFromEvent)
		return 0;

	LPCTSTR FieldName =Field_Name;
	CString strForm_Tag =Form_Tag;
	CString strCaption =FieldName;
	strCaption.MakeUpper();
	CString strMessage;
	long nRetVal = 0;
	
	if(strCaption != "DELETED" && strCaption != "REFRESH" && strCaption != "SELECT")
	{
		
		// Manage Synchronous Changes 
		if(!m_pCommonCategory->ValidateOnRecordStatus())
			return 0;
		//-------------------------------------------------
	}

	if(Details_Full_Recoed.vt!=VT_EMPTY)
	{
		SAFEARRAY *pSAFEARRAY=V_ARRAY(&Details_Full_Recoed);
		VARIANT* pVar=(VARIANT*)(pSAFEARRAY->pvData);

		int nLoops=0;
		nLoops = pSAFEARRAY->rgsabound->cElements;
		if(nLoops == 1)
			nLoops++;	
		m_pCommonCategory->m_bCancelOperation=TRUE;
		m_pCommonCategory->m_nNumberOfUnDeletedRecords = 0;
		if(!m_pCommonCategory)
			m_pCommonCategory->m_bCancelOperation=FALSE;
		int nLoop =0;

		if (nLoops < 0 && m_pCommonCategory)
		{
			m_pCommonCategory->WaitCursor();
			nRetVal = m_pCommonCategory->ButtonClicked(FieldName , Form_Tag, Master_Full_Recoed,CString(""),Field_Caption);
			m_pCommonCategory->AfterButtonClicked(FieldName,Form_Tag,nRetVal);
		}
		else
		{
			for(nLoop =0;nLoop < nLoops -1;nLoop++)
			{
				BSTR str=V_BSTR(&pVar[nLoop]);
				CString strSubFullRecord(str);
				if(m_pCommonCategory)
				{
					m_pCommonCategory->WaitCursor();
					nRetVal = m_pCommonCategory->ButtonClicked(FieldName , Form_Tag, Master_Full_Recoed,strSubFullRecord,Field_Caption);
					m_pCommonCategory->AfterButtonClicked(FieldName,Form_Tag,nRetVal);
				}
			}
		}
	}
	else
	{
		if(m_pCommonCategory)
		{
			m_pCommonCategory->WaitCursor();
			nRetVal = m_pCommonCategory->ButtonClicked(FieldName , Form_Tag, Master_Full_Recoed,CString(""),Field_Caption);
			m_pCommonCategory->AfterButtonClicked(FieldName,Form_Tag,nRetVal);
		}
	}


	return nRetVal;
}

CString	CCategory::Find(CString strAllData,CString strField)
{
	strAllData.MakeUpper();
	strField.MakeUpper();
	strField+="|";
	int nPos=strAllData.Find(strField);
	if(nPos<0)
		return "";

	CString strTemp = strAllData.Mid(nPos+strField.GetLength());
	nPos=strTemp.Find("|");
	if(nPos<0)
		return strTemp;

	return strTemp.Left(nPos);

}

void CCategory::OnGridRowReposition(LPCTSTR Form_Tag, short Selected_Tab, long AbsolutePosition, LPCTSTR Full_Record,LPCTSTR subForm_Tag)
{	
	m_pCommonCategory->WaitCursor();
	if(bReturnFromEvent)
		return;
	CString strFormTag=m_pCommonCategory->GetFormTag();
	if(strFormTag=="")
		strFormTag=Form_Tag;
	
	if(m_pCommonCategory)
	{
		m_pCommonCategory->GridRowReposition(strFormTag, Selected_Tab, AbsolutePosition, Full_Record,subForm_Tag);
	}
	
	
}

int CCategory::DoFunction(int nCurrentCard,CString strFunction,int nStatus,BOOL bModal,CString strCriteria,CString strComesFrom,CString strScreenDefaults,CString strReturnBrowseValue)
{
	return m_pADMNobj->DoFunction(nCurrentCard,strFunction,nStatus,bModal,strCriteria,strComesFrom,strScreenDefaults,strReturnBrowseValue);
}

BOOL CCategory::IsArabic()
{
	return m_pADMNobj->IsArabic();
}

BOOL CCategory::IsHijri()
{
	return m_pADMNobj->IsHijri();
}
CWnd* CCategory::GetParentWnd()
{
	return m_pParentWnd;
}
long CCategory::GetParentWndAsLong()
{
	return (long)m_pParentWnd->GetParent();//m_pADMNobj->GetParent();
}


int CCategory::GetDisplayStatus()
{
	return m_pADMNobj->GetDisplayStatus();
}

long CCategory::ExecuteSQL(CString &strSqlStatement,UINT unConnectionDB,BOOL bIgnoreCommit)
{
	m_pCommonCategory->WaitCursor();
	long lRetFieldsCount=0;
	try
	{
		lRetFieldsCount = m_pADMNPolyDb->DBExecSql(strSqlStatement,unConnectionDB,FALSE);
	}
	catch(...)
	{
		lRetFieldsCount = 0;
	}
	return lRetFieldsCount;
}

BOOL CCategory::GetTableRecodingStatus(CString &strTableName)
{
	CString strSQL;
	BOOL bRetVal;
	CPolyDbRecordset DaoRecset(PDBRS_LOAD_FROM_SYS_DB);
	strSQL.Format("SELECT TRUETABLENAME FROM vwTablesInfo WHERE TABLENAME = '%s' AND APPLICATIONCODE IN (%d,%ld) AND TABLENAME = TRUETABLENAME \
 UNION SELECT DISTINCT LINKNAME FROM vwLSA WHERE (LinkOtherTable <> '' OR LinkOtherTable IS NOT NULL) AND LINKNAME = LinkOtherTable AND LINKNAME = '%s' AND ApplicationCode IN(%d,%ld)",strTableName,APP_CODE,m_lAppCode,strTableName,APP_CODE,m_lAppCode);
	long lRetVal = DaoRecset.Open(AFX_DAO_USE_DEFAULT_TYPE,strSQL);
	DaoRecset.Close();
	if(lRetVal <= 0)
		bRetVal = FALSE;
	else
		bRetVal = TRUE;
	return bRetVal;
}

//////////////// CPolyDb Recordset

INTERFACE_IMPL(CPolyDbRecordset,EventSink)
CPolyDbRecordset::CPolyDbRecordset(UINT unConnectionDB)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	m_pPolyDb=new _DB;
	extern CADMNApp theApp;
	CString strDPath=theApp.GetADMNObj()->GetDataPath();
	CString strSystemPath=theApp.GetADMNObj()->GetSystemPath();
	switch(unConnectionDB)
	{
	case PDBRS_LOAD_FROM_APP_DB:
		CADMNObj::DBInit(theApp.GetAppCode(),theApp.GetAppODBC(),m_pPolyDb,NULL,FALSE);
		m_bDataDB=TRUE;
		break;
	case PDBRS_LOAD_FROM_SYS_DB:
		{
//			strFormat.Format("Provider=Microsoft.Jet.OLEDB.4.0;Persist Security Info=False;Data Source=%s;Jet OLEDB:Database Password=First2000",strSystemPath);
			m_pPolyDb->DBInit(DB_ACCESS,strSystemPath,strSystemPath,theApp.GetAppCode(),-1,"","","");
			m_bDataDB=FALSE;

		}
		break;
	}
}

CPolyDbRecordset::~CPolyDbRecordset()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if(m_pPolyDb)
	{
		try
		{
			delete m_pPolyDb;
			m_pPolyDb =NULL;
		}
		catch(...)
		{}
	}
}

long CPolyDbRecordset::Open(int,CString &strSql)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	m_bEOF=TRUE;
	long lRetVal=0;
	if(m_pPolyDb==NULL)
	{
		m_pPolyDb=new _DB;
		extern CADMNApp theApp;
		CString strDPath=theApp.GetADMNObj()->GetDataPath();
		CString strSystemPath=theApp.GetADMNObj()->GetSystemPath();
		CADMNObj::DBInit(theApp.GetAppCode(),theApp.GetAppODBC(),m_pPolyDb,NULL);
	}
	try
	{		
		if(m_bDataDB)
			lRetVal = m_pPolyDb->DBBuildSet(SILENTPOLYDBRECORDSET,strSql.GetBuffer(NULL),1,"",NULL,"");
		else
			lRetVal = m_pPolyDb->DBBuildSet(SILENTPOLYDBRECORDSETF,strSql.GetBuffer(NULL),1,"",NULL,"");

		if(lRetVal>0)
		{
			MoveLast();
			MoveFirst();
		}
	}
	catch(...)
	{
	}
	return lRetVal;
}

BOOL CPolyDbRecordset::IsEOF()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	if(m_bEOF)
		return m_bEOF;
	return (m_pPolyDb->RecSetEOF()==FALSE)?FALSE:TRUE;
}

void CPolyDbRecordset::Close()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	delete m_pPolyDb;
	m_pPolyDb=NULL;
}

void CPolyDbRecordset::GetFieldValue(CString strFieldName,CString &strRetValue)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	strRetValue = m_pPolyDb->RecFieldGet(strFieldName);
}

void CPolyDbRecordset::GetFieldValue(CString strFieldName,int &nRetValue)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CString strRetValue = m_pPolyDb->RecFieldGet(strFieldName);
	strRetValue.MakeUpper();
	if(strRetValue=="" || strRetValue =="FALSE")
		nRetValue=0;
	else if(strRetValue=="TRUE") 
		nRetValue=1;
	else
		nRetValue=atoi(strRetValue);
}

void CPolyDbRecordset::GetFieldValue(CString strFieldName,long &lRetValue)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CString strRetValue = m_pPolyDb->RecFieldGet(strFieldName);
	if(strRetValue=="")
		lRetValue=0;
	lRetValue=atol(strRetValue);
}
void CPolyDbRecordset::GetFieldValue(CString strFieldName,float &fRetValue)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CString strRetValue = m_pPolyDb->RecFieldGet(strFieldName);
	if(strRetValue=="")
		fRetValue=0;
	fRetValue=atof(strRetValue);
}

void CPolyDbRecordset::GetFieldValue(CString strFieldName,COleDateTime &OleDateTimeRetValue)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CString strRetValue = m_pPolyDb->RecFieldGet(strFieldName);
	OleDateTimeRetValue.ParseDateTime(strRetValue);
}

void CPolyDbRecordset::GetFieldValue(CString strFieldName,double &dRetValue)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	CString strRetValue = m_pPolyDb->RecFieldGet(strFieldName);
	if(strRetValue=="")
		dRetValue=0;
	dRetValue=atof(strRetValue);
}

void CPolyDbRecordset::Move(long lRows)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	m_pPolyDb->RecMoveAbsolute(-1,lRows);
}

void CPolyDbRecordset::MoveFirst()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	m_pPolyDb->RecMoveFirst();
	m_bEOF=FALSE;
}

void CPolyDbRecordset::MoveNext()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	m_pPolyDb->RecMoveNext();
}

void CPolyDbRecordset::MoveLast()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	m_pPolyDb->RecMoveLast();
}

void CPolyDbRecordset::AddNew()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	m_pPolyDb->RecAddNew();
}

void CPolyDbRecordset::Edit()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	m_pPolyDb->RecEdit();
}

void CPolyDbRecordset::Update()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	m_pPolyDb->RecUpdate();
}

void CPolyDbRecordset::SetFieldValue(LPCTSTR lpszName, LPCTSTR lpszValue)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	m_pPolyDb->RecFieldPut(lpszName, lpszValue);
}

BOOL CPolyDbRecordset::Find(long lFindType, LPCTSTR lpszFilter)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	short shRetVal=-1;
	switch(lFindType)
	{
	case AFX_DAO_FIRST:
		shRetVal=m_pPolyDb->RecFindFirst(lpszFilter);
		break;
	case AFX_DAO_LAST:
		shRetVal=m_pPolyDb->RecFindLast(lpszFilter);
		break;
	}
	return shRetVal==1;
}

long CPolyDbRecordset::GetAbsolutePosition()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return m_pPolyDb->RecGetAbsolute();
}

void CPolyDbRecordset::SetAbsolutePosition(long lNewPos)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	m_pPolyDb->RecMoveAbsolute(-1, lNewPos);
}

void CPolyDbRecordset::GetFullRecord(CString &strRetValue)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	strRetValue = m_pPolyDb->RecGetFullRecord();
	strRetValue.TrimRight ();
}

long CPolyDbRecordset::GetRecordCount()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	
	MoveLast();
	return GetAbsolutePosition() + 1;
}


short CPolyDbRecordset::Delete()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	return m_pPolyDb->RecDelete();
}

CString CCategory::GetInitModule()
{
	return m_pADMNobj->m_strInitModule;
}

CString CCategory::GetUserLogin()
{
	return m_pADMNobj->m_strLoginUserName;
}

BOOL CCategory::GetMRSRejectFlag()
{
	return m_pADMNobj->m_bRejectQtyInMRS;
}
CString CCategory::GetWorkingFolder()
{
	return "";
}
CString CCategory::GetUserFullName()
{
	return m_pADMNobj->m_strUserFullName;
}

CString CCategory::GetTableKey(CString TableName)
{
	CPolyDbRecordset DaoRecset(PDBRS_LOAD_FROM_SYS_DB);
	CString strKeyField;
	CString strSQL;
	strSQL.Format("SELECT DISTINCT KEYFIELD FROM vwTablesInfo WHERE TRUETABLENAME ='%s' AND APPLICATIONCODE IN (%d,%d) AND KEYFIELD IS NOT NULL",TableName,APP_CODE,m_lAppCode);
	DaoRecset.Open(AFX_DAO_USE_DEFAULT_TYPE,strSQL);	
	DaoRecset.MoveFirst();
	if(!DaoRecset.IsEOF())
	{
		DaoRecset.GetFieldValue("KEYFIELD",strKeyField);
	}
	DaoRecset.Close();
	return strKeyField;
}

CString CCategory::ShowNotepad (CString strValue,CString strEnCaption,enum TextStyle nStyle,int nType,BOOL bLocked,COLORREF bkColor)
{
	return (char*)GetADMNObj()->ShowNotepad (strValue.AllocSysString(),strEnCaption.AllocSysString(),nStyle,nType,bLocked,bkColor);
}

void CCategory::OnReletedRecordSelected(LPCTSTR strFormTag, LPCTSTR strTableName, LPCTSTR strCriteria)
{
	DoFunction(-1,CString(strFormTag),NORMAL_MODE,false,CString(strCriteria));
}

CString CCategory::GetFastSearchCriteria()
{
	return m_pADMNobj->GetFastSearchCriteria();
}

void CCategory::SetFastSearchCriteria(CString strCriteria)
{
	m_pADMNobj->SetFastSearchCriteria(strCriteria.AllocSysString());
}

