#include "stdafx.h"
//#include "io.h"
 //#include "commoncategory.h"

#include "ADMNapp.h"
#include "ADMN.h"
#include "ADMNobj.h"
//to use ADMNOBJ

#ifdef	_DEBUG
#define	new	DEBUG_NEW
#endif

#define	ADD_NEW_FROM_FILTER_SCREEN	"-2"
#define	EMPTY_SQL					"-1"

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
///////////INITIALIZE STATIC VARIABLES///////////////

long	CCommonCategory::m_nShowPos=0;
long	CCommonCategory::m_nStockCodingWay = 0;
long	CCommonCategory::m_nEmpSetting =0;
LPDISPATCH	CCommonCategory::m_pActiveRecordset = NULL;
CPolyDbRecordset *CCommonCategory::m_FirstSysRecSet=NULL;
//extern IFSearchObjPtr	gSearchObj;
extern IFirstDesktopPtr		gpFirstDesktopObj;
extern IRegHandlePtr		gpRegHandle;

//extern UINT m_unCurMenuID;
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
CCommonCategory::CCommonCategory(CCategory *pCategory)
{
	m_bDisableFilterScreen = false;
	m_strHOEmpCode = "";
	m_strHOEmpName = "";
	m_strDepartCode = "";
	m_strDepartName = "";
	m_bOpenList=false;
	m_bOneToMany=false;
	m_nScreenHelpID = 0;
	m_strComesFrom = "";
	m_bHasListWindow=FALSE;
	m_bModalScreen=TRUE;
	m_bMainSubBrowsing=FALSE;
	int nDisplayStatus=pCategory->GetDisplayStatus();
	m_bAddNewMode=nDisplayStatus==ADD_NEW_MODE;

	m_bEditMode=nDisplayStatus==EDIT_MODE;
	m_bCancelOperation=TRUE;
	m_nNumberOfUnDeletedRecords = 0;
	m_pADMNPolyDb = pCategory->GetADMNPolyDB();
	m_pADMNSYSPolyDb = pCategory->GetADMNSYSPolyDB();
	m_pCategory=pCategory;
	m_pCategory->SetMyCCategory(this);
	m_pCategory->m_pToolsListener->SetMyCCategory(this);

	m_bLanguage = m_pCategory->IsArabic();

	m_strFormTag="";
	m_bSubWindowScreen = FALSE;
	if(m_FirstSysRecSet ==NULL)
	{
		m_FirstSysRecSet = new CPolyDbRecordset(PDBRS_LOAD_FROM_SYS_DB);
		CString strFormatSQL;
		strFormatSQL.Format("SELECT * FROM vwTablesInfo WHERE APPLICATIONCODE IN (%d,%d) ORDER BY TABLENAME",APP_CODE,m_pCategory->m_lAppCode);
		m_FirstSysRecSet->Open(AFX_DAO_USE_DEFAULT_TYPE,strFormatSQL);
	}
}

CCommonCategory::~CCommonCategory()
{
	try
	{
		m_pCategory=NULL;
	}
	catch(...)
	{
		return;
	}
}

BOOL CCommonCategory::Validate()
{
	BOOL bRetVal=m_pADMNPolyDb!=NULL;
	if(!bRetVal)
	{
		if(!m_bLanguage)
			AfxMessageBox("No DB Available");
		else
			AfxMessageBox("áÇ íæÌÏ ãßÊÈÉ");
	}
	return bRetVal;
}

short CCommonCategory::GridShow(LPCTSTR title, BOOL one_to_many, BOOL AllowUpdate, BOOL AllowAdd, BOOL AllowDelete, BOOL lang, LPSTR strTableName,int nOpenState,int nHelpID)
{
	BOOL bModal=(m_pCategory->IsModalPolyDb())?TRUE:FALSE;;//The screen must be modal when in sub browsing state;
	short retval=0;
	
	if(m_pADMNPolyDb)
	{
		try
		{
			long nShowPos=m_nShowPos;
			m_nShowPos=0;
			m_bAddNewMode=FALSE;
			///////////////
			if (!AllowAdd && nShowPos == -1)
				nShowPos = 0;
//			if(nOpenState==0 && nShowPos<0)
//				nShowPos=0;			

			SetCurrentLanguage(m_bLanguage);
			if(one_to_many)
				DisableSubToolBarForLockedScreens(FALSE);

			m_pADMNPolyDb->GridShow(title,AllowUpdate, AllowAdd, AllowDelete,strTableName,(bModal)?0:m_pCategory->GetParentHWnd(),nOpenState,nShowPos,nHelpID);
			m_strMenuTitle = title;

			if(!bModal)
			{
				if (gpFirstDesktopObj != NULL && m_strMenuTitle  != "")
				{
					int nMenuID = m_pCategory->GetMenuID();
					gpFirstDesktopObj->AddRecentMenuItem(m_strMenuTitle .AllocSysString(),nMenuID);
				}
				MovePolydbForm();
			}
		}
		catch(...)
		{
			LPVOID lpMsgBuf;
			FormatMessage( 
				FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
				NULL,
				GetLastError(),
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
				(LPTSTR) &lpMsgBuf,
				0,
				NULL 
			);

			// Free the buffer.
			LocalFree( lpMsgBuf );
		}
	}
	return retval;
}

UINT CCommonCategory::ParentManage(LPCTSTR strTableName,BOOL bAllowUpdate,BOOL bAllowAddNew,BOOL bAllowDelete,CString strTableNameForSql,LPCTSTR strSelectStatement,BOOL bModal,LPCTSTR report_file ,int nMaxNoRecord ,int nCustomButtons,CString strToolTips,BOOL bIgnoreFilterScreen)
{
	if(!Validate())
		return -1;
	m_bLanguage = m_pCategory->IsArabic();
	SetCurrentLanguage(m_bLanguage);
	m_nMaxNoRecord=nMaxNoRecord;
	m_bModal=bModal;
	m_bAllowAddNew = bAllowAddNew;
	m_bAllowUpdate = bAllowUpdate;
	m_bAllowDelete = bAllowDelete;
	CString strCaptTag;
	m_strFSA ="";
	
	//use this function or the other 2 lines between braces in order of optimization

	{
		m_strFSA = strTableName;
		strCaptTag = strTableName;
	}

	if(m_strFormTag=="")
		m_strFormTag=strCaptTag;
	bModal=m_pCategory->IsModalPolyDb();
	


//	if(!bModal)
//	{
//		ThisScreenAtom=FindAtom(m_strFormTag);// USE ATOMS TO MARK THIS SCREEN AS BEING ALREADY SHOWN
//		if(ThisScreenAtom!=0)
//			return 0;	
//	}
//	ThisScreenAtom=AddAtom(m_strFormTag);
	BOOL bShowEmptyList=FALSE;
	if(m_strScreenCaption != "")
		GetScreenData(m_strScreenCaption ,m_strScreenCaption,m_strReportFileName,m_bOneToMany,m_strUniqueFields,m_strOrderFields,m_nScreenHelpID,m_strKeyField,bShowEmptyList,m_strStatusField);
	else
		GetScreenData(strCaptTag,m_strScreenCaption,m_strReportFileName,m_bOneToMany,m_strUniqueFields,m_strOrderFields,m_nScreenHelpID,m_strKeyField,bShowEmptyList,m_strStatusField);

	
	
	if (m_bOneToMany && m_bAddNewMode==false && m_bEditMode==false)
		m_bOpenList=true;

	ATOM ThisScreenAtom	=	IsScreenLoaded(strCaptTag,m_bOpenList);
	if(!ThisScreenAtom)
		return -1;

	CString strTitle;
	if(m_bLanguage)
	{
		strTitle.Format("ÞÇÆãÉ %s",m_strScreenCaption);
	}
	else
	{
		strTitle.Format("%s List",m_strScreenCaption);
	}

	if(strTableNameForSql == "")
		strTableNameForSql = m_strFSA;
	
	m_stringTableName= strTableName;	
	m_strTableNameForSql =strTableNameForSql;
	CString strBuildStatement;

	if(strSelectStatement==NULL)
	{
	//	if(m_bOneToMany)
	//		strBuildStatement.Format("SELECT * FROM %s",strTableNameForSql,m_strOrderFields);
	//	else
			strBuildStatement=GetBrowsingSQL(strTableNameForSql,strSelectStatement);
		
		if(m_strOrderFields !="")
			strBuildStatement+= " ORDER BY " + m_strOrderFields;
	}
	else
	{
		CString strSelStatement=strSelectStatement;
		strSelStatement.MakeUpper();
		int nSelectPos=strSelStatement.Find("SELECT");
		if(nSelectPos==-1 || nSelectPos>5)	// WRONG IN SELECT STATEMENT
		{
			if(strSelStatement.Find("ORDER BY") ==-1)
			{
				//strBuildStatement.Format("SELECT * FROM %s %s ",strTableNameForSql,strSelectStatement);// SHUTEQP
				strBuildStatement=GetBrowsingSQL(strTableNameForSql,strSelectStatement);
				if(m_strOrderFields !="")
				{
					strBuildStatement+= " ORDER BY " + m_strOrderFields;
				}
			}
			else
				strBuildStatement=GetBrowsingSQL(strTableNameForSql,strSelectStatement);
				//strBuildStatement.Format("SELECT * FROM %s %s",strTableNameForSql,strSelectStatement);// SHUTEQP
		}
		else
		{
			if(m_strOrderFields !="" && strSelStatement.Find(" ORDER BY ") == -1)
				strBuildStatement+= strSelStatement + " ORDER BY " + m_strOrderFields;
			else
				strBuildStatement=strSelStatement;
		}
	}

	m_strBuildStatement=strBuildStatement;
	if(m_bEditMode==FALSE)
		m_nShowPos=-1;
	if(strTableNameForSql != "DEMO" && m_bOneToMany && m_bAddNewMode==FALSE && m_bEditMode==FALSE)
	{
		CString strCaption;
		int nPosOfBrace=strCaption.Find("AS [");
		char *pCaption=strCaption.GetBuffer(NULL)+nPosOfBrace+4;
		char *pSecondBrace=strchr(pCaption,']');
		if(pSecondBrace)
			*pSecondBrace=0;
		
		CString strRetVal="";//APPTABLEINDEX";
		if (m_strKeyField != "" && m_strKeyField.Find("|")==-1)
			strRetVal =m_strKeyField;

		m_bMainSubBrowsing=TRUE;
		m_nShowPos=0;
		SetModalScreen(FALSE);
		long lRetVal=0;

		FormEnableButton(BROWSABLE,BASETOOLBAR,NEW_BUTTONNAME, m_bAllowAddNew,FALSE);
		FormEnableButton(BROWSABLE,BASETOOLBAR,DELETE_BUTTONNAME, m_bAllowDelete ,FALSE);
	
		long lParentHandle = 0;
		lParentHandle = m_pCategory->GetParentHWnd();

		CString strFastSearchCriteria = m_pCategory->GetFastSearchCriteria();
		m_pCategory->SetFastSearchCriteria("");

		if (strFastSearchCriteria != "")
		{
			m_pADMNPolyDb->CreateFilter(m_strFormTag,"Last Search",strFastSearchCriteria,0);
		}
		else if (bShowEmptyList == TRUE && bIgnoreFilterScreen == FALSE && m_bDisableFilterScreen != true)
		{
			CString strRetSQL = ShowFilterScreen(m_strFSA,m_strScreenCaption,strTableNameForSql,TRUE,m_strBuildStatement);
			if(strRetSQL == EMPTY_SQL) 
			{
				DeleteAtom(ThisScreenAtom);
				delete m_pCategory;
				return -1;
			}
			else if(strRetSQL == ADD_NEW_FROM_FILTER_SCREEN)
			{
				return 1;
			}
			if (strRetSQL != "")
				m_pADMNPolyDb->CreateFilter(m_stringTableName,"", strRetSQL, FALSE);
		}

		m_strScreenCaption=strTitle;
		lRetVal = m_pADMNPolyDb->ListShow(m_stringTableName, strTitle ,m_strBuildStatement,strRetVal ,"",TRUE,lParentHandle,m_stringTableName,-1);
		if (!bAllowUpdate)
			FormEnableButton(BROWSABLE,BASETOOLBAR,COMMON_BUTTONNAME, FALSE,FALSE);

		UpdateTablesInfoCriteria(m_stringTableName, m_strBuildStatement);
		m_strMenuTitle = strTitle;
		if(!bModal)
		{
			if (gpFirstDesktopObj != NULL && m_strMenuTitle  != "")
			{
				int nMenuID = m_pCategory->GetMenuID();
				gpFirstDesktopObj->AddRecentMenuItem(m_strMenuTitle .AllocSysString(),nMenuID);
			}
		}
		MovePolydbForm();

		if(lRetVal<0)
		{
			DeleteAtom(ThisScreenAtom);
			delete m_pCategory;
			return -1;
		}
		else
		{
			m_bHasListWindow=TRUE;
			m_bMainSubBrowsing=FALSE;
			return 0;
			MSG WindowMsg;
			while(GetMessage(&WindowMsg,NULL,NULL,NULL))
			{
				::TranslateMessage(&WindowMsg);
				::DispatchMessage(&WindowMsg);
				if(m_bMainSubBrowsing==FALSE)
					break;
			}
			if(m_nShowPos==-1 && m_bAddNewMode==FALSE)	// one to many cancel
			{
				delete m_pCategory;
				return -1;
			}
		}
	}	
	return CompleteParentManage();
}

UINT CCommonCategory::CompleteParentManage()
{
	if(m_nShowPos==-1 && m_bAddNewMode==FALSE && m_bEditMode==FALSE)	// if one to one
		m_nShowPos=0;
	m_bEditMode=FALSE;
	long lRetVal=0;
	if(m_bOneToMany)
	{
		//this is a problem in polydb that there is a relation between list and one to many
		if (m_pActiveRecordset != NULL)
			lRetVal = m_pADMNPolyDb->DBBuildSet((m_bOneToMany==FALSE)?1:2,NULL,m_nMaxNoRecord,m_strUniqueFields.GetBuffer(NULL),m_pActiveRecordset,m_strFormTag);
		else
		{
			CString strFastSearchCriteria = m_pCategory->GetFastSearchCriteria();
			if (strFastSearchCriteria != "")
			{
				m_pCategory->SetFastSearchCriteria("");
				CString strOrderBy;
				strOrderBy = m_strBuildStatement.Mid(m_strBuildStatement.Find("ORDER BY"));
				if (strOrderBy == m_strBuildStatement)
					strOrderBy="";
				m_strBuildStatement.Replace(strOrderBy,"");
				m_strBuildStatement = m_strBuildStatement + " AND " + strFastSearchCriteria.Mid(5) + " " + strOrderBy;
			}
			lRetVal = m_pADMNPolyDb->DBBuildSet((m_bOneToMany==FALSE)?1:2,m_strBuildStatement.GetBuffer(NULL),m_nMaxNoRecord,m_strUniqueFields.GetBuffer(NULL),m_pActiveRecordset,m_strFormTag);
		}
	}
	else
	{

		UpdateTablesInfoCriteria(m_stringTableName, m_strBuildStatement);
		lRetVal = m_pADMNPolyDb->DBBuildSet((m_bOneToMany==FALSE)?1:2,m_strBuildStatement.GetBuffer(NULL),m_nMaxNoRecord,m_strUniqueFields.GetBuffer(NULL),NULL,m_strFormTag);
		m_bSubWindowScreen = TRUE; //Added To Solve The Problem Of Maximum No Of Process Exceeded
	}

	if(lRetVal < 0)
	{
		AfxMessageBox("DBBUILDSET Failed");
		return -1;
	}
	lRetVal = m_pADMNPolyDb->FieldSetAttrib(m_strFSA.GetBuffer(NULL));
	if (lRetVal == 0)
	{
		MessageBox(NULL,"Screen dosen't have any attributes in FSA","Prompt",MB_OK | MB_ICONEXCLAMATION |MB_TASKMODAL);
		return 0;
	}
	int nOpenState = 0;
	if(m_bOneToMany)
	{
//		nOpenState = 2;
		CString strTag = m_strFSA;

		lRetVal = m_pADMNPolyDb->LinkSetAttrib(strTag.GetBuffer(NULL));
		lRetVal = m_pADMNPolyDb->LinkFieldsAttrib(strTag.GetBuffer(NULL));
	}

	SetScreenDefauls();
	
	m_pCategory->SetModalPollyDB(m_bModal);
	// Removed from PolyDB by Ahmed Azmy in 6 Jan 2013
	/*if(m_strReportFileName != "")
	{
		if( (_access( m_strReportFileName, 0 )) != -1 )
			m_pADMNPolyDb->ReportEnable((m_bOneToMany==TRUE)?2:1,m_strReportFileName);
	}*/
	
	UINT unRetVal=0;
	int nScreenType = ONETOONE;
	if(m_bOneToMany)
	{
		nScreenType = ONETOMANY;
	}
	FormEnableButton(nScreenType,BASETOOLBAR,NEW_BUTTONNAME, m_bAllowAddNew,FALSE);
	FormEnableButton(nScreenType,BASETOOLBAR,DELETE_BUTTONNAME, m_bAllowDelete ,FALSE);
	unRetVal=GridShow(m_strScreenCaption, m_bOneToMany,m_bAllowUpdate , m_bAllowAddNew, m_bAllowDelete, 0,(LPSTR)m_stringTableName.GetBuffer(NULL),nOpenState,m_nScreenHelpID);
	m_bHasListWindow = FALSE;
	return unRetVal;
}

void CCommonCategory::GetTablesNames(LPCTSTR strTableName,CString &strFSA,CString &strLSA,CString &strLFA,CString &strCaptTag)
{
	char *pHashPos=strchr((char*)strTableName,'#');
	if(pHashPos)
		*pHashPos=0;
	char*pSlash=strchr((char*)strTableName,'\\');
	if(pSlash)
	{
		*pSlash=0;
		strFSA=strTableName;
		pSlash++;
		if(*pSlash=='s')	// NAME\sANYTHING
		{
			pSlash++;
			char *pSlash2=strchr(pSlash,'\\');
			if(pSlash2)
			{
				*pSlash2=0;
				strLSA=pSlash;
				pSlash2++;
				if(*pSlash2=='f')	// NAME\sNAME\fANYTHING
				{
					pSlash2++;
					char *pSlash3=strchr(pSlash2,'\\');
					if(pSlash3)
					{
						*pSlash3=0;
						strLFA=pSlash2;
						pSlash3++;
						if(*pSlash3=='c')	// NAME\sNAME\fNAME\cNAME
						{
							pSlash3++;
							strCaptTag=pSlash3;
						}
						else 
							ASSERT(FALSE);
					}
					else	// NAME\sNAME\fNAME
					{
						strLFA=strCaptTag=pSlash2;
					}
				}
				else	// NAME\sNAME\cANYTHING
				{
					if(*pSlash2=='c')	// NAME\sNAME\cNAME
					{
						pSlash2++;
						strLFA=strLSA;
						strCaptTag=pSlash2;
					}
					else
						ASSERT(FALSE);
				}
			}
			else	// NAME\sNAME
			{
				strLSA=strLFA=strCaptTag=pSlash;
			}
		}
		else	// NAME\fANYTHING || NAME\cANYTHING
		{
			strLSA=strFSA;
			if(*pSlash=='f')// NAME\fANYTHING 
			{				
				pSlash++;
				char *pSlash2=strchr(pSlash,'\\');
				if(pSlash2)	// NAME\fNAME\ANYTHING
				{
					*pSlash2=0;					
					strLFA=pSlash;
					pSlash2++;
					if(*pSlash2=='c')	// NAME\fNAME\cNAME
					{
						pSlash2++;
						strCaptTag=pSlash2;
					}
					else 
						ASSERT(FALSE);
				}
				else	// NAME\fNAME
				{
					strLFA=pSlash;
				}
			}
			else	//NAME\cANYTHING
			{
				strLFA=strLSA;
				if(*pSlash=='c')
				{
					pSlash++;
					strCaptTag=pSlash;
				}
				else
					ASSERT(FALSE);
			}
		}
	}
	else	// NAME
	{
		strFSA=strTableName;
		strLSA=strTableName;
		strLFA=strTableName;
		strCaptTag=strTableName;
	}

}
CString CCommonCategory::GetDbPath()
{
	return m_pCategory->GetDbPath();
}

CString	CCommonCategory::Find(CString strAllData,CString strField,CString strTable)
{
	if(strTable!="")
	{
		CString strCaption=strField;
	}
	CString strAllDatacopy=strAllData;
	strAllDatacopy.MakeUpper();
	CString strFieldCopy=strField;
	strFieldCopy.MakeUpper();
	strFieldCopy+="|";
	int nPos=strAllDatacopy.Find(strFieldCopy);
	if(nPos<0)
		return "";
	CString strTemp=strAllData.GetBuffer(NULL)+nPos;
	CString strRetVal=strTemp.GetBuffer(NULL)+strField.GetLength()+1;
	char *pNull=strchr(strRetVal.GetBuffer(NULL),'|');
	if(pNull)
		*pNull=0;

	return strRetVal.GetBuffer(NULL);
} 

BOOL CCommonCategory::AskForRelatedTables(LPCTSTR TableName, LPCTSTR Field_name,LPCTSTR Field_Data)
{
	CString strFSA,
			strLSA,
			strLFA,
			strDumy;

	BOOL bRetVal=0;
	CString strLinkedTable="";
	CString strLinkedField="";
	CString strSearchOnLinkedField="";

	CPolyDbRecordset *pDaoRecset=new CPolyDbRecordset(PDBRS_LOAD_FROM_SYS_DB);
	CString FSAString = "SELECT DISTINCT TABLENAME,DATAFIELDNAME,BROWSINGRETFIELD FROM vwFSA WHERE BROWSINGTABLE =";
	CString LFAString = "SELECT DISTINCT TABLENAME,LINKNAME,DATAFIELDNAME,BROWSINGRETFIELD FROM vwLFA WHERE BROWSINGTABLE =";
	CString FullSqlString;

	CPolyDbRecordset *pDoaLinkTable=new CPolyDbRecordset;

	CPolyDbRecordset *pDoaTrueTableFrmLSA=new CPolyDbRecordset(PDBRS_LOAD_FROM_SYS_DB);
	CString strField_name = Field_name;
	CString strField_Data =Field_Data;
	if(strField_name!="")
		FullSqlString.Format("%s '%s' AND TABLENAME <> '%s' AND BROWSINGRETFIELD ='%s' AND APPLICATIONCODE = %ld AND FIELDSTYLE <> 11",FSAString,TableName,TableName,strField_name,m_pCategory->m_lAppCode);
	else
		FullSqlString.Format("%s '%s' AND TABLENAME <> '%s' AND APPLICATIONCODE = %ld AND FIELDSTYLE <> 11",LFAString,TableName,TableName,m_pCategory->m_lAppCode);

	pDaoRecset->Open(AFX_DAO_USE_DEFAULT_TYPE,FullSqlString);
	if(!pDaoRecset->IsEOF())
	{
		while(!pDaoRecset->IsEOF())
		{
			pDaoRecset->GetFieldValue("TABLENAME",strLinkedTable);
			if(strField_name=="")
			{
				pDaoRecset->GetFieldValue("BROWSINGRETFIELD",strField_name);
				strField_Data = Find(strField_Data,strField_name);
			}
			
			if (strField_Data != "")
			{
				if(m_pCategory->GetTableRecodingStatus(strLinkedTable))
				{
					GetTablesNames(strLinkedTable.GetBuffer(NULL),strFSA,strLSA,strLFA,strDumy);
					strLinkedTable=strFSA;

					pDaoRecset->GetFieldValue("DATAFIELDNAME",strLinkedField);
					if (strLinkedField.Find("(") == -1) // (means this field is driven by nested SQL
					{
						strSearchOnLinkedField.Format("SELECT %s FROM %s WHERE %s = '%s'",strLinkedField,strLinkedTable,strLinkedField,strField_Data);
						long lRetVal = pDoaLinkTable->Open(AFX_DAO_USE_DEFAULT_TYPE,strSearchOnLinkedField);
						if(lRetVal < ERROROPENTABLE)
						{
							pDaoRecset->MoveNext();
							continue;
						}
						if(!pDoaLinkTable->IsEOF())
						{
							bRetVal = TRUE;
							return bRetVal;
						}
					}
				}
			}
			
			pDaoRecset->MoveNext();
			bRetVal = FALSE;
		}
	}

	bRetVal=FALSE;
	if(strField_name!="")
		FullSqlString.Format("%s '%s' AND BROWSINGRETFIELD='%s' AND APPLICATIONCODE = %ld AND FIELDSTYLE IN (1,3)",LFAString,TableName,Field_name,m_pCategory->m_lAppCode);
	else
		FullSqlString.Format("%s '%s' AND APPLICATIONCODE = %ld AND FIELDSTYLE <> 11",LFAString,TableName,m_pCategory->m_lAppCode);

	pDaoRecset->Open(AFX_DAO_USE_DEFAULT_TYPE,FullSqlString);
	if(pDaoRecset->IsEOF())
		bRetVal=FALSE;
	else
	{
		while(!pDaoRecset->IsEOF())
		{

			pDaoRecset->GetFieldValue("LINKNAME",strLinkedTable);
			pDaoRecset->GetFieldValue("BROWSINGRETFIELD",strField_name);
			
			//Updated by Doaa Desouky
			//Date :17/5/2011
			/*Description
				Solve bug When (use uncoded item in material request and then try to delete Uncoded item
				the item deleted without notify user that there is related record in material request*/
			/*Solution description
				in function in case of tab use linkname from FirstSys (vwLFA) as the table name
				but in some cases the link name is diffrent with the true table name so i make the function 
				use the true table name from vwLSA instead of linkname*/
			//These lines added
			CString strTrueTableName;
			CString MainTableName;
			pDaoRecset->GetFieldValue("TABLENAME",MainTableName);
			strTrueTableName.Format("SELECT LINKOTHERTABLE FROM vwLSA WHERE TABLENAME = '%s' AND LINKNAME ='%s' AND APPLICATIONCODE = %ld" ,MainTableName, strLinkedTable, m_pCategory->m_lAppCode );
			pDoaTrueTableFrmLSA->Open(AFX_DAO_USE_DEFAULT_TYPE,strTrueTableName);
			pDoaTrueTableFrmLSA->GetFieldValue("LINKOTHERTABLE",strTrueTableName);
/////////////////////////////////////////////////////////////////////////////
			//And these lines commented
			/*GetTablesNames(strLinkedTable.GetBuffer(NULL),strFSA,strLSA,strLFA,strDumy);
			strLinkedTable=strFSA;
			pDaoRecset->GetFieldValue("DATAFIELDNAME",strLinkedField);
			strSearchOnLinkedField.Format("SELECT %s FROM %s WHERE %s = '%s'",strLinkedField,strLinkedTable,strLinkedField,strField_Data);*/
////////////////////////////////////////////////////////////////////
			//these lines are instead of commented lines 
			if (strTrueTableName != "")
			{
				GetTablesNames(strTrueTableName.GetBuffer(NULL),strFSA,strLSA,strLFA,strDumy);
				strTrueTableName=strFSA;
				pDaoRecset->GetFieldValue("DATAFIELDNAME",strLinkedField);
				strSearchOnLinkedField.Format("SELECT %s FROM %s WHERE %s = '%s'",strLinkedField,strTrueTableName,strLinkedField,strField_Data);
	////////////////////////////////////////////////////////////////////////////////////
				pDoaLinkTable->Open(AFX_DAO_USE_DEFAULT_TYPE,strSearchOnLinkedField);
				if(!pDoaLinkTable->IsEOF())
				{				
					bRetVal = TRUE;
					return bRetVal;
				}
				else
				{
					pDaoRecset->MoveNext();
					bRetVal = FALSE;
				}
			}
			else
			{
				pDaoRecset->MoveNext();
				bRetVal = FALSE;
			}
		}
	}

	pDaoRecset->Close();
	delete pDoaLinkTable;
	delete pDaoRecset;
	return bRetVal;
}
void CCommonCategory::DeleteFromRelatedTables(CString strTableName,CString strFullRecord)
{
	CPolyDbRecordset DaoRecSet(PDBRS_LOAD_FROM_SYS_DB);
	CString strOpenLFA;
	strTableName.MakeUpper();
	strOpenLFA.Format("SELECT * FROM vwLSA WHERE TableName = '%s' AND APPLICATIONCODE = %d",strTableName,m_pCategory->m_lAppCode);

	DaoRecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,strOpenLFA);
	if(DaoRecSet.IsEOF())
	{
		DaoRecSet.Close();
		return;
	}
	
	CString strLinkedTableName;
	CString strLinkedLocalField;
	CString strLinkedLocalFieldContents;
	CString strLinkedOtherField;
	CString strFullDeleteSql;
	CString strTabAttrib;
	while(!DaoRecSet.IsEOF())
	{
		DaoRecSet.GetFieldValue("LinkOtherTable",strLinkedTableName);
		DaoRecSet.GetFieldValue("LinkLocalField",strLinkedLocalField);
		DaoRecSet.GetFieldValue("LinkOtherField",strLinkedOtherField);
		DaoRecSet.GetFieldValue("TABATTRIB",strTabAttrib);
		if(strTabAttrib.Find("VIEW") >=0)
		{
			DaoRecSet.MoveNext();
			continue;
		}
		strLinkedLocalFieldContents = Find(strFullRecord,strLinkedLocalField,strTableName);
		
		if(strLinkedTableName != "")
		{
			strFullDeleteSql.Format("DELETE FROM %s WHERE %s = '%s'",strLinkedTableName,strLinkedOtherField,strLinkedLocalFieldContents);
			ExecuteSQL(strFullDeleteSql);
		}
		DaoRecSet.MoveNext();
	}
	DaoRecSet.Close();
}

void CCommonCategory::SetCurrentPos(long lAbsolutePosition)
{
	m_nShowPos = lAbsolutePosition;
}

long CCommonCategory::ExecuteSQL(CString& strSqlStatement,UINT unConnectionDB,BOOL bIgnoreCommit)
{
	long lRetVal = m_pCategory->ExecuteSQL(strSqlStatement,unConnectionDB,bIgnoreCommit);
	return lRetVal;
}

void CCommonCategory::GetScreenData(CString &strFSA,CString &strScreenCaption,CString &strReportFile,BOOL &m_bOneToMany,CString &strUniqueFields,CString &strOrderFields,int &nHelpID,CString &strKeyField,BOOL &bShowEmptyList,CString &strStatusField)
{
	CString strFormatSQL;
	CString strTag=strFSA;
	
	strFormatSQL.Format("TABLENAME = '%s'",strTag);
	BOOL bRetVal = m_FirstSysRecSet->Find(AFX_DAO_FIRST,strFormatSQL);
	CString strScreenName="";
	CString strReportFileName,strSingleMany,strUniqueFieldsCriteria;
	strOrderFields = "1";
	if(bRetVal==FALSE)
	{
		strScreenCaption = "";
		strReportFile = "";
		m_bOneToMany=FALSE;
		return;
	}

	////////////////////////////////////////////////////////////////////////////
	// Get screen caption from the EXE Menu (may be changed from the privilege)
	CString strAppTitle,strArabicTitle,strEnglishTitle;
	strArabicTitle.LoadString(IDS_ARABICCAPTION);
	strEnglishTitle.LoadString(IDS_ENGLISHCAPTION);

	m_pCategory->GetParentWnd()->GetWindowText(strAppTitle);
	if (strAppTitle == strArabicTitle || strAppTitle == strEnglishTitle)
	{
		long lMenuID = m_pCategory->GetMenuID();
		CMenu* pMenu = m_pCategory->GetParentWnd()->GetMenu();
		pMenu->GetMenuString(lMenuID,strScreenName,MF_BYCOMMAND);
		strScreenName.Replace("&","");
		if (strScreenName.Find("  ") != -1)
			strScreenName = strScreenName.Mid(0,strScreenName.Find("  "));

#ifdef	_DEBUG
		CString strMenuID;
		strMenuID.Format("%ld",lMenuID);
		m_FirstSysRecSet->SetFieldValue("MENUID",strMenuID);
		m_FirstSysRecSet->Update();
#endif

	}
	if (strScreenName == "")
	{
		if(!m_bLanguage)
			m_FirstSysRecSet->GetFieldValue("ENGLISHCAPTION",strScreenName);
		else
			m_FirstSysRecSet->GetFieldValue("ARABICCAPTION",strScreenName);
	}
	////////////////////////////////////////////////////////////////////////////

	m_FirstSysRecSet->GetFieldValue("REPORTFILENAME",strReportFileName);
	m_FirstSysRecSet->GetFieldValue("UNIQUEFIELDS",strUniqueFieldsCriteria);
	m_FirstSysRecSet->GetFieldValue("SINGLEMANY",strSingleMany);
	m_FirstSysRecSet->GetFieldValue("ORDERBYCLAUSE",strOrderFields);//LOAD THE SORT ORDER CRITERIA
	m_FirstSysRecSet->GetFieldValue("HELPCONTEXTID",nHelpID);
	m_FirstSysRecSet->GetFieldValue("KEYFIELD",strKeyField);
	m_FirstSysRecSet->GetFieldValue("SHOWEMPTYLIST",bShowEmptyList);
	m_FirstSysRecSet->GetFieldValue("STATUSFIELD",strStatusField);

	if(strOrderFields == "")
		m_strOrderFields = "";

	if(strSingleMany == "2")
	{
		m_bOneToMany = TRUE;
		m_bSubWindowScreen = TRUE;
	}
	else
		m_bOneToMany = FALSE;

	strScreenCaption = strScreenName;
	strUniqueFields = strUniqueFieldsCriteria;
}

CString CCommonCategory::GetCurrentDate(CString &strFormat)
{
	CString strRetDate;
	CString strDate = m_pADMNPolyDb->GetServerDate();
	COleDateTime OleDate;
	OleDate.ParseDateTime(strDate);

	if(strFormat != "MONTHDAYYEAR")
		strRetDate = OleDate.Format("%d/%m/%Y");
	else
		strRetDate = OleDate.Format("%m/%d/%Y");
	return strRetDate;
}
void CCommonCategory::WaitCursor()
{
	AfxGetApp()->BeginWaitCursor();
	return;
}
BOOL CCommonCategory::AskYesNoMessage(CString &strTitle,CString &strMessage)
{
	BOOL bRetVal;
	if(m_bLanguage)
		strTitle = "ÊäÈíå";
	if(MessageBox(NULL,strMessage,strTitle,MB_YESNO | MB_ICONEXCLAMATION | MB_TASKMODAL) == IDYES)
		bRetVal =  TRUE;
	else 
		bRetVal =  FALSE;
	return bRetVal;
}
void CCommonCategory::FillListRecordSet(LPDISPATCH	pActiveRecordset)
{
	m_pActiveRecordset = pActiveRecordset;
}

void CCommonCategory::DisableSubToolBarForLockedScreens(BOOL bDelete)
{
	FormEnableButton(ONETOMANY,SUBTOOLBAR,COPY_BUTTONNAME,FALSE,FALSE);
	FormEnableButton(ONETOMANY,SUBTOOLBAR,COMMON_BUTTONNAME,FALSE,FALSE);
	if(bDelete)
		FormEnableButton(ONETOMANY,SUBTOOLBAR,DELETE_BUTTONNAME,FALSE,FALSE);
}

void CCommonCategory::ActivateListWindow()
{
	ATOM ScrAtom = FindAtom(m_strFormTag);
	if(ScrAtom!=0)
	{
		DeleteAtom(ScrAtom);
	}
	m_bHasListWindow = TRUE;
	m_pActiveRecordset = NULL; //reset the Active RecordSet
}

CString CCommonCategory::GetTrueTableName()
{
	return m_strTableNameForSql;
}

BOOL CCommonCategory::CheckKey(CString &strTableName)
{
	ATOM ThisScreenAtom=FindAtom(strTableName);
	if(ThisScreenAtom)
	{
		MessageBox(NULL,"This Screen is already opened","Prompt",MB_OK | MB_ICONEXCLAMATION |MB_TASKMODAL);
		return TRUE;
	}
	return FALSE;
}

COleDateTime CCommonCategory::GetGregDate(CString &strDate)
{
	COleDateTime GergDate;
	GergDate.ParseDateTime(strDate);
	if(m_pCategory->IsArabic())
	{
		COleDateTime oleHDate;
		UDATE uHijriiDate;
		HRESULT hr=E_INVALIDARG;
		LONG lCounter=0;
		int iDay=0;
		int iMonth=0;
		int iYear=0;
		iDay=__min(GergDate.GetDay(),30);
		iMonth=GergDate.GetMonth();
		iYear=GergDate.GetYear();
		oleHDate.SetStatus(COleDateTime::invalid);
		while (oleHDate.m_status == COleDateTime::invalid && lCounter < 10)
		{
			oleHDate.SetDateTime(iYear,iMonth,iDay-lCounter,0,0,0);
			oleHDate.GetAsSystemTime(uHijriiDate.st );
			hr=VarDateFromUdate(&uHijriiDate,VARIANT_CALENDAR_HIJRI,&oleHDate.m_dt);
			lCounter ++;
		}
		lCounter --;
		if(hr == S_OK)
			GergDate.m_dt=oleHDate.m_dt - lCounter;
		CString strMyDate = GergDate.Format("%d/%m/%Y");
	}
	return GergDate;
}

CString CCommonCategory::GetTXNIndex(CString strTable,CString strRetField,CString strRefField,CString strRefValue,CString strWhereClause)
{
	CString strSQL,strTXNIndex;
	if(strWhereClause=="")
		strSQL.Format("SELECT %s FROM %s WHERE %s = '%s'",strRetField,strTable,strRefField,strRefValue);
	else
	{
		if(strWhereClause.Find("WHERE ")==0)
		{
			strSQL.Format("SELECT %s FROM %s %s = '%s' AND %s",strRetField,strTable,strRefField,strRefValue,strWhereClause);
		}
		else
			strSQL.Format("SELECT %s FROM %s WHERE %s = '%s' AND %s",strRetField,strTable,strRefField,strRefValue,strWhereClause);
	}
	CPolyDbRecordset DaoRecSet;
	DaoRecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,strSQL);
	DaoRecSet.GetFieldValue(strRetField,strTXNIndex);
	DaoRecSet.Close();
	return strTXNIndex;
}

int CCommonCategory::GetCount(CString strTableName,CString strLinkField,CString strIndex,BOOL bString,CString strAddSQL)
{
	CString strSQL;
	int nCount = 0;
	if(bString==TRUE)//means string format
		strSQL.Format("SELECT COUNT (1) AS NOOFRECORDS FROM %s WHERE %s = '%s'",strTableName,strLinkField,strIndex);
	else
		strSQL.Format("SELECT COUNT (1) AS NOOFRECORDS FROM %s WHERE %s = %s",strTableName,strLinkField,strIndex);
	if(strAddSQL !="")
	{
		if (strAddSQL.Find("WHERE") == 0)
		{
			strAddSQL = strAddSQL.Mid(5);
		}
		strSQL+=" AND "+strAddSQL;
	}
	nCount = GetRetVal(strSQL);
	return nCount ;
}

// by aazmy bug id:7940 
CString CCommonCategory::GetTafkeetVal(CString &strSQL)
{
	CPolyDbRecordset DaoRecSet;
	DaoRecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,strSQL);
	DaoRecSet.MoveFirst();
	CString strValue;
	DaoRecSet.GetFieldValue("TAFKEET",strValue);
	DaoRecSet.Close();
	return strValue;
}

long CCommonCategory::GetRetVal(CString &strSQL)
{
	CPolyDbRecordset DaoRecSet;
	DaoRecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,strSQL);
	DaoRecSet.MoveFirst();
	long lCount =-1;
	DaoRecSet.GetFieldValue("NOOFRECORDS",lCount);
	DaoRecSet.Close();
	return lCount;
}
double CCommonCategory::GetRetDVal(CString &strSQL)
{
	CPolyDbRecordset DaoRecSet;
	DaoRecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,strSQL);
	DaoRecSet.MoveFirst();
	double lCount =-1;
	DaoRecSet.GetFieldValue("NOOFRECORDS",lCount);
	DaoRecSet.Close();
	return lCount;
}

CString CCommonCategory::FormatValueForSQL(CString strValue)
{
	strValue.Replace("'","''");
	return strValue;
}


//this function to get the sort order of the items tab in order to 
//create the line numbers correct
CString CCommonCategory::GetOrderCriteria(CString strMainTableName,CString strTableName)
{
	CPolyDbRecordset DaoRecSet(PDBRS_LOAD_FROM_SYS_DB);
	CString strSQL;
	strSQL.Format("SELECT DISTINCT LINKSQL FROM vwLSA WHERE APPLICATIONCODE=%d AND TABLENAME='%s' AND LINKOTHERTABLE = '%s'",m_pCategory->m_lAppCode,strMainTableName,strTableName);
	CString strSortOrder = "";//ORDER BY 1";
	DaoRecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,strSQL);
	if(DaoRecSet.IsEOF())
	{
		DaoRecSet.Close();
		return strSortOrder;
	}

	DaoRecSet.MoveFirst();
	DaoRecSet.GetFieldValue("LINKSQL",strSortOrder);
	DaoRecSet.Close();

	int nPos = strSortOrder.Find("ORDER BY");
	if (nPos >=0)
		strSortOrder = strSortOrder.Mid(nPos);
	return strSortOrder;
}
CString CCommonCategory::GetSegment(CString strScreenTag)
{
	m_pCategory->m_pToolsListener->InitDBTools();

	CString strGeneratedCode;
	CString strSQL;
	strGeneratedCode= m_pCategory->m_pToolsListener->m_pToolsObj->GetSegmentedCode(m_pCategory->m_lAppCode,strScreenTag,"",FALSE);
	if (strGeneratedCode != "")
	{
		m_pCategory->m_pToolsListener->m_pToolsObj->IncreaseSegment(m_pCategory->m_lAppCode,strScreenTag,"");
	}
	return strGeneratedCode;
}

CString CCommonCategory::GetFieldAttributes(CString &strTableName,CString &strFieldName)
{
	CString strAttrib;
	CPolyDbRecordset DaoRecSet(PDBRS_LOAD_FROM_SYS_DB);
	CString strFormatSQL;
	strFormatSQL.Format("SELECT ValidationRule FROM fsa WHERE APPLICATIONCODE = %d and TableName ='%s' and DataFieldName = '%s'",m_pCategory->m_lAppCode,strTableName,strFieldName);
	DaoRecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,strFormatSQL);
	DaoRecSet.GetFieldValue("ValidationRule",strAttrib);
	return strAttrib;
}

void CCommonCategory::RefreshScreen()
{
	FormDoAction(GetFormType(),SAVE_BUTTON);
	FormMakeRefresh(GetFormType());
}

CString CCommonCategory::GetBrowsingSQL(CString TableName, LPCTSTR WhereClause)
{
	return m_pADMNPolyDb->GetBrowsingSQL(TableName,WhereClause);
}

void CCommonCategory::SetCurrentLanguage(BOOL bNewValue)
{
	m_pADMNPolyDb->SetCurrentLanguage(bNewValue);
}

void CCommonCategory::SubMakeRefresh()
{
	m_pADMNPolyDb->SubMakeRefresh();
}
short CCommonCategory::GetFormType()
{
	return m_pADMNPolyDb->GetFormType();
}
short CCommonCategory::FormEnableButton(short Form_Type, short ToolbarID, LPCTSTR ButtonKey, BOOL State, BOOL bForCurrTabOnly)
{
	return m_pADMNPolyDb->FormEnableButton(Form_Type, ToolbarID, ButtonKey, State, bForCurrTabOnly);
}
void CCommonCategory::LockScreen(short Form_Type, BOOL bLockMain, BOOL bLockSubs)
{
	m_pADMNPolyDb->LockScreen(Form_Type,bLockMain,bLockSubs);
}

short CCommonCategory::LinkFieldsAttribSingle(LPCTSTR Link_Name, LPCTSTR Field_Name, LPCTSTR Field_Caption, short Max_Length, LPCTSTR Field_Help, LPCTSTR Field_Attrib_Rules, LPCTSTR Field_Mask, LPCTSTR Field_Default, short Field_Style, LPCTSTR Field_F_Table, 
		LPCTSTR Field_F_SQL, LPCTSTR Field_F_Field, LPCTSTR Field_Ret_Field, LPCTSTR strBrowsingArray, long ArabicHelpContextID, long EnglishHelpContextID, LPCTSTR strBrowsingHelpFields)
{
	return m_pADMNPolyDb->LinkFieldsAttribSingle(Link_Name, Field_Name, Field_Caption, Max_Length, Field_Help, Field_Attrib_Rules, Field_Mask, Field_Default, Field_Style, Field_F_Table, 
		Field_F_SQL, Field_F_Field, Field_Ret_Field, strBrowsingArray, ArabicHelpContextID, EnglishHelpContextID, strBrowsingHelpFields);
}
short CCommonCategory::FieldSetAttribSingle(LPCTSTR Field_Name, LPCTSTR Field_Caption, short Max_Length, LPCTSTR Field_Help, LPCTSTR Field_Attrib_Rules, LPCTSTR Field_Mask, LPCTSTR Field_Default, short Field_Style, LPCTSTR Field_F_Table, LPCTSTR Field_F_SQL, 
		LPCTSTR Field_F_Field, LPCTSTR Field_Ret_Field, LPCTSTR strBrowsingArray, long ArabicHelpContextID, long EnglishHelpContextID, LPCTSTR strBrowsingHelpFields)
{
	return m_pADMNPolyDb->FieldSetAttribSingle(Field_Name, Field_Caption, Max_Length, Field_Help, Field_Attrib_Rules, Field_Mask, Field_Default, Field_Style, Field_F_Table, Field_F_SQL, 
		Field_F_Field, Field_Ret_Field, strBrowsingArray, ArabicHelpContextID, EnglishHelpContextID, strBrowsingHelpFields);
}
CString CCommonCategory::ShowFilterScreen(LPCTSTR strTableName, LPCTSTR strCaption, LPCTSTR strTrueTableName, BOOL bSaveFilter, LPCTSTR strBaseCriteria,CString *pstrReadableCriteria)
{
	BSTR bstrReadableCriteria;
	
	if (pstrReadableCriteria == NULL)
		bstrReadableCriteria = CString("").AllocSysString();
	else
		bstrReadableCriteria = pstrReadableCriteria->AllocSysString();
	
	CString strSQL;

	CString strFormCaption(strCaption);
	if (m_bAllowAddNew)
		strFormCaption += "|ADDNEW";

	strSQL = m_pADMNPolyDb->ShowFilterScreenEx(strTableName, strFormCaption, strTrueTableName, bSaveFilter, strBaseCriteria,&bstrReadableCriteria);//,m_bAllowAddNew);
	
	if (pstrReadableCriteria != NULL)
		*pstrReadableCriteria = CString(bstrReadableCriteria);

	return strSQL;
}
CString CCommonCategory::FormChangeCaption(short Form_Type, LPCTSTR strCaption)
{
	return m_pADMNPolyDb->FormChangeCaption(Form_Type, strCaption);
}
//Poly Db Encapsulation
CString CCommonCategory::ListShowEx(LPCTSTR List_Tag, LPCTSTR List_Title, LPCTSTR SQL_Statement, LPCTSTR Return_Field, LPCTSTR Old_Value, BOOL MultiSelection, LPCTSTR strAttribTableName, long lHelpID)
{
	_DB pPolyDb;
	m_pCategory->GetADMNObj()->DBInit(m_pCategory->GetADMNObj()->GetAppCode(),m_pCategory->GetADMNObj()->GetODBC(),  &pPolyDb,NULL,FALSE);
	pPolyDb.FormEnableButton(BROWSABLE,BASETOOLBAR,NEW_BUTTONNAME, FALSE,FALSE);
	pPolyDb.FormEnableButton(BROWSABLE,BASETOOLBAR,DELETE_BUTTONNAME, FALSE,FALSE);
	pPolyDb.FormEnableButton(BROWSABLE,BASETOOLBAR,COMMON_BUTTONNAME, FALSE,FALSE);
	return pPolyDb.ListShowEx(List_Tag, List_Title,SQL_Statement,Return_Field ,Old_Value,MultiSelection,strAttribTableName,lHelpID);
}

void CCommonCategory::FormSetFieldEx(CString strFormTag ,CString Field,CString Value,int nFormType)
{
	m_pADMNPolyDb->FormSetField(strFormTag,Field,Value,nFormType);
}

void CCommonCategory::FormSetField(CString strTableName,CString Field,CString Value,int nFormType)
{
	m_pADMNPolyDb->FormSetField(strTableName,Field,Value,nFormType);
}

void CCommonCategory::FormDoAction(short Form_Type, short Button_Index)
{
	m_pADMNPolyDb->FormDoAction(Form_Type, Button_Index);
}
short CCommonCategory::FormMakeRefresh(short Form_Type)
{
	return m_pADMNPolyDb->FormMakeRefresh(Form_Type);
}

CString CCommonCategory::FormGetFieldEx(CString strFormTag ,CString Field,int nFormType)
{
	return m_pADMNPolyDb->FormGetFieldEx(strFormTag,Field,nFormType);
}

CString CCommonCategory::FormGetField(CString strTableName,CString Field,int nFormType)
{
	CString strRetVal = m_pADMNPolyDb->FormGetField(strTableName,Field,nFormType);
	
	if (strRetVal == "/  /")
		strRetVal = "";

	return strRetVal;
}
void CCommonCategory::HandleActionEx(short Form_Type, BOOL Cancel, short Selected_Records)
{
	m_pADMNPolyDb->HandleAction(Form_Type, Cancel, Selected_Records,"");
}

short CCommonCategory::TabEnableEx(LPCTSTR strSubTag, BOOL State)
{
	return m_pADMNPolyDb->TabEnableEx(strSubTag, State);
}

void CCommonCategory::MovePolydbForm()
{
	CRect rcRect;
	CWnd::FromHandle((HWND)m_pCategory->GetParentHWnd())->GetClientRect(&rcRect);

	CRect rc=m_pCategory->GetFormRect();
	if(rc.bottom == 0)
		return;
	m_pADMNPolyDb->MoveForm(-1,rc.left,rc.top,rc.Width()+rc.left,rc.Height()+rc.top);
	m_pCategory->m_pToolsListener->m_pToolsObj->MoveTree(rc.left,rc.top,rc.Width()+rc.left,rc.Height()+rc.top);
}
void CCommonCategory::OnScreenExit()
{
	if (gpFirstDesktopObj != NULL)// && (m_bOpenList || m_bOneToMany == FALSE) )
	{
		int nMenuID = m_pCategory->GetMenuID();
		gpFirstDesktopObj->RemoveRecentMenuItem(m_strScreenCaption.AllocSysString(),nMenuID);
	}
}

void CCommonCategory::BringWindowToTop()
{
	if (gpFirstDesktopObj != NULL)
		gpFirstDesktopObj->ActivateMenuItem(m_strMenuTitle.AllocSysString());

	m_pADMNPolyDb->BringFormToTop(-1);
}

void CCommonCategory::UpdateTablesInfoCriteria(CString strFormTag, CString strSQL)
{
	// THIS FUNCTION WAS USED ONCE TO UPDATE [WhereClause] IN [vwTablesInfo] TABLE UNDER FIRSTSYSDB.MDB
	// THE [WhereClause] FIELD IS VERY ESSENTIAL IN FIELD DEPENDENCY FEATURE IN POLYDB 
	// BY AHMED AZMY
	return;

	CString strWhere = "";
	
	strSQL.MakeUpper();
	
	if (strSQL.Find("ORDER BY ") != -1)
		strSQL = strSQL.Left(strSQL.Find("ORDER BY "));

	if (strSQL.Find("WHERE ") != -1)
		strWhere = strSQL.Mid(strSQL.Find("WHERE "));

	if (strWhere != "")
	{
		AfxMessageBox(strWhere);
		strWhere.Replace("'","''");
		CString strUpdateSQL;
		strUpdateSQL.Format("UPDATE TablesInfo SET WhereClause='%s' WHERE (WhereClause='' OR WhereClause IS NULL) AND ApplicationCode=%d AND TableName='%s'",strWhere,m_pCategory->m_lAppCode,strFormTag);
		long lRetFieldsCount = m_pADMNPolyDb->DBExecSql((LPCSTR)strUpdateSQL,PDBRS_LOAD_FROM_SYS_DB,0);
		if (lRetFieldsCount != 1)
			AfxMessageBox("ERROR");
	}
}

ATOM CCommonCategory::IsScreenLoaded(CString strFormTag, bool bList)
{
	int nSkip=0;
	ATOM ThisScreenAtom=0;
	try
	{
		BOOL bModal=m_pCategory->IsModalPolyDb();
		if(!bModal)
		{
			ThisScreenAtom=FindAtom(strFormTag);
			if(ThisScreenAtom!=0)
			{
				!bList ? nSkip=1:nSkip=0;
				m_pCategory->GetADMNObj()->ActivateForm(strFormTag.AllocSysString(),true,nSkip,true);
				ThisScreenAtom=0;
				return 0;	
			}
		}
		ThisScreenAtom=AddAtom(strFormTag);
	}
	catch(...)
	{
		
	}
	return ThisScreenAtom;
}

CString CCommonCategory::GetSelectedRecordCriteria()
{
	CString strCriteria;
	CString strKeyFieldValue = m_pADMNPolyDb->FormGetField(m_strTableNameForSql,m_strKeyField,-1);
	strCriteria.Format("%s='%s'", m_strKeyField, strKeyFieldValue);
	return strCriteria;
}

void CCommonCategory::FindRecord(CString strCriteria)
{
	m_pADMNPolyDb->FindRecord(strCriteria,-1);
}

void CCommonCategory::SetScreenDefauls()
{
	m_strScreenDefauls = m_pCategory->GetScreenDefauls();
	
	CString strScreenDefauls = m_strScreenDefauls;

	strScreenDefauls.Replace("||","| |");
	if (strScreenDefauls == "")
		return;


	CString strFieldName=strtok(strScreenDefauls.GetBuffer (0),"|");
	CString strValue=strtok(NULL,"|");
	
	FieldSetAttribSingle(strFieldName,"",-1,"","","",strValue,-1,"","","","""","",0,0,"");	

	while (strValue != "")
	{
		strFieldName=strtok(NULL,"|");
		strValue=strtok(NULL,"|");
		FieldSetAttribSingle(strFieldName,"",-1,"","","",strValue,-1,"","","","""","",0,0,"");	
	}
	
}


//---START---------Manage Synchronous Changes ---------By Nehad in 15 April 2014-----------------------
// This Function used in category class to save the record status in the start
void CCommonCategory::SetStartedTXNStatus()
{
	if(GetStatusFieldName() == "")
		return;

	m_strStatusVal = FormGetField(GetTrueTableName(),GetStatusFieldName());
}
// This Helper function to read current record status at any action on this screen (field change ,toolbar or custom button)
CString CCommonCategory::ReadTXNStatus()
{
	if(GetStatusFieldName() == "")
		return "";

	CString strKeyFieldVal = FormGetField(GetTrueTableName(),m_strKeyField);	
	CString strStatus = GetTXNIndex(GetTrueTableName(),GetStatusFieldName(),m_strKeyField,strKeyFieldVal,"");
	return strStatus;
}
// This Helper function to check if the record status changed or not.
BOOL CCommonCategory::IsStatusChanged()
{
	if(GetStatusFieldName() == "")
		return FALSE;

	CString strCurrentStatus = ReadTXNStatus();
	if(m_strStatusVal != "" && strCurrentStatus != "" && strCurrentStatus != m_strStatusVal)
	{
		return TRUE;
	}
	return FALSE;
}
// This Function used in category class to perform action if the record status changed
BOOL CCommonCategory::ValidateOnRecordStatus()
{
	if(GetStatusFieldName() == "")
		return TRUE;		

	if(IsStatusChanged())
	{
		if(!m_bLanguage)
			AfxMessageBox("Sorry, This record was changed by another user.");
		else
			AfxMessageBox("äÃÓÝ, åÐÇ ÇáÓÌá ÞÏ ÊãÊÛííÑå ãä ÞÈá ãÓÊÎÏã ÂÎÑ.");
		m_bCancelOperation = TRUE;
		short nShort=0;
		try
		{
			HandleActionEx(-1,TRUE,nShort);
		}
		catch(...)
		{

		}
		FormMakeRefresh(GetFormType());
		
		return FALSE;
	}
	return TRUE;
}
//---END---------Manage Synchronous Changes ---------By Nehad in 15 April 2014-----------------------


CString CCommonCategory::GetPolicySettingValue(CString strSettingName)
{
	IRegHandlePtr pRegHandle = gpRegHandle;
	CString strSection	= "ADMN";
	CString strValue = (char*)pRegHandle->GetSetting("ADMN",strSection.AllocSysString(),strSettingName.AllocSysString(),"");
	return strValue;
}

CString CCommonCategory::GetValueFromSQL(CString strSQL,CString strField)
{
	CString strRetVal;
	CPolyDbRecordset DaoRecSet;
	DaoRecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,strSQL);
	DaoRecSet.GetFieldValue(strField,strRetVal);
	DaoRecSet.Close();
	return strRetVal;
}

long CCommonCategory::RebuildSegments(CString strFormTag, CString strSQL)
{
	m_pCategory->m_pToolsListener->InitDBTools();
	return m_pCategory->m_pToolsListener->m_pToolsObj->RebuildSegments(m_pCategory->m_lAppCode, strFormTag, strSQL);
}

void CCommonCategory::GetEmpInfoByLogin()
{
	CString strRetVal;
	CPolyDbRecordset DaoRecSet;

	CString strSQL;
	strSQL.Format("SELECT EMPLOYEE_CODE,EMPLOYEE_NAME,EMPLOYEE_WSHOP DEPART_CODE,(SELECT ISNULL(DEPART_NAME,DEPART_DESCR) FROM CMN_DEPART WHERE DEPART_CODE=EMPLOYEE_WSHOP) DEPART_NAME FROM CMN_EMPLOYEE WHERE EMPLOYEE_LOGINNAME='%s'",m_pCategory->GetUserLogin());
	
	DaoRecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,strSQL);
	DaoRecSet.GetFieldValue("EMPLOYEE_CODE",m_strHOEmpCode);
	DaoRecSet.GetFieldValue("EMPLOYEE_NAME",m_strHOEmpName);
	DaoRecSet.GetFieldValue("DEPART_CODE",m_strDepartCode);
	DaoRecSet.GetFieldValue("DEPART_NAME",m_strDepartName);

	DaoRecSet.Close();
}

CString CCommonCategory::GetHOEmails(CString strHOCode,CString strType)
{
	CString strRetVal="";
	CPolyDbRecordset DaoRecSet;

	CString strSQL;
	strSQL.Format("SELECT HOEMAIL_EMAIL FROM CMN_HOEMAIL WHERE HOEMAIL_HOCODE = '%s' AND HOEMAIL_TYPE='%s'",strHOCode,strType);

	DaoRecSet.Open(AFX_DAO_USE_DEFAULT_TYPE,strSQL);

	CString strEmail;
	while (!DaoRecSet.IsEOF())
	{
		DaoRecSet.GetFieldValue("HOEMAIL_EMAIL",strEmail);
		if (strEmail != "")
			strRetVal = strRetVal + strEmail + ";";

		DaoRecSet.MoveNext();
	}
	
	DaoRecSet.Close();

	if (strRetVal != "")
	{
		if (strRetVal.Right(1) == ";")
			strRetVal = strRetVal.Left(strRetVal.GetLength()-1);
	}
	return strRetVal;
}
