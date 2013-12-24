// BuildingsKeeper.cpp: implementation of the BuildingsKeeper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "xgame.h"
#include "BuildingsKeeper.h"

#include "MetalFactory.h"
#include "DiplogenFactory.h"
#include "CrystalFactory.h"
#include "SunPowerFactory.h"
#include "RobotFactory.h"
#include "LabFactory.h"
#include "Boatyard.h"
#include "NaniteFactory.h"

BuildingsKeeper::BuildingsKeeper(GameData* d)
:data_(d)
{
  assert(data_ != NULL);
  CreateBuildings();
}

BuildingsKeeper::~BuildingsKeeper()
{
  for(int i = 0 ; i < entry_buildings_.size() ; ++i)
  {
    delete entry_buildings_[i];
  }
}

void BuildingsKeeper::CreateBuildings()
{
  Building* metal = new MetalFactory(FACTORY_BUILDS_NAME[0] ,   FACTORY_BUILDS_SIMPLE_DISP[0] , FACTORY_BUILDING_MINAL , 0);
  Building* cry   = new CrystalFactory(FACTORY_BUILDS_NAME[1] , FACTORY_BUILDS_SIMPLE_DISP[1] , FACTORY_BUILDING_CRYSTAL , 0);
  Building* dip   = new DiplogenFactory(FACTORY_BUILDS_NAME[2] ,FACTORY_BUILDS_SIMPLE_DISP[2] , FACTORY_BUILDING_DIPLOGEN , 0);
  Building* power = new SunpowerFactory(FACTORY_BUILDS_NAME[3] ,FACTORY_BUILDS_SIMPLE_DISP[3] , FACTORY_BUILDING_SUNPOWER , 0);
  Building* robot = new RobotFactory(FACTORY_BUILDS_NAME[4] ,FACTORY_BUILDS_SIMPLE_DISP[4] , FACTORY_BUILDING_ROBOT , 0);
  Building* lab   = new LabFactory(FACTORY_BUILDS_NAME[5] ,FACTORY_BUILDS_SIMPLE_DISP[5] , FACTORY_BUILDING_LAB , 0);
  Building* boat  = new Boatyard(FACTORY_BUILDS_NAME[6] ,FACTORY_BUILDS_SIMPLE_DISP[6] , FACTORY_BUILDING_BOATYARD , 0);  
  Building* nanite= new NaniteFactory(FACTORY_BUILDS_NAME[7] ,FACTORY_BUILDS_SIMPLE_DISP[7] , FACTORY_BUILDING_NANITE , 0);  


  entry_buildings_.push_back(metal);
  entry_buildings_.push_back(cry);
  entry_buildings_.push_back(dip);
  entry_buildings_.push_back(power); 
  entry_buildings_.push_back(robot); 
  entry_buildings_.push_back(lab); 
  entry_buildings_.push_back(boat); 
  entry_buildings_.push_back(nanite); 

  assert(data_ != NULL);
  for(int i = 0 ; i < entry_buildings_.size() ; ++i)
  {
    entry_buildings_[i]->SetDataPtr(data_);
    entry_buildings_[i]->Load();
  }
}

void BuildingsKeeper::SetProductPercent(int index , double percent)
{
  assert(index >= 0 && index < entry_buildings_.size());
  entry_buildings_[index]->SetProducePercent(percent);
}

Building* BuildingsKeeper::GetBuilding(int index)
{
  assert(index >= 0 && index < entry_buildings_.size());
  return entry_buildings_[index];
}

void BuildingsKeeper::SetTotalPercent()
{
  int consume_power = 0;
  int exist_power   = 0;
  for(int i = 0 ; i < entry_buildings_.size() ; ++i)
  {
    consume_power += entry_buildings_[i]->GetConsumePower();
    exist_power   += entry_buildings_[i]->ProducePower();
  }
  //adjust for sun power planet's power
  exist_power += data_->GetBoatNumber(BOAT_SUNPOWER_PLANET) * (20 + data_->STAR_TEMP() / 4.0);

  double p = 0.0;
  if(exist_power == 0){
    p = 0.0;
  }
  else if(exist_power >= consume_power){
    p = 1.0;
  }
  else{
    p = exist_power * 1.0 / consume_power;
  }
  data_->SetExistPower(exist_power);
  data_->SetConsumePower(consume_power);
  data_->SetTotalProducePercent(p);
  Building::SetTotalProducePercent(p);
}