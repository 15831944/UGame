// finishtipdlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\XGame\xgame.h"
#include "finishtipdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFinishTipDlg dialog


CFinishTipDlg::CFinishTipDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFinishTipDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFinishTipDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFinishTipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFinishTipDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFinishTipDlg, CDialog)
	//{{AFX_MSG_MAP(CFinishTipDlg)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFinishTipDlg message handlers

void CFinishTipDlg::OnTimer(UINT nIDEvent) 
{
  KillTimer(TIMER_FOR_TIPDLG);
  AnimateWindow(GetSafeHwnd(), 1000 , AW_HIDE | AW_VER_POSITIVE);	
  ShowWindow(SW_HIDE);
	CDialog::OnTimer(nIDEvent);
}

BOOL CFinishTipDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFinishTipDlg::OnDestroy() 
{
	CDialog::OnDestroy();
}

void CFinishTipDlg::OnClose() 
{
	CDialog::OnClose();
}

void CFinishTipDlg::SetTipText(const CString& info)
{
  GetDlgItem(IDC_STA_INFO)->SetWindowText(info);
}

void CFinishTipDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	AnimateWindow(GetSafeHwnd(), 800 , AW_HIDE | AW_VER_POSITIVE);
	KillTimer(TIMER_FOR_TIPDLG);
  ShowWindow(SW_HIDE);	
	CDialog::OnLButtonDown(nFlags, point);
}

void CFinishTipDlg::Show(int delay)
{  
  int nFullWidth=GetSystemMetrics(SM_CXSCREEN); 
	int nFullHeight=GetSystemMetrics(SM_CYSCREEN); 
  int w = 150;
  int h = 93;
	this->SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
	this->MoveWindow(nFullWidth - w , nFullHeight - h , w , h);
	AnimateWindow(this->GetSafeHwnd(), 800 , AW_VER_NEGATIVE);	
  ShowWindow(SW_SHOW);
	SetTimer(TIMER_FOR_TIPDLG , delay * 1000 , NULL);	
}