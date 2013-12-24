// pagepersoninfo.cpp : implementation file
//

#include "stdafx.h"
#include "..\XGame\xgame.h"
#include "pagepersoninfo.h"
#include "GameFileReader.h"
#include "communication.h"
#include "UStar.h"
#include "XGameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CPagePersonInfo dialog


CPagePersonInfo::CPagePersonInfo(UINT iconID /*= NULL*/ , CWnd* pParent /*=NULL*/)
: CPageIcon(CPagePersonInfo::IDD , iconID)
{
  //{{AFX_DATA_INIT(CPagePersonInfo)
	m_sort_type = SORT_BY_NAME;
	m_gala = 1;
	m_pos = 1;
	m_sys = 1;
	//}}AFX_DATA_INIT
}


void CPagePersonInfo::DoDataExchange(CDataExchange* pDX)
{
  CPageIcon::DoDataExchange(pDX);
  //{{AFX_DATA_MAP(CPagePersonInfo)
  DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Radio(pDX, IDC_RADIO1, m_sort_type);
	DDX_Text(pDX, IDC_EDIT_GALA, m_gala);
	DDV_MinMaxUInt(pDX, m_gala, 1, MAX_GALAXY_GALA);
	DDX_Text(pDX, IDC_EDIT_POS, m_pos);
	DDV_MinMaxUInt(pDX, m_pos, 1, MAX_GALAXY_POS);
	DDX_Text(pDX, IDC_EDIT_SYS, m_sys);
	DDV_MinMaxUInt(pDX, m_sys, 1, MAX_GALAXY_SYS);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPagePersonInfo, CPageIcon)
//{{AFX_MSG_MAP(CPagePersonInfo)
ON_WM_SIZE()
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_BTN_GO, OnBtnGo)
	ON_BN_CLICKED(IDC_BTN_GO_TARGET, OnBtnGoTarget)
	ON_EN_CHANGE(IDC_EDIT_GALA, OnChangeEditGala)
	ON_EN_CHANGE(IDC_EDIT_POS, OnChangeEditPos)
	ON_EN_CHANGE(IDC_EDIT_SYS, OnChangeEditSys)
	ON_BN_CLICKED(IDC_BTN_UPDATERANK, OnBtnUpdaterank)
	//}}AFX_MSG_MAP
  ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, OnSetItemColor)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPagePersonInfo message handlers

BOOL CPagePersonInfo::OnInitDialog() 
{
  CPageIcon::OnInitDialog();	
  Initialize();
  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}


void CPagePersonInfo::Initialize()
{
  m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);	
  m_list.InsertColumn(0 , "排名" , LVCFMT_CENTER , 140);
  m_list.InsertColumn(1 , "名称" , LVCFMT_CENTER , 190);
  m_list.InsertColumn(2 , "积分" , LVCFMT_CENTER , 190);
  m_list.InsertColumn(3 , "舰队" , LVCFMT_CENTER , 190);
  
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
}

void CPagePersonInfo::OnSize(UINT nType, int cx, int cy) 
{
  CPageIcon::OnSize(nType, cx, cy);	
}

void CPagePersonInfo::Notify_Init()
{
  UpdateListData();  
}

void CPagePersonInfo::Notify_Galaxy_Update()
{
  UpdateListData();  
}

void CPagePersonInfo::UpdateListData()
{
  UpdateData(TRUE);
  vector<Sort_Table_t>&table_stars = comm_->GetStarsTable();
  //sort
  if(m_sort_type == SORT_BY_NAME)
    sort(table_stars.begin() , table_stars.end() , greater_by_rank_functor<Sort_Table_t>() );
  else if(m_sort_type == SORT_BY_FLEET)
    sort(table_stars.begin() , table_stars.end() , greater_by_fleet_functor<Sort_Table_t>());
  else
    sort(table_stars.begin() , table_stars.end() , lower_by_position_functor<Sort_Table_t>());

  vector<Sort_Table_t> sort_stars;
  if(m_sort_type == SORT_BY_POSITION)
  {
    sort_stars = table_stars;
    sort(sort_stars.begin() , sort_stars.end() , greater_by_rank_functor<Sort_Table_t>() );
  }  

  CString info;
  CWaitCursor waitor;
  TCHAR buf[64];
  m_list.SetRedraw(FALSE);
  m_list.DeleteAllItems();
  ulong pos = 0;
  for(ulong i = 0 ; i < table_stars.size() ; ++i)
  {
    Sort_Table_t& node = table_stars[i];
    if(node.rank >= 1)
    {
      if(m_sort_type == SORT_BY_POSITION)
      {
        vector<Sort_Table_t>::iterator itor = 
          find_if(sort_stars.begin() , 
          sort_stars.end()   , 
          binder2nd< match_func<Sort_Table_t , int> >(match_func<Sort_Table_t , int>() , node.position) );
        info = "-1";
        if(itor != sort_stars.end())
        {
          ulong r = distance(sort_stars.begin() , itor) + 1;
          info.Format("%d" , r);
        }
      }
      else      
        info.Format("%d" , pos + 1);
      m_list.InsertItem(pos , info);
      
      m_list.SetItemText(pos , 1 , node.name);
      
      info.Format("%s" , AddPointsToNumber(node.rank , buf));
      m_list.SetItemText(pos , 2 , info);
      
      info.Format("%s" , AddPointsToNumber(node.fleet , buf));
      m_list.SetItemText(pos , 3 , info);  
      
      ++pos;      
    }
  } 
  m_list.SetRedraw(TRUE);  
}


void CPagePersonInfo::OnRadio1() 
{
  int type_buf = m_sort_type;
	UpdateData(TRUE);
  if(type_buf != m_sort_type)
  {
    UpdateListData();
  }	
}

void CPagePersonInfo::OnRadio2() 
{
	int type_buf = m_sort_type;
	UpdateData(TRUE);
  if(type_buf != m_sort_type)
  {
    UpdateListData();
  }	
}

void CPagePersonInfo::OnRadio3() 
{
	int type_buf = m_sort_type;
	UpdateData(TRUE);
  if(type_buf != m_sort_type)
  {
    UpdateListData();
  }		
}

void CPagePersonInfo::OnBtnGo() 
{
	for(int i = 0 ; i < m_list.GetItemCount() ; ++i)
  {
    if(m_list.GetItemText(i , 1).CompareNoCase(GetDataPtr()->GetLoginedAccountName()) == 0)
    { 
      m_list.SetFocus();
      m_list.EnsureVisible(i , FALSE);
      m_list.SetItemState(i, LVIS_FOCUSED|LVIS_SELECTED, LVIS_FOCUSED|LVIS_SELECTED);
      return;
    }
  }	
}

void CPagePersonInfo::OnSetItemColor(NMHDR* pNMHDR, LRESULT* pResult )
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
    if(m_list.GetItemText(pLVCD->nmcd.dwItemSpec , 1).CompareNoCase(GetDataPtr()->GetLoginedAccountName()) == 0)
    {
      pLVCD->clrText   = RGB(0 , 0 , 255);
      pLVCD->clrTextBk = RGB(0 , 255 , 0);
    }
    *pResult = CDRF_DODEFAULT;
  }
}

void CPagePersonInfo::ViewRank(PlaniPos pos , bool is_self)
{
  GetCommander()->SwitchToPage(this);
  CString info;
  char buf[40];
  for(int i = 0 ; i < m_list.GetItemCount() ; ++i)
  {
    if(is_self)
      info = GetDataPtr()->GetLoginedAccountName();
    else
      info = pos.ToCString(buf);
    if(m_list.GetItemText(i , 1).CompareNoCase(info) == 0)
    { 
      m_list.SetFocus();
      m_list.EnsureVisible(i , FALSE);
      m_list.SetItemState(i, LVIS_FOCUSED|LVIS_SELECTED, LVIS_FOCUSED|LVIS_SELECTED);
      return;
    }
  }
}

void CPagePersonInfo::OnBtnGoTarget() 
{
	UpdateData(TRUE);	
  PlaniPos pos(m_gala , m_sys , m_pos);
  ViewRank(pos , false);
}

void CPagePersonInfo::OnChangeEditGala() 
{
	UpdateData(TRUE);	
  m_gala = m_gala > MAX_GALAXY_GALA ? MAX_GALAXY_GALA : m_gala;
  m_gala = m_gala < 1 ? 1 : m_gala;
  UpdateData(FALSE);	
}

void CPagePersonInfo::OnChangeEditPos() 
{
	UpdateData(TRUE);		
  m_pos = m_pos > MAX_GALAXY_POS ? MAX_GALAXY_POS : m_pos;
  m_pos = m_pos < 1 ? 1 : m_pos;
  UpdateData(FALSE);	
}

void CPagePersonInfo::OnChangeEditSys() 
{
	UpdateData(TRUE);	
  m_sys = m_sys > MAX_GALAXY_SYS ? MAX_GALAXY_SYS : m_sys;
  m_sys = m_sys < 1 ? 1 : m_sys;
  UpdateData(FALSE);	
}

void CPagePersonInfo::OnBtnUpdaterank() 
{
	comm_->UpdateGalaxyRank();	
  UpdateListData();  
}

void CPagePersonInfo::UpdateRank()
{
  comm_->UpdateGalaxyRank();	
  UpdateListData();  
}

void CPagePersonInfo::GetMyRank(uchar& rank_type , int& rank)
{
  rank_type = m_sort_type;
  for(ushort i = 0 ; i < m_list.GetItemCount() ; ++i)
  {
    if(m_list.GetItemText(i , 1).CompareNoCase(GetDataPtr()->GetLoginedAccountName()) == 0)
    { 
      rank = atoi(m_list.GetItemText(i , 0));
      return;
    }
  }	
  rank = -1;
}