// XGameDlg.h : header file
//

#if !defined(AFX_XGAMEDLG_H__638DECA6_75DC_4574_971E_EBE75C7D4B1C__INCLUDED_)
#define AFX_XGAMEDLG_H__638DECA6_75DC_4574_971E_EBE75C7D4B1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CXGameDlg dialog

#include "pagebuildings.h"
#include "pagepersoninfo.h"
#include "pageresource.h"
#include "pagegalaxy.h"
#include "pageresreachcenter.h"
#include "pageboatyard.h"
#include "pageinformation.h"
#include "pagecommander.h"
#include "pagedefense.h"
#include "pagedocuments.h"

#include "communication.h"
#include "ColorStatic.h"

#include "MFECToolTip.h"
#include "BtnST.h"

class GameData;
class BuildingsKeeper;
class ResearchKeeper;
class BoatsKeeper;
class DefensesKeeper;
class ObserverBase;

enum WINDOW_TYPE{
  APP_SHOW_S_SHOW,
  APP_SHOW_S_TRAY,
  APP_SHOW_S_HIDE,
};

enum {
  SAVE_T_5,
  SAVE_T_10,
  SAVE_T_20,
  SAVE_T_30,
  SAVE_T_40,
  SAVE_T_50,
  SAVE_T_60,
  SAVE_T_DISABLE,
};

class CXGameDlg : public CDialog
{
private:
  CFont font_bar;
  WINDOW_TYPE show_status_;
  bool is_silent_mode_;

  //pages
  CPagePersonInfo     page_person_;
  CPageBuildings      page_buildings_;
  CPageResource       page_resource_;
  CPageGalaxy         page_galaxy_;
  CPageBoatyard       page_boatyard_;
  CPageResreachCenter page_reseach_center_;
  CPageInformation    page_information_;
  CPageCommander      page_commander_;
  CPageDefense        page_defense_;
  CPageDocuments      page_docs_;

  //communication
  Communication       comm_;

  //data
  GameData*        data_;
  BuildingsKeeper* buildings_keeper_;
  ResearchKeeper * researchs_keeper_;
  BoatsKeeper    * boats_keeper_;
  DefensesKeeper * defense_keeper_;

  //sheets
  CPropertySheet m_sheet;

  //Observer
  std::vector<ObserverBase*> entry_observers_;

  //gui
  CBitmap m_bmpBackground;

  CColorStatic m_sta_rank;
  CColorStatic m_sta_money;
  CColorStatic m_sta_metal;
  CColorStatic m_sta_crystal;
  CColorStatic m_sta_doplogen;
  CColorStatic m_sta_power;
  CColorStatic m_sta_regtime;

  CColorStatic m_log_rank;
  CColorStatic m_log_produce;
  CColorStatic m_log_metal;
  CColorStatic m_log_crystal;
  CColorStatic m_log_diplogen;
  CColorStatic m_log_power;
  
  NOTIFYICONDATA shell_notify_data_;
  //  
  bool is_exit_after_tasks_over_;

  //menu
  CMenu menu_tray_;

  //timer for save
  uchar save_mode_;
  ElapsedTimer timer_for_save_;

  //buttons
  CButtonST m_btn_account_info;
  
public:
	CXGameDlg(GameData* d , CWnd* pParent = NULL);	// standard constructor
  ~CXGameDlg();
  //notifys
  void Notify_Score_Changed();
  void Notify_Resource_Changed();
  void Notify_Buildings_LevelUp();
  void Notify_Technics_LevelUp();
  void Notify_Building_ProducePercent_Changed(int index , double percent);
  void Notify_Ships_Changed(bool has_sunpower = false);
  void Notify_Ships_Produced(int type , ulong number);
  void Notify_Defenses_Changed();
  void Notify_Defenses_Produced(int type , ulong number);
  void Notify_Resource_Consumed(double r);
  void Notify_Galaxy_Update();
  void Notify_Money_Change();
  void Notify_Galaxy_UpdateTimer_Go();
  void Notify_Trade_Center_Time_Go(CString para);
  void Notify_SuperTransferGate_Time_Go(CString para);

  void SwitchToPage(CPropertyPage* active_page);
  void SwitchToPage(int index);

  void MessageNotify(int new_info_num);
  bool IsSilentMode(){return is_silent_mode_;}

// Dialog Data
	//{{AFX_DATA(CXGameDlg)
	enum { IDD = IDD_XGAME_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXGameDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CXGameDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnDestroy();
  afx_msg LRESULT OnHotKey(WPARAM wParam,LPARAM lParam);
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtnAccountInfo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
  void Initialize();
  void InitControls();
  void InitSheet();
  void InitSkins();
  void InitKernel();

  void addsystray();
  void delsystray();

  void SetWindowStatus(WINDOW_TYPE type);
  void Logoff();

  int GetSaveModeMenuIDByMode()
  {
    switch(save_mode_)
    {
    case SAVE_T_5:
    	return IDR_SHELL_MENU_SAVE_05;
    case SAVE_T_10:
    	return IDR_SHELL_MENU_SAVE_10;
    case SAVE_T_20:
      return IDR_SHELL_MENU_SAVE_20;
    case SAVE_T_30:
      return IDR_SHELL_MENU_SAVE_30;
    case SAVE_T_40:
    	return IDR_SHELL_MENU_SAVE_40;
    case SAVE_T_50:
    	return IDR_SHELL_MENU_SAVE_50;
    case SAVE_T_60:
      return IDR_SHELL_MENU_SAVE_60;
    case SAVE_T_DISABLE:
      return IDR_SHELL_MENU_SAVE_DISABLE;
    default:
      assert(!"error save mode");
      return IDR_SHELL_MENU_SAVE_DISABLE;
    }
  }

  void SetSaveModeByMenuID(int id)
  {
    switch(id)
    {
    case IDR_SHELL_MENU_SAVE_05:
    	save_mode_ = SAVE_T_5;
      break;
    case IDR_SHELL_MENU_SAVE_10:
    	save_mode_ = SAVE_T_10;
      break;
    case IDR_SHELL_MENU_SAVE_20:
      save_mode_ = SAVE_T_20;
      break;
    case IDR_SHELL_MENU_SAVE_30:
      save_mode_ = SAVE_T_30;
      break;
    case IDR_SHELL_MENU_SAVE_40:
    	save_mode_ = SAVE_T_40;
      break;
    case IDR_SHELL_MENU_SAVE_50:
    	save_mode_ = SAVE_T_50;
      break;
    case IDR_SHELL_MENU_SAVE_60:
      save_mode_ = SAVE_T_60;
      break;
    case IDR_SHELL_MENU_SAVE_DISABLE:
      save_mode_ = SAVE_T_DISABLE;
      break;
    default:
      save_mode_ = SAVE_T_DISABLE;
      assert(!"error save mode menu id");
    }
  }

  ushort GetSaveTime()
  {
    switch(save_mode_)
    {
    case SAVE_T_5:
    	return 5;
    case SAVE_T_10:
    	return 10;
    case SAVE_T_20:
      return 20;
    case SAVE_T_30:
      return 30;
    case SAVE_T_40:
    	return 40;
    case SAVE_T_50:
    	return 50;
    case SAVE_T_60:
      return 60;
    case SAVE_T_DISABLE:
      return 0xffff;
    default:
      assert(!"error save mode");
      return 0xffff;
    }
  }
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XGAMEDLG_H__638DECA6_75DC_4574_971E_EBE75C7D4B1C__INCLUDED_)
