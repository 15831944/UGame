#if !defined(AFX_SUPERGATETRANSFERDLG_H__5D4EB49B_02CE_4ACA_A4B7_E6551F6BD3ED__INCLUDED_)
#define AFX_SUPERGATETRANSFERDLG_H__5D4EB49B_02CE_4ACA_A4B7_E6551F6BD3ED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// supergatetransferdlg.h : header file
//

struct STAR_ITEM_T{
  uchar index;
  PlaniPos pos;
  STAR_ITEM_T(uchar i , PlaniPos p) : index(i) , pos(p){}
};

/////////////////////////////////////////////////////////////////////////////
// CSuperGateTransferDlg dialog

class CSuperGateTransferDlg : public CDialog
{
// Construction
public:
	CSuperGateTransferDlg(std::vector<STAR_ITEM_T>& s , CWnd* pParent = NULL);   // standard constructor
  std::vector<STAR_ITEM_T>& stars_;
  uchar m_selected_index_;

// Dialog Data
	//{{AFX_DATA(CSuperGateTransferDlg)
	enum { IDD = IDD_DLG_TRANSFER_BY_SUPERGATE };
	CListBox	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSuperGateTransferDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSuperGateTransferDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUPERGATETRANSFERDLG_H__5D4EB49B_02CE_4ACA_A4B7_E6551F6BD3ED__INCLUDED_)
