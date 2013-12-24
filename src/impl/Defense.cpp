// Defense.cpp: implementation of the Defense class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "xgame.h"
#include "Defense.h"
#include "GameDataRecorder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const CString Defense::TECH_NEEDED_STRING[] = 
{
  _T("造船厂：1"),                 //MISS
  _T("造船厂：2，能量技术：1"), //slaser
  _T("造船厂：4，能量技术：3"), //hlaser
  _T("造船厂：6，能量技术：6，武器技术：3，防御盾系统：1"),  //gauss
  _T("造船厂：4，能量技术：8"),   //icon
  _T("造船厂：8，等离子技术：7"),  //pc
};


Defense::Defense(const CString& name , const CString& des , int index)
: name_(name) , desprition_(des) , index_(index) , data_(NULL)
{
  assert(index_ >= DEFENSE_START && index_ < DEFENSE_MAX);
}

Defense::~Defense()
{

}

bool Defense::CanProduce()
{
  int boatyard = data_->GetBuildingLevel(FACTORY_BUILDING_BOATYARD);
  int weapon = data_->GetResearchLevel(RESEARCH_WEAPON);
  int power = data_->GetResearchLevel(RESEARCH_POWER);
  int plasm = data_->GetResearchLevel(RESEARCH_PLASM);
  int shield = data_->GetResearchLevel(RESEARCH_SHEILED);

  switch(index_)
  {
  case DEFENSE_MISS:
    return boatyard >= 1;
  case DEFENSE_SLASER:
    return boatyard >= 2 && power >= 1;
  case DEFENSE_HLASER:
    return boatyard >= 4 && power >= 3;
  case DEFENSE_GAUSS:
    return boatyard >= 6 && power >= 6 && weapon >= 3 && shield >= 1;
  case DEFENSE_ICON:
    return boatyard >= 4 && power >= 8;
  case DEFENSE_PC:
    return boatyard >= 8 && plasm >= 7;
  default:
    assert(!"error boats tag!");
    break;
  }
  return false;
}

double Defense::GetProduceTime()
{
  produce_time_ = get_boat_produce_seconds(data_->GetBuildingLevel(FACTORY_BUILDING_BOATYARD) , data_->GetBuildingLevel(FACTORY_BUILDING_NANITE) , 
    GetProduceMinal() , GetProduceCrystal() , 1.0);
  return produce_time_;
}

double Defense::GetProduceMinal()
{
  return DEFENSES_RESOURCE_NEED_BASE[index_][0] ;
}

double Defense::GetProduceCrystal()
{
  return DEFENSES_RESOURCE_NEED_BASE[index_][1]  ;
}

double Defense::GetProduceDiplogen() 
{
  return DEFENSES_RESOURCE_NEED_BASE[index_][2]  ;
}

const CString& Defense::GetTechNeeded()
{
  return TECH_NEEDED_STRING[index_];
}

void Defense::ProduceDefenses(int number)
{
  Defenses_Number_ += number;
  data_->SET_STAR_DEFENSE(index_ , data_->GET_STAR_DEFENSE(index_) + number);
}

void Defense::Save()
{
  data_->SET_STAR_DEFENSE(index_, Defenses_Number_); 
}

void Defense::Load()
{
  Defenses_Number_ = data_->GET_STAR_DEFENSE(index_); 
}

int Defense::GetNumber()
{
  Defenses_Number_ = data_->GET_STAR_DEFENSE(index_); 
  return Defenses_Number_;
}