#ifndef _CHANDOVER_H
#define _CHANDOVER_H

class CHandOver:public CCommonCategory
{
public:
	void DefineUserDefinedChecks();
	CHandOver(CCategory *pCategory):CCommonCategory(pCategory)
	{
		m_pCategory = pCategory;
		GetEmpInfoByLogin();

	};
	~CHandOver();

	void OnScreenReady(LPCTSTR strFormTag);
	long ButtonClicked(LPCTSTR Caption, LPCTSTR Table_Name, LPCTSTR Master_Full_Recoed,LPCTSTR Details_Full_Recoed,LPCTSTR Field_Caption);
	void OnSendReport(BSTR* strTo, BSTR* strCc, BSTR* strSubject, BSTR* strBody);
	void ConfirmToolBarButtonClicked(CString strForm_Tag,short Seleted_Tab,CString strButton_Name,CString strFullRecord,short nLoop,short Toolbar_ID);

	void SubjectType();
	void OpenedHandOver();
	void ClosedHandOver();
	void ShowHandOverLinkedDocument(CString strSQL,CString strComesFrom,CString strScreenDefaults);
	void PrepareHO(CString strBaseHO);
};
#endif
