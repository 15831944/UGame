#if !defined(AFX_FINISHTIPDLG_H__A62A5677_64E2_491D_A14D_68FDA1032116__INCLUDED_)
#define AFX_FINISHTIPDLG_H__A62A5677_64E2_491D_A14D_68FDA1032116__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// finishtipdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFinishTipDlg dialog

class CFinishTipDlg : public CDialog
{
// Construction
public:
	CFinishTipDlg(CWnd* pParent = NULL);   // standard constructor
  void SetTipText(const CString& info);
  void Show(int delay = 1);

// Dialog Data
	//{{AFX_DATA(CFinishTipDlg)
	enum { IDD = IDD_JOB_FINISH_TIP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFinishTipDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFinishTipDlg)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINISHTIPDLG_H__A62A5677_64E2_491D_A14D_68FDA1032116__INCLUDED_)
