
#include "stdafx.h"
#include "xgame.h"
#include "ProduceImproveCenter.h"

ProduceImproveCenter::ProduceImproveCenter(const CString& name  , const CString& des, int index , int level)
:Building(name , des ,  index , level)
{

}

ProduceImproveCenter::~ProduceImproveCenter()
{

}

void ProduceImproveCenter::Load()
{
  level_ = data_->GetBoatyardLevel();
  self_produce_Percent_ = 0.0;
}

void ProduceImproveCenter::Save()
{
  data_->SetBoatyardLevel(level_);
}

////consume
//consume resource needed
double ProduceImproveCenter::GetUpgradeMinal()
{  
  return get_other_factory_upgrade_resource(FACTORY_DATA[FACTORY_BUILDING_BOATYARD][FACTORY_TBL_N_METAL] , level_);
}

double ProduceImproveCenter::GetUpgradeCrystal()
{
  return get_other_factory_upgrade_resource(FACTORY_DATA[FACTORY_BUILDING_BOATYARD][FACTORY_TBL_N_CRYSTAL] , level_);
}
double ProduceImproveCenter::GetUpgradeDiplogen()
{
  return get_other_factory_upgrade_resource(FACTORY_DATA[FACTORY_BUILDING_BOATYARD][FACTORY_TBL_N_DIPLOGEN] , level_);
}

//total upgrade resource
double ProduceImproveCenter::GetTotalUpgradeMinal()
{
  return 0L;
}
double ProduceImproveCenter::GetTotalUpgradeCrystal() 
{
  return 0L;
}
double ProduceImproveCenter::GetTotalUpgradeDiplogen()
{
  return 0L;
}

//consume Power
unsigned long ProduceImproveCenter::GetConsumePower() 
{
  return 0L;
}

////produce
double ProduceImproveCenter::ProduceMinal() 
{
  return 0.0;
}
double ProduceImproveCenter::ProduceCrystal() 
{
  return 0.0;
}
double ProduceImproveCenter::ProduceDiplogen() 
{
  return 0.0;
}
unsigned long ProduceImproveCenter::ProducePower() 
{
  return 0L;
}

double ProduceImproveCenter::GetUpgradeTime()
{
  upgrade_time_ = get_factory_upgrade_seconds(data_->GetRobertFactoryLevel() , data_->GetNaniteLevel() , GetUpgradeMinal() , GetUpgradeCrystal() , 1.0);
  return upgrade_time_;
}

bool ProduceImproveCenter::CanLevelUp()
{
  //robot factory >= 2
  return data_->GetRobertFactoryLevel() >= 2;
}
