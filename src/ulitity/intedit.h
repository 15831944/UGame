#if !defined(AFX_INTEDIT_H__DE471E84_CDC7_4FC0_86AC_FE8A4D6254CC__INCLUDED_)
#define AFX_INTEDIT_H__DE471E84_CDC7_4FC0_86AC_FE8A4D6254CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// intedit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIntEdit window
#define WM_INTEDIT_CHANGED WM_USER + 36

class CIntEdit : public CEdit
{
private:
  UINT min_value_;
  UINT max_value_;
  CWnd* pParent_;
  UINT  controlID;

public:
	CIntEdit(UINT id = 0 , CWnd* p = NULL);

// Attributes
public:
  void SetRange(UINT min_data , UINT max_data)
  {
    if(min_data > max_data)
      swap(min_data , max_data);
    min_value_ = min_data; 
    max_value_ = max_data;
  }
  UINT GetData() const;
  void SetData(UINT d);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIntEdit)
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(CIntEdit)
	afx_msg void OnChange();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTEDIT_H__DE471E84_CDC7_4FC0_86AC_FE8A4D6254CC__INCLUDED_)
