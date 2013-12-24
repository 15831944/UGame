
#include "stdafx.h"
#include "xgame.h"
#include "pageinformation.h"
#include "XGameDlg.h"

CPageInformation::CPageInformation(UINT iconID /*= NULL*/ , CWnd* pParent /*=NULL*/)
: CPageIcon(CPageInformation::IDD , iconID) 
{
  //{{AFX_DATA_INIT(CPageInformation)
	m_op_option = 0;
	m_bDeleteReporter = TRUE;
	//}}AFX_DATA_INIT
  old_info_number_ = 0L;
}

void CPageInformation::DoDataExchange(CDataExchange* pDX)
{
  CPageIcon::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CPageInformation)
	DDX_CBIndex(pDX, IDC_COMBO1, m_op_option);
	DDX_Check(pDX, IDC_CHECK, m_bDeleteReporter);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPageInformation, CPageIcon)
//{{AFX_MSG_MAP(CPageInformation)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOk)
	ON_BN_CLICKED(IDC_BTN_COPY, OnBtnCopy)
	//}}AFX_MSG_MAP
ON_NOTIFY(HTMLLIST_SELECTIONCHANGED, IDC_MYLIST , OnMyList_SelectionChanged)
ON_NOTIFY(HTMLLIST_LBUTTONDBLCLICK,  IDC_MYLIST , OnMyList_LButtonDClick)
ON_NOTIFY(HTMLLIST_ITEMDELETE,  IDC_MYLIST , OnMyList_ItemDelete)
ON_NOTIFY(HTMLLIST_ITEMDELETEALL,  IDC_MYLIST , OnMyList_ItemDeleteAll)
END_MESSAGE_MAP()

BOOL CPageInformation::OnInitDialog() 
{
  CPageIcon::OnInitDialog();	
  Initialize();
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageInformation::DisplayInfoNumber()
{
  CString info;
  int new_info = m_list.GetItemCount() - old_info_number_;
  if(new_info <= 0)
    new_info = 0;
  info.Format("当前消息总数：%d，其中新消息：%d 条" , m_list.GetItemCount() , new_info);
  (GetDlgItem(IDC_STA_INFO))->SetWindowText(info);
}

void CPageInformation::OnMyList_SelectionChanged(NMHDR* pNMHDR, LRESULT*)
{
  if(m_list.GetSelectedItem() >= 0)
  {
    old_info_number_ = m_list.GetItemCount();	
	  GetCommander()->MessageNotify(0L);
    DisplayInfoNumber();
    GetDlgItem(IDC_BTN_COPY)->EnableWindow(TRUE);
  }
  else
  {
    GetDlgItem(IDC_BTN_COPY)->EnableWindow(FALSE);
  }
}

void CPageInformation::OnMyList_LButtonDClick(NMHDR* pNMHDR, LRESULT*)
{
  int sel = m_list.GetSelectedItem();
  DWORD d = m_list.GetItemData(sel);
  if(d == 0) return;
  Item_Date* pData = (Item_Date*)d;
  if(pData->type == TASK_T_SPY)
  {
    comm_->PrepareAttack(pData->target_star_index);
  }
  else if(pData->type == TASK_T_ATTACK)
  {
    ShellExecute(NULL, _T("open"), pData->report_file , NULL, NULL, SW_SHOWNORMAL);
  }
  GetDlgItem(IDC_BTN_COPY)->EnableWindow(sel != NONE_SELECTED);
}


void CPageInformation::OnMyList_ItemDelete(NMHDR* pNMHDR, LRESULT*)
{
  NM_HTMLLISTCTRL* pItem = (NM_HTMLLISTCTRL*)pNMHDR;
  assert(pItem->nItemNo >= 0 && pItem->nItemNo < m_list.GetItemCount());
  DWORD d = m_list.GetItemData(pItem->nItemNo);
  Item_Date* pData = (Item_Date*)d;
  delete pData;
  m_list.SetItemData(pItem->nItemNo , 0);
  GetDlgItem(IDC_BTN_COPY)->EnableWindow(FALSE);
}

void CPageInformation::OnMyList_ItemDeleteAll(NMHDR* pNMHDR, LRESULT*)
{
  for(int i = 0 ; i < m_list.GetItemCount() ; ++i)
  {
    DWORD d = m_list.GetItemData(i);
    Item_Date* pData = (Item_Date*)d;
    delete pData;
    m_list.SetItemData(i , 0);
  } 
  GetDlgItem(IDC_BTN_COPY)->EnableWindow(FALSE);
}

CString CPageInformation::FillString(const CString& oristr , int length)
{
  if(oristr.GetLength() >= length)
  {
    return oristr;
  }
  CString buff(oristr);
  int sz = length - oristr.GetLength();
  while(sz > 0)
  {
    buff += " ";
    --sz;
  }
  return buff;
}

void CPageInformation::Initialize()
{ 
  CRect rect;
  GetClientRect(&rect);
  m_list.SetBKColor(RGB(55 , 77 , 112));
  m_list.SetSelectedColor(RGB(60 , 80 , 150));  
  m_list.Create(this,CRect(0 ,0 , rect.Width() , rect.Height() - 40),IDC_MYLIST);
  m_list.SetExtendedStyle(HTMLLIST_STYLE_GRIDLINES | HTMLLIST_STYLE_CHECKBOX);
  GetDlgItem(IDC_BTN_COPY)->EnableWindow(FALSE);
  DisplayInfoNumber();
}

void CPageInformation::ReportSpyInfo(const Spy_info& spy)
{
  CString info;
  CTime t = CTime::GetCurrentTime();
  TCHAR buff[64];

  ElapsedTimer timer;
  timer.Init(spy.refresh_minuter_ * 60);
  //normal info
  info.Format("<font color=#00FF00><b>间谍报告来自星座：%s（%d-%02d-%02d %02d:%02d:%02d）</b></font><font color=#FFFFFF><br></br>"
    "【一般】<br></br>星座积分          %.0f<br></br>逃跑几率          %.1f%%" ,
    spy.star_->position_.ToCString(buff) , t.GetYear() , t.GetMonth() , t.GetDay() , t.GetHour() , t.GetMinute() , t.GetSecond() ,
    spy.star_->rank_  , spy.star_->elpase_ * 100.0);

  int s = pow(spy.star_->spy_level_ - GetDataPtr()->GetResearchLevel(RESEARCH_SPY) , 2);
  if( spy.star_->spy_level_ > GetDataPtr()->GetResearchLevel(RESEARCH_SPY) )
    s = -1 * s;
  s += spy.spynumber_;
  CString tmp(info);

  TCHAR buf_m[40] ;
  TCHAR buf_c[40] ;
  TCHAR buf_d[40] ;
  //resource
  info.Format("%s<br></br>【资源】<br></br>金屬  %s          晶體  %s          重氫  %s" , 
    info , AddPointsToNumber(spy.star_->metal_ , buf_m) , AddPointsToNumber(spy.star_->crystal_ , buf_c) , AddPointsToNumber(spy.star_->diplogen_ , buf_d));
    
  //fleet
  if(s >= 2)
  {
    tmp = info;
    int cnt = 0;
    CString str , str2;
    info.Format("%s<br></br>【艦隊】" , tmp);
    for(int i = T_KT ; i < T_RAK ; ++i)
    {
      if( (spy.star_->is_fleet_out == false || i == T_SAT) && spy.star_->fleet_and_defense_[i].Num >= 1)
      {
        tmp = info;
        if(cnt % 2 == 0)
        {
          tmp += "<br></br>";
        }        
        str.Format("%s%.0f" , FillString(BOATS_NAME[i] , 18) , spy.star_->fleet_and_defense_[i].Num);
        str2.Format("%s" , FillString(str , 30));
        info.Format("%s%s" , tmp , str2);
        ++cnt;
      }
    }
  }
  //defense
  if(s >= 4)
  {
    tmp = info;
    int cnt = 0;
    CString str , str2;
    info.Format("%s<br></br>【防禦】" , tmp);
    for(int i = T_RAK ; i < T_END ; ++i)
    {
      if(spy.star_->fleet_and_defense_[i].Num >= 1)
      {
        tmp = info;
        if(cnt % 2 == 0)
        {
          tmp += "<br></br>";
        }        
        str.Format("%s%.0f" , FillString(DEFENSES_NAME[i - T_RAK] , 18) , spy.star_->fleet_and_defense_[i].Num);
        str2.Format("%s" , FillString(str , 30));
        info.Format("%s%s" , tmp , str2);
        ++cnt;
      }
    }
  }
  //techs
  if(s >= 6)
  {
    tmp = info;
    CString str;
    info.Format("%s<br></br>【研究】" , tmp);
    tmp = info;
    str.Format("<br></br>%s%d" , FillString("間諜探測技術" , 18) , spy.star_->spy_level_);
    info.Format("%s%s" , tmp , str);
    
    tmp = info;
    str.Format("<br></br>%s%d" , FillString("武器技術" , 18) , spy.star_->ship_techs_.Weapon);
    info.Format("%s%s" , tmp , str);

    tmp = info;
    str.Format("<br></br>%s%d" , FillString("防禦盾系統" , 18) , spy.star_->ship_techs_.Shield);
    info.Format("%s%s" , tmp , str);

    tmp = info;
    str.Format("<br></br>%s%d" , FillString("船艦裝甲化" , 18) , spy.star_->ship_techs_.Armour);
    info.Format("%s%s" , tmp , str);
  }
  //hero
  if(s >= 10)
  {
    tmp = info;
    CString str;
    info.Format("%s<br></br>【英雄】" , tmp);
    tmp = info;
    if(spy.star_->double_res_hero)
    {
      str.Format("<br></br>银河地质学家      %d" , spy.star_->double_res_hero);
    }  
    info.Format("%s%s" , tmp , str);
  }

  info += "</font>";
  m_list.InsertItem(info , 0 , HTML_TEXT , AUTO , FALSE);  
  Item_Date* item = new Item_Date;
  item->type = REPORT_T_SPY;
  item->target_star_index = spy.star_->index_;
  DWORD d = DWORD(item);
  m_list.SetItemData(0 , d); 

  DisplayInfoNumber();
  GetCommander()->MessageNotify(m_list.GetItemCount() - old_info_number_);
}

void CPageInformation::ReportWarInfo(const War_info& war)
{
  CString info;
  TCHAR buf[64];
  TCHAR buf1[64];
  TCHAR buf2[64];
  TCHAR buf3[64];
  PlaniPos pos = Index2Pos(war.attack_star_index_);
  CTime t = CTime::GetCurrentTime();
  CString s;
  if(war.get_double_res_hero) s = "<br></br>(获得英雄：银河地质学家)";
  info.Format("<font color=#FF0000><b>战斗报告来自星座：%s（A：%s D：%s  废墟：%s）（%d-%02d-%02d %02d:%02d:%02d）</b>%s</font>" ,
   pos.ToCString(buf) , AddPointsToNumber(war.self_lost_ , buf1) , AddPointsToNumber(war.target_lost_ , buf2) ,
   AddPointsToNumber(war.recycled_res_ , buf3) , t.GetYear() , t.GetMonth() , t.GetDay() , t.GetHour() , t.GetMinute() , t.GetSecond() ,s);
  m_list.InsertItem(info , 0 , HTML_TEXT , AUTO , FALSE); 
  Item_Date* item = new Item_Date;
  item->type = REPORT_T_WAR;
  item->target_star_index = war.attack_star_index_;
  strcpy(item->report_file , war.battle_report_file_);
  DWORD d = DWORD(item);
  m_list.SetItemData(0 , d);
  DisplayInfoNumber();
  GetCommander()->MessageNotify(m_list.GetItemCount() - old_info_number_);
}

void CPageInformation::ReportFleetReach(const COMMAND_TASK& task)
{  
  CString info;
  TCHAR buf1[40];
  TCHAR buf2[40];
  PlaniPos pt(task.star->position_);
  PlaniPos ps(task.leave_pos);
  CTime t = CTime::GetCurrentTime();
  info.Format("<font color=#FFFFFF><b>您的一支舰队从 %s 到 %s（数量：%d，金属 %.0f 晶体 %.0f 重氢 %.0f"
    "）（%d-%02d-%02d %02d:%02d:%02d）</b></font>" ,
   pt.ToCString(buf1) , ps.ToCString(buf2) , GetFleetShipsNumber(task.fleet) , double(task.res.metal_) , double(task.res.crystal_) , double(task.res.diplogen_) , t.GetYear() , t.GetMonth() , t.GetDay() , t.GetHour() , t.GetMinute() , t.GetSecond());
  
  m_list.InsertItem(info , 0 , HTML_TEXT , AUTO , FALSE); 
  m_list.SetItemData(0 , 0);
  DisplayInfoNumber();
  GetCommander()->MessageNotify(m_list.GetItemCount() - old_info_number_);
}

void CPageInformation::ReportRecycleInfo(const COMMAND_TASK& task)
{
  CString info;
  TCHAR buf[40];
  PlaniPos pt(task.star->position_);
  CTime t = CTime::GetCurrentTime();
  info.Format("<font color=#FFFFFF><b>回收报告来自：%s（你的%.0f艘回收船共回收了 %.0f 金属和 %.0f 晶体"
    "）（%d-%02d-%02d %02d:%02d:%02d）</b></font>" ,
   pt.ToCString(buf) , task.fleet[BOAT_RECYCLE].Num, double(task.res.metal_) , double(task.res.crystal_), t.GetYear() , t.GetMonth() , t.GetDay() , t.GetHour() , t.GetMinute() , t.GetSecond());
  m_list.InsertItem(info , 0 , HTML_TEXT , AUTO , FALSE); 
  m_list.SetItemData(0 , 0);
  DisplayInfoNumber();
  GetCommander()->MessageNotify(m_list.GetItemCount() - old_info_number_);
}

void CPageInformation::ReportTransferInfo(const COMMAND_TASK& task)
{  
  CString info;
  TCHAR buf1[40];
  TCHAR buf2[40];
  PlaniPos pt(task.star->position_);
  PlaniPos ps(task.leave_pos);
  CTime t = CTime::GetCurrentTime();
  info.Format("<font color=#FFFFFF><b>您的一支舰队从 %s 运输金属 %.0f 晶体 %.0f 重氢 %.0f 到 %s"
    "）（%d-%02d-%02d %02d:%02d:%02d）</b></font>" ,
   ps.ToCString(buf1) , double(task.res.metal_) , double(task.res.crystal_) , double(task.res.diplogen_)  , pt.ToCString(buf2), t.GetYear() , t.GetMonth() , t.GetDay() , t.GetHour() , t.GetMinute() , t.GetSecond());
  
  m_list.InsertItem(info , 0 , HTML_TEXT , AUTO , FALSE); 
  m_list.SetItemData(0 , 0);
  DisplayInfoNumber();
  GetCommander()->MessageNotify(m_list.GetItemCount() - old_info_number_);
}

void CPageInformation::ReportColonyInfo(const COMMAND_TASK& task, bool bSuccess)
{  
  CString info;
  TCHAR buf1[40];
  TCHAR buf2[40];
  PlaniPos pt(task.star->position_);
  PlaniPos ps(task.leave_pos);
  CTime t = CTime::GetCurrentTime();
  if(bSuccess)
   info.Format("<font color=#FFFFFF><b>您的一支殖民舰队从 %s 到 %s 殖民成功，恭喜你多了一个殖民基地！"
    "）（%d-%02d-%02d %02d:%02d:%02d）</b></font>" ,
   ps.ToCString(buf1) , pt.ToCString(buf2) , t.GetYear() , t.GetMonth() , t.GetDay() , t.GetHour() , t.GetMinute() , t.GetSecond());
  else
    info = "非常不幸，由于某种原因导致您的殖民任务失败了，殖民舰队被摧毁！";  
  m_list.InsertItem(info , 0 , HTML_TEXT , AUTO , FALSE); 
  m_list.SetItemData(0 , 0);
  DisplayInfoNumber();
  GetCommander()->MessageNotify(m_list.GetItemCount() - old_info_number_);
}

BOOL CPageInformation::OnSetActive() 
{
  old_info_number_ = m_list.GetItemCount();	
	GetCommander()->MessageNotify(0L);
  DisplayInfoNumber();
	return CPageIcon::OnSetActive();
}

BOOL CPageInformation::OnKillActive() 
{
	old_info_number_ = m_list.GetItemCount();	
  GetCommander()->MessageNotify(0L);
  DisplayInfoNumber();
	return CPageIcon::OnKillActive();
}

void CPageInformation::OnBtnOk() 
{
	UpdateData(TRUE);
  if(m_list.GetItemCount() == 0)
    return;
  switch(m_op_option)
  {
  case DELETE_FLAG:
    DeleteInfo(DELETE_FLAG);
  	break;
  case DELETE_NO_FLAG:
    DeleteInfo(DELETE_NO_FLAG);
  	break;
  case DELETE_ALL:
    DeleteInfo(DELETE_ALL);
    break;
  default:
    assert(false);
    break;
  }	
}

void CPageInformation::DeleteInfo(int mode)
{
  vector<int> flags;
  int n = m_list.GetItemCount() - 1;
  for(int i = n ; i >= 0 ; --i)
  {
    if(mode == DELETE_FLAG)
    {
      if(m_list.GetItemCheck(i))
        flags.push_back(i);
    }
    else if(mode == DELETE_NO_FLAG)
    {
      if(!m_list.GetItemCheck(i))
        flags.push_back(i);
    }
    else if(mode == DELETE_ALL)
    {
      flags.push_back(i);
    }
  }
  for(i = 0 ; i < flags.size() ; ++i)
  {    
    if(m_bDeleteReporter)
    {
      DWORD d = m_list.GetItemData(flags[i]);
      Item_Date* item = (Item_Date*)d;
      if(item != 0 && item->type == REPORT_T_WAR)
      {
        DeleteFile(item->report_file);
      }
    }
    m_list.DeleteItem(flags[i]);
  }
  for(i = 0 ; i < m_list.GetItemCount() ; ++i)
  {
    m_list.SetItemCheck(i , FALSE);
  }
  m_list.AdjustScrollBar();
  m_list.RedrawWindow();
  DisplayInfoNumber();
}

UINT CPageInformation::GetFleetShipsNumber(const FLEET& ships)
{
  ULONG cnt = 0;
  for(int i = 0 ; i < ships.size() ; ++i)
  {
    cnt += ships[i].Num;
  }
  return cnt;
}

void CPageInformation::Notify_Exit()
{
  if(m_list.GetItemCount() == 0)
    return;
  m_list.DeleteAllItems();
}

void CPageInformation::OnBtnCopy() 
{
  if(m_list.GetItemCount() == 0)
  {
    return;
  }
  int sel = m_list.GetSelectedItem();
  if(sel == NONE_SELECTED)
  {
    AfxMessageBox("请先选中要复制的项目");
    return;
  }
  if ( !OpenClipboard() )
  {
    AfxMessageBox( "Cannot open the Clipboard" );
    return;
  }
  // Remove the current Clipboard contents
  if( !EmptyClipboard() )
  {
    AfxMessageBox( "Cannot empty the Clipboard" );
    return;
  }
  HGLOBAL hGlobal;		// Global memory handle
  LPSTR lpszData;			// Pointer to clipboard data
  unsigned long nSize;	// Size of clipboard data
  CString msg = m_list.GetItemText(sel);
  msg.Replace("<br></br>" , "\n");
  msg.Replace("<b>" , "");
  msg.Replace("</b>" , "");
  msg.Replace("<font color=#00FF00>" , "");
  msg.Replace("<font color=#FF0000>" , "");
  msg.Replace("<font color=#FFFFFF>" , "");
  msg.Replace("</font>" , "");

  nSize = msg.GetLength();
  if(nSize == 0)
  {
    CloseClipboard();	
    return;
  }
  char* buf = new char[nSize + 1];
  strcpy (buf, msg);	
  nSize = lstrlen(buf);  
  hGlobal = GlobalAlloc(GMEM_ZEROINIT, nSize+1);
  if (hGlobal == NULL){
    CloseClipboard();	
    delete[] buf;
    return;
  }
  lpszData = (LPSTR)GlobalLock(hGlobal);	
  for (UINT i = 0; i < nSize + 1; ++i)
    *(lpszData + i) = *(buf + i);				
  GlobalUnlock(hGlobal);
  ::SetClipboardData(CF_TEXT, hGlobal);
  CloseClipboard();	
  delete[] buf;  
}
