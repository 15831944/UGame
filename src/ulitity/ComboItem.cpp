// ComboItem.cpp : implementation file
//

#include "stdafx.h"
#include "ComboItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CComboItem::CComboItem( int nItem, int nSubItem , const vector<CString>& lists)
:m_nSubItem(nSubItem) , m_nItem(nItem)
{
  m_bVK_ESCAPE = FALSE;
  for(int i = 0 ; i < lists.size() ; ++i)
  {
    m_sList.push_back(lists[i]);
  }
}

CComboItem::~CComboItem()
{
}


BEGIN_MESSAGE_MAP(CComboItem, CComboBox)
	//{{AFX_MSG_MAP(CComboItem)
	ON_WM_NCDESTROY()
	ON_WM_KILLFOCUS()
	ON_CONTROL_REFLECT(CBN_CLOSEUP, OnCloseup)
	ON_WM_CREATE()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboItem message handlers

BOOL CComboItem::PreTranslateMessage(MSG* pMsg) 
{
  if( pMsg->message == WM_KEYDOWN )	
  {		
    if(pMsg->wParam == VK_ESCAPE)
    {
      m_bVK_ESCAPE = TRUE;
      GetParent()->SetFocus();
      return 1;
    }	
  }		
  return CComboBox::PreTranslateMessage(pMsg);
}

void CComboItem::OnNcDestroy() 
{
	CComboBox::OnNcDestroy();
	delete this;	
}

void CComboItem::OnKillFocus(CWnd* pNewWnd) 
{
	int nIndex = GetCurSel();
	CComboBox::OnKillFocus(pNewWnd);
	CString str;	
	GetWindowText(str);
	// Send Notification to parent of ListView ctrl	
	LV_DISPINFO lvDispinfo;
	lvDispinfo.hdr.hwndFrom = GetParent()->m_hWnd;
	lvDispinfo.hdr.idFrom = GetDlgCtrlID();//that's us
	lvDispinfo.hdr.code = LVN_ENDLABELEDIT;
	lvDispinfo.item.mask = LVIF_TEXT | LVIF_PARAM;	
	lvDispinfo.item.iItem = m_nItem;
	lvDispinfo.item.iSubItem = m_nSubItem;
	lvDispinfo.item.pszText = m_bVK_ESCAPE ? NULL : LPTSTR((LPCTSTR)str);
	lvDispinfo.item.cchTextMax = str.GetLength();
	lvDispinfo.item.lParam = GetItemData(GetCurSel());
	if(!m_bVK_ESCAPE && nIndex != CB_ERR)
		GetParent()->GetParent()->SendMessage(WM_NOTIFY,GetParent()->GetDlgCtrlID(),(LPARAM)&lvDispinfo);
	PostMessage(WM_CLOSE);
}

void CComboItem::OnCloseup() 
{
	GetParent()->SetFocus();	
}

int CComboItem::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CComboBox::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CFont* font = GetParent()->GetFont();	
	SetFont(font);
	//add the items from CStringlist
	for(int i = 0 ; i < m_sList.size() ; i++)
		AddString((LPCTSTR)(m_sList[i]));	
	SetFocus();	
	return 0;
}

void CComboItem::OnSize(UINT nType, int cx, int cy) 
{
	CComboBox::OnSize(nType, cx, cy);		
}
