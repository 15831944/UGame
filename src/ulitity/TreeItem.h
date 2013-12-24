#if !defined(AFX_TREEITEM_H__8B294049_593F_4A53_9311_41C16B01E847__INCLUDED_)
#define AFX_TREEITEM_H__8B294049_593F_4A53_9311_41C16B01E847__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TreeItem.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CTreeItem window

class CTreeItem : public CTreeCtrl
{
private:
  CImageList m_ImgLst; 

public:
	CTreeItem(int nItem, int nSubItem);

protected:
  BOOL IsLeafNote(HTREEITEM hItem);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeItem)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTreeItem();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTreeItem)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnNcDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

inline
BOOL CTreeItem::IsLeafNote(HTREEITEM hItem)
{
  return hItem != NULL && (!ItemHasChildren(hItem)) && GetParentItem(hItem) != NULL; 
  
}


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEITEM_H__8B294049_593F_4A53_9311_41C16B01E847__INCLUDED_)
