// TreeItem.cpp : implementation file
//

#include "stdafx.h"
#include "TreeItem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeItem

CTreeItem::CTreeItem(int nItem, int nSubItem )
{

}

CTreeItem::~CTreeItem()
{
 
}


BEGIN_MESSAGE_MAP(CTreeItem, CTreeCtrl)
	//{{AFX_MSG_MAP(CTreeItem)
	ON_WM_KILLFOCUS()
	ON_WM_NCDESTROY()
	ON_WM_CREATE()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeItem message handlers

void CTreeItem::OnKillFocus(CWnd* pNewWnd) 
{
  
}

void CTreeItem::OnNcDestroy() 
{
	CTreeCtrl::OnNcDestroy();	
	delete this;
	
}

int CTreeItem::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

void CTreeItem::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
  
}


BOOL CTreeItem::PreTranslateMessage(MSG* pMsg) 
{
  if( pMsg->message == WM_KEYDOWN )	
  {		
    if(pMsg->wParam == VK_ESCAPE)	
    {
      GetParent()->SetFocus();
      return 1;
    }	
  }		
	
	return CTreeCtrl::PreTranslateMessage(pMsg);
}
