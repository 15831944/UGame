#if !defined(AFX_TRADECENTERDLG_H__947B8405_F4C6_46D0_BA38_D08206AFA0D4__INCLUDED_)
#define AFX_TRADECENTERDLG_H__947B8405_F4C6_46D0_BA38_D08206AFA0D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// tradecenterdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTradeCenterDlg dialog
class GameData;
class CPageCommander;

enum{
  TRADE_T_OUT,
  TRADE_T_IN,
};

class CTradeCenterDlg : public CDialog
{
private:
  GameData* data_;
  CPageCommander* pParent_;

public:
	CTradeCenterDlg(GameData* acc , CWnd* pParent);   // standard constructor
  bool is_traded;

// Dialog Data
	//{{AFX_DATA(CTradeCenterDlg)
	enum { IDD = IDD_DIALOG_TRADE_CENTER };
	UINT	m_crystal;
	UINT	m_diop;
	UINT	m_metal;
	CString	m_trade_percent;
	UINT	m_trade_money;
	int		m_trade_type;
	UINT	m_avai_crystal;
	UINT	m_avai_metal;
	UINT	m_avai_diop;
	UINT	m_trade_poundage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTradeCenterDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTradeCenterDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnMetalMax();
	afx_msg void OnBtnCryMax();
	afx_msg void OnBtnDiopMax();
	afx_msg void OnChangeEditM();
	afx_msg void OnChangeEditD();
	afx_msg void OnChangeEditC();
	afx_msg void OnRadio2();
	afx_msg void OnRadio1();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
  void UpdateTradeMoney();
  void UpdateCtrls();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRADECENTERDLG_H__947B8405_F4C6_46D0_BA38_D08206AFA0D4__INCLUDED_)
