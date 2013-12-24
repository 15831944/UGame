#include "stdafx.h"
#include "xgame.h"
#include "pagebuildings.h"
#include "GameDataRecorder.h"
#include "XGameDlg.h"
#include "BuildingsKeeper.h"
#include "TipWarpper.h"

using namespace std;

CPageBuildings::CPageBuildings(UINT iconID /*=NULL*/ , CWnd* pParent /*=NULL*/)
	: CPageIcon(CPageBuildings::IDD , iconID)
{
	//{{AFX_DATA_INIT(CPageBuildings)
	//}}AFX_DATA_INIT
  font_ctrls_text.CreateFont(
    22,                        // nHeight
    0,                         // nWidth
    0,                         // nEscapement
    0,                         // nOrientation
    TRUE,                      // nWeight
    FALSE,                     // bItalic
    FALSE,                     // bUnderline
    0,                         // cStrikeOut
    ANSI_CHARSET,              // nCharSet
    OUT_DEFAULT_PRECIS,        // nOutPrecision
    CLIP_DEFAULT_PRECIS,       // nClipPrecision
    DEFAULT_QUALITY,           // nQuality
    DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
    "Arial Black");        // lpszFacename
  cur_building_index = -1;
  buff_cosume_metal = 0.0;
  buff_cosume_cryst = 0.0;
  buff_cosume_diplo = 0.0;
  is_building_ = false;
}

CPageBuildings::~CPageBuildings()
{
}


void CPageBuildings::DoDataExchange(CDataExchange* pDX)
{
	CPageIcon::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageBuildings)
	DDX_Control(pDX, IDC_LIST_PROGRESS, m_ProgressList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageBuildings, CPageIcon)
	//{{AFX_MSG_MAP(CPageBuildings)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BTN_BUILD, OnBtnBuild)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnCancel)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PROGRESS, OnClickListProgress)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_PROGRESS, OnRclickListProgress)
	//}}AFX_MSG_MAP
  ON_NOTIFY(HTMLLIST_SELECTIONCHANGED, IDC_MYLIST , OnMyList_SelectionChanged)
  ON_NOTIFY(HTMLLIST_LBUTTONDBLCLICK,  IDC_MYLIST , OnMyList_LButtonDClick)
END_MESSAGE_MAP()

BOOL CPageBuildings::OnInitDialog() 
{
	CPageIcon::OnInitDialog();	
  CreateImageList();  
  InitDlgCtrls();  
  //1 minute
  SetTimer(TIMER_PRODUCE , 60 * 1000 , NULL);
  //adjust offline resource
  //AdjustOfflineResource();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageBuildings::OnMyList_LButtonDClick(NMHDR* pNMHDR, LRESULT*)
{
  GetCommander()->SwitchToPage(PAGE_DOCUMENTS);
  comm_->ShowDocument(0 , m_list.GetSelectedItem());
}

void CPageBuildings::Notify_Init()
{
  AdjustOfflineResource();
}

void CPageBuildings::AdjustOfflineResource()
{
  double m = 0.0;
  double c = 0.0;
  double d = 0.0;
  for(int i = 0 ; i < building_keeper_->Size() ; ++i)
  {
    m += (Buildings_Entry(i)->ProduceMinal()    * Buildings_Entry(i)->GetProducePercent() * Building::GetTotalProducePercent());
    c += (Buildings_Entry(i)->ProduceCrystal()  * Buildings_Entry(i)->GetProducePercent() * Building::GetTotalProducePercent());
    d += (Buildings_Entry(i)->ProduceDiplogen() * Buildings_Entry(i)->GetProducePercent() * Building::GetTotalProducePercent());
  }
  GetDataPtr()->AdjustOfflineResource(m , c , d);
  GetCommander()->Notify_Resource_Changed();
}

void CPageBuildings::CreateImageList()
{
  BOOL	bRetValue = FALSE;
	HICON	hIcon = NULL;

	// Create image list
	bRetValue = m_ImageList.Create(120, 120, ILC_COLOR32 | ILC_MASK , 8 , 1);
	ASSERT(bRetValue == TRUE);

  m_ImageList_small.Create(68, 68, ILC_COLOR32 | ILC_MASK , 8 , 1);

	// Add some icons
	hIcon = AfxGetApp()->LoadIcon(IDI_ICON_MINAL_FACTORY);
	m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);
  // Add some icons
	hIcon = AfxGetApp()->LoadIcon(IDI_ICON_CRYCALFACTORY);
	m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);
  // Add some icons
	hIcon = AfxGetApp()->LoadIcon(IDI_ICON_DIPOFACTORY);
	m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_ICON_SUNPOWERFACTORY);
	m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_ICON_ROBERTFACTORY);
	m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_ICON_LABFACTORY);
	m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_ICON_BOATYARD);
	m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);

  hIcon = AfxGetApp()->LoadIcon(IDI_ICON_NATITEFACTORY);
	m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);  
}

//init ctrls
void CPageBuildings::InitDlgCtrls()
{
  CRect rect; 
  GetClientRect(&rect);
  m_list.SetBKColor(RGB(55 , 77 , 112));
  m_list.SetSelectedColor(RGB(60 , 80 , 150));
  m_list.Create(this,CRect(0 ,0 , rect.Width() , rect.Height() - 180),IDC_MYLIST);
  GetDlgItem(IDC_STA_INFO)->MoveWindow(0 , rect.bottom - 148 , rect.Width() , 1);
  m_list.SetImageList(&m_ImageList);
  m_list.SetExtendedStyle(HTMLLIST_STYLE_GRIDLINES | HTMLLIST_STYLE_IMAGES);
  GetDlgItem(IDC_BTN_BUILD)->EnableWindow(FALSE);
  GetDlgItem(IDC_STA_BUILD_TIMER)->SetFont(&font_ctrls_text);
  int sel = int(m_ProgressList.GetFirstSelectedItemPosition()) - 1;
  GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(sel >= 0 && sel < entry_tasks_.size());
  m_ProgressList.SetExtendedStyle(m_ProgressList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

  m_ProgressList.InsertColumn(0,"编号",LVCFMT_CENTER,40);
	m_ProgressList.InsertColumn(1,"任务内容",LVCFMT_CENTER,120);
	m_ProgressList.InsertColumn(2,"任务进度",LVCFMT_CENTER,140);
	
  InitList();		
}

//refresh listctrl
void CPageBuildings::InitList()
{
  SetItemInfo(true);	
}

void CPageBuildings::UpdateItemText()
{
  SetItemInfo(false);	
}

void CPageBuildings::SetItemInfo(bool bInit)
{
  for(int i = 0 ; i < building_keeper_->Size() ; ++i)
  {
    CString info;
    CString op;
    ElapsedTimer t(Buildings_Entry(i)->GetUpgradeTime());
    
    CString color = HIGH_LIGHT_COLOR;    
    if(!Buildings_Entry(i)->CanLevelUp())
    {
      color = GRAY_COLOR;
    }     
    if(Buildings_Entry(i)->CanLevelUp() && !IsResourceEnough(i))
    {
      color = NO_RESOURCE_COLOR;
    }
    if(GetDataPtr()->STAR_USED_SIZE() >= GetDataPtr()->STAR_CIRU())
    {
      color = NO_SIZE_COLOR;
      op = "，星球方圆已满";
    }    
    if(Buildings_Entry(i)->CanLevelUp() && is_building_ && i == entry_tasks_[0])
    {
      op = "，正在升级...";
    }
    
    CString need;
    if(!Buildings_Entry(i)->CanLevelUp())
    {
      need = _T("（升级需求：") + Buildings_Entry(i)->GetCanlevelString() + "）";
    }    
    char buff1[64];
    char buff2[64];
    char buff3[64];
    
    info.Format("<font color=%s><b>%s(等级：%2d %s)</font><font color=#E6EBFB></b><br><br>%s<br><br>金属：<b>%s  </b> 晶体：<b>%s  </b> 重氢：<b>%s</b><br><br>升级时间：<b>%d小时 %02d分 %02d秒 %s</b></font>", 
      color , Buildings_Entry(i)->GetName() , Buildings_Entry(i)->GetLevel() , op ,  Buildings_Entry(i)->GetSimpleDisp() , AddPointsToNumber(Buildings_Entry(i)->GetUpgradeMinal() , buff1) ,
      AddPointsToNumber(Buildings_Entry(i)->GetUpgradeCrystal() , buff2) , AddPointsToNumber(Buildings_Entry(i)->GetUpgradeDiplogen() , buff3) , t.GetHour() , t.GetMinute() , t.GetSecond() , need);
    
    if(bInit)
      m_list.InsertItem(info , Buildings_Entry(i)->GetIndex() , HTML_TEXT , 120);
    else
      m_list.SetItemText(i , info );
  }		
}

void CPageBuildings::OnSize(UINT nType, int cx, int cy) 
{
	CPageIcon::OnSize(nType, cx, cy);
}

void CPageBuildings::OnMyList_SelectionChanged(NMHDR* pNMHDR, LRESULT*)
{  
	NM_HTMLLISTCTRL *pListNMHDr = (NM_HTMLLISTCTRL*) pNMHDR;
	if(pListNMHDr->nItemNo != NONE_SELECTED && m_list.GetSelectedItem() != NONE_SELECTED)
	{
    GetDlgItem(IDC_BTN_BUILD)->EnableWindow(Buildings_Entry(pListNMHDr->nItemNo)->CanLevelUp());      
	}
  else
  {
    GetDlgItem(IDC_BTN_BUILD)->EnableWindow(FALSE);
  }
}

void CPageBuildings::OnBtnBuild() 
{	
  //max 256 tasks
  if(entry_tasks_.size() > 256)
    return;
  int sel = m_list.GetSelectedItem();	
  assert(sel >= FACTORY_BUILDING_START && sel < FACTORY_BUILDINGS_MAX);
  entry_tasks_.push_back(sel);
  CString info;
  int index = m_ProgressList.GetItemCount();
  info.Format("%02d" , index);
  m_ProgressList.InsertItem(index , info);
  m_ProgressList.SetItemText(index , 1 , Buildings_Entry(sel)->GetName());
  m_ProgressList.SetItemText(index , 2 , "0.000%");
  UpdateIndex();
  if(entry_tasks_.size() == 1)
  {
    StartOneTask();
  }
}

void CPageBuildings::UpdateIndex()
{
  CString info;
  for(int i = 0 ; i < entry_tasks_.size() ; ++i)
  {
    info.Format("%02d" , i);
    m_ProgressList.SetItemText(i , 0 , info);
  }
}

//start building
void CPageBuildings::StartOneTask()
{
  int sel = entry_tasks_[0];
  assert(sel >= 0 && sel < building_keeper_->Size());

  building_timer_.Init(Buildings_Entry(sel)->GetUpgradeTime());  
  GetDlgItem(IDC_STA_BUILD_TIMER)->SetWindowText(building_timer_.ToCString());
  
  //wait resource
  if(IsResourceEnough(sel) == FALSE || Buildings_Entry(sel)->CanLevelUp() == false)
    return ;  

  //set 1 second timer
  SetTimer(TIMER_BUILDING_LEVEL_UP , TIMER_BASE , NULL);
  cur_building_index = sel;

  //buffer resource for cancel
  buff_cosume_metal = Buildings_Entry(sel)->GetUpgradeMinal();
  buff_cosume_cryst = Buildings_Entry(sel)->GetUpgradeCrystal();
  buff_cosume_diplo = Buildings_Entry(sel)->GetUpgradeDiplogen();

  GetDataPtr()->DecreaseResource(Buildings_Entry(sel)->GetUpgradeMinal() , Buildings_Entry(sel)->GetUpgradeCrystal() , Buildings_Entry(sel)->GetUpgradeDiplogen());
  is_building_ = true;
  SetWorkFlag(true);
  tip_ = "建筑：0%%";
  GetCommander()->Notify_Resource_Changed();
  UpdateItemText();
}

void CPageBuildings::OnTimer(UINT nIDEvent) 
{
  //building
	if(nIDEvent == TIMER_BUILDING_LEVEL_UP)
  {
    building_timer_.Go();
    GetDlgItem(IDC_STA_BUILD_TIMER)->SetWindowText(building_timer_.ToCString());
    double r = (building_timer_.GetElapseSecond() / (building_timer_.GetLeftSecond() + building_timer_.GetElapseSecond()));
    tip_.Format("建筑：%0.0f%%" , r * 100);
    CString s;
    s.Format("%.3f%%" , r * 100.0);
    m_ProgressList.SetItemText(0 , 2 , s);
    if(building_timer_.IsZero())
    {
      KillTimer(TIMER_BUILDING_LEVEL_UP);
      EndOneTask();

      //start again
      if(entry_tasks_.size() > 0)
      {
        StartOneTask();
      }
      //finish all task
      else
      {
        GetDlgItem(IDC_STA_BUILD_TIMER)->SetWindowText("");        
      }
    }
  }	
  //produce, 1 minute
  else if(nIDEvent == TIMER_PRODUCE)
  {
    double m = 0.0;
    double c = 0.0;
    double d = 0.0;
    for(int i = 0 ; i < building_keeper_->Size() ; ++i)
    {
      m += Buildings_Entry(i)->ProduceMinal();
      c += Buildings_Entry(i)->ProduceCrystal();
      d += Buildings_Entry(i)->ProduceDiplogen();
    }
    GetDataPtr()->IncreaseResource(m , c , d);    
    GetCommander()->Notify_Resource_Changed();
    UpdateItemText();
  }
	CPageIcon::OnTimer(nIDEvent);
}

//end building
void CPageBuildings::EndOneTask()
{
  assert(entry_tasks_.size() > 0);
  Buildings_Entry(entry_tasks_[0])->LevelUp();
  Buildings_Entry(entry_tasks_[0])->Save();
  is_building_ = false;
  SetWorkFlag(false);
  UpdateItemText();
  GetCommander()->Notify_Buildings_LevelUp();  
  GetCommander()->Notify_Resource_Consumed(buff_cosume_metal + buff_cosume_cryst + buff_cosume_diplo);
  entry_tasks_.erase(entry_tasks_.begin());
  m_ProgressList.DeleteItem(0);  
  UpdateIndex();
  int sel = int(m_ProgressList.GetFirstSelectedItemPosition()) - 1;
  GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(sel >= 0 && sel < entry_tasks_.size());	
  if(entry_tasks_.empty() && (!GetCommander()->IsSilentMode()))
    TipWarpper::Instance().ShowTip("建筑升级任务全部完成");
}

void CPageBuildings::OnDestroy() 
{
  KillTimer(TIMER_PRODUCE);
	CPageIcon::OnDestroy();
}

BOOL CPageBuildings::IsResourceEnough(int index)
{
  assert(index >= 0 && index < building_keeper_->Size());
  if(GetDataPtr()->GetResource(RESOURCE_METAL) >= Buildings_Entry(index)->GetUpgradeMinal() &&
     GetDataPtr()->GetResource(RESOURCE_CRYSTAL) >= Buildings_Entry(index)->GetUpgradeCrystal() &&
     GetDataPtr()->GetResource(RESOURCE_DIPLOGEN) >= Buildings_Entry(index)->GetUpgradeDiplogen())
    return TRUE;
  return FALSE;
}

void CPageBuildings::OnBtnCancel() 
{
  CString info;
  int sel = int(m_ProgressList.GetFirstSelectedItemPosition()) - 1;
  if(!(sel >= 0 && sel < entry_tasks_.size())) return;  
  if(sel == 0)
  {
    if(is_building_)
    {
      info.Format("正在升级：%s，你确定要取消升级吗？" ,  Buildings_Entry(cur_building_index)->GetName());    
      if(MessageBox(info , "警告"  , MB_YESNO | MB_ICONWARNING) == IDYES)
      {
        CancelBuilding(); 
        entry_tasks_.erase(entry_tasks_.begin());
        m_ProgressList.DeleteItem(0); 
        UpdateIndex();
        GetDlgItem(IDC_STA_BUILD_TIMER)->SetWindowText("");
        if(!entry_tasks_.empty())
        {
          StartOneTask();
        }
        sel = int(m_ProgressList.GetFirstSelectedItemPosition()) - 1;
        GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(sel >= 0 && sel < entry_tasks_.size());
        return;
      }
      else
      {
        sel = int(m_ProgressList.GetFirstSelectedItemPosition()) - 1;
        GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(sel >= 0 && sel < entry_tasks_.size());
        return;
      }
    }
    entry_tasks_.erase(entry_tasks_.begin());
    m_ProgressList.DeleteItem(0);
    UpdateIndex();
    if(entry_tasks_.size() > 0)
    {
      StartOneTask();
    }
  }
  else
  {
    vector<int>::iterator itor = entry_tasks_.begin();
    for(int i = 0 ; i < entry_tasks_.size() ; ++i , ++itor)
    {
      if(i == sel)
        break;
    }
    entry_tasks_.erase(itor);
    m_ProgressList.DeleteItem(sel);
    UpdateIndex();
  }    
  sel = int(m_ProgressList.GetFirstSelectedItemPosition()) - 1;
  GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(sel >= 0 && sel < entry_tasks_.size());
}

void CPageBuildings::CancelBuilding()
{
  KillTimer(TIMER_BUILDING_LEVEL_UP);
  CString info;
  GetDataPtr()->IncreaseResource(buff_cosume_metal , buff_cosume_cryst , buff_cosume_diplo);
  GetCommander()->Notify_Resource_Changed();
  is_building_ = false;
  SetWorkFlag(false);
  UpdateItemText();
}

void CPageBuildings::Notify_Exit()
{
  if(m_hWnd == NULL)
    return;
  if(is_building_)
    CancelBuilding();
}

void CPageBuildings::Notify_Resource_Changed()
{
  if(m_hWnd != NULL)
  {
    UpdateItemText();
    if(is_building_ == FALSE && entry_tasks_.size() > 0)
    {
      StartOneTask();
    }
  }  
}

void CPageBuildings::OnClickListProgress(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int sel = int(m_ProgressList.GetFirstSelectedItemPosition()) - 1;
  GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(sel >= 0 && sel < entry_tasks_.size());	
	*pResult = 0;
}

void CPageBuildings::OnRclickListProgress(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int sel = int(m_ProgressList.GetFirstSelectedItemPosition()) - 1;
  GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(sel >= 0 && sel < entry_tasks_.size());	
	*pResult = 0;
}


void CPageBuildings::Notify_Building_LevelUp()
{
  if(m_hWnd == NULL)
    return;
  UpdateItemText();
  if(m_list.GetSelectedItem() != NONE_SELECTED)
	  GetDlgItem(IDC_BTN_BUILD)->EnableWindow(Buildings_Entry(m_list.GetSelectedItem())->CanLevelUp());
  else
    GetDlgItem(IDC_BTN_BUILD)->EnableWindow(FALSE);
}

void CPageBuildings::Notify_Technics_LevelUp()
{
  if(m_hWnd == NULL)
    return;
  UpdateItemText();
  if(m_list.GetSelectedItem() != NONE_SELECTED)
	  GetDlgItem(IDC_BTN_BUILD)->EnableWindow(Buildings_Entry(m_list.GetSelectedItem())->CanLevelUp());
  else
    GetDlgItem(IDC_BTN_BUILD)->EnableWindow(FALSE);
}
