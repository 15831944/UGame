// ResearchTechnics.cpp: implementation of the ResearchTechnics class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "xgame.h"
#include "ResearchTechnics.h"
#include "GameDataRecorder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


const CString ResearchTechnics::TECH_NEEDED_STRING[] = 
{
  _T("实验研究室：3"),  //spy
  _T("实验研究室：1"),  //computer
  _T("实验研究室：4"),  //attack
  _T("实验研究室：6，能量技术：3"),  //sheiled
  _T("实验研究室：2"),  //defense
  _T("实验研究室：1"),  //power
  _T("实验研究室：7 ，能量技术：5，防护盾系统：5"),  //super tech
  _T("实验研究室：1 ，能量技术：1"),  //burning
  _T("实验研究室：2 ，能量技术：1"),  //pulse
  _T("实验研究室：7 ，超空间技术：3"),  //super space
  _T("实验研究室：4 ，能量技术：8"),  //plasm
  _T("实验研究室：12  能量：300000"),  //gravition
};

ResearchTechnics::ResearchTechnics(const CString& name , const CString& des , int index , int level)
: name_(name) , desprition_(des) , index_(index) , level_(level)
{
  assert(index_ >= RESEARCH_START && index_ < RESEARCH_MAX);
}

ResearchTechnics::~ResearchTechnics()
{
  
}

void ResearchTechnics::Load()
{
  level_ = data_->GetResearchLevel(index_);
}

void ResearchTechnics::Save()
{
  data_->SetResearchLevel(index_ , level_);
}

bool ResearchTechnics::CanLevelUp()
{
  int lab = data_->GetBuildingLevel(FACTORY_BUILDING_LAB);
  int energy = data_->GetResearchLevel(RESEARCH_POWER);
  int sheild = data_->GetResearchLevel(RESEARCH_SHEILED);
  int super = data_->GetResearchLevel(RESEARCH_SUPERTECH);
  ulong totalpower = data_->GetExistPower();

  switch(index_)
  {
  case RESEARCH_SPY:
    return lab >= 3;
  case RESEARCH_COMPUTER:
    return lab >= 1;
  case RESEARCH_WEAPON:
    return lab >= 4;
  case RESEARCH_SHEILED:
    return lab >= 6 && energy >= 3;
  case RESEARCH_ARMOUR:
    return lab >= 2 ;
  case RESEARCH_POWER:
    return lab >= 1;
  case RESEARCH_SUPERTECH:
    return lab >= 7 && energy >= 5 && sheild >= 5;
  case RESEARCH_BURNING:
    return lab >= 1 && energy >= 1;
  case RESEARCH_PULSE:
    return lab >= 2 && energy >= 1;
  case RESEARCH_SUPERSPACE:
    return lab >= 7 && super >= 3;
  case RESEARCH_PLASM:
    return lab >= 4 && energy >= 8;
  case RESEARCH_GRAVITION:
    return lab >= 12 && totalpower >= 300000 * (pow(3 , level_));
  default:
    assert(!"error research technics tag!");
    break;
  }
  return false;
}

ulong ResearchTechnics::GetUpgradeTime()
{
  upgrade_time_ = get_research_upgrade_seconds(data_->GetBuildingLevel(FACTORY_BUILDING_LAB) , data_->GetBuildingLevel(FACTORY_BUILDING_NANITE) ,  
    GetUpgradeMinal() , GetUpgradeCrystal() , 1.0);
  return upgrade_time_;
}

double ResearchTechnics::GetUpgradeMinal()
{
  return get_research_upgrade_resource(RESEARCH_RESOURCE_NEED_BASE[index_][0] , level_);
}

double ResearchTechnics::GetUpgradeCrystal()
{
  return get_research_upgrade_resource(RESEARCH_RESOURCE_NEED_BASE[index_][1] , level_);
}

double ResearchTechnics::GetUpgradeDiplogen() 
{
  return get_research_upgrade_resource(RESEARCH_RESOURCE_NEED_BASE[index_][2] , level_);

}

CString ResearchTechnics::GetTechNeeded()
{
  if(index_ == RESEARCH_GRAVITION)
  {
    CString s;
    s.Format("实验研究室：12  能量：%d" , ulong(300000 * pow(3 , level_)));
    return s;
  }
  return TECH_NEEDED_STRING[index_];
}
