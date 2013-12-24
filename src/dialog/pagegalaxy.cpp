// pagegalaxy.cpp : implementation file
//

#include "stdafx.h"
#include "..\XGame\xgame.h"
#include "pagegalaxy.h"
#include "communication.h"
#include "XGameDlg.h"
#include "TipWarpper.h"
#include "GameLogger.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageGalaxy dialog

CPageGalaxy::CPageGalaxy(UINT iconID /*= NULL*/ , CWnd* pParent /*=NULL*/)
: CPageIcon(CPageGalaxy::IDD , iconID)
{
  //{{AFX_DATA_INIT(CPageGalaxy)
	//}}AFX_DATA_INIT
  menu.LoadMenu(IDR_GALAXY_MENU);
  refresh_time_ = 30L;
  is_attacking_player = false;
}

void CPageGalaxy::DoDataExchange(CDataExchange* pDX)
{
  CPageIcon::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CPageGalaxy)
	DDX_Control(pDX, IDC_EDIT_SHOW_SYS, m_ctl_sys);
	DDX_Control(pDX, IDC_EDIT_SHOW_GALA, m_ctl_gala);
  DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageGalaxy, CPageIcon)
//{{AFX_MSG_MAP(CPageGalaxy)
ON_WM_SIZE()
ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnRclickList1)
ON_COMMAND(ID_MENU_GALAXY_ATTACK, OnMenuGalaxyAttack)
ON_COMMAND(ID_MENU_GALAXY_SPY, OnMenuGalaxySpy)
ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
ON_WM_TIMER()
ON_WM_DESTROY()
ON_BN_CLICKED(IDC_BTN_GALA_LEFT, OnBtnGalaLeft)
ON_BN_CLICKED(IDC_BTN_GALA_RIGHT, OnBtnGalaRight)
ON_BN_CLICKED(IDC_BTN_SYS_LEFT, OnBtnSysLeft)
ON_BN_CLICKED(IDC_BTN_SYS_RIGHT, OnBtnSysRight)
ON_BN_CLICKED(IDC_BTN_SHOW, OnBtnShow)
ON_BN_CLICKED(IDC_BTN_SPYS, OnBtnSpys)
	ON_COMMAND(ID_MENU_GALAXY_VIEW_RANK, OnMenuGalaxyViewRank)
	ON_COMMAND(ID_MENU_GALAXY_RECYCLE, OnMenuGalaxyRecycle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////


void CPageGalaxy::OnSize(UINT nType, int cx, int cy) 
{
  CPageIcon::OnSize(nType, cx, cy);
  if(IsWindow(m_list))
    m_list.MoveWindow(0 , 0 , cx , cy);		
}

BOOL CPageGalaxy::OnInitDialog() 
{
  CPageIcon::OnInitDialog();
  CreateImageList();  
  set_refresh_mimutes();
  update_timer_.Init(refresh_time_ * 60);  
  GetDlgItem(IDC_STATIC_TIME)->SetWindowText(update_timer_.ToCString());
  int delays = 1200 / (1 + GetDataPtr()->GetLoginedAccountComputerRank());
#ifdef USE_FOR_TEST_ATTACK
  delays = 30;
#endif
  SetTimer(TIMER_FOR_GALAXY, 1000 , NULL);
  if(GetDataPtr()->CAN_COMPUTER_ATTACK())
    SetTimer(TIMER_FOR_CHECK_ATTACKING , delays * 1000 , NULL);
  m_list.SetImageList(&m_ImageList , LVSIL_SMALL );
  InitDlgCtrls();  
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageGalaxy::CreateImageList()
{
  BOOL	bRetValue = FALSE;
  HICON	hIcon = NULL;
  
  // Create image list
  bRetValue = m_ImageList.Create(33, 33, ILC_COLOR32 | ILC_MASK , 10 , 1);
  ASSERT(bRetValue == TRUE);
  // Add some icons
  hIcon = AfxGetApp()->LoadIcon(IDI_ICON1_STAR);
  m_ImageList.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_ICON2_STAR);
  m_ImageList.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_ICON3_STAR);
  m_ImageList.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_ICON4_STAR);
  m_ImageList.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_ICON5_STAR);
  m_ImageList.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_ICON6_STAR);
  m_ImageList.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_ICON7_STAR);
  m_ImageList.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_ICON8_STAR);
  m_ImageList.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_ICON9_STAR);
  m_ImageList.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_ICON10_STAR);
  m_ImageList.Add(hIcon);
  
}

void CPageGalaxy::InitDlgCtrls()
{
  m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);	
  m_list.InsertColumn(0 , "位置" , LVCFMT_LEFT , 80);
  m_list.InsertColumn(1 , "名称" , LVCFMT_CENTER , 150);
  m_list.InsertColumn(2 , "积分排名" , LVCFMT_CENTER , 100);
  m_list.InsertColumn(3 , "战场废墟" , LVCFMT_CENTER , 400);  

  //edit
  m_ctl_gala.SetRange(1 , MAX_GALAXY_GALA);
  m_ctl_sys.SetRange(1 , MAX_GALAXY_SYS);
  
#ifdef LISTCTRL_USING_MY_FONT
  LOGFONT lf;
  memset(&lf, 0, sizeof(LOGFONT));
  lf.lfHeight = 14;
  strcpy(lf.lfFaceName, "新宋体");
  font_list.CreateFontIndirect(&lf);
  m_list.SetFont(&font_list, TRUE);
#endif
  
  m_list.SetBkColor(RGB(55 , 79 , 112));
  m_list.SetTextBkColor(RGB(55 , 79 , 112));
  m_list.SetTextColor(RGB(231 , 233 ,234));    

  //create
  CreatStars();  
}

void CPageGalaxy::CreatStars()
{   
  for(int i = 0 ; i < MAX_GALAXY_GALA * MAX_GALAXY_SYS * MAX_GALAXY_POS ; ++i)
  {    
    Star star(GetDataPtr() , i);
    entry_starts_.push_back(star);
  }  
  //update sort table
  UpdateSortTable();  
}

void CPageGalaxy::UpdateSortTable()
{
  //sort table
  Sort_Table_t node;
  enrty_sorted_stars.clear();
  for(size_t i = 0 ; i < entry_starts_.size() ; ++i)
  {
    Star& s = entry_starts_[i];
    //enemy star
    if(s.type_ == STAR_T_ENEMY)
    {
      node.rank = s.rank_;
      node.name = s.name_;
      node.position = Pos2Index(s.position_);
      node.fleet = s.UpdateFleetNumber();
      enrty_sorted_stars.push_back(node);
    }
    //self star
    else if(s.type_ == STAR_T_SELF)
    {
      if(s.position_ == GetDataPtr()->STAR_POSITION(HOMESTAR))
      {
        node.rank     = GetDataPtr()->GetLoginedAccountRank();
        node.name     = GetDataPtr()->GetLoginedAccountName();
        node.position = Pos2Index(GetDataPtr()->STAR_POSITION(HOMESTAR));
        node.fleet    = comm_->GetAllFleetNumber();
        enrty_sorted_stars.push_back(node);
      }
    }
  }
  //display
  ShowStars(GetDataPtr()->GetLoginedAccountPosition().Gala , GetDataPtr()->GetLoginedAccountPosition().Sys);
}

void CPageGalaxy::ShowStars(uchar gala , ushort sys)
{
  m_list.SetRedraw(FALSE);
  m_list.DeleteAllItems();
  vector<Star*> result;
  SearchSysStars(gala , sys , result);
  vector<Sort_Table_t> sort_stars = enrty_sorted_stars;
  sort(sort_stars.begin() , sort_stars.end() , greater_by_rank_functor<Sort_Table_t>() );
  for(int i = 0 ; i < result.size() ; ++i)
  {
    Star* star = result[i];
    //pos and name
    CString info;
    info.Format("%d" , star->position_.Pos);
    m_list.InsertItem(i , info , star->bitmap_index_);
    DWORD d = star->index_;
    m_list.SetItemData(i , d);    
    if(star->is_npc_player)
    {
      m_list.SetItemText(i , 1 , star->name_);    
    }
    else
    {
      m_list.SetItemText(i , 1 , Type2Name(star->type_ , star->position_));  
    }      
    
    //rank
    vector<Sort_Table_t>::iterator itor = 
      find_if(sort_stars.begin() , 
              sort_stars.end()   , 
              binder2nd< match_func<Sort_Table_t , int> >(match_func<Sort_Table_t , int>() , Pos2Index(star->position_)) );
    info = "";
    if(itor != sort_stars.end() && star->type_ != STAR_T_NONE)
    {
      ulong r = distance(sort_stars.begin() , itor) + 1;
      info.Format("%d" , r);
    }
    m_list.SetItemText(i , 2 , info);

    //recycled resource
    char buf1[64];
    char buf2[64];
    if(star->recycled_metal_ > 0 || star->recycled_crystal_ >0)
      info.Format("金属：%s 晶体：%s" , AddPointsToNumber(star->recycled_metal_ , buf1) , AddPointsToNumber(star->recycled_crystal_ , buf2) );
    else
      info = "";
    m_list.SetItemText(i , 3 , info);
  }
  m_ctl_gala.SetData(gala);
  m_ctl_sys.SetData(sys);
  m_list.SetRedraw(TRUE);
}

void CPageGalaxy::OnTimer(UINT nIDEvent) 
{
  if(nIDEvent == TIMER_FOR_GALAXY)
  {
    //go one second    
    update_timer_.Go();    
    if(update_timer_.IsZero())
    {
      KillTimer(TIMER_FOR_GALAXY);
      set_refresh_mimutes();
      update_timer_.Init(refresh_time_ * 60); 
      for(int i = 0 ; i < entry_starts_.size() ; ++i)
      {
        entry_starts_[i].Update();      
      }
      
      //update sort table
      UpdateSortTable();
      
      GetCommander()->Notify_Galaxy_Update();
      SetTimer(TIMER_FOR_GALAXY , 1000 , NULL);      

      //log
      CGameLogger::Instance().Log("galaxy update complete.");
    }  
    GetCommander()->Notify_Galaxy_UpdateTimer_Go();
    GetDlgItem(IDC_STATIC_TIME)->SetWindowText(update_timer_.ToCString());
  }
  //attack player
  else if(nIDEvent == TIMER_FOR_CHECK_ATTACKING && GetDataPtr()->CAN_COMPUTER_ATTACK())
  {
    ulong id = RandomNumber(entry_starts_.size() - 1);
    Star& s = entry_starts_[id];
    int ratio = 75;
#ifdef USE_FOR_TEST_ATTACK
    ratio = 100;
#endif
    if(s.type_ == STAR_T_ENEMY && s.fleet_number_ > 0 && (RandomNumber(100) < ratio) && is_attacking_player == false && s.is_fleet_out == false)
    {
      s.is_fleet_out = true;
      is_attacking_player = true;
      comm_->AttackPlayer(s);      
    }
  }
  CPageIcon::OnTimer(nIDEvent);
}

void CPageGalaxy::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
  POSITION pos = m_list.GetFirstSelectedItemPosition();
  //not sel
  if(pos == NULL) return;
  int sel = int(pos) - 1;  
  DWORD index = m_list.GetItemData(sel);
  assert(index < entry_starts_.size());
  Star& star = entry_starts_[index];
  if(star.type_ == STAR_T_NONE)
  {
    return;
  }
  
  //spy satellites > 0 && task > 0
  menu.GetSubMenu(0)->EnableMenuItem(ID_MENU_GALAXY_SPY ,    
    (GetDataPtr()->GetAvaliableTasks() > 0 && star.type_ == STAR_T_ENEMY)  ? MF_ENABLED : MF_GRAYED);
  menu.GetSubMenu(0)->EnableMenuItem(ID_MENU_GALAXY_ATTACK , 
    GetDataPtr()->GetAvaliableTasks() > 0 && star.type_ == STAR_T_ENEMY ? MF_ENABLED : MF_GRAYED);
  menu.GetSubMenu(0)->EnableMenuItem(ID_MENU_GALAXY_RECYCLE , 
    GetDataPtr()->GetAvaliableTasks() > 0 && star.recycled_crystal_ + star.recycled_metal_ > 0 ? MF_ENABLED : MF_GRAYED);
  menu.GetSubMenu(0)->SetDefaultItem(ID_MENU_GALAXY_SPY);
  CPoint pt;
  GetCursorPos(&pt);
  menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN,pt.x , pt.y , this , NULL);	
  *pResult = 0;	
}

void CPageGalaxy::OnMenuGalaxyAttack() 
{
  if(GetDataPtr()->GetAvaliableTasks() > 0 )
  {
    POSITION pos = m_list.GetFirstSelectedItemPosition();
    //not sel
    if(pos == NULL) return;
    int sel = int(pos) - 1;  
    PlaniPos p;
    p.Gala = m_ctl_gala.GetData();
    p.Sys  = m_ctl_sys.GetData();
    p.Pos  = sel + 1;  
    Star& s = entry_starts_[Pos2Index(p)];
    if(s.type_ == STAR_T_ENEMY)
      comm_->PrepareAttack(Pos2Index(p));
  }  
  else
  {
    AfxMessageBox("任务已达到最大！");
  }
}

void CPageGalaxy::OnMenuGalaxySpy() 
{
  POSITION pos = m_list.GetFirstSelectedItemPosition();
  //not sel
  if(pos == NULL) return;
  int sel = int(pos) - 1; 
  PlaniPos p;
  p.Gala = m_ctl_gala.GetData();
  p.Sys  = m_ctl_sys.GetData();
  p.Pos  = sel + 1;  
  Star& s = entry_starts_[Pos2Index(p)];
  if(s.type_ == STAR_T_ENEMY)
  {
    if(GetDataPtr()->GetAvaliableTasks() <= 0)
    { 
      AfxMessageBox("舰队任务已达到最大！");
      return;
    }
    comm_->Spy(s);
  }  
}

Star& CPageGalaxy::GetStar(int index)
{
  assert(index >= 0 && index <entry_starts_.size());
  return entry_starts_[index];
}

Star& CPageGalaxy::GetStar(const PlaniPos& pos)
{
  return GetStar(Pos2Index(pos));
}

void CPageGalaxy::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{  
  OnMenuGalaxySpy();	
  *pResult = 0;
}

void CPageGalaxy::OnDestroy() 
{
  KillTimer(TIMER_FOR_GALAXY);
  KillTimer(TIMER_FOR_CHECK_ATTACKING);
  CPageIcon::OnDestroy();
}


void CPageGalaxy::UpdateShowStarInfo()
{
  ShowStars(m_ctl_gala.GetData() , m_ctl_sys.GetData());	
}

void CPageGalaxy::Notify_Technics_LevelUp()
{  
}

void CPageGalaxy::OnBtnGalaLeft() 
{
  m_ctl_gala.SetData(m_ctl_gala.GetData() - 1);
  ShowStars(m_ctl_gala.GetData() , m_ctl_sys.GetData());
}

void CPageGalaxy::OnBtnGalaRight() 
{
  m_ctl_gala.SetData(m_ctl_gala.GetData() + 1);
  ShowStars(m_ctl_gala.GetData() , m_ctl_sys.GetData());	
}

void CPageGalaxy::OnBtnSysLeft() 
{
  m_ctl_sys.SetData(m_ctl_sys.GetData() - 1);
  ShowStars(m_ctl_gala.GetData() , m_ctl_sys.GetData());
  
}

void CPageGalaxy::OnBtnSysRight() 
{
  m_ctl_sys.SetData(m_ctl_sys.GetData() + 1);
  ShowStars(m_ctl_gala.GetData() , m_ctl_sys.GetData());  
}

void CPageGalaxy::OnBtnShow() 
{
  ShowStars(m_ctl_gala.GetData() , m_ctl_sys.GetData());	
}

BOOL CPageGalaxy::OnSetActive() 
{
  return CPageIcon::OnSetActive();
}

BOOL CPageGalaxy::PreTranslateMessage(MSG* pMsg) 
{
  if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
  {
    GetDlgItem(IDC_BTN_SHOW)->SetFocus();
    OnBtnShow();
    return 0;
  }	
  return CPageIcon::PreTranslateMessage(pMsg);
}

void CPageGalaxy::OnBtnSpys() 
{
  PlaniPos p;
  p.Gala = m_ctl_gala.GetData();
  p.Sys  = m_ctl_sys.GetData();
  for(int i = 1 ; i <= MAX_GALAXY_POS ; ++i)
  {
    p.Pos  = i ;
    Star& s = entry_starts_[Pos2Index(p)];
    if(s.type_ == STAR_T_ENEMY)
    {
      if(GetDataPtr()->GetAvaliableTasks() <= 0)
      { 
        return;
      }
      if(comm_->Spy(s) == false)
      {
        return;
      }
    }  
  }  
}

void CPageGalaxy::OnMenuGalaxyViewRank() 
{
	POSITION pos = m_list.GetFirstSelectedItemPosition();
  //not sel
  if(pos == NULL) return;
  int sel = int(pos) - 1; 
  PlaniPos p;
  p.Gala = m_ctl_gala.GetData();
  p.Sys  = m_ctl_sys.GetData();
  p.Pos  = sel + 1;
  Star& s = entry_starts_[Pos2Index(p)];
  if(s.type_ != STAR_T_NONE)
  {
    comm_->ViewRank(p , s.type_ == STAR_T_SELF);
  }  
}

void CPageGalaxy::OnMenuGalaxyRecycle() 
{
	if(GetDataPtr()->GetAvaliableTasks() > 0 )
  {
    POSITION pos = m_list.GetFirstSelectedItemPosition();
    //not sel
    if(pos == NULL) return;
    int sel = int(pos) - 1;  
    PlaniPos p;
    p.Gala = m_ctl_gala.GetData();
    p.Sys  = m_ctl_sys.GetData();
    p.Pos  = sel + 1;  
    Star& s = entry_starts_[Pos2Index(p)];
    if(s.recycled_crystal_ + s.recycled_metal_ > 0)
      comm_->PrepareRecycle(Pos2Index(p));
  }  
  else
  {
    AfxMessageBox("任务已达到最大！");
  }	
}
