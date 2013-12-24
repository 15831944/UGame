#if !defined(AFX_NEWACCOUNTDLG_H__851899C3_4AE3_4375_860A_ED8FEE9CE0F3__INCLUDED_)
#define AFX_NEWACCOUNTDLG_H__851899C3_4AE3_4375_860A_ED8FEE9CE0F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// newaccountdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewAccountDlg dialog
class AccountManager;

class CNewAccountDlg : public CDialog
{
private:
  AccountManager* account_;

public:
	CNewAccountDlg(AccountManager* acc , CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewAccountDlg)
	enum { IDD = IDD_DIALOG_NEWACCOUNT };
	CString	m_accout_name;
	CString	m_password;
	CString	m_password_again;
	CString	m_star_name;
	int		m_computer_type;
	UINT	m_game_speed;
	int		m_bCOMAI;
	CString	m_npc_name;
	BOOL	m_computer_attack_me;
	BOOL	m_bNotResUp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewAccountDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewAccountDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
  BOOL IsValidText(const CString& buff)
  { 
    if(buff.IsEmpty())
      return FALSE;

    for(int i = 0 ; i < buff.GetLength() ; ++i)
    {
      char c = buff[i];
      BOOL f =
        c >= 'a' && c <= 'z' ||  //a~z
        c >= 'A' && c <= 'Z' ||  //A~Z
        c == '_'             ||  //_
        c >= '0' && c <= '9' ;   //0~9      
      
      //invalid char
      if(!f)
      {
        return FALSE;
      }
    }
    return TRUE;
  };
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWACCOUNTDLG_H__851899C3_4AE3_4375_860A_ED8FEE9CE0F3__INCLUDED_)
