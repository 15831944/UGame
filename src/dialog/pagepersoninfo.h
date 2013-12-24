#if !defined(AFX_PAGEPERSONINFO_H__BFB23A07_7C01_44D5_9FC0_CA699E931812__INCLUDED_)
#define AFX_PAGEPERSONINFO_H__BFB23A07_7C01_44D5_9FC0_CA699E931812__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// pagepersoninfo.h : header file
//

#include "ObserverBase.h"
#include "PageIcon.h"
#include "ReportCtrl.h"

enum{
  SORT_BY_NAME,
  SORT_BY_FLEET,
  SORT_BY_POSITION,
};

class CPagePersonInfo : public CPageIcon , public ObserverBase
{
private:
  CFont font_list;

public:
	CPagePersonInfo(UINT iconID = NULL , CWnd* pParent = NULL);   // standard constructor
  virtual void Notify_Init();
  virtual void Notify_Galaxy_Update();
  void    ViewRank(PlaniPos pos , bool is_self);
  void    GetMyRank(uchar& rank_type , int& rank);
  void    UpdateRank();

  // Dialog Data
	//{{AFX_DATA(CPagePersonInfo)
	enum { IDD = IDD_PAGE1_PERSON_INFO };
	CListCtrl	m_list;
	int		m_sort_type;
	UINT	m_gala;
	UINT	m_pos;
	UINT	m_sys;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPagePersonInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPagePersonInfo)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnBtnGo();
	afx_msg void OnBtnGoTarget();
	afx_msg void OnChangeEditGala();
	afx_msg void OnChangeEditPos();
	afx_msg void OnChangeEditSys();
	afx_msg void OnBtnUpdaterank();
	//}}AFX_MSG
  afx_msg void OnSetItemColor(NMHDR*, LRESULT*);
	DECLARE_MESSAGE_MAP()

private:
  void Initialize();  
  void UpdateListData();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEPERSONINFO_H__BFB23A07_7C01_44D5_9FC0_CA699E931812__INCLUDED_)
