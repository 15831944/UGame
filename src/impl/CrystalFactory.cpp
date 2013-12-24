
#include "stdafx.h"
#include "xgame.h"
#include "CrystalFactory.h"

CrystalFactory::CrystalFactory(const CString& name  , const CString& des, int index , int level)
:Building(name , des ,  index , level)
{

}

CrystalFactory::~CrystalFactory()
{
  
}

////consume
//consume resource needed
double CrystalFactory::GetUpgradeMinal()
{  
  return get_produce_factory_upgrade_resource(FACTORY_DATA[FACTORY_BUILDING_CRYSTAL][FACTORY_TBL_N_METAL] , level_);
}

double CrystalFactory::GetUpgradeCrystal()
{
  return get_produce_factory_upgrade_resource(FACTORY_DATA[FACTORY_BUILDING_CRYSTAL][FACTORY_TBL_N_CRYSTAL] , level_);
}

double CrystalFactory::GetUpgradeDiplogen()
{
  return get_produce_factory_upgrade_resource(FACTORY_DATA[FACTORY_BUILDING_CRYSTAL][FACTORY_TBL_N_DIPLOGEN] , level_);
}

//total upgrade resource
double CrystalFactory::GetTotalUpgradeMinal()
{
  return 0L;
}
double CrystalFactory::GetTotalUpgradeCrystal() 
{
  return 0L;
}
double CrystalFactory::GetTotalUpgradeDiplogen()
{
  return 0L;
}

//consume Power
unsigned long CrystalFactory::GetConsumePower() 
{
  return get_produce_factory_consume_power(FACTORY_DATA[FACTORY_BUILDING_CRYSTAL][FACTORY_TBL_POWER] , level_ , self_produce_Percent_);
}

////produce
double CrystalFactory::ProduceMinal() 
{
  return get_produce_factory_produce_resource_per_minute(0 , FACTORY_DATA[FACTORY_BUILDING_CRYSTAL][FACTORY_TBL_P_METAL] , level_ ,
    self_produce_Percent_ , total_produce_Percent_) * pow(2 , data_->GET_STAR_DOUBLE_RES_HERO());
}

double CrystalFactory::ProduceCrystal() 
{
  return get_produce_factory_produce_resource_per_minute(10 , FACTORY_DATA[FACTORY_BUILDING_CRYSTAL][FACTORY_TBL_P_CRYSTAL] , level_ ,
    self_produce_Percent_ , total_produce_Percent_) * pow(2 , data_->GET_STAR_DOUBLE_RES_HERO());
}

double CrystalFactory::ProduceDiplogen() 
{
  return get_produce_factory_produce_resource_per_minute(0 , FACTORY_DATA[FACTORY_BUILDING_CRYSTAL][FACTORY_TBL_P_DIPLOGEN] , level_ ,
    self_produce_Percent_ , total_produce_Percent_) * (-0.002 * data_->STAR_TEMP() + 1.28 ) * pow(2 , data_->GET_STAR_DOUBLE_RES_HERO());
}

unsigned long CrystalFactory::ProducePower() 
{
  return 0L;
}

void CrystalFactory::SetProducePercent(double p)
{
  Building::SetProducePercent(p);
  data_->SetProductPercent(FACTORY_BUILDING_CRYSTAL , p);
}
