#if !defined(AFX_EDITITEM_H__834127E5_9297_11D5_8AFA_DAC6E5A1C54B__INCLUDED_)
#define AFX_EDITITEM_H__834127E5_9297_11D5_8AFA_DAC6E5A1C54B__INCLUDED_

class CEditList;
class CEditItem : public CEdit
{
private:
   BOOL bNumOnly;
   CEditList* pParentListCtrl;
   int m_limit_number;
   CString max_number;
   
public:
	CEditItem(int nItem, int nSubItem, CString &sContent , BOOL num = true , CEditList* parent = NULL , int limitnum = 10 , CString def_num = "0");

private:
  BOOL IsNumber(UINT nChar);
  
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditItem)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditItem();

	// Generated message map functions
protected:
	int		m_nItem;
	int		m_nSubItem;
	CString m_sContent;
	BOOL	m_bVK_ESCAPE;
	//{{AFX_MSG(CEditItem)
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnNcDestroy();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetfocus();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

inline
BOOL CEditItem::IsNumber(UINT nChar)
{
  if( (nChar >= '0' && nChar <= '9')  || nChar == VK_DELETE || nChar == VK_BACK)
    return TRUE;
  return FALSE;
}

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITITEM_H__834127E5_9297_11D5_8AFA_DAC6E5A1C54B__INCLUDED_)
