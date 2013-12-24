#include "stdafx.h"
#include "XGame.h"
#include "XGameDlg.h"
#include "Logindlg.h"
#include "GameLogger.h"

BEGIN_MESSAGE_MAP(CXGameApp, CWinApp)
	//{{AFX_MSG_MAP(CXGameApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

CXGameApp::CXGameApp()
{
  data_.SetAccountPtr(&account_manager_);
}

CXGameApp theApp;
extern float _speed_adjust_;

BOOL CXGameApp::InitInstance()
{
#ifdef USING_SKINPLUSPLUS
  //use skin plus plus 
  InitializeSkin(_T(".\\skin\\Minimized.ssk"));
#else  
  //use gui color
  SetDialogBkColor(RGB(55 , 77 , 112) , RGB(255 , 255 , 255));
#endif
  InitRand();
  AfxEnableControlContainer();
  //login
  CLoginDlg login(&account_manager_);
  if(IDCANCEL == login.DoModal())
  {
    //exit
    return FALSE;
  }
  //load game data
  if(!data_.Load())
  {
    AfxMessageBox("读取帐号档案失败，程序退出！");
    return FALSE;
  }

  //update speed adjust
  _speed_adjust_ = data_.GAME_SPEED();

  //init logger
  CGameLogger::Instance().Init(data_.GetLoginedAccountName());  

  //log
  CGameLogger::Instance().Log("load game data successfully...ugame login.");

#ifdef _AFXDLL
	Enable3dControls();			  // Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

  CXGameDlg dlg(&data_);
  m_pMainWnd = &dlg;    
  dlg.DoModal();
  return FALSE;
}

int CXGameApp::ExitInstance() 
{
#ifdef USING_SKINPLUSPLUS
  ExitSkin();
#endif
	return CWinApp::ExitInstance();
}

void CXGameApp::Logoff(bool isDisplayerr)
{
  //exit&Save account data to file
  while(!data_.Save())
  {
    if(IDNO == ::MessageBox(NULL , "保存帐号档案失败，需要重试吗？" , "警告" , MB_YESNO | MB_ICONWARNING))
    {
      break;
    }
  }
  //log
  CGameLogger::Instance().Log("save game data successfully...");
}

void CXGameApp::SaveAccountData(bool isDisplayerr)
{
  Logoff(isDisplayerr);
}
