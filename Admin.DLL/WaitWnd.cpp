// WaitWnd.cpp : implementation file
//

#include "stdafx.h"
#include "WaitWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWaitWnd::CWaitWnd()
{
	m_bShow = false;
}

BEGIN_MESSAGE_MAP(CWaitWnd, CWnd)
	//{{AFX_MSG_MAP(CWaitWnd)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CWaitWnd::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	if(m_bShow)
	{
		CRect rect;
		CBrush brush(RGB(192,192,192));
		GetClientRect(&rect); 
		dc.FillRect(rect,&brush);
		dc.SetBkMode(TRANSPARENT);
		dc.TextOut(10,20,m_strMessage); 
		brush.DeleteObject(); 	
	}
}
void CWaitWnd::ShowMessage(CString strText,BOOL bShow)
{
	if(bShow)
	{
		CreateMessage();
		m_strMessage = strText;
		m_bShow = bShow;
		Invalidate();
		UpdateWindow();
	}
	else
	{
		DestroyMessage();
	}
}
BOOL CWaitWnd::CreateMessage()
{
	DWORD dwStyle = WS_VISIBLE|WS_POPUP;
	WNDCLASS WndClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = NULL;
	WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
	WndClass.hInstance   = AfxGetInstanceHandle();
	CBrush brush(RGB(0,255,255));
	WndClass.hbrBackground  = (HBRUSH)brush.m_hObject;
	WndClass.hIcon = LoadIcon(NULL, MAKEINTRESOURCE(129));
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.lpszClassName = "";
	CString strClassName = ::AfxRegisterWndClass(WndClass.style,WndClass.hCursor,WndClass.hbrBackground,WndClass.hIcon); 
	BOOL b = CreateEx(WS_EX_TOPMOST,strClassName,NULL,dwStyle,CRect(130,220,600,280),NULL,0,NULL);
	return b;
}
void CWaitWnd::DestroyMessage()
{
	delete this;
}