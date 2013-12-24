#include "StdAfx.h"
#include "WarSimulator.h"

extern float _speed_adjust_;

WarSimulator::WarSimulator()
{  

}

//Simulate war
bool WarSimulator::Simulate(int number , const CString& attack_name , const CString& defender_name , Resource& defnder_res ,
    bool is_elapse , FLEET& attack , FLEET& defence , ShipTechs& att_tech , ShipTechs& def_tech , BattleRes& result , bool is_be_attacked)
{
  //sets
  int FleetID = 0;  
  //res
  Res resource;
  resource.met = defnder_res.metal_;
  resource.kris = defnder_res.crystal_;
  resource.deut = defnder_res.diplogen_;
  FLEET def_copy_fleet = defence;
  //if elapsed
  if(is_elapse && is_be_attacked == false)
  {
    resource.met = resource.kris = resource.deut = 0;
    for(int i = T_KT ; i < T_RAK ; ++i)
    {
      def_copy_fleet[i].Num = 0;
    }
  }
  kernel_.SetPlayerName(attack_name , defender_name);
  kernel_.SetTargetResource(resource , FleetID);
  kernel_.SetFleet(&attack, &def_copy_fleet);
  kernel_.SetTechs(&att_tech, &def_tech , FleetID);

  //simulate
  bool ret = kernel_.Simulate(number);  
  if(!ret) return false;
  ////set result
  //report file
  CTime t = CTime::GetCurrentTime();
  if(is_be_attacked)
    sprintf(result.report_file_ , ".\\html\\%s_%d-%02d-%02d_%02d-%02d-%02d.htm" , attack_name
      , t.GetYear() , t.GetMonth() , t.GetDay() , t.GetHour() , t.GetMinute() , t.GetSecond());
  else
    sprintf(result.report_file_ , ".\\html\\%s_%d-%02d-%02d_%02d-%02d-%02d.htm" , defender_name
      , t.GetYear() , t.GetMonth() , t.GetDay() , t.GetHour() , t.GetMinute() , t.GetSecond());
  kernel_.GenerateCR(result.report_file_);

  //fleets
  result.self_fleet_.clear();
  result.target_fleet_.clear();
  result.self_fleet_.resize(T_END);
  result.target_fleet_.resize(T_END);
  kernel_.GetFleetAfterSim(&result.self_fleet_[0] , &result.target_fleet_[0] , 0);
  //if elapsed
  if(is_elapse)
  {
    //reload fleet
    for(int i = T_KT ; i < T_RAK ; ++i)
    {
      result.target_fleet_[i].Num = defence[i].Num;
    }
  }

  BattleResult& r = kernel_.GetBattleResult();
  //attack loss
  result.loss_resource_.metal_ = r.VerlusteAngreifer.met;
  result.loss_resource_.crystal_ = r.VerlusteAngreifer.kris;
  result.loss_resource_.diplogen_ = r.VerlusteAngreifer.deut;

  //defense loss after rebuild defense
  result.target_loss_resource_.metal_ = r.VerlVertmitAufbau.met;
  result.target_loss_resource_.crystal_ = r.VerlVertmitAufbau.kris;
  result.target_loss_resource_.diplogen_ = r.VerlVertmitAufbau.deut;

  //recycled resource
  result.recycled_resource_.metal_ = r.TF.met;
  result.recycled_resource_.crystal_ = r.TF.kris;
  result.recycled_resource_.diplogen_ = r.TF.deut;
  
  //plunder resource
  result.catch_resource_.metal_ = r.Beute.met;
  result.catch_resource_.crystal_ = r.Beute.kris;
  result.catch_resource_.diplogen_ = r.Beute.deut;  

  return true;
}

UINT WarSimulator::GetFleetSpeed(FLEET& ships , float r )
{
  //fleet speed
  return kernel_.GetFleetSpeed(0 , ships) * r;
}

double WarSimulator::GetFleetOil(FLEET& ships , PlaniPos& selfpos , PlaniPos& targetpos , float r)
{
  assert(CheckPosValid(selfpos) && CheckPosValid(targetpos));
  if(GetFleetShipsNumber(ships) < 1)
  {
    return 0L;
  }
  return (double)kernel_.GetFuel(selfpos , targetpos , ships) * sqrt(r);
}

UINT WarSimulator::GeFleetFlySecond(FLEET& ships , PlaniPos& selfpos , PlaniPos& targetpos , float r)
{ 
  if(GetFleetShipsNumber(ships) < 1)
  {
    return 0L;
  }
  float seed = _speed_adjust_;

  UINT t = (UINT)(kernel_.ComputeFlyTime(selfpos , targetpos , 0 , ships) / r) / seed;//modify fleet speed
  if(t < 3) t = 3;
  return t;
}

double WarSimulator::GetFleetCapacity(FLEET& ships)
{
  double cnt = 0.0;
  for(int i = 0 ; i < ships.size() ; ++i)
  {
    cnt += (kernel_.GetShipCapacity(ships[i].Type) * ships[i].Num);
  }
  return cnt;
}

UINT WarSimulator::GetFleetShipsNumber(FLEET& ships)
{
  ULONG cnt = 0;
  for(int i = 0 ; i < ships.size() ; ++i)
  {
    cnt += UINT(ships[i].Num);
  }
  return cnt;
}

Resource WarSimulator::GetFleetWorth(FLEET& fleet)
{
  Res r;
  r = kernel_.GetFleetWorth(&fleet);
  Resource tmp;
  tmp.crystal_ = r.kris;
  tmp.metal_   = r.met;
  tmp.diplogen_ = r.deut;
  return tmp;
}