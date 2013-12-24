// pageresreachcenter.cpp : implementation file
//

#include "stdafx.h"
#include "..\XGame\xgame.h"
#include "pageresreachcenter.h"
#include "ResearchKeeper.h"
#include "ResearchTechnics.h"
#include "XGameDlg.h"
#include "TipWarpper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageResreachCenter dialog


CPageResreachCenter::CPageResreachCenter(UINT iconID /*= NULL*/ , CWnd* pParent /*=NULL*/)
: CPageIcon(CPageResreachCenter::IDD , iconID)
{
  //{{AFX_DATA_INIT(CPageResreachCenter)
	//}}AFX_DATA_INIT
 font_ctrls_text.CreateFont(
    22,                        // nHeight
    0,                         // nWidth
    0,                         // nEscapement
    0,                         // nOrientation
    TRUE,                     // nWeight
    FALSE,                     // bItalic
    FALSE,                     // bUnderline
    0,                         // cStrikeOut
    ANSI_CHARSET,              // nCharSet
    OUT_DEFAULT_PRECIS,        // nOutPrecision
    CLIP_DEFAULT_PRECIS,       // nClipPrecision
    DEFAULT_QUALITY,           // nQuality
    DEFAULT_PITCH | FF_SWISS,  // nPitchAndFamily
    "Arial Black");        // lpszFacename
  cur_research_index = -1;
  buff_cosume_metal = 0;
  buff_cosume_cryst = 0;
  buff_cosume_diplo = 0;
  is_researching_ = false;
}


void CPageResreachCenter::DoDataExchange(CDataExchange* pDX)
{
  CPageIcon::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CPageResreachCenter)
	DDX_Control(pDX, IDC_LIST_PROGRESS, m_ProgressList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageResreachCenter, CPageIcon)
//{{AFX_MSG_MAP(CPageResreachCenter)
ON_WM_SIZE()
ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_RESEARCH, OnBtnResearch)
	ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnCancel)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_CLICK, IDC_LIST_PROGRESS, OnClickListProgress)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_PROGRESS, OnRclickListProgress)
	//}}AFX_MSG_MAP
  ON_NOTIFY(HTMLLIST_SELECTIONCHANGED, IDC_MYLIST , OnMyList_SelectionChanged)
  ON_NOTIFY(HTMLLIST_LBUTTONDBLCLICK,  IDC_MYLIST , OnMyList_LButtonDClick)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageResreachCenter message handlers

void CPageResreachCenter::OnSize(UINT nType, int cx, int cy) 
{
  CPageIcon::OnSize(nType, cx, cy);
}

void CPageResreachCenter::OnMyList_LButtonDClick(NMHDR* pNMHDR, LRESULT*)
{
  GetCommander()->SwitchToPage(PAGE_DOCUMENTS);
  comm_->ShowDocument(1 , m_list.GetSelectedItem());
}

void CPageResreachCenter::OnMyList_SelectionChanged(NMHDR* pNMHDR, LRESULT*)
{
  NM_HTMLLISTCTRL *pListNMHDr = (NM_HTMLLISTCTRL*) pNMHDR;
	if(pListNMHDr->nItemNo != NONE_SELECTED && m_list.GetSelectedItem() != NONE_SELECTED)
	{
    GetDlgItem(IDC_BTN_RESEARCH)->EnableWindow(Researchs_Entry(pListNMHDr->nItemNo)->CanLevelUp());      
	}
  else
  {
    GetDlgItem(IDC_BTN_RESEARCH)->EnableWindow(FALSE);
  }
} 

BOOL CPageResreachCenter::OnInitDialog() 
{
  CPageIcon::OnInitDialog();
  CreateImageList();
  InitDlgCtrls();
  
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageResreachCenter::CreateImageList()
{
    BOOL	bRetValue = FALSE;
	HICON	hIcon = NULL;

	// Create image list
	bRetValue = m_ImageList.Create(120, 120, ILC_COLOR32 | ILC_MASK , 9 , 1);
	ASSERT(bRetValue == TRUE);

  m_ImageList_small.Create(68, 68, ILC_COLOR32 | ILC_MASK , 9 , 1);

	// Add some icons
	hIcon = AfxGetApp()->LoadIcon(IDI_TECH_ICON_SPY);
	m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);
  // Add some icons
	hIcon = AfxGetApp()->LoadIcon(IDI_TECH_ICON_COMPUTER);
	m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);
  // Add some icons
	hIcon = AfxGetApp()->LoadIcon(IDI_TECH_ICON_ATTACK);
	m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);
  // sheiled
	hIcon = AfxGetApp()->LoadIcon(IDI_TECH_ICON_SHEILED);
	m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);
  // DEFENSE
	hIcon = AfxGetApp()->LoadIcon(IDI_TECH_ICON_DEFENSE);
	m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);
  // super tech
	hIcon = AfxGetApp()->LoadIcon(IDI_TECH_ICON_SUPERTECH);
	m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);
  // Add some icons
	hIcon = AfxGetApp()->LoadIcon(IDI_TECH_ICON_POWER);
	m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_TECH_ICON_BURNING);
	m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_TECH_ICON_PULSE);
	m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);
  // super tech
	hIcon = AfxGetApp()->LoadIcon(IDI_TECH_ICON_SUPERSPACE);
	m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);
  // super tech
	hIcon = AfxGetApp()->LoadIcon(IDI_TECH_ICON_DENGLIZI);
	m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);
  // super tech
	hIcon = AfxGetApp()->LoadIcon(IDI_TECH_ICON_GRAVITION);
	m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);
}

void CPageResreachCenter::InitDlgCtrls()
{
  CRect rect; 
  GetClientRect(&rect);
  m_list.SetBKColor(RGB(55 , 77 , 112));
  m_list.SetSelectedColor(RGB(60 , 80 , 150));
  m_list.Create(this,CRect(0 ,0 , rect.Width() , rect.Height() - 180),IDC_MYLIST);
  GetDlgItem(IDC_STA_INFO)->MoveWindow(0 , rect.bottom - 148 , rect.Width() , 1);
  m_list.SetImageList(&m_ImageList);
  m_list.SetExtendedStyle(HTMLLIST_STYLE_GRIDLINES | HTMLLIST_STYLE_IMAGES);
  GetDlgItem(IDC_BTN_RESEARCH)->EnableWindow(FALSE);
  GetDlgItem(IDC_STA_RESEARCH_TIMER)->SetFont(&font_ctrls_text);
  int sel = int(m_ProgressList.GetFirstSelectedItemPosition()) - 1;
  GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(sel >= 0 && sel < entry_tasks_.size());
  m_ProgressList.SetExtendedStyle(m_ProgressList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

  m_ProgressList.InsertColumn(0,"编号",LVCFMT_CENTER,40);
	m_ProgressList.InsertColumn(1,"任务内容",LVCFMT_CENTER,120);
	m_ProgressList.InsertColumn(2,"任务进度",LVCFMT_CENTER,140);
  InitList();		
}

void CPageResreachCenter::InitList()
{
  SetItemInfo(true);
}

void CPageResreachCenter::UpdateItemText()
{
  SetItemInfo(false);
}

void CPageResreachCenter::SetItemInfo(bool bInit)
{
  for(int i = 0 ; i < research_keeper_->Size() ; ++i)
  {
    CString info;
    ElapsedTimer t(Researchs_Entry(i)->GetUpgradeTime());
    
    CString color = HIGH_LIGHT_COLOR;
    if(!Researchs_Entry(i)->CanLevelUp())
    {
      color = GRAY_COLOR;
    } 
    
    if(Researchs_Entry(i)->CanLevelUp() && !IsResourceEnough(i))
    {
      color = NO_RESOURCE_COLOR;
    }
    
    CString op;
    if(Researchs_Entry(i)->CanLevelUp() && is_researching_ && i == entry_tasks_[0])
    {
      op = "，正在升级...";
    }
    
    CString need;
    if(!Researchs_Entry(i)->CanLevelUp())
    {
      need = _T("（升级需求：") + Researchs_Entry(i)->GetTechNeeded() + "）";
    }   
    
    char buff1[64];
    char buff2[64];
    char buff3[64];
    
    info.Format("<font color=%s><b>%s(等级：%2d %s)</font><font color=#E6EBFB></b><br><br>%s<br><br>金属：<b>%s  </b> 晶体：<b>%s  </b> 重氢：<b>%s</b><br><br>升级时间：<b>%d小时 %02d分 %02d秒 %s</b></font>", 
      color , Researchs_Entry(i)->GetName() , Researchs_Entry(i)->GetLevel() , op ,  Researchs_Entry(i)->GetSimpleDisp() , AddPointsToNumber(Researchs_Entry(i)->GetUpgradeMinal() , buff1) ,
      AddPointsToNumber(Researchs_Entry(i)->GetUpgradeCrystal() , buff2) , AddPointsToNumber(Researchs_Entry(i)->GetUpgradeDiplogen() , buff3) , t.GetHour() , t.GetMinute() , t.GetSecond() , need);
    
    if(bInit)
      m_list.InsertItem(info , Researchs_Entry(i)->GetIndex() , HTML_TEXT , 120);
    else
      m_list.SetItemText(i , info );
  }		
}

void CPageResreachCenter::OnBtnResearch() 
{
	//max 256 tasks
  if(entry_tasks_.size() > 256)
    return;
  int sel = m_list.GetSelectedItem();	
  assert(sel >= RESEARCH_START && sel < RESEARCH_MAX);
  entry_tasks_.push_back(sel);
  CString info;
  int index = m_ProgressList.GetItemCount();
  info.Format("%02d" , index);
  m_ProgressList.InsertItem(index , info);
  m_ProgressList.SetItemText(index , 1 , Researchs_Entry(sel)->GetName());
  m_ProgressList.SetItemText(index , 2 , "0.000%");
  UpdateIndex();
  if(entry_tasks_.size() == 1)
  {
    StartOneTask();
  }
}

void CPageResreachCenter::UpdateIndex()
{
  CString info;
  for(int i = 0 ; i < entry_tasks_.size() ; ++i)
  {
    info.Format("%02d" , i);
    m_ProgressList.SetItemText(i , 0 , info);
  }
}

void CPageResreachCenter::StartOneTask()
{
  int sel = entry_tasks_[0];
  assert(sel >= 0 && sel < research_keeper_->Size());

  research_timer_.Init(Researchs_Entry(sel)->GetUpgradeTime());  
  GetDlgItem(IDC_STA_RESEARCH_TIMER)->SetWindowText(research_timer_.ToCString());
  
  //wait resource
  if(IsResourceEnough(sel) == FALSE || Researchs_Entry(sel)->CanLevelUp() == false)
    return ;  

  //set 1 second timer
  SetTimer(TIMER_RESEARCH_LEVEL_UP , TIMER_BASE , NULL);
  cur_research_index = sel;

  //buffer resource for cancel
  buff_cosume_metal = Researchs_Entry(sel)->GetUpgradeMinal();
  buff_cosume_cryst = Researchs_Entry(sel)->GetUpgradeCrystal();
  buff_cosume_diplo = Researchs_Entry(sel)->GetUpgradeDiplogen();

  GetDataPtr()->DecreaseResource(Researchs_Entry(sel)->GetUpgradeMinal() , Researchs_Entry(sel)->GetUpgradeCrystal() , Researchs_Entry(sel)->GetUpgradeDiplogen());
  is_researching_ = true;
  SetWorkFlag(true);
  tip_ = "研究：0%%";
  GetCommander()->Notify_Resource_Changed();
  UpdateItemText();
}

void CPageResreachCenter::OnTimer(UINT nIDEvent) 
{
  //research
	if(nIDEvent == TIMER_RESEARCH_LEVEL_UP)
  {
    research_timer_.Go();
    GetDlgItem(IDC_STA_RESEARCH_TIMER)->SetWindowText(research_timer_.ToCString());
    double r = (research_timer_.GetElapseSecond() / (research_timer_.GetLeftSecond() + research_timer_.GetElapseSecond()));
    tip_.Format("研究：%0.0f%%" , r * 100);
    CString s;
    s.Format("%.3f%%" , r * 100.0);
    m_ProgressList.SetItemText(0 , 2 , s);
    if(research_timer_.IsZero())
    {
      KillTimer(TIMER_RESEARCH_LEVEL_UP);
      EndOneTask();

      //start again
      if(entry_tasks_.size() > 0)
      {
        StartOneTask();
      }
      //finish all task
      else
      {
        GetDlgItem(IDC_STA_RESEARCH_TIMER)->SetWindowText("");        
      }
    }
  }	
  
  CPageIcon::OnTimer(nIDEvent);
}

void CPageResreachCenter::EndOneTask()
{
  assert(entry_tasks_.size() > 0);
  Researchs_Entry(entry_tasks_[0])->LevelUp();
  Researchs_Entry(entry_tasks_[0])->Save();
  is_researching_ = false;
  SetWorkFlag(false);
  UpdateItemText();
  GetCommander()->Notify_Technics_LevelUp();  
  GetCommander()->Notify_Resource_Consumed(buff_cosume_metal + buff_cosume_cryst + buff_cosume_diplo);
  entry_tasks_.erase(entry_tasks_.begin());
  m_ProgressList.DeleteItem(0);  
  UpdateIndex();
  int sel = int(m_ProgressList.GetFirstSelectedItemPosition()) - 1;
  GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(sel >= 0 && sel < entry_tasks_.size());	
  if(entry_tasks_.empty() && (!GetCommander()->IsSilentMode()))
    TipWarpper::Instance().ShowTip("研究任务全部完成");
}

BOOL CPageResreachCenter::IsResourceEnough(int index)
{
  assert(index >= 0 && index < research_keeper_->Size());
  if(GetDataPtr()->GetResource(RESOURCE_METAL) >= Researchs_Entry(index)->GetUpgradeMinal() &&
     GetDataPtr()->GetResource(RESOURCE_CRYSTAL) >= Researchs_Entry(index)->GetUpgradeCrystal() &&
     GetDataPtr()->GetResource(RESOURCE_DIPLOGEN) >= Researchs_Entry(index)->GetUpgradeDiplogen())
    return TRUE;
  return FALSE;
}

void CPageResreachCenter::CancelRearching()
{
  KillTimer(TIMER_RESEARCH_LEVEL_UP);
  CString info;
  GetDataPtr()->IncreaseResource(buff_cosume_metal , buff_cosume_cryst , buff_cosume_diplo);
  GetCommander()->Notify_Resource_Changed();
  is_researching_ = false;
  SetWorkFlag(false);
  UpdateItemText();
}

void CPageResreachCenter::OnBtnCancel() 
{
  CString info;
  int sel = int(m_ProgressList.GetFirstSelectedItemPosition()) - 1;
  if(!(sel >= 0 && sel < entry_tasks_.size())) return;
  if(sel == 0)
  {
    if(is_researching_)
    {
      info.Format("正在升级：%s，你确定要取消升级吗？" ,  Researchs_Entry(cur_research_index)->GetName());    
      if(MessageBox(info , "警告"  , MB_YESNO | MB_ICONWARNING) == IDYES)
      {
        CancelRearching(); 
        entry_tasks_.erase(entry_tasks_.begin());
        m_ProgressList.DeleteItem(0);   
        UpdateIndex();
        GetDlgItem(IDC_STA_RESEARCH_TIMER)->SetWindowText("");
        if(entry_tasks_.size() > 0)
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

void CPageResreachCenter::OnDestroy() 
{
  KillTimer(TIMER_PRODUCE);
	CPageIcon::OnDestroy();	
}

void CPageResreachCenter::Notify_Exit()
{
  if(m_hWnd == NULL)
    return;
  if(is_researching_)
    CancelRearching();
}

void CPageResreachCenter::Notify_Building_LevelUp()
{
  if(m_hWnd == NULL)
    return;
  UpdateItemText();
  if(m_list.GetSelectedItem() != NONE_SELECTED)
	  GetDlgItem(IDC_BTN_RESEARCH)->EnableWindow(Researchs_Entry(m_list.GetSelectedItem())->CanLevelUp());
  else
    GetDlgItem(IDC_BTN_RESEARCH)->EnableWindow(FALSE);
}

void CPageResreachCenter::Notify_Technics_LevelUp()
{
  if(m_hWnd == NULL)
    return;
  UpdateItemText();
  if(m_list.GetSelectedItem() != NONE_SELECTED)
    GetDlgItem(IDC_BTN_RESEARCH)->EnableWindow(Researchs_Entry(m_list.GetSelectedItem())->CanLevelUp());
  else
    GetDlgItem(IDC_BTN_RESEARCH)->EnableWindow(FALSE);
}

void CPageResreachCenter::Notify_Resource_Changed()
{
  if(m_hWnd != NULL)
  {
    UpdateItemText();
    if(is_researching_ == FALSE && entry_tasks_.size() > 0)
    {
      StartOneTask();
    }
  }  
}

void CPageResreachCenter::OnClickListProgress(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int sel = int(m_ProgressList.GetFirstSelectedItemPosition()) - 1;
  GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(sel >= 0 && sel < entry_tasks_.size());	
	
	*pResult = 0;
}

void CPageResreachCenter::OnRclickListProgress(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int sel = int(m_ProgressList.GetFirstSelectedItemPosition()) - 1;
  GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(sel >= 0 && sel < entry_tasks_.size());	
	
	*pResult = 0;
}
