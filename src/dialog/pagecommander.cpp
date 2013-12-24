#include "stdafx.h"
#include "..\XGame\xgame.h"
#include "pagecommander.h"
#include "communication.h"
#include "XGameDlg.h"
#include "TipWarpper.h"
#include "tradecenterdlg.h"
#include "supergatetransferdlg.h"
#include "GameLogger.h"


extern float _speed_adjust_;

static int Set_List_Column_Type( int col )
{ 
  if( col == 2)
    return CEditList::eEdit;  
  return CEditList::eReadOnly;
}

CPageCommander::CPageCommander(UINT iconID /*= NULL*/ , CWnd* pParent /*=NULL*/)
	: CPageIcon(CPageCommander::IDD , iconID) , m_list1(this) ,
  m_ctl_pos_gala(IDC_EDIT_GALA , this) , 
  m_ctl_pos_sys(IDC_EDIT_SYS , this) ,
  m_ctl_pos_pos(IDC_EDIT_POS , this)
{
	//{{AFX_DATA_INIT(CPageCommander)
	m_default_spy = 1;
	m_speed_ratio = 0;
	m_task_type = TASK_T_NONE;
	m_self_star = 0;
	m_transfer_metal = 0;
	m_transfer_crystal = 0;
	m_transfer_diop = 0;
	m_target_star_type = 0;
	m_fast_star = -1;
	//}}AFX_DATA_INIT
  task_counter_ = 0;
  InitIDManager();
  available_transfer_number_ = 0.0;
  menu_list.LoadMenu(IDR_MENU_FLEETLIST);
}


void CPageCommander::DoDataExchange(CDataExchange* pDX)
{
	CPageIcon::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageCommander)
	DDX_Control(pDX, IDC_LIST_TASK_ENEMY, m_list_enemy);
	DDX_Control(pDX, IDC_EDIT_POS, m_ctl_pos_pos);
	DDX_Control(pDX, IDC_EDIT_SYS, m_ctl_pos_sys);
	DDX_Control(pDX, IDC_EDIT_GALA, m_ctl_pos_gala);
	DDX_Control(pDX, IDC_COMBO2, m_ctl_target_type);
	DDX_Control(pDX, IDC_COMBO_SPEED, m_ctl_speed);
	DDX_Control(pDX, IDC_COMBO_FASTSTAR, m_ctl_fast_star);
	DDX_Control(pDX, IDC_COMBO1, m_ctl_self_star);
	DDX_Control(pDX, IDC_LIST_TASK_LIST, m_list2);
	DDX_Control(pDX, IDC_LIST_TASK, m_list1);
	DDX_Text(pDX, IDC_EDIT_DEFAULT, m_default_spy);
	DDX_CBIndex(pDX, IDC_COMBO_SPEED, m_speed_ratio);
	DDX_Radio(pDX, IDC_RADIO1, m_task_type);
	DDX_CBIndex(pDX, IDC_COMBO1, m_self_star);
	DDX_Text(pDX, IDC_EDIT_METAL, m_transfer_metal);
	DDX_Text(pDX, IDC_EDIT_CRYSTAL, m_transfer_crystal);
	DDX_Text(pDX, IDC_EDIT_DIOP, m_transfer_diop);
	DDX_CBIndex(pDX, IDC_COMBO2, m_target_star_type);
	DDX_CBIndex(pDX, IDC_COMBO_FASTSTAR, m_fast_star);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageCommander, CPageIcon)
	//{{AFX_MSG_MAP(CPageCommander)
	ON_WM_TIMER()
	ON_EN_KILLFOCUS(IDC_EDIT_DEFAULT, OnKillfocusEditDefault)
	ON_BN_CLICKED(ID_BTN_ALL, OnBtnAll)
	ON_BN_CLICKED(ID_BTN_NONE, OnBtnNone)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_TASK, OnDblclkListTask)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	ON_CBN_EDITCHANGE(IDC_COMBO_SPEED, OnEditchangeComboSpeed)
	ON_CBN_CLOSEUP(IDC_COMBO_SPEED, OnCloseupComboSpeed)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_TASK_LIST, OnRclickListTaskList)
	ON_COMMAND(ID_MENU_FLEET_CALLBACK, OnMenuFleetCallback)
	ON_CBN_CLOSEUP(IDC_COMBO1, OnCloseupCombo1)
	ON_CBN_CLOSEUP(IDC_COMBO_FASTSTAR, OnCloseupComboFaststar)
	ON_CBN_CLOSEUP(IDC_COMBO2, OnCloseupCombo2)
	ON_BN_CLICKED(IDC_BTN_METAL_MAX, OnBtnMetalMax)
	ON_BN_CLICKED(IDC_BTN_CRYSTAL_MAX, OnBtnCrystalMax)
	ON_BN_CLICKED(IDC_BTN_DIOP_MAX, OnBtnDiopMax)
	ON_EN_CHANGE(IDC_EDIT_CRYSTAL, OnChangeEditCrystal)
	ON_EN_CHANGE(IDC_EDIT_DIOP, OnChangeEditDiop)
	ON_EN_CHANGE(IDC_EDIT_METAL, OnChangeEditMetal)
	ON_BN_CLICKED(IDC_BTN_ALL_RESOURCE, OnBtnAllResource)
	ON_BN_CLICKED(ID_BTN_DESTROYCOLONY, OnBtnDestroycolony)
	ON_BN_CLICKED(ID_BTN_PRODUCEMOON, OnBtnProducemoon)
	ON_BN_CLICKED(ID_BTN_PRODUCEGATE, OnBtnProducegate)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(ID_BTN_TRANSFER, OnBtnTransfer)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnSelchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO_SPEED, OnSelchangeComboSpeed)
	ON_CBN_SELCHANGE(IDC_COMBO_FASTSTAR, OnSelchangeComboFaststar)
	ON_BN_CLICKED(ID_BTN_TRADE, OnBtnTrade)
	ON_BN_CLICKED(ID_BTN_ALL_WAR, OnBtnAllWar)
	ON_BN_CLICKED(ID_BTN_ALL_BANJIA, OnBtnAllBanjia)
	//}}AFX_MSG_MAP
  ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_TASK_LIST, OnSetItemColor)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageCommander message handlers

void CPageCommander::OnSetItemColor(NMHDR* pNMHDR, LRESULT* pResult )
{
  NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );
  *pResult = 0;
  if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
  {
    *pResult = CDRF_NOTIFYITEMDRAW;
  }
  else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
  {
    *pResult = CDRF_NOTIFYSUBITEMDRAW;
  }
  else if ( (CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage )
  {
    COLORREF crText = RGB(0 , 0 , 0);      
    if (pLVCD->iSubItem == 2)
    {
      crText = RGB(0 , 0 , 255);
    }
    else if (pLVCD->iSubItem == 6)
    {
      crText = RGB(255 , 0 , 0);
    }
    pLVCD->clrText = crText;
    *pResult = CDRF_DODEFAULT;
  }
}

BOOL CPageCommander::OnInitDialog() 
{
	CPageIcon::OnInitDialog();
	m_list1.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
  m_list1.SetColumnType((fGetType)Set_List_Column_Type);
	m_list2.SetExtendedStyle(LVS_EX_FULLROWSELECT);
  m_list_enemy.SetExtendedStyle(LVS_EX_FULLROWSELECT);
  m_list1.Initialize();
  m_list1.EnableToolTips(TRUE);
  m_list2.EnableToolTips(TRUE);

  //edit
  m_ctl_pos_gala.SetRange(1 , MAX_GALAXY_GALA);
  m_ctl_pos_sys.SetRange(1 , MAX_GALAXY_SYS);
  m_ctl_pos_pos.SetRange(1 , MAX_GALAXY_POS);

  //init ctrls
  m_sta_is_max.SubclassDlgItem(IDC_STA_IS_MAX , this);
  m_sta_is_max.SetTextColor(RGB(255 , 0 , 0));

  m_sta_transfer.SubclassDlgItem(IDC_STATIC_TRANSFER , this);
  m_sta_transfer.SetTextColor(RGB(0 , 255 , 0));

  m_sta_ships_number.SubclassDlgItem(IDC_STATIC_ATTACK , this);
  m_sta_ships_number.SetTextColor(RGB(0 , 255 , 0));

  m_sta_time.SubclassDlgItem(IDC_STATIC_TIME , this);
  m_sta_time.SetTextColor(RGB(0 , 255 , 0));
  m_sta_time.SetCaption("-");

  m_sta_oil.SubclassDlgItem(IDC_STATIC_OIL , this);
  m_sta_oil.SetTextColor(RGB(0 , 255 , 0));
  m_sta_oil.SetCaption("-");

  m_sta_task_number.SubclassDlgItem(IDC_STA_MAX_TASKS , this);
  m_sta_task_number.SetTextColor(RGB(0 , 255 , 0));

  m_sta_left_res.SubclassDlgItem(IDC_STATIC_LEFT_CAPACITY , this);
  m_sta_left_res.SetTextColor(RGB(0 , 255 , 0));

  m_sta_is_max.SetBackColor(RGB(55 , 77 , 112));
  m_sta_transfer.SetBackColor(RGB(55 , 77 , 112));
  m_sta_ships_number.SetBackColor(RGB(55 , 77 , 112));
  m_sta_time.SetBackColor(RGB(55 , 77 , 112));
  m_sta_oil.SetBackColor(RGB(55 , 77 , 112));
  m_sta_task_number.SetBackColor(RGB(55 , 77 , 112));
  m_sta_left_res.SetBackColor(RGB(55 , 77 , 112));  

	m_list1.InsertColumn(0 , "船舰名称" , LVCFMT_LEFT,  150);
  m_list1.InsertColumn(1 , "可用数" , LVCFMT_CENTER,  200);
  m_list1.InsertColumn(2 , "派遣数（直接输入数字）" , LVCFMT_CENTER,  200);

  for(int i = 0 ; i < BOAT_MAX ; ++i)
  {
    m_list1.InsertItem(i , BOATS_NAME[i]);
    CString info , tip;
    info.Format("速度：%d" , kernel_.GetShipSpeed(ITEM_TYPE(i) , 0));
    tip += info;

    info.Format("\n装载：%d" , SHIP_TRANSFER_CAPACITY[i] );
    tip += info;

    m_list1.SetItemToolTipText(i, 0, tip);
  }

  m_list2.InsertColumn(0 , "编号" , LVCFMT_CENTER , 50);
  m_list2.InsertColumn(1 , "任务" , LVCFMT_CENTER , 80);
  m_list2.InsertColumn(2 , "船舰数量" , LVCFMT_CENTER , 68);
  m_list2.InsertColumn(3 , "出发星球" , LVCFMT_CENTER , 68);
  m_list2.InsertColumn(4 , "目标星球" , LVCFMT_CENTER , 68);
  m_list2.InsertColumn(5 , "携带资源" , LVCFMT_CENTER , 320);
  m_list2.InsertColumn(6 , "剩余时间" , LVCFMT_CENTER , 104);  
  
  m_list_enemy.InsertColumn(0 , "敌方坐标" , LVCFMT_CENTER , 68);
  m_list_enemy.InsertColumn(1 , "我方坐标" , LVCFMT_CENTER , 68);
  m_list_enemy.InsertColumn(2 , "舰队组成" , LVCFMT_CENTER , 535); 
  m_list_enemy.InsertColumn(3 , "剩余时间" , LVCFMT_CENTER , 100); 
  

#ifdef LISTCTRL_USING_MY_FONT
  LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 14;
	strcpy(lf.lfFaceName, "新宋体");
	font_list.CreateFontIndirect(&lf);
	m_list1.SetFont(&font_list, TRUE);
#endif

  m_default_spy = GetDataPtr()->GetDefaultSpyNumber();
  GetDlgItem(IDOK)->EnableWindow(FALSE);
  UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//init
void CPageCommander::Notify_Init()
{
  UpdateCombo();
  m_self_star = HOMESTAR;
  PlaniPos pos = GetDataPtr()->STAR_POSITION(HOMESTAR);
  m_ctl_pos_gala.SetData(pos.Gala);
  m_ctl_pos_sys.SetData(pos.Sys);
  m_ctl_pos_pos.SetData(pos.Pos);

  UpdateData(FALSE);
  NotifySelfStarChanged(ACTIVE_STAR_INDEX());
  TaskCounterLabelChange(); 

  //trade time
  //SET timer 1 s, 60 minutes
  timer_for_trade_.Init(3600);
  SetTimer(TIMER_FOR_TRADE , 1000 , NULL);
  GetDlgItem(ID_BTN_TRADE)->SetWindowText(timer_for_trade_.ToCString());
  GetDlgItem(ID_BTN_TRADE)->EnableWindow(FALSE);

  //transfer time
  //SET timer, 1 s , 60 minutes
  timer_for_gate_.Init(3600);
  SetTimer(TIMER_FOR_GATE , 1000 , NULL);
  GetDlgItem(ID_BTN_TRANSFER)->SetWindowText(timer_for_gate_.ToCString());
  GetDlgItem(ID_BTN_TRANSFER)->EnableWindow(FALSE);
}

//combo star list update
void CPageCommander::UpdateCombo()
{
  //combo clear
  m_ctl_self_star.ResetContent();
  m_ctl_fast_star.ResetContent();
  m_ctl_fast_star.AddString("选择目标星球");
  CString info;
  info.Format("主星   【%d:%d:%d】" , 
    GetDataPtr()->GetLoginedAccountPosition().Gala , 
    GetDataPtr()->GetLoginedAccountPosition().Sys , 
    GetDataPtr()->GetLoginedAccountPosition().Pos);
  m_ctl_self_star.AddString(info);
  m_ctl_fast_star.AddString(info);
  m_ctl_self_star.SetItemData(0 , HOMESTAR);
  m_ctl_fast_star.SetItemData(1 , HOMESTAR);
  int cnt = 1;
  for(int i = 1 ; i < STAR_MAX  ; ++i)
  {
    Colonize_Planet_Ram& c = GetDataPtr()->GetColonyStarObj(i - 1);
    if(c.is_exist)
    {      
      PlaniPos p = Index2Pos(c.position);
      info.Format("殖民星%d【%d:%d:%d】" , cnt , p.Gala , p.Sys , p.Pos);
      m_ctl_self_star.AddString(info);
      m_ctl_fast_star.AddString(info);
      m_ctl_self_star.SetItemData(cnt , i);
      m_ctl_fast_star.SetItemData(cnt + 1 , i);
      ++cnt;
    }
  } 
  m_fast_star = 0;
  UpdateData(FALSE);
}

//update ctrls when change self leave star
void CPageCommander::NotifySelfStarChanged(uchar pos)
{
  UpdateData(TRUE);
  assert(pos < STAR_MAX);
  CString info;
  double m , c , h;
  bool   moon , gate;
  PlaniPos position;  

  m        = GetDataPtr()->STAR_RESOURCE(pos).metal_;
  c        = GetDataPtr()->STAR_RESOURCE(pos).crystal_;
  h        = GetDataPtr()->STAR_RESOURCE(pos).diplogen_;
  moon     = GetDataPtr()->STAR_HAS_MOON(pos);
  gate     = GetDataPtr()->STAR_HAS_GATE(pos);
  position = GetDataPtr()->STAR_POSITION(pos);
 
  //text
  TCHAR buff[64];
  GetDlgItem(IDC_STATIC_STAR_METAL)->SetWindowText(AddPointsToNumber(__int64(m) , buff));
  GetDlgItem(IDC_STATIC_STAR_CRYSTAL)->SetWindowText(AddPointsToNumber(__int64(c) , buff));
  GetDlgItem(IDC_STATIC_STAR_DIOP)->SetWindowText(AddPointsToNumber(__int64(h) , buff));
  info.Format("月球：%s" , moon ? _T("有") : _T("无"));
  GetDlgItem(IDC_STATIC_MOON)->SetWindowText(info);
  info.Format("传送门：%s" , gate ? _T("有") : _T("无"));
  GetDlgItem(IDC_STATIC_GATE)->SetWindowText(info);
  GetDlgItem(IDC_STATIC_LEAVE_POS)->SetWindowText(position.ToCString(buff));

  //button
  GetDlgItem(ID_BTN_DESTROYCOLONY)->EnableWindow(pos != HOMESTAR);
  GetDlgItem(ID_BTN_DESTROYCOLONY)->ShowWindow(pos != HOMESTAR ? SW_SHOW : SW_HIDE);

  GetDlgItem(ID_BTN_PRODUCEGATE)->EnableWindow(moon && (!gate));
  GetDlgItem(ID_BTN_PRODUCEGATE)->ShowWindow(moon && (!gate) ? SW_SHOW : SW_HIDE);

  //gate
  GetDlgItem(ID_BTN_TRANSFER)->ShowWindow(moon && gate ? SW_SHOW : SW_HIDE);

  //trade
  GetDlgItem(ID_BTN_TRADE)->ShowWindow(pos == HOMESTAR ? SW_SHOW : SW_HIDE);

  //self star
  self_leave_star_pos_ = position;

  //fleet changed
  UpdateShipsChanged(pos);
}

//star ships changed
void CPageCommander::UpdateShipsChanged(uchar self_star_index)
{
  CString info;
  for(int i = 0 ; i < BOAT_MAX ; ++i)
  { 
    unsigned long pre_n  = atoi(m_list1.GetItemText(i , 1));
    unsigned long avi_n  = GetDataPtr()->STAR_BOAT_NUMBER(i , self_star_index);
    info.Format("%d" , avi_n);
    m_list1.SetItemText(i , 1 , info);

    if(pre_n > avi_n || atoi(m_list1.GetItemText(i , 2)) == 0)
      m_list1.SetItemText(i , 2 , "");
  }
  Notify_Task_Settings_Changed();
}

void CPageCommander::TaskCounterLabelChange()
{
  CString info;
  info.Format("最大任务数：%d ，当前正在执行的任务数：%d ", GetDataPtr()->GetResearchLevel(RESEARCH_COMPUTER) + 1 , task_counter_);
  m_sta_task_number.SetCaption(info);
  if(GetDataPtr()->GetAvaliableTasks() == 0)
  {    
    m_sta_is_max.SetCaption("任务数已经达到最大，不能执行新任务！");
    GetDlgItem(IDOK)->EnableWindow(FALSE);
  }
  else
  {
    //fleet
    FLEET fleet;
    SItem item; 
    item.OwnerID = 0;
    for(int i = 0 ; i < BOAT_MAX ; ++i)
    {
      item.Type = ITEM_TYPE(i);
      item.Num  = atoi(m_list1.GetItemText(i , 2)); 
      fleet.push_back(item);
    }
    GetDlgItem(IDOK)->EnableWindow(war_.GetFleetShipsNumber(fleet) >= 1 && GetDataPtr()->GetAvaliableTasks() > 0);
    m_sta_is_max.SetCaption("");
  }
}

void CPageCommander::Notify_Task_Settings_Changed()
{
  UpdateData(TRUE);
  //position
  PlaniPos pos_l(self_leave_star_pos_);
  PlaniPos pos_t(m_ctl_pos_gala.GetData() , m_ctl_pos_sys.GetData() , m_ctl_pos_pos.GetData() ,  m_target_star_type == 1 , false);
  if(!CheckPosValid(pos_l) || !CheckPosValid(pos_t))
  {
    return;
  }
  Star& s = comm_->GetStar(Pos2Index(pos_t));

  //fleet
  FLEET fleet;
  SItem item; 
  item.OwnerID = 0;
  for(int i = 0 ; i < BOAT_MAX ; ++i)
  {
    item.Type = ITEM_TYPE(i);
    item.Num  = atoi(m_list1.GetItemText(i , 2)); 
    fleet.push_back(item);
  }

  if(war_.GetFleetShipsNumber(fleet) < 1)
  {
    m_task_type = TASK_T_NONE;
  }

  GetDlgItem(IDOK)->EnableWindow(war_.GetFleetShipsNumber(fleet) >= 1 && GetDataPtr()->GetAvaliableTasks() > 0);
  UpdateData(FALSE);  
  
  double transfer = war_.GetFleetCapacity(fleet);
  double fule     = war_.GetFleetOil(fleet , pos_l , pos_t ,  (10 - m_speed_ratio) / 10.0);

  //capacity
  CString info;
  info.Format("%.0f" , transfer);
  m_sta_transfer.SetCaption(info);

  available_transfer_number_ = transfer - fule;
  SetTransferNumber(-1);

  //ships number
  int number   = war_.GetFleetShipsNumber(fleet);
  info.Format("%d" , number);
  m_sta_ships_number.SetCaption(info);

  //fuel
  if(CheckPosValid(pos_t) && CheckPosValid(pos_l))
  {    
    info.Format("%.0f" , fule);
  }
  else
  {
    info = "-";
  }
  m_sta_oil.SetCaption(info);


  //time
  if(CheckShips() && CheckPosValid(pos_l) && CheckPosValid(pos_t))
  {
    ulong s  = war_.GeFleetFlySecond(fleet ,  pos_l , pos_t , (10 - m_speed_ratio) / 10.0 );
    ElapsedTimer t;
    t.Init(s);
    info = t.ToCString();
  }
  else
  {
    info = "-";
  }
  m_sta_time.SetCaption(info);  

  ////hide radios
  //spy
  GetDlgItem(IDC_RADIO1)->ShowWindow((s.type_ == STAR_T_ENEMY && pos_t.bRuin == false) ? SW_SHOW : SW_HIDE);

  //attack
  GetDlgItem(IDC_RADIO2)->ShowWindow((s.type_ == STAR_T_ENEMY && pos_t.bRuin == false) ? SW_SHOW : SW_HIDE);

  //recycle
  // chengph [8/18/2007 CPH]
  GetDlgItem(IDC_RADIO3)->ShowWindow( pos_t.bRuin == true ? SW_SHOW : SW_HIDE);

  //transfer
  GetDlgItem(IDC_RADIO4)->ShowWindow((s.type_ == STAR_T_SELF && pos_t.bRuin == false && !(pos_l == pos_t)) ? SW_SHOW : SW_HIDE);

  //dispatch
  GetDlgItem(IDC_RADIO5)->ShowWindow((s.type_ == STAR_T_SELF && pos_t.bRuin == false && !(pos_l == pos_t)) ? SW_SHOW : SW_HIDE);

  //colonize
  GetDlgItem(IDC_RADIO6)->ShowWindow((s.type_ == STAR_T_NONE && pos_t.bRuin == false) ? SW_SHOW : SW_HIDE);

  //layout
  LayoutTaskRadios();
}

void CPageCommander::LayoutTaskRadios()
{  
  vector<Radio_t> radios;
  radios.push_back(Radio_t(IDC_RADIO1 , GetDlgItem(IDC_RADIO1)->IsWindowVisible() == TRUE));
  radios.push_back(Radio_t(IDC_RADIO2 , GetDlgItem(IDC_RADIO2)->IsWindowVisible() == TRUE));
  radios.push_back(Radio_t(IDC_RADIO3 , GetDlgItem(IDC_RADIO3)->IsWindowVisible() == TRUE));
  radios.push_back(Radio_t(IDC_RADIO4 , GetDlgItem(IDC_RADIO4)->IsWindowVisible() == TRUE));
  radios.push_back(Radio_t(IDC_RADIO5 , GetDlgItem(IDC_RADIO5)->IsWindowVisible() == TRUE));
  radios.push_back(Radio_t(IDC_RADIO6 , GetDlgItem(IDC_RADIO6)->IsWindowVisible() == TRUE));

  ulong x = 260 , y = 270;
  uchar cnt = 0 , pos = 0;

  for(int i = 0 ; i < radios.size() ; ++i)
  {
    if(radios[i].bShow)
    {
      GetDlgItem(radios[i].id)->MoveWindow(x , y , 80 , 16);
      y += 40;
      ++cnt;
      pos = i;
      m_task_type = i;
    }
  }
  if(cnt == 1)
  {
    GetDlgItem(radios[pos].id)->MoveWindow(x , 290 , 80 , 16);
  }
  else if(cnt == 0)
  {
    m_task_type = TASK_T_NONE;
  }
  UpdateData(FALSE);
}

void CPageCommander::InitIDManager()
{
  ID_t tmp;
  for(uchar i = 0 ; i < MAX_ID ; ++i)
  {
    tmp.id_ = i;
    tmp.bUsed = false;
    entry_IDs_.push_back(tmp);
  }
}

bool CPageCommander::CalcTransferRes(FLEET& fleet , PlaniPos& self , PlaniPos& target , Resource& result)
{
  UpdateData(TRUE);
  double fuel    = war_.GetFleetOil(fleet , self , target , (10 - m_speed_ratio) / 10.0);
  double ability = war_.GetFleetCapacity(fleet);
  if(fuel > ability)
  {
    return false;
  }
  double avail = ability - fuel;
  //first HH
  result.diplogen_ = min( min(m_transfer_diop , GetDataPtr()->STAR_RESOURCE(ACTIVE_STAR_INDEX()).diplogen_ - fuel) , avail);
  avail -= result.diplogen_;
  if(avail > 0)
  {
    //then metal
    result.metal_ = min( min(m_transfer_metal , GetDataPtr()->STAR_RESOURCE(ACTIVE_STAR_INDEX()).metal_) , avail);
    avail -= result.metal_;
    if(avail > 0)
    {
      //last crystal
      result.crystal_ = min( min(m_transfer_crystal , GetDataPtr()->STAR_RESOURCE(ACTIVE_STAR_INDEX()).crystal_) , avail);
    }
  }

  return true;
}

//Spy begin out
bool CPageCommander::SpyFleetOut(Star& star , bool isGalaxyCMD)
{
  //ships number assign
  UpdateData(TRUE);
  if(GetDataPtr()->STAR_BOAT_NUMBER(BOAT_SPY_PLANET , ACTIVE_STAR_INDEX()) <= 0)
  {
    AfxMessageBox("没有可用的间谍卫星！");
    return false;
  }
  if( (!isGalaxyCMD) && atoi(m_list1.GetItemText(BOAT_SPY_PLANET , 2)) <= 0 )
  {
    AfxMessageBox("请先部署你的舰队进行间谍，任务失败！");
    return false;
  }  
  if(isGalaxyCMD)
  {
    if(m_default_spy <= 0)
    {
      AfxMessageBox("请先设置默认间谍卫星数目，任务失败！");
      return false;
    }
  }
  uchar index = GetFreeId();
  //COOMAD
  COMMAND_TASK task;
  if(!isGalaxyCMD)
  {
    AssignShips(task.fleet);  
  }
  //if Galaxy command, reset spy number
  else
  {
    task.fleet[BOAT_SPY_PLANET].Num = m_default_spy <= GetDataPtr()->STAR_BOAT_NUMBER(BOAT_SPY_PLANET , ACTIVE_STAR_INDEX()) ? m_default_spy : GetDataPtr()->STAR_BOAT_NUMBER(BOAT_SPY_PLANET , ACTIVE_STAR_INDEX());
  }  
  task.star = &star;
  task.leave_pos = self_leave_star_pos_;

  //oil
  double oil = war_.GetFleetOil(task.fleet , task.leave_pos , task.star->position_ , (10 - m_speed_ratio) / 10.0);
  if(oil > GetDataPtr()->STAR_RESOURCE(ACTIVE_STAR_INDEX()).diplogen_)
  {
    AfxMessageBox("燃料不足，任务失败！");
    return false;
  }

  //sets
  task.index = index;
  task.leave_star_index = ACTIVE_STAR_INDEX();
  task.cycle  = war_.GeFleetFlySecond(task.fleet , task.leave_pos , task.star->position_ , (10 - m_speed_ratio) / 10.0) ;
  task.task   = TASK_T_SPY;  
  task.timer.Init(task.cycle);

  Resource resource;
  if(CalcTransferRes(task.fleet , task.leave_pos , task.star->position_ , resource) == false)
  {
    AfxMessageBox("舰队无足够空间装载燃料，任务失败！");
    return false;
  }  
  task.res.metal_     = resource.metal_;
  task.res.crystal_   = resource.crystal_;
  task.res.diplogen_  = resource.diplogen_;
  GetDataPtr()->DecreaseResource(task.res.metal_ , task.res.crystal_ , task.res.diplogen_ + oil , ACTIVE_STAR_INDEX());
  GetCommander()->Notify_Resource_Changed();
  StarResChanged(task.leave_star_index);

  m_transfer_metal = m_transfer_crystal = m_transfer_diop = 0;
  UpdateData(FALSE);

  task.is_go = true;
  map_tasks_.insert(std::make_pair(index , task));
  //set timer
  SetTimer(index , TIMER_BASE , NULL);
  ++task_counter_;
  GetDataPtr()->ShipsOut(task.fleet , ACTIVE_STAR_INDEX());
  TaskCounterLabelChange(); 
  SetWorkFlag(task_counter_ != 0);
  if(task_counter_ != 0)
  {
    tip_.Format("舰队：%d" , task_counter_);
  }  
  GetCommander()->Notify_Ships_Changed();
  StarFleetChanged(task.leave_star_index);
  UpdateTaskList();
  return true;
}

//Do spy event
void CPageCommander::DoSpy(COMMAND_TASK& task)
{
  Spy_info spy_info;
  spy_info.refresh_minuter_ = comm_->GetRefreshMinutes();
  spy_info.star_ = task.star;  
  spy_info.spynumber_ = task.fleet[BOAT_SPY_PLANET].Num;
  comm_->ReportSpyInfo(spy_info);   
}

void CPageCommander::DoneSpy(COMMAND_TASK& task)
{
  GetDataPtr()->ShipsIn(task.fleet , task.leave_star_index);
  GetCommander()->Notify_Ships_Changed();
  StarFleetChanged(task.leave_star_index);
  GetDataPtr()->IncreaseResource((double)task.res.metal_ , (double)task.res.crystal_ , (double)task.res.diplogen_ , task.leave_star_index);
  GetCommander()->Notify_Resource_Changed();
  StarResChanged(task.leave_star_index);
  --task_counter_;    
  TaskCounterLabelChange(); 
  //all task over
  FleetTaskOverTip();
  SetWorkFlag(task_counter_ != 0);
  if(task_counter_ != 0)
  {
    tip_.Format("舰队：%d" , task_counter_);
  }
}

void CPageCommander::AttackFleetOut(int target_pos)
{
  UpdateData(TRUE);
  CString info;
  int index = GetFreeId();
  Star* s = &comm_->GetStar(target_pos);
  //insert
  COMMAND_TASK task;
  AssignShips(task.fleet);
  task.star = s;
  task.leave_pos = self_leave_star_pos_;
  task.leave_star_index = ACTIVE_STAR_INDEX();

  //oil
  double oil = war_.GetFleetOil(task.fleet , task.leave_pos , task.star->position_ , (10 - m_speed_ratio) / 10.0);
  if(oil > GetDataPtr()->STAR_RESOURCE(ACTIVE_STAR_INDEX()).diplogen_)
  {
    AfxMessageBox("燃料不足，任务失败！");
    return;
  }

  //sets
  task.index = index;
  task.cycle  = war_.GeFleetFlySecond(task.fleet , task.leave_pos , task.star->position_ , (10 - m_speed_ratio) / 10.0 );
  task.task = TASK_T_ATTACK;  
  task.timer.Init(task.cycle);   
  Resource resource;
  if(CalcTransferRes(task.fleet , task.leave_pos , task.star->position_ , resource) == false)
  {
    AfxMessageBox("舰队无足够空间装载燃料，任务失败！");
    return;
  }  
  task.res.metal_     = resource.metal_;
  task.res.crystal_   = resource.crystal_;
  task.res.diplogen_  = resource.diplogen_;
  GetDataPtr()->DecreaseResource(task.res.metal_ , task.res.crystal_ , task.res.diplogen_ + oil , ACTIVE_STAR_INDEX());
  GetCommander()->Notify_Resource_Changed();
  StarResChanged(task.leave_star_index);

  m_transfer_metal = m_transfer_crystal = m_transfer_diop = 0;
  UpdateData(FALSE);

  task.is_go = true;
  map_tasks_.insert(std::make_pair(index , task));
  //set timer
  SetTimer(TIMER_TASKBASE + index , TIMER_BASE , NULL);
  GetDataPtr()->ShipsOut(task.fleet , ACTIVE_STAR_INDEX());
  ++task_counter_;
  TaskCounterLabelChange(); 
  SetWorkFlag(task_counter_ != 0);
  if(task_counter_ != 0)
  {
    tip_.Format("舰队：%d" , task_counter_);
  }
  GetCommander()->Notify_Ships_Changed();
  StarFleetChanged(task.leave_star_index);
  UpdateTaskList();
}

void CPageCommander::DoAttack(COMMAND_TASK& task)
{
  War_info war_info;
  war_info.get_double_res_hero = false;
  FLEET& self_fleet   = task.fleet;
  FLEET& target_fleet = task.star->fleet_and_defense_;
  ShipTechs self_techs;
  self_techs.Weapon = GetDataPtr()->GetResearchLevel(RESEARCH_WEAPON);
  self_techs.Armour = GetDataPtr()->GetResearchLevel(RESEARCH_ARMOUR);
  self_techs.Shield = GetDataPtr()->GetResearchLevel(RESEARCH_SHEILED);
  ShipTechs& target_techs = task.star->ship_techs_;
  Resource r;
  r.metal_ =   task.star->metal_;
  r.crystal_ = task.star->crystal_;
  r.diplogen_ =task.star->diplogen_;

  bool is_elaspe = false;
  if(RandomNumber(100) < (task.star->elpase_) * 100){
    is_elaspe = true;
  }
  BattleRes res;
  CString temp_name;
  temp_name.Format("%d-%d-%d" , task.star->position_.Gala , task.star->position_.Sys , task.star->position_.Pos);
  bool ret = war_.Simulate(1 , GetDataPtr()->GetLoginedAccountName() , temp_name , r , is_elaspe , self_fleet , target_fleet , self_techs , target_techs , res);
  if(ret)
  {
    //self fleet
    self_fleet.resize(T_END);
    std::copy(res.self_fleet_.begin() , res.self_fleet_.end() , self_fleet.begin());

    //target fleet
    target_fleet.resize(T_END);
    std::copy(res.target_fleet_.begin() , res.target_fleet_.end() , target_fleet.begin());

    //plauder
    task.res.metal_ += res.catch_resource_.metal_;
    task.res.crystal_ += res.catch_resource_.crystal_;
    task.res.diplogen_ += res.catch_resource_.diplogen_;

    //loss
    task.loss_res.metal_ = res.loss_resource_.metal_;
    task.loss_res.crystal_ = res.loss_resource_.crystal_;
    task.loss_res.diplogen_ = res.loss_resource_.diplogen_;

    //recycled res
    task.star->recycled_metal_ += res.recycled_resource_.metal_;
    task.star->recycled_crystal_ += res.recycled_resource_.crystal_;

    //update
    comm_->UpdateShowStarInfo();

    //defense resource loss
    task.star->metal_ -= res.catch_resource_.metal_;
    task.star->crystal_ -= res.catch_resource_.crystal_;
    task.star->diplogen_ -= res.catch_resource_.diplogen_;

    //defense rank loss
    task.star->rank_ -= ((res.target_loss_resource_.metal_ + res.target_loss_resource_.crystal_ + res.target_loss_resource_.diplogen_) / 1000.0);
    task.star->rank_ = task.star->rank_ <= 0.0 ? 0.0 : task.star->rank_;

    //is can back
    task.is_can_back = war_.GetFleetShipsNumber(res.self_fleet_) >= 0.5;

    //can not back
    if(!task.is_can_back)
    {
      task.res.crystal_ = task.res.metal_ = task.res.diplogen_ = 0;
    }
    else
    {
      if(task.star->double_res_hero > 0 && (is_elaspe || res.catch_resource_.metal_ >= 1) && (GetDataPtr()->GET_STAR_DOUBLE_RES_HERO() < MAX_DOUBLE_RES_HERO_NUM))
      {
        GetDataPtr()->ADD_STAR_DOUBLE_RES_HERO(task.star->double_res_hero);
        war_info.get_double_res_hero   = true;
        task.star->double_res_hero = 0;
      }
    }
    task.star->UpdateComputerRAM();

    //score change
    double lost_score = (double)(res.loss_resource_.metal_ + res.loss_resource_.crystal_ + res.loss_resource_.diplogen_) / 1000.0;
    GetDataPtr()->UpdateRank(-1.0 * lost_score);
    GetCommander()->Notify_Score_Changed();

    //war info
    war_info.attack_star_index_ = task.star->index_;
    war_info.self_lost_ = res.loss_resource_.metal_ + res.loss_resource_.crystal_ + res.loss_resource_.diplogen_;
    war_info.target_lost_ = res.target_loss_resource_.metal_ + res.target_loss_resource_.crystal_ + res.target_loss_resource_.diplogen_;
    war_info.recycled_res_ = res.recycled_resource_.metal_ + res.recycled_resource_.crystal_;
    strcpy(war_info.battle_report_file_ , res.report_file_);
    comm_->ReportWarInfo(war_info);  
  }  
}

void CPageCommander::DoneAttack(COMMAND_TASK& task)
{
  GetDataPtr()->ShipsIn(task.fleet , task.leave_star_index);
  if(war_.GetFleetShipsNumber(task.fleet) >= 1)
  {    
    GetCommander()->Notify_Ships_Changed();
    StarFleetChanged(task.leave_star_index);  
    GetDataPtr()->IncreaseResource((double)task.res.metal_ , (double)task.res.crystal_ , (double)task.res.diplogen_ , task.leave_star_index);
    GetCommander()->Notify_Resource_Changed();
    StarResChanged(task.leave_star_index);
    comm_->ReportFleetReach(task);
  }
  --task_counter_;   
  TaskCounterLabelChange(); 
  //all task over
  FleetTaskOverTip();
  SetWorkFlag(task_counter_ != 0);
  if(task_counter_ != 0)
  {
    tip_.Format("舰队：%d" , task_counter_);
  }
}

////recycle task
void CPageCommander::RecycleFleetOut(int target_pos)
{
  UpdateData(TRUE);
  CString info;
  int index = GetFreeId();
  Star* s = &comm_->GetStar(target_pos);
  
  //insert
  COMMAND_TASK task;
  AssignShips(task.fleet);
  task.star = s;
  task.leave_pos = self_leave_star_pos_;
  task.leave_star_index = ACTIVE_STAR_INDEX();

  PlaniPos pos_temp = task.star->position_;
  pos_temp.bRuin = true;

  //oil
  double oil = war_.GetFleetOil(task.fleet , task.leave_pos , pos_temp , (10 - m_speed_ratio) / 10.0);
  if(oil > GetDataPtr()->STAR_RESOURCE(ACTIVE_STAR_INDEX()).diplogen_)
  {
    AfxMessageBox("燃料不足，任务失败！");
    return;
  }

  //sets
  task.index = index;
  task.cycle  = war_.GeFleetFlySecond(task.fleet , task.leave_pos , pos_temp , (10 - m_speed_ratio) / 10.0 );
  task.task = TASK_T_RECYCLE;
  task.timer.Init(task.cycle);   
  Resource resource;
  if(CalcTransferRes(task.fleet , task.leave_pos , pos_temp , resource) == false)
  {
    AfxMessageBox("舰队无足够空间装载燃料，任务失败！");
    return;
  }  
  task.res.metal_     = resource.metal_;
  task.res.crystal_   = resource.crystal_;
  task.res.diplogen_  = resource.diplogen_;
  GetDataPtr()->DecreaseResource(task.res.metal_ , task.res.crystal_ , task.res.diplogen_ + oil , ACTIVE_STAR_INDEX());
  GetCommander()->Notify_Resource_Changed();
  StarResChanged(task.leave_star_index);
  m_transfer_metal = m_transfer_crystal = m_transfer_diop = 0;
  UpdateData(FALSE);

  task.is_go = true;
  map_tasks_.insert(std::make_pair(index , task));
  //set timer
  SetTimer(TIMER_TASKBASE + index , TIMER_BASE , NULL);
  GetDataPtr()->ShipsOut(task.fleet , ACTIVE_STAR_INDEX());
  ++task_counter_;
  TaskCounterLabelChange(); 
  SetWorkFlag(task_counter_ != 0);
  if(task_counter_ != 0)
  {
    tip_.Format("舰队：%d" , task_counter_);
  }  
  GetCommander()->Notify_Ships_Changed();
  StarFleetChanged(task.leave_star_index);
  UpdateTaskList();
}

void CPageCommander::DoRecycle(COMMAND_TASK& task)
{
  int64 recycle_capacity = task.fleet[BOAT_RECYCLE].Num * 20000;
  assert(recycle_capacity > 0);
  int64 recycled_metal = task.star->recycled_metal_;
  int64 recycled_crystal = task.star->recycled_crystal_;

  int64 m = 0 , c = 0;
  //capacity enough
  if(recycle_capacity >= recycled_metal + recycled_crystal)
  {
    m = recycled_metal;
    c = recycled_crystal;
  } 
  //capacity not enough
  else
  {
    //M >= C
    if(recycled_crystal <= recycled_metal)
    {
      //CAPACITY <= C
      if(recycle_capacity <= recycled_crystal)
      {
        m = 0;
        c = recycle_capacity;
      }
      //CAPACITY <= M && //CAPACITY > C
      else if(recycle_capacity > recycled_crystal && recycle_capacity <= recycled_metal)
      {
        m = recycle_capacity - recycled_crystal;
        c = recycled_crystal;
      }
      //CAPACITY > M
      else
      {
        m = recycle_capacity - recycled_crystal;
        c = recycled_crystal;
      }
    }
    //M < C
    else
    {
      //CAPACITY <= M
      if(recycle_capacity <= recycled_metal)
      {
        m = 0;
        c = recycle_capacity;
      }    
      //CAPACITY > M && CAPACITY <= C
      else if(recycle_capacity > recycled_metal && recycle_capacity <= recycled_crystal)
      {
        m = 0;
        c = recycled_crystal;
      }
      //CAPACITY > C
      else
      {
        m = recycle_capacity - recycled_crystal;
        c = recycled_crystal;
      }
    }
  }
  assert(m >= 0 && c >= 0);
  assert(m + c <= recycle_capacity);

  m = m < 0 ? 0 : m;
  m = m > recycle_capacity ? recycle_capacity : m;

  c = c < 0 ? 0 : c;
  c = c > recycle_capacity ? recycle_capacity : c;

  //self resource change
  task.res.metal_ += m;
  task.res.crystal_ += c;
  //target recycled resource change
  task.star->recycled_metal_   -= m;
  task.star->recycled_crystal_ -= c;
  comm_->UpdateShowStarInfo();
  task.star->UpdateComputerRAM();
  comm_->ReportRecycleInfo(task);
}

void CPageCommander::DoneRecycle(COMMAND_TASK& task)
{
  GetDataPtr()->ShipsIn(task.fleet , task.leave_star_index);
  GetCommander()->Notify_Ships_Changed();
  StarFleetChanged(task.leave_star_index);
  --task_counter_;   
  TaskCounterLabelChange(); 
  GetDataPtr()->IncreaseResource((double)task.res.metal_ , (double)task.res.crystal_ , (double)task.res.diplogen_ , task.leave_star_index);
  GetCommander()->Notify_Resource_Changed();
  StarResChanged(task.leave_star_index);
  if(war_.GetFleetShipsNumber(task.fleet) > 0)
  {
    comm_->ReportFleetReach(task);
  }
  //all task over
  FleetTaskOverTip();
  SetWorkFlag(task_counter_ != 0);
  if(task_counter_ != 0)
  {
    tip_.Format("舰队：%d" , task_counter_);
  }
}

void CPageCommander::TransferFleetOut(int target_pos  , int tasktype)
{
  UpdateData(TRUE);
  CString info;
  int index = GetFreeId();
  Star* s = &comm_->GetStar(target_pos);
  //insert
  COMMAND_TASK task;
  AssignShips(task.fleet);
  task.star = s;
  task.leave_pos = PlaniPos(self_leave_star_pos_.Gala , self_leave_star_pos_.Sys , self_leave_star_pos_.Pos);
  task.leave_star_index = ACTIVE_STAR_INDEX();

  //oil
  double oil = war_.GetFleetOil(task.fleet , task.leave_pos , task.star->position_ , (10 - m_speed_ratio) / 10.0);
  if(oil > GetDataPtr()->STAR_RESOURCE(ACTIVE_STAR_INDEX()).diplogen_)
  {
    AfxMessageBox("燃料不足，任务失败！");
    return;
  }

  //sets
  task.index = index;
  task.cycle  = war_.GeFleetFlySecond(task.fleet , task.leave_pos , task.star->position_ , (10 - m_speed_ratio) / 10.0 );
  task.task = tasktype;  
  task.timer.Init(task.cycle);   
  Resource resource;
  if(CalcTransferRes(task.fleet , task.leave_pos , task.star->position_ , resource) == false)
  {
    AfxMessageBox("舰队无足够空间装载燃料，任务失败！");
    return;
  }  
  task.res.metal_     = resource.metal_;
  task.res.crystal_   = resource.crystal_;
  task.res.diplogen_  = resource.diplogen_;
  if(tasktype == TASK_T_DISPATCH)
  {
    task.fuel = oil * 0.5;
  }
  GetDataPtr()->DecreaseResource(task.res.metal_ , task.res.crystal_ , task.res.diplogen_ + oil , ACTIVE_STAR_INDEX());
  GetCommander()->Notify_Resource_Changed();
  StarResChanged(task.leave_star_index);
  m_transfer_metal = m_transfer_crystal = m_transfer_diop = 0;
  UpdateData(FALSE);

  task.is_go = true;
  map_tasks_.insert(std::make_pair(index , task));
  //set timer
  SetTimer(TIMER_TASKBASE + index , TIMER_BASE , NULL);
  GetDataPtr()->ShipsOut(task.fleet , ACTIVE_STAR_INDEX());
  ++task_counter_;
  TaskCounterLabelChange(); 
  SetWorkFlag(task_counter_ != 0);
  if(task_counter_ != 0)
  {
    tip_.Format("舰队：%d" , task_counter_);
  }  
  GetCommander()->Notify_Ships_Changed();
  StarFleetChanged(task.leave_star_index);
  UpdateTaskList();
}

void CPageCommander::DoTransfer(COMMAND_TASK& task)
{
  GetDataPtr()->IncreaseResource(task.res.metal_ , task.res.crystal_ , task.res.diplogen_ , GetDataPtr()->GetStarIndexByPos(task.star->position_));
  GetCommander()->Notify_Resource_Changed();
  StarResChanged( GetDataPtr()->GetStarIndexByPos(task.star->position_));
  comm_->ReportTransferInfo(task);
  task.res.metal_ = task.res.crystal_ = task.res.diplogen_ = 0;  
}

void CPageCommander::DoneTransfer(COMMAND_TASK& task)
{
  GetDataPtr()->ShipsIn(task.fleet , task.leave_star_index);
  GetCommander()->Notify_Ships_Changed();
  StarFleetChanged(task.leave_star_index);
  GetDataPtr()->IncreaseResource(task.res.metal_ , task.res.crystal_ , task.res.diplogen_ , task.leave_star_index);
  GetCommander()->Notify_Resource_Changed();
  StarResChanged(task.leave_star_index);
  --task_counter_;   
  TaskCounterLabelChange(); 
  if(war_.GetFleetShipsNumber(task.fleet) > 0)
  {
    comm_->ReportFleetReach(task);
  }
  //all task over
  FleetTaskOverTip();
  SetWorkFlag(task_counter_ != 0);
  if(task_counter_ != 0)
  {
    tip_.Format("舰队：%d" , task_counter_);
  }
}

void CPageCommander::DoneDispatch(COMMAND_TASK& task)
{
  GetDataPtr()->IncreaseResource(task.res.metal_ , task.res.crystal_ , task.res.diplogen_ + task.fuel , GetDataPtr()->GetStarIndexByPos(task.star->position_));
  GetCommander()->Notify_Resource_Changed();
  StarResChanged( GetDataPtr()->GetStarIndexByPos(task.star->position_));
  GetDataPtr()->ShipsIn(task.fleet , GetDataPtr()->GetStarIndexByPos(task.star->position_));
  GetCommander()->Notify_Ships_Changed();  
  StarFleetChanged(GetDataPtr()->GetStarIndexByPos(task.star->position_));
  --task_counter_;   
  TaskCounterLabelChange(); 

  COMMAND_TASK t = task;
  PlaniPos buf_l = t.leave_pos;
  PlaniPos buf_s = t.star->position_;
  
  t.leave_pos        = task.star->position_;
  t.star->position_  = task.leave_pos;
  comm_->ReportFleetReach(t);
  
  t.leave_pos = buf_l;
  t.star->position_ = buf_s;

  //all task over
  FleetTaskOverTip();
  SetWorkFlag(task_counter_ != 0);
  if(task_counter_ != 0)
  {
    tip_.Format("舰队：%d" , task_counter_);
  }
}

void CPageCommander::DoneColony(COMMAND_TASK& task)
{
  //label change
  Star* s = task.star;
  --task_counter_;  
  TaskCounterLabelChange(); 

  //score change
  Resource res = war_.GetFleetWorth(task.fleet);
  double lost_score = (double)(res.metal_ + res.crystal_ + res.diplogen_) / 1000.0;
  GetDataPtr()->UpdateRank(-1.0 * lost_score);
  GetCommander()->Notify_Score_Changed();

  //fail to colonize
  if(GetDataPtr()->GetStarNumber() >= STAR_MAX || s->type_ != STAR_T_NONE)
  {
    comm_->ReportColonyInfo(task , false);
  }
  //successfully
  else
  {
    GetDataPtr()->Colonize(task.star->position_);
    s->type_ = STAR_T_SELF;
    comm_->ReportColonyInfo(task , true);
    task.star->UpdateComputerRAM();
    UpdateCombo();
    UpdateData(FALSE);
  }  
  
  //all task over
  FleetTaskOverTip();
  SetWorkFlag(task_counter_ != 0);

  //finish
  task.is_can_back = false;
  if(task_counter_ != 0)
  {
    tip_.Format("舰队：%d" , task_counter_);
  }  
}

void CPageCommander::CallbackFleetBack(COMMAND_TASK& task)
{
  GetDataPtr()->ShipsIn(task.fleet , task.leave_star_index);
  GetCommander()->Notify_Ships_Changed();
  StarFleetChanged(task.leave_star_index);
  GetDataPtr()->IncreaseResource(task.res.metal_ , task.res.crystal_ , task.res.diplogen_ , task.leave_star_index);
  GetCommander()->Notify_Resource_Changed();
  StarResChanged(task.leave_star_index);
  --task_counter_;   
  TaskCounterLabelChange(); 
  if(war_.GetFleetShipsNumber(task.fleet) > 0)
  {
    COMMAND_TASK t = task;
    PlaniPos buf = t.star->position_;
    t.star->position_  = task.leave_pos;
    comm_->ReportFleetReach(t);
    t.star->position_  = buf;
    
  }
  //all task over
  FleetTaskOverTip();
  SetWorkFlag(task_counter_ != 0);
  if(task_counter_ != 0)
  {
    tip_.Format("舰队：%d" , task_counter_);
  }
}

void CPageCommander::OnTimer(UINT nIDEvent) 
{
  //for gate  
  if(nIDEvent == TIMER_FOR_GATE)
  {
    timer_for_gate_.Go();
    if(timer_for_gate_.IsZero())
    {
      KillTimer(TIMER_FOR_GATE);
      GetDlgItem(ID_BTN_TRANSFER)->SetWindowText("传送...");
      GetDlgItem(ID_BTN_TRANSFER)->EnableWindow(TRUE);
      GetCommander()->Notify_SuperTransferGate_Time_Go("超空传送：准备完毕");
      if(!GetCommander()->IsSilentMode() && GetDlgItem(ID_BTN_TRANSFER)->IsWindowVisible())
       TipWarpper::Instance().ShowTip("传送门已经准备好了");

    }
    else
    {
      GetDlgItem(ID_BTN_TRANSFER)->SetWindowText(timer_for_gate_.ToCString());
      GetDlgItem(ID_BTN_TRANSFER)->EnableWindow(FALSE);
      GetCommander()->Notify_SuperTransferGate_Time_Go("超空传送：" + timer_for_gate_.ToCString());
    }
  }
  //for trade
  else if(nIDEvent == TIMER_FOR_TRADE)
  {
    timer_for_trade_.Go();
    if(timer_for_trade_.IsZero())
    {
      KillTimer(TIMER_FOR_TRADE);
      GetDlgItem(ID_BTN_TRADE)->SetWindowText("交易...");
      GetDlgItem(ID_BTN_TRADE)->EnableWindow(TRUE);
      GetCommander()->Notify_Trade_Center_Time_Go("贸易中心：准备完毕");
      if(!GetCommander()->IsSilentMode())
       TipWarpper::Instance().ShowTip("交易所已经开放了");
    }
    else
    {
      GetDlgItem(ID_BTN_TRADE)->SetWindowText(timer_for_trade_.ToCString());
      GetDlgItem(ID_BTN_TRADE)->EnableWindow(FALSE);
      GetCommander()->Notify_Trade_Center_Time_Go("贸易中心：" + timer_for_trade_.ToCString());
    }
  }
  else if(nIDEvent == TIMER_FOR_ENEMY_ATTACKING)
  {
    if(enemy_task.star != 0)
    {
      enemy_task.timer.Go();
      m_list_enemy.SetItemText(0, 3, enemy_task.timer.ToCString());  
      if(enemy_task.timer.IsZero())
      {
        //kill timer
        KillTimer(TIMER_FOR_ENEMY_ATTACKING); 
        //bombing
        EnemyAttacking();
        //delete
        m_list_enemy.DeleteAllItems();
        //notify to galaxy
        comm_->DoneAttacking();
      }
    }
  }
  //for task
  else
  {
    int index = nIDEvent - TIMER_TASKBASE;
    COMMAND_TASK& task = map_tasks_[index];
    
    task.timer.Go();
    UpdateTimerInfo(index);
    
    //time is over
    if(task.timer.IsZero())
    {
      //kill timer
      KillTimer(index);    
      
      //reach the target star
      if(task.is_go == true)
      {      
        int type = task.task;
        //spy task
        if(type == TASK_T_SPY)
        {
          DoSpy(task);
          task.timer.Init(map_tasks_[index].cycle);
          task.is_go = false;
          SetTimer(index , TIMER_BASE , NULL);
        }    
        //attack task
        else if(type == TASK_T_ATTACK)
        {
          DoAttack(task);
          //can back
          if(task.is_can_back)
          {
            task.timer.Init(task.cycle);
            task.is_go = false;
            SetTimer(index , TIMER_BASE , NULL);
          }
          //can not back
          else
          {
            DoneAttack(task);
            std::map<int , COMMAND_TASK>::iterator itor = map_tasks_.find(index);
            assert(itor != map_tasks_.end());
            map_tasks_.erase(itor); 
            SetIDFlag(index , false);
          }        
        }  
        
        //transfer
        else if(type == TASK_T_TRANSPORT)
        {
          DoTransfer(task);
          task.timer.Init(task.cycle);
          task.is_go = false;
          SetTimer(index , TIMER_BASE , NULL);
        }
        
        //dispatch
        else if(type == TASK_T_DISPATCH)
        {
          DoneDispatch(task);
          std::map<int , COMMAND_TASK>::iterator itor = map_tasks_.find(index);
          assert(itor != map_tasks_.end());
          map_tasks_.erase(itor); 
          SetIDFlag(index , false);
        }
        
        //recycle
        else if(type == TASK_T_RECYCLE)
        {
          DoRecycle(task);
          task.timer.Init(task.cycle);
          task.is_go = false;
          SetTimer(index , TIMER_BASE , NULL);
        }
        
        //colonization
        else if(type == TASK_T_COLONIZE)
        {
          //colonize task fleet can not back, always be distried
          DoneColony(task);
          std::map<int , COMMAND_TASK>::iterator itor = map_tasks_.find(index);
          assert(itor != map_tasks_.end());
          map_tasks_.erase(itor); 
          SetIDFlag(index , false);
        }
        //error type tag
        else
        {
          assert(!"error task type");
        }
        //update list
        UpdateTaskList();
      }   
      
      //fleet return back
      else
      {
        int type = task.task;
        assert(task.is_can_back == true);
        //come back or callback
        if(type == TASK_T_SPY)
        {
          DoneSpy(task);   
        }
        //come back or callback
        else if(type == TASK_T_ATTACK)
        {
          DoneAttack(task);
        }
        //come back or callback
        else if(type == TASK_T_RECYCLE)
        {
          DoneRecycle(task);
        }
        //come back or callback
        else if(type == TASK_T_TRANSPORT)
        {
          DoneTransfer(task);
        }
        //dispatch task call back
        else if(type == TASK_T_DISPATCH)
        {
          CallbackFleetBack(task);
        }
        //colonize task call back
        else if(type == TASK_T_COLONIZE)
        { 
          CallbackFleetBack(task);
        }
        //error task tag
        else
        {
          assert(!"error task type");
        }
        std::map<int , COMMAND_TASK>::iterator itor = map_tasks_.find(index);
        assert(itor != map_tasks_.end());
        map_tasks_.erase(itor); 
        SetIDFlag(index , false); 
        UpdateTaskList();
      }
    }
  }  
  CPageIcon::OnTimer(nIDEvent);
}

void CPageCommander::OnOK() 
{
  UpdateData(TRUE);
  //CHECK not 100% speed
  if(m_speed_ratio != 0)
  {
    CString info;
    info.Format("当前舰队速度为%.0f%%，您仍继续发出舰队吗？" , (10 - m_speed_ratio) * 10.0);
    if(MessageBox(info , "速度警告" , MB_YESNO | MB_ICONWARNING) == IDNO)
    {
      m_speed_ratio = 0;
      UpdateData(FALSE);
      return;
    }
  }
  PlaniPos pos(m_ctl_pos_gala.GetData() , m_ctl_pos_sys.GetData() , m_ctl_pos_pos.GetData());
  if(CheckPosValid(pos) == false)
  {
    AfxMessageBox("目标星球坐标非法！");
    return;
  }
  //attack
  if(m_task_type == TASK_T_ATTACK)
  {
    if(!CanAttack(Pos2Index(pos)))
    {
      AfxMessageBox("攻击任务设置错误！");
      return;
    }
    AttackFleetOut(Pos2Index(pos));
  }
  //spy
  else if(m_task_type == TASK_T_SPY)
  {
    if(GetDataPtr()->STAR_BOAT_NUMBER(BOAT_SPY_PLANET , ACTIVE_STAR_INDEX()) == 0)
    {
      AfxMessageBox("现在没有可用的间谍卫星，任务失败！");
      return;
    }
    if(!CanSpy(Pos2Index(pos)))
    {
      AfxMessageBox("间谍任务设置错误！");
      return;
    }
    Star& s = comm_->GetStar(Pos2Index(pos));
    SpyFleetOut(s , false);
  }  
  //recycle
  else if(m_task_type == TASK_T_RECYCLE)
  {
    if(GetDataPtr()->STAR_BOAT_NUMBER(BOAT_RECYCLE , ACTIVE_STAR_INDEX()) == 0)
    {
      AfxMessageBox("现在没有可用的回收船，任务失败！");
      return;
    }
    Star& s = comm_->GetStar(Pos2Index(pos));
    if(s.recycled_crystal_ + s.recycled_metal_ == 0)
    {
      AfxMessageBox("目标位置无太空废墟可回收！");
      return;
    }
    RecycleFleetOut(Pos2Index(pos));
  }

  //transfer
  else if(m_task_type == TASK_T_TRANSPORT)
  {
    if(!CanTransferOrDispatch(Pos2Index(pos)))
    {
      AfxMessageBox("运输任务设置错误！");
      return;
    }
    TransferFleetOut(Pos2Index(pos) , TASK_T_TRANSPORT);
  }

  //dispatch
  else if(m_task_type == TASK_T_DISPATCH)
  {
    if(!CanTransferOrDispatch(Pos2Index(pos)))
    {
      AfxMessageBox("派遣任务设置错误！");
      return;
    }
    TransferFleetOut(Pos2Index(pos) , TASK_T_DISPATCH);
  }

  //colony
  else if(m_task_type == TASK_T_COLONIZE)
  {
    if(!CanColonize(Pos2Index(pos)))
    {
      AfxMessageBox("殖民任务设置错误！");
      return;
    }
    TransferFleetOut(Pos2Index(pos) , TASK_T_COLONIZE);
  }

  else
  {
    AfxMessageBox("请选择舰队任务！");
    return;
  } 
}

void CPageCommander::Prepare_Attack(int target_pos)
{
  PlaniPos pos = Index2Pos(target_pos);
  GetCommander()->SwitchToPage(this);
  m_ctl_pos_gala.SetData(pos.Gala);
  m_ctl_pos_sys.SetData(pos.Sys);
  m_ctl_pos_pos.SetData(pos.Pos);
  UpdateData(FALSE);  
  m_task_type   = TASK_T_ATTACK;
  Notify_Task_Settings_Changed();    
}

void CPageCommander::Prepare_Recycle(int target_pos)
{
  PlaniPos pos = Index2Pos(target_pos);
  GetCommander()->SwitchToPage(this);
  m_ctl_pos_gala.SetData(pos.Gala);
  m_ctl_pos_sys.SetData(pos.Sys);
  m_ctl_pos_pos.SetData(pos.Pos);
  UpdateData(FALSE); 
  m_task_type   = TASK_T_RECYCLE;
  Notify_Task_Settings_Changed(); 
}

void CPageCommander::Notify_Exit()
{
  if(m_hWnd == NULL)
    return;
  ShipsGoHome();
}

void CPageCommander::ShipsGoHome()
{
  std::map<int , COMMAND_TASK>::iterator iter = map_tasks_.begin();
  for(; iter != map_tasks_.end() ; ++iter)
  {
    GetDataPtr()->ShipsIn((*iter).second.fleet , (*iter).second.leave_star_index);
    //1 / 3 resource can back
    GetDataPtr()->IncreaseResource((double)(*iter).second.res.metal_ / 3.0 , (double)(*iter).second.res.crystal_ / 3.0 , (double)(*iter).second.res.diplogen_ / 3.0 , (*iter).second.leave_star_index);
  }
  GetCommander()->Notify_Resource_Changed();
}

void CPageCommander::Notify_Ships_Changed()
{
  if(m_hWnd == NULL)
    return;
  CString info;
  for(int i = 0 ; i < BOAT_MAX ; ++i)
  { 
    unsigned long pre_n  = atoi(m_list1.GetItemText(i , 1));
    unsigned long avi_n  = GetDataPtr()->STAR_BOAT_NUMBER(i , ACTIVE_STAR_INDEX());
    info.Format("%d" , avi_n);
    m_list1.SetItemText(i , 1 , info);
    //if ships reduce, means ships out
    if(pre_n > avi_n)
    {
      m_list1.SetItemText(i , 2 , "");
      AutoSetTask();
      Notify_Task_Settings_Changed();
    }
  }
}

BOOL CPageCommander::OnSetActive() 
{
	m_default_spy = GetDataPtr()->GetDefaultSpyNumber();  
  UpdateData(FALSE);
	return CPageIcon::OnSetActive();
}

void CPageCommander::OnKillfocusEditDefault() 
{
	UpdateData(TRUE);
  GetDataPtr()->SetDefaultSpyNumber(m_default_spy);		
}

void CPageCommander::OnBtnAll() 
{
	CString info;  
  for(int i = 0 ; i < BOAT_MAX ; ++i)
  {
    if(i != BOAT_SUNPOWER_PLANET)
    {
      info.Format("%s" , m_list1.GetItemText(i , 1));
      if(atoi(info) == 0)
        info = "";
      m_list1.SetItemText(i , 2 , info);
    }    
  }  
  AutoSetTask();
  Notify_Task_Settings_Changed();
}

void CPageCommander::OnBtnNone() 
{
  for(int i = 0 ; i < BOAT_MAX ; ++i)
  {
     m_list1.SetItemText(i , 2 , "");
  }  
  Notify_Task_Settings_Changed();
}

void CPageCommander::OnDblclkListTask(NMHDR* pNMHDR, LRESULT* pResult) 
{
	size_t sel = (int)m_list1.GetFirstSelectedItemPosition() - 1;
  if(sel != BOAT_SUNPOWER_PLANET)
  {
    if( atoi(m_list1.GetItemText(sel , 2)) != 0)
      m_list1.SetItemText(sel , 2 , _T("") );
    else
    {
      if(atoi(m_list1.GetItemText(sel , 1)) != 0)
        m_list1.SetItemText(sel , 2 , m_list1.GetItemText(sel , 1) );
    }  
    AutoSetTask();
    Notify_Task_Settings_Changed();    
  }	
	*pResult = 0;
}

LRESULT CPageCommander::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if(message == WM_LISTCTRL_TEXT_CHANGED)
  {
    AutoSetTask();
    Notify_Task_Settings_Changed();
    return 1;
  }	
  //Edit change
  else if(message == WM_INTEDIT_CHANGED)
  {
    if(UINT(wParam) == IDC_EDIT_GALA || UINT(wParam) == IDC_EDIT_SYS || UINT(wParam) == IDC_EDIT_POS)
      Notify_Task_Settings_Changed();
    return 1;
  }
	return CPageIcon::WindowProc(message, wParam, lParam);
}

void CPageCommander::OnChangeEdit1() 
{
	Notify_Task_Settings_Changed();	
}

void CPageCommander::OnEditchangeComboSpeed() 
{
	Notify_Task_Settings_Changed();		
}

void CPageCommander::OnCloseupComboSpeed() 
{
}

void CPageCommander::OnSelchangeComboSpeed() 
{
	int buf = m_speed_ratio;
  UpdateData(TRUE);
  if(buf != m_speed_ratio)
  {
    Notify_Task_Settings_Changed();	
  }
}

void CPageCommander::UpdateTaskList()
{
  m_list2.SetRedraw(FALSE);
  m_list2.DeleteAllItems();
  std::map<int , COMMAND_TASK>::iterator itor = map_tasks_.begin();

  CString info;
  TCHAR buf[64];
  for(int i = 0 ; i < map_tasks_.size() ; ++i , ++itor)
  {
    //index
    info.Format("%d" , i);
    m_list2.InsertItem(i , info);
    DWORD d = DWORD(&(*itor).second);
    m_list2.SetItemData(i , d);
    
    //task type
    info = ConvertTaskType((*itor).second.is_go , (*itor).second.task);
    m_list2.SetItemText(i , 1 ,  info);
    
    //ships number
    info.Format("%d" , war_.GetFleetShipsNumber((*itor).second.fleet));
    m_list2.SetItemText(i , 2 ,  info);

    CString info , tip;
    for(int b = 0 ; b < BOAT_MAX ; ++b)
    {
      if((*itor).second.fleet[b].Num >= 0.5)
      {
        info.Format("%s %.0f\n" , BOATS_SHORT_NAME[b] , (*itor).second.fleet[b].Num);
        tip += info;
      }      
    }
    tip.TrimRight("\n");
    m_list2.SetItemToolTipText(i, 2, tip);
    
    //leave position
    info.Format("%s" , (*itor).second.leave_pos.ToCString(buf));
    m_list2.SetItemText(i , 3 ,  info);  
    
    //target position
    info.Format("%s" , (*itor).second.star->position_.ToCString(buf));
    m_list2.SetItemText(i , 4 ,  info); 

    //resource
    char buff1[64];
    char buff2[64];
    char buff3[64];
    info.Format("金属：%s 水晶：%s 重氢：%s" , AddPointsToNumber((*itor).second.res.metal_ , buff1) , 
      AddPointsToNumber((*itor).second.res.crystal_ , buff2) , AddPointsToNumber((*itor).second.res.diplogen_ , buff3) );
    m_list2.SetItemText(i , 5 ,  info); 
    
    //time
    m_list2.SetItemText(i , 6 ,  (*itor).second.timer.ToCString());
  }
  m_list2.SetRedraw(TRUE);
}

void CPageCommander::UpdateTimerInfo(uchar task_index)
{
  for(int i = 0 ; i < m_list2.GetItemCount() ; ++i)
  {
    DWORD d = m_list2.GetItemData(i);
    COMMAND_TASK* task = (COMMAND_TASK*)d;
    if(task != 0 && task->index == task_index)
    {
      COMMAND_TASK& task = map_tasks_[task_index];      
      m_list2.SetItemText(i , 6 , task.timer.ToCString());
      return;
    }
  }
}

void CPageCommander::OnRclickListTaskList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POSITION pos = m_list2.GetFirstSelectedItemPosition();
  //not sel
  if(pos == NULL) return;
  int sel = int(pos) - 1;  
  if(sel < 0 || sel >= map_tasks_.size()) return;

  DWORD d = m_list2.GetItemData(sel);
  COMMAND_TASK* task = (COMMAND_TASK*)d;
  if(task->is_go == false)
    return;

  //less than 2 seconds, can not call back
  if(task->timer.GetLeftSecond() < 2)
    return;

	CPoint pt;
  GetCursorPos(&pt);
  menu_list.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN,pt.x , pt.y , this , NULL);	
	*pResult = 0;	
}

void CPageCommander::OnMenuFleetCallback() 
{
	POSITION pos = m_list2.GetFirstSelectedItemPosition();
  //not sel
  if(pos == NULL) return;
  int sel = int(pos) - 1;  
  if(sel < 0 || sel >= map_tasks_.size()) return;

  DWORD d = m_list2.GetItemData(sel);
  COMMAND_TASK* task = (COMMAND_TASK*)d;
  if(task->is_go == false)
    return;

  //less than 2 seconds, can not call back
  if(task->timer.GetLeftSecond() <= 3)
    return;

  task->is_go = false;
  double e_s = task->timer.GetElapseSecond();
  task->timer.Init(e_s);
  UpdateTaskList();
}

void CPageCommander::Notify_Technics_LevelUp()
{
  assert(task_counter_ >= 0);
  GetDataPtr()->UpdateAvaliableTasks(task_counter_);
  TaskCounterLabelChange(); 
  for(int i = 0 ; i < BOAT_MAX ; ++i)
  {
    CString info , tip;
    info.Format("速度：%d" , kernel_.GetShipSpeed(ITEM_TYPE(i) , 0));
    tip += info;

    info.Format("\n装载：%d" , SHIP_TRANSFER_CAPACITY[i] );
    tip += info;

    m_list1.SetItemToolTipText(i, 0, tip);
  }
}

void CPageCommander::OnCloseupCombo1() 
{
}

void CPageCommander::OnSelchangeCombo1() 
{	
  int buf = m_self_star;
  UpdateData(TRUE);
  if(buf != m_self_star)
  {
    //target position change
    //PlaniPos pos = GetDataPtr()->STAR_POSITION(ACTIVE_STAR_INDEX());
    //m_ctl_pos_gala.SetData(pos.Gala);
    //m_ctl_pos_sys.SetData(pos.Sys);
    //m_ctl_pos_pos.SetData(pos.Pos);
    //UpdateData(FALSE); 
    NotifySelfStarChanged(ACTIVE_STAR_INDEX());	       
  }  
  UpdateData(TRUE);
}

void CPageCommander::OnCloseupComboFaststar() 
{
}

void CPageCommander::OnSelchangeComboFaststar() 
{
	UpdateData(TRUE);
  if(m_fast_star < 1)
    return;
  assert(m_fast_star < STAR_MAX + 1);
  PlaniPos position;  
  if(m_fast_star == HOMESTAR + 1)
  {
    position = GetDataPtr()->GetLoginedAccountPosition();
  }
  else
  {
    DWORD index = m_ctl_fast_star.GetItemData(m_fast_star);
    assert(index >= 0 && index < STAR_MAX);
    Colonize_Planet_Ram& colony = GetDataPtr()->GetColonyStarObj(index - 1);
    position = Index2Pos(colony.position);
  }
  //target position
  m_ctl_pos_gala.SetData(position.Gala);
  m_ctl_pos_sys.SetData(position.Sys);
  m_ctl_pos_pos.SetData(position.Pos);
  UpdateData(FALSE);
  Notify_Task_Settings_Changed();  	
  m_fast_star = 0;
  UpdateData(FALSE);	
}

bool CPageCommander::CanAttack(int star_index)
{
  Star & s = comm_->GetStar(star_index);
  return (CheckShips() && s.type_ == STAR_T_ENEMY);
}

bool CPageCommander::CanSpy(int star_index)
{
  Star & s = comm_->GetStar(star_index);
  return (CheckSpyPlanet() && s.type_ == STAR_T_ENEMY);
}

bool CPageCommander::CanTransferOrDispatch(int star_index)
{
  Star & s = comm_->GetStar(star_index);
  return CheckShips() && s.type_ == STAR_T_SELF;
}

bool CPageCommander::CanColonize(int star_index)
{
  Star & s = comm_->GetStar(star_index);
  return CheckColony() && GetDataPtr()->GetStarNumber() < STAR_MAX && s.type_ == STAR_T_NONE;
}

void CPageCommander::OnCloseupCombo2() 
{
}

void CPageCommander::OnSelchangeCombo2() 
{
  Notify_Task_Settings_Changed();	
}

void CPageCommander::OnBtnMetalMax() 
{
  SetTransferNumber(RESOURCE_METAL);  
}

void CPageCommander::OnBtnCrystalMax() 
{
  SetTransferNumber(RESOURCE_CRYSTAL);  
}

void CPageCommander::OnBtnDiopMax() 
{
  SetTransferNumber(RESOURCE_DIPLOGEN);  
}

void CPageCommander::OnChangeEditCrystal() 
{
  UpdateData(TRUE);  
  CString info;
  GetDlgItem(IDC_EDIT_CRYSTAL)->GetWindowText(info);
  if(info.IsEmpty())
    GetDlgItem(IDC_EDIT_CRYSTAL)->SetWindowText("0");
  UpdateData(FALSE);  
  SetTransferNumber(-1);  
}

void CPageCommander::OnChangeEditDiop() 
{
  UpdateData(TRUE);  
  CString info;
  GetDlgItem(IDC_EDIT_DIOP)->GetWindowText(info);
  if(info.IsEmpty())
    GetDlgItem(IDC_EDIT_DIOP)->SetWindowText("0");
  UpdateData(FALSE);  
  SetTransferNumber(-1);  
}

void CPageCommander::OnChangeEditMetal() 
{
  UpdateData(TRUE);  
  CString info;
  GetDlgItem(IDC_EDIT_METAL)->GetWindowText(info);
  if(info.IsEmpty())
    GetDlgItem(IDC_EDIT_METAL)->SetWindowText("0");
  UpdateData(FALSE); 
  SetTransferNumber(-1);  
}


void CPageCommander::OnBtnAllResource() 
{	
  SetTransferNumber(RESOURCE_MAX);  
}

void CPageCommander::SetTransferNumber(int type)
{
  UpdateData(TRUE);
  double fuel = atof(m_sta_oil.GetCaption());
  //fuel >= available_transfer_number_
  if(available_transfer_number_ <= 0)
  {
    m_transfer_diop = m_transfer_metal = m_transfer_crystal = 0L;
  }
  else
  {
    Resource r = GetDataPtr()->STAR_RESOURCE(ACTIVE_STAR_INDEX());
    if(type == RESOURCE_METAL){
      double t = available_transfer_number_ - (m_transfer_crystal + m_transfer_diop);
      t = t < 0 ? 0 : t;
      m_transfer_metal   =  min(r.metal_ , t);
    }
    
    else if(type == RESOURCE_CRYSTAL){
      m_transfer_crystal = 0;
      double t = available_transfer_number_ - (m_transfer_metal + m_transfer_diop);
      t = t < 0 ? 0 : t;
      m_transfer_crystal =  min(r.crystal_ , t);
    }
    
    else if(type == RESOURCE_DIPLOGEN){
      double t = available_transfer_number_ - (m_transfer_metal + m_transfer_crystal);
      t = t < 0 ? 0 : t;
      m_transfer_diop    =  min(r.diplogen_ - fuel , t);
    }
    
    else if(type == RESOURCE_MAX){
      double reserve_r = 0.0;
      //first HH
      m_transfer_diop = min(available_transfer_number_ , r.diplogen_ - fuel);
      reserve_r = available_transfer_number_ - m_transfer_diop;
      if(reserve_r > 0)
      {
        //then metal
        m_transfer_metal = min(reserve_r , r.metal_);
        reserve_r = available_transfer_number_ - m_transfer_diop - m_transfer_metal;
        if(reserve_r > 0)
        { 
          //last crystal
          m_transfer_crystal = min(reserve_r , r.crystal_);
        }
      }
    }    
  }  
  
  UpdateData(FALSE);	  
  double l = available_transfer_number_ - (m_transfer_metal + m_transfer_crystal + m_transfer_diop);
  if(l >= 0)
    m_sta_left_res.SetTextColor(RGB(0 , 255 , 0));
  else
    m_sta_left_res.SetTextColor(RGB(255 , 0 , 0));
  
  CString info;
  info.Format("%.0f" , l);
  m_sta_left_res.SetCaption(info);
}

void CPageCommander::Notify_Resource_Changed()
{
  UpdateData(TRUE);
  if(m_self_star < 0 || m_self_star >= STAR_MAX)
    return;
  //target position change
  int pos = ACTIVE_STAR_INDEX();
  assert(pos < STAR_MAX);
  CString info;
  double m = GetDataPtr()->STAR_RESOURCE(pos).metal_;
  double c = GetDataPtr()->STAR_RESOURCE(pos).crystal_;
  double h = GetDataPtr()->STAR_RESOURCE(pos).diplogen_;

  //text
  TCHAR buff[64];
  GetDlgItem(IDC_STATIC_STAR_METAL)->SetWindowText(AddPointsToNumber(__int64(m) , buff));
  GetDlgItem(IDC_STATIC_STAR_CRYSTAL)->SetWindowText(AddPointsToNumber(__int64(c) , buff));
  GetDlgItem(IDC_STATIC_STAR_DIOP)->SetWindowText(AddPointsToNumber(__int64(h) , buff));
}

void CPageCommander::OnBtnDestroycolony() 
{
	UpdateData(TRUE);
  assert(ACTIVE_STAR_INDEX() < STAR_MAX);
  if(ACTIVE_STAR_INDEX() == HOMESTAR)
  {
    AfxMessageBox("主星不能放弃！");
    return;
  }

  if(HasFleetBehavior(GetDataPtr()->STAR_POSITION(ACTIVE_STAR_INDEX())))
  {
    AfxMessageBox("该殖民星现有舰队活动，不能放弃！");
    return;
  }

  if(MessageBox("此操作会导致该星上的舰队和资源全部消失，你确定要放弃该殖民星吗？" , "警告" , MB_YESNO | MB_ICONWARNING) == IDNO)
  {
    return;
  }  

  //galaxy refresh
  Star& s = comm_->GetStar(Pos2Index(GetDataPtr()->STAR_POSITION(ACTIVE_STAR_INDEX())));
  assert(s.type_ == STAR_T_SELF);
  s.type_ = STAR_T_NONE;
  ////score change
  //fleet
  FLEET fleet;
  SItem item;
  item.OwnerID = 0;
  for(int i = 0 ; i < BOAT_MAX ; ++i)
  {
    item.Type = ITEM_TYPE(i);
    item.Num  = GetDataPtr()->STAR_BOAT_NUMBER(i , ACTIVE_STAR_INDEX());
    fleet.push_back(item);
  }
  Resource worth = war_.GetFleetWorth(fleet);
  GetDataPtr()->UpdateRank(-1.0 * (double)(worth.crystal_ + worth.diplogen_ + worth.metal_) / 1000.0);    
  //gate lost
  if(GetDataPtr()->STAR_HAS_GATE(ACTIVE_STAR_INDEX()))
  {
    GetDataPtr()->UpdateRank(-1.0 * 8000000 / 1000.0);   
  }
  GetCommander()->Notify_Score_Changed();

  //destroy
  GetDataPtr()->DestroyStar(ACTIVE_STAR_INDEX());	
  UpdateCombo();
  m_self_star = HOMESTAR;
  UpdateData(FALSE);
  NotifySelfStarChanged(HOMESTAR);   
}

bool CPageCommander::HasFleetBehavior(const PlaniPos& pos)
{
  std::map<int , COMMAND_TASK>::iterator itor = map_tasks_.begin();
  for( ; itor != map_tasks_.end() ; ++itor)
  {
    if((*itor).second.leave_pos == pos || (*itor).second.star->position_ == pos)
    {
      return true;
    }
  }
  return false;
}

void CPageCommander::OnBtnProducemoon() 
{
	UpdateData(TRUE);
  assert(ACTIVE_STAR_INDEX() < STAR_MAX);

  if(MessageBox("此操作会摧毁你所选的所有舰队，以最多20%的概率造月球，确定继续吗？" , "警告" , MB_YESNO | MB_ICONWARNING) == IDNO)
  {
    return;
  }  

  //fleet disappear
  FLEET fleet;
  fleet.resize(BOAT_MAX);
  AssignShips(fleet , true);
  GetDataPtr()->ShipsOut(fleet , ACTIVE_STAR_INDEX() , true);
  GetCommander()->Notify_Ships_Changed(fleet[BOAT_SUNPOWER_PLANET].Num > 0.5);

  //score change
  Resource worth = war_.GetFleetWorth(fleet);
  GetDataPtr()->UpdateRank(-1.0 * (double)(worth.crystal_ + worth.diplogen_ + worth.metal_) / 1000.0);    
  GetCommander()->Notify_Score_Changed();

  //ruin produce
  Star& s = comm_->GetStar(Pos2Index(GetDataPtr()->STAR_POSITION(ACTIVE_STAR_INDEX())));
  s.recycled_crystal_ += 0.3 * worth.crystal_;
  s.recycled_metal_   += 0.3 * worth.metal_;
  comm_->UpdateShowStarInfo();

  //result
  UINT percent = UINT((0.3 * worth.crystal_ + 0.3 * worth.metal_) / 100000);
  percent = (percent > 20 ? 20 : percent);
  CString info;
  if(RandomNumber(100) < percent)
  {
    //moon created
    GetDataPtr()->PRODUCE_MOON(ACTIVE_STAR_INDEX());
    NotifySelfStarChanged(ACTIVE_STAR_INDEX());
    info.Format("恭喜，您已经以 %d%% 概率在此星球成功造月"  , percent);
    MessageBox(info , "造月成功" , MB_OK | MB_ICONINFORMATION);
  }    	
  else
  {
    info.Format("很遗憾，您以 %d%% 概率在此星球造月失败！"  , percent);
    MessageBox(info , "造月失败" ,  MB_OK | MB_ICONINFORMATION);
  }
}

void CPageCommander::OnBtnProducegate() 
{
	UpdateData(TRUE);
  assert(ACTIVE_STAR_INDEX() < STAR_MAX);
  if(!GetDataPtr()->STAR_HAS_MOON(ACTIVE_STAR_INDEX()))
  {
    AfxMessageBox("此星球现无月球，不能造传送门");
    return;
  }	
  if(GetDataPtr()->STAR_HAS_GATE(ACTIVE_STAR_INDEX()))
  {
    AfxMessageBox("此星球现有传送门，不用再造");
    return;
  }	
  
  if(MessageBox("造门将花费200W金属 400W晶体 200W 重氢，继续吗？" , "警告" , MB_YESNO | MB_ICONWARNING) == IDNO)
  {
    return;
  } 

  Resource r = GetDataPtr()->STAR_RESOURCE(ACTIVE_STAR_INDEX());
  if(r.metal_ < 2000000 || r.crystal_ < 4000000 || r.diplogen_ < 2000000)
  {
    AfxMessageBox("此星资源不够造门！");
    return;
  }
  
  GetDataPtr()->DecreaseResource(2000000 , 4000000 , 2000000 , ACTIVE_STAR_INDEX());
  GetCommander()->Notify_Resource_Changed();
  GetCommander()->Notify_Resource_Consumed(8000000);
  GetDataPtr()->PRODUCE_GATE(ACTIVE_STAR_INDEX());
  NotifySelfStarChanged(ACTIVE_STAR_INDEX());
}

void CPageCommander::StarResChanged(uchar index)
{
  assert(index < STAR_MAX);
  if(ACTIVE_STAR_INDEX() != index)
    return;
  NotifySelfStarChanged(index);
}

void CPageCommander::StarFleetChanged(uchar index)
{
  assert(index < STAR_MAX);
  if(ACTIVE_STAR_INDEX() != index)
    return;
  UpdateShipsChanged(index);
}

void CPageCommander::OnBtnTransfer() 
{
  UpdateData(TRUE);
  vector<STAR_ITEM_T> tmp;
  for(int i = 0 ; i < STAR_MAX ; ++i)
  {
    if(GetDataPtr()->STAR_IS_EXISTED(i) && GetDataPtr()->STAR_HAS_GATE(i) && ACTIVE_STAR_INDEX() != i)
    {
      tmp.push_back(STAR_ITEM_T(i , GetDataPtr()->STAR_POSITION(i)));
    }
  }   

  //call dialog
	CSuperGateTransferDlg dlg(tmp);	
  if(dlg.DoModal() == IDOK)
  {
    if(dlg.m_selected_index_ != 0xff)
    {
      uchar out_p = ACTIVE_STAR_INDEX();
      uchar in_p  = dlg.m_selected_index_;
      FLEET fleet;
      fleet.resize(BOAT_MAX);
      AssignShips(fleet);
      GetDataPtr()->ShipsOut(fleet , out_p);
      GetDataPtr()->ShipsIn(fleet , in_p);
      GetCommander()->Notify_Ships_Changed();
      StarFleetChanged(out_p);
      StarFleetChanged(in_p);
      //SET timer, 1 s , 60 minutes
      timer_for_gate_.Init(3600);
      SetTimer(TIMER_FOR_GATE , 1000 , NULL);
      GetDlgItem(ID_BTN_TRANSFER)->SetWindowText(timer_for_gate_.ToCString());
      GetDlgItem(ID_BTN_TRANSFER)->EnableWindow(FALSE);
    }
  }
}

BOOL CPageCommander::PreTranslateMessage(MSG* pMsg) 
{
  if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
  {
    if(GetDlgItem(IDOK)->IsWindowEnabled() && GetDlgItem(IDOK)->IsWindowVisible())
      OnOK();
  }
	return CPageIcon::PreTranslateMessage(pMsg);
}

void CPageCommander::OnBtnTrade() 
{
	CTradeCenterDlg dlg(GetDataPtr() , this);
  dlg.DoModal();	
  
  //SET timer 1 s, 60 minutes
  timer_for_trade_.Init(3600);
  SetTimer(TIMER_FOR_TRADE , 1000 , NULL);
  GetDlgItem(ID_BTN_TRADE)->SetWindowText(timer_for_trade_.ToCString());
  GetDlgItem(ID_BTN_TRADE)->EnableWindow(FALSE);
}

void CPageCommander::NotifyFinishedTrade()
{
  GetCommander()->Notify_Resource_Changed();
  GetCommander()->Notify_Money_Change();
}

void CPageCommander::FleetTaskOverTip()
{
  if(task_counter_ == 0 && (!GetCommander()->IsSilentMode()))
    TipWarpper::Instance().ShowTip("舰队任务完成");
}

void CPageCommander::OnBtnAllWar() 
{
	CString info;  
  for(int i = 0 ; i < BOAT_MAX ; ++i)
  {
    if(i == BOAT_LIGHT_FIGHTER || i == BOAT_HEAVY_FIGHTER || i == BOAT_CRUISER || i == BOAT_WARSHIP || i == BOAT_DESTROYER || i == BOAT_BOMBER)
    {
      info.Format("%s" , m_list1.GetItemText(i , 1));
      if(atoi(info) == 0)
        info = "";
      m_list1.SetItemText(i , 2 , info);
    }    
  }  
  AutoSetTask();
  Notify_Task_Settings_Changed();	
}

void CPageCommander::OnBtnAllBanjia() 
{
	CString info;  
  for(int i = 0 ; i < BOAT_MAX ; ++i)
  {
    if(i == BOAT_LIGHT_FIGHTER || i == BOAT_HEAVY_FIGHTER || i == BOAT_CRUISER || 
       i == BOAT_WARSHIP || i == BOAT_DESTROYER || i == BOAT_SMALL_SCUTTER || i == BOAT_LARGE_SCUTTER)
    {
      info.Format("%s" , m_list1.GetItemText(i , 1));
      if(atoi(info) == 0)
        info = "";
      m_list1.SetItemText(i , 2 , info);
    }    
  }  
  AutoSetTask();
  Notify_Task_Settings_Changed();		
}

void CPageCommander::EnemyAttackComing(Star& s)
{
  CString info;
  char buf[128];
  info.Format("%s" , s.position_.ToCString(buf));
  m_list_enemy.InsertItem(0 , info);
  
  info.Format("%s" , GetDataPtr()->GetLoginedAccountPosition().ToCString(buf));
  m_list_enemy.SetItemText(0 , 1 , info);
  
  FLEET f(s.fleet_and_defense_);
  //following fleet do not go
  f[T_SAT].Num  = 0.0;
  f[T_KOLO].Num = 0.0;
  f[T_REC].Num  = 0.0;
  f[T_SPIO].Num = 0.0;
  for(int d = T_RAK ; d < T_END ; ++d)
  {
    f[d].Num = 0.0;
  }

  //ships number
  info.Format("数量：%d，组成（" , war_.GetFleetShipsNumber(f));  
  CString tip , temp;
  for(int b = 0 ; b < BOAT_MAX ; ++b)
  {
    if(f[b].Num >= 0.5)
    {
      temp.Format("%s %.0f " , BOATS_SHORT_NAME[b] , f[b].Num);
      tip += temp;
    }      
  }
  tip.TrimRight();
  tip += "）";
  m_list_enemy.SetItemText(0, 2, info + tip);  
  
  enemy_task.is_can_back = true;
  enemy_task.star = &s;
  enemy_task.cycle = war_.GeFleetFlySecond(f , s.position_ , GetDataPtr()->GetLoginedAccountPosition() , 1.0 );
  if(enemy_task.cycle < 60)  enemy_task.cycle = 60;
#ifdef USE_FOR_TEST_ATTACK
  enemy_task.cycle = 30;
#endif
  enemy_task.timer.Init(enemy_task.cycle);
  m_list_enemy.SetItemText(0, 3, enemy_task.timer.ToCString());  
  SetTimer(TIMER_FOR_ENEMY_ATTACKING , 1000 , NULL);
  TipWarpper::Instance().ShowTip("敌军来侵！" , 1);
}

void CPageCommander::EnemyAttacking()
{
  War_info war_info;
  war_info.get_double_res_hero = false;
  //attack
  FLEET attack_fleet(enemy_task.star->fleet_and_defense_);
  //following fleet do not go
  attack_fleet[T_SAT].Num  = 0.0;
  attack_fleet[T_KOLO].Num = 0.0;
  attack_fleet[T_REC].Num  = 0.0;
  attack_fleet[T_SPIO].Num = 0.0;
  for(int d = T_RAK ; d < T_END ; ++d)
  {
    attack_fleet[d].Num = 0.0;
  }
  //defender
  FLEET  defense_fleet ;
  //fleet
  for(int b = BOAT_START ; b < BOAT_MAX ; ++b)
  {
    SItem item;
    item.Type = (ITEM_TYPE)b;
    item.Num  = GetDataPtr()->GetBoatNumber(b);
    defense_fleet.push_back(item);
  }
  //defense
  for( b = DEFENSE_START ; b < DEFENSE_MAX ; ++b)
  {
    SItem item;
    item.Type = (ITEM_TYPE)(b + BOAT_MAX);
    item.Num  = GetDataPtr()->GET_STAR_DEFENSE(b);
    defense_fleet.push_back(item);
  }
  ShipTechs defense_techs;
  defense_techs.Weapon = GetDataPtr()->GetResearchLevel(RESEARCH_WEAPON);
  defense_techs.Armour = GetDataPtr()->GetResearchLevel(RESEARCH_ARMOUR);
  defense_techs.Shield = GetDataPtr()->GetResearchLevel(RESEARCH_SHEILED);
  ShipTechs& attack_techs = enemy_task.star->ship_techs_;
  Resource r = GetDataPtr()->STAR_RESOURCE(HOMESTAR);
  BattleRes res;
  CString temp_name;
  temp_name.Format("%d-%d-%d" , enemy_task.star->position_.Gala , enemy_task.star->position_.Sys , enemy_task.star->position_.Pos);
  bool ret = war_.Simulate(1 , temp_name , GetDataPtr()->GetLoginedAccountName() , r , false , attack_fleet , defense_fleet , attack_techs , defense_techs , res , true);
  if(ret)
  {
    //defender fleet
    defense_fleet.clear();
    defense_fleet.resize(T_END);
    std::copy(res.target_fleet_.begin() , res.target_fleet_.end() , defense_fleet.begin());
    //fleet
    for(int b = BOAT_START ; b < BOAT_MAX ; ++b)
    {
      GetDataPtr()->SetBoatNumber(b , (ulong)defense_fleet[b].Num);
    }
    //defense
    for( b = DEFENSE_START ; b < DEFENSE_MAX ; ++b)
    {
      GetDataPtr()->SET_STAR_DEFENSE(b , (ulong)defense_fleet[b + BOAT_MAX].Num);
    }
    GetCommander()->Notify_Ships_Changed(true);
    GetCommander()->Notify_Defenses_Changed();

    //attack fleet
    attack_fleet.resize(T_END);
    std::copy(res.self_fleet_.begin() , res.self_fleet_.end() , attack_fleet.begin());  
    for(b = BOAT_START ; b < BOAT_MAX ; ++b)
    {
      if(b != BOAT_SUNPOWER_PLANET && b != BOAT_CONOLY && b != BOAT_RECYCLE && b != BOAT_SPY_PLANET)
        enemy_task.star->fleet_and_defense_[b].Num = attack_fleet[b].Num;
    }

    //defender loss
    double defense_lost_metal = res.target_loss_resource_.metal_;
    double defense_lost_crys  = res.target_loss_resource_.crystal_;
    double defense_lost_diru  = res.target_loss_resource_.diplogen_;
    double defense_lost_rank  = -1.0 * (defense_lost_metal + defense_lost_crys + defense_lost_diru ) / 1000.0;
    GetDataPtr()->UpdateRank(defense_lost_rank);
    GetCommander()->Notify_Score_Changed();
    //resource loss
    GetDataPtr()->DecreaseResource(res.catch_resource_.metal_ , res.catch_resource_.crystal_ , res.catch_resource_.diplogen_);
    GetCommander()->Notify_Resource_Changed();

    //attacker loss
    double attacker_lost_metal = res.loss_resource_.metal_;
    double attacker_lost_crys  = res.loss_resource_.crystal_;
    double attacker_lost_diru  = res.loss_resource_.diplogen_;
    double attacker_lost_rank  = (attacker_lost_metal + attacker_lost_crys + attacker_lost_diru ) / 1000.0;
    enemy_task.star->rank_    -= attacker_lost_rank;
    enemy_task.star->metal_ += res.catch_resource_.metal_;
    enemy_task.star->crystal_ += res.catch_resource_.crystal_;
    enemy_task.star->diplogen_ += res.catch_resource_.diplogen_;

    //recycled
    Star& defense_star = comm_->GetStar(Pos2Index(GetDataPtr()->GetLoginedAccountPosition()));
    defense_star.recycled_metal_   += 0.3 * (defense_lost_metal + attacker_lost_metal);
    defense_star.recycled_crystal_ += 0.3 * (defense_lost_crys + attacker_lost_crys);

    //update
    comm_->UpdateShowStarInfo();
    defense_star.UpdateComputerRAM();

    //war info
    war_info.attack_star_index_ = enemy_task.star->index_;
    war_info.self_lost_ = res.loss_resource_.metal_ + res.loss_resource_.crystal_ + res.loss_resource_.diplogen_;
    war_info.target_lost_ = res.target_loss_resource_.metal_ + res.target_loss_resource_.crystal_ + res.target_loss_resource_.diplogen_;

    war_info.recycled_res_ = res.recycled_resource_.metal_ + res.recycled_resource_.crystal_;
    strcpy(war_info.battle_report_file_ , res.report_file_);
    comm_->ReportWarInfo(war_info);  
  }  
  enemy_task.star->is_fleet_out = false;
  enemy_task.star = 0;
}
