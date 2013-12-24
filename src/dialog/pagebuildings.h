#if !defined(_PAGE_BUILDING_HEADER)
#define _PAGE_BUILDING_HEADER

#include "ObserverBase.h"
#include "ListBoxST.h"
#include "Building.h"
#include "HTMLListCtrl.h"
#include "ElapsedTimer.h"
#include "PageIcon.h"
#include "ListCtrlex.h"

class CPageBuildings : public CPageIcon , public ObserverBase
{
private:
  CFont font_list;
  CFont font_ctrls_text;

  CImageList	m_ImageList;
  CImageList	m_ImageList_small;
  CHTMLListCtrl m_list;
  ElapsedTimer  building_timer_;
  int cur_building_index;

  double buff_cosume_metal;
  double buff_cosume_cryst;
  double buff_cosume_diplo;
  bool is_building_;

  std::vector<int> entry_tasks_;


public:
	CPageBuildings(UINT iconID = NULL , CWnd* pParent = NULL);   // standard constructor
  ~CPageBuildings();
  virtual void Notify_Exit();
  virtual void Notify_Resource_Changed();
  virtual void Notify_Building_LevelUp();
  virtual void Notify_Technics_LevelUp();
  virtual void Notify_Init();

// Dialog Data
	//{{AFX_DATA(CPageBuildings)
	enum { IDD = IDD_PAGE2_BUILDINGS };
	CListCtrl	m_ProgressList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageBuildings)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageBuildings)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBtnBuild();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnBtnCancel();
	afx_msg void OnClickListProgress(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickListProgress(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
  afx_msg void OnMyList_SelectionChanged(NMHDR* pNMHDR, LRESULT*);
  afx_msg void OnMyList_LButtonDClick(NMHDR* pNMHDR, LRESULT*) ;
	DECLARE_MESSAGE_MAP()
    
private:
  void CreateImageList();
  void InitDlgCtrls();
  void InitList();

  void StartOneTask();
  void EndOneTask();
  
  BOOL IsResourceEnough(int index);
  void UpdateItemText();

  void CancelBuilding();
  void AdjustOfflineResource();

  void SetItemInfo(bool bInit);
  void UpdateIndex();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_PAGE_BUILDING_HEADER)
