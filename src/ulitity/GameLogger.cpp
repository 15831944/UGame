#include "stdafx.h"
#include "xgame.h"
#include "GameLogger.h"

CGameLogger::CGameLogger()
{
}

CGameLogger::~CGameLogger()
{
}

void CGameLogger::Init(const CString& account_name)
{
  account_name_ = account_name;
  //delete existed log file
  CString name;
  name.Format(".\\log\\UGame[%s].log" , account_name_);
  DeleteFile(name);
}

void CGameLogger::Log(const CString& info)
{
  CString name;
  name.Format(".\\log\\UGame[%s].log" , account_name_);
  if(logger_.Open(name , CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite))
  {
    CTime t = CTime::GetCurrentTime();
    CString msg;
    msg.Format("[%d-%02d-%02d %02d:%02d:%02d] %s\n" , 
                t.GetYear() , t.GetMonth() , t.GetDay() , 
                t.GetHour() , t.GetMinute() , t.GetSecond() , info);
    logger_.SeekToEnd();
    logger_.WriteString(msg);
    logger_.Close();
  }  
}

CGameLogger& CGameLogger::Instance()
{
  static CGameLogger self;
  return self;
}