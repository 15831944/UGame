#include "stdafx.h"
#include "xgame.h"
#include "BuildFactory.h"

double BuildFactory::total_produce_Percent_ = 1.0;

BuildFactory::BuildFactory(uchar id , const CString& chs_name , const CString& eng_name , const CString& need , const CString& des, int level , double p_r , GameData* data)
: slef_id_(id) , chs_name_(chs_name) , eng_name_(eng_name) , need_(need) , description_(des) , level_(level) , produce_Percent_(p_r) , data_(data)
{

}

BuildFactory::~BuildFactory()
{

}

//upgrade resource
double BuildFactory::GetUpgradeMinal()
{
  return get_produce_factory_upgrade_resource(FACTORY_DATA[slef_id_][FACTORY_TBL_N_METAL] , level_);
}

double BuildFactory::GetUpgradeCrystal()
{
  return get_produce_factory_upgrade_resource(FACTORY_DATA[slef_id_][FACTORY_TBL_N_CRYSTAL] , level_);
}

double BuildFactory::GetUpgradeDiplogen()
{
  return get_produce_factory_upgrade_resource(FACTORY_DATA[slef_id_][FACTORY_TBL_N_DIPLOGEN] , level_);
}

//total upgrade resource
double BuildFactory::GetTotalUpgradeMinal()
{
  return 0L;
}
double BuildFactory::GetTotalUpgradeCrystal() 
{
  return 0L;
}
double BuildFactory::GetTotalUpgradeDiplogen()
{
  return 0L;
}

//consume Power
unsigned long BuildFactory::GetConsumePower() 
{
  return get_produce_factory_consume_power(FACTORY_DATA[slef_id_][FACTORY_TBL_POWER] , level_ , produce_Percent_);
}

////produce
double BuildFactory::ProduceMinalOneMinute() 
{
  return get_produce_factory_produce_resource_per_minute(0 , FACTORY_DATA[slef_id_][FACTORY_TBL_P_METAL] , level_ ,
    produce_Percent_ , total_produce_Percent_) * pow(2 , data_->GET_STAR_DOUBLE_RES_HERO());
}

double BuildFactory::ProduceCrystalOneMinute() 
{
  return get_produce_factory_produce_resource_per_minute(10 , FACTORY_DATA[slef_id_][FACTORY_TBL_P_CRYSTAL] , level_ ,
    produce_Percent_ , total_produce_Percent_) * pow(2 , data_->GET_STAR_DOUBLE_RES_HERO());
}

double BuildFactory::ProduceDiplogenOneMinute() 
{
  return get_produce_factory_produce_resource_per_minute(0 , FACTORY_DATA[slef_id_][FACTORY_TBL_P_DIPLOGEN] , level_ ,
    produce_Percent_ , total_produce_Percent_) * (-0.002 * data_->star_temp_high_ + 1.28 ) * pow(2 , data_->GET_STAR_DOUBLE_RES_HERO());
}

unsigned long BuildFactory::ProducePower() 
{
  return get_produce_factory_produce_power(FACTORY_DATA[slef_id_][FACTORY_TBL_P_POWER] , level_ , produce_Percent_);
}

//upgrade time, return is second
double BuildFactory::GetUpgradeSecond()
{
  upgrade_time_ = get_factory_upgrade_seconds(data_->GetRobertFactoryLevel() , data_->GetNaniteLevel() , GetUpgradeMinal() , GetUpgradeCrystal() , 1.0);
  return upgrade_time_;
}

//total percent
void BuildFactory::SetTotalProductPercent(double p)
{
  total_produce_Percent_ = p;
}

//self percent
void BuildFactory::SetProducePercent(double p)
{
  produce_Percent_ = p;
}