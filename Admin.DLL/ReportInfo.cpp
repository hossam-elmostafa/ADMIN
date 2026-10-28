// ReportInfo.cpp: implementation of the CReportInfo class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ADMN.h"
#include "ReportInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReportInfo::~CReportInfo()
{

}

int CReportInfo::ShowReportsInfo()
{
	CString strSQL;
	strSQL.Format("SELECT * FROM CMN_REPINFO WHERE (REPINFO_APPCODE = %d)",m_pCategory->m_lAppCode);
	ParentManage("CMN_REPINFO",true,true,true,"CMN_REPINFO",strSQL);
	return 1;
}

void CReportInfo::OnScreenReady(LPCTSTR Form_Tag)
{
	CString strFormTag(Form_Tag);
	if (strFormTag == "CMN_REPINFO")
	{
		CString strApp;
		strApp.Format("%ld",m_pCategory->m_lAppCode);
		m_pADMNPolyDb->FieldSetAttribSingle("REPINFO_APPCODE", "", -1, "", "","" , strApp, -1,"","","","","",-1,-1,"");
	}
}

long CReportInfo::ButtonClicked(LPCTSTR Caption, LPCTSTR Table_Name, LPCTSTR Master_Full_Recoed,LPCTSTR Details_Full_Recoed,LPCTSTR Field_Caption)
{
	CString strButtonKey(Caption);
	CString strFormTag(Table_Name);
	CString strFullRecord(Master_Full_Recoed);
	CString strSQL;

	strButtonKey.MakeUpper();
	strFormTag.MakeUpper();

	if (strButtonKey == "RUN_REPORT")
	{
		CString strReportTitle		= Find(strFullRecord,"REPINFO_REPORTTITLE");
		CString strReportFileName   = Find(strFullRecord,"REPINFO_REPORTFILENAME");

		strSQL.Format("SELECT REPORTSOURCE FROM REPORTS WHERE APPLICATIONCODE=%ld AND REPORTFILENAME='%s'",m_pCategory->m_lAppCode,strReportFileName);
		CString strReportFile = GetValueFromSQL(strSQL,"REPORTSOURCE");

		m_pADMNPolyDb->ReportPrint(strReportFile,strReportTitle,"","",1,FALSE,m_pCategory->GetParentHWnd());
	}
	else if (strButtonKey == "UPDATE_REPORT")
	{
		CString strReportFileName	= Find(strFullRecord,"REPINFO_REPORTFILENAME");
		CString strReportTitle		= Find(strFullRecord,"REPINFO_REPORTTITLE");
		CString strReportDesc		= Find(strFullRecord,"REPINFO_REPORTDESC");

		strSQL.Format("UPDATE REPORTS SET REPORTTITLE='%s', REPORTDESCRIPTION='%s' WHERE APPLICATIONCODE=%ld AND REPORTFILENAME='%s'",strReportTitle,strReportDesc,m_pCategory->m_lAppCode,strReportFileName);
		ExecuteSQL(strSQL);
	}
	return 1;
}