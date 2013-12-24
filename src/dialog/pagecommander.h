#if !defined(PAGE_COMMANDER_HEADER_)
#define PAGE_COMMANDER_HEADER_

#include "ObserverBase.h"
#include "ElapsedTimer.h"
#include "UStar.h"
#include "EditList.h"
#include "PageIcon.h"
#include "WarSimulator.h"

#include "ColorStatic.h"
#include "ToolTipListCtrl.h"
#include "MFECToolTip.h"

#include "intedit.h"

#include "comboboxex.h"

#define MAX_ID 128


class CPageCommander : public CPageIcon , public ObserverBase
{
private:  
  CFont font_list;
  std::map<int , COMMAND_TASK> map_tasks_;
  int task_counter_;
  CColorStatic	m_sta_is_max;
  CColorStatic	m_sta_task_number;

  CColorStatic  m_sta_transfer;
  CColorStatic  m_sta_ships_number;
  CColorStatic  m_sta_time;
  CColorStatic  m_sta_oil;
  CColorStatic  m_sta_left_res;
  CMenu menu_list;
  
  WarSimulator war_;
  struct ID_t{
    uchar  id_;
    bool   bUsed;
  };
  std::vector<ID_t> entry_IDs_;
  PlaniPos self_leave_star_pos_;
  double  available_transfer_number_;

  struct Radio_t{
    UINT id;
    bool bShow;
    Radio_t(UINT i , bool b) : id(i) , bShow(b){}
  };

  //counter for gate
  ElapsedTimer timer_for_gate_;
  ElapsedTimer timer_for_trade_;
  COMMAND_TASK enemy_task;

public:
	CPageCommander(UINT iconID = NULL , CWnd* pParent = NULL);   // standard constructor
  bool SpyFleetOut(Star& star , bool isGalaxyCMD = true);
  void Prepare_Attack(int target_pos);
  void Prepare_Recycle(int target_pos);
  void NotifyFinishedTrade();
  ulong GetAllFleetNumber();
  void  EnemyAttackComing(Star& s);

  virtual void Notify_Exit();
  virtual void Notify_Ships_Changed();
  virtual void Notify_Technics_LevelUp();
  virtual void Notify_Init();
  virtual void Notify_Resource_Changed();

// Dialog Data
	//{{AFX_DATA(CPageCommander)
	enum { IDD = IDD_DIALOG_COMMANDER };
	CListCtrl	m_list_enemy;
	CIntEdit	m_ctl_pos_pos;
	CIntEdit	m_ctl_pos_sys;
	CIntEdit	m_ctl_pos_gala;
	CMyComboBox	m_ctl_target_type;
	CMyComboBox	m_ctl_speed;
	CMyComboBox	m_ctl_fast_star;
	CMyComboBox	m_ctl_self_star;
	CToolTipListCtrl	m_list2;
	CEditList	m_list1;
	UINT	m_default_spy;
	int		m_speed_ratio;
	int		m_task_type;
	int		m_self_star;
	UINT	m_transfer_metal;
	UINT	m_transfer_crystal;
	UINT	m_transfer_diop;
	int		m_target_star_type;
	int		m_fast_star;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageCommander)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageCommander)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	afx_msg void OnKillfocusEditDefault();
	afx_msg void OnBtnAll();
	afx_msg void OnBtnNone();
	afx_msg void OnDblclkListTask(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEdit1();
	afx_msg void OnEditchangeComboSpeed();
	afx_msg void OnCloseupComboSpeed();
	afx_msg void OnRclickListTaskList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuFleetCallback();
	afx_msg void OnCloseupCombo1();
	afx_msg void OnCloseupComboFaststar();
	afx_msg void OnCloseupCombo2();
	afx_msg void OnBtnMetalMax();
	afx_msg void OnBtnCrystalMax();
	afx_msg void OnBtnDiopMax();
	afx_msg void OnChangeEditCrystal();
	afx_msg void OnChangeEditDiop();
	afx_msg void OnChangeEditMetal();
	afx_msg void OnBtnAllResource();
	afx_msg void OnBtnDestroycolony();
	afx_msg void OnBtnProducemoon();
	afx_msg void OnBtnProducegate();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnBtnTransfer();
	afx_msg void OnSelchangeCombo2();
	afx_msg void OnSelchangeComboSpeed();
	afx_msg void OnSelchangeComboFaststar();
	afx_msg void OnBtnTrade();
	afx_msg void OnBtnAllWar();
	afx_msg void OnBtnAllBanjia();
	//}}AFX_MSG
  afx_msg void OnSetItemColor(NMHDR*, LRESULT*);
	DECLARE_MESSAGE_MAP()

private:
  //ID manager
  void InitIDManager();
  void UpdateCombo();
  void NotifySelfStarChanged(uchar pos);
  uchar GetFreeId();
  void  SetIDFlag(uchar id , bool bUsed);
  
  //out
  void AttackFleetOut(int target_pos);
  void RecycleFleetOut(int target_pos);
  void TransferFleetOut(int target_pos  , int tasktype);

  bool CheckShips();
  void AssignShips(FLEET& ships , bool produce_moon = false);
  int GetShipsNumber(Ships_NUMs& ships);
  bool CheckColony();
  void Notify_Task_Settings_Changed();
  void ShipsGoHome();

  //spy&war&recycle
  void DoSpy(COMMAND_TASK& task);
  void DoneSpy(COMMAND_TASK& task);
  
  void DoAttack(COMMAND_TASK& task);
  void DoneAttack(COMMAND_TASK& task);

  void DoRecycle(COMMAND_TASK& task);
  void DoneRecycle(COMMAND_TASK& task);

  void DoTransfer(COMMAND_TASK& task);
  void DoneTransfer(COMMAND_TASK& task);
  void DoneDispatch(COMMAND_TASK& task);
  void DoneColony(COMMAND_TASK& task);

  void UpdateShipsChanged(uchar self_star_index);
  bool CheckSpyPlanet();
  void UpdateTaskList();
  CString ConvertTaskType(bool is_go , int t);

  void UpdateTimerInfo(uchar task_index);
  void CallbackFleetBack(COMMAND_TASK& task);

  //bools
  bool CanAttack(int star_index);
  bool CanSpy(int star_index);
  bool CanTransferOrDispatch(int star_index);
  bool CanColonize(int star_index);
  void SetTransferNumber(int type);
  void LayoutTaskRadios();
  bool CalcTransferRes(FLEET& fleet , PlaniPos& self , PlaniPos& target , Resource& result);
  bool HasFleetBehavior(const PlaniPos& pos);
  uchar ACTIVE_STAR_INDEX()
  {
    return (uchar)m_ctl_self_star.GetItemData(m_self_star);
  }

  void StarResChanged(uchar index);
  void StarFleetChanged(uchar index);
  void TaskCounterLabelChange();

  void FleetTaskOverTip();
  void AutoSetTask();
  void EnemyAttacking();
};

inline void CPageCommander::AutoSetTask()
{
  //ships should not equal 0
  bool flag = 
     atoi(m_list1.GetItemText(BOAT_SMALL_SCUTTER , 2)) == 0 &&
     atoi(m_list1.GetItemText(BOAT_LARGE_SCUTTER , 2)) == 0 &&
     atoi(m_list1.GetItemText(BOAT_LIGHT_FIGHTER , 2)) == 0 &&
     atoi(m_list1.GetItemText(BOAT_HEAVY_FIGHTER , 2)) == 0 &&
     atoi(m_list1.GetItemText(BOAT_SPY_PLANET , 2))    == 0 &&
     atoi(m_list1.GetItemText(BOAT_CRUISER , 2))       == 0 &&
     atoi(m_list1.GetItemText(BOAT_WARSHIP , 2))       == 0 &&
     atoi(m_list1.GetItemText(BOAT_CONOLY , 2))        == 0 &&
     //recycle > 0
     atoi(m_list1.GetItemText(BOAT_RECYCLE , 2))       >  0 &&
     atoi(m_list1.GetItemText(BOAT_BOMBER , 2))        == 0 &&
     atoi(m_list1.GetItemText(BOAT_DESTROYER , 2))     == 0 &&
     atoi(m_list1.GetItemText(BOAT_DS , 2))            == 0;
  m_target_star_type = int(flag);
  UpdateData(FALSE);
}

inline bool CPageCommander::CheckShips()
{
  //ships should not equal 0
  if(atoi(m_list1.GetItemText(BOAT_SMALL_SCUTTER , 2)) == 0 &&
     atoi(m_list1.GetItemText(BOAT_LARGE_SCUTTER , 2)) == 0 &&
     atoi(m_list1.GetItemText(BOAT_LIGHT_FIGHTER , 2)) == 0 &&
     atoi(m_list1.GetItemText(BOAT_HEAVY_FIGHTER , 2)) == 0 &&
     atoi(m_list1.GetItemText(BOAT_SPY_PLANET , 2))    == 0 &&
     atoi(m_list1.GetItemText(BOAT_CRUISER , 2))       == 0 &&
     atoi(m_list1.GetItemText(BOAT_WARSHIP , 2))       == 0 &&
     atoi(m_list1.GetItemText(BOAT_CONOLY , 2))        == 0 &&
     atoi(m_list1.GetItemText(BOAT_RECYCLE , 2))       == 0 &&
     atoi(m_list1.GetItemText(BOAT_BOMBER , 2))        == 0 &&
     atoi(m_list1.GetItemText(BOAT_DESTROYER , 2))     == 0 &&
     atoi(m_list1.GetItemText(BOAT_DS , 2))            == 0)
     return false;
  return true;
}

inline bool CPageCommander::CheckSpyPlanet()
{
  //spy ships should not equal 0
  return atoi(m_list1.GetItemText(BOAT_SPY_PLANET , 2)) > 0;
}

inline bool CPageCommander::CheckColony()
{
  if(atoi(m_list1.GetItemText(BOAT_SMALL_SCUTTER , 2)) == 0 &&
     atoi(m_list1.GetItemText(BOAT_LARGE_SCUTTER , 2)) == 0 &&
     atoi(m_list1.GetItemText(BOAT_LIGHT_FIGHTER , 2)) == 0 &&
     atoi(m_list1.GetItemText(BOAT_HEAVY_FIGHTER , 2)) == 0 &&
     atoi(m_list1.GetItemText(BOAT_SPY_PLANET , 2))    == 0 &&
     atoi(m_list1.GetItemText(BOAT_CRUISER , 2))       == 0 &&
     atoi(m_list1.GetItemText(BOAT_WARSHIP , 2))       == 0 &&
     atoi(m_list1.GetItemText(BOAT_CONOLY , 2))        >  0 &&
     atoi(m_list1.GetItemText(BOAT_RECYCLE , 2))       == 0 &&
     atoi(m_list1.GetItemText(BOAT_BOMBER , 2))        == 0 &&
     atoi(m_list1.GetItemText(BOAT_DESTROYER , 2))     == 0 &&
     atoi(m_list1.GetItemText(BOAT_DS , 2))            == 0)
     return true;
  return false;
}

inline void CPageCommander::AssignShips(FLEET& ships , bool produce_moon)
{
  UpdateData(TRUE);
  assert(ships.size() == BOAT_MAX);
  for(int i = 0 ; i < BOAT_MAX ; ++i)
  {
    SItem& item = ships[i];
    item.OwnerID = 0;
    item.Type = ITEM_TYPE(i);
    ulong num = atoi(m_list1.GetItemText(i , 2));
    if(i == BOAT_SUNPOWER_PLANET && (!produce_moon))
    {
      num = 0L;
    }
    item.Num = num;
  }
}

inline CString CPageCommander::ConvertTaskType(bool is_go , int t)
{
  CString info;
  switch(t)
  {
  case TASK_T_SPY:
    info = "¼äµý";
    break;
  case TASK_T_ATTACK:
    info = "¹¥»÷";
  	break;
  case TASK_T_RECYCLE:
    info = "»ØÊÕ";
    break;
  case TASK_T_TRANSPORT:
    info = "ÔËÊä";
    break;
  case TASK_T_DISPATCH:
    info = "ÅÉÇ²";
    break;
  case TASK_T_COLONIZE:
    info = "Ö³Ãñ";
    break;
  default:
    assert(false);
    break;
  }
  if(!is_go){
    info += "·µº½";
  }
  return info;
}

inline uchar CPageCommander::GetFreeId()
{
  for(uchar i = 0 ; i < MAX_ID ; ++i)
  {
    if(entry_IDs_[i].bUsed == false)
    {
      entry_IDs_[i].bUsed = true;
      return i;
    }
  }
  return MAX_ID;
}

inline void  CPageCommander::SetIDFlag(uchar id , bool bUsed)
{
  assert(id < MAX_ID);
  entry_IDs_[id].bUsed = bUsed;
}

inline ulong CPageCommander::GetAllFleetNumber()
{
  ulong num = GetDataPtr()->ACCOUNT_AVAILABLE_FLEET_NUMBER();
  std::map<int , COMMAND_TASK>::iterator itor = map_tasks_.begin();
  for( ; itor != map_tasks_.end() ; ++itor)
  {
    num += war_.GetFleetShipsNumber((*itor).second.fleet);
  }
  return num;
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(PAGE_COMMANDER_HEADER_)
