#include "stdafx.h"
#include "xgame.h"
#include "UStar.h"
#include "GameDataRecorder.h"

static const int MAX_RESOURCE_BASE  = 1000;

Star::Star(GameData* gamedata , UINT index)
{
  data_              = gamedata;
  computer_info_     = &data_->COMPUTER_PLANET(index);
  index_             = index;
  recycled_metal_    = computer_info_->ruin_metal;
  recycled_crystal_  = computer_info_->ruin_crystal;
  is_fleet_out       = false;
  is_npc_player      = computer_info_->is_npc_target != 0;  
  name_              = "";
  double_res_hero    = computer_info_->num_double_res_hero;
  rank_              = computer_info_->score;
  is_salve_planet    = computer_info_->is_slave_planet != 0;
  type_              = computer_info_->owner_type;
  
  //star position
  position_     = Index2Pos(index_);
  bitmap_index_ = RandomNumber(10); 
  
  //generate enemy
  if(computer_info_->owner_type == STAR_T_ENEMY)
  {
    char buf[32];
    if(is_npc_player && data_->NPC_NAME().IsEmpty() == FALSE)
    {      
      name_.Format("%s[%s]" , data_->NPC_NAME() , position_.ToCString(buf));
    }  
    else
    {
      name_.Format("%s" , position_.ToCString(buf));
    }
    generate();
  }    
  if(computer_info_->owner_type == STAR_T_SELF)
  {
    name_ = data_->GetLoginedAccountName();
    rank_ = data_->GetLoginedAccountRank();
    double_res_hero = data_->GET_STAR_DOUBLE_RES_HERO();
  }
}

void Star::Update()
{
  //just update enemy
  if(type_ == STAR_T_ENEMY)
  {
    generate();
  } 
}

inline
void Star::generate()
{
   //player info
  ShipTechs selfTechs;
  selfTechs.Weapon = data_->GetResearchLevel(RESEARCH_WEAPON);
  selfTechs.Shield = data_->GetResearchLevel(RESEARCH_SHEILED);
  selfTechs.Armour = data_->GetResearchLevel(RESEARCH_ARMOUR);
  uchar computer_rank = data_->GetLoginedAccountComputerRank();
  double account_rank = data_->GetLoginedAccountRank();
  ////enemy star information
  //random create fleets and defenses
  fleet_and_defense_.clear();
  float seed = 1000.0;
  switch(computer_rank)
  {
  case COMPUTER_T_MID:
    seed = 3000.0;
    break;
  case COMPUTER_T_LOW:
    seed = 6000.0;
    break;
  }
  CTime curT = CTime::GetCurrentTime();
  CTimeSpan span = curT - data_->REGISTER_TIME();
  long register_seconds = span.GetTotalSeconds();
  assert(register_seconds >= 0);
  if(register_seconds < 0) register_seconds = 0;
  //on line time ratio
  //high: 24 hours one day
  double online_ratio = 1.0;
  //mid: 12 hours one day
  if(computer_rank == COMPUTER_T_MID)
  {
    online_ratio = 0.6;
  }
  //low: 5 hours one day
  else if(computer_rank == COMPUTER_T_LOW)
  {
    online_ratio = 0.3;
  }
  double base_rank = pow(register_seconds * online_ratio / 3600.0 , 2.2) * pow(_speed_adjust_ , 1.4); 

  //computer AI setting
  UINT base = 0;
  //by time
  if(data_->COMPUTER_AI_MODE() == COM_AI_T_BY_TIME)
  {
    base = base_rank   / 5678.0;
  }
  //by player
  else
  {
    base = account_rank / seed;
  }

  //random
  int temp = RandomNumber(100);
  //3%: no fleets and defense: 0-2
  if(temp < COMPUTER_T_HIGH + 2 - computer_rank)
  {
    base = 1;
  }
  //5% percent, fewest fleet and defense, 3~8
  else if(temp >= 3 && temp < 8)
  {
    base = UINT(base / 6.0);
  }
  //5% percent, fewer fleet and defense, 8~13
  else if(temp >= 8 && temp < 13)
  {
    base = UINT(base / 4.0);
  }
  //5% percent, few fleet and defense, 13~18
  else if(temp >= 13 && temp < 18)
  {
    base = UINT(base / 2.0);
  }
  //5% percent, many fleet and defense, 85~90
  else if(temp >= 85 && temp < 90)
  {
    base = UINT(base * 2.0);
  }
  //5% percent, more fleet and defense, 90~95
  else if(temp >= 90 && temp < 95)
  {
    base = UINT(base * 4.0);
  }
  //5% percent, most many fleet and defense, 95~99
  else if(temp >= 95 && temp < 100)
  {
    base = UINT(base * 6.0);    
  }
  //%67 normal
  else
  {
  }

  base = (base == 0 ? 1 : base);
  SItem item;
  item.OwnerID = 0;
  //S.C    
  item.Type    = T_KT;
  item.Num     = RandomNumber(base * 3);
  fleet_and_defense_.push_back(item);
  //L.C
  item.Type    = T_GT;
  item.Num     = RandomNumber(base);
  fleet_and_defense_.push_back(item);
  //L.F
  item.Type    = T_LJ;
  item.Num     = RandomNumber(base * 50);
  fleet_and_defense_.push_back(item);
  //H.F
  item.Type    = T_SJ;
  item.Num     = RandomNumber(base * 10);
  fleet_and_defense_.push_back(item);
  //C.L
  item.Type    = T_KREUZER;
  item.Num     = RandomNumber(base * 4);
  fleet_and_defense_.push_back(item);
  //BB
  item.Type    = T_SS;
  item.Num     = RandomNumber(base * 4);
  fleet_and_defense_.push_back(item);
  //Colony
  item.Type    = T_KOLO;
  item.Num     = RandomNumber(10);
  fleet_and_defense_.push_back(item);
  //Recycle
  item.Type    = T_REC;
  item.Num     = RandomNumber(base);
  fleet_and_defense_.push_back(item);
  //spy
  item.Type    = T_SPIO;
  item.Num     = RandomNumber(base / 10.0 + 1);
  fleet_and_defense_.push_back(item);
  //bomber
  item.Type    = T_BOMBER;
  item.Num     = RandomNumber(base);
  fleet_and_defense_.push_back(item);
  //solar ship
  item.Type    = T_SAT;
  item.Num     = RandomNumber(base / 5.0 + 1);
  fleet_and_defense_.push_back(item);
  //destroyer
  item.Type    = T_ZER;
  item.Num     = RandomNumber(base);
  fleet_and_defense_.push_back(item);
  //ds
  item.Type    = T_TS;
  item.Num     = RandomNumber(base / 200.0 + 1);
  fleet_and_defense_.push_back(item);

  //Missile Launcher
  item.Type    = T_RAK;
  item.Num     = RandomNumber(base * 15);
  fleet_and_defense_.push_back(item);

  //Small Laser
  item.Type    = T_LL;
  item.Num     = RandomNumber(base * 15);
  fleet_and_defense_.push_back(item);

  //heavy Laser
  item.Type    = T_SL;
  item.Num     = RandomNumber(base / 5.0 + 1);
  fleet_and_defense_.push_back(item);

  //Gauss
  item.Type    = T_GAUSS;
  item.Num     = RandomNumber(base / 10.0 + 1);
  fleet_and_defense_.push_back(item);

  //ION
  item.Type    = T_IONEN;
  item.Num     = RandomNumber(base / 10.0 + 1);
  fleet_and_defense_.push_back(item);

  //PC
  item.Type    = T_PLASMA;
  item.Num     = RandomNumber(base / 20.0 + 1);
  fleet_and_defense_.push_back(item);

  //Small Shield Dome
  item.Type    = T_KS;
  item.Num     = RandomNumber(2);
  fleet_and_defense_.push_back(item);

  //LARGE Shield Dome
  item.Type    = T_GS;
  item.Num     = RandomNumber(2);
  fleet_and_defense_.push_back(item);

  assert(fleet_and_defense_.size() == T_END);
  //special 3% or less than 30 score no fleets and defense, i
  if(register_seconds == 0 || RandomNumber(100) < 3 || account_rank < 500.0)
  {
    for(int i = T_KT ; i < T_END ; ++i)
    {
      fleet_and_defense_[i].Num = 0;
    }
  }
  //calc fleet number
  fleet_number_ = 0L;
  for(int i = T_KT ; i < T_RAK ; ++i)
  {
    fleet_number_ += fleet_and_defense_[i].Num;
  }

  //calc score
  Res worth = kernel_.GetFleetWorth(&fleet_and_defense_);
  UINT t = RandomNumber(30) + 60;//60% ~ 90%
  rank_  = (worth.met + worth.deut + worth.kris) / 1000.0 * (100.0 / t);

  //resource
  metal_    = pow(_speed_adjust_ , 0.3) * pow(2 , COMPUTER_T_HIGH - computer_rank) * ( pow(rank_ , 0.6) + 100) * RandomNumber(MAX_RESOURCE_BASE);
  crystal_  = pow(_speed_adjust_ , 0.3) * pow(2 , COMPUTER_T_HIGH - computer_rank) * ( pow(rank_ , 0.6) + 100) * RandomNumber(UINT(MAX_RESOURCE_BASE / 1.5));
  diplogen_ = pow(_speed_adjust_ , 0.3) * pow(2 , COMPUTER_T_HIGH - computer_rank) * ( pow(rank_ , 0.6) + 100) * RandomNumber(UINT(MAX_RESOURCE_BASE / 2.5));

  ////tech and elapsed percent
  spy_level_     = RandomNumber(data_->GetResearchLevel(RESEARCH_SPY) + pow(4 , computer_rank));
  elpase_        = RandomNumber(250 * (1 + computer_rank)) / 1000.0;

  //special 4%: resource much, elpase_ * 2
  if(RandomNumber(100) < COMPUTER_T_HIGH + 3 - computer_rank)
  {
    metal_    *= (50 * pow(2 , computer_rank));
    crystal_  *= (50 * pow(2 , computer_rank));
    diplogen_ *= (50 * pow(2 , computer_rank));
    elpase_   *= pow(2 , computer_rank);    
  }
  elpase_    = elpase_ > 1 ? 1.0 : elpase_;

  //max resource
  ulong max_res = 200000000 * pow(2 , computer_rank) * pow(_speed_adjust_ , 0.3);
  metal_    = metal_    > max_res ? max_res : metal_;
  crystal_  = crystal_  > max_res ? max_res : crystal_;
  diplogen_ = diplogen_ > max_res ? max_res : diplogen_;

  //techs
  ship_techs_.Armour = RandomNumber(selfTechs.Weapon + pow(3 , computer_rank));
  ship_techs_.Shield = RandomNumber(selfTechs.Weapon + pow(3 , computer_rank));
  ship_techs_.Weapon = RandomNumber(selfTechs.Weapon + pow(3 , computer_rank));
}

