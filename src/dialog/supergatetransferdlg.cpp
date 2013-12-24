// supergatetransferdlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\XGame\xgame.h"
#include "supergatetransferdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSuperGateTransferDlg dialog


CSuperGateTransferDlg::CSuperGateTransferDlg(std::vector<STAR_ITEM_T>&s , CWnd* pParent /*=NULL*/)
	: CDialog(CSuperGateTransferDlg::IDD, pParent) , stars_(s)
{
	//{{AFX_DATA_INIT(CSuperGateTransferDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_selected_index_ = 0xff;
}


void CSuperGateTransferDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSuperGateTransferDlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP 
}


BEGIN_MESSAGE_MAP(CSuperGateTransferDlg, CDialog)
	//{{AFX_MSG_MAP(CSuperGateTransferDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSuperGateTransferDlg message handlers

BOOL CSuperGateTransferDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
  CString info;
  TCHAR buf[40];
  int cnt = 1;
  for(int i = 0 ; i < stars_.size() ; ++i)
  {
    STAR_ITEM_T item = stars_[i];
    assert(item.index < STAR_MAX);
    if(item.index == HOMESTAR)
    {
      info.Format("Ö÷ÐÇ   ¡¾%s¡¿" , item.pos.ToCString(buf));
    }
    else
    {
      info.Format("Ö³ÃñÐÇ%d¡¾%s¡¿" , cnt , item.pos.ToCString(buf));
      ++cnt;
    }
    m_list.AddString(info);
    m_list.SetItemData(i , item.index);
  }	
  GetDlgItem(IDOK)->EnableWindow(stars_.size() > 0);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSuperGateTransferDlg::OnOK() 
{
	UpdateData(TRUE);
  int sel = m_list.GetCurSel();	
  if(sel >= 0 && sel < stars_.size())
   m_selected_index_ = m_list.GetItemData(sel);
  else
   m_selected_index_ = 0xff;
	CDialog::OnOK();
}
