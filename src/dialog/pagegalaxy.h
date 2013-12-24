#if !defined(AFX_PAGEGALAXY_H__3111DEDA_BDA4_4C36_92D5_2044D02CDB7F__INCLUDED_)
#define AFX_PAGEGALAXY_H__3111DEDA_BDA4_4C36_92D5_2044D02CDB7F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// pagegalaxy.h : header file
//

#include "ObserverBase.h"
#include "UStar.h"
#include "PageIcon.h"
#include "MFECToolTip.h"
#include "ElapsedTimer.h"
#include "intedit.h"

extern float _speed_adjust_;

template<class T , class U>
class match_func : public binary_function<T, U , bool>
{
public:
  result_type operator() ( const first_argument_type x , const second_argument_type y) const
  {
    return x.position == y;
  }
}; 

class CPageGalaxy : public CPageIcon , public ObserverBase
{
private:
  CMenu menu;
  CFont font_list;
  std::vector<Star> entry_starts_;
  CImageList m_ImageList;
  unsigned long refresh_time_;

  std::vector<Sort_Table_t> enrty_sorted_stars;
  ElapsedTimer update_timer_;
  bool is_attacking_player;

public:
	CPageGalaxy(UINT iconID = NULL , CWnd* pParent = NULL);   // standard constructor
  Star& GetStar(int index);
  Star& GetStar(const PlaniPos& pos);
  std::vector<Sort_Table_t>& GetStarTable()
  {
    return enrty_sorted_stars;
  }

  ulong get_refresh_mimutes()
  {
    return refresh_time_;
  }
  void UpdateShowStarInfo();
  void Notify_Technics_LevelUp();
  void UpdateSortTable();
  void DoneAttacking();
  CString GetUpdateTimeString()
  {
    return update_timer_.ToCString();
  }

// Dialog Data
	//{{AFX_DATA(CPageGalaxy)
	enum { IDD = IDD_DIALOG_GALAXY };
	CIntEdit	m_ctl_sys;
	CIntEdit	m_ctl_gala;
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageGalaxy)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageGalaxy)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuGalaxyAttack();
	afx_msg void OnMenuGalaxySpy();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnBtnGalaLeft();
	afx_msg void OnBtnGalaRight();
	afx_msg void OnBtnSysLeft();
	afx_msg void OnBtnSysRight();
	afx_msg void OnBtnShow();
	afx_msg void OnBtnSpys();
	afx_msg void OnMenuGalaxyViewRank();
	afx_msg void OnMenuGalaxyRecycle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
  void InitDlgCtrls();
  void CreatStars();
  UINT GenerateMagicNumber(int r);
  void CreateImageList();
  void set_refresh_mimutes()
  {
#ifndef USE_FOR_SMALL_GALAXY_VERSION
    float speed_ratio = pow(_speed_adjust_ , 0.5);
    int seed = 4000.0 / (pow(2 , COMPUTER_RANK())) / speed_ratio;
    refresh_time_ = RandomNumber(seed) + 10;
#else
    refresh_time_ = 12 * 60.0;
#endif
  }  

  void SearchSysStars(uchar gala , ushort sys , std::vector<Star*>& result)
  {
    assert(gala <= MAX_GALAXY_GALA && sys <= MAX_GALAXY_SYS);
    PlaniPos pos(gala , sys , 1);
    ulong index = Pos2Index(pos);
    for(int i = 0 ; i < MAX_GALAXY_POS ; ++i)
    {
      Star* s = &entry_starts_[index + i];
      result.push_back(s);
    }
  }

  void ShowStars(uchar gala , ushort sys);
  CString Type2Name(int type , const PlaniPos& pos);
  uchar COMPUTER_RANK()
  {
    return GetDataPtr()->GetLoginedAccountComputerRank();
  }
};

inline UINT CPageGalaxy::GenerateMagicNumber(int r)
{
  CTime cur_time = CTime::GetCurrentTime();
  unsigned long seed1 = cur_time.GetYear() + cur_time.GetMonth() + cur_time.GetDay() + cur_time.GetHour() + cur_time.GetMinute() + cur_time.GetSecond();
  unsigned long seed2 = ::GetTickCount();
  unsigned long seed3 = (unsigned)time(NULL);
  UINT magic_number = seed1 * (r + 1) + seed2 * (r + 3) + seed3 * (r + 5);
  return magic_number;
}

inline CString CPageGalaxy::Type2Name(int type , const PlaniPos& pos)
{
  CString info;
  switch(type)
  {
  case STAR_T_ENEMY:
  	info.Format("%d:%d:%d" , pos.Gala , pos.Sys , pos.Pos);
    break;
  case STAR_T_NONE:
  	info = "";
    break;
  case STAR_T_SELF:
  	info = GetDataPtr()->GetLoginedAccountName();
    break;
  default:
    assert(false);
    break;
  }
  return info;
}

inline
void CPageGalaxy::DoneAttacking()
{
  is_attacking_player = false;
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


#endif // !defined(AFX_PAGEGALAXY_H__3111DEDA_BDA4_4C36_92D5_2044D02CDB7F__INCLUDED_)
