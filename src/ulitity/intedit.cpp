// intedit.cpp : implementation file
//

#include "stdafx.h"
#include "..\XGame\xgame.h"
#include "intedit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CIntEdit

CIntEdit::CIntEdit(UINT id , CWnd* p) : min_value_(0L) , max_value_(0L) , pParent_(p) , controlID(id)
{
}


BEGIN_MESSAGE_MAP(CIntEdit, CEdit)
	//{{AFX_MSG_MAP(CIntEdit)
	ON_CONTROL_REFLECT(EN_CHANGE, OnChange)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIntEdit message handlers

void CIntEdit::OnChange() 
{
  CString data;
  GetWindowText(data);
  UINT d = (UINT)(atoi(data));
  //less min value
  if(d < min_value_)
  {
    data.Format("%d" , min_value_);
    SetWindowText(data);
    return;
  }
  //greater max value
  if(d > max_value_)
  {
    data.Format("%d" , max_value_);
    SetWindowText(data);
    return;
  }  
  if(pParent_ != 0)
  {
    pParent_->PostMessage(WM_INTEDIT_CHANGED , controlID , 0); 
  }  
}

void CIntEdit::SetData(UINT d)
{
  CString data; 
  data.Format("%d" , d);
  SetWindowText(data);
}

UINT CIntEdit::GetData() const
{
  CString data; 
  GetWindowText(data);
  return atoi(data);
}

void CIntEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{  
	if ( ((nChar >= '0' && nChar <= '9') || (nChar == VK_BACK)) == false)
  {
    return;
  }	
  CString data; 
  GetWindowText(data);
  int s , e;
  this->GetSel(s , e);
  if(s == 0 && e == 0 && nChar == '0' && data.IsEmpty() == FALSE)
  {
    return;
  }
	CEdit::OnChar(nChar, nRepCnt, nFlags);
}
