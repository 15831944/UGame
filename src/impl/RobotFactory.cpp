
#include "stdafx.h"
#include "xgame.h"
#include "RobotFactory.h"

RobotFactory::RobotFactory(const CString& name  , const CString& des, int index , int level)
:Building(name , des ,  index , level)
{

}

RobotFactory::~RobotFactory()
{

}

////consume
//consume resource needed
double RobotFactory::GetUpgradeMinal()
{  
  return get_other_factory_upgrade_resource(FACTORY_DATA[FACTORY_BUILDING_ROBOT][FACTORY_TBL_N_METAL] , level_);
}

double RobotFactory::GetUpgradeCrystal()
{
  return get_other_factory_upgrade_resource(FACTORY_DATA[FACTORY_BUILDING_ROBOT][FACTORY_TBL_N_CRYSTAL] , level_);
}
double RobotFactory::GetUpgradeDiplogen()
{
  return get_other_factory_upgrade_resource(FACTORY_DATA[FACTORY_BUILDING_ROBOT][FACTORY_TBL_N_DIPLOGEN] , level_);
}

//total upgrade resource
double RobotFactory::GetTotalUpgradeMinal()
{
  return 0L;
}
double RobotFactory::GetTotalUpgradeCrystal() 
{
  return 0L;
}
double RobotFactory::GetTotalUpgradeDiplogen()
{
  return 0L;
}

//consume Power
unsigned long RobotFactory::GetConsumePower() 
{
  return 0L;
}

////produce
double RobotFactory::ProduceMinal() 
{
  return 0.0;
}
double RobotFactory::ProduceCrystal() 
{
  return 0.0;
}
double RobotFactory::ProduceDiplogen() 
{
  return 0.0;
}
unsigned long RobotFactory::ProducePower() 
{
  return 0L;
}
