// ReportInfo.h: interface for the CReportInfo class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPORTINFO_H__91414D70_0770_4BC9_8396_F8DE6F8C06BC__INCLUDED_)
#define AFX_REPORTINFO_H__91414D70_0770_4BC9_8396_F8DE6F8C06BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CommonCategory.h"

class CReportInfo : public CCommonCategory  
{
public:
	CReportInfo(CCategory *pCategory):CCommonCategory(pCategory)
	{
		m_pCategory = pCategory;
	};
	virtual ~CReportInfo();

	int ShowReportsInfo();
	void OnScreenReady(LPCTSTR Form_Tag);
	long ButtonClicked(LPCTSTR Caption, LPCTSTR Table_Name, LPCTSTR Master_Full_Recoed,LPCTSTR Details_Full_Recoed,LPCTSTR Field_Caption);
};

#endif // !defined(AFX_REPORTINFO_H__91414D70_0770_4BC9_8396_F8DE6F8C06BC__INCLUDED_)
