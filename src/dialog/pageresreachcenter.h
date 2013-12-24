#if !defined(AFX_PAGERESREACHCENTER_H__C0295264_3876_4B7E_9DD0_4537A494DAC8__INCLUDED_)
#define AFX_PAGERESREACHCENTER_H__C0295264_3876_4B7E_9DD0_4537A494DAC8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// pageresreachcenter.h : header file
//

#include "ObserverBase.h"
#include "HTMLListCtrl.h"
#include "ElapsedTimer.h"
#include "PageIcon.h"
#include "ListCtrlex.h"

class CPageResreachCenter : public CPageIcon , public ObserverBase
{
private:
  CFont font_list;
  CFont font_ctrls_text;

  CImageList	m_ImageList;
  CImageList	m_ImageList_small;
  CHTMLListCtrl m_list;
  ElapsedTimer  research_timer_;
  int cur_research_index;

  int buff_cosume_metal;
  int buff_cosume_cryst;
  int buff_cosume_diplo;

  bool is_researching_;
  std::vector<int> entry_tasks_;
  
public:
	CPageResreachCenter(UINT iconID = NULL , CWnd* pParent = NULL);   // standard constructor
  virtual void Notify_Exit();
  virtual void Notify_Building_LevelUp();
  virtual void Notify_Resource_Changed() ;
  virtual void Notify_Technics_LevelUp();
// Dialog Data
	//{{AFX_DATA(CPageResreachCenter)
	enum { IDD = IDD_DIALOG_RESEARCH_CENTER };
	CListCtrl	m_ProgressList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageResreachCenter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageResreachCenter)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnResearch();
	afx_msg void OnBtnCancel();
	afx_msg void OnDestroy();
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

  void CancelRearching();
  void SetItemInfo(bool bInit);
  void UpdateIndex();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGERESREACHCENTER_H__C0295264_3876_4B7E_9DD0_4537A494DAC8__INCLUDED_)
