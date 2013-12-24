
#include "stdafx.h"
#include "xgame.h"
#include "MetalFactory.h"

MetalFactory::MetalFactory(const CString& name  , const CString& des, int index , int level)
:Building(name , des ,  index , level)
{

}

MetalFactory::~MetalFactory()
{

}

////consume
//consume resource needed
double MetalFactory::GetUpgradeMinal()
{  
  return get_produce_factory_upgrade_resource(FACTORY_DATA[FACTORY_BUILDING_MINAL][FACTORY_TBL_N_METAL] , level_);
}

double MetalFactory::GetUpgradeCrystal()
{
  return get_produce_factory_upgrade_resource(FACTORY_DATA[FACTORY_BUILDING_MINAL][FACTORY_TBL_N_CRYSTAL] , level_);
}

double MetalFactory::GetUpgradeDiplogen()
{
  return get_produce_factory_upgrade_resource(FACTORY_DATA[FACTORY_BUILDING_MINAL][FACTORY_TBL_N_DIPLOGEN] , level_);
}

//total upgrade resource
double MetalFactory::GetTotalUpgradeMinal()
{
  return 0L;
}
double MetalFactory::GetTotalUpgradeCrystal() 
{
  return 0L;
}
double MetalFactory::GetTotalUpgradeDiplogen()
{
  return 0L;
}

//consume Power
unsigned long MetalFactory::GetConsumePower() 
{
  return get_produce_factory_consume_power(FACTORY_DATA[FACTORY_BUILDING_MINAL][FACTORY_TBL_POWER] , level_ , self_produce_Percent_);
}

////produce
double MetalFactory::ProduceMinal() 
{
  return get_produce_factory_produce_resource_per_minute(20 , FACTORY_DATA[FACTORY_BUILDING_MINAL][FACTORY_TBL_P_METAL] , level_ ,
    self_produce_Percent_ , total_produce_Percent_) * pow(2 , data_->GET_STAR_DOUBLE_RES_HERO());
}

double MetalFactory::ProduceCrystal() 
{
  return get_produce_factory_produce_resource_per_minute(0 , FACTORY_DATA[FACTORY_BUILDING_MINAL][FACTORY_TBL_P_CRYSTAL] , level_ ,
    self_produce_Percent_ , total_produce_Percent_) * pow(2 , data_->GET_STAR_DOUBLE_RES_HERO());
}

double MetalFactory::ProduceDiplogen() 
{
  return get_produce_factory_produce_resource_per_minute(0 , FACTORY_DATA[FACTORY_BUILDING_MINAL][FACTORY_TBL_P_DIPLOGEN] , level_ ,
    self_produce_Percent_ , total_produce_Percent_)  * (-0.002 * data_->STAR_TEMP() + 1.28 ) * pow(2 , data_->GET_STAR_DOUBLE_RES_HERO());
}

unsigned long MetalFactory::ProducePower() 
{
  return 0L;
}

void MetalFactory::SetProducePercent(double p)
{
  Building::SetProducePercent(p);
  data_->SetProductPercent(FACTORY_BUILDING_MINAL , p);
}