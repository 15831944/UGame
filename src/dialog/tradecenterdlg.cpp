// tradecenterdlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\XGame\xgame.h"
#include "tradecenterdlg.h"
#include "pagecommander.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTradeCenterDlg dialog


CTradeCenterDlg::CTradeCenterDlg(GameData* acc , CWnd* pParent /*=NULL*/)
	: CDialog(CTradeCenterDlg::IDD, pParent) , data_(acc) , pParent_((CPageCommander*)pParent)
{
	//{{AFX_DATA_INIT(CTradeCenterDlg)
	m_crystal = 0;
	m_diop = 0;
	m_metal = 0;
	m_trade_percent = _T("2:1:1");
	m_trade_money = 0;
	m_trade_type = 0;
	m_avai_crystal = 0;
	m_avai_metal = 0;
	m_avai_diop = 0;
	m_trade_poundage = 0;
	//}}AFX_DATA_INIT
  is_traded = false;
}


void CTradeCenterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTradeCenterDlg)
	DDX_Text(pDX, IDC_EDIT_C, m_crystal);
	DDX_Text(pDX, IDC_EDIT_D, m_diop);
	DDX_Text(pDX, IDC_EDIT_M, m_metal);
	DDX_Text(pDX, IDC_EDIT_TRADE_PERCENT, m_trade_percent);
	DDX_Text(pDX, IDC_EDIT_TRADE_MONEY, m_trade_money);
	DDX_Radio(pDX, IDC_RADIO2, m_trade_type);
	DDX_Text(pDX, IDC_EDIT_AVAI_C, m_avai_crystal);
	DDX_Text(pDX, IDC_EDIT_AVAI_M, m_avai_metal);
	DDX_Text(pDX, IDC_EDIT_AVAI_D, m_avai_diop);
	DDX_Text(pDX, IDC_EDIT_TRADE_POUNDAGE, m_trade_poundage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTradeCenterDlg, CDialog)
	//{{AFX_MSG_MAP(CTradeCenterDlg)
	ON_BN_CLICKED(IDC_BTN_METAL_MAX, OnBtnMetalMax)
	ON_BN_CLICKED(IDC_BTN_CRY_MAX, OnBtnCryMax)
	ON_BN_CLICKED(IDC_BTN_DIOP_MAX, OnBtnDiopMax)
	ON_EN_CHANGE(IDC_EDIT_M, OnChangeEditM)
	ON_EN_CHANGE(IDC_EDIT_D, OnChangeEditD)
	ON_EN_CHANGE(IDC_EDIT_C, OnChangeEditC)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTradeCenterDlg message handlers

BOOL CTradeCenterDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
  //ctrls
  UpdateCtrls();

  //available resource
  ulong r = data_->GetLoginedAccountRank() / 2000.0 + 1;
  ulong seed = RandomNumber(1000) + 1;
  m_avai_metal = 100 * seed * r;

  seed = RandomNumber(500) + 1;
  m_avai_crystal = 100 * seed * r;

  seed = RandomNumber(500) + 1;
  m_avai_diop = 100 * seed * r;

  //max number
  m_avai_metal   = m_avai_metal   > 100000000 ? 100000000 : m_avai_metal;
  m_avai_crystal = m_avai_crystal > 50000000 ? 50000000 : m_avai_crystal;
  m_avai_diop    = m_avai_diop    > 50000000 ? 50000000 : m_avai_diop;

  UpdateData(FALSE);	

  UpdateTradeMoney();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CTradeCenterDlg::OnBtnMetalMax() 
{
	UpdateData(TRUE);
  if(m_trade_type == TRADE_T_OUT)
	  m_metal = min(data_->STAR_RESOURCE(HOMESTAR).metal_ , m_avai_metal);
  else
  {
    double avail_money = data_->GetAccountMoney() - m_crystal * 1.05 - m_diop * 1.05;
    avail_money = avail_money < 0.0 ? 0.0 : avail_money;
    m_metal = min((double)m_avai_metal , avail_money * 2.0 / 1.05);
  }
  UpdateData(FALSE);	
  UpdateTradeMoney();
}

void CTradeCenterDlg::OnBtnCryMax() 
{
  UpdateData(TRUE);
  if(m_trade_type == TRADE_T_OUT)
	  m_crystal = min(data_->STAR_RESOURCE(HOMESTAR).crystal_ , m_avai_crystal);
  else
  {
    double avail_money = data_->GetAccountMoney() - m_metal * 0.525 - m_diop * 1.05;
    avail_money = avail_money < 0.0 ? 0.0 : avail_money;
    m_crystal = min((double)m_avai_crystal , avail_money * 1.0 / 1.05);
  }

  UpdateData(FALSE);		
  UpdateTradeMoney();
}

void CTradeCenterDlg::OnBtnDiopMax() 
{	
  UpdateData(TRUE);
  if(m_trade_type == TRADE_T_OUT)
	  m_diop = min(data_->STAR_RESOURCE(HOMESTAR).diplogen_ , m_avai_diop);
  else
  {
    double avail_money = data_->GetAccountMoney() - m_metal * 0.525 - m_crystal * 1.05;
    avail_money = avail_money < 0.0 ? 0.0 : avail_money;
    m_diop = min((double)m_avai_diop , avail_money * 1.0 / 1.05);
  }
  UpdateData(FALSE);		
  UpdateTradeMoney();
}

void CTradeCenterDlg::OnChangeEditM() 
{
  UpdateData(TRUE);
  m_metal = m_metal > m_avai_metal ? m_avai_metal : m_metal;
  if(m_trade_type == TRADE_T_OUT)
  {
    m_metal = m_metal > data_->STAR_RESOURCE(HOMESTAR).metal_ ? data_->STAR_RESOURCE(HOMESTAR).metal_ : m_metal;
  }
  else
  {
    double avail_money = data_->GetAccountMoney() - m_crystal * 1.05 - m_diop * 1.05;
    avail_money = avail_money < 0.0 ? 0.0 : avail_money;
    m_metal = m_metal > avail_money * 2.0 / 1.05 ? avail_money * 2.0 / 1.05 : m_metal;
  }
  UpdateData(FALSE);
  UpdateTradeMoney();
}

void CTradeCenterDlg::OnChangeEditC() 
{
  UpdateData(TRUE);
	m_crystal = m_crystal > m_avai_crystal ? m_avai_crystal : m_crystal;
	if(m_trade_type == TRADE_T_OUT)
  {
    m_crystal = m_crystal > data_->STAR_RESOURCE(HOMESTAR).crystal_ ? data_->STAR_RESOURCE(HOMESTAR).crystal_ : m_crystal;
  }
  else
  {
    double avail_money = data_->GetAccountMoney() - m_diop * 1.05 - m_metal * 0.525;
    avail_money = avail_money < 0.0 ? 0.0 : avail_money;
    m_crystal = m_crystal > avail_money * 1.0 / 1.05 ? avail_money * 1.0 / 1.05 : m_crystal;
  }
  UpdateData(FALSE);
  UpdateTradeMoney();
}

void CTradeCenterDlg::OnChangeEditD() 
{
  UpdateData(TRUE);
  m_diop = m_diop > m_avai_diop ? m_avai_diop : m_diop;
	if(m_trade_type == TRADE_T_OUT)
  {
    m_diop = m_diop > data_->STAR_RESOURCE(HOMESTAR).diplogen_ ? data_->STAR_RESOURCE(HOMESTAR).diplogen_ : m_diop;
  }
  else
  {
    double avail_money = data_->GetAccountMoney() - m_crystal * 1.05 - m_metal * 0.525;
    avail_money = avail_money < 0.0 ? 0.0 : avail_money;
    m_diop = m_diop > avail_money * 1.0 / 1.05 ? avail_money * 1.0 / 1.05 : m_diop;
  }
  UpdateData(FALSE);
	UpdateTradeMoney();
}

void CTradeCenterDlg::OnRadio2() 
{
  int buf = m_trade_type;
  UpdateData(TRUE);
  if(buf != m_trade_type)
  {
    m_metal = m_crystal = m_diop = 0L;
    UpdateData(FALSE);	
  }
  UpdateTradeMoney();
}

void CTradeCenterDlg::OnRadio1() 
{
	int buf = m_trade_type;
  UpdateData(TRUE);
  if(buf != m_trade_type)
  {
    m_metal = m_crystal = m_diop = 0L;
    UpdateData(FALSE);	
  }
	UpdateTradeMoney();
}

void CTradeCenterDlg::UpdateTradeMoney()
{
  UpdateData(TRUE);
  //1 U Money = 2M = 1C = 1H
  m_trade_money = m_metal * 0.5 + m_crystal + m_diop;
  m_trade_poundage = m_trade_money * 0.05;
  GetDlgItem(IDOK)->EnableWindow(m_trade_money > 0);
  UpdateData(FALSE);
}

void CTradeCenterDlg::UpdateCtrls()
{
  char buf[64];	
	//ctrls
  CString info;
  info.Format("%s" , AddPointsToNumber(data_->STAR_RESOURCE(HOMESTAR).metal_ , buf));
  GetDlgItem(IDC_STA_METAL)->SetWindowText(info);

  info.Format("%s" , AddPointsToNumber(data_->STAR_RESOURCE(HOMESTAR).crystal_ , buf));
  GetDlgItem(IDC_STA_CRY)->SetWindowText(info);

  info.Format("%s" , AddPointsToNumber(data_->STAR_RESOURCE(HOMESTAR).diplogen_ , buf));
  GetDlgItem(IDC_STA_DIOP)->SetWindowText(info);

  info.Format("%s" , AddPointsToNumber(data_->GetAccountMoney() , buf));
  GetDlgItem(IDC_STA_MONEY)->SetWindowText(info);
}

void CTradeCenterDlg::OnOK() 
{
	//check trade confirming 
  UpdateData(TRUE);
  UpdateCtrls();
  CString info;
  CString type = (m_trade_type == TRADE_T_OUT ? "卖出" : "买进");
  info.Format("您交易的类型是：%s，交易U币：%d，交易手续费U币：%d，您确定要交易吗？",type , m_trade_money , m_trade_poundage);
  if(MessageBox(info , "请确定" , MB_YESNO | MB_ICONQUESTION) == IDNO)
    return;
  //check number
  if(m_trade_money < 1L)
  {
    return;
  }

  //out, is enough money
  if(m_trade_type == TRADE_T_OUT)
  {
    //metal
    if(m_metal > m_avai_metal)
    {
      AfxMessageBox("您要卖出的金属数目超过交易中心收购最大值，请调整");
      GetDlgItem(IDC_EDIT_METAL)->SetFocus();
      return;
    }
    if(m_metal > data_->STAR_RESOURCE(HOMESTAR).metal_)
    {
      AfxMessageBox("您目前没有这么多可以卖出的金属，请调整");
      GetDlgItem(IDC_EDIT_METAL)->SetFocus();
      return;
    }
    //crystal
    if(m_crystal > m_avai_crystal)
    {
      AfxMessageBox("您要卖出的晶体数目超过交易中心收购最大值，请调整");
      GetDlgItem(IDC_EDIT_CRYSTAL)->SetFocus();
      return;
    }
    if(m_crystal > data_->STAR_RESOURCE(HOMESTAR).crystal_)
    {
      AfxMessageBox("您目前没有这么多可以卖出的晶体，请调整");
      GetDlgItem(IDC_EDIT_CRYSTAL)->SetFocus();
      return;
    }
    //diop
    if(m_diop > m_avai_diop)
    {
      AfxMessageBox("您要卖出的重氢数目超过交易中心收购最大值，请调整");
      GetDlgItem(IDC_EDIT_DIOP)->SetFocus();
      return;
    }
    if(m_diop > data_->STAR_RESOURCE(HOMESTAR).diplogen_)
    {
      AfxMessageBox("您目前没有这么多可以卖出的重氢，请调整");
      GetDlgItem(IDC_EDIT_DIOP)->SetFocus();
      return;
    }
  }  

  //in, is enough money
  if(m_trade_type == TRADE_T_IN)
  {
    //metal
    if(m_metal > m_avai_metal)
    {
      AfxMessageBox("您要卖进的金属数目超过交易中心卖出最大值，请调整");
      GetDlgItem(IDC_EDIT_METAL)->SetFocus();
      return;
    }
    //crystal
    if(m_crystal > m_avai_crystal)
    {
      AfxMessageBox("您要卖进的晶体数目超过交易中心卖出最大值，请调整");
      GetDlgItem(IDC_EDIT_CRYSTAL)->SetFocus();
      return;
    }
    //diop
    if(m_diop > m_avai_diop)
    {
      AfxMessageBox("您要卖进的重氢数目超过交易中心卖出最大值，请调整");
      GetDlgItem(IDC_EDIT_DIOP)->SetFocus();
      return;
    }
    //money
    if(m_trade_money + m_trade_poundage > data_->GetAccountMoney())
    {
      AfxMessageBox("您的U币不够支付，请调整买进资源");
      GetDlgItem(IDC_EDIT_METAL)->SetFocus();
      return;
    }
  }
  //check pass, out
  if(m_trade_type == TRADE_T_OUT)
  {
    //resource decrease
    data_->DecreaseResource(m_metal , m_crystal , m_diop , HOMESTAR);

    //U money increase
    data_->UpdateAccountMoney(m_trade_money - m_trade_poundage);
  }
  //check pass, in
  else
  {
    //resource increase
    data_->IncreaseResource(m_metal , m_crystal , m_diop , HOMESTAR);

    //U money decrease
    data_->UpdateAccountMoney( - 1.0 * (m_trade_money + m_trade_poundage));
  }
  //notify
  pParent_->NotifyFinishedTrade();
  UpdateCtrls();

  //update
  m_avai_metal -= m_metal;
  m_avai_crystal -= m_crystal;
  m_avai_diop -= m_diop;
  m_metal = 0L;
  m_crystal = 0L;
  m_diop = 0L;
  UpdateData(FALSE);
  UpdateTradeMoney();
  is_traded = true;
}
