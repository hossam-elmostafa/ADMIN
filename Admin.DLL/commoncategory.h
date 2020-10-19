////CommonCategory.h
#ifndef _COMMONCATEGORY_H
#define _COMMONCATEGORY_H

class _DB;
class CCategory;

#define NEW_BUTTON				1
#define SAVE_BUTTON				2	
#define CANCEL_BUTTON			3
#define DELETE_BUTTON			4
#define NEXT_BUTTON				5
#define PREVIOUS_BUTTON			6
#define FIND_BUTTON				7
#define PRINT_BUTTON 			8
#define SORT_BUTTON				9
#define COPY_BUTTON				10
#define EXIT					11
#define SEND_REPORT_BUTTON		16
								
#define UNKNONE					-1
#define ONETOONE				1
#define ONETOMANY				2
#define BROWSABLE				3
#define ERROROPENTABLE			0
#define BASETOOLBAR				0
#define SUBTOOLBAR				1

#define NEW_BUTTONNAME			"NEW"
#define SAVE_BUTTONNAME			"SAVE"	
#define CANCEL_BUTTONNAME		"CANCEL"
#define DELETE_BUTTONNAME		"DELETE"
#define NEXT_BUTTONNAME			"NEXT"
#define PREVIOUS_BUTTONNAME		"PREVIOUS"
#define FIND_BUTTONNAME			"FIND"
#define PRINT_BUTTONNAME 		"PRINT"
#define SORT_BUTTONNAME			"SORT"
#define COPY_BUTTONNAME			"COPY"
#define EXITNAME				"EXIT"
#define COMMON_BUTTONNAME		"COMMON"
#define DETAILS_BUTTONNAME		"DETAILS"
#define SELECT_BUTTONNAME		"SELECT"
#define PASTE_BUTTONNAME		"PASTE"
#define ADVFILTER_BUTTONNAME	"FILTERSCREEN"
#define EDIT_BUTTONNAME			"EDIT"
#define SELCURRENT_BUTTONNAME	"SELECTCURRENT"
#define FILTER_BUTTONNAME		"FILTER"
#define REMFILTER_BUTTONNAME	"REMOVEFILTER"
#define EDIT_BUTTONNAME			"EDIT"

enum
{
	SCREEN1= 0,
	HO_O,
	HO_C,
	HOSUBJECTTYPE,
	HO_LINK_DOC,
	SHOWDOCUMENTLIBRARY,
	SHOWDOCUMENTTEMPLATES,
	LIBRARYSUBS
};

class CCommonCategory:public CToolsCategory
{
public:
	CCommonCategory(){m_nCurrentCard=-1;};
	CCommonCategory(CCategory *pCategory);
	virtual ~CCommonCategory();
	virtual void OnScreenReady(LPCTSTR strFormTag){return;};
	virtual void UpdateAfterBrowse(LPCTSTR Form_Tag, LPCTSTR Full_Recoed, LPCTSTR Table, LPCTSTR Return_Value,LPCTSTR Browsing_Field, LPCTSTR Criteria){};
	virtual void ConfirmToolBarButtonClicked(CString strForm_Tag,short Seleted_Tab,CString strButton_Name,CString strFullRecord,short nLoop,short Toolbar_ID){m_bCancelOperation=FALSE;};
	virtual void ConfirmToolBarButtonClickedDone(CString strForm_Tag,short Seleted_Tab,CString strButton_Name,CString strFullRecord,short nLoop,short Toolbar_ID){m_bCancelOperation=FALSE;};
	virtual void SubFieldChanged(LPCTSTR Form_Tag, LPCTSTR Field_Name, LPCTSTR old_value, LPCTSTR New_Value, LPCTSTR full_record, long Main_Position, long Details_Position, short grid_edit_mode){};
	virtual void EventSFieldChanged(LPCTSTR Form_Tag, LPCTSTR Field_Name, LPCTSTR old_value, LPCTSTR New_Value, LPCTSTR full_record, long Record_Position, short grid_edit_mode){};
	virtual void OnTreeSelected(LPCTSTR Table_Name, LPCTSTR Field_Value){};
	virtual long ButtonClicked(LPCTSTR Caption, LPCTSTR Table_Name, LPCTSTR Master_Full_Recoed,LPCTSTR Details_Full_Recoe,LPCTSTR Field_Caption){return 0;};
	virtual bool BeforeButtonClicked(LPCTSTR ButtonKey, LPCTSTR FormTag){return true;};
	virtual void AfterButtonClicked (LPCTSTR ButtonKey,LPCTSTR FormTag,long lAffectedRec){};
	virtual void MainSubReposition(CString strFormTag, long Main_Position, short Seleted_Tab,CString strSubFormTag){};
	virtual void GridRowReposition(LPCTSTR Form_Tag, short Selected_Tab, long AbsolutePosition, LPCTSTR Full_Record,LPCTSTR subForm_Tag){};
	virtual void OnBrowsableCustomButtonClicked(LPCTSTR Table, const VARIANT& Record, short CustomButtonID){};

	virtual void OnSendReport(BSTR* strTo, BSTR* strCc, BSTR* strSubject, BSTR* strBody){};
	virtual void OnAddNewBar(LPDISPATCH Bar, BOOL bActionCompleted, long UserID){};
	virtual void OnDeleteBar(LPDISPATCH Bar, BOOL bActionCompleted, long UserID){};
	virtual void OnChangeBar(LPDISPATCH OldBar, LPDISPATCH NewBar, BOOL bActionCompleted, long UserID){};
	virtual void OnUnloadPlan(BOOL bActionCompleted){};
	virtual void OnPlanChange(short nRows, LPCTSTR StartDate, LPCTSTR EndDate, long PlanStyle, BOOL bActionCompleted, long UserID){};
	virtual void OnNodeSelected(LPCTSTR TableName, LPCTSTR ReturnValue, LPCTSTR strVisablePath , LPCTSTR strHiddenPath, short nNodeLevel,long UserID,LPCTSTR strData){};
	virtual void OnNodeExpanded(LPCTSTR TableName, LPCTSTR ReturnValue, LPCTSTR strVisablePath , LPCTSTR strHiddenPath, short nNodeLevel,long UserID,LPCTSTR strData){};
	virtual void OnFindNode(LPCTSTR bstrFindItem,LPCTSTR bstrFindData){};
	
	virtual void OnNodeMenuPulled( LPCTSTR TableName, LPCTSTR ReturnValue, LPCTSTR strVisablePath, LPCTSTR strHiddenPath, short nNodeLevel, long UserID,LPCTSTR strData ){};
	virtual void OnNodeMenuItemClicked(LPCTSTR MenuID,LPCTSTR TableName, LPCTSTR ReturnValue, LPCTSTR strVisablePath , LPCTSTR strHiddenPath, short nNodeLevel,long UserID,LPCTSTR strData){};
	virtual void OnRangeNotify(LPCTSTR Form_Tag, LPCTSTR Mask1, LPCTSTR Mask2){};
	virtual void OnColDblClicked(LPCTSTR ColValue){};
	//virtual void OnNodesCheckList (_variant_t & vtNodes){};
	virtual void OnNodeDeselect (){};
	virtual void OnTreeTerminated (){};
	CString GetSegment(CString strScreenTag);
	void	SetScreenDefauls();
	void	SetCurrentPos(long lAbsolutePosition);
	void	FillListRecordSet(LPDISPATCH	pActiveRecordset);
	void	ActivateListWindow();
	void DisableSubToolBarForLockedScreens(BOOL bDelete);
	long	ExecuteSQL(CString& strSqlStatement,UINT unConnectionDB=PDBRS_LOAD_FROM_APP_DB,BOOL bIgnoreCommit = FALSE);
	void	GetScreenData(CString &strFSA,CString &strScreenCaption,CString &strReportFile,BOOL &m_bOneToMany,CString &strUniqueFields,CString &strOrderFields,int &nHelpID,CString &strKeyField,BOOL &bShowEmptyList,CString &strStatusField);
	void	WaitCursor();
	CString	GetHOEmails(CString strHOCode,CString strType);

	BOOL	AskYesNoMessage(CString &strTitle,CString &strMessage);
	UINT	CompleteParentManage();
	CString GetTrueTableName();
	void AdjustTXNBrowseInfo(CString strCallerTXN);

	BOOL	IsModalScreen(){return m_bModalScreen;};
	CString GetFormTag(){return m_strFormTag;};
	COleDateTime GetGregDate(CString &strDate);
	CString GeneratePartNumbersFromQuote();

	CString GetOrderCriteria(CString strMainTableName,CString strSubTableName);
	CString GetLinkField(){return m_strKeyField;};
	void OnScreenExit();
	void BringWindowToTop();

	ATOM IsScreenLoaded(CString strFormTag, bool bList);
	CString ListShowEx(LPCTSTR List_Tag, LPCTSTR List_Title, LPCTSTR SQL_Statement, LPCTSTR Return_Field, LPCTSTR Old_Value, BOOL MultiSelection, LPCTSTR strAttribTableName, long lHelpID);
	void	FormSetField(CString strTableName,CString Field,CString Value,int nFormType=-1);
	void	FormSetFieldEx(CString strFormTag ,CString Field,CString Value,int nFormType=-1);
	void	FormDoAction(short Form_Type, short Button_Index);
	short FormMakeRefresh(short Form_Type);
	CString FormGetField(CString strTableName,CString Field,int nFormType=-1);
	CString FormGetFieldEx(CString strFormTag ,CString Field,int nFormType=-1);
	CString GetBrowsingSQL(CString TableName, LPCTSTR WhereClause);
	void HandleActionEx(short Form_Type, BOOL Cancel, short Selected_Records);
	short TabEnableEx(LPCTSTR strSubTag, BOOL State);
	void SetCurrentLanguage(BOOL bNewValue);
	void SubMakeRefresh();
	short GetFormType();
	short FormEnableButton(short Form_Type, short ToolbarID, LPCTSTR ButtonKey, BOOL State, BOOL bForCurrTabOnly);
	void LockScreen(short Form_Type, BOOL bLockMain, BOOL bLockSubs);
	short LinkFieldsAttribSingle(LPCTSTR Link_Name, LPCTSTR Field_Name, LPCTSTR Field_Caption, short Max_Length, LPCTSTR Field_Help, LPCTSTR Field_Attrib_Rules, LPCTSTR Field_Mask, LPCTSTR Field_Default, short Field_Style, LPCTSTR Field_F_Table, 
		LPCTSTR Field_F_SQL, LPCTSTR Field_F_Field, LPCTSTR Field_Ret_Field, LPCTSTR strBrowsingArray, long ArabicHelpContextID, long EnglishHelpContextID, LPCTSTR strBrowsingHelpFields);
	short FieldSetAttribSingle(LPCTSTR Field_Name, LPCTSTR Field_Caption, short Max_Length, LPCTSTR Field_Help, LPCTSTR Field_Attrib_Rules, LPCTSTR Field_Mask, LPCTSTR Field_Default, short Field_Style, LPCTSTR Field_F_Table, LPCTSTR Field_F_SQL, 
		LPCTSTR Field_F_Field, LPCTSTR Field_Ret_Field, LPCTSTR strBrowsingArray, long ArabicHelpContextID, long EnglishHelpContextID, LPCTSTR strBrowsingHelpFields);
	CString ShowFilterScreen(LPCTSTR strTableName, LPCTSTR strCaption, LPCTSTR strTrueTableName, BOOL bSaveFilter, LPCTSTR strBaseCriteria,CString *pstrReadableCriteria = NULL);
	CString FormChangeCaption(short Form_Type, LPCTSTR strCaption);
		/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////

	CString GetSelectedRecordCriteria();
	void FindRecord(CString strCriteria);
	void UpdateTablesInfoCriteria(CString strFormTag, CString strSQL);
	CString GetTXNIndex(CString strTable,CString strRetField,CString strRefField,CString strRefValue,CString strWhereClause= "");
	CString GetUniqueFields()
	{
		return m_strUniqueFields;
	};
	CString	Find(CString strAllData,CString strField,CString strTable="");
	int GetCount(CString strTableName,CString strLinkField,CString strIndex,BOOL bString=FALSE,CString strAddSQL="");
	long GetRetVal(CString &strSQL);
	double GetRetDVal(CString &strSQL);
	CString GetTafkeetVal(CString &strSQL);
	CString FormatValueForSQL(CString strValue);
	BOOL CheckKey(CString &strTableName);
	
	//policies
	CString GetValueFromSQL(CString strSQL,CString strField);
	
	CString GetScreenCaption(){return m_strScreenCaption;}
	void ShowTXNDetails(CString strTXNType="",CString strCode="",CString strSTS="",CString strTXNSTS="");
	BOOL ValidateBeforeHandelUnCodedItem(CString strStore);

	CString GetFieldAttributes(CString &strTableName,CString &strFieldName);
	void RefreshScreen();
	void MovePolydbForm();
	long RebuildSegments(CString strFormTag, CString strSQL);

	//---START---------Manage Synchronous Changes ---------By Nehad in 15 April 2014-----------------------
	void	SetStartedTXNStatus();
	CString ReadTXNStatus();
	BOOL	IsStatusChanged();
	BOOL	ValidateOnRecordStatus();
	CString GetStatusFieldName(){return m_strStatusField;}
	CString GetTXNRes(CString strScrTitle,CString strTXN,CString strAction,bool bMultiSelection = false);
	protected:
		CString				m_strStatusVal,m_strStatusField,m_strScreenDefauls;
	//---END---------Manage Synchronous Changes ---------By Nehad in 15 April 2014-----------------------

protected:
	BOOL	Validate();
	short	GridShow(LPCTSTR title, BOOL one_to_many, BOOL AllowUpdate, BOOL AllowAdd, BOOL AllowDelete, BOOL lang, LPSTR strTableName,int nOpenState,int nHelpID);
	UINT	ParentManage(LPCTSTR strTableName,BOOL bAllowUpdate =TRUE,BOOL bAllowAddNew =TRUE,BOOL bAllowDelete =TRUE,CString strTableNameForSql = "",LPCTSTR strSelectStatement= NULL,BOOL bModal=FALSE,LPCTSTR report_file = NULL,int nMaxNoRecord =0,int nCustomButtons=0,CString strToolTips="",BOOL bIgnoreFilterScreen=FALSE);
	void	GetTablesNames(LPCTSTR strTableName,CString &strFSA,CString &strLSA,CString &strLFA,CString &strCaptTag);
	CString GetDbPath();
	BOOL	AskForRelatedTables(LPCTSTR TableName, LPCTSTR Field_name,LPCTSTR Field_Data);
	void	DeleteFromRelatedTables(CString strTableName,CString strFullRecord);
	void	SetModalScreen(BOOL bState)	{m_bModalScreen=bState;};
	CString GetPolicySettingValue(CString strSettingName);

	CString GetCurrentDate(CString &strFormat);
	void GetEmpInfoByLogin();

public:
	CString				m_strHOEmpCode;
	CString				m_strHOEmpName;
	CString				m_strDepartCode;
	CString				m_strDepartName;


	CString				m_strMenuTitle;
	BOOL				m_bCancelOperation,
						m_bSubWindowScreen,
						m_bOneToMany;
	int					m_nNumberOfUnDeletedRecords,
						m_nCurrentCard;
	static long			m_nShowPos,
						m_nStockCodingWay,		// WRONG TO BE PUT HERE
						m_nEmpSetting ;
	static CPolyDbRecordset	*m_FirstSysRecSet;

	BOOL				m_bMainSubBrowsing,
						m_bAddNewMode,
						m_bEditMode,m_bLanguage,m_bDisableFilterScreen;

	BOOL				m_bHasListWindow;
	CString				m_strComesFrom;
protected:
	bool				m_bOpenList;	
	BOOL				m_bAutoCode;
					
	CCategory			*m_pCategory;
	_DB					*m_pADMNPolyDb;
	_DB					*m_pADMNSYSPolyDb;
							
	CString				m_strBuildStatement,
						m_strFormTag;

	BOOL				m_bModalScreen;
	CString				m_strFSA,
						m_strReportFileName,
						m_strScreenCaption,
						m_strKeyField,
						m_stringTableName,
						m_strUniqueFields,
						m_strOrderFields,
						m_strTableNameForSql;

	int					m_nMaxNoRecord,
						m_nScreenHelpID;
	BOOL				m_bModal,
						m_bAllowAddNew,
						m_bAllowUpdate,
						m_bAllowDelete;
	static LPDISPATCH	m_pActiveRecordset;
};

#endif
