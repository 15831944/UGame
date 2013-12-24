// GameData.h: interface for the GameData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEDATA_H__E87031F1_4D59_49B4_8700_F95B2E6597E0__INCLUDED_)
#define AFX_GAMEDATA_H__E87031F1_4D59_49B4_8700_F95B2E6597E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AccountManager;
class GameData  
{
private:
  AccountManager* account_;
  Account_Entry_Ram account_entry_ram_;
  unsigned long existPower_;
  unsigned long consumePower_;
  double        producePercent_;  
  //others
  uchar avaliable_tasks_;
  ulong offline_second_;  
public:
  GameData();
	~GameData();
  void SetAccountPtr(AccountManager* a){account_ = a;}

  //GAME INFO
  ushort GAME_SPEED()
  {
    return account_entry_ram_.speed;
  }

  CTime REGISTER_TIME()
  {
    CTime t(account_entry_ram_.register_time);
    return t;
  }

  uchar COMPUTER_AI_MODE()
  {
    return account_entry_ram_.computer_ai_mode;
  }

  CString NPC_NAME()
  {
    return account_entry_ram_.npc_name;
  }

  bool CAN_COMPUTER_ATTACK()
  {
    return account_entry_ram_.computer_is_attack_player != 0;
  }

  char STAR_TEMP()
  {
    return account_entry_ram_.temp;
  }

  USHORT STAR_CIRU()
  {
    return account_entry_ram_.ciru;
  }

  bool IS_NOT_UP_RES_OFFLINE()
  {
    return account_entry_ram_.is_not_up_resource_offline != 0;
  }

  uchar GET_STAR_DOUBLE_RES_HERO()
  {
    return account_entry_ram_.double_res_hero;
  }

  void ADD_STAR_DOUBLE_RES_HERO(uchar n)
  {
    account_entry_ram_.double_res_hero += n;
  }

  Computer_Planet_Ram& COMPUTER_PLANET(ulong index)
  {
    assert(index < MAX_GALAXY_GALA * MAX_GALAXY_SYS * MAX_GALAXY_POS);
    return account_entry_ram_.compters_info[index];
  }

  ////person----------------------------------------------------------------//
  //Account name
  CString GetLoginedAccountName(){return CString(account_entry_ram_.account_name);}
  
  //Account password
  CString GetLoginedAccountPass(){return CString(account_entry_ram_.password);}
 
  //Account star name
  CString GetLoginedAccountStarName(){return CString(account_entry_ram_.star_name);}
 
  //Position
  PlaniPos GetLoginedAccountPosition(){return Index2Pos(account_entry_ram_.position);}

  //Moon
  bool HasMoon(){return account_entry_ram_.has_moon != 0;}
  void SetMoon(bool m){account_entry_ram_.has_moon = m;}

  //Gate
  bool HasSuperGate(){return account_entry_ram_.has_gate != 0;}
  void SetSuperGate(bool s){account_entry_ram_.has_gate = s;}

  //rank
  double GetLoginedAccountRank(){return account_entry_ram_.score;}
  void SetLoginedAccountRank(double rank)
  {
    account_entry_ram_.score = rank; 
    account_entry_ram_.score = (account_entry_ram_.score <= 0.0 ? 0.0 : account_entry_ram_.score);
  }
  void UpdateRank(double r)
  {
    account_entry_ram_.score += r; 
    account_entry_ram_.score = (account_entry_ram_.score <= 0.0 ? 0.0 : account_entry_ram_.score);
  }

  //computer rank
  uchar GetLoginedAccountComputerRank()
  {
    return account_entry_ram_.computer_rank;
  } 
  //money
  double GetAccountMoney()
  {
    return account_entry_ram_.account_money;
  }
  void UpdateAccountMoney(double m)
  {
    account_entry_ram_.account_money += m;
    if(account_entry_ram_.account_money < 0.0)
    {
      account_entry_ram_.account_money = 0.0;
    }
  }

  ////buildings----------------------------------------------------------------//
  ushort GetBuildingLevel(uchar index)
  {
    assert(index <FACTORY_BUILDINGS_MAX);
    return account_entry_ram_.star_buildings[index];
  }

  void SetBuildingLevel(uchar index , ushort l)
  {
    assert(index <FACTORY_BUILDINGS_MAX );
    account_entry_ram_.star_buildings[index] = l;
  }

  ////resource----------------------------------------------------------------//
  double GetResource(uchar index)
  {
    assert(index <RESOURCE_MAX );
    return account_entry_ram_.resources[index];
  }
  void SetResource(uchar index , double r)
  {
    assert(index <RESOURCE_MAX );
    account_entry_ram_.resources[index] = r;
  }

  ////percent----------------------------------------------------------------//
  double GetProductPercent(uchar index)
  {
    assert(index <PRODUCT_MAX );
    switch(index)
    {
    case PRODUCT_METAL:
    	return account_entry_ram_.metal_percent;
    case PRODUCT_CRYSTAL:
    	return account_entry_ram_.cryst_percent;
    case PRODUCT_DIPLOGEN:
    	return account_entry_ram_.diplo_percent;
    case PRODUCT_SOLAR:
    	return account_entry_ram_.solar_percent;
    default:
      assert(false);
    }
    return 0;
  }
  void SetProductPercent(uchar index , double r)
  {
    assert(index <PRODUCT_MAX );
    switch(index)
    {
    case PRODUCT_METAL:
    	account_entry_ram_.metal_percent = r * 100;
      break;
    case PRODUCT_CRYSTAL:
    	account_entry_ram_.cryst_percent = r * 100;
      break;
    case PRODUCT_DIPLOGEN:
    	account_entry_ram_.diplo_percent = r * 100;
      break;
    case PRODUCT_SOLAR:
    	account_entry_ram_.solar_percent = r * 100;
      break;
    default:
      assert(false);
      break;
    }
  }  

  ////research----------------------------------------------------------------//
  ushort GetResearchLevel(uchar index)
  {
    assert(index <RESEARCH_MAX );
    return account_entry_ram_.star_researchs[index];
  }

  void SetResearchLevel(uchar index , ushort l)
  {
    assert(index <RESEARCH_MAX );
    account_entry_ram_.star_researchs[index] = l;
  }

  ////boats----------------------------------------------------------------//
  ulong GetBoatNumber(uchar index)
  {
    assert(index <BOAT_MAX );
    return account_entry_ram_.star_boats[index];
  }

  void SetBoatNumber(uchar index , ulong n)
  {
    assert(index <BOAT_MAX );
    account_entry_ram_.star_boats[index] = n;
  }
  
 ////default spy number----------------------------------------------------------------//
  ulong GetDefaultSpyNumber()
  {
    return account_entry_ram_.default_spy_num;
  }
  void SetDefaultSpyNumber(ulong p)
  {
    account_entry_ram_.default_spy_num = p;
  }

  ////Conolys----------------------------------------------------------------//
  Colonize_Planet_Ram& GetColonyStarObj(uchar index)
  {
    assert(index < STAR_MAX - 1);
    return account_entry_ram_.conolize_planets[index];
  }
  
  int GetStarIndexByPos(const PlaniPos& pos)
  {
    ulong index = Pos2Index(pos);
    if(account_entry_ram_.position == index) return HOMESTAR;
    for(int i = 1 ; i < STAR_MAX - 1 ; ++i)
    {
      if(account_entry_ram_.conolize_planets[i].position == index)
      {
        return i;
      }
    }
    assert(false);
    return HOMESTAR;
  }   
    
  uchar GetStarNumber()
  {
    uchar cnt = 1;
    for(int i = 0 ; i < STAR_MAX - 1 ; ++i)
    {
      if(account_entry_ram_.conolize_planets[i].is_exist)
      {
        ++cnt;
      }
    }
    return cnt;
  }

  void Colonize(const PlaniPos& pos)
  {
    uchar index = search_first_uncolonized_star();
    if(index >= STAR_MAX - 1)
    {
      return;
    }
    Colonize_Planet_Ram& c = account_entry_ram_.conolize_planets[index];
    c.is_exist = 1;
    c.position = Pos2Index(pos);
  }

  void DestroyStar(int index)
  {
    assert(index > HOMESTAR && index < STAR_MAX);
    Colonize_Planet_Ram& c = account_entry_ram_.conolize_planets[index];
    c.is_exist = 0;
    c.position = 0;
    c.metal = c.crystal = c.diplogen = 0;
    c.has_gate = c.has_moon = false;
    memset(c.star_boats , 0 , BOAT_MAX * 4);
  }

  //star funcs-----------------------------------------------------------//
  Resource STAR_RESOURCE(uchar index)
  {
    assert(index < STAR_MAX);
    Resource tmp;
    if(index == HOMESTAR)
    {
      tmp.metal_ =    account_entry_ram_.resources[RESOURCE_METAL];
      tmp.crystal_ =  account_entry_ram_.resources[RESOURCE_CRYSTAL];
      tmp.diplogen_ = account_entry_ram_.resources[RESOURCE_DIPLOGEN];
    }
    else
    {
      Colonize_Planet_Ram& c = account_entry_ram_.conolize_planets[index - 1];
      tmp.metal_    = c.metal;
      tmp.crystal_  = c.crystal;
      tmp.diplogen_ = c.diplogen;
    }
    return tmp;
  }

  UINT STAR_BOAT_NUMBER(uchar type , int index)
  {
    assert(index < STAR_MAX);
    assert(type < BOAT_MAX);
    UINT tmp = 0L;
    if(index == HOMESTAR)
    {
      tmp = account_entry_ram_.star_boats[type];
    }
    else
    {
      Colonize_Planet_Ram& c = account_entry_ram_.conolize_planets[index - 1];
      tmp = c.star_boats[type];
    }
    return tmp;
  }

  bool STAR_HAS_MOON(int index)
  {
    assert(index < STAR_MAX);
    bool tmp = false;
    if(index == HOMESTAR)
    {
      tmp = account_entry_ram_.has_moon != 0;
    }
    else
    {
      Colonize_Planet_Ram& c = account_entry_ram_.conolize_planets[index - 1];
      tmp = (c.has_moon != 0);
    }
    return tmp;
  }

  bool STAR_HAS_GATE(int index)
  {
    assert(index < STAR_MAX);
    bool tmp = false;
    if(index == HOMESTAR)
    {
      tmp = account_entry_ram_.has_gate != 0;
    }
    else
    {
      Colonize_Planet_Ram& c = account_entry_ram_.conolize_planets[index - 1];
      tmp = (c.has_gate != 0);
    }
    return tmp;
  }

  bool STAR_IS_EXISTED(int index)
  {
    assert(index < STAR_MAX);
    bool tmp = true;
    if(index == HOMESTAR)
    {
      tmp = true;
    }
    else
    {
      Colonize_Planet_Ram& c = account_entry_ram_.conolize_planets[index - 1];
      tmp = (c.is_exist != 0);
    }
    return tmp;
  }

  PlaniPos STAR_POSITION(int index)
  {
    assert(index < STAR_MAX);
    PlaniPos tmp;
    if(index == HOMESTAR)
    {
      tmp = Index2Pos(account_entry_ram_.position);
    }
    else
    {
      Colonize_Planet_Ram& c = account_entry_ram_.conolize_planets[index - 1];
      tmp = Index2Pos(c.position);
    }
    return tmp;
  }

  void PRODUCE_MOON(int index , bool isProduce = true)
  {
    assert(index < STAR_MAX);
    if(index == HOMESTAR)
    {
      account_entry_ram_.has_moon = isProduce;
    }
    else
    {
      Colonize_Planet_Ram& c = account_entry_ram_.conolize_planets[index - 1];
      c.has_moon = isProduce;
    }
  }

  void PRODUCE_GATE(int index , bool isProduce = true)
  {
    assert(index < STAR_MAX);
    if(index == HOMESTAR)
    {
      account_entry_ram_.has_gate = isProduce;
    }
    else
    {
      Colonize_Planet_Ram& c = account_entry_ram_.conolize_planets[index - 1];
      c.has_gate = isProduce;
    }
  }

  double ACCOUNT_AVAILABLE_FLEET_NUMBER()
  {
    double fleet_n = 0.0;
    for(uchar i = 0 ; i < STAR_MAX ; ++i)
    {
      if(STAR_IS_EXISTED(i))
      {
        for(int f = T_KT ; f < T_RAK ; ++f)
        {
          fleet_n += STAR_BOAT_NUMBER(f , i);
        }
      }
    }
    return fleet_n;
  }

  ushort STAR_USED_SIZE()
  {
    ushort t = 0;
    for(int i = 0 ; i < FACTORY_BUILDINGS_MAX ; ++i)
    {
      t += account_entry_ram_.star_buildings[i];
    }
    return t;
  }

  ulong GET_STAR_DEFENSE(uchar type)
  {
    assert(type <= DEFENSE_MAX);
    return account_entry_ram_.star_defenses[type];
  }

  void SET_STAR_DEFENSE(uchar type , ulong num)
  {
    assert(type <= DEFENSE_MAX);
    account_entry_ram_.star_defenses[type] = num;
  }


public:
  void IncreaseResource(double metal , double crystal , double diplogen , uchar star = HOMESTAR);
  void DecreaseResource(double metal , double crystal , double diplogen , uchar star = HOMESTAR);

  int  GetExistPower()       {return      existPower_;}
  int  GetConsumePower()     {return      consumePower_;}
  double GetTotalProducePercent() {return producePercent_;}

  void SetExistPower(unsigned long e)   {existPower_ = e;}
  void SetConsumePower(unsigned long c) {consumePower_ = c;}
  void SetTotalProducePercent(double p) {producePercent_ = p;}

  void UpdateAvaliableTasks(int task_counter){avaliable_tasks_ = account_entry_ram_.star_researchs[RESEARCH_COMPUTER] + 1 - task_counter;}
  int  GetAvaliableTasks(){return avaliable_tasks_;}
  void AdjustOfflineResource(double metal , double crystal , double diplogen);
  
  void ShipsOut(const FLEET& ships , uchar star = HOMESTAR , bool bProduceMoon = false)
  {
    if(star == HOMESTAR)
    {
      for(int i = 0 ; i < ships.size() ; ++i)
      {
        account_entry_ram_.star_boats[i] -= ships[i].Num;
        if(account_entry_ram_.star_boats[i] < 0L)
        {
          account_entry_ram_.star_boats[i] = 0L;
        }
      }      
    }
    else
    {
      for(int i = 0 ; i < ships.size() ; ++i)
      {
        account_entry_ram_.conolize_planets[star -1].star_boats[i] -= ships[i].Num;
        if(account_entry_ram_.conolize_planets[star -1].star_boats[i] < 0L)
        {
          account_entry_ram_.conolize_planets[star -1].star_boats[i] = 0L;
        }
      }      
    }
    if(!bProduceMoon)
    {
      --avaliable_tasks_;
    }
  }

  void ShipsIn(const FLEET& ships , uchar star = HOMESTAR) 
  {
    if(star == HOMESTAR)
    {
      for(int i = 0 ; i < ships.size() ; ++i)
      {
        account_entry_ram_.star_boats[i] += ships[i].Num;
      }      
    }
    else
    {
      for(int i = 0 ; i < ships.size() ; ++i)
      {
        account_entry_ram_.conolize_planets[star -1].star_boats[i] += ships[i].Num;
      }      
    }
    ++avaliable_tasks_;
  }
public:
  bool Load();
  bool Save();

private:
  uchar search_first_uncolonized_star()
  {
    for(int i = 0 ; i < STAR_MAX - 1 ; ++i)
    {
      if(account_entry_ram_.conolize_planets[i].is_exist == 0)
      {
        return i;
      }
    }
   return 255;
  }
};

#endif // !defined(AFX_GAMEDATA_H__E87031F1_4D59_49B4_8700_F95B2E6597E0__INCLUDED_)
