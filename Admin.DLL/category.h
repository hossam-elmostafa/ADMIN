////Category.h
#ifndef _CATEGORY_H
#define _CATEGORY_H

#define	PDBRS_LOAD_FROM_APP_DB	4
#define	PDBRS_LOAD_FROM_SYS_DB	5

enum
{
	NORMAL_MODE=0,
	ADD_NEW_MODE,
	EDIT_MODE
};

#define DB_ACCESS		1
#define DB_SQLSERVER	2
#define DB_ORACLE		3
#define DB_NOTDEFINED	4
class _DB;
class CADMNObj;
class CListlistener;
class CCommonCategory;
#include "ToolsListener.h"

class CPolyDbRecordset:public CCmdTarget
{
public:
	CPolyDbRecordset(UINT unConnectionDB=PDBRS_LOAD_FROM_APP_DB);
	~CPolyDbRecordset();
	BEGIN_INTERFACE_PART_NEW(EventSink)
	long	Open(int,CString &strSql);
	BOOL	IsEOF();
	void	Close();
	void	GetFieldValue(CString strFieldName,CString &strRetValue);
	void	GetFieldValue(CString strFieldName,int &nRetValue);
	void	GetFieldValue(CString strFieldName,long &lRetValue);
	void	GetFieldValue(CString strFieldName,COleDateTime &OleDateTimeRetValue);
	void	GetFieldValue(CString strFieldName,double &dRetValue);
	void	GetFieldValue(CString strFieldName,float &fRetValue);
	void	Move(long lRows);
	void	MoveFirst();
	void	MoveNext();
	void	MoveLast();
	void	AddNew();
	void	Edit();
	void	Update();
	void	SetFieldValue(LPCTSTR lpszName, LPCTSTR lpszValue);
	BOOL	Find(long lFindType, LPCTSTR lpszFilter);
	long	GetAbsolutePosition();
	void	SetAbsolutePosition(long lNewPos);
	long	GetRecordCount();
	short	Delete();
	void	GetFullRecord(CString &strRetValue);

public:
	_DB		*m_pPolyDb;
	BOOL	m_bEOF,
			m_bDataDB;
};

class CCategory:public CCmdTarget
{
public:
	void HandleSUItemBrowseSQL();
	void SetFastSearchCriteria(CString strCriteria);
	CString GetFastSearchCriteria();
	CRect GetFormRect(){return m_rcFormRect;}
	SetFormRect(CRect rcFormRect)
	{
		m_rcFormRect=rcFormRect;
	}
	CWnd* GetParentWnd();
	CString GetDbPath();
	CCategory(CString DbName, CWnd* pParentWnd,CADMNObj *pADMNobj,_DB *pADMNSYSPolyDb);
	CCategory(CCategory*pCategory);
	void SetMyCCategory(CCommonCategory *pCommonCategory){m_pCommonCategory=pCommonCategory;};
	CCommonCategory * GetMyCCategory(){return m_pCommonCategory;};
	~CCategory();
	_DB		*GetADMNPolyDB();
	_DB		*GetADMNSYSPolyDB();
	long	GetParentHWnd();
	CString GetFirstSysDBPath();
	CADMNObj	*GetADMNObj(){return m_pADMNobj;};
	CString GetInitModule();
	BOOL IsModalPolyDb();
	CString GetScreenDefauls();
	long GetParentWndAsLong();
	void SetModalPollyDB(BOOL bStatus);
	BOOL AskForRelatedTables(LPCTSTR TableName, LPCTSTR Field_name);
	CString Find(CString strAllData,CString strField);
	void SetListLestener(CListlistener *pListlistener){		m_pListlistener=pListlistener;	};
	int		DoFunction(int nCurrentCard,CString strFunction,int nStatus=NORMAL_MODE,BOOL bModal=FALSE,CString strCriteria = "",CString strComesFrom="",CString strScreenDefaults="",CString strReturnBrowseValue="");
	void	SetPaneText(int nPos,char* pText,BOOL bState);
	BOOL	IsArabic();
	int		GetDisplayStatus();
	long	ExecuteSQL(CString &strSqlStatement,UINT unConnectionDB=PDBRS_LOAD_FROM_APP_DB,BOOL bIgnoreCommit = FALSE);
	BOOL	GetTableRecodingStatus(CString &strTableName);
	CString GetConnectionString() {return m_strConnection;};
	CString GetUserLogin();
	BOOL GetMRSRejectFlag();
	CString GetReplicateFrom();
	CString GetReplicationLocationID();
	CString GetWorkingFolder();
	CString GetUserFullName();
	BOOL IsHijri();
	CString GetTableKey(CString TableName);

	void HandleCustomButton(CCommonCategory* pCommonCategory,CString Form_Tag, CString Field_Name, CString Field_Caption, CString Master_Full_Recoed,CString Details_Full_Recoed, CString Table_Name, CString Criteria);
	CString ShowNotepad (CString strValue,CString strEnCaption,enum TextStyle nStyle,int nType,BOOL bLocked,COLORREF bkColor);
	int GetUserID(){return m_User;}
	void ValidateOnRecordStatus(CString strForm_Tag);
	void SetMenuID(int MenuID)
	{
		m_unCurMenuID = MenuID;
	}
	int GetMenuID()
	{
		return m_unCurMenuID;
	}

public:
	long	m_lAppCode;
	BOOL	m_bAddNew;
	int		m_nEngine;
	CString	m_strODBC;
	int		m_unCurMenuID;
	BEGIN_INTERFACE_PART_NEW(EventSink)
	afx_msg void OnEventSFieldChanged(LPCTSTR Form_Tag, LPCTSTR Field_Name, LPCTSTR old_value, LPCTSTR New_Value, LPCTSTR full_record, long Record_Position, short grid_edit_mode);
	afx_msg void OnEventMFieldChanged(LPCTSTR Form_Tag, LPCTSTR Field_Name, LPCTSTR old_value, LPCTSTR New_Value, LPCTSTR full_record, long Main_Position, long Details_Position, short grid_edit_mode,int EditMode_Area);
	afx_msg void SGFieldChanged(LPCTSTR Form_Tag, LPCTSTR Panel_Tag, LPCTSTR Field_Name, LPCTSTR Old_Value, LPCTSTR New_Value, LPCTSTR Full_Record, long Record_Position);
	afx_msg void OnEventBrowsingAddNewItem(LPCTSTR Form_Tag, LPCTSTR Table_Name, LPCTSTR Criteria,LPDISPATCH ListRecordset);
	afx_msg void OnBrowsingSelectedItem(LPCTSTR Form_Tag, LPCTSTR Full_Recoed, LPCTSTR Table, LPCTSTR Return_Value ,LPCTSTR pszBrowsingField , LPCTSTR Criteria,long AbsolutePosition,LPDISPATCH ListRecordset);
	afx_msg void OnBrowsingEditItemSelected(LPCTSTR Form_Tag, LPCTSTR Full_Record, LPCTSTR Table , LPCTSTR Criteria,long AbsolutePosition,LPDISPATCH ListRecordset);
	afx_msg void OnBrowsingChangePosition(LPCTSTR Form_Tag, LPCTSTR Full_Recoed, LPCTSTR Table, LPCTSTR Return_Value, LPCTSTR Criteria);
	afx_msg void OnTreeNodeSelected(LPCTSTR Table_Name, LPCTSTR Field_Value);
	afx_msg long OnCustomButtonClicked(LPCTSTR Form_Tag, LPCTSTR Field_Name, LPCTSTR Field_Caption, LPCTSTR Master_Full_Recoed,const VARIANT& Details_Full_Recoed,LPCTSTR Table_Name, LPCTSTR Criteria, long AbsolutePosition, LPDISPATCH ListRecordset);
	afx_msg void OnEventToolBarButtonClicked(LPCTSTR Button_Name, LPCTSTR Form_Tag, short Seleted_Tab, const VARIANT& Full_Record, short Toolbar_ID,LPCTSTR subForm_Tag);
	afx_msg void OnEventToolBarButtonClickedDone(LPCTSTR Button_Name, LPCTSTR Form_Tag, short Seleted_Tab, const VARIANT& Full_Record, short Toolbar_ID,LPCTSTR subForm_Tag);
	afx_msg void OnEventMainSubReposition(LPCTSTR Form_Tag, long Main_Position, short Seleted_Tab,LPCTSTR subForm_Tag);
	afx_msg void OnGridRowReposition(LPCTSTR Form_Tag, short Selected_Tab, long AbsolutePosition, LPCTSTR Full_Record,LPCTSTR subForm_Tag);
	afx_msg void OnBrowsableCustomButtonClicked(LPCTSTR Form_Tag, LPCTSTR Table, const VARIANT& Record, short CustomButtonID , LPCTSTR Criteria,LPDISPATCH ListRecordset);
	afx_msg void OnBeforeBrowseButtonClick(LPCTSTR Form_Tag,LPCTSTR Link_Tag, LPCTSTR FieldName, LPCTSTR CellContent, LPCTSTR BrowsingTable, LPCTSTR BrowsingSQL, LPCTSTR BrowsingField, LPCTSTR BrowsingRetField, LPCTSTR Full_Record);
	afx_msg void OnBrowsingToolBarButtonClicked(LPCTSTR List_Tag, LPCTSTR Button_Key, LPCTSTR Table_Name, LPCTSTR Criteria, long AbsolutePosition, const VARIANT& Record, LPDISPATCH ListRecordset , BOOL bCustomButton);
	afx_msg void OnKeyCheck(BOOL Dongle_Exist);
	afx_msg void RangeNotify(LPCTSTR Form_Tag, LPCTSTR Mask1_Text, LPCTSTR Mask2_Text);
	afx_msg void AddNewBar(LPDISPATCH Bar, BOOL bActionCompleted, long UserID);
	afx_msg void DeleteBar(LPDISPATCH Bar, BOOL bActionCompleted, long UserID);
	afx_msg void ChangeBar(LPDISPATCH OldBar, LPDISPATCH NewBar, BOOL bActionCompleted, long UserID);
	afx_msg void UnloadPlan(BOOL bActionCompleted);
	afx_msg void PlanChange(short nRows, LPCTSTR StartDate, LPCTSTR EndDate, long PlanStyle, BOOL bActionCompleted, long UserID);
	afx_msg void NodeSelected(const VARIANT& TableName, LPCTSTR ReturnValue, long UserID);
	afx_msg void RangeEnterd(LPCTSTR Form_Tag, LPCTSTR Mask1, LPCTSTR Mask2);
	afx_msg void BrowseDuplicatedValue(LPCTSTR strFormTag, LPCTSTR strFieldName, LPCTSTR strBrowsingTable, LPCTSTR strBrowsingRetField, LPCTSTR strBrowsingValue, BOOL* bShowList);
	afx_msg void OnScreenReady(LPCTSTR FormTag);
	afx_msg void SendReport(BSTR* strTo, BSTR* strCc, BSTR* strSubject, BSTR* strBody);
	afx_msg void OnReletedRecordSelected(LPCTSTR strFormTag, LPCTSTR strTableName, LPCTSTR strCriteria);

	DECLARE_EVENTSINK_MAP()

protected:
	void AdjustRelatedTables(CString strTag,CString strField_Name,CString strOld_value, CString strNew_Value, short grid_edit_mode);

protected:	
	CPolyDbRecordset m_DaoRecSet;
	CWnd* 	m_pParentWnd;
	CString	m_strDbPath,
			m_strConnection,
			m_strSystemPath;
	_DB		*m_pADMNPolyDb;
	_DB		*m_pADMNSYSPolyDb;
	CADMNObj *m_pADMNobj;
	CListlistener *m_pListlistener;
	CCommonCategory	*m_pCommonCategory;
protected:
	int		m_User;
	CRect m_rcFormRect;

public:
	CString	m_strDBName;
	CString	m_strDBUser;
	CString	m_strServerName;
	CToolsListener		*m_pToolsListener;
	
};
#endif
