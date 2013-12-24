#if !defined(AFX_XGAME_H__010E79E2_6031_44AD_AF87_F3C31AC9E70B__INCLUDED_)
#define AFX_XGAME_H__010E79E2_6031_44AD_AF87_F3C31AC9E70B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CXGameApp:
// See XGame.cpp for the implementation of this class
//

#include "GameFileReader.h"
#include "GameDataRecorder.h"

class CXGameApp : public CWinApp
{
private:
  AccountManager account_manager_;
  GameData       data_;

public:
	CXGameApp();
  AccountManager& GetAccountManager() {return account_manager_;}
  void Logoff(bool isDisplayerr = true);
  void SaveAccountData(bool isDisplayerr = true);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXGameApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CXGameApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XGAME_H__010E79E2_6031_44AD_AF87_F3C31AC9E70B__INCLUDED_)
