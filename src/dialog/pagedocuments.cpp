// pagedocuments.cpp : implementation file
//

#include "stdafx.h"
#include "..\XGame\xgame.h"
#include "pagedocuments.h"

#include "ResearchKeeper.h"
#include "ResearchTechnics.h"

#include "BuildingsKeeper.h"
#include "Building.h"

#include "BoatsKeeper.h"
#include "Spaceship.h"

#include "ElapsedTimer.h"
#include "XGameDlg.h"

#include "HighFrequencyElapsedTimer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

enum
{
  ROOT_FACTORY,
  ROOT_RESEARCH,
  ROOT_SHIPS,
  ROOT_DEPENPS,
};

const int MAX_LEVEL = 50;

CPageDocuments::CPageDocuments(UINT iconID /*= NULL*/ , CWnd* pParent /*=NULL*/)
	: CPageIcon(CPageDocuments::IDD, iconID)
{
	//{{AFX_DATA_INIT(CPageDocuments)
	//}}AFX_DATA_INIT
   find_first_ = 0;
   find_second_ = 0;
}


void CPageDocuments::DoDataExchange(CDataExchange* pDX)
{
	CPageIcon::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageDocuments)
	DDX_Control(pDX, IDC_LIST_DETAILS, m_list);
	DDX_Control(pDX, IDC_TREE1, m_tree);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageDocuments, CPageIcon)
	//{{AFX_MSG_MAP(CPageDocuments)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnSelchangedTree1)
	ON_WM_DESTROY()
	ON_NOTIFY(NM_DBLCLK, IDC_TREE1, OnDblclkTree1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CPageDocuments::TreeItemData_t::TreeItemData_t(int l , int i , int pi , const CString& n)
:layer(l) , index(i) , parent_index(pi) , name(n)
{

}

BOOL CPageDocuments::OnInitDialog() 
{
	CPageIcon::OnInitDialog();	
	Initialize();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CPageDocuments::Initialize()
{
//  m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT);
  CreateImageList();
  InitTree();
}

void CPageDocuments::CreateImageList()
{
  BOOL	bRetValue = FALSE;
  HICON	hIcon = NULL;
  
  // Create image list
  bRetValue = m_image_index.Create(20, 20, ILC_COLOR32 | ILC_MASK , 5 , 1);
  ASSERT(bRetValue == TRUE);  
 
  // Add some icons
  hIcon = AfxGetApp()->LoadIcon(IDI_GUI_FACTORY);
  m_image_index.Add(hIcon);
  // Add some icons
  hIcon = AfxGetApp()->LoadIcon(IDI_GUI_RESEARCH);
  m_image_index.Add(hIcon);
  // Add some icons
  hIcon = AfxGetApp()->LoadIcon(IDI_GUI_BOATYARD);
  m_image_index.Add(hIcon);
  // Add some icons
  hIcon = AfxGetApp()->LoadIcon(IDI_ICON_MINAL_FACTORY);
  m_image_index.Add(hIcon);

  hIcon = AfxGetApp()->LoadIcon(IDI_ICON_CRYCALFACTORY);
  m_image_index.Add(hIcon);

  hIcon = AfxGetApp()->LoadIcon(IDI_ICON_DIPOFACTORY);
  m_image_index.Add(hIcon);

  hIcon = AfxGetApp()->LoadIcon(IDI_ICON_SUNPOWERFACTORY);
  m_image_index.Add(hIcon);

  hIcon = AfxGetApp()->LoadIcon(IDI_ICON_ROBERTFACTORY);
  m_image_index.Add(hIcon);

  hIcon = AfxGetApp()->LoadIcon(IDI_ICON_LABFACTORY);
  m_image_index.Add(hIcon);

  hIcon = AfxGetApp()->LoadIcon(IDI_ICON_BOATYARD);
  m_image_index.Add(hIcon);

  hIcon = AfxGetApp()->LoadIcon(IDI_ICON_NATITEFACTORY);
  m_image_index.Add(hIcon);

  //
  hIcon = AfxGetApp()->LoadIcon(IDI_TECH_ICON_SPY);
  m_image_index.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_TECH_ICON_COMPUTER);
  m_image_index.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_TECH_ICON_ATTACK);
  m_image_index.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_TECH_ICON_SHEILED);
  m_image_index.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_TECH_ICON_DEFENSE);
  m_image_index.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_TECH_ICON_POWER);
  m_image_index.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_TECH_ICON_SUPERTECH);
  m_image_index.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_TECH_ICON_BURNING);
  m_image_index.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_TECH_ICON_PULSE);
  m_image_index.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_TECH_ICON_SUPERSPACE);
  m_image_index.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_TECH_ICON_DENGLIZI);
  m_image_index.Add(hIcon);
  hIcon = AfxGetApp()->LoadIcon(IDI_TECH_ICON_GRAVITION);
  m_image_index.Add(hIcon);
}

void CPageDocuments::InitTree()
{
  m_tree.SetImageList(&m_image_index,TVSIL_NORMAL);
  HTREEITEM rootItem;
  HTREEITEM childItem;

  rootItem = m_tree.InsertItem(_T("生产工厂"),  0 , 0);
  m_tree.SetItemData(rootItem , DWORD(new TreeItemData_t(0 , ROOT_FACTORY , -1 , _T("生产工厂"))));
  for(int i = 0 ; i < building_keeper_->Size() ; ++i)
  {
    childItem = m_tree.InsertItem(Buildings_Entry(i)->GetName() , 3 + i , 3 + i , rootItem);
    m_tree.SetItemData(childItem , DWORD(new TreeItemData_t(1 , i , ROOT_FACTORY , Buildings_Entry(i)->GetName())));
  }

  rootItem = m_tree.InsertItem(_T("科学研究"),  1 , 1);
  m_tree.SetItemData(rootItem , DWORD(new TreeItemData_t(0 , ROOT_RESEARCH , -1 , _T("科学研究"))));
  for( i = 0 ; i < research_keeper_->Size() ; ++i)
  {
    childItem = m_tree.InsertItem(Researchs_Entry(i)->GetName() , 11 + i , 11 + i , rootItem);
    m_tree.SetItemData(childItem , DWORD(new TreeItemData_t(1 , i , ROOT_RESEARCH , Researchs_Entry(i)->GetName())));
  }

  rootItem = m_tree.InsertItem(_T("舰队资料"),  2 , 2);
  m_tree.SetItemData(rootItem , DWORD(new TreeItemData_t(0 , ROOT_SHIPS , -1 , _T("舰队资料"))));


  rootItem = m_tree.GetRootItem();
  m_tree.SelectItem(rootItem);
  m_tree.Expand(rootItem ,TVE_EXPAND  );
  
  childItem = m_tree.GetNextSiblingItem(rootItem);
  m_tree.Expand(childItem ,TVE_EXPAND  );

}

void CPageDocuments::OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	HTREEITEM item = m_tree.GetSelectedItem();
  if(item == NULL) return;

  TreeItemData_t* data = (TreeItemData_t*)(m_tree.GetItemData(item));
  //first layer
  if(data->layer == 0)
  {
    if(data->index == ROOT_SHIPS)
    {
      DisplayShips(data->index);
    }
    else
    {
      DisplayDummy(data->index);
    }
  } 
 	//first layer
  else if(data->layer == 1)
  {
    //factorys
    if(data->parent_index == ROOT_FACTORY)
    {
      DisplayFactory(data->index);
    }
    else if(data->parent_index == ROOT_RESEARCH)
    {
      DisplayResearch(data->index);
    }
  } 
	*pResult = 0;
}


void CPageDocuments::DisplayFactory(int index)
{
  assert(index >= 0 && index < FACTORY_BUILDINGS_MAX);
  CString info;
  m_list.DeleteAllItems();
  DeleteAllColumns();
  m_list.InsertColumn(0 , "等级" , LVCFMT_LEFT , 40);
  m_list.InsertColumn(1 , "升级金属" , LVCFMT_LEFT , 90);
  m_list.InsertColumn(2 , "升级晶体" , LVCFMT_LEFT , 90);
  m_list.InsertColumn(3 , "升级重氢" , LVCFMT_LEFT , 90);
  m_list.InsertColumn(4 , "产生能量" , LVCFMT_LEFT , 90);
  m_list.InsertColumn(5 , "升级时间" , LVCFMT_LEFT , 100); 
  m_list.InsertColumn(6 , "生产金属" , LVCFMT_LEFT , 90); 
  m_list.InsertColumn(7 , "生产晶体" , LVCFMT_LEFT , 90); 
  m_list.InsertColumn(8 , "生产重氢" , LVCFMT_LEFT , 90); 
  for(int i = 0 ; i < MAX_LEVEL ; ++i)
  {
    info.Format("%d" , i);
    m_list.InsertItem(i , info);
    double m = 0.0;
    double c = 0.0;
    double d = 0.0;

    if(index > FACTORY_BUILDING_PRODUCE_MAX)
    {
      m = get_other_factory_upgrade_resource(FACTORY_DATA[index][FACTORY_TBL_N_METAL] , i);
      c = get_other_factory_upgrade_resource(FACTORY_DATA[index][FACTORY_TBL_N_CRYSTAL] , i);
      d = get_other_factory_upgrade_resource(FACTORY_DATA[index][FACTORY_TBL_N_DIPLOGEN] , i);
    }
    else
    {
      m = get_produce_factory_upgrade_resource(FACTORY_DATA[index][FACTORY_TBL_N_METAL] , i);
      c = get_produce_factory_upgrade_resource(FACTORY_DATA[index][FACTORY_TBL_N_CRYSTAL] , i);
      d = get_produce_factory_upgrade_resource(FACTORY_DATA[index][FACTORY_TBL_N_DIPLOGEN] , i);
    }
    //metal
    info.Format("%.0f" ,  m);
    m_list.SetItemText(i , 1 , info);

    //crystal
    info.Format("%.0f" ,  c);
    m_list.SetItemText(i , 2 , info);

    //diplogen
    info.Format("%.0f" ,  d);
    m_list.SetItemText(i , 3 , info);

    //sun power factory
    int p = get_produce_factory_consume_power(FACTORY_DATA[index][FACTORY_TBL_POWER] , i , 1.0);
    info.Format("%d" , p );
    if(index != FACTORY_BUILDING_SUNPOWER && p != 0)
    { 
      info.Format("-%d" , p );
    }
    m_list.SetItemText(i , 4 , info);

    //time
    double t = get_factory_upgrade_seconds(GetDataPtr()->GetBuildingLevel(FACTORY_BUILDING_ROBOT) , GetDataPtr()->GetBuildingLevel(FACTORY_BUILDING_NANITE) , m , c , 1.0);
    ElapsedTimer timer;
    timer.Init(t);
    m_list.SetItemText(i , 5 , timer.ToCString());

    //produce metal
    ulong a = 0;
    if(index == FACTORY_BUILDING_MINAL)
      a = 20;
    m = get_produce_factory_produce_resource_per_minute(a , FACTORY_DATA[index][FACTORY_TBL_P_METAL] , i , 1.0 , 1.0) * 
      pow(2 , GetDataPtr()->GET_STAR_DOUBLE_RES_HERO());
    info.Format("%.0f" , m * 60);
    m_list.SetItemText(i , 6 , info);

    //produce crystal
    a = 0;
    if(index == FACTORY_BUILDING_CRYSTAL)
      a = 10;
    c = get_produce_factory_produce_resource_per_minute(a , FACTORY_DATA[index][FACTORY_TBL_P_CRYSTAL] , i , 1.0 , 1.0) * 
      pow(2 , GetDataPtr()->GET_STAR_DOUBLE_RES_HERO());
    info.Format("%.0f" , c * 60);
    m_list.SetItemText(i , 7 , info);

    //produce diplogen
    d = (-0.002 * GetDataPtr()->STAR_TEMP() + 1.28 ) * 
      get_produce_factory_produce_resource_per_minute(0 , FACTORY_DATA[index][FACTORY_TBL_P_DIPLOGEN] , i , 1.0 , 1.0) * 
      pow(2 , GetDataPtr()->GET_STAR_DOUBLE_RES_HERO());
    info.Format("%.0f" , d * 60);
    m_list.SetItemText(i , 8 , info);
  }
  m_list.SetItemBkColor(Buildings_Entry(index)->GetLevel() , -1 , RGB(0 , 255 , 0));
}

void CPageDocuments::DisplayShips(int index)
{
  CString info;
  m_list.DeleteAllItems();
  DeleteAllColumns();
  m_list.InsertColumn(0 , "船舰名字" , LVCFMT_LEFT , 100);
  m_list.InsertColumn(1 , "建造金属" , LVCFMT_LEFT , 80);
  m_list.InsertColumn(2 , "建造晶体" , LVCFMT_LEFT , 80);
  m_list.InsertColumn(3 , "建造重氢" , LVCFMT_LEFT , 80);
  m_list.InsertColumn(4 , "建造时间" , LVCFMT_LEFT , 80); 
  m_list.InsertColumn(5 , "攻击能力" , LVCFMT_LEFT , 80); 
  m_list.InsertColumn(6 , "运载能力" , LVCFMT_LEFT , 80); 
  m_list.InsertColumn(7 , "飞行速度" , LVCFMT_LEFT , 80); 
  m_list.InsertColumn(8 , "技术需求" , LVCFMT_LEFT , 250);

  for(int i = 0 ; i < BOAT_MAX ; ++i)
  {
    info.Format("%s" , BOATS_NAME[i]);
    m_list.InsertItem(i , info);

   //metal
    info.Format("%d" , BOATS_RESOURCE_NEED_BASE[i][0] );
    m_list.SetItemText(i , 1 , info);

    //crystal
    info.Format("%d" , BOATS_RESOURCE_NEED_BASE[i][1] );
    m_list.SetItemText(i , 2 , info);

    //diplogen
    info.Format("%d" , BOATS_RESOURCE_NEED_BASE[i][2] );
    m_list.SetItemText(i , 3 , info);

    //time
    double t = get_boat_produce_seconds(
                        GetDataPtr()->GetBuildingLevel(FACTORY_BUILDING_BOATYARD), //shipyard level
                        GetDataPtr()->GetBuildingLevel(FACTORY_BUILDING_NANITE),   //nanitefactory level
                        BOATS_RESOURCE_NEED_BASE[i][0] , 
                        BOATS_RESOURCE_NEED_BASE[i][1], 
                        1.0);
    
    HighFrequencyElapsedTimer timer;
    timer.Init(t * 1000);
    m_list.SetItemText(i , 4 , timer.ToCString());

    //attack force
    info.Format("%d" , UINT(SHIP_ATTACK_FORCE_BASE[i] * (1 + 0.1 * GetDataPtr()->GetResearchLevel(RESEARCH_WEAPON))) );
    m_list.SetItemText(i , 5 , info);

    //transfer capacity force    
    info.Format("%d" , SHIP_TRANSFER_CAPACITY[i] );
    m_list.SetItemText(i , 6 , info);

    //speed
    info.Format("%d" , kernel_.GetShipSpeed(ITEM_TYPE(i) , 0));
    m_list.SetItemText(i , 7 , info);

    //tech needed    
    m_list.SetItemText(i , 8 , Boats_Entry(i)->GetTechNeeded());
   }
}

void CPageDocuments::DisplayResearch(int index)
{
  assert(index >= 0 && index < RESEARCH_MAX);
  CString info;
  m_list.DeleteAllItems();
  DeleteAllColumns();
  m_list.InsertColumn(0 , "等级" , LVCFMT_LEFT ,     40);
  m_list.InsertColumn(1 , "升级金属" , LVCFMT_LEFT , 130);
  m_list.InsertColumn(2 , "升级晶体" , LVCFMT_LEFT , 130);
  m_list.InsertColumn(3 , "升级重氢" , LVCFMT_LEFT , 130);
  m_list.InsertColumn(4 , "升级时间" , LVCFMT_LEFT , 130); 

  for(int i = 0 ; i < MAX_LEVEL ; ++i)
  {
    info.Format("%d" , i);
    m_list.InsertItem(i , info);

   //metal
    info.Format("%.0f" , get_research_upgrade_resource(RESEARCH_RESOURCE_NEED_BASE[index][0] , i) );
    m_list.SetItemText(i , 1 , info);

    //crystal
    info.Format("%.0f" , get_research_upgrade_resource(RESEARCH_RESOURCE_NEED_BASE[index][1] , i) );
    m_list.SetItemText(i , 2 , info);

    //diplogen
    info.Format("%.0f" , get_research_upgrade_resource(RESEARCH_RESOURCE_NEED_BASE[index][2] , i));
    m_list.SetItemText(i , 3 , info);

    //time
    double t = get_research_upgrade_seconds(
                        GetDataPtr()->GetBuildingLevel(FACTORY_BUILDING_LAB),  //LabFactory level
                        GetDataPtr()->GetBuildingLevel(FACTORY_BUILDING_NANITE),         //nanitefactory level
                        get_research_upgrade_resource(RESEARCH_RESOURCE_NEED_BASE[index][0] , i)   , 
                        get_research_upgrade_resource(RESEARCH_RESOURCE_NEED_BASE[index][1] , i)   , 
                        1.0);
    ElapsedTimer timer;
    timer.Init(t);
    m_list.SetItemText(i , 4 , timer.ToCString());
   }
  m_list.SetItemBkColor(Researchs_Entry(index)->GetLevel() , -1 , RGB(0 , 255 , 0));
}

void CPageDocuments::DeleteAllColumns()
{
//  m_list.DeleteAllColumns();
  while (m_list.GetHeaderCtrl()->GetItemCount() > 0)
		m_list.DeleteColumn(0);
}

void CPageDocuments::DisplayDummy(int index)
{
  assert(index == ROOT_FACTORY || index == ROOT_RESEARCH);
  CString info;
  m_list.DeleteAllItems();
  DeleteAllColumns();
  if(index == ROOT_FACTORY)
  {
    m_list.InsertColumn(0 , "帝国生产工厂" , LVCFMT_LEFT , 100);
    m_list.InsertColumn(1 , "技术需求" , LVCFMT_LEFT , 180);
    m_list.InsertColumn(2 , "描述" , LVCFMT_LEFT , 530);


    for(int i = 0 ; i < building_keeper_->Size() ; ++i)
    {
      m_list.InsertItem(i , Buildings_Entry(i)->GetName());
      m_list.SetItemText(i , 1 , Buildings_Entry(i)->GetCanlevelString());
      m_list.SetItemText(i , 2 , Buildings_Entry(i)->GetSimpleDisp());
    }
  }
  else if(index == ROOT_RESEARCH)
  {
    m_list.InsertColumn(0 , "帝国科学研究" , LVCFMT_LEFT , 90);
    m_list.InsertColumn(1 , "技术需求" , LVCFMT_LEFT , 180);
    m_list.InsertColumn(2 , "描述" , LVCFMT_LEFT , 650);


    for(int i = 0 ; i < research_keeper_->Size() ; ++i)
    {
      m_list.InsertItem(i , Researchs_Entry(i)->GetName());
      m_list.SetItemText(i , 1 , Researchs_Entry(i)->GetTechNeeded());
      m_list.SetItemText(i , 2 , Researchs_Entry(i)->GetSimpleDisp());
    }
  }
}

void CPageDocuments::ParseTree(PARSING_FUNCTION pf, HTREEITEM hti /* = TVI_ROOT */,
                              void *pvParam /* = NULL */)
{
  if (hti == TVI_ROOT)
  {
     hti = m_tree.GetRootItem(); 
  }
  else
  {
    hti = m_tree.GetChildItem(hti); 
  }
  while(hti != NULL)
  {
    (this->*pf)(hti, pvParam);
    ParseTree(pf, hti, pvParam);
    hti = m_tree.GetNextSiblingItem(hti);
  }
}

void CPageDocuments::pfClear(HTREEITEM hti, void *)
{
  ASSERT(hti != NULL);
  DWORD data = m_tree.GetItemData(hti);
  TreeItemData_t* finding_item = (TreeItemData_t*)data;
  delete finding_item;
  finding_item = NULL;  
}

void CPageDocuments::OnDestroy() 
{
  ParseTree(pfClear);
	CPageIcon::OnDestroy();	
}

void CPageDocuments::ShowDocument(int first , int second)
{
  find_first_ = first;
  find_second_ = second;
  cur_sel_item_ = NULL;
  HTREEITEM item = m_tree.GetRootItem();

  //first layer
  if(first == 0)
  {
    if(second == -1)
    {
      m_tree.SelectItem(item);
    }
    else if(second >= 0 && second < FACTORY_BUILDINGS_MAX)
    {     
      FindItem(pfFindItem);
      if(cur_sel_item_ != NULL)
      {
        m_tree.SelectItem(m_tree.GetRootItem());
        m_tree.SelectItem(cur_sel_item_);
      }
    }
  } 
  //second layer
  else if(first == 1)
  {
    if(second == -1)
    {
      item = m_tree.GetNextSiblingItem(item);
      m_tree.SelectItem(item);
    }
    else if(second >= 0 && second < RESEARCH_MAX)
    {
     cur_sel_item_ = NULL;
      FindItem(pfFindItem);
      if(cur_sel_item_ != NULL)
      {
        m_tree.SelectItem(m_tree.GetRootItem());
        m_tree.SelectItem(cur_sel_item_);
      }
    }
  } 
  //third layer
  else if(first == 2)
  {
    if(second == -1)
    {
      item = m_tree.GetNextSiblingItem(item);
      item = m_tree.GetNextSiblingItem(item);
      m_tree.SelectItem(item);
    }
  } 
}

bool CPageDocuments::pfFindItem(HTREEITEM hti)
{
  DWORD data = m_tree.GetItemData(hti);
  TreeItemData_t* finding_item = (TreeItemData_t*)data;
  if(finding_item->parent_index == find_first_ && finding_item->index == find_second_)
     return true;
  return false;
}

void CPageDocuments::FindItem(FindMatchItemFunc pf, HTREEITEM hti)
{
  if (hti == TVI_ROOT)
    hti = m_tree.GetRootItem(); 
  else
    hti = m_tree.GetChildItem(hti); 

  while(hti != NULL)
  {    
    if((this->*pf)(hti) == true)
    {
      cur_sel_item_ = hti;
      return;
    }
    FindItem(pf, hti);
    hti = m_tree.GetNextSiblingItem(hti);
  }
}

void CPageDocuments::OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	HTREEITEM item = m_tree.GetSelectedItem();
  if(item != NULL)
  {
    DWORD d = m_tree.GetItemData(item);
    TreeItemData_t* data = (TreeItemData_t*)d;
    if( data->parent_index == 0 )
    {
      GetCommander()->SwitchToPage(PAGE_BUILDING);
    }
    else if( data->parent_index == 1 )
    {
      GetCommander()->SwitchToPage(PAGE_RESEARCH);
    }
    else if( data->index == 2 && data->parent_index == -1)
    {
      GetCommander()->SwitchToPage(PAGE_BOATYARD);
    }
  }	
	*pResult = 0;
}
