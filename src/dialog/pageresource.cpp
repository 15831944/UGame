// pageresource.cpp : implementation file
//

#include "stdafx.h"
#include "..\XGame\xgame.h"
#include "pageresource.h"
#include "BuildingsKeeper.h"
#include "Building.h"
#include "XGameDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CPageResource::CPageResource(UINT iconID /*= NULL*/ , CWnd* pParent /*=NULL*/)
	: CPageIcon(CPageResource::IDD , iconID)
{
	//{{AFX_DATA_INIT(CPageResource)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  menu.LoadMenu(IDR_MENU_REDOURCE_PERCENT);  
}


void CPageResource::DoDataExchange(CDataExchange* pDX)
{
	CPageIcon::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageResource)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageResource, CPageIcon)
	//{{AFX_MSG_MAP(CPageResource)
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, OnRclickList1)
	ON_COMMAND(ID_MENU_RESOURCE_P00, OnMenuResourceP00)
	ON_COMMAND(ID_MENU_RESOURCE_P10, OnMenuResourceP10)
	ON_COMMAND(ID_MENU_RESOURCE_P100, OnMenuResourceP100)
	ON_COMMAND(ID_MENU_RESOURCE_P20, OnMenuResourceP20)
	ON_COMMAND(ID_MENU_RESOURCE_P30, OnMenuResourceP30)
	ON_COMMAND(ID_MENU_RESOURCE_P40, OnMenuResourceP40)
	ON_COMMAND(ID_MENU_RESOURCE_P50, OnMenuResourceP50)
	ON_COMMAND(ID_MENU_RESOURCE_P60, OnMenuResourceP60)
	ON_COMMAND(ID_MENU_RESOURCE_P70, OnMenuResourceP70)
	ON_COMMAND(ID_MENU_RESOURCE_P80, OnMenuResourceP80)
	ON_COMMAND(ID_MENU_RESOURCE_P90, OnMenuResourceP90)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	//}}AFX_MSG_MAP
  ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST1, OnSetItemColor)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageResource message handlers

BOOL CPageResource::OnInitDialog() 
{
	CPageIcon::OnInitDialog();
  CRect rect;
  GetClientRect(&rect);
  m_list.MoveWindow(0 , 0 , rect.Width() , rect.Height());
  m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
  m_list.InsertColumn(0  , "    " , LVCFMT_LEFT , 170);
  m_list.InsertColumn(1  , "金属" , LVCFMT_LEFT , 110); 
  m_list.InsertColumn(2  , "晶体" , LVCFMT_LEFT , 110);
  m_list.InsertColumn(3  , "重氢" , LVCFMT_LEFT , 110);
  m_list.InsertColumn(4  , "能量" , LVCFMT_LEFT , 110);	
  m_list.InsertColumn(5  , "生产率" , LVCFMT_LEFT , 110);	

  m_list.SetBkColor(RGB(55 , 79 , 112));
  m_list.SetTextBkColor(RGB(55 , 79 , 112));
  m_list.SetTextColor(RGB(231 , 233 ,234));
  
#ifdef LISTCTRL_USING_MY_FONT
  LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 14;
	strcpy(lf.lfFaceName, "新宋体");
	font.CreateFontIndirect(&lf);
	m_list.SetFont(&font, TRUE);
#endif
  buff_solar_plant_ = GetDataPtr()->GetBoatNumber(BOAT_SUNPOWER_PLANET);
  UpdateListData();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageResource::UpdateListData()
{
  if(m_hWnd == NULL)
    return;
  CString info;  
  m_list.SetRedraw(FALSE);
  m_list.DeleteAllItems();

  info.Format("金属提炼厂（Level：%d）", GetDataPtr()->GetBuildingLevel(FACTORY_BUILDING_MINAL));
  m_list.InsertItem(FACTORY_BUILDING_MINAL ,    info);

  info.Format("晶体提炼厂（Level：%d）", GetDataPtr()->GetBuildingLevel(FACTORY_BUILDING_CRYSTAL));
  m_list.InsertItem(FACTORY_BUILDING_CRYSTAL ,  info);

  info.Format("重氢压缩厂（Level：%d）", GetDataPtr()->GetBuildingLevel(FACTORY_BUILDING_DIPLOGEN));
  m_list.InsertItem(FACTORY_BUILDING_DIPLOGEN , info);

  info.Format("太阳能工厂（Level：%d）", GetDataPtr()->GetBuildingLevel(FACTORY_BUILDING_SUNPOWER));
  m_list.InsertItem(FACTORY_BUILDING_SUNPOWER , info);

  info.Format("太阳能卫星（%d）" , GetDataPtr()->GetBoatNumber(BOAT_SUNPOWER_PLANET));
  m_list.InsertItem(4 , info);

  m_list.InsertItem(5 , "合计");

  int total_metal = 0;
  int total_crys = 0;
  int total_dipl = 0;
  int total_power = 0;

  for(int i = FACTORY_BUILDING_START ; i <= FACTORY_BUILDING_PRODUCE_MAX ; ++i)
  {
    total_metal += int(Buildings_Entry(i)->ProduceMinal() * 60);
    info.Format("%d" , int(Buildings_Entry(i)->ProduceMinal() * 60));
    m_list.SetItemText(i , 1 , info);

    total_crys += int(Buildings_Entry(i)->ProduceCrystal() * 60);
    info.Format("%d" , int(Buildings_Entry(i)->ProduceCrystal() * 60));
    m_list.SetItemText(i , 2 , info);

    total_dipl += int(Buildings_Entry(i)->ProduceDiplogen() * 60);
    info.Format("%d" , int(Buildings_Entry(i)->ProduceDiplogen() * 60));
    m_list.SetItemText(i , 3 , info);
    if(i == FACTORY_BUILDING_SUNPOWER)
    {
      total_power += Buildings_Entry(i)->ProducePower();
      info.Format("%d" , Buildings_Entry(i)->ProducePower() );
      m_list.SetItemText(i , 4 , info);
    }
    else
    {
      total_power -= Buildings_Entry(i)->GetConsumePower();
      info.Format("-%d" , Buildings_Entry(i)->GetConsumePower() );
      m_list.SetItemText(i , 4 , info);
    }    
    info.Format("%d%%" , int(100 * Buildings_Entry(i)->GetProducePercent()));
    m_list.SetItemText(i , 5 , info);
  }

  //sun power planet
  m_list.SetItemText(4 , 1 , _T("0"));
  m_list.SetItemText(4 , 2 , _T("0"));
  m_list.SetItemText(4 , 3 , _T("0"));
  info.Format("%d" , int(GetDataPtr()->GetBoatNumber(BOAT_SUNPOWER_PLANET) * (20 + GetDataPtr()->STAR_TEMP() / 4.0)));
  m_list.SetItemText(4 , 4 , info);
  m_list.SetItemText(4 , 5 , _T("100%（Fixed）"));

  //adjust power
  total_power += GetDataPtr()->GetBoatNumber(BOAT_SUNPOWER_PLANET) * (20 + GetDataPtr()->STAR_TEMP() / 4.0);

  //total
  info.Format("%d" , total_metal);
  m_list.SetItemText(5 , 1 , info);

  info.Format("%d" , total_crys);
  m_list.SetItemText(5 , 2 , info);

  info.Format("%d" , total_dipl);
  m_list.SetItemText(5 , 3 , info);

  info.Format("%d" , total_power);
  m_list.SetItemText(5 , 4 , info);

  info.Format("%0.3f" , Building::GetTotalProducePercent());
  m_list.SetItemText(5 , 5 , info);

  m_list.SetRedraw(TRUE);
}

void CPageResource::Notify_Building_LevelUp()
{
  if(m_hWnd == NULL)
    return;
  UpdateListData();
}

void CPageResource::OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
  POSITION pos = m_list.GetFirstSelectedItemPosition();
  //not sel
  if(pos == NULL) return;
  int sel = int(pos) - 1;
  //invalid
  if(sel >= 4) return;
  
  menu.CheckMenuRadioItem(ID_MENU_RESOURCE_P100 , ID_MENU_RESOURCE_P00 , ID_MENU_RESOURCE_P00 - GetCurrentPercentIndex(sel) , MF_BYCOMMAND);
  menu.GetSubMenu(0)->SetDefaultItem(ID_MENU_RESOURCE_P100);

	CPoint pt;
  GetCursorPos(&pt);
  menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN,pt.x , pt.y , this , NULL);	
	*pResult = 0;
}

int CPageResource::GetCurrentPercentIndex(int building_index)
{
  double p = Buildings_Entry(building_index)->GetProducePercent();
  unsigned long i = (unsigned long)(p * 10.0);
  if(p - i >= 0.5) 
    return i + 1;
  return i;
}

void CPageResource::OnMenuResourceP00() 
{
  ChangePercent(0);
}

void CPageResource::OnMenuResourceP10() 
{
	ChangePercent(1);	
}

void CPageResource::OnMenuResourceP20() 
{
	ChangePercent(2);	
	
}

void CPageResource::OnMenuResourceP30() 
{
	ChangePercent(3);	
	
}

void CPageResource::OnMenuResourceP40() 
{
	ChangePercent(4);	
	
}

void CPageResource::OnMenuResourceP50() 
{
	ChangePercent(5);	
	
}

void CPageResource::OnMenuResourceP60() 
{
	ChangePercent(6);	
	
}

void CPageResource::OnMenuResourceP70() 
{
	ChangePercent(7);	
	
}

void CPageResource::OnMenuResourceP80() 
{
	ChangePercent(8);	
	
}

void CPageResource::OnMenuResourceP90() 
{
	ChangePercent(9);	
	
}

void CPageResource::OnMenuResourceP100() 
{
	ChangePercent(10);	
	
}

void CPageResource::ChangePercent(int level)
{
  int sel = int(m_list.GetFirstSelectedItemPosition()) - 1;
  if(sel < 0 || sel >= 4)
    return;
  assert(sel >= 0 && sel < 4);
  Buildings_Entry(sel)->SetProducePercent(level * 0.1);
  GetCommander()->Notify_Building_ProducePercent_Changed(sel , level * 0.1);
  menu.CheckMenuRadioItem(ID_MENU_RESOURCE_P100 , ID_MENU_RESOURCE_P00 , ID_MENU_RESOURCE_P00 - level , MF_BYCOMMAND);
  UpdateListData();
}

void CPageResource::OnSetItemColor(NMHDR* pNMHDR, LRESULT* pResult )
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
    COLORREF crText = RGB(231 , 233 ,234);      
    if ( (pLVCD->iSubItem == 1 && pLVCD->nmcd.dwItemSpec  == 0) ||
         (pLVCD->iSubItem == 2 && pLVCD->nmcd.dwItemSpec  == 1) ||
         (pLVCD->iSubItem == 3 && pLVCD->nmcd.dwItemSpec  == 2) ||
         (pLVCD->iSubItem == 4 && pLVCD->nmcd.dwItemSpec  == 3) ||
         (pLVCD->iSubItem == 4 && pLVCD->nmcd.dwItemSpec  == 4) ||
         (pLVCD->iSubItem == 5 && pLVCD->nmcd.dwItemSpec  == 5) )
    {
      crText = RGB(255 , 255 ,0);
    }
    else if ((pLVCD->iSubItem == 4 && pLVCD->nmcd.dwItemSpec  == 0) ||
             (pLVCD->iSubItem == 4 && pLVCD->nmcd.dwItemSpec  == 1) ||
             (pLVCD->iSubItem == 4 && pLVCD->nmcd.dwItemSpec  == 2) )
    {
      crText = RGB(255, 0 ,0);
    }
    pLVCD->clrText = crText;
    *pResult = CDRF_DODEFAULT;
  }
}

void CPageResource::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
  POSITION pos = m_list.GetFirstSelectedItemPosition();
  //not sel
  if(pos == NULL) return;
  int sel = int(pos) - 1;
  //invalid
  if(sel >= 4) return;	
  ChangePercent(10);	  
	*pResult = 0;
}

void CPageResource::Notify_Ships_Changed()
{
  if(m_hWnd == NULL)
    return;
  ulong curr_solar_plant_ = GetDataPtr()->GetBoatNumber(BOAT_SUNPOWER_PLANET);
  //compare
  if(curr_solar_plant_ != buff_solar_plant_)
  {
    //update list
    UpdateListData();
    //update buff
    buff_solar_plant_ = curr_solar_plant_;
  }  
}
