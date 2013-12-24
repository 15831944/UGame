// logindlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\XGame\XGame.h"
#include "logindlg.h"
#include "newaccountdlg.h"
#include "findforgotpassdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg dialog


CLoginDlg::CLoginDlg(AccountManager* accountMgr , CWnd* pParent /*=NULL*/)
: CDialog(CLoginDlg::IDD, pParent) , account_(accountMgr)
{
  //{{AFX_DATA_INIT(CLoginDlg)
  m_password = _T("");
  //}}AFX_DATA_INIT
  assert(account_ != 0);
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CLoginDlg)
  DDX_Control(pDX, IDC_COMBO1, m_accounts);
  DDX_Text(pDX, IDC_EDIT2, m_password);
  //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
//{{AFX_MSG_MAP(CLoginDlg)
	ON_BN_CLICKED(IDC_BTN_NEWCOUNT, OnBtnNewcount)
	ON_BN_CLICKED(IDC_BTN_FORGET_PASSWORD, OnBtnForgetPassword)
	ON_BN_CLICKED(IDC_BTN_DELETE_ACCOUNT, OnBtnDeleteAccount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers

BOOL CLoginDlg::OnInitDialog() 
{
  CDialog::OnInitDialog();
  for(int i = 0 ; i < account_->AccountSize() ; ++i)
  {
    m_accounts.AddString(account_->AccountName(i));
  }
  if(account_->AccountSize() > 0)
    m_accounts.SetCurSel(0);
  else
  {
    GetDlgItem(IDC_BTN_FORGET_PASSWORD)->EnableWindow(FALSE);
    GetDlgItem(IDOK)->EnableWindow(FALSE);
    GetDlgItem(IDC_BTN_DELETE_ACCOUNT)->EnableWindow(FALSE);
  }  
  GetDlgItem(IDC_EDIT2)->SetFocus();

  m_toolTip.Create(this);
	CStringArray straInfo;
	straInfo.RemoveAll();
	straInfo.Add("ÕÒ»ØÍü¼ÇµÄÃÜÂë");
	m_toolTip.AddControlInfo(IDC_BTN_FORGET_PASSWORD , straInfo );

  straInfo.RemoveAll();
	straInfo.Add("É¾³ýÑ¡ÖÐµÄÕÊºÅ");
	m_toolTip.AddControlInfo(IDC_BTN_DELETE_ACCOUNT , straInfo );

  return FALSE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CLoginDlg::OnOK() 
{
  UpdateData(TRUE);
  CString name;
  int index = 0;
  m_accounts.GetWindowText(name);
  if(account_->CheckValidAccount(name , m_password , index)){
    account_->Login(index);
    CDialog::OnOK();
    return;
  }	
  m_password = "";
  UpdateData(FALSE);
  GetDlgItem(IDC_EDIT2)->SetFocus();
  MessageBox("ÃÜÂë´íÎó£¬ÇëÖØÐÂÊäÈëÃÜÂë" , "ÃÜÂë´íÎó" , MB_OK | MB_ICONERROR);
}

void CLoginDlg::OnBtnNewcount() 
{
  CNewAccountDlg dlg(account_);
  if(IDOK == dlg.DoModal())
  {
    CWaitCursor waitor;
    if(account_->RegisterAccount(dlg.m_accout_name , dlg.m_password , dlg.m_star_name , dlg.m_computer_type , dlg.m_game_speed , dlg.m_bCOMAI , dlg.m_npc_name , dlg.m_computer_attack_me , dlg.m_bNotResUp) == false)
    {
      AfxMessageBox("×¢²áÐÂÕÊºÅÊ§°Ü£¬Ô­ÒòÎ´Öª£¡");
      return;
    }
    m_accounts.ResetContent();
    int pos = 0;
    for(int i = 0 ; i < account_->AccountSize() ; ++i)
    {
      m_accounts.AddString(account_->AccountName(i));
      if(account_->AccountName(i) == dlg.m_accout_name)
        pos = i;
    }
    if(account_->AccountSize() > 0)
    {
      GetDlgItem(IDOK)->EnableWindow(TRUE);
      GetDlgItem(IDC_BTN_FORGET_PASSWORD)->EnableWindow(TRUE);
      GetDlgItem(IDC_BTN_DELETE_ACCOUNT)->EnableWindow(TRUE);
      m_accounts.SetCurSel(pos);
      UpdateData(FALSE);
    }
    else
    {
      GetDlgItem(IDOK)->EnableWindow(FALSE);
      GetDlgItem(IDC_BTN_DELETE_ACCOUNT)->EnableWindow(FALSE);
      GetDlgItem(IDC_BTN_FORGET_PASSWORD)->EnableWindow(FALSE);
    }  
    GetDlgItem(IDC_EDIT2)->SetFocus();    
  }	
}

void CLoginDlg::OnBtnForgetPassword() 
{
  CString name;
  m_accounts.GetWindowText(name);
  if(name.IsEmpty())
    return;
  CFindForgotPassDlg dlg(account_);
  dlg.m_account_name = name;
  dlg.DoModal();
}

BOOL CLoginDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_MOUSEMOVE)
	{
		POINT pt = pMsg->pt;
		ScreenToClient(&pt);
		m_toolTip.ShowToolTip((CPoint)pt);
	}	
	return CDialog::PreTranslateMessage(pMsg);
}

void CLoginDlg::OnBtnDeleteAccount() 
{
  CString name;
  m_accounts.GetWindowText(name);
  if(name.IsEmpty())
    return;	
  CString info;
  info.Format("ÄúÈ·¶¨ÒªÉ¾³ýÕÊºÅ %s Âð£¿" , name);
  if(MessageBox(info , "¾¯¸æ" , MB_YESNO | MB_ICONWARNING) == IDNO)
  {
    return;
  }

  CWaitCursor waitor;
  if(account_->DeleteAccount(name) == false)
  {
    AfxMessageBox("É¾³ýÕÊºÅÊ§°Ü£¬Ô­ÒòÎ´Öª£¡");
    return;
  }
  m_accounts.ResetContent();
  for(int i = 0 ; i < account_->AccountSize() ; ++i)
  {
    m_accounts.AddString(account_->AccountName(i));
  }
  if(account_->AccountSize() > 0)
  {
    GetDlgItem(IDOK)->EnableWindow(TRUE);
    GetDlgItem(IDC_BTN_FORGET_PASSWORD)->EnableWindow(TRUE);
    GetDlgItem(IDC_BTN_DELETE_ACCOUNT)->EnableWindow(TRUE);
    m_accounts.SetCurSel(0);
    UpdateData(FALSE);
  }
  else
  {
    GetDlgItem(IDOK)->EnableWindow(FALSE);
    GetDlgItem(IDC_BTN_DELETE_ACCOUNT)->EnableWindow(FALSE);
    GetDlgItem(IDC_BTN_FORGET_PASSWORD)->EnableWindow(FALSE);
  }  
  GetDlgItem(IDC_EDIT2)->SetFocus();    
}
