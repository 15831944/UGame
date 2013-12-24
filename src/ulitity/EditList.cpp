// EditList.cpp : implementation file
//

#include "stdafx.h"
#include "ComboItem.h"
#include "EditItem.h"
#include "EditList.h"
#include "TreeItem.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEditList


CEditList::CEditList(CWnd* bar , UINT IDimage /*=NULL*/  , BOOL bMenu /*= TRUE*/ )
: pParent(bar)
{
	m_fGetType = NULL;
  m_limit_number = 10;  
  ID_EDIT  = 0x1000;
  ID_COMBO = 0x2000;
}

CEditList::~CEditList()
{	
}

void CEditList::Initialize()
{
  ModifyStyle(NULL , LVS_REPORT | LVS_SINGLESEL | WS_BORDER);
	SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);	
}


BEGIN_MESSAGE_MAP(CEditList, CToolTipListCtrl)
//{{AFX_MSG_MAP(CEditList)
ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, OnEndlabeledit)
ON_NOTIFY_REFLECT(NM_CLICK, OnClick)
ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CEditList::OnClick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if( GetFocus() != this) 
		SetFocus();	
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;	
	if ( m_fGetType && m_fGetType( pNMListView->iSubItem ) == eCombo )
		ComboItem(pNMListView->iItem, pNMListView->iSubItem);
	else if ( m_fGetType && m_fGetType( pNMListView->iSubItem ) == eEdit && pNMListView->iItem != BOAT_SUNPOWER_PLANET)
		EditItem (pNMListView->iItem, pNMListView->iSubItem);
	else if ( m_fGetType && m_fGetType( pNMListView->iSubItem ) == eTree )
		TreeItem (pNMListView->iItem, pNMListView->iSubItem);	
	*pResult = 0;
}

CEdit *CEditList::EditItem(int nItem, int nSubItem)
{
  //if pre item is 0, can't edit
  CString pre_item_str = GetItemText(nItem, nSubItem - 1);
  if(atoi(pre_item_str) <= 0)
    return NULL;

	CRect rect;
	int offset = 0;
	if(!EnsureVisible(nItem, TRUE))
	{ 
		return NULL;	
	}	
	GetSubItemRect(nItem, nSubItem, LVIR_BOUNDS, rect);
	// Now scroll if we need to expose the column
	CRect rcClient;
	GetClientRect(rcClient);
	if( offset + rect.left < 0 || offset + rect.left > rcClient.right )
	{
		CSize size(offset + rect.left,0);		
		Scroll(size);
		rect.left -= size.cx;
	}
  rect.top  -= 3;
	rect.left += offset;	
	rect.right = rect.left + GetColumnWidth(nSubItem);
	if(rect.right > rcClient.right) 
		rect.right = rcClient.right;
	
	// Get Column alignment	
	LV_COLUMN lvcol;
	lvcol.mask = LVCF_FMT;
	GetColumn(nSubItem, &lvcol);
	
  //style
	DWORD dwStyle;
	if((lvcol.fmt & LVCFMT_JUSTIFYMASK) == LVCFMT_LEFT)
		dwStyle = ES_LEFT;
	else if((lvcol.fmt & LVCFMT_JUSTIFYMASK) == LVCFMT_RIGHT)
		dwStyle = ES_RIGHT;
	else 
		dwStyle = ES_CENTER;		
	dwStyle |= WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | WS_BORDER;

  //create
	CEditItem *pEdit = new CEditItem(nItem, nSubItem, GetItemText(nItem, nSubItem) , true  , this , m_limit_number , pre_item_str);
	pEdit->Create(dwStyle, rect, this, ID_EDIT++);	
  pEdit->SetLimitText(m_limit_number);
	return pEdit;
}

void CEditList::OnEndlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO *plvDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM *plvItem = &plvDispInfo->item;
	
	if( plvItem->iItem != -1 &&   // valid item
		plvItem->pszText )		      // valid text
	{
    CString preContent = GetItemText(plvItem->iItem, plvItem->iSubItem);
		SetItemText( plvItem->iItem, plvItem->iSubItem, plvItem->pszText);
	}	
	*pResult = 0;	
}

CComboBox * CEditList::ComboItem(int nItem, int nSubItem)
{  
	CString strFind = GetItemText(nItem, nSubItem);
	//basic code start
	CRect rect;
	int offset = 0;
	// Make sure that the item is visible
	if( !EnsureVisible(nItem, TRUE)) 
		return NULL;
	
	GetSubItemRect(nItem, nSubItem, LVIR_BOUNDS, rect);
	// Now scroll if we need to expose the column
	CRect rcClient;
	GetClientRect(rcClient);
	if( offset + rect.left < 0 || offset + rect.left > rcClient.right )
	{
		CSize size;
		size.cx = offset + rect.left;
		size.cy = 0;
		Scroll(size);
		rect.left -= size.cx;
	}
	
	rect.left += offset;	
	rect.right = rect.left + GetColumnWidth(nSubItem);
	if(rect.right > rcClient.right) 
		rect.right = rcClient.right;
	//basic code end
	
	rect.bottom += 30 * rect.Height();//dropdown area
	
	DWORD dwStyle =  WS_CHILD | WS_VISIBLE | WS_VSCROLL |CBS_DROPDOWNLIST | CBS_DISABLENOSCROLL;
  vector<CString> tmp;
  tmp.push_back("¼äµý");
  tmp.push_back("¹¥»÷");
	CComboBox *pList = new CComboItem(nItem , nSubItem , tmp);	
	pList->Create(dwStyle, rect, this, ID_COMBO++);
	pList->ModifyStyleEx(0,WS_EX_CLIENTEDGE);//can we tell at all	
	pList->ShowDropDown();
	pList->SelectString(-1, strFind.GetBuffer(1));
	// The returned pointer should not be saved
	return pList;
}

CTreeCtrl* CEditList::TreeItem( int nItem, int nSubItem)
{
#define IDC_TREEINLISTVIEW 0x1236
	CString strFind = GetItemText(nItem, nSubItem);
	//basic code start
	CRect rect;
	int offset = 0;
	// Make sure that the item is visible
	if( !EnsureVisible(nItem, TRUE)) 
		return NULL;
	
	GetSubItemRect(nItem, nSubItem, LVIR_BOUNDS, rect);
	// Now scroll if we need to expose the column
	CRect rcClient;
	GetClientRect(rcClient);
	if( offset + rect.left < 0 || offset + rect.left > rcClient.right )
	{
		CSize size;
		size.cx = offset + rect.left;
		size.cy = 0;
		Scroll(size);
		rect.left -= size.cx;
	}
	rect.left += offset;	
	rect.right = rect.left + GetColumnWidth(nSubItem);
	if(rect.right > rcClient.right) 
		rect.right = rcClient.right;
	//basic code end
	rect.bottom += 15 * rect.Height();//dropdown area
	DWORD dwStyle = WS_BORDER |  WS_CHILD| WS_VISIBLE | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT ;
	CTreeItem *pTree = new CTreeItem(nItem , nSubItem );
  
	pTree->Create(dwStyle, rect, this, IDC_TREEINLISTVIEW);
	pTree->ModifyStyleEx(0,WS_EX_CLIENTEDGE);//can we tell at all	
	return pTree;
}

void CEditList::UpdateIndex()
{
	int cnt = GetItemCount();
	CString str;
	for(int i = 0 ; i < cnt ; i++)
	{
		str.Format("%d" , i);
		SetItemText(i , 0 , str);
	}
}

void CEditList::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
}

BOOL CEditList::PreTranslateMessage(MSG* pMsg) 
{
  return CToolTipListCtrl::PreTranslateMessage(pMsg);
}

void CEditList::Notify_Text_Changed()
{
  ::SendMessage(pParent->GetSafeHwnd() , WM_LISTCTRL_TEXT_CHANGED , 0 , 0);
}

BOOL CEditList::DeleteAllItems()
{
  return CToolTipListCtrl::DeleteAllItems();
}

BOOL CEditList::DeleteItem( int nItem )
{
  return CToolTipListCtrl::DeleteItem(nItem);
}