// findforgotpassdlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\XGame\xgame.h"
#include "findforgotpassdlg.h"
#include "GameFileReader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindForgotPassDlg dialog


CFindForgotPassDlg::CFindForgotPassDlg(AccountManager* acc , CWnd* pParent /*=NULL*/)
	: CDialog(CFindForgotPassDlg::IDD, pParent) , account_(acc)
{
	//{{AFX_DATA_INIT(CFindForgotPassDlg)
	m_account_name = _T("");
	m_star_name = _T("");
	//}}AFX_DATA_INIT
}


void CFindForgotPassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFindForgotPassDlg)
	DDX_Text(pDX, IDC_EDIT_ACCOUNTNAME, m_account_name);
	DDX_Text(pDX, IDC_EDIT_STAR_NAME, m_star_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFindForgotPassDlg, CDialog)
	//{{AFX_MSG_MAP(CFindForgotPassDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFindForgotPassDlg message handlers

BOOL CFindForgotPassDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
  UpdateData(FALSE);
  GetDlgItem(IDC_EDIT_STAR_NAME)->SetFocus();
	
	// TODO: Add extra initialization here
	
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFindForgotPassDlg::OnOK() 
{
  UpdateData(TRUE);
  CString password;
  if(account_->CanGetPassword(m_account_name , m_star_name , password))
  {
    CString info;
    info.Format("�����˻�����Ϊ %s �����ø������½" , password);
    ::MessageBox(NULL , info , "�ɹ�" , MB_OK | MB_ICONINFORMATION );
  }
  else
  {
    ::MessageBox(NULL , "���ṩ���������Ʋ����ϸ��˻���¼��" , "����" , MB_OK | MB_ICONWARNING );
    GetDlgItem(IDC_EDIT_STAR_NAME)->SetFocus();
  }
}
