// TipWarpper.h: interface for the TipWarpper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIPWARPPER_H__BA78ADC4_4880_4062_A184_B378967396A8__INCLUDED_)
#define AFX_TIPWARPPER_H__BA78ADC4_4880_4062_A184_B378967396A8__INCLUDED_

#include "finishtipdlg.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class TipWarpper  
{
private:
  CFinishTipDlg* dlg_;

public:
  ~TipWarpper();

private:
	TipWarpper();
  TipWarpper(const TipWarpper&);
  TipWarpper& operator=(const TipWarpper&);

public:
  void ShowTip(const CString& info , int delay = 1);
  static TipWarpper& Instance();

};

#endif // !defined(AFX_TIPWARPPER_H__BA78ADC4_4880_4062_A184_B378967396A8__INCLUDED_)
