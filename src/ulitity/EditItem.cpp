#include "stdafx.h"
#include "EditItem.h"
#include "EditList.h"


CEditItem::CEditItem(int nItem, int nSubItem, CString &sContent , BOOL num , CEditList* parent /*= NULL*/ ,  int limitnum , CString def_num)
:m_limit_number(limitnum)
{
  bNumOnly = num;
	m_nItem = nItem;
	m_nSubItem = nSubItem;
	m_sContent = sContent;
	m_bVK_ESCAPE = FALSE; 
  pParentListCtrl = parent;
  max_number = def_num;
}

CEditItem::~CEditItem()
{
}


BEGIN_MESSAGE_MAP(CEditItem, CEdit)
	//{{AFX_MSG_MAP(CEditItem)
	ON_WM_CHAR()
	ON_WM_NCDESTROY()
	ON_WM_KILLFOCUS()
	ON_WM_CREATE()
	ON_CONTROL_REFLECT(EN_SETFOCUS, OnSetfocus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL CEditItem::PreTranslateMessage(MSG* pMsg) 
{
	if( pMsg->message == WM_KEYDOWN )	
	{		
		if( pMsg->wParam == VK_RETURN || 
			pMsg->wParam == VK_DELETE ||
			pMsg->wParam == VK_ESCAPE ||
			GetKeyState( VK_CONTROL) < 0)
		{			
			::TranslateMessage(pMsg);
			::DispatchMessage(pMsg);
			return 1;
		}	
	}
  //disable RButton menu
  if( pMsg->message == WM_RBUTTONDOWN )	
	{		
		return 1;
	}
  if( pMsg->message == WM_RBUTTONUP )	
	{		
		return 1;
	}

	return CEdit::PreTranslateMessage(pMsg);
}

void CEditItem::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
  if( nChar == VK_ESCAPE ||	nChar == VK_RETURN)
  {    
		if( nChar == VK_ESCAPE)
			m_bVK_ESCAPE = 1;		
		GetParent()->SetFocus();
		return;	
	}

  if(bNumOnly && (!IsNumber(nChar)) )
    return;

  //buffering
  CString pre_str;	
	GetWindowText(pre_str);	

  //change
	CEdit::OnChar(nChar, nRepCnt, nFlags);	

  //compare with max number
	CString str;	
	GetWindowText(str);	
  if(atoi(str) > atoi(max_number)){
    //don't change
    SetWindowText(pre_str);
    return;
  }

	CWindowDC dc(this);
	CFont *pFont = GetParent()->GetFont();
	CFont *pFontDC = dc.SelectObject(pFont);
	CSize size = dc.GetTextExtent(str);	
	dc.SelectObject(pFontDC);
	size.cx += 5;
	CRect rect, rcParent;	
	GetClientRect(&rect);
	GetParent()->GetClientRect(&rcParent);
	ClientToScreen(&rect);
	GetParent()->ScreenToClient(&rect);
	if(size.cx > rect.Width())	
	{
		if(size.cx + rect.left < rcParent.right)
			rect.right = rect.left + size.cx;		
		else			
			rect.right = rcParent.right;
		MoveWindow(&rect);	
	}	
}

void CEditItem::OnNcDestroy() 
{
	CEdit::OnNcDestroy();	
	delete this;
}

void CEditItem::OnKillFocus(CWnd* pNewWnd) 
{
	CEdit::OnKillFocus(pNewWnd);	
	CString str;	
  GetWindowText(str);

  //clear start "0" and spaces
  str.TrimLeft();
  if(str.GetLength() > 1)
    str.TrimLeft("0");

  str.TrimRight();  
  if(atoi(str) > atoi(max_number)){
    //don't change
    SetWindowText(max_number);
    str = max_number;
  }

  if(atoi(str) == 0 )
  {
    str = "";
  }

	// Send Notification to parent of ListView ctrl	
	LV_DISPINFO lvDispInfo;
	lvDispInfo.hdr.hwndFrom = GetParent()->m_hWnd;
	lvDispInfo.hdr.idFrom = GetDlgCtrlID();	
	lvDispInfo.hdr.code = LVN_ENDLABELEDIT;
	lvDispInfo.item.mask = LVIF_TEXT;	
	lvDispInfo.item.iItem = m_nItem;
	lvDispInfo.item.iSubItem = m_nSubItem;
	lvDispInfo.item.pszText = m_bVK_ESCAPE ? NULL : LPTSTR((LPCTSTR)str);
	lvDispInfo.item.cchTextMax = str.GetLength();
  if(!m_bVK_ESCAPE){
    //change item text
	  GetParent()->GetParent()->SendMessage( WM_NOTIFY, GetParent()->GetDlgCtrlID(),(LPARAM)&lvDispInfo);
    //notify
    pParentListCtrl->Notify_Text_Changed();
  }
  ASSERT(pParentListCtrl != NULL);
	DestroyWindow();	
}

int CEditItem::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEdit::OnCreate(lpCreateStruct) == -1)		
		return -1;	
  
	CFont* font = GetParent()->GetFont();
	SetFont(font);
 	SetWindowText(m_sContent);
	SetFocus();	
	SetSel(0, -1);
	return 0;
}

void CEditItem::OnSetfocus() 
{
  ASSERT(pParentListCtrl != NULL);
}
