
#include "stdafx.h"
#include "xgame.h"
#include "SunpowerFactory.h"

SunpowerFactory::SunpowerFactory(const CString& name  , const CString& des, int index , int level)
:Building(name , des , index , level)
{

}

SunpowerFactory::~SunpowerFactory()
{

}

////consume
//consume resource needed
double SunpowerFactory::GetUpgradeMinal()
{  
  return get_produce_factory_upgrade_resource(FACTORY_DATA[FACTORY_BUILDING_SUNPOWER][FACTORY_TBL_N_METAL] , level_);
}

double SunpowerFactory::GetUpgradeCrystal()
{
  return get_produce_factory_upgrade_resource(FACTORY_DATA[FACTORY_BUILDING_SUNPOWER][FACTORY_TBL_N_CRYSTAL] , level_);
}

double SunpowerFactory::GetUpgradeDiplogen()
{
  return get_produce_factory_upgrade_resource(FACTORY_DATA[FACTORY_BUILDING_SUNPOWER][FACTORY_TBL_N_DIPLOGEN] , level_);
}

//total upgrade resource
double SunpowerFactory::GetTotalUpgradeMinal()
{
  return 0L;
}
double SunpowerFactory::GetTotalUpgradeCrystal() 
{
  return 0L;
}
double SunpowerFactory::GetTotalUpgradeDiplogen()
{
  return 0L;
}

//consume Power
unsigned long SunpowerFactory::GetConsumePower() 
{
  return 0;
}

////produce
double SunpowerFactory::ProduceMinal() 
{
  return 0;
}

double SunpowerFactory::ProduceCrystal() 
{
  return 0;
}

double SunpowerFactory::ProduceDiplogen() 
{
  return 0;
}

unsigned long SunpowerFactory::ProducePower() 
{
  return get_produce_factory_produce_power(FACTORY_DATA[FACTORY_BUILDING_SUNPOWER][FACTORY_TBL_P_POWER] , level_ , self_produce_Percent_);
}

void SunpowerFactory::SetProducePercent(double p)
{
  Building::SetProducePercent(p);
  data_->SetProductPercent(PRODUCT_SOLAR , p);
}