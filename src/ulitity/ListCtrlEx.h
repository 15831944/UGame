#ifndef _LISTCTRL_PROGRESS_H_
#define _LISTCTRL_PROGRESS_H_

#include <AFXTEMPL.H>

// CListCtrlEx
#define IDC_PROGRESS_LIST WM_USER

class CListCtrlEx : public CListCtrl
{
private:
  DECLARE_DYNAMIC(CListCtrlEx)
	// the array of the Progress Controls in the list control
	CArray<CProgressCtrl* , CProgressCtrl* > m_ProgressList;

	// the column which should contain the progress bars
	int m_ProgressColumn;
public:
	CListCtrlEx();
	virtual ~CListCtrlEx();
  void DeleteItem(int nItem);
  void DeleteAllItems();
	// initialize the column containing the bars
	void InitProgressColumn(int ColNum=0);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};

#endif
