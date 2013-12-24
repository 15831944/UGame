// TipWarpper.cpp: implementation of the TipWarpper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "xgame.h"
#include "TipWarpper.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TipWarpper::TipWarpper()
{
  dlg_ = new CFinishTipDlg;
  dlg_->Create(IDD_JOB_FINISH_TIP);
}

TipWarpper::~TipWarpper()
{
  delete dlg_;
  dlg_ = NULL;
}

void TipWarpper::ShowTip(const CString& info , int delay)
{
  dlg_->SetTipText(info);
  dlg_->Show(delay);
}

TipWarpper& TipWarpper::Instance()
{
  static TipWarpper self;
  return self;
}