#if !defined(_PAGE_INFORMATION_HEADER_)
#define _PAGE_INFORMATION_HEADER_

#include "ObserverBase.h"
#include "HTMLListCtrl.h"
#include "PageIcon.h"

enum{
  DELETE_FLAG,
  DELETE_NO_FLAG,
  DELETE_ALL
};

enum{
  REPORT_T_SPY,
  REPORT_T_WAR,
  REPORT_T_RECYCLE,
  REPORT_T_FLEET_BACK,
};

class CPageInformation : public CPageIcon , public ObserverBase
{
private:
  CHTMLListCtrl m_list;
  ulong old_info_number_;  
  struct Item_Date{
  int type;
  int target_star_index;
  char report_file[256];    
  Item_Date()
  {
    type = TASK_T_ATTACK;
    target_star_index = 0;
    memset(report_file , '\0' , 128);
  }
};

public:
	CPageInformation(UINT iconID = NULL , CWnd* pParent = NULL);   // standard constructor
  void ReportSpyInfo(const Spy_info& spy);
  void ReportWarInfo(const War_info& war);
  void ReportFleetReach(const COMMAND_TASK& task);
  void ReportRecycleInfo(const COMMAND_TASK& task);
  void ReportTransferInfo(const COMMAND_TASK& task);
  void ReportColonyInfo(const COMMAND_TASK& task , bool bSuccess);

  void Notify_Exit();

// Dialog Data
	//{{AFX_DATA(CPageInformation)
	enum { IDD = IDD_DIALOG_INFOMATION };
	int		m_op_option;
	BOOL	m_bDeleteReporter;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageInformation)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageInformation)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnOk();
	afx_msg void OnBtnCopy();
	//}}AFX_MSG
  afx_msg void OnMyList_SelectionChanged(NMHDR* pNMHDR, LRESULT*);
  afx_msg void OnMyList_LButtonDClick(NMHDR* pNMHDR, LRESULT*);
  afx_msg void OnMyList_ItemDelete(NMHDR* pNMHDR, LRESULT*);	
  afx_msg void OnMyList_ItemDeleteAll(NMHDR* pNMHDR, LRESULT*);	
DECLARE_MESSAGE_MAP()

private:
  void Initialize();
  void DisplayInfoNumber();
  void DeleteInfo(int mode);
  CString FillString(const CString& oristr , int length);
  UINT GetFleetShipsNumber(const FLEET& ships);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_PAGE_INFORMATION_HEADER_)
