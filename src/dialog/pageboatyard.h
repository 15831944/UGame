#if !defined(_PAGE_BOATYARD_HEADER_)
#define _PAGE_BOATYARD_HEADER_

#include "ObserverBase.h"
#include "HTMLListCtrl.h"
#include "ElapsedTimer.h"
#include "PageIcon.h"
#include "ListCtrlex.h"
#include "HighFrequencyElapsedTimer.h"

class CPageBoatyard : public CPageIcon , public ObserverBase
{
private:
  CFont font_list;
  CFont font_ctrls_text;

  CImageList	m_ImageList;
  CImageList	m_ImageList_small;
  CHTMLListCtrl m_list;
  ElapsedTimer  produce_timer_;
  int cur_produce_index;

  HighFrequencyElapsedTimer  high_produce_timer_;

  double buff_cosume_metal;
  double buff_cosume_cryst;
  double buff_cosume_diplo;

  bool is_producing_;

  struct Produce_Tast_t{
    int  index;
    UINT number;
  };
  std::vector<Produce_Tast_t> entry_tasks_;
  unsigned long counter_;

public:
	CPageBoatyard(UINT iconID = NULL , CWnd* pParent = NULL);   // standard constructor
  virtual void Notify_Exit();
  virtual void Notify_Building_LevelUp();
  virtual void Notify_Technics_LevelUp();
  virtual void Notify_Ships_Changed();
  virtual void Notify_Resource_Changed();

// Dialog Data
	//{{AFX_DATA(CPageBoatyard)
	enum { IDD = IDD_DIALOG_BOATYARD };
	CListCtrl	m_ProgressList;
	UINT	m_ships_produce_number;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageBoatyard)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageBoatyard)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnCancel();
	afx_msg void OnBtnProduce();
	afx_msg void OnClickListProgress(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickListProgress(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEdit1();
	//}}AFX_MSG
  afx_msg void OnMyList_SelectionChanged(NMHDR* pNMHDR, LRESULT*);
  afx_msg void OnMyList_LButtonDClick(NMHDR* pNMHDR, LRESULT*);  
	DECLARE_MESSAGE_MAP()

private:
  void CreateImageList();
  void InitDlgCtrls();
  void InitList();

  void StartOneTask();
  void EndOneTask();
  
  BOOL IsResourceEnough(int index , UINT number = 1);
  void UpdateItemText();
  UINT GetMaxProduceNumber(int index , UINT def_number);

  void StartRearching();
  void EndRearching();

  void CancelCurrentProducing();
  void CancelProducingByIndex(int index);
  void SetItemInfo(bool bInit);
  void UpdateIndex();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_PAGE_BOATYARD_HEADER_)
