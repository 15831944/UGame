

#include "stdafx.h"
#include "xgame.h"
#include "FactoryBuilding.h"

//consume
const int FactoryBuilding::UPGRADE_MINAL_TBL[] =
{
  60, 48 , 225 , 75
};

const int FactoryBuilding::UPGRADE_CRYSTAL_TBL[] =
{
  15, 24 , 75 , 30
};

const int FactoryBuilding::UPGRADE_DIPLOGEN_TBL[] =
{
  0, 0 , 0 , 0
};

const int FactoryBuilding::CONSUME_POWER_TBL[] =
{
  10, 10 , 20 , 0
};

//produce
const int FactoryBuilding::PRODUCE_MINAL_TBL[] =
{
  30, 0 , 0 , 0
};

const int FactoryBuilding::PRODUCE_CRYSTAL_TBL[] =
{
  0, 20 , 0 , 0
};

const int FactoryBuilding::PRODUCE_DIPLOGEN_TBL[] =
{
  0, 0 , 10 , 0
};

const int FactoryBuilding::PRODUCE_POWER_TBL[] =
{
  0, 0 , 0 , 20
};

FactoryBuilding::FactoryBuilding(const CString& name , int index , int level)
:Building(name , index , level)
{
  assert(index >= 0 && index < FACTORY_BUILDINGS_MAX);
}

FactoryBuilding::~FactoryBuilding()
{

}

//consume power
unsigned long FactoryBuilding::GetConsumePower()
{  
  return CONSUME_POWER_TBL[index_] * GetLevel() * pow(1.1 , GetLevel());
}

//upgrade resource needed
unsigned long FactoryBuilding::GetUpgradeMinal()
{
  return UPGRADE_MINAL_TBL[index_] * pow(1.5 , GetLevel() - 1);
}

unsigned long FactoryBuilding::GetUpgradeCrystal()
{
  return UPGRADE_CRYSTAL_TBL[index_] * pow(1.5 , GetLevel() - 1);
}

unsigned long FactoryBuilding::GetUpgradeDiplogen()
{
  return UPGRADE_DIPLOGEN_TBL[index_] * pow(1.5 , GetLevel() - 1);
}

//total upgrade resource
unsigned long FactoryBuilding::GetTotalUpgradeMinal()
{
  return 0L;
}

unsigned long FactoryBuilding::GetTotalUpgradeCrystal()
{
  return 0L;
}
unsigned long FactoryBuilding::GetTotalUpgradeDiplogen()
{
  return 0L;
}

//produce
unsigned long FactoryBuilding::PrudeceMinal()
{
  return PRODUCE_MINAL_TBL[index_] * GetLevel() * pow(1.1 , GetLevel());
}

unsigned long FactoryBuilding::PrudeceCrystal()
{
  return PRODUCE_CRYSTAL_TBL[index_] * GetLevel() * pow(1.1 , GetLevel());
}

unsigned long FactoryBuilding::PrudeceDiplogen()
{
  return PRODUCE_DIPLOGEN_TBL[index_] * GetLevel() * pow(1.1 , GetLevel());
}

unsigned long FactoryBuilding::PrudecePower()
{
  return PRODUCE_POWER_TBL[index_] * GetLevel() * pow(1.1 , GetLevel());
}
