
#include "stdafx.h"
#include "xgame.h"
#include "GameFileReader.h"

AccountManager::AccountManager()
:cur_login_index_(0)
{
  InitAccountList();
}

AccountManager::~AccountManager()
{
}

void AccountManager::InitAccountList()
{
  entry_accounts_.clear();
  CFileFind ff;
	CString szDir = ".\\accounts\\";
	szDir += "*.*";	
	BOOL res = ff.FindFile(szDir);
	while(res)
	{
		res = ff.FindNextFile();
		if(!ff.IsDirectory() && !ff.IsDots())
		{
      CString name("");
      CString passord("");
      CString starname("");
      if(CheckFile(ff.GetFilePath() , name , passord , starname) == TRUE)
      {
        accout_t tmp;
        tmp.name = name;
        tmp.pswd = passord;
        tmp.starname = starname;    
        entry_accounts_.push_back(tmp);
      }      
		}	
	}		
	ff.Close();
}

BOOL AccountManager::CheckFile(const CString& path , CString& name , CString& password , CString& starname)
{
  if(path.Right(4).CompareNoCase(".acc") == 0)
  {
    Account_Entry_Ram entry_ram;
    CFile theFile;
    if(theFile.Open(path, CFile::modeRead))
    {
      CArchive archive(&theFile, CArchive::load);
      UINT cnt = archive.Read(&entry_ram , sizeof(Account_Entry_Ram));
      if(cnt != sizeof(Account_Entry_Ram) && CString(entry_ram.ident).Compare("$UGAME_ACC_HEADER$") != 0)
      {
        archive.Close();
        theFile.Close();
        return FALSE;
      }  
      name =     CString(entry_ram.account_name);
      password = CString(entry_ram.password);
      starname = CString(entry_ram.star_name);
      archive.Close();
      theFile.Close();
      return TRUE;
    }    
  }
  return FALSE;
}

size_t AccountManager::AccountSize()
{
  return entry_accounts_.size();
}

CString AccountManager::AccountName(size_t index)
{
  assert(index < entry_accounts_.size());
  return entry_accounts_[index].name;
}

CString AccountManager::AccountPassword(size_t index)
{
  assert(index < entry_accounts_.size());
  return entry_accounts_[index].pswd;
}

bool AccountManager::CheckValidAccount(const CString& accout , const CString& pass , int& index)
{
  for(int i = 0 ; i < entry_accounts_.size() ; ++i)
  {
    //both account name and password match
    if(entry_accounts_[i].name.CompareNoCase(accout) == 0 && entry_accounts_[i].pswd == pass){
      index = i;
      return true;
    }
  }
  index = -1;
  return false;
}

bool AccountManager::ExistAccount(const CString& name)
{
  for(int i = 0 ; i < entry_accounts_.size() ; ++i)
  {
    if(entry_accounts_[i].name.CompareNoCase(name) == 0)
    {
      return true;
    }
  }
  return false;
}

bool AccountManager::RegisterAccount(const CString& name , const CString& password , const CString& star_name , 
                                     uchar com_r , int speed , uchar com_ai_r , CString npc_name , 
                                     BOOL computer_attack_me , BOOL not_up_res)
{
  ////1.file name
  CString filename = ".\\accounts\\" + name + ".acc";
  ////2.settings
  CFile theFile;
  if(theFile.Open(filename, CFile::modeCreate | CFile::modeWrite))
  {    
    Account_Entry_Ram entry_ram;
    //ident
    strcpy(entry_ram.ident , "$UGAME_ACC_HEADER$");

    //account name
    strncpy(entry_ram.account_name , name , 32);

    //password
    strncpy(entry_ram.password , password , 32);

    //star name
    strncpy(entry_ram.star_name , star_name , 32);

    //position
    ULONG index = 1 +(RandomNumber(MAX_GALAXY_GALA * MAX_GALAXY_SYS * MAX_GALAXY_POS));
    entry_ram.position = index;

    //score
    entry_ram.score = 0.0;

    //default_spy_num
    entry_ram.default_spy_num = 1;

    //account_money
    entry_ram.account_money = 0.0;

    //resource
    for(uchar i = 0 ; i < RESOURCE_DIPLOGEN ; ++i)
    {
      entry_ram.resources[i] = 5000.0;
    }
    entry_ram.resources[RESOURCE_DIPLOGEN] = 0;

    //product percent
    entry_ram.metal_percent = 100;
    entry_ram.cryst_percent = 100;
    entry_ram.diplo_percent = 100;
    entry_ram.solar_percent = 100;

    //star buildings
    memset(entry_ram.star_buildings , 0 , FACTORY_BUILDINGS_MAX * 4);

    //star researches
    memset(entry_ram.star_researchs , 0 , RESEARCH_MAX * 4);

    //star boats
    memset(entry_ram.star_boats , 0 , BOAT_MAX * 4);

    //star defenses
    memset(entry_ram.star_defenses , 0 , DEFENSE_MAX * 4);

    //log&reg time
    CTime cur_time = CTime::GetCurrentTime();
    entry_ram.last_logout_time = 0L;
    entry_ram.register_time = cur_time.GetTime();

    //misc settings
    entry_ram.has_moon = 0;
    entry_ram.has_gate = 0;
    entry_ram.is_not_up_resource_offline = (UCHAR)not_up_res;

    //temp , ciru , speed
    entry_ram.temp = RandomHighTemp(Index2Pos(index).Pos);
    entry_ram.ciru = RandomStarSize(Index2Pos(index).Pos);
    entry_ram.speed = speed;

    //heroes
    entry_ram.double_res_hero = 0;

    //npc name
    strncpy(entry_ram.npc_name , npc_name , 32);

    //AI 
    entry_ram.computer_rank = com_r;
    entry_ram.computer_is_attack_player = computer_attack_me;
    entry_ram.computer_ai_mode = com_ai_r;
    entry_ram.reserved_1 = 0xFF;

    //reserved
    memset(entry_ram.reserved_buff , 0xFF , 256);

    ////Conolized planets
    for(i = 0 ; i < STAR_MAX - 1 ; ++i)
    {
      entry_ram.conolize_planets[i].metal = entry_ram.conolize_planets[i].crystal = entry_ram.conolize_planets[i].diplogen = 0.0;
      entry_ram.conolize_planets[i].has_moon = entry_ram.conolize_planets[i].has_gate = entry_ram.conolize_planets[i].is_exist = 0;
      entry_ram.conolize_planets[i].position = 0;
      for(uchar b = 0 ; b < BOAT_MAX ; ++b)
      {
        entry_ram.conolize_planets[i].star_boats[b] = 0.0;
      }
    }

    ////computer mappings
    for(ulong c = 0 ; c < MAX_GALAXY_GALA * MAX_GALAXY_SYS * MAX_GALAXY_POS ; ++c)
    {
      entry_ram.compters_info[c].score = entry_ram.compters_info[c].lost_score = entry_ram.compters_info[c].ruin_metal = entry_ram.compters_info[c].ruin_crystal = 0.0;
      entry_ram.compters_info[c].is_npc_target = 0;
      entry_ram.compters_info[c].num_double_res_hero = 0;
      entry_ram.compters_info[c].is_slave_planet = 0;
      entry_ram.compters_info[c].reserved = 0xFFFFFFFF;
      //type
      //self
      if(c == index) entry_ram.compters_info[c].owner_type = STAR_T_SELF;
      else
      {
        if(RandomNumber(100) < 10)
        {
          entry_ram.compters_info[c].owner_type = STAR_T_NONE;
        }
        else
        {
          entry_ram.compters_info[c].owner_type = STAR_T_ENEMY;
        }
      }
    }
    //hero&NPC
    USHORT double_res_hero = 0;
    uchar cnt = 0;
    while(cnt < 3 && entry_ram.compters_info[double_res_hero = RandomNumber(MAX_GALAXY_GALA * MAX_GALAXY_SYS * MAX_GALAXY_POS)].owner_type == STAR_T_ENEMY)
    {
      entry_ram.compters_info[double_res_hero].num_double_res_hero = 1;
      ++cnt;
    }
    USHORT npc_target = 0;
    cnt = 0;
    while(cnt < 3 && entry_ram.compters_info[npc_target = RandomNumber(MAX_GALAXY_GALA * MAX_GALAXY_SYS * MAX_GALAXY_POS)].owner_type == STAR_T_ENEMY)
    {
      entry_ram.compters_info[npc_target].is_npc_target = 1;
      ++cnt;
    }

    ////save as file
    CArchive archive(&theFile, CArchive::store);
    archive.Write(&entry_ram , sizeof(Account_Entry_Ram));
    archive.Close();
    theFile.Close();

    InitAccountList();
    return true;
  }
  return false;  
}

bool AccountManager::DeleteAccount(const CString& name)
{
  //1.delete account file
  CString filename = ".\\accounts\\" + name + ".acc";
  if(DeleteFile(filename) == FALSE)
  {
    return false;
  }

  //2.update
  InitAccountList();
  return true;
}

bool AccountManager::CanGetPassword(const CString& account , const CString& starname , CString& password)
{
  for(int i = 0 ; i < entry_accounts_.size() ; ++i)
  {
    if(entry_accounts_[i].name.CompareNoCase(account) == 0)
    {
      if(starname.CompareNoCase(entry_accounts_[i].starname) ==0 )
      {
        password = entry_accounts_[i].pswd;
        return true;
      }      
    }
  }
  return false;
}

void AccountManager::Login(int index)
{
  assert(index >= 0 && index < AccountSize());
  cur_login_index_ = index;
}



