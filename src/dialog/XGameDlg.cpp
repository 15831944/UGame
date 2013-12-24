// XGameDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XGame.h"
#include "XGameDlg.h"
#include "GameFileReader.h"
#include "BuildingsKeeper.h"
#include "ResearchKeeper.h"
#include "BoatsKeeper.h"
#include "DefensesKeeper.h"
#include "TipWarpper.h"
#include "GameLogger.h"
#include "AccountDlg.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_SHELL_MESSAGE WM_USER + 200
#define ID_HIDE_SHOW_HETKEY 1001
const int GUI_DIALOG_WIDTH = 733;
const int GUI_DIALOG_HEIGHT_HEADER = 100;
const int SAVE_TIME_MENU_POS = 4;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
  GameData* data_;
public:
	CAboutDlg(GameData* d);

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_thanklist;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg void OnBtnHelp();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg(GameData* d) : data_(d) , CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	m_thanklist = _T("");
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Text(pDX, IDC_EDIT_THANKLIST, m_thanklist);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_BN_CLICKED(ID_BTN_HELP, OnBtnHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


CXGameDlg::CXGameDlg(GameData* d , CWnd* pParent /*=NULL*/)
	: CDialog(CXGameDlg::IDD, pParent) , data_(d),
    page_person_(IDI_GUI_PERSON , this),
    page_buildings_(IDI_GUI_FACTORY , this),
    page_resource_(IDI_GUI_RESOURCE , this),
    page_galaxy_(IDI_GUI_GALAXY , this),
    page_boatyard_(IDI_GUI_BOATYARD , this),
    page_reseach_center_(IDI_GUI_RESEARCH , this),
    page_information_(IDI_GUI_INFORMATION , this),
    page_commander_(IDI_GUI_COMMAND, this),
    page_defense_(IDI_GUI_DEFENSE , this),
    page_docs_(IDI_GUI_DOCUMENTS , this)
{
	//{{AFX_DATA_INIT(CXGameDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
  buildings_keeper_ = new BuildingsKeeper(data_);
  researchs_keeper_ = new ResearchKeeper(data_);
  boats_keeper_     = new BoatsKeeper(data_);
  defense_keeper_   = new DefensesKeeper(data_);
  buildings_keeper_->SetTotalPercent();
  is_silent_mode_ = false;
  is_exit_after_tasks_over_ = false;
  menu_tray_.LoadMenu(IDR_SHELL_MENU);
}

CXGameDlg::~CXGameDlg()
{
  delete buildings_keeper_;
  delete researchs_keeper_;
  delete boats_keeper_;
  delete defense_keeper_;
}

void CXGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXGameDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CXGameDlg, CDialog)
	//{{AFX_MSG_MAP(CXGameDlg) 
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
  ON_MESSAGE(WM_HOTKEY, OnHotKey)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_ACCOUNT_INFO, OnBtnAccountInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXGameDlg message handlers

BOOL CXGameDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
  }
  
  // Set the icon for this dialog.  The framework does this automatically
  //  when the application's main window is not a dialog
  SetIcon(m_hIcon, TRUE);			// Set big icon
  SetIcon(m_hIcon, FALSE);		// Set small icon	

  //init
  Initialize();	

#ifdef TRANSPARENT_GUI_INTERFACE
  //set transparent window
  SetWindowLong(m_hWnd ,GWL_EXSTYLE,GetWindowLong(m_hWnd,GWL_EXSTYLE)^0x80000);
  HINSTANCE hInst = LoadLibrary("User32.DLL"); 
  if(hInst) 
  {            
    typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD);          
    MYFUNC fun = NULL;
    fun=(MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
    if(fun)fun(m_hWnd, 0 , 245 , 2);
    FreeLibrary(hInst);
  }  
#endif  
  //startup status
  show_status_ = APP_SHOW_S_SHOW;

  save_mode_ = SAVE_T_30;
  //set again
  timer_for_save_.Init(GetSaveTime() * 60);
  menu_tray_.GetSubMenu(0)->ModifyMenu(SAVE_TIME_MENU_POS , MF_BYPOSITION | MF_STRING , SAVE_TIME_MENU_POS , "定时保存数据：" + timer_for_save_.ToCString());
  //1 second
  SetTimer(TIMER_FOR_SAVE , 1000 , NULL);
  return TRUE;  // return TRUE  unless you set the focus to a control
}

void CXGameDlg::InitSkins()
{
  //window title
  int speed = data_->GAME_SPEED();
  CString t;
  t.Format("UGame [by RedHunter] (%d倍速)" , speed);
  SetWindowText(t);
  m_bmpBackground.LoadBitmap(IDB_BIT_GUI_MAIN);
  
  //number
  m_sta_rank.SubclassDlgItem(IDC_STA_RANK , this);
  m_sta_rank.SetTextColor(RGB(255 , 255 , 0));
  m_sta_rank.SetBackColor(RGB(55 , 77 , 112));
  
  m_sta_money.SubclassDlgItem(IDC_STA_PRODUCE_RATIO , this);
  m_sta_money.SetTextColor(RGB(192 , 192 , 240));
  m_sta_money.SetBackColor(RGB(55 , 77 , 112));
  
  m_sta_metal.SubclassDlgItem(IDC_STA_MINAL , this);
  m_sta_metal.SetTextColor(RGB(255 , 255 , 255)); 
  m_sta_metal.SetBackColor(RGB(55 , 77 , 112));
  
  m_sta_crystal.SubclassDlgItem(IDC_STA_CRY , this);
  m_sta_crystal.SetTextColor(RGB(255 , 255 , 255));
  m_sta_crystal.SetBackColor(RGB(55 , 77 , 112));
  
  m_sta_doplogen.SubclassDlgItem(IDC_STA_DIP , this);
  m_sta_doplogen.SetTextColor(RGB(255 , 255 , 255));
  m_sta_doplogen.SetBackColor(RGB(55 , 77 , 112));
  
  m_sta_power.SubclassDlgItem(IDC_STA_POWER , this); 
  m_sta_power.SetTextColor(RGB(0 , 255 , 0));
  m_sta_power.SetBackColor(RGB(55 , 77 , 112));  

  m_sta_regtime.SubclassDlgItem(IDC_STA_REG_TIME , this); 
  m_sta_regtime.SetTextColor(RGB(192 , 192 , 192));
  m_sta_regtime.SetBackColor(RGB(55 , 77 , 112));    
  
  //log 
  m_log_rank.SubclassDlgItem(IDC_STATIC1 , this); 
  m_log_rank.SetTextColor(RGB(192 , 192 , 192));
  m_log_rank.SetBackColor(RGB(55 , 77 , 112));
  m_log_rank.SetCaption("积分：");
  
  m_log_produce.SubclassDlgItem(IDC_STATIC2 , this);
  m_log_produce.SetTextColor(RGB(192 , 192 , 192));
  m_log_produce.SetBackColor(RGB(55 , 77 , 112)); 
  m_log_produce.SetCaption("U币：");
  
  m_log_metal.SubclassDlgItem(IDC_STATIC3 , this);
  m_log_metal.SetTextColor(RGB(255 , 255 , 255));
  m_log_metal.SetBackColor(RGB(55 , 77 , 112));
  m_log_metal.SetCaption("金属");
  
  m_log_crystal.SubclassDlgItem(IDC_STATIC4 , this);
  m_log_crystal.SetTextColor(RGB(255 , 255 , 255));
  m_log_crystal.SetBackColor(RGB(55 , 77 , 112));
  m_log_crystal.SetCaption("晶体");
  
  m_log_diplogen.SubclassDlgItem(IDC_STATIC5 , this);
  m_log_diplogen.SetTextColor(RGB(255 , 255 , 255));
  m_log_diplogen.SetBackColor(RGB(55 , 77 , 112));
  m_log_diplogen.SetCaption("重氢");
  
  m_log_power.SubclassDlgItem(IDC_STATIC6 , this);
  m_log_power.SetTextColor(RGB(255 , 255 , 255));
  m_log_power.SetBackColor(RGB(55 , 77 , 112));
  m_log_power.SetCaption("能量");   

  //button
  m_btn_account_info.SubclassDlgItem(IDC_BTN_ACCOUNT_INFO, this);
	m_btn_account_info.SetActiveBgColor(RGB(55 , 77 , 112));
	m_btn_account_info.SetActiveFgColor(RGB(255 , 255 , 240));
	m_btn_account_info.SetInactiveBgColor(RGB(55 , 77 , 112));
	m_btn_account_info.SetInactiveFgColor(RGB(255 , 255 , 240));
}

void CXGameDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout(data_);
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CXGameDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
    CPaintDC dc(this);
    dc.SetBkMode(TRANSPARENT);
		CRect rect;
		GetClientRect(&rect);
		CDC dcMem; 
		dcMem.CreateCompatibleDC(&dc); 
		BITMAP bitMap;
		m_bmpBackground.GetBitmap(&bitMap);
		CBitmap *pbmpOld=dcMem.SelectObject(&m_bmpBackground);
		dc.StretchBlt(0 , 0 , rect.Width() , GUI_DIALOG_HEIGHT_HEADER, &dcMem,0,0,bitMap.bmWidth,bitMap.bmHeight,SRCCOPY);
  }
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CXGameDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CXGameDlg::OnCancel() 
{
  //put it in tray
  SetWindowStatus(APP_SHOW_S_TRAY);
}

void CXGameDlg::OnOK() 
{
}

BOOL CXGameDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
  {
    //push ESC key, put it in tray
    SetWindowStatus(APP_SHOW_S_TRAY);
    return TRUE;
  }	
	return CDialog::PreTranslateMessage(pMsg);
}

void CXGameDlg::Initialize(){
  //set hot key
	RegisterHotKey(m_hWnd, ID_HIDE_SHOW_HETKEY, MOD_ALT, 'Z'); // ALT+Z
  InitKernel();   
  InitSkins();
  InitSheet();
  InitControls();  
}

void CXGameDlg::InitSheet(){    
  //add pages
  m_sheet.AddPage(&page_person_);
  m_sheet.AddPage(&page_galaxy_);
  m_sheet.AddPage(&page_commander_);
  m_sheet.AddPage(&page_information_);
  m_sheet.AddPage(&page_resource_); 
  m_sheet.AddPage(&page_buildings_);  
  m_sheet.AddPage(&page_reseach_center_);
  m_sheet.AddPage(&page_boatyard_);    
  m_sheet.AddPage(&page_defense_);    
  m_sheet.AddPage(&page_docs_); 

  //push observers
  entry_observers_.push_back(&page_person_);
  entry_observers_.push_back(&page_galaxy_);
  entry_observers_.push_back(&page_commander_);
  entry_observers_.push_back(&page_information_);
  entry_observers_.push_back(&page_resource_);
  entry_observers_.push_back(&page_buildings_);
  entry_observers_.push_back(&page_reseach_center_);  
  entry_observers_.push_back(&page_boatyard_);
  entry_observers_.push_back(&page_defense_);
  entry_observers_.push_back(&page_docs_);

  //communication initialize
  comm_.Initialize(&page_person_ ,
                   &page_buildings_,
                   &page_resource_,
                   &page_galaxy_,
                   &page_boatyard_,
                   &page_reseach_center_,
                   &page_information_,
                   &page_commander_,
                   &page_docs_);

  //set pointers to observers
  for(int i = 0 ; i < entry_observers_.size() ; ++i)
  {
    entry_observers_[i]->SetDataPtr(data_);
    entry_observers_[i]->SetParentPtr(this);
    entry_observers_[i]->SetCommPtr(&comm_);
    entry_observers_[i]->SetResearchsKeeper(researchs_keeper_);
    entry_observers_[i]->SetBuildingsKeeper(buildings_keeper_);
    entry_observers_[i]->SetBoatsKeeper(boats_keeper_);
    entry_observers_[i]->SetDefensesKeeper(defense_keeper_);
  }

  m_sheet.Create(this, WS_CHILD | WS_VISIBLE, WS_EX_CONTROLPARENT);    
  CRect rect;
  GetClientRect(&rect); 
  m_sheet.SetWindowPos(NULL, 0, 95, rect.Width() , rect.Height() - 95, SWP_NOZORDER | SWP_NOACTIVATE);

  //Create all pages and call InitDialog()
  for(i = 0 ; i < m_sheet.GetPageCount(); ++i)
  {
    m_sheet.SetActivePage(m_sheet.GetPage(i));
  }

  //set default page is person page
  m_sheet.SetActivePage(&page_person_);

  //Init pages
  for(i = 0 ; i < entry_observers_.size() ; ++i)
  {
    entry_observers_[i]->Notify_Init();
  }
}

void CXGameDlg::InitControls()
{ 
  TCHAR buf[64];
  TCHAR buf1[64];
  CString info;
  CString r;
  uchar  c_r = data_->GetLoginedAccountComputerRank();
  m_btn_account_info.SetWindowText(info);

  info.Format("%s[%s]" , data_->GetLoginedAccountName() , data_->GetLoginedAccountPosition().ToCString(buf));
  m_btn_account_info.SetWindowText(info);

  info.Format("%s" , AddPointsToNumber(data_->GetLoginedAccountRank() , buf));
  m_sta_rank.SetCaption(info);

  info.Format("%s" , AddPointsToNumber(data_->GetResource(RESOURCE_METAL) , buf));
  m_sta_metal.SetCaption(info);

  info.Format("%s" , AddPointsToNumber(data_->GetResource(RESOURCE_CRYSTAL) , buf));
  m_sta_crystal.SetCaption(info);

  info.Format("%s" , AddPointsToNumber(data_->GetResource(RESOURCE_DIPLOGEN) , buf));
  m_sta_doplogen.SetCaption(info);

  info.Format("%s/%s" , AddPointsToNumber(data_->GetExistPower() - data_->GetConsumePower() , buf1) , AddPointsToNumber(data_->GetExistPower() , buf));
  if(data_->GetExistPower() - data_->GetConsumePower() < 0)
    m_sta_power.SetTextColor(RGB(255 , 0 , 0));
  else
    m_sta_power.SetTextColor(RGB(0 , 255 , 0));
  m_sta_power.SetCaption(info);

  info.Format("%s" , AddPointsToNumber(data_->GetAccountMoney() , buf) );
  m_sta_money.SetCaption(info);

  info.Format("注册时间：%d-%02d-%02d %02d:%02d:%02d" , data_->REGISTER_TIME().GetYear() , data_->REGISTER_TIME().GetMonth() , 
    data_->REGISTER_TIME().GetDay() , data_->REGISTER_TIME().GetHour() , data_->REGISTER_TIME().GetMinute() , data_->REGISTER_TIME().GetSecond());
  m_sta_regtime.SetCaption(info);
}

void CXGameDlg::InitKernel()
{
  InitRand();
  kernel_.LoadLangFile(".\\cfg\\cht_lang_v0.9.4.0b.ini");
  kernel_.SetOwnPosition(data_->GetLoginedAccountPosition(), 0);
  kernel_.SetRF(RF_065);
  kernel_.SetUseShipDataFromFile(false);
  kernel_.SetDefInDebris(false);
  kernel_.SetNewFuel(true);
  kernel_.RebuildSmallDefense(false);
  kernel_.SetDefRebuildFactor(0.7f);  
  int c = data_->GetResearchLevel(RESEARCH_BURNING);
  int p = data_->GetResearchLevel(RESEARCH_PULSE);
  int s = data_->GetResearchLevel(RESEARCH_SUPERSPACE);
  kernel_.SetSpeed(100 , c , p , s , 0);
}

//resource changed
void CXGameDlg::Notify_Resource_Changed()
{
  TCHAR buf[64];
  CString info;

  info.Format("%s" , AddPointsToNumber(data_->GetResource(RESOURCE_METAL) , buf));
  m_sta_metal.SetCaption(info);

  info.Format("%s" , AddPointsToNumber(data_->GetResource(RESOURCE_CRYSTAL) , buf));
  m_sta_crystal.SetCaption(info);

  info.Format("%s" , AddPointsToNumber(data_->GetResource(RESOURCE_DIPLOGEN) , buf));
  m_sta_doplogen.SetCaption(info);

  //notify resource change
  for(int i = 0 ; i < entry_observers_.size() ; ++i)
  {
    entry_observers_[i]->Notify_Resource_Changed();
  }
}

void CXGameDlg::Notify_Ships_Produced(int type , ulong number)
{
  CString info;
  
  //if is sun power planet
  if(type == BOAT_SUNPOWER_PLANET)
  {
    //total percent change
    buildings_keeper_->SetTotalPercent();

    //change text display
    TCHAR buf[64];
    TCHAR buf1[64];
    info.Format("%s/%s" , AddPointsToNumber(data_->GetExistPower() - data_->GetConsumePower() , buf1) , AddPointsToNumber(data_->GetExistPower() , buf));
    if(data_->GetExistPower() - data_->GetConsumePower() < 0)
      m_sta_power.SetTextColor(RGB(255 , 0 , 0));
    else
      m_sta_power.SetTextColor(RGB(0 , 255 , 0));
    m_sta_power.SetCaption(info);
  }
  //notify ships change
  for(int i = 0 ; i < entry_observers_.size() ; ++i)
  {
    entry_observers_[i]->Notify_Ships_Changed();
  }
}

void CXGameDlg::Notify_Defenses_Produced(int type , ulong number)
{
  //notify defenses change
  for(int i = 0 ; i < entry_observers_.size() ; ++i)
  {
    entry_observers_[i]->Notify_Defense_Changed();
  }
}

void CXGameDlg::Notify_Defenses_Changed()
{
  //notify defenses change
  for(int i = 0 ; i < entry_observers_.size() ; ++i)
  {
    entry_observers_[i]->Notify_Defense_Changed();
  }
}

void CXGameDlg::Notify_Ships_Changed(bool has_sunpower)
{
  if(has_sunpower)
  {
    CString info;    
    //total percent change
    buildings_keeper_->SetTotalPercent();    
    //change text display
    TCHAR buf[64];
    TCHAR buf1[64];
    info.Format("%s/%s" , AddPointsToNumber(data_->GetExistPower() - data_->GetConsumePower() , buf1) , AddPointsToNumber(data_->GetExistPower() , buf));
    if(data_->GetExistPower() - data_->GetConsumePower() < 0)
      m_sta_power.SetTextColor(RGB(255 , 0 , 0));
    else
      m_sta_power.SetTextColor(RGB(0 , 255 , 0));
    m_sta_power.SetCaption(info);    
  }
  
  //notify ships change
  for(int i = 0 ; i < entry_observers_.size() ; ++i)
  {
    entry_observers_[i]->Notify_Ships_Changed();
  }
}

void CXGameDlg::Notify_Galaxy_Update()
{
  //notify galaxy change
  for(int i = 0 ; i < entry_observers_.size() ; ++i)
  {
    entry_observers_[i]->Notify_Galaxy_Update();
  }
}

void CXGameDlg::Notify_Money_Change()
{
  CString info;
  char buf[64];
  info.Format("%s" , AddPointsToNumber(data_->GetAccountMoney() , buf) );
  m_sta_money.SetCaption(info);
}

void CXGameDlg::Notify_Galaxy_UpdateTimer_Go()
{
  menu_tray_.GetSubMenu(0)->ModifyMenu(IDR_SHELL_MENU_GALAXYUPDATETIME , MF_BYCOMMAND | MF_STRING , IDR_SHELL_MENU_GALAXYUPDATETIME , "银河刷新：" + page_galaxy_.GetUpdateTimeString());
}

void CXGameDlg::Notify_Trade_Center_Time_Go(CString para)
{
  menu_tray_.GetSubMenu(0)->ModifyMenu(IDR_SHELL_MENU_TRADE , MF_BYCOMMAND | MF_STRING , IDR_SHELL_MENU_TRADE , para);
}

void CXGameDlg::Notify_SuperTransferGate_Time_Go(CString para)
{
  menu_tray_.GetSubMenu(0)->ModifyMenu(IDR_SHELL_MENU_GATE , MF_BYCOMMAND | MF_STRING , IDR_SHELL_MENU_GATE , para);
}

void CXGameDlg::Notify_Score_Changed()
{
  //change text display
  CString info;  
  TCHAR buf[64];
  info.Format("%s" , AddPointsToNumber(data_->GetLoginedAccountRank() , buf));
  m_sta_rank.SetCaption(info);

  //notify ships change
  for(int i = 0 ; i < entry_observers_.size() ; ++i)
  {
    entry_observers_[i]->Notify_Score_Changed();
  }
}

//notify level up
void CXGameDlg::Notify_Buildings_LevelUp()
{
  //total percent change
  buildings_keeper_->SetTotalPercent();
  //data_->UpdateRank(1.0);
  
  //change text display
  CString info;
  TCHAR buf[64];
  TCHAR buf1[64];
  info.Format("%s/%s" , AddPointsToNumber(data_->GetExistPower() - data_->GetConsumePower() , buf1) , AddPointsToNumber(data_->GetExistPower() , buf));
  if(data_->GetExistPower() - data_->GetConsumePower() < 0)
    m_sta_power.SetTextColor(RGB(255 , 0 , 0));
  else
    m_sta_power.SetTextColor(RGB(0 , 255 , 0));
  m_sta_power.SetCaption(info);
  
  info.Format("%s" , AddPointsToNumber(data_->GetLoginedAccountRank() , buf));
  m_sta_rank.SetCaption(info);
  
  //notify observers level up
  for(int i = 0 ; i < entry_observers_.size() ; ++i)
  {
    entry_observers_[i]->Notify_Building_LevelUp();
  }  
}

void CXGameDlg::Notify_Resource_Consumed(double r)
{
  double c = r / 1000.0;
  data_->UpdateRank(c);
  CString info;
  TCHAR buf[64];
  info.Format("%s" , AddPointsToNumber(data_->GetLoginedAccountRank() , buf));
  m_sta_rank.SetCaption(info);
}

void CXGameDlg::Notify_Technics_LevelUp()
{
  //data_->UpdateRank(1.0);
  //change text display
  CString info;
  TCHAR buf[64];
  info.Format("%s" , AddPointsToNumber(data_->GetLoginedAccountRank() , buf));
  m_sta_rank.SetCaption(info);

  //update kernel
  int c = data_->GetResearchLevel(RESEARCH_BURNING);
  int p = data_->GetResearchLevel(RESEARCH_PULSE);
  int s = data_->GetResearchLevel(RESEARCH_SUPERSPACE);
  kernel_.SetSpeed(100 , c , p , s , 0);

  //notify observers level up
  for(int i = 0 ; i < entry_observers_.size() ; ++i)
  {
    entry_observers_[i]->Notify_Technics_LevelUp();
  }   
}

void CXGameDlg::Notify_Building_ProducePercent_Changed(int index , double percent)
{
  //produce percent change
  buildings_keeper_->SetProductPercent(index , percent);

  //total percent change
  buildings_keeper_->SetTotalPercent();

  //change text display
  CString info;
  TCHAR buf[64];
  TCHAR buf1[64];
  info.Format("%s/%s" , AddPointsToNumber(data_->GetExistPower() - data_->GetConsumePower() , buf1) , AddPointsToNumber(data_->GetExistPower() , buf));
  if(data_->GetExistPower() - data_->GetConsumePower() < 0)
    m_sta_power.SetTextColor(RGB(255 , 0 , 0));
  else
    m_sta_power.SetTextColor(RGB(0 , 255 , 0));
  m_sta_power.SetCaption(info);

  //notify product percent change
  for(int i = 0 ; i < entry_observers_.size() ; ++i)
  {
    entry_observers_[i]->Notify_Building_ProducePercent_Changed();
  }
}

LRESULT CXGameDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
  int i = 0;
  switch(message)
  {
    //system commands
  case WM_SYSCOMMAND:
    if(wParam == SC_MINIMIZE || wParam == SC_CLOSE)
    {
      //put it in tray
      SetWindowStatus(APP_SHOW_S_TRAY);
      return 0;
    }
    break; 
    //tray shell message
  case WM_SHELL_MESSAGE:
    //left button double click
    if(lParam == WM_LBUTTONDBLCLK)
    {
      //show
      SetWindowStatus(APP_SHOW_S_SHOW);
    }
    //right&left button up
    else if(lParam == WM_RBUTTONUP || lParam == WM_LBUTTONUP)
    {	
      OnBtnAccountInfo();
    }  
    if(lParam == WM_MOUSEMOVE)
    {
      CString title;
      title.Format("UGame[%s:%.0f]" , data_->GetLoginedAccountName() , data_->GetLoginedAccountRank() );
      bool w = false;
      for(int i = 0 ; i < entry_observers_.size() ; ++i)
      {
        CString tmp = entry_observers_[i]->GetTipInfo();
        if(entry_observers_[i]->GetWorkFlag() && (!tmp.IsEmpty()) )
        {
          title += "\n";
          title += tmp;
          w = true;
        }
      }    
      if(w == false)
      {
        title.Format("UGame [%s:%.0f]" , data_->GetLoginedAccountName() , data_->GetLoginedAccountRank());
      }

      if(title.GetLength() > 62)
      {
        title = title.Left(62);
      }
      strcpy(shell_notify_data_.szTip, title);
      shell_notify_data_.uFlags = NIF_TIP;
	    Shell_NotifyIcon(NIM_MODIFY, &shell_notify_data_);
      return 0;
    }
    break;	
    //notify system shutdown or reboot event
  case WM_QUERYENDSESSION:
    //notify exit
    for( i = 0 ; i < entry_observers_.size() ; ++i)
    {
      entry_observers_[i]->Notify_Exit();
    }
    //log
    CGameLogger::Instance().Log("system will shutdown or reset, save data...");
    Logoff();
   if(!is_silent_mode_)
     TipWarpper::Instance().ShowTip("账户信息保存完成");
    return TRUE;
  default:
    break;
  }		  
  return CDialog::WindowProc(message, wParam, lParam);
}

void CXGameDlg::addsystray()
{
  shell_notify_data_.cbSize=sizeof(NOTIFYICONDATA);
  shell_notify_data_.hWnd=this->m_hWnd;
  shell_notify_data_.uID=IDR_MAINFRAME;
  shell_notify_data_.uFlags=NIF_MESSAGE|NIF_ICON|NIF_TIP;
  shell_notify_data_.uCallbackMessage = WM_SHELL_MESSAGE;
  shell_notify_data_.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
  CString title;
  title.Format("UGame (%s: %.0f)" , data_->GetLoginedAccountName() , data_->GetLoginedAccountRank());
  if(title.GetLength() > 62)
  {
    title = title.Left(62);
  }
  strcpy(shell_notify_data_.szTip , title);
  Shell_NotifyIcon(NIM_ADD , &shell_notify_data_);
}

void CXGameDlg::delsystray()
{
	shell_notify_data_.cbSize=sizeof(NOTIFYICONDATA);
	shell_notify_data_.hWnd=this->m_hWnd;
	shell_notify_data_.uID=IDR_MAINFRAME;
	shell_notify_data_.uFlags=NIF_MESSAGE|NIF_ICON|NIF_TIP;
	shell_notify_data_.uCallbackMessage = WM_SHELL_MESSAGE;
	shell_notify_data_.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	strcpy(shell_notify_data_.szTip,"UGame");
	Shell_NotifyIcon(NIM_DELETE , &shell_notify_data_);
}

void CXGameDlg::OnDestroy() 
{
  UnregisterHotKey(m_hWnd , ID_HIDE_SHOW_HETKEY);
	CDialog::OnDestroy();
}

LRESULT CXGameDlg::OnHotKey(WPARAM wParam,LPARAM lParam)
{
  //window status transfer chart when push hot key
  //(1) = show   (2) = tray   (3) = hide
  //       (1)
  //      /   \
  //     /     \
  //   (2)---->(3)
  //hot key pushed
  if(wParam == ID_HIDE_SHOW_HETKEY) 	
  {
    //1.if window show, put it at tray
    if(show_status_ == APP_SHOW_S_SHOW)
    {
      SetWindowStatus(APP_SHOW_S_TRAY);
    }
    //2.if window in tray, hide it
    else if(show_status_ == APP_SHOW_S_TRAY)
    {
      SetWindowStatus(APP_SHOW_S_HIDE);
    }
    //3.if window hide, show it
    else if(show_status_ == APP_SHOW_S_HIDE)
    {
      SetWindowStatus(APP_SHOW_S_SHOW);
    }    
  }
  return 0; 
}

void CXGameDlg::SwitchToPage(CPropertyPage* active_page)
{
  for(int i = 0 ; i < m_sheet.GetPageCount() ; ++i)
  {
    if(m_sheet.GetPage(i) == active_page)
      break;
  }
  if(i >= m_sheet.GetPageCount())
    return;
  m_sheet.SetActivePage(active_page);
}

void CXGameDlg::SwitchToPage(int index)
{
  assert(index >= 0 && index < m_sheet.GetPageCount());
  if(!(index >= 0 && index < m_sheet.GetPageCount()))
    return;
  m_sheet.SetActivePage(m_sheet.GetPage(index));
}

void CXGameDlg::MessageNotify(int new_info_num)
{
  if(new_info_num > 0)
  {
    int speed = data_->GAME_SPEED();
    CString t;
    t.Format("UGame [by RedHunter] (%d倍速)[您有新消息：%d 条]" , speed , new_info_num);
    SetWindowText(t);
  }
  else
  {
    int speed = data_->GAME_SPEED();
    CString t;
    t.Format("UGame [by RedHunter] (%d倍速)" , speed );
    SetWindowText(t);
  }
}

void CXGameDlg::OnClose() 
{
	CDialog::OnClose();
}


void CAboutDlg::OnBtnHelp() 
{
	ShellExecute(NULL , "open" , "readme.txt" , "" ,"",SW_SHOW);	
}

void CXGameDlg::OnTimer(UINT nIDEvent) 
{
  //exit
  if(nIDEvent == TIMER_FOR_EXIT)
  {
    if(is_exit_after_tasks_over_)
    {
      bool TipFlag = true;
      for(int i = 0 ; i < entry_observers_.size() ; ++i)
      {
        if(entry_observers_[i]->GetWorkFlag())
        {
          TipFlag = false;
          break;
        }
      }
      if(TipFlag)
      {
        KillTimer(TIMER_FOR_EXIT);
        //notify exit
        for( i = 0 ; i < entry_observers_.size() ; ++i)
        {
          entry_observers_[i]->Notify_Exit();
        }
        Logoff();
      }
    }
  }
  //save account data
  else if(nIDEvent == TIMER_FOR_SAVE)
  {
    timer_for_save_.Go();
    menu_tray_.GetSubMenu(0)->ModifyMenu(SAVE_TIME_MENU_POS , MF_BYPOSITION | MF_STRING , SAVE_TIME_MENU_POS , "定时保存数据：" + timer_for_save_.ToCString());
    //save
    if(timer_for_save_.IsZero())
    {
      KillTimer(TIMER_FOR_SAVE);
      bool idleFlag = true;
      for(int i = 0 ; i < entry_observers_.size() ; ++i)
      {
        if(entry_observers_[i]->GetWorkFlag())
        {
          idleFlag = false;
          break;
        }
      }
      //all finish
      if(idleFlag)
      {
        //kill
        menu_tray_.GetSubMenu(0)->ModifyMenu(SAVE_TIME_MENU_POS , MF_BYPOSITION | MF_STRING , SAVE_TIME_MENU_POS , "定时保存数据（正在保存...)");        
        CWaitCursor waitor;
        CXGameApp* game_app = (CXGameApp*)AfxGetApp();
        game_app->SaveAccountData();
      }
      //set again
      timer_for_save_.Init(GetSaveTime() * 60);
      menu_tray_.GetSubMenu(0)->ModifyMenu(SAVE_TIME_MENU_POS , MF_BYPOSITION | MF_STRING , SAVE_TIME_MENU_POS , "定时保存数据：" + timer_for_save_.ToCString());
      SetTimer(TIMER_FOR_SAVE , 1000 , NULL);
    }
  }
  CDialog::OnTimer(nIDEvent);
}

void CXGameDlg::SetWindowStatus(WINDOW_TYPE type)
{
  //1.show
  if(type == APP_SHOW_S_SHOW)
  {
    ShowWindow(SW_SHOW);
    delsystray();
    SetForegroundWindow();
    SetFocus();
    SetWindowPos(&CWnd::wndTop, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);    
  }
  //2.tray
  else if(type == APP_SHOW_S_TRAY)
  {
    addsystray();
    ShowWindow(SW_HIDE);
  }
  //3.hide
  else
  {
    delsystray();
    ShowWindow(SW_HIDE);
  }    
  show_status_ = type;
}

void CXGameDlg::Logoff()
{  
  KillTimer(TIMER_FOR_SAVE);
  delsystray();  
  EndDialog(IDCANCEL);
  CXGameApp* game_app = (CXGameApp*)AfxGetApp();
  game_app->Logoff();   
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
  CString info = _T("1.作者RedHunter，邮箱：ugame.redhunter@gmail.com，有任何问题请联系RedHunter。\r\n\r\n");
  info += _T("2.该游戏E2.00(不包含E2.00)以前版本属于完全免费版本，你可以在网络上进行随意传播和拷贝，但是不能用于任何商业活动，违者必追究其法律责任。\r\n\r\n");
  info += _T("3.本游戏程序绝不包含任何恶意代码和后门程序，请放心使用。\r\n\r\n");
  info += _T("4.感谢OGame提供一些游戏数据和图片资料，本游戏纯属个人娱乐之用。\r\n\r\n");	
  info += _T("Enjoy It!");
	GetDlgItem(IDC_EDIT1)->SetWindowText(info);	
  GetDlgItem(IDC_EDIT1)->SendMessage(EM_FMTLINES , TRUE , 0);

  info =  _T("下列名字是 www.cwebgame.com 上的注册ID：\r\n");
  info += _T("laoxibu\r\n");
  info += _T("于二\r\n");
  info += _T("OOXXXXOO\r\n");
  info += _T("RedTiger2007\r\n");
  info += _T("残雪夕阳\r\n");
  info += _T("iLoveIriya\r\n");
  info += _T("shingod\r\n"); 
  info += _T("Bernie\r\n");   
  info += _T("lysfox\r\n");    
  info += _T("下列以EMAIL地址代替：\r\n");
  info += _T("la0wang@gmail.com\r\n");   
  info += _T("p______k@hotmail.com\r\n");
  info += _T("Xhplus@gmail.com\r\n");
  info += _T("f481315@gmail.com\r\n");
  info += _T("liukeran19870202@tom.com");
  	
  GetDlgItem(IDC_EDIT_THANKLIST)->SetWindowText(info);	
  GetDlgItem(IDC_EDIT_THANKLIST)->SendMessage(EM_FMTLINES , TRUE , 0);

  CString title = _T("关于 UGame");

#ifdef USE_FOR_SMALL_GALAXY_VERSION
  title += "[单银河]";
#endif

  SetWindowText(title);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CXGameDlg::OnBtnAccountInfo() 
{
  CMenu* pPopup = menu_tray_.GetSubMenu(0);
  //default menu item
  ::SetMenuDefaultItem(pPopup->m_hMenu,0,TRUE);
  if(this->IsWindowVisible())
  {
    pPopup->EnableMenuItem(IDR_SHELL_MENU_DISPLAY , MF_GRAYED);
  }
  else
  {
    pPopup->EnableMenuItem(IDR_SHELL_MENU_DISPLAY , MF_ENABLED);
  }
  //check silent mode&task over exit
  pPopup->CheckMenuItem(IDR_SHELL_MENU_SILENTMODE      , is_silent_mode_           ? MF_CHECKED : MF_UNCHECKED);	 
  pPopup->CheckMenuItem(IDR_SHELL_MENU_EXITWHENALLOVER , is_exit_after_tasks_over_ ? MF_CHECKED : MF_UNCHECKED);
  pPopup->CheckMenuRadioItem(IDR_SHELL_MENU_SAVE_DISABLE , IDR_SHELL_MENU_SAVE_05 , GetSaveModeMenuIDByMode() ,MF_BYCOMMAND);
  
  //get rank information
  {
    uchar t = 0;
    int   r = -1;
    page_person_.GetMyRank(t , r);
    CString s;
    if(t == SORT_BY_NAME || t == SORT_BY_POSITION)
    {
      s = "积分排名：";
    }
    else
    {
      s = "舰队排名：";
    }
    CString info;
    info.Format("%s%d" , s , r);
    pPopup->ModifyMenu(IDR_SHELL_MENU_RANK , MF_BYCOMMAND | MF_STRING , IDR_SHELL_MENU_RANK , info);                      
    info.Format("目前积分：%.0f" , data_->GetLoginedAccountRank());
    pPopup->ModifyMenu(IDR_SHELL_MENU_ACCOUNT_RANK , MF_BYCOMMAND | MF_STRING , IDR_SHELL_MENU_ACCOUNT_RANK , info);
  }
  CPoint Point;
  GetCursorPos(&Point);
  SetForegroundWindow();
  int res = pPopup->TrackPopupMenu(TPM_RIGHTBUTTON|TPM_RETURNCMD, Point.x, Point.y, this , NULL);     
  //display
  if(res == IDR_SHELL_MENU_DISPLAY) 
  {
    SetWindowStatus(APP_SHOW_S_SHOW);
  }
  ////timer for save Data
  //05 ~ 60
  else if(res >= IDR_SHELL_MENU_SAVE_60 && res <= IDR_SHELL_MENU_SAVE_05)
  {
    SetSaveModeByMenuID(res);
    //kill timer
    KillTimer(TIMER_FOR_SAVE);
    //set again
    timer_for_save_.Init(GetSaveTime() * 60);
    menu_tray_.GetSubMenu(0)->ModifyMenu(SAVE_TIME_MENU_POS , MF_BYPOSITION | MF_STRING , SAVE_TIME_MENU_POS , "定时保存数据：" + timer_for_save_.ToCString());
    //1 second
    SetTimer(TIMER_FOR_SAVE , 1000 , NULL);
  }
  //disable save timer
  else if(res == IDR_SHELL_MENU_SAVE_DISABLE)
  {
    //kill timer
    KillTimer(TIMER_FOR_SAVE);
    menu_tray_.GetSubMenu(0)->ModifyMenu(SAVE_TIME_MENU_POS , MF_BYPOSITION | MF_STRING , SAVE_TIME_MENU_POS , "定时保存数据（禁止）");
    SetSaveModeByMenuID(res);        
  }
  //save right away
  else if(res == IDR_SHELL_MENU_SAVE)
  {
    //kill timer
    KillTimer(TIMER_FOR_SAVE);
    bool idleFlag = true;
    for(int i = 0 ; i < entry_observers_.size() ; ++i)
    {
      if(entry_observers_[i]->GetWorkFlag())
      {
        idleFlag = false;
        break;
      }
    }
    //all finish
    if(idleFlag)
    {
      CWaitCursor waitor;
      menu_tray_.GetSubMenu(0)->ModifyMenu(SAVE_TIME_MENU_POS , MF_BYPOSITION | MF_STRING , SAVE_TIME_MENU_POS , "定时保存数据（正在保存...)");
      //save
      CXGameApp* game_app = (CXGameApp*)AfxGetApp();
      game_app->SaveAccountData(); 
    }
    //set again
    if(save_mode_ != SAVE_T_DISABLE)
    {
      timer_for_save_.Init(GetSaveTime() * 60);
      menu_tray_.GetSubMenu(0)->ModifyMenu(SAVE_TIME_MENU_POS , MF_BYPOSITION | MF_STRING , SAVE_TIME_MENU_POS , "定时保存数据：" + timer_for_save_.ToCString());
      //1 second
      SetTimer(TIMER_FOR_SAVE , 1000 , NULL);
    }
    else
    {
      menu_tray_.GetSubMenu(0)->ModifyMenu(SAVE_TIME_MENU_POS , MF_BYPOSITION | MF_STRING , SAVE_TIME_MENU_POS , "定时保存数据（禁止）");
    }
  }
  ////timer for save over
  
  //galaxy update time
  else if(res == IDR_SHELL_MENU_GALAXYUPDATETIME)
  {
    SetWindowStatus(APP_SHOW_S_SHOW);
    SwitchToPage(PAGE_GALAXY);
  }
  //trade center time
  else if(res == IDR_SHELL_MENU_TRADE){
    SetWindowStatus(APP_SHOW_S_SHOW);
    SwitchToPage(PAGE_COMMAND);
  }
  //gate time
  else if(res == IDR_SHELL_MENU_GATE){
    SetWindowStatus(APP_SHOW_S_SHOW);
    SwitchToPage(PAGE_COMMAND);
  }
  //update rank
  else if(res == IDR_SHELL_MENU_RANK)
  { 
    page_person_.UpdateRank();
  }
  //about box
  else if(res == IDR_SHELL_MENU_ABOUT)
  {
    CAboutDlg dlg(data_);
    dlg.DoModal();
  }
  //RANK
  else if(res == IDR_SHELL_MENU_ACCOUNT_RANK)
  {
  }
  //exit
  else if(res == IDR_SHELL_MENU_EXIT) 
  {
    bool idleFlag = false;
    for(int i = 0 ; i < entry_observers_.size() ; ++i)
    {
      if(entry_observers_[i]->GetWorkFlag())
      {
        idleFlag = true;
        break;
      }
    }
    
    //check tip flag
    if(idleFlag && (!is_silent_mode_))
    {
      if(MessageBox("如果退出游戏，目前正在进行的操作将被取消掉，在外的舰队被召回（只有1/3的资源被带回），你确定要退出吗？", "警告" , MB_YESNO | MB_ICONQUESTION) != IDYES)
      {
        return ;
      }    
    }  
    //notify exit
    for( i = 0 ; i < entry_observers_.size() ; ++i)
    {
      entry_observers_[i]->Notify_Exit();
    }
    Logoff();
  }
  //set silent mode
  else if(res == IDR_SHELL_MENU_SILENTMODE) 
  {
    is_silent_mode_ = !is_silent_mode_;
  }
  else if(res == IDR_SHELL_MENU_ACCOUNT_INFO)
  {
    CAccountDlg dlg(data_);
    dlg.DoModal();	
  }
  //exit after all task complete
  else if(res == IDR_SHELL_MENU_EXITWHENALLOVER) 
  {
    is_exit_after_tasks_over_ = !is_exit_after_tasks_over_;
    if(is_exit_after_tasks_over_)
    {
      //2 second
      SetTimer(TIMER_FOR_EXIT , 1000 , NULL);
    }	
    else
    {
      KillTimer(TIMER_FOR_EXIT);
    }
  }
}
