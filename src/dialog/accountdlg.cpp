// accountdlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\XGame\xgame.h"
#include "accountdlg.h"
#include "GameDataRecorder.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAccountDlg dialog




CAccountDlg::CAccountDlg(GameData* d , CWnd* pParent /*=NULL*/)
	: data_(d) , CDialog(CAccountDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAccountDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAccountDlg)
	DDX_Control(pDX, IDC_LIST1, m_list_hero);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAccountDlg, CDialog)
	//{{AFX_MSG_MAP(CAccountDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAccountDlg message handlers

BOOL CAccountDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//account
  CString info;
  char buf[32];
  info.Format("��Ϸ�ʺţ�%s [%s]\r\n" , data_->GetLoginedAccountName() , data_->GetLoginedAccountPosition().ToCString(buf));
  CString temp;
  //planet name
  temp.Format("�������ƣ�%s\r\n" , data_->GetLoginedAccountStarName());
  info += temp;
  //temp
  temp.Format("�����¶ȣ���Լ %d��C �� %d��C\r\n" , data_->STAR_TEMP() - 40 , data_->STAR_TEMP());
  info += temp;
  //size
  temp.Format("���Ƿ�Բ��%d/%d ��Բ\r\n" , data_->STAR_USED_SIZE() , data_->STAR_CIRU());
  info += temp;
  //speed
  temp.Format("��Ϸ�ٶȣ�%d ����\r\n" , data_->GAME_SPEED());
  info += temp; 
  //computer rank
  CString s;
  if(data_->GetLoginedAccountComputerRank() == COMPUTER_T_LOW)
  {
    s = "��������";
  }
  else if(data_->GetLoginedAccountComputerRank() == COMPUTER_T_MID)
  {
    s = "�м�����";
  }
  else
  {
    s = "��������";
  }
  //ai mode
  temp.Format("���Լ���%s\r\n" , s);
  info += temp;  
  s = "������Ϸʱ�䷢չ";
  if(data_->COMPUTER_AI_MODE() == COM_AI_T_BY_PLAYER)
  {
    s = "������һ������ˢ��";
  }
  temp.Format("����ģʽ��%s\r\n" , s);
  info += temp;  
  s = "���Իṥ�����";
  if(data_->CAN_COMPUTER_ATTACK() == false)
  {
    s = "���Բ��ṥ�����";
  }
  temp.Format("���Թ�����%s\r\n" , s);
  info += temp;  

  temp.Format("NPC��ɫ ��%s\r\n" , data_->NPC_NAME());
  info += temp;  
  //resource
  s = "������Դ������";
  if(data_->IS_NOT_UP_RES_OFFLINE())
  {
    s = "������Դ��������";
  }
  temp.Format("��Դģʽ��%s\r\n" , s);
  info += temp;

  temp.Format("ע��ʱ�䣺%d-%02d-%02d %02d:%02d:%02d" , data_->REGISTER_TIME().GetYear() , data_->REGISTER_TIME().GetMonth() , 
    data_->REGISTER_TIME().GetDay() , data_->REGISTER_TIME().GetHour() , data_->REGISTER_TIME().GetMinute() , data_->REGISTER_TIME().GetSecond());
  info += temp;  

  GetDlgItem(IDC_EDIT_ACCOUNT_INFO)->SetWindowText(info);	
  GetDlgItem(IDC_EDIT_ACCOUNT_INFO)->SendMessage(EM_FMTLINES , TRUE , 0);

  m_list_hero.InsertColumn(0 , "Ӣ��" , LVCFMT_CENTER , 100);
  m_list_hero.InsertColumn(1 , "��Ŀ" , LVCFMT_CENTER , 60);
  m_list_hero.InsertColumn(2 , "����" , LVCFMT_CENTER , 240);

  if(data_->GET_STAR_DOUBLE_RES_HERO() > 0)
  {
    int size = m_list_hero.GetItemCount();
    m_list_hero.InsertItem(size , "���ӵ���ѧ��");
    info.Format("%d�����3λ��" , data_->GET_STAR_DOUBLE_RES_HERO());
    m_list_hero.SetItemText(size , 1 , info);
    m_list_hero.SetItemText(size , 2 , "ÿһλ���ӵ���ѧ��ʹ��Դ��������");
  }

  GetDlgItem(IDC_LIST1)->SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
