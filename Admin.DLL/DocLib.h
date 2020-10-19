// DocLib.h: interface for the CDocLib class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOCLIB_H__BC761CD1_FF5A_490B_A8AC_B6BBBF2F84AE__INCLUDED_)
#define AFX_DOCLIB_H__BC761CD1_FF5A_490B_A8AC_B6BBBF2F84AE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDocLib:public CCommonCategory
{
public:
	void DefineUserDefinedChecks();
	CDocLib(CCategory *pCategory):CCommonCategory(pCategory)
	{
		m_pCategory = pCategory;
		m_pLibraryTree = NULL;
		m_pTenderDocument=NULL;
	};
	~CDocLib(){};

//	void OnScreenReady(LPCTSTR strFormTag){};
	long ButtonClicked(LPCTSTR Caption, LPCTSTR Table_Name, LPCTSTR Master_Full_Recoed,LPCTSTR Details_Full_Recoed,LPCTSTR Field_Caption);
//	void ConfirmToolBarButtonClicked(CString strForm_Tag,short Seleted_Tab,CString strButton_Name,CString strFullRecord,short nLoop,short Toolbar_ID){};

	void ShowDocumentLibrary();
	void ShowDocumentTemplates();
	void ShowLibrarySubs(CString strSQL,CString strComesFrom,CString strScreenDefaults);

	void ShowLibraryTree();
	bool CreateToolsTree();
	bool CreateDocumentGenerator();
	void EditContent(CString strTablePart);
	CString ShowNotepadEx (_bstr_t bstrValue,_bstr_t bstrEnCaption,enum TextStyle nStyle,int nMaxLen,BOOL bLocked,COLORREF bkColor,BSTR *bstrPlainText);
	CString AddNewVersion(CString strLibCode,bool bMainTitle);

	void GenerateTender(CString strTemplate,CString strTenderNo,CString strOutputFileName);
	void GenerateContract(CString strTemplate,CString strContractNo,CString strOutputFileName);
	void ShowTenderTree(CString strTenderNo,BOOL bLocked);
	void ShowContractTree(CString strContractNo,BOOL bLocked);

private:
	_CLibraryTreePtr	m_pLibraryTree;
	_CTenderDocumentPtr	m_pTenderDocument;
};

#endif // !defined(AFX_DOCLIB_H__BC761CD1_FF5A_490B_A8AC_B6BBBF2F84AE__INCLUDED_)
