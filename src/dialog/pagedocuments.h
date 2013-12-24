#if !defined(AFX_PAGEDOCUMENTS_H__D1C95486_C6DA_4FF9_B4C3_B02550E40F34__INCLUDED_)
#define AFX_PAGEDOCUMENTS_H__D1C95486_C6DA_4FF9_B4C3_B02550E40F34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// pagedocuments.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageDocuments dialog.

#include "ObserverBase.h"
#include "PageIcon.h"
#include "ListBoxST.h"
#include "ReportCtrl.h"

class CPageDocuments : public CPageIcon , public ObserverBase
{
private:
  typedef void (CPageDocuments::*PARSING_FUNCTION)(HTREEITEM hti, void *pvParam);
  typedef bool (CPageDocuments::*FindMatchItemFunc)(HTREEITEM hti);

  CImageList m_image_index;
  struct TreeItemData_t
  {
    int layer;
    int index;
    int parent_index;
    CString name;
    TreeItemData_t(int l , int i , int pi , const CString& n);
  };

  HTREEITEM cur_sel_item_;
  int find_first_;
  int find_second_;
public:
	CPageDocuments(UINT iconID = NULL , CWnd* pParent =NULL);   // standard constructor
  void ShowDocument(int first , int second);
// Dialog Data
	//{{AFX_DATA(CPageDocuments)
	enum { IDD = IDD_DIALOG_SHOW_DETAILS };
	CReportCtrl	m_list;
	CTreeCtrl	m_tree;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageDocuments)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageDocuments)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangedTree1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnDblclkTree1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
  void Initialize();
  void CreateImageList();
  void InitTree();

  void DisplayFactory(int index);
  void DisplayResearch(int index);
  void DisplayShips(int index);
  void DeleteAllColumns();

  void DisplayDummy(int index);
  void ParseTree(PARSING_FUNCTION pf, HTREEITEM hti  = TVI_ROOT , void *pvParam  = NULL );
  void pfClear(HTREEITEM hti, void *);
  bool pfFindItem(HTREEITEM hti);
  void FindItem(FindMatchItemFunc pf, HTREEITEM hti = TVI_ROOT) ;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEDOCUMENTS_H__D1C95486_C6DA_4FF9_B4C3_B02550E40F34__INCLUDED_)
