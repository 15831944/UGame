#include "stdafx.h"
#include "xgame.h"
#include "Building.h"

static const CString BUILDING_LEVEL_UP_STRING [] = 
{
  _T(""),
  _T(""),
  _T(""),
  _T(""),
  _T(""),
  _T(""),
  _T("机器人工厂：2"),
  _T("机器人工厂：10，电脑技术：10"),
};

double Building::total_produce_Percent_ = 0.0;

Building::Building(const CString& name  , const CString& des, int index , int level)
:name_(name) , description_(des) , index_(index) , level_(level) , data_(NULL) , self_produce_Percent_(0.0)
{
}

Building::~Building()
{
}

void Building::LevelUp()
{
  ++level_;
}

void Building::SetTotalProducePercent(double p)
{
  total_produce_Percent_ = p;
}

double Building::GetTotalProducePercent()
{
  return total_produce_Percent_;
}

bool Building::CanLevelUp()
{
  return data_->STAR_USED_SIZE() < data_->STAR_CIRU();
}

CString Building::GetCanlevelString()
{
  return BUILDING_LEVEL_UP_STRING[index_];
}

void Building::Load()
{
  level_ = data_->GetBuildingLevel(index_);
  if(index_ >= FACTORY_BUILDING_MINAL && index_ <= FACTORY_BUILDING_SUNPOWER)
    self_produce_Percent_ = data_->GetProductPercent(index_) / 100.0;
  else
    self_produce_Percent_ = 0.0;
}

void Building::Save() 
{
  data_->SetBuildingLevel(index_ , level_);
  if(index_ >= FACTORY_BUILDING_MINAL && index_ <= FACTORY_BUILDING_SUNPOWER)
    data_->SetProductPercent(index_ , self_produce_Percent_);
}

double Building::GetUpgradeTime()
{
  upgrade_time_ = get_factory_upgrade_seconds(data_->GetBuildingLevel(FACTORY_BUILDING_ROBOT) , data_->GetBuildingLevel(FACTORY_BUILDING_NANITE) , GetUpgradeMinal() , GetUpgradeCrystal() , 1.0);
  return upgrade_time_;
}