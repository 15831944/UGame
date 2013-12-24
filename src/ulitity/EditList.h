#if !defined(AFX_EDITLIST_H__834127E6_9297_11D5_8AFA_DAC6E5A1C54B__INCLUDED_)
#define AFX_EDITLIST_H__834127E6_9297_11D5_8AFA_DAC6E5A1C54B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EditList.h : header file
//
typedef int (* fGetType) (int);
#include <map>
#include <vector>

using namespace std;
class CEditItem;

#define WM_LISTCTRL_TEXT_CHANGED WM_USER + 25

#include "ToolTipListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CEditList window
class CEditList : public CToolTipListCtrl
{
private:
  CWnd* pParent;
  int   m_limit_number;
  int   ID_EDIT;
  int   ID_COMBO;
  
public:
	CEditList(CWnd* bar , UINT IDimage = NULL , BOOL bMenu = TRUE);
  virtual ~CEditList();

	// Attributes
public:
	enum eType{	eReadOnly ,	eEdit , eCombo , eTree};	
	fGetType m_fGetType;
	
	// Operations
public:
  void SetColumnType(fGetType func) { m_fGetType = func;}
  void SetColumnType(int col , int type);

  void UpdateIndex();  
  void DeleteAllColumns();

  void MoveSelItemUp();
  void MoveSelItemDown();

  void AddNewItem();
  void DeleteSeletedItem();

  void CopySelItem();
  void CutSelItem();
  void PasteSelItem();

  void EnableMenu(BOOL bEnable = TRUE);
  void EnableMenuItems(vector<int>& items , BOOL bEnable = TRUE);
  void Initialize();
  int GetColumnCount();
  void SetLimitNumber(int num){m_limit_number = num;}

  void Notify_Text_Changed();

  virtual BOOL DeleteAllItems( );
  virtual BOOL DeleteItem( int nItem );

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditList)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
	
	// Generated message map functions
protected:	
	CComboBox * ComboItem( int nItem,  int nSubItem);
	CEdit *     EditItem( int nItem, int nSubItem);
  CTreeCtrl*  TreeItem( int nItem, int nSubItem);

	//{{AFX_MSG(CEditList)
	afx_msg void OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClick(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

inline
int CEditList::GetColumnCount()
{
  return GetHeaderCtrl()->GetItemCount();
}

inline
void CEditList::DeleteAllColumns()
{
  int sz = GetColumnCount();
  for (int i = 0 ; i < sz ; i++)
  {
    DeleteColumn(0);
  }
}
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EDITLIST_H__834127E6_9297_11D5_8AFA_DAC6E5A1C54B__INCLUDED_)
