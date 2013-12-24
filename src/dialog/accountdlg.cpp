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
  info.Format("游戏帐号：%s [%s]\r\n" , data_->GetLoginedAccountName() , data_->GetLoginedAccountPosition().ToCString(buf));
  CString temp;
  //planet name
  temp.Format("星球名称：%s\r\n" , data_->GetLoginedAccountStarName());
  info += temp;
  //temp
  temp.Format("主星温度：大约 %d°C 到 %d°C\r\n" , data_->STAR_TEMP() - 40 , data_->STAR_TEMP());
  info += temp;
  //size
  temp.Format("主星方圆：%d/%d 方圆\r\n" , data_->STAR_USED_SIZE() , data_->STAR_CIRU());
  info += temp;
  //speed
  temp.Format("游戏速度：%d 倍速\r\n" , data_->GAME_SPEED());
  info += temp; 
  //computer rank
  CString s;
  if(data_->GetLoginedAccountComputerRank() == COMPUTER_T_LOW)
  {
    s = "超级菜鸟";
  }
  else if(data_->GetLoginedAccountComputerRank() == COMPUTER_T_MID)
  {
    s = "中级高手";
  }
  else
  {
    s = "超级高手";
  }
  //ai mode
  temp.Format("电脑级别：%s\r\n" , s);
  info += temp;  
  s = "根据游戏时间发展";
  if(data_->COMPUTER_AI_MODE() == COM_AI_T_BY_PLAYER)
  {
    s = "根据玩家积分随机刷新";
  }
  temp.Format("电脑模式：%s\r\n" , s);
  info += temp;  
  s = "电脑会攻击玩家";
  if(data_->CAN_COMPUTER_ATTACK() == false)
  {
    s = "电脑不会攻击玩家";
  }
  temp.Format("电脑攻击：%s\r\n" , s);
  info += temp;  

  temp.Format("NPC角色 ：%s\r\n" , data_->NPC_NAME());
  info += temp;  
  //resource
  s = "下线资源会增加";
  if(data_->IS_NOT_UP_RES_OFFLINE())
  {
    s = "下线资源不会增加";
  }
  temp.Format("资源模式：%s\r\n" , s);
  info += temp;

  temp.Format("注册时间：%d-%02d-%02d %02d:%02d:%02d" , data_->REGISTER_TIME().GetYear() , data_->REGISTER_TIME().GetMonth() , 
    data_->REGISTER_TIME().GetDay() , data_->REGISTER_TIME().GetHour() , data_->REGISTER_TIME().GetMinute() , data_->REGISTER_TIME().GetSecond());
  info += temp;  

  GetDlgItem(IDC_EDIT_ACCOUNT_INFO)->SetWindowText(info);	
  GetDlgItem(IDC_EDIT_ACCOUNT_INFO)->SendMessage(EM_FMTLINES , TRUE , 0);

  m_list_hero.InsertColumn(0 , "英雄" , LVCFMT_CENTER , 100);
  m_list_hero.InsertColumn(1 , "数目" , LVCFMT_CENTER , 60);
  m_list_hero.InsertColumn(2 , "功能" , LVCFMT_CENTER , 240);

  if(data_->GET_STAR_DOUBLE_RES_HERO() > 0)
  {
    int size = m_list_hero.GetItemCount();
    m_list_hero.InsertItem(size , "银河地质学家");
    info.Format("%d（最多3位）" , data_->GET_STAR_DOUBLE_RES_HERO());
    m_list_hero.SetItemText(size , 1 , info);
    m_list_hero.SetItemText(size , 2 , "每一位银河地质学家使资源产量翻倍");
  }

  GetDlgItem(IDC_LIST1)->SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
