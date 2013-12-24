#if !defined(AFX_PAGERESOURCE_H__887C6755_7957_4604_8EB2_BA4272C77E9D__INCLUDED_)
#define AFX_PAGERESOURCE_H__887C6755_7957_4604_8EB2_BA4272C77E9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// pageresource.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageResource dialog
#include "ObserverBase.h"
#include "PageIcon.h"

class CPageResource : public CPageIcon , public ObserverBase
{
private:
  CFont font;
  ulong buff_solar_plant_;
public:
	CPageResource(UINT iconID = NULL , CWnd* pParent = NULL);   // standard constructor
  virtual void Notify_Building_LevelUp();
  virtual void Notify_Ships_Changed();

// Dialog Data
	//{{AFX_DATA(CPageResource)
	enum { IDD = IDD_PAGE3_RESOURCE };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageResource)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageResource)
	virtual BOOL OnInitDialog();
	afx_msg void OnRclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuResourceP00();
	afx_msg void OnMenuResourceP10();
	afx_msg void OnMenuResourceP100();
	afx_msg void OnMenuResourceP20();
	afx_msg void OnMenuResourceP30();
	afx_msg void OnMenuResourceP40();
	afx_msg void OnMenuResourceP50();
	afx_msg void OnMenuResourceP60();
	afx_msg void OnMenuResourceP70();
	afx_msg void OnMenuResourceP80();
	afx_msg void OnMenuResourceP90();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
  afx_msg void OnSetItemColor(NMHDR*, LRESULT*);
	DECLARE_MESSAGE_MAP()
private:
  void UpdateListData();
  CMenu menu;

  int GetCurrentPercentIndex(int building_index);
  void ChangePercent(int level);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGERESOURCE_H__887C6755_7957_4604_8EB2_BA4272C77E9D__INCLUDED_)
