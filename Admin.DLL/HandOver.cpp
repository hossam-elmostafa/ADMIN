#include "stdafx.h"
#include "HandOver.h"
#include "ADMNapp.h"
#include "ADMN.h"
#include "ADMNobj.h"

CHandOver::~CHandOver()
{
}

void CHandOver::SubjectType()
{
	MovePolydbForm();
	m_nCurrentCard=HOSUBJECTTYPE;
	ParentManage("CMN_HOSUBJTYPE");
}

void CHandOver::OpenedHandOver()
{
	MovePolydbForm();
	m_nCurrentCard=HO_O;

	if (m_strHOEmpCode == "")
	{
		if(!m_bLanguage)
			MessageBox(NULL,"You are not able to open this screen.\n\nPlease contact the system administrator to map your account in Employees screen","Admin Module",MB_ICONEXCLAMATION |MB_TASKMODAL);
		else
			MessageBox(NULL,"·« Ì„ﬂ‰ﬂ › Õ Â–Â «·‘«‘….\n\nÌ—ÃÏ «·« ’«· »„”ƒÊ· «·‰Ÿ«„ · ⁄ÌÌ‰ Õ”«»ﬂ ›Ì ‘«‘… «·„ÊŸ›Ì‰","Admin Module",MB_ICONEXCLAMATION |MB_TASKMODAL);

		return;
	}

	CString strSQL;
	strSQL.Format("SELECT * FROM VWCMN_HO WHERE (HO_APPCODE = %d AND HO_STATUS = 'O' AND HO_HOEMP = '%s') ORDER BY HO_FROMDATE DESC",m_pCategory->m_lAppCode,m_strHOEmpCode);

	ParentManage("HO_O",true,true,true,"VWCMN_HO",strSQL);
}

void CHandOver::ClosedHandOver()
{
	MovePolydbForm();
	m_nCurrentCard=HO_C;

	CString strSQL;

	strSQL.Format("SELECT * FROM VWCMN_HO WHERE (HO_APPCODE = %d AND HO_STATUS = 'C' AND '%s' IN (SELECT HOAUTHORITY_EMP FROM CMN_HOAUTHORITY WHERE HOAUTHORITY_HOCODE=HO_CODE)) ORDER BY HO_FROMDATE DESC",m_pCategory->m_lAppCode,m_strHOEmpCode);

	ParentManage("HO_C",false,false,false,"VWCMN_HO",strSQL);
}

void CHandOver::ShowHandOverLinkedDocument(CString strSQL,CString strComesFrom,CString strScreenDefaults)
{
	MovePolydbForm();
	m_nCurrentCard=HO_LINK_DOC;

	bool bFullAccess = true;
	
	if (strComesFrom == "")
		strComesFrom = Find(strScreenDefaults,"COMES_FROM");
	
	if (strComesFrom == "HO_C")
		bFullAccess = false;

	m_pCategory->GetADMNObj()->SetHOLinkedDocScreenDefauls(strScreenDefaults);
	m_pCategory->GetADMNObj()->SetScreenDefauls(strScreenDefaults);

	ParentManage("CMN_HOLINKDOC",bFullAccess,bFullAccess,bFullAccess,"CMN_HOLINKDOC",strSQL,true);
}	

void CHandOver::OnScreenReady(LPCTSTR Form_Tag)
{
	CString strFormTag(Form_Tag);
	if (strFormTag == "HO_O")
	{
		// Set the logged in user in HOEmp 
        m_pADMNPolyDb->FieldSetAttribSingle("HO_HOEMP", "", -1, "", "","" , m_strHOEmpCode, -1,"","","","","",-1,-1,"");
		m_pADMNPolyDb->FieldSetAttribSingle("HOEMP_NAME", "", -1, "", "","" , m_strHOEmpName, -1,"","","","","",-1,-1,"");

        m_pADMNPolyDb->FieldSetAttribSingle("HO_DEPART", "", -1, "", "","" , m_strDepartCode, -1,"","","","","",-1,-1,"");
		m_pADMNPolyDb->FieldSetAttribSingle("DEPART_DESC", "", -1, "", "","" , m_strDepartName, -1,"","","","","",-1,-1,"");
	}
}

long CHandOver::ButtonClicked(LPCTSTR Caption, LPCTSTR Table_Name, LPCTSTR Master_Full_Recoed,LPCTSTR Details_Full_Recoed,LPCTSTR Field_Caption)
{
	CString strButtonKey(Caption);
	CString strFormTag(Table_Name);
	CString strSQL;
	CString strSubFullRecord(Details_Full_Recoed);

	strButtonKey.MakeUpper();
	strFormTag.MakeUpper();

	if (strButtonKey == "CLOSE_HO")
	{
		CString strMessage;
		if(!m_bLanguage)
			strMessage = "Are you sure";
		else
			strMessage = "Â· √‰  „ √ﬂœø";


		if (MessageBox(NULL,strMessage,"Admin Module",MB_YESNOCANCEL | MB_ICONQUESTION | MB_TASKMODAL) == IDYES)
		{
			if(!m_bLanguage)
				strMessage = "Do you want to send HO report to the defined e-mails";
			else
				strMessage = "Â·  —Ìœ ≈—”«·  ﬁ—Ì— ≈·Ï —”«∆· «·»—Ìœ «·≈·ﬂ —Ê‰Ì «·„Õœœ…";
			if (MessageBox(NULL,strMessage,"Admin Module",MB_YESNO | MB_ICONQUESTION | MB_TASKMODAL) == IDYES)
				m_pADMNPolyDb->FormDoAction(UNKNONE, SEND_REPORT_BUTTON);
            
            m_pADMNPolyDb->FormSetField("VWCMN_HO", "HO_STATUS", "C", UNKNONE);
            m_pADMNPolyDb->FormDoAction(UNKNONE, SAVE_BUTTON);;
            m_pADMNPolyDb->FormMakeRefresh(UNKNONE);
        }	
	}

	else if (strButtonKey == "PREPARE_HO_PREV")
	{
		CString strTOEmpCode = m_pADMNPolyDb->FormGetField("VWCMN_HO", "HO_TOEMP", UNKNONE);	
		strSQL.Format("SELECT * FROM VWCMN_HO WHERE HO_CODE IN (SELECT TOP 1 HO_CODE FROM CMN_HO WHERE HO_STATUS='C' AND HO_HOEMP='%s' AND '%s' IN (HO_TOEMP,HO_BKEMP) ORDER BY HO_FROMDATE DESC)",strTOEmpCode,m_strHOEmpCode);
		CString strBaseHO = ListShowEx("HO_C","Select Hand Over",strSQL,"HO_CODE","",true,"HO_C",0);
		
		PrepareHO(strBaseHO);
	}

	else if (strButtonKey == "PREPARE_HO_ANY")
	{
		strSQL = "SELECT * FROM VWCMN_HO WHERE HO_STATUS='C'";
		CString strBaseHO = ListShowEx("HO_C","Select Hand Over",strSQL,"HO_CODE","",true,"HO_C",0);
		
		PrepareHO(strBaseHO);
	}

	else if (strButtonKey == "ACTV_LINK_DOC")
	{
        CString strHOCode = m_pADMNPolyDb->FormGetField("VWCMN_HO", "HO_CODE", ONETOMANY);
        CString strActivityCode = m_pADMNPolyDb->FormGetField("CMN_HOACTV", "HOACTV_CODE", ONETOMANY);
        CString strCriterea;

		if (strActivityCode == "")
			return 0;

        strCriterea.Format("WHERE (HOLINKDOC_HOCODE='%s' AND HOLINKDOC_ACTVCODE='%s')",strHOCode,strActivityCode);
        
		CString strDefaults="";

		strDefaults.Format("COMES_FROM|%s|HOLINKDOC_HOCODE|%s|HOLINKDOC_ACTVCODE|%s|",strFormTag,strHOCode,strActivityCode);
		
		m_pCategory->DoFunction(0,"CMN_HOLINKDOC",NORMAL_MODE,TRUE,strCriterea,strFormTag,strDefaults);
	}

	else if (strButtonKey == "CLOSE_HO_ACTV")
	{
		if (Find(strSubFullRecord,"HOACTV_COMPLETEDATE") == "")
		{
			if(!m_bLanguage)
				MessageBox(NULL,"Please enter Completion Date","Admin Module",MB_OK | MB_ICONQUESTION | MB_TASKMODAL);
			else
				MessageBox(NULL,"«·—Ã«¡ ≈œŒ«·  «—ÌŒ «·≈‰ Â«¡","Admin Module",MB_OK | MB_ICONQUESTION | MB_TASKMODAL);

            return 0;
        }
		CString strHOCode = Find(strSubFullRecord,"HOACTV_HOCODE");
		CString strActivityCode = Find(strSubFullRecord,"HOACTV_CODE");
		CString strSQL;

		if (strActivityCode == "")
			return 0;

		strSQL.Format("UPDATE CMN_HOACTV SET HOACTV_STATUS='C',HOACTV_COMPLETEPERC=100 WHERE HOACTV_HOCODE='%s' AND HOACTV_CODE='%s'",strHOCode,strActivityCode);
		ExecuteSQL(strSQL);
        m_pADMNPolyDb->SubMakeRefresh();		
	}

	else if (strButtonKey == "REOPEN_HO_ACTV")
	{
		CString strHOCode = Find(strSubFullRecord,"HOACTV_HOCODE");
		CString strActivityCode = Find(strSubFullRecord,"HOACTV_CODE");
		CString strSQL;

		if (strActivityCode == "")
			return 0;

		strSQL.Format("UPDATE CMN_HOACTV SET HOACTV_STATUS='O' WHERE HOACTV_HOCODE='%s' AND HOACTV_CODE='%s'",strHOCode,strActivityCode);
		ExecuteSQL(strSQL);
        m_pADMNPolyDb->SubMakeRefresh();
	}

	return 0;
}

void CHandOver::OnSendReport(BSTR* strTo, BSTR* strCc, BSTR* strSubject, BSTR* strBody)
{
	// Sent HO to the concerned persons
	if (m_strFormTag == "HO_O" || m_strFormTag == "HO_C")
	{
		CString strHOCode = m_pADMNPolyDb->FormGetField("VWCMN_HO", "HO_CODE", UNKNONE);
		
		*strTo = GetHOEmails(strHOCode,"TO").AllocSysString();
		*strCc = GetHOEmails(strHOCode,"CC").AllocSysString();
	}
}

void CHandOver::PrepareHO(CString strBaseHO)
{
	if (strBaseHO == "")
		return;

	CString strMessage;
	if(!m_bLanguage)
		strMessage = "All records under this Hand Over record will be deleted.\n\nAre you sure?";
	else
		strMessage = "”Ì „ Õ–› ﬂ«›… «·”Ã·«  «·„ÊÃÊœ… ÷„‰ ”Ã· «· ”·Ì„ Â–«. \ n \ n Â· √‰  „ √ﬂœø";

	if (MessageBox(NULL,strMessage,"Admin Module",MB_YESNOCANCEL | MB_ICONQUESTION | MB_TASKMODAL) != IDYES)
		return;
	
	CString strSQL;
	CString strHOCode = m_pADMNPolyDb->FormGetField("VWCMN_HO", "HO_CODE", UNKNONE);

	strSQL.Format("PrepareHO '%s','%s'",strBaseHO,strHOCode);
	ExecuteSQL(strSQL);
	m_pADMNPolyDb->FormMakeRefresh(UNKNONE);
}

void CHandOver::ConfirmToolBarButtonClicked(CString strForm_Tag,short Seleted_Tab,CString strButton_Name,CString strFullRecord,short nLoop,short Toolbar_ID)
{
	m_bCancelOperation=FALSE;

	if (strForm_Tag == "HO_O" && strButton_Name == "SAVE")
	{
		// First save
		if (m_pADMNPolyDb->FormGetField("VWCMN_HO", "HO_DAYSCOUNT", UNKNONE) == "") 
		{
			if(!m_bLanguage)
				MessageBox(NULL,"You should prepare this record before adding new activities","Admin Module",MB_ICONEXCLAMATION |MB_TASKMODAL);
			else
				MessageBox(NULL,"ÌÃ» ⁄·Ìﬂ  Õ÷Ì— Â–« «·”Ã· ﬁ»· ≈÷«›… √‰‘ÿ… ÃœÌœ…","Admin Module",MB_ICONEXCLAMATION |MB_TASKMODAL);
		}
	}

}