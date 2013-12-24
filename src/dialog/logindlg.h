#if !defined(AFX_LOGINDLG_H__23CB389D_5F38_42DF_90DA_C831A6BE5D52__INCLUDED_)
#define AFX_LOGINDLG_H__23CB389D_5F38_42DF_90DA_C831A6BE5D52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// logindlg.h : header file
//

#include "GameFileReader.h"
#include "MFECToolTip.h"

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog

class CLoginDlg : public CDialog
{
private:
  AccountManager* account_;
  CMFECToolTip m_toolTip;
public:
	CLoginDlg(AccountManager* accountMgr , CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLoginDlg)
	enum { IDD = IDD_LOGIN_DIALOG };
	CComboBox	m_accounts;
	CString	m_password;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoginDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoginDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBtnNewcount();
	afx_msg void OnBtnForgetPassword();
	afx_msg void OnBtnDeleteAccount();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGINDLG_H__23CB389D_5F38_42DF_90DA_C831A6BE5D52__INCLUDED_)
