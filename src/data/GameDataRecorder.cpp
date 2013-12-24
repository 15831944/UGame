// GameData.cpp: implementation of the GameData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "xgame.h"
#include "GameDataRecorder.h"
#include "GameFileReader.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

GameData::GameData() : account_(NULL)
{
  producePercent_ = 0.0;
  offline_second_ = 0L;
}

GameData::~GameData()
{
  
}

bool GameData::Save()
{
  CString path;
  path.Format(".\\accounts\\%s.acc" , account_->AccountName(account_->LoginedIndex()));
  CFile theFile;
  if(theFile.Open(path , CFile::modeCreate | CFile::modeWrite))
  {
    CArchive archive(&theFile, CArchive::store);
    //save quit time
    CTime cur_time = CTime::GetCurrentTime();
    account_entry_ram_.last_logout_time = cur_time.GetTime();
    archive.Write(&account_entry_ram_ , sizeof(Account_Entry_Ram));
    archive.Close();
    theFile.Close();
    return true;
  }
  return false;
}

bool GameData::Load()
{
  CString path;
  path.Format(".\\accounts\\%s.acc" , account_->AccountName(account_->LoginedIndex()));
  CFile theFile;
  if(theFile.Open(path , CFile::modeRead))
  {
    CArchive archive(&theFile, CArchive::load);
    if(archive.Read(&account_entry_ram_ , sizeof(Account_Entry_Ram)) != sizeof(Account_Entry_Ram))
      return false;
    avaliable_tasks_ = account_entry_ram_.star_researchs[RESEARCH_COMPUTER] + 1;
    //off line time
    //adjust offline's resource
    CTime cur_time = CTime::GetCurrentTime();
    CTime pre_time(account_entry_ram_.last_logout_time);
    CTimeSpan span      = cur_time - pre_time;
    ulong total_seconds = span.GetTotalSeconds();     
    //if off line time < 0 or > 7 days, cann't adjust resource
    if((total_seconds < 0 || total_seconds > 604800L) || account_entry_ram_.is_not_up_resource_offline != 0)
    {
      offline_second_ = 0L;
    }
    else
    {
      offline_second_ = total_seconds;
    }

    archive.Close();
    theFile.Close();
    return true;
  }
  return false;
}

//adjust off line resource
void GameData::AdjustOfflineResource(double metal , double crystal , double diplogen)
{
  // minalFactory
  account_entry_ram_.resources[RESOURCE_METAL]    +=  (metal * offline_second_) / 60.0;

  // crystalFactory
  account_entry_ram_.resources[RESOURCE_CRYSTAL]  += (crystal * offline_second_) / 60.0;

  //diopFactory
  account_entry_ram_.resources[RESOURCE_DIPLOGEN] +=   (diplogen * offline_second_) / 60.0;

  assert(account_entry_ram_.resources[RESOURCE_METAL] >= 0 && 
    account_entry_ram_.resources[RESOURCE_CRYSTAL] >= 0 && 
    account_entry_ram_.resources[RESOURCE_DIPLOGEN] >= 0);
}

//increase resource
void GameData::IncreaseResource(double metal , double crystal , double diplogen , uchar star)
{
  if(star == HOMESTAR)
  {
    // minalFactory
    account_entry_ram_.resources[RESOURCE_METAL] += metal;
    
    // crystalFactory
    account_entry_ram_.resources[RESOURCE_CRYSTAL] += crystal;
    
    //diopFactory
    account_entry_ram_.resources[RESOURCE_DIPLOGEN] += diplogen;
    
    assert(account_entry_ram_.resources[RESOURCE_METAL] >= 0 
      && account_entry_ram_.resources[RESOURCE_CRYSTAL] >= 0 
      && account_entry_ram_.resources[RESOURCE_DIPLOGEN] >= 0);

    //check
    account_entry_ram_.resources[RESOURCE_METAL]    = account_entry_ram_.resources[RESOURCE_METAL] < 0    ? 0 : account_entry_ram_.resources[RESOURCE_METAL];
    account_entry_ram_.resources[RESOURCE_CRYSTAL]  = account_entry_ram_.resources[RESOURCE_CRYSTAL] < 0  ? 0 : account_entry_ram_.resources[RESOURCE_CRYSTAL];
    account_entry_ram_.resources[RESOURCE_DIPLOGEN] = account_entry_ram_.resources[RESOURCE_DIPLOGEN] < 0 ? 0 : account_entry_ram_.resources[RESOURCE_DIPLOGEN];
  }
  else
  {
    Colonize_Planet_Ram& c = account_entry_ram_.conolize_planets[star - 1];
    // minalFactory
    c.metal += metal;
    
    // crystalFactory
    c.crystal += crystal;
    
    //diopFactory
    c.diplogen += diplogen;

    assert(c.metal >= 0 && c.crystal >= 0 && c.diplogen >= 0);

    //check
    c.metal   = c.metal   < 0  ? 0 : c.metal;
    c.crystal = c.crystal < 0  ? 0 : c.crystal;
    c.diplogen    = c.diplogen    < 0  ? 0 : c.diplogen;
  } 
}

//decrease resource
void GameData::DecreaseResource(double metal , double crystal , double diplogen , uchar star)
{
  if(star == HOMESTAR)
  {
    // minalFactory
    account_entry_ram_.resources[RESOURCE_METAL] -= metal;
    
    // crystalFactory
    account_entry_ram_.resources[RESOURCE_CRYSTAL] -= crystal;
    
    //diopFactory
    account_entry_ram_.resources[RESOURCE_DIPLOGEN] -= diplogen;
    
    assert(account_entry_ram_.resources[RESOURCE_METAL] >= 0 
      && account_entry_ram_.resources[RESOURCE_CRYSTAL] >= 0 
      && account_entry_ram_.resources[RESOURCE_DIPLOGEN] >= 0);

    //check
    account_entry_ram_.resources[RESOURCE_METAL]    = account_entry_ram_.resources[RESOURCE_METAL] < 0    ? 0 : account_entry_ram_.resources[RESOURCE_METAL];
    account_entry_ram_.resources[RESOURCE_CRYSTAL]  = account_entry_ram_.resources[RESOURCE_CRYSTAL] < 0  ? 0 : account_entry_ram_.resources[RESOURCE_CRYSTAL];
    account_entry_ram_.resources[RESOURCE_DIPLOGEN] = account_entry_ram_.resources[RESOURCE_DIPLOGEN] < 0 ? 0 : account_entry_ram_.resources[RESOURCE_DIPLOGEN];
  }
  else
  {
    Colonize_Planet_Ram& c = account_entry_ram_.conolize_planets[star - 1];
    // minalFactory
    c.metal -= metal;
    
    // crystalFactory
    c.crystal -= crystal;
    
    //diopFactory
    c.diplogen -= diplogen;

    assert(c.metal >= 0 && c.crystal >= 0 && c.diplogen >= 0);

    //check
    c.metal   = c.metal   < 0  ? 0 : c.metal;
    c.crystal = c.crystal < 0  ? 0 : c.crystal;
    c.diplogen    = c.diplogen    < 0  ? 0 : c.diplogen;
  } 
}