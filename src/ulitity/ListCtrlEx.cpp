#include "stdafx.h"
#include "ListCtrlEx.h"

IMPLEMENT_DYNAMIC(CListCtrlEx, CListCtrl)

CListCtrlEx::CListCtrlEx() : m_ProgressColumn(0)
{
}

CListCtrlEx::~CListCtrlEx()
{
  int Count = m_ProgressList.GetSize();
  for (int i = 0; i < Count; i++)
  {
    CProgressCtrl* pCtrl = m_ProgressList.GetAt(0);
    pCtrl->DestroyWindow();
    delete pCtrl;
    m_ProgressList.RemoveAt(0);
  }
}

BEGIN_MESSAGE_MAP(CListCtrlEx, CListCtrl)
ON_WM_PAINT()
END_MESSAGE_MAP()

void CListCtrlEx::OnPaint()
{
  int i;
  int Top = GetTopIndex();
  int Total = GetItemCount();
  int PerPage = GetCountPerPage();
  int Last = ((Top+PerPage) > Total)? Total : Top+PerPage;
  int Count = m_ProgressList.GetSize();
  CProgressCtrl* pCtrl;
  if ((Last-Top) > Count)
  {
    for (i = Count; i < Last-Top; i++)
    {
      pCtrl = new CProgressCtrl();
      CRect rt(1,1,1,1);
      pCtrl->Create(NULL, rt, this, IDC_PROGRESS_LIST+i);
      m_ProgressList.Add(pCtrl);
    }
  }
  
  CHeaderCtrl* pHeader = GetHeaderCtrl();
  for (i = Top; i < Last; i++)
  {
    CRect ColRt;
    pHeader->GetItemRect(m_ProgressColumn, &ColRt);
    
    CRect rt;
    GetItemRect(i, &rt, LVIR_LABEL);
    rt.top += 1;
    rt.bottom -= 1;
    rt.left += ColRt.left;
    rt.right = rt.left + ColRt.Width() - 4;
    
    pCtrl = m_ProgressList.GetAt(i-Top);
    CString strPercent = GetItemText(i, m_ProgressColumn);
    int nPercent = atoi(strPercent);
    pCtrl->SetPos(nPercent);
    pCtrl->MoveWindow(&rt);
    pCtrl->ShowWindow(SW_SHOWNORMAL);
  }
  CListCtrl::OnPaint();
}

void CListCtrlEx::InitProgressColumn(int ColNum/*=0*/)
{
  m_ProgressColumn=ColNum;
}

void CListCtrlEx::DeleteItem(int nItem)
{
  if(nItem >= GetItemCount())
    return;
  CProgressCtrl* pCtrl = m_ProgressList.GetAt(nItem);
  pCtrl->DestroyWindow();
  delete pCtrl;
  m_ProgressList.RemoveAt(nItem);
  CListCtrl::DeleteItem(nItem);
}

void CListCtrlEx::DeleteAllItems()
{
  int Count = m_ProgressList.GetSize();
  for (int i = 0; i < Count; i++)
  {
    CProgressCtrl* pCtrl = m_ProgressList.GetAt(0);
    pCtrl->DestroyWindow();
    delete pCtrl;
    m_ProgressList.RemoveAt(0);
  }
  CListCtrl::DeleteAllItems();
}