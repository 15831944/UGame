// Spaceship.cpp: implementation of the Spaceship class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "xgame.h"
#include "Spaceship.h"
#include "GameDataRecorder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const CString Spaceship::TECH_NEEDED_STRING[] = 
{
  _T("�촬����2��ȼ�����棺2"),                 //Small Cargo Ship
  _T("�촬����4��ȼ�����棺6"),                 //large Cargo Ship
  _T("�촬����1��ȼ�����棺1"),                 //light fighter
  _T("�촬����3������װ�׻���2���������棺2"),  //heavy fighter

  _T("�촬����5���������棺4"),    //Cruiser
  _T("�촬����7�����ռ����棺4"),  //Battleship

  _T("�촬����4���������棺3"),    //CONOLY
  _T("�촬����4��ȼ�����棺6��������ϵͳ��2"),    //recycle

  _T("�촬����3��ȼ�����棺3 �����������2"),  //Espionage Probe
  _T("�촬����8���������棺6�������Ӽ�����5"),   //BOMBER
  _T("�촬����1"),    //Solar Satellite

  _T("�촬����9�� ���ռ����棺6�����ռ�Ƽ���5"),   //destroyer
  _T("�촬����12�����ռ����棺7�����ռ�Ƽ���6��������1"),   //ds

};

Spaceship::Spaceship(const CString& name , const CString& des , int index)
: name_(name) , desprition_(des) , index_(index) , data_(NULL)
{
  assert(index_ >= BOAT_START && index_ < BOAT_MAX);
}

Spaceship::~Spaceship()
{

}

bool Spaceship::CanProduce()
{
  int boatyard = data_->GetBuildingLevel(FACTORY_BUILDING_BOATYARD);
  int burning  = data_->GetResearchLevel(RESEARCH_BURNING);
  int weapon = data_->GetResearchLevel(RESEARCH_WEAPON);
  int pulse = data_->GetResearchLevel(RESEARCH_PULSE);
  int power = data_->GetResearchLevel(RESEARCH_POWER);
  int supertech = data_->GetResearchLevel(RESEARCH_SUPERTECH);
  int supersapce = data_->GetResearchLevel(RESEARCH_SUPERSPACE);
  int spy = data_->GetResearchLevel(RESEARCH_SPY);
  int gravition = data_->GetResearchLevel(RESEARCH_GRAVITION);
  int armour = data_->GetResearchLevel(RESEARCH_ARMOUR);
  int plasm = data_->GetResearchLevel(RESEARCH_PLASM);
  int shield = data_->GetResearchLevel(RESEARCH_SHEILED);

  switch(index_)
  {
  case BOAT_SMALL_SCUTTER:
    return boatyard >= 2 && burning >= 2;
  case BOAT_LARGE_SCUTTER:
    return boatyard >= 4 && burning >= 6;
  case BOAT_LIGHT_FIGHTER:
    return boatyard >= 1 && burning >= 1;
  case BOAT_HEAVY_FIGHTER:
    return boatyard >= 3 && armour >= 2 && pulse >= 2;
  case BOAT_CRUISER:
    return boatyard >= 5 && pulse >= 4;
  case BOAT_WARSHIP:
    return boatyard >= 7 && supersapce >= 4;
  case BOAT_CONOLY:  
    return boatyard >= 4 && pulse >= 3;
  case BOAT_RECYCLE:
    return boatyard >= 4 && burning >= 6 && shield >= 2;
  case BOAT_SPY_PLANET:
    return boatyard >= 3 && burning >=3 && spy >= 2;
  case BOAT_BOMBER:
    return boatyard >= 8 && pulse >=6 && plasm >= 5;
  case BOAT_SUNPOWER_PLANET:
    return boatyard >= 1;
  case BOAT_DESTROYER:
    return boatyard >= 9 && supersapce >=6 && supertech >= 5;
  case BOAT_DS:
    return boatyard >= 12 && supersapce >=7 && supertech >= 6 && gravition >= 1;
  default:
    assert(!"error boats tag!");
    break;
  }
  return false;
}

double Spaceship::GetProduceTime()
{
  produce_time_ = get_boat_produce_seconds(data_->GetBuildingLevel(FACTORY_BUILDING_BOATYARD) , data_->GetBuildingLevel(FACTORY_BUILDING_NANITE) , 
    GetProduceMinal() , GetProduceCrystal() , 1.0);
  return produce_time_;
}

double Spaceship::GetProduceMinal()
{
  return BOATS_RESOURCE_NEED_BASE[index_][0] ;
}

double Spaceship::GetProduceCrystal()
{
  return BOATS_RESOURCE_NEED_BASE[index_][1]  ;
}

double Spaceship::GetProduceDiplogen() 
{
  return BOATS_RESOURCE_NEED_BASE[index_][2]  ;
}

const CString& Spaceship::GetTechNeeded()
{
  return TECH_NEEDED_STRING[index_];
}

void Spaceship::ProduceShips(int number)
{
  Ships_Number_ += number;
  data_->SetBoatNumber(index_ , data_->GetBoatNumber(index_) + number); 
}

void Spaceship::Save()
{
  data_->SetBoatNumber(index_, Ships_Number_); 
}

void Spaceship::Load()
{
  Ships_Number_ = data_->GetBoatNumber(index_); 
}

int Spaceship::GetNumber()
{
  Ships_Number_ = data_->GetBoatNumber(index_); 
  return Ships_Number_;
}