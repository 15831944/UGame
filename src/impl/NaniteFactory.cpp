
#include "stdafx.h"
#include "xgame.h"
#include "NaniteFactory.h"

NaniteFactory::NaniteFactory(const CString& name  , const CString& des, int index , int level)
:Building(name , des ,  index , level)
{

}

NaniteFactory::~NaniteFactory()
{

}

////consume
//consume resource needed
double NaniteFactory::GetUpgradeMinal()
{  
  return get_other_factory_upgrade_resource(FACTORY_DATA[FACTORY_BUILDING_NANITE][FACTORY_TBL_N_METAL] , level_);
}

double NaniteFactory::GetUpgradeCrystal()
{
  return get_other_factory_upgrade_resource(FACTORY_DATA[FACTORY_BUILDING_NANITE][FACTORY_TBL_N_CRYSTAL] , level_);
}
double NaniteFactory::GetUpgradeDiplogen()
{
  return get_other_factory_upgrade_resource(FACTORY_DATA[FACTORY_BUILDING_NANITE][FACTORY_TBL_N_DIPLOGEN] , level_);
}

//total upgrade resource
double NaniteFactory::GetTotalUpgradeMinal()
{
  return 0L;
}
double NaniteFactory::GetTotalUpgradeCrystal() 
{
  return 0L;
}
double NaniteFactory::GetTotalUpgradeDiplogen()
{
  return 0L;
}

//consume Power
unsigned long NaniteFactory::GetConsumePower() 
{
  return 0L;
}

////produce
double NaniteFactory::ProduceMinal() 
{
  return 0.0;
}
double NaniteFactory::ProduceCrystal() 
{
  return 0.0;
}
double NaniteFactory::ProduceDiplogen() 
{
  return 0.0;
}
unsigned long NaniteFactory::ProducePower() 
{
  return 0L;
}

bool NaniteFactory::CanLevelUp()
{
  //robot factory >= 2
  return Building::CanLevelUp() && data_->GetBuildingLevel(FACTORY_BUILDING_ROBOT) >= 10 && data_->GetResearchLevel(RESEARCH_COMPUTER) >= 10;
}
