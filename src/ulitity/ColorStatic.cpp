// ColorStatic.cpp : implementation file
//

#include "stdafx.h"
#include "XGame.h"
#include "ColorStatic.h"

CColorStatic::CColorStatic()
{
	m_TextColor=RGB(0,0,0);
}

CColorStatic::~CColorStatic()
{
}


BEGIN_MESSAGE_MAP(CColorStatic, CStatic)
	//{{AFX_MSG_MAP(CColorStatic)
	ON_WM_CREATE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int CColorStatic::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	return 0;
}

void CColorStatic::OnPaint() 
{
	CPaintDC dc(this); 
	CRect rect;
	GetClientRect(&rect);
	dc.SetBkMode(TRANSPARENT);

  //fill back ground with Back color
  CBrush br(m_BackColor);
  dc.FillRect(rect , &br); 

  CFont Font;
  LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 12;
  lf.lfWeight = FW_NORMAL;
	strcpy(lf.lfFaceName, "ËÎÌו");
	Font.CreateFontIndirect(&lf);
	CFont *pOldFont = dc.SelectObject(&Font);

  dc.SetTextColor(m_TextColor);   
	dc.DrawText(m_strCaption,&rect,DT_CENTER);
	dc.SelectObject(pOldFont);
}

void CColorStatic::Create(CString strCaption, COLORREF BackColor)
{	
  
}

void CColorStatic::SetCaption(CString strCaption)
{
	m_strCaption = strCaption;
  Invalidate();
}

void CColorStatic::SetBackColor(COLORREF BackColor)
{
	m_BackColor=BackColor;
}

void CColorStatic::SetTextColor(COLORREF TextColor)
{
	m_TextColor=TextColor;
}
