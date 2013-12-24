
#include "stdafx.h"
#include "xgame.h"
#include "LabFactory.h"

LabFactory::LabFactory(const CString& name  , const CString& des, int index , int level)
:Building(name , des ,  index , level)
{

}

LabFactory::~LabFactory()
{

}

////consume
//consume resource needed
double LabFactory::GetUpgradeMinal()
{  
  return get_other_factory_upgrade_resource(FACTORY_DATA[FACTORY_BUILDING_LAB][FACTORY_TBL_N_METAL] , level_);
}

double LabFactory::GetUpgradeCrystal()
{
  return get_other_factory_upgrade_resource(FACTORY_DATA[FACTORY_BUILDING_LAB][FACTORY_TBL_N_CRYSTAL] , level_);
}
double LabFactory::GetUpgradeDiplogen()
{
  return get_other_factory_upgrade_resource(FACTORY_DATA[FACTORY_BUILDING_LAB][FACTORY_TBL_N_DIPLOGEN] , level_);
}

//total upgrade resource
double LabFactory::GetTotalUpgradeMinal()
{
  return 0L;
}
double LabFactory::GetTotalUpgradeCrystal() 
{
  return 0L;
}
double LabFactory::GetTotalUpgradeDiplogen()
{
  return 0L;
}

//consume Power
unsigned long LabFactory::GetConsumePower() 
{
  return 0L;
}

////produce
double LabFactory::ProduceMinal() 
{
  return 0.0;
}
double LabFactory::ProduceCrystal() 
{
  return 0.0;
}
double LabFactory::ProduceDiplogen() 
{
  return 0.0;
}
unsigned long LabFactory::ProducePower() 
{
  return 0L;
}

