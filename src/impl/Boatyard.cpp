
#include "stdafx.h"
#include "xgame.h"
#include "Boatyard.h"

Boatyard::Boatyard(const CString& name  , const CString& des, int index , int level)
:Building(name , des ,  index , level)
{
}

Boatyard::~Boatyard()
{

}

////consume
//consume resource needed
double Boatyard::GetUpgradeMinal()
{  
  return get_other_factory_upgrade_resource(FACTORY_DATA[FACTORY_BUILDING_BOATYARD][FACTORY_TBL_N_METAL] , level_);
}

double Boatyard::GetUpgradeCrystal()
{
  return get_other_factory_upgrade_resource(FACTORY_DATA[FACTORY_BUILDING_BOATYARD][FACTORY_TBL_N_CRYSTAL] , level_);
}
double Boatyard::GetUpgradeDiplogen()
{
  return get_other_factory_upgrade_resource(FACTORY_DATA[FACTORY_BUILDING_BOATYARD][FACTORY_TBL_N_DIPLOGEN] , level_);
}

//total upgrade resource
double Boatyard::GetTotalUpgradeMinal()
{
  return 0L;
}
double Boatyard::GetTotalUpgradeCrystal() 
{
  return 0L;
}
double Boatyard::GetTotalUpgradeDiplogen()
{
  return 0L;
}

//consume Power
unsigned long Boatyard::GetConsumePower() 
{
  return 0L;
}

////produce
double Boatyard::ProduceMinal() 
{
  return 0.0;
}
double Boatyard::ProduceCrystal() 
{
  return 0.0;
}
double Boatyard::ProduceDiplogen() 
{
  return 0.0;
}
unsigned long Boatyard::ProducePower() 
{
  return 0L;
}

bool Boatyard::CanLevelUp()
{
  //robot factory >= 2
  return Building::CanLevelUp() && data_->GetBuildingLevel(FACTORY_BUILDING_ROBOT) >= 2;
}
