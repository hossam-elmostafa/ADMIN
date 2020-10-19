#if !defined(AFX_WAITWND_H__571CB9C0_D691_11D5_BF0A_0050BA39D2DC__INCLUDED_)
#define AFX_WAITWND_H__571CB9C0_D691_11D5_BF0A_0050BA39D2DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WaitWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWaitWnd window

class CWaitWnd : public CWnd
{
// Construction
public:
	CWaitWnd();
	
// Attributes
public:
	void ShowMessage(CString strText,BOOL bShow);
	BOOL CreateMessage();
	void DestroyMessage();
// Operations
public:
	CString m_strMessage;
	BOOL m_bShow;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaitWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWaitWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWaitWnd)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAITWND_H__571CB9C0_D691_11D5_BF0A_0050BA39D2DC__INCLUDED_)
