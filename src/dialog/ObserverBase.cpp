#include "stdafx.h"
#include "xgame.h"
#include "ObserverBase.h"
#include "XGameDlg.h"
#include "BuildingsKeeper.h"
#include "ResearchKeeper.h"
#include "BoatsKeeper.h"
#include "DefensesKeeper.h"

ObserverBase::ObserverBase():data_(NULL) , parent_(NULL) , bWorking_(false) , tip_("")
{
}

ObserverBase::~ObserverBase()
{
}

GameData* ObserverBase::GetDataPtr()
{
  return data_;
}

CXGameDlg* ObserverBase::GetCommander()
{
  return parent_;
}

void ObserverBase::SetParentPtr(CXGameDlg* p)
{
  parent_ = p;
}

void ObserverBase::SetDataPtr(GameData* d)
{
  data_ = d;
}

void ObserverBase::SetBuildingsKeeper(BuildingsKeeper* k)
{
  building_keeper_ = k;
}

Building* ObserverBase::GetBuilding(int index)
{
  return building_keeper_->GetBuilding(index);
}

void ObserverBase::SetResearchsKeeper(ResearchKeeper* k)
{
  research_keeper_ = k;
}

ResearchTechnics* ObserverBase::GetResearch(int index)
{
  return research_keeper_->GetResearch(index);
}

void ObserverBase::SetBoatsKeeper(BoatsKeeper* k)
{
  boat_keeper_ = k;
}

Spaceship* ObserverBase::GetBoat(int index)
{
  return boat_keeper_->GetBoat(index);
}

void ObserverBase::SetDefensesKeeper(DefensesKeeper* k)
{
  defense_keeper_ = k;
}

Defense* ObserverBase::GetDefense(int index)
{
  return defense_keeper_->GetDefense(index);
}

void ObserverBase::SetCommPtr(Communication* p)
{
  comm_ = p;
}

void ObserverBase::Notify_Score_Changed()
{
  //nothing to do
}

void ObserverBase::Notify_Building_LevelUp()
{
  //nothing to do
}

void ObserverBase::Notify_Building_ProducePercent_Changed()
{
  //nothing to do
}

void ObserverBase::Notify_Resource_Changed()
{
  //nothing to do
}

void ObserverBase::Notify_Exit()
{
  //nothing to do
}

void ObserverBase::Notify_Technics_LevelUp()
{
  //nothing to do
}

void ObserverBase::Notify_Ships_Changed()
{
  //nothing to do
}

const CString& ObserverBase::GetTipInfo()
{
  return tip_;
}

void ObserverBase::Notify_Init()
{
  //nothing to do
}

void ObserverBase::Notify_Galaxy_Update()
{
  //nothing to do
}

void ObserverBase::Notify_Defense_Changed()
{
  //nothing to do
}