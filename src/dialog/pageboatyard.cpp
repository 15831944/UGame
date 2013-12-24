#include "stdafx.h"
#include "..\XGame\xgame.h"
#include "pageboatyard.h"

#include "BoatsKeeper.h"
#include "Spaceship.h"
#include "XGameDlg.h"
#include "TipWarpper.h"

CPageBoatyard::CPageBoatyard(UINT iconID /*= NULL*/ , CWnd* pParent /*=NULL*/)
: CPageIcon(CPageBoatyard::IDD , iconID)
{
  //{{AFX_DATA_INIT(CPageBoatyard)
	m_ships_produce_number = 1;
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
  cur_produce_index = -1;
  buff_cosume_metal = 0.0;
  buff_cosume_cryst = 0.0;
  buff_cosume_diplo = 0.0;
  is_producing_ = false;
  counter_ = 0L;
}


void CPageBoatyard::DoDataExchange(CDataExchange* pDX)
{
  CPageIcon::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CPageBoatyard)
	DDX_Control(pDX, IDC_LIST_PROGRESS, m_ProgressList);
	DDX_Text(pDX, IDC_EDIT1, m_ships_produce_number);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageBoatyard, CPageIcon)
//{{AFX_MSG_MAP(CPageBoatyard)
ON_WM_TIMER()
ON_WM_SIZE()
ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnCancel)
ON_BN_CLICKED(IDC_BTN_RESEARCH, OnBtnProduce)
	ON_NOTIFY(NM_CLICK, IDC_LIST_PROGRESS, OnClickListProgress)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_PROGRESS, OnRclickListProgress)
	ON_EN_CHANGE(IDC_EDIT1, OnChangeEdit1)
	//}}AFX_MSG_MAP
ON_NOTIFY(HTMLLIST_SELECTIONCHANGED, IDC_MYLIST , OnMyList_SelectionChanged)
ON_NOTIFY(HTMLLIST_LBUTTONDBLCLICK,  IDC_MYLIST , OnMyList_LButtonDClick)
END_MESSAGE_MAP()


void CPageBoatyard::OnMyList_SelectionChanged(NMHDR* pNMHDR, LRESULT*)
{
  NM_HTMLLISTCTRL *pListNMHDr = (NM_HTMLLISTCTRL*) pNMHDR;
  if(pListNMHDr->nItemNo != NONE_SELECTED && m_list.GetSelectedItem() != NONE_SELECTED)
	{
    GetDlgItem(IDC_BTN_RESEARCH)->EnableWindow(Boats_Entry(pListNMHDr->nItemNo)->CanProduce() && IsResourceEnough(pListNMHDr->nItemNo));   
    GetDlgItem(IDC_EDIT1)->EnableWindow(Boats_Entry(pListNMHDr->nItemNo)->CanProduce() && IsResourceEnough(pListNMHDr->nItemNo));
    
	}
  else
  {
    GetDlgItem(IDC_BTN_RESEARCH)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
  }
} 

void CPageBoatyard::OnMyList_LButtonDClick(NMHDR* pNMHDR, LRESULT*)
{
  GetCommander()->SwitchToPage(PAGE_DOCUMENTS);
  comm_->ShowDocument(2 , -1);
}

void CPageBoatyard::OnSize(UINT nType, int cx, int cy) 
{
  CPageIcon::OnSize(nType, cx, cy);
}

BOOL CPageBoatyard::OnInitDialog() 
{
  CPageIcon::OnInitDialog();
  CreateImageList();
  InitDlgCtrls(); 
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageBoatyard::Notify_Exit()
{
  if(m_hWnd == NULL)
    return;
  if(entry_tasks_.empty())
    return;
  if(is_producing_)
    CancelCurrentProducing();    
  else
    CancelProducingByIndex(0);
  for(int i = 1 ; i < entry_tasks_.size() ; ++i)
  {
    CancelProducingByIndex(i);
  }
}

void CPageBoatyard::CreateImageList()
{
  BOOL	bRetValue = FALSE;
  HICON	hIcon = NULL;
  
  // Create image list
  bRetValue = m_ImageList.Create(120, 120, ILC_COLOR32 | ILC_MASK , 9 , 1);
  ASSERT(bRetValue == TRUE);
  
  m_ImageList_small.Create(68, 68, ILC_COLOR32 | ILC_MASK , 9 , 1);
  
  // Add some icons
  hIcon = AfxGetApp()->LoadIcon(IDI_BOAT_SMALL_SCUTTER);
  m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);
  // Add some icons
  hIcon = AfxGetApp()->LoadIcon(IDI_BOAT_LARGESCUTTER);
  m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);
  // Add some icons
  hIcon = AfxGetApp()->LoadIcon(IDI_BOAT_LIGHT_FIGHTER);
  m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);
  // Add some icons
  hIcon = AfxGetApp()->LoadIcon(IDI_BOAT_HEAVY_FIGHTER);
  m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_BOAT_CRUISOR);
  m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_BOAT_WARSHIP);
  m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);

  hIcon = AfxGetApp()->LoadIcon(IDI_BOAT_CONOLY);
  m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);

  hIcon = AfxGetApp()->LoadIcon(IDI_BOAT_RECYCLE);
  m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);

  hIcon = AfxGetApp()->LoadIcon(IDI_BOAT_SPY_PLANET);
  m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);

  hIcon = AfxGetApp()->LoadIcon(IDI_BOAT_BOMBER);
  m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);

  hIcon = AfxGetApp()->LoadIcon(IDI_BOAT_SUNPOWER_PLANET);
  m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);

  hIcon = AfxGetApp()->LoadIcon(IDI_BOAT_DESTROYER);
  m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);

  hIcon = AfxGetApp()->LoadIcon(IDI_BOAT_DS);
  m_ImageList.Add(hIcon);
  m_ImageList_small.Add(hIcon);
}

void CPageBoatyard::InitDlgCtrls()
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
  GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
  GetDlgItem(IDC_STA_RESEARCH_TIMER)->SetFont(&font_ctrls_text);
  int sel = int(m_ProgressList.GetFirstSelectedItemPosition()) - 1;
  GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(sel >= 0 && sel < entry_tasks_.size());
  m_ProgressList.SetExtendedStyle(m_ProgressList.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

  m_ProgressList.InsertColumn(0,"编号",LVCFMT_CENTER,40);
	m_ProgressList.InsertColumn(1,"任务内容",LVCFMT_CENTER,100);
  m_ProgressList.InsertColumn(2,"剩余数量",LVCFMT_CENTER,80);
	m_ProgressList.InsertColumn(3,"任务进度",LVCFMT_CENTER,80);
  InitList();		
}

void CPageBoatyard::InitList()
{
  SetItemInfo(true);	
}

void CPageBoatyard::UpdateItemText()
{
  SetItemInfo(false);
}

void CPageBoatyard::SetItemInfo(bool bInit)
{
  for(int i = 0 ; i < boat_keeper_->Size() ; ++i)
  {
    CString info;
    HighFrequencyElapsedTimer t(Boats_Entry(i)->GetProduceTime() * 1000);
    
    CString color = HIGH_LIGHT_COLOR;
    if(!Boats_Entry(i)->CanProduce())
    {
      color = GRAY_COLOR;
    } 
    
    if(Boats_Entry(i)->CanProduce() && !IsResourceEnough(i))
    {
      color = NO_RESOURCE_COLOR;
    }
    
    CString op;
    if(Boats_Entry(i)->CanProduce() && is_producing_ && i == entry_tasks_[0].index)
    {
      op = "，正在生产...";
    }
    
    CString need;
    if(!Boats_Entry(i)->CanProduce())
    {
      need = _T("（生产需求：") + Boats_Entry(i)->GetTechNeeded() + "）";
    }    
    char buff1[64];
    char buff2[64];
    char buff3[64];
    
    info.Format("<font color=%s><b>%s(数量：%d)</font><font color=#E6EBFB></b><br><br>%s<br><br>金属：<b>%s  </b> 晶体：<b>%s  </b> 重氢：<b>%s</b><br><br>升级时间：<b>%d小时 %02d分 %02d秒 %d毫秒%s</b></font>", 
      color , Boats_Entry(i)->GetName() , Boats_Entry(i)->GetNumber() , Boats_Entry(i)->GetSimpleDisp() , AddPointsToNumber(Boats_Entry(i)->GetProduceMinal() , buff1) ,
      AddPointsToNumber(Boats_Entry(i)->GetProduceCrystal() , buff2) , AddPointsToNumber(Boats_Entry(i)->GetProduceDiplogen() ,buff3) , t.GetHour() , t.GetMinute() , t.GetSecond() , t.GetMSecond(), need);
    if(bInit)
      m_list.InsertItem(info , Boats_Entry(i)->GetIndex() , HTML_TEXT , 120);
    else
      m_list.SetItemText(i , info );
  }		
}

BOOL CPageBoatyard::IsResourceEnough(int index , UINT number)
{
  assert(index >= 0 && index < boat_keeper_->Size());
  if(GetDataPtr()->GetResource(RESOURCE_METAL) >=   (Boats_Entry(index)->GetProduceMinal() * number)    &&
    GetDataPtr()->GetResource(RESOURCE_CRYSTAL) >=  (Boats_Entry(index)->GetProduceCrystal()  * number) &&
    GetDataPtr()->GetResource(RESOURCE_DIPLOGEN) >= (Boats_Entry(index)->GetProduceDiplogen() * number))
    return TRUE;
  return FALSE;
}

void CPageBoatyard::OnBtnProduce() 
{
  UpdateData(TRUE);
  if(m_ships_produce_number <= 0) 
    return;
  if(m_ships_produce_number > MAX_PRODUCED_BOAT)
  {
    m_ships_produce_number = MAX_PRODUCED_BOAT;
    UpdateData(FALSE);
  }
  //max 256 tasks
  if(entry_tasks_.size() > 256)
    return;
  int sel = m_list.GetSelectedItem();	
  assert(sel >= BOAT_START && sel < BOAT_MAX);
  UINT s = GetMaxProduceNumber(sel , m_ships_produce_number);
  assert(s > 0);
  Produce_Tast_t task;
  task.index = sel;
  task.number = s;
  entry_tasks_.push_back(task);  

  //resource reduce  
  GetDataPtr()->DecreaseResource(Boats_Entry(sel)->GetProduceMinal()    * s , 
                                 Boats_Entry(sel)->GetProduceCrystal()  * s , 
                                 Boats_Entry(sel)->GetProduceDiplogen() * s);
  GetCommander()->Notify_Resource_Changed();  
  CString info;
  int index = m_ProgressList.GetItemCount();
  info.Format("%02d" , index);
  m_ProgressList.InsertItem(index , info);
  m_ProgressList.SetItemText(index , 1 , Boats_Entry(sel)->GetName());
  info.Format("%d" , s);
  m_ProgressList.SetItemText(index , 2 , info);
  m_ProgressList.SetItemText(index , 3 , "0.000%");
  UpdateIndex();
  if(entry_tasks_.size() == 1)
  {
    StartOneTask();
  }
  m_ships_produce_number = 1;
  UpdateData(FALSE);
}

void CPageBoatyard::UpdateIndex()
{
  CString info;
  for(int i = 0 ; i < entry_tasks_.size() ; ++i)
  {
    info.Format("%02d" , i);
    m_ProgressList.SetItemText(i , 0 , info);
  }
}

void CPageBoatyard::StartOneTask()
{
  UpdateData(TRUE);
  int sel = entry_tasks_[0].index;

  CString info;
  assert(sel >= 0 && sel < boat_keeper_->Size());
  
  //ms
  high_produce_timer_.Init(Boats_Entry(sel)->GetProduceTime() * 1000 * entry_tasks_[0].number);  
  info = high_produce_timer_.ToCString();
  GetDlgItem(IDC_STA_RESEARCH_TIMER)->SetWindowText(info);
  
  //set TIMER_BASE_HIGH_FREQUENCY ms timer
  counter_ = 0L;
  SetTimer(TIMER_PRODUCE_BOAT , TIMER_BASE_HIGH_FREQUENCY , NULL);
  cur_produce_index = sel;
  
  //buffer resource for cancel
  buff_cosume_metal = Boats_Entry(sel)->GetProduceMinal()    * entry_tasks_[0].number;
  buff_cosume_cryst = Boats_Entry(sel)->GetProduceCrystal()  * entry_tasks_[0].number;
  buff_cosume_diplo = Boats_Entry(sel)->GetProduceDiplogen() * entry_tasks_[0].number;
  
  is_producing_ = true;
  SetWorkFlag(true);

  tip_ = "船厂：0%%";
  UpdateItemText();
}

void CPageBoatyard::OnTimer(UINT nIDEvent) 
{
   //research
	if(nIDEvent == TIMER_PRODUCE_BOAT)
  {
    ++counter_;
    if((counter_ >= ulong(Boats_Entry(cur_produce_index)->GetProduceTime() * (1000 / TIMER_BASE_HIGH_FREQUENCY))) && entry_tasks_[0].number > 0)
    {
      counter_ = 0L;
      Boats_Entry(cur_produce_index)->ProduceShips(1);
      GetCommander()->Notify_Ships_Produced(cur_produce_index , 1);      
      GetCommander()->Notify_Resource_Consumed(Boats_Entry(cur_produce_index)->GetProduceMinal() + Boats_Entry(cur_produce_index)->GetProduceCrystal() + Boats_Entry(cur_produce_index)->GetProduceDiplogen());

      entry_tasks_[0].number--;
      UpdateItemText();
      CString info;
      info.Format("%d" , entry_tasks_[0].number);
      m_ProgressList.SetItemText(0 , 2 , info);

      buff_cosume_metal = Boats_Entry(cur_produce_index)->GetProduceMinal()    * entry_tasks_[0].number;
      buff_cosume_cryst = Boats_Entry(cur_produce_index)->GetProduceCrystal()  * entry_tasks_[0].number;
      buff_cosume_diplo = Boats_Entry(cur_produce_index)->GetProduceDiplogen() * entry_tasks_[0].number;
    }
    //TIMER_BASE_HIGH_FREQUENCY ms
    high_produce_timer_.Go(TIMER_BASE_HIGH_FREQUENCY);
    CString info = high_produce_timer_.ToCString();
    GetDlgItem(IDC_STA_RESEARCH_TIMER)->SetWindowText(info);

    double r = (high_produce_timer_.GetElapseMSecond() / (high_produce_timer_.GetLeftMSecond() + high_produce_timer_.GetElapseMSecond()));
    tip_.Format("船厂：%0.0f%%" , r * 100.0);
    CString s;
    s.Format("%.3f%%" , r * 100.0);
    m_ProgressList.SetItemText(0 , 3 , s);
    if(high_produce_timer_.IsZero() || entry_tasks_[0].number == 0)
    {
      counter_ = 0L;
      KillTimer(TIMER_PRODUCE_BOAT);
      EndOneTask();

      //start again
      if(!entry_tasks_.empty())
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

void CPageBoatyard::EndOneTask()
{
  is_producing_ = false;
  SetWorkFlag(false);  
  entry_tasks_.erase(entry_tasks_.begin());
  m_ProgressList.DeleteItem(0); 
  UpdateIndex();
  UpdateItemText();
  int sel = int(m_ProgressList.GetFirstSelectedItemPosition()) - 1;
  GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(sel >= 0 && sel < entry_tasks_.size());	
  if(entry_tasks_.empty() && (!GetCommander()->IsSilentMode()))
    TipWarpper::Instance().ShowTip("飞船生产任务全部完成");
}

void CPageBoatyard::OnBtnCancel() 
{
  CString info;
  int sel = int(m_ProgressList.GetFirstSelectedItemPosition()) - 1;
  if(!(sel >= 0 && sel < entry_tasks_.size())) return;  
  //sel == 0
  if(sel == 0)
  {
    if(is_producing_)
    {
      info.Format("正在生产：%s，你确定要取消生产吗？" ,  Boats_Entry(cur_produce_index)->GetName());    
      if(MessageBox(info , "警告"  , MB_YESNO | MB_ICONWARNING) == IDYES)
      {
        KillTimer(TIMER_PRODUCE_BOAT);
        CancelCurrentProducing(); 
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
    CancelProducingByIndex(0);
    entry_tasks_.erase(entry_tasks_.begin());
    m_ProgressList.DeleteItem(0);
    UpdateIndex();
    if(entry_tasks_.size() > 0)
    {
      StartOneTask();
    }
  }

  //sel != 0
  else
  {
    CancelProducingByIndex(sel);
    vector<Produce_Tast_t>::iterator itor = entry_tasks_.begin();
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

void CPageBoatyard::CancelCurrentProducing()
{
  GetDataPtr()->IncreaseResource(buff_cosume_metal , buff_cosume_cryst ,  buff_cosume_diplo);
  GetCommander()->Notify_Resource_Changed();
  is_producing_ = false;
  SetWorkFlag(false);
  UpdateItemText();
}

void CPageBoatyard::CancelProducingByIndex(int index)
{
  assert(index >= 0 && index < entry_tasks_.size());
  int ship_type = entry_tasks_[index].index;
  UINT ship_num = entry_tasks_[index].number;

  double metal = Boats_Entry(ship_type)->GetProduceMinal()    * ship_num;
  double cryst = Boats_Entry(ship_type)->GetProduceCrystal()  * ship_num;
  double diplo = Boats_Entry(ship_type)->GetProduceDiplogen() * ship_num;

  GetDataPtr()->IncreaseResource(metal , cryst ,  diplo);
  GetCommander()->Notify_Resource_Changed();
  UpdateItemText();
}

void CPageBoatyard::Notify_Building_LevelUp()
{
  if(m_hWnd == NULL)
    return;
  UpdateItemText();
  int sel = m_list.GetSelectedItem();
  if(m_list.GetSelectedItem() != NONE_SELECTED)
	{
    GetDlgItem(IDC_BTN_RESEARCH)->EnableWindow(Boats_Entry(sel)->CanProduce() && IsResourceEnough(sel));   
    GetDlgItem(IDC_EDIT1)->EnableWindow(Boats_Entry(sel)->CanProduce() && IsResourceEnough(sel));    
	}
  else
  {
    GetDlgItem(IDC_BTN_RESEARCH)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
  }
}

void CPageBoatyard::Notify_Technics_LevelUp()
{
  if(m_hWnd == NULL)
    return;
  UpdateItemText();
  int sel = m_list.GetSelectedItem();
  if(m_list.GetSelectedItem() != NONE_SELECTED)
	{
    GetDlgItem(IDC_BTN_RESEARCH)->EnableWindow(Boats_Entry(sel)->CanProduce() && IsResourceEnough(sel));   
    GetDlgItem(IDC_EDIT1)->EnableWindow(Boats_Entry(sel)->CanProduce() && IsResourceEnough(sel));    
	}
  else
  {
    GetDlgItem(IDC_BTN_RESEARCH)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
  }
}

void CPageBoatyard::Notify_Ships_Changed()
{
  if(m_hWnd != NULL)
    UpdateItemText();
}

void CPageBoatyard::Notify_Resource_Changed()
{
  if(m_hWnd == NULL)
    return;
  UpdateItemText();
  int sel = m_list.GetSelectedItem();
  if(m_list.GetSelectedItem() != NONE_SELECTED)
	{
    GetDlgItem(IDC_BTN_RESEARCH)->EnableWindow(Boats_Entry(sel)->CanProduce() && IsResourceEnough(sel));   
    GetDlgItem(IDC_EDIT1)->EnableWindow(Boats_Entry(sel)->CanProduce() && IsResourceEnough(sel));    
	}
  else
  {
    GetDlgItem(IDC_BTN_RESEARCH)->EnableWindow(FALSE);
    GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
  }
}

UINT CPageBoatyard::GetMaxProduceNumber(int index , UINT def_number)
{
  if(IsResourceEnough(index , def_number))
  {
    return def_number;
  }

  int m = -1;
  if(UINT(Boats_Entry(index)->GetProduceMinal()) > 0)
  {
    m = 1.0 * GetDataPtr()->GetResource(RESOURCE_METAL)    / Boats_Entry(index)->GetProduceMinal();
  }
  int c = -1;
  if(UINT(Boats_Entry(index)->GetProduceCrystal()) > 0)
  {
    c = 1.0 * GetDataPtr()->GetResource(RESOURCE_CRYSTAL)  / Boats_Entry(index)->GetProduceCrystal();
  }
  int h = -1;
  if(UINT(Boats_Entry(index)->GetProduceDiplogen()) > 0)
  {
    h = 1.0 * GetDataPtr()->GetResource(RESOURCE_DIPLOGEN) / Boats_Entry(index)->GetProduceDiplogen();
  }
  vector<int> tmp;
  if(m > 0)
    tmp.push_back(m);
  if(c > 0)
    tmp.push_back(c);
  if(h > 0)
    tmp.push_back(h);
  if(tmp.size() > 0)
  {
    std::sort(tmp.begin() , tmp.end());
    return tmp[0];
  }
  assert(false);
  return 1;
}

void CPageBoatyard::OnClickListProgress(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int sel = int(m_ProgressList.GetFirstSelectedItemPosition()) - 1;
  GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(sel >= 0 && sel < entry_tasks_.size());	
	*pResult = 0;
}

void CPageBoatyard::OnRclickListProgress(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int sel = int(m_ProgressList.GetFirstSelectedItemPosition()) - 1;
  GetDlgItem(IDC_BTN_CANCEL)->EnableWindow(sel >= 0 && sel < entry_tasks_.size());	
	*pResult = 0;
}


void CPageBoatyard::OnChangeEdit1() 
{
	UpdateData(TRUE);
  if(m_ships_produce_number > MAX_PRODUCED_BOAT)
  {
    m_ships_produce_number = MAX_PRODUCED_BOAT;
    UpdateData(FALSE);
  }  
}
