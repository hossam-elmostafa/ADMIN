// DocLib.cpp: implementation of the CDocLib class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DocLib.h"
#include "ADMNApp.h"
#include "ADMN.h"
#include "ADMNobj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void CDocLib::ShowDocumentLibrary()
{
	MovePolydbForm();
	m_nCurrentCard=SHOWDOCUMENTLIBRARY;
	ParentManage("VWCPMS_TNDRLIB");
}

void CDocLib::ShowDocumentTemplates()
{
	MovePolydbForm();
	m_nCurrentCard=SHOWDOCUMENTTEMPLATES;
	ParentManage("VWCPMS_TOCTMPLT");
}

void CDocLib::ShowLibrarySubs(CString strSQL,CString strComesFrom,CString strScreenDefaults)
{
	MovePolydbForm();
	m_nCurrentCard=LIBRARYSUBS;

	bool bFullAccess = true;
	
	if (strComesFrom == "")
		strComesFrom = Find(strScreenDefaults,"COMES_FROM");
	
	if (strComesFrom == "????")// use it if you want to make it read only
		bFullAccess = false;

	m_pCategory->GetADMNObj()->SetLibrarySubsScreenDefauls(strScreenDefaults);
	m_pCategory->GetADMNObj()->SetScreenDefauls(strScreenDefaults);

	ParentManage("VWCPMS_TNDRLIBSBCNTNT",bFullAccess,bFullAccess,bFullAccess,"VWCPMS_TNDRLIBSBCNTNT",strSQL,true);
}	

long CDocLib::ButtonClicked(LPCTSTR Caption, LPCTSTR Table_Name, LPCTSTR Master_Full_Recoed,LPCTSTR Details_Full_Recoed,LPCTSTR Field_Caption)
{
	CString strButtonName (Caption);
	CString strFormTag(Table_Name);
	strButtonName.MakeUpper();

	if (strButtonName == "SHOW_LIBRARY_TREE")
		ShowLibraryTree();

	else if (strButtonName == "EDIT_CONTENT")
	{
		if (strFormTag == "VWCPMS_TNDRLIB")
			EditContent("TNDRLIBCNTNT");

		else if (strFormTag == "VWCPMS_TNDRLIBSBCNTNT")
			EditContent("TNDRLIBSBCNTNT");
	}

	else if (strButtonName == "ADD_NEW_VERSION")
	{
		if (strFormTag == "VWCPMS_TNDRLIB")
		{
			CString strLibCode = FormGetField("VWCPMS_TNDRLIBCNTNT","TNDRLIBCNTNT_FULCOD");
			AddNewVersion(strLibCode,true);
			SubMakeRefresh();
		}

		else if (strFormTag == "VWCPMS_TNDRLIBSBCNTNT")
		{
			CString strLibCode = FormGetField("VWCPMS_TNDRLIBSBCNTNT","TNDRLIBSBCNTNT_FULCOD");
			AddNewVersion(strLibCode,false);
			FormMakeRefresh(UNKNONE);
		}
	}

	else if (strButtonName == "SUB_CONTENT")
	{
        CString strLibCode = m_pADMNPolyDb->FormGetField("VWCPMS_TNDRLIBCNTNT", "TNDRLIBCNTNT_FULCOD", ONETOMANY);
        CString strCriterea;

		if (strLibCode == "")
			return 0;

        strCriterea.Format("SELECT * FROM VWCPMS_TNDRLIBSBCNTNT WHERE (TNDRLIBSBCNTNT_MCOD='%s')",strLibCode);
        
		CString strDefaults="";
		strDefaults.Format("COMES_FROM|%s|TNDRLIBSBCNTNT_MCOD|%s",strFormTag,strLibCode);
		
		m_pCategory->DoFunction(0,"VWCPMS_TNDRLIBSBCNTNT",NORMAL_MODE,TRUE,strCriterea,strFormTag,strDefaults);
	}

	return 0;	
}

CString CDocLib::AddNewVersion(CString strLibCode,bool bMainTitle)
{
	// 256-90200-2
	CString strSQL;
	CString strNewContentCode ;

	if (bMainTitle)
	{
		strSQL.Format("EXECUTE P_TNDR_LIB_ADDNEW_VERSION '%s'",strLibCode);
		ExecuteSQL(strSQL);
	}
	else 
	{
		strSQL.Format("EXECUTE P_TNDR_LIB_SUB_ADDNEW_VERSION '%s'",strLibCode);
		ExecuteSQL(strSQL);
	}

	// Get the new version code
	strSQL.Format("SELECT dbo.GetLastLibFullCode('%s',%d) AS RETVAL",strLibCode,bMainTitle);
	strNewContentCode = GetValueFromSQL(strSQL,"RETVAL");

	return strNewContentCode;
}

void CDocLib::EditContent(CString strTablePart)
{
	BSTR bstrPlainText= FormGetField("VWCPMS_" + strTablePart,strTablePart + "_TXT").AllocSysString();
	CString strRTFText = FormGetField("VWCPMS_" + strTablePart,strTablePart + "_RTFTXT");

	strRTFText = ShowNotepadEx(strRTFText.AllocSysString(),"Library Content",TS_RTF,0,FALSE,RGB(255,255,255),&bstrPlainText);

	FormSetField("VWCPMS_" + strTablePart,strTablePart + "_TXT",CString(bstrPlainText));
	FormSetField("VWCPMS_" + strTablePart,strTablePart + "_RTFTXT",strRTFText);
}

CString CDocLib::ShowNotepadEx (_bstr_t bstrValue,_bstr_t bstrEnCaption,enum TextStyle nStyle,int nMaxLen,BOOL bLocked,COLORREF bkColor,BSTR *bstrPlainText)
{
	_FNotepadObjPtr m_pNotepadeObj = NULL;
	if(m_pNotepadeObj == NULL) 
	{
		HRESULT hr = m_pNotepadeObj.CreateInstance(__uuidof(FNotepadObj));
		
		if(hr)
			return "";
	}
	try
	{
		if (bkColor == 0 || bkColor > 16777215)
			bkColor = RGB(255,255,255);
		
		m_pNotepadeObj->SetWindowsMessageStyle(true);
		return (char*)m_pNotepadeObj->ShowNotepadEx (bstrValue,bstrEnCaption,nStyle,nMaxLen,bLocked,bkColor,bstrPlainText);
	}
	catch(_com_error &e)
	{
		_bstr_t str_t = e.Description();
		return "";
	}
}

void CDocLib::ShowLibraryTree()
{
	CString strTemplateCode = FormGetField("VWCPMS_TOCTMPLT","TOCTMPLT_COD");

	if (!CreateToolsTree())
		return;

	m_pLibraryTree->ShowTemplateTree(strTemplateCode.AllocSysString(),0);
	FormMakeRefresh(UNKNONE);
}

bool CDocLib::CreateToolsTree()
{
	if (m_pLibraryTree != NULL)
		return true;

	CString strConnection = m_pCategory->GetConnectionString();
	
	HRESULT hr = m_pLibraryTree.CreateInstance(__uuidof(CLibraryTree));
	if (hr != 0)
	{
		AfxMessageBox("Can't Create Instance from CLibraryTree");
		return false;
	}

	m_pLibraryTree->OpenDirectConnection(strConnection.AllocSysString(),m_pCategory->GetUserID(),m_pCategory->GetUserLogin().AllocSysString(),m_pCategory->GetUserFullName().AllocSysString());
	return true;
}

bool CDocLib::CreateDocumentGenerator()
{
	if (m_pTenderDocument != NULL)
		return true;

	CString strConnection = m_pCategory->GetConnectionString();
	
	HRESULT hr = m_pTenderDocument.CreateInstance(__uuidof(CTenderDocument));
	if (hr != 0)
	{
		AfxMessageBox("Can't Create Instance from CTenderDocument");
		return false;
	}

	m_pTenderDocument->OpenDirectConnection(strConnection.AllocSysString(),m_pCategory->GetUserID(),m_pCategory->GetUserLogin().AllocSysString(),m_pCategory->GetUserFullName().AllocSysString());
	return true;
}

void CDocLib::GenerateTender(CString strTemplate,CString strTenderNo,CString strOutputFileName)
{
	if (!CreateDocumentGenerator())
		return;

	m_pTenderDocument->GenerateTender(strTemplate.AllocSysString(),strTenderNo.AllocSysString(),strOutputFileName.AllocSysString());
}

void CDocLib::GenerateContract(CString strTemplate,CString strContractNo,CString strOutputFileName)
{
	if (!CreateDocumentGenerator())
		return;

	m_pTenderDocument->GenerateContract(strTemplate.AllocSysString(),strContractNo.AllocSysString(),strOutputFileName.AllocSysString());
}

void CDocLib::ShowTenderTree(CString strTenderNo,BOOL bLocked)
{
	if (!CreateToolsTree())
		return;

	m_pLibraryTree->ShowTenderTree(strTenderNo.AllocSysString(),bLocked);
}

void CDocLib::ShowContractTree(CString strContractNo,BOOL bLocked)
{
	if (!CreateToolsTree())
		return;

	m_pLibraryTree->ShowContractTree(strContractNo.AllocSysString(),bLocked);
}