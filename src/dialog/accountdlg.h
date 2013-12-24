#if !defined(AFX_ACCOUNTDLG_H__CF8934C6_102F_4F46_8806_7AA6FA93B216__INCLUDED_)
#define AFX_ACCOUNTDLG_H__CF8934C6_102F_4F46_8806_7AA6FA93B216__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// accountdlg.h : header file
//

class GameData;

/////////////////////////////////////////////////////////////////////////////
// CAccountDlg dialog

class CAccountDlg : public CDialog
{
  GameData *data_;
// Construction
public:
	CAccountDlg(GameData* d , CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAccountDlg)
	enum { IDD = IDD_DIALOG_ACCOUNT_INFO };
	CListCtrl	m_list_hero;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAccountDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAccountDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACCOUNTDLG_H__CF8934C6_102F_4F46_8806_7AA6FA93B216__INCLUDED_)
