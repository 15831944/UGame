#ifndef WBL_PAGEICON_H__INCLUDED_
#define WBL_PAGEICON_H__INCLUDED_

class CPageIcon : public CPropertyPage
{
private:
	DECLARE_DYNAMIC(CPageIcon)

public:
  CPageIcon(UINT nIDTemplate, UINT nIconID);
	~CPageIcon();

// Dialog Data
	//{{AFX_DATA(CPageIcon)
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageIcon)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageIcon)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Members
private:
  UINT m_nIconID;
  HICON m_hIcon;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // WBL_PAGEICON_H__INCLUDED_
