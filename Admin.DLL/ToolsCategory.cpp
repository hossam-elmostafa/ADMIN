
#include"stdafx.h"
#include "ADMN.h"
#include "ADMNobj.h"
#include "Listlisten.h"
#include "ADMNapp.h"
#include "IO.h"
//#define _PDBTRACE 

#ifdef	_DEBUG
#define	new	DEBUG_NEW
#endif

#define	MAIN_NEW_NONEMPTY_RECORD_NAVIGATE	-1
#define	MAIN_NEW_RECORD						0
#define	GRID_FREE_NAVIGATE					0
#define	GRID_NEW_EMPTY_RECORD_NAVIGATE		1
#define	GRID_NEW_NONEMPTY_RECORD_NAVIGATE	2
#define	SILENTPOLYDBRECORDSET				4


BEGIN_EVENTSINK_MAP(CToolsCategory, CCmdTarget)
    //{{AFX_EVENTSINK_MAP(CAboutDlg)
	ON_EVENT(CToolsCategory, -1,1,AddNewBar,VTS_DISPATCH VTS_BOOL VTS_I4)
	ON_EVENT(CToolsCategory, -1,2,DeleteBar,VTS_DISPATCH VTS_BOOL VTS_I4)
	ON_EVENT(CToolsCategory, -1,3,ChangeBar,VTS_DISPATCH VTS_DISPATCH VTS_BOOL VTS_I4)
	ON_EVENT(CToolsCategory, -1,4,UnloadPlan,VTS_BOOL)
	ON_EVENT(CToolsCategory, -1,5,PlanChange,VTS_I2 VTS_BSTR VTS_BSTR VTS_I4 VTS_BOOL VTS_I4)
	ON_EVENT(CToolsCategory, -1,6,NodeSelected,VTS_VARIANT VTS_BSTR VTS_I4)
	ON_EVENT(CToolsCategory, -1,7,RangeEnterd,VTS_BSTR VTS_BSTR VTS_BSTR)
	
		
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

INTERFACE_IMPL(CToolsCategory,EventSink)


CToolsCategory::CToolsCategory(CString DbPath, CWnd* pParentWnd,CADMNObj *pADMNobj,_DB *pADMNSYSPolyDb)
{
	m_pCommonCategory=NULL;
	m_pListlistener=NULL;
	m_pParentWnd=pParentWnd;
	m_pTools = new _Tools;
	m_pObject=m_pTools->m_lpDispatch;
	AFX_MANAGE_STATE(AfxGetStaticModuleState())
	EstablishConnectionWithEventSrc();
}


CToolsCategory::CToolsCategory(CToolsCategory* pToolsCategory)
{
	m_pCommonCategory=NULL;
	m_pListlistener=NULL;
	m_pParentWnd=pToolsCategory->m_pParentWnd;
	m_strDbPath=pToolsCategory->m_strDbPath;	
	m_pADMNobj=pToolsCategory->m_pADMNobj;
	m_strSystemPath=pToolsCategory->m_strSystemPath;

	EstablishConnectionWithEventSrc();
}

CToolsCategory::~CToolsCategory()
{
	EndConnectionWithEventSrc();
}


long CToolsCategory::GetParentHWnd()
{
	HWND hWnd=m_pParentWnd->GetTopWindow()->GetSafeHwnd();
	return (long)(DWORD)hWnd;
}

	
void CToolsCategory::RangeNotify(LPCTSTR Form_Tag, LPCTSTR Mask1_Text, LPCTSTR Mask2_Text)
{
}
void CToolsCategory::AddNewBar(LPDISPATCH Bar, BOOL bActionCompleted, long UserID)
{

}
void CToolsCategory::DeleteBar(LPDISPATCH Bar, BOOL bActionCompleted, long UserID)
{

}
void CToolsCategory::ChangeBar(LPDISPATCH OldBar, LPDISPATCH NewBar, BOOL bActionCompleted, long UserID)
{

}

void CToolsCategory::UnloadPlan(BOOL bActionCompleted)
{

}

void CToolsCategory::PlanChange(short nRows, LPCTSTR StartDate, LPCTSTR EndDate, long PlanStyle, BOOL bActionCompleted, long UserID)
{

}

void CToolsCategory::NodeSelected(const VARIANT& TableName, LPCTSTR ReturnValue, long UserID)
{

}

void CToolsCategory::RangeEnterd(LPCTSTR Form_Tag, LPCTSTR Mask1, LPCTSTR Mask2)
{

}

CWnd* CToolsCategory::GetParentWnd()
{
	return m_pParentWnd;
}

