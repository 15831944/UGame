// newaccountdlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\XGame\xgame.h"
#include "newaccountdlg.h"
#include "GameFileReader.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewAccountDlg dialog


CNewAccountDlg::CNewAccountDlg(AccountManager* acc , CWnd* pParent /*=NULL*/)
	: CDialog(CNewAccountDlg::IDD, pParent) , account_(acc)
{
	//{{AFX_DATA_INIT(CNewAccountDlg)
	m_accout_name = _T("");
	m_password = _T("");
	m_password_again = _T("");
	m_star_name = _T("");
	m_computer_type = COMPUTER_T_MID;
	m_game_speed = 10;
	m_bCOMAI = 0;
	m_npc_name = _T("");
	m_computer_attack_me = TRUE;
	m_bNotResUp = FALSE;
	//}}AFX_DATA_INIT
}


void CNewAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewAccountDlg)
	DDX_Text(pDX, IDC_EDIT_NAME, m_accout_name);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_password);
	DDX_Text(pDX, IDC_EDIT_PASSWORDAGAIN, m_password_again);
	DDX_Text(pDX, IDC_EDIT_STAR_NAME, m_star_name);
	DDX_CBIndex(pDX, IDC_COMBO1, m_computer_type);
	DDX_Text(pDX, IDC_EDIT_SPEED, m_game_speed);
	DDX_Radio(pDX, IDC_RADIO1, m_bCOMAI);
	DDX_Text(pDX, IDC_EDIT_NPC_NAME, m_npc_name);
	DDX_Check(pDX, IDC_CHECK1, m_computer_attack_me);
	DDX_Check(pDX, IDC_CHECK_RESOURCE, m_bNotResUp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewAccountDlg, CDialog)
	//{{AFX_MSG_MAP(CNewAccountDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewAccountDlg message handlers

BOOL CNewAccountDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	GetDlgItem(IDC_EDIT_NAME)->SetFocus();	
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewAccountDlg::OnOK() 
{
  UpdateData(TRUE);
	//check account
  if(m_accout_name.IsEmpty())
  {
    AfxMessageBox("�ʺ�������Ϊ�գ������������ʻ�����");
    GetDlgItem(IDC_EDIT_NAME)->SetFocus();
    return;
  }
  if(m_accout_name.GetLength() > 16)
  {
    AfxMessageBox("�ʺ�����󳤶�Ϊ16�������������ʻ�����");
    GetDlgItem(IDC_EDIT_NAME)->SetFocus();
    return;
  }
  if(IsValidText(m_accout_name) == FALSE)
  {
    AfxMessageBox("�ʺ�����ֻ�������֡���ĸ���»��ߣ������������ʻ�����");
    GetDlgItem(IDC_EDIT_NAME)->SetFocus();
    return;
  }
  if(account_->ExistAccount(m_accout_name))
  {
    AfxMessageBox("���ʺ��Ѿ���ע�ᣬ�����������ʻ�����");
    GetDlgItem(IDC_EDIT_NAME)->SetFocus();
    return;
  }
  //password
  if(m_password != m_password_again)
  {
    AfxMessageBox("�����������ò�һ�£���������������");
    GetDlgItem(IDC_EDIT_PASSWORD)->SetFocus();
    return;
  }
  if(m_password.GetLength() > 16)
  {
    AfxMessageBox("�����Ϊ16λ�������������ʻ�����");
    GetDlgItem(IDC_EDIT_PASSWORD)->SetFocus();
    return;
  }
  //star name
  if(m_star_name.IsEmpty())
  {
    AfxMessageBox("����������Ϊ�գ�������������������");
    GetDlgItem(IDC_EDIT_STAR_NAME)->SetFocus();
    return;
  }
  if(m_star_name.GetLength() > 16)
  {
    AfxMessageBox("��������󳤶�Ϊ16��������������������");
    GetDlgItem(IDC_EDIT_STAR_NAME)->SetFocus();
    return;
  }
  if(IsValidText(m_star_name) == FALSE)
  {
    AfxMessageBox("��������ֻ�������֡���ĸ���»��ߣ�������������������");
    GetDlgItem(IDC_EDIT_STAR_NAME)->SetFocus();
    return;
  }	
  if(m_game_speed < 1 || m_game_speed > MAX_GAME_SPEED)
  {
    CString INFO;
    INFO.Format("�Ƿ�����Ϸ�ٶ����ã��ٶȷ�ΧΪ1-%d" , MAX_GAME_SPEED);
    AfxMessageBox(INFO);
    GetDlgItem(IDC_EDIT_SPEED)->SetFocus();
    return;
  }
  //npc name
  if(m_npc_name.GetLength() > 16)
  {
    AfxMessageBox("NPC������󳤶�Ϊ16������������NPC����");
    GetDlgItem(IDC_EDIT_NPC_NAME)->SetFocus();
    return;
  }
  if(m_npc_name.IsEmpty() == FALSE && IsValidText(m_npc_name) == FALSE)
  {
    AfxMessageBox("NPC����ֻ�������֡���ĸ���»��ߣ�����������NPC����");
    GetDlgItem(IDC_EDIT_NPC_NAME)->SetFocus();
    return;
  }	
	CDialog::OnOK();
}
