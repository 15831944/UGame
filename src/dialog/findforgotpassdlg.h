#if !defined(AFX_FINDFORGOTPASSDLG_H__3CFAEA83_95B8_48D7_B510_4B3F216C5BCF__INCLUDED_)
#define AFX_FINDFORGOTPASSDLG_H__3CFAEA83_95B8_48D7_B510_4B3F216C5BCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// findforgotpassdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFindForgotPassDlg dialog

class AccountManager;

class CFindForgotPassDlg : public CDialog
{
private:
  AccountManager* account_;

public:
	CFindForgotPassDlg(AccountManager* acc , CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFindForgotPassDlg)
	enum { IDD = IDD_DIALOG_FIND_FORGETPASSWORD };
	CString	m_account_name;
	CString	m_star_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindForgotPassDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFindForgotPassDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDFORGOTPASSDLG_H__3CFAEA83_95B8_48D7_B510_4B3F216C5BCF__INCLUDED_)
