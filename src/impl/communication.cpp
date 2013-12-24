#include "stdafx.h"
#include "xgame.h"
#include "communication.h"

#include "pagebuildings.h"
#include "pagepersoninfo.h"
#include "pageresource.h"
#include "pagegalaxy.h"
#include "pageresreachcenter.h"
#include "pageboatyard.h"
#include "pageinformation.h"
#include "pagecommander.h"
#include "pagedocuments.h"

#include "UStar.h"

//**************************************************//
//This class is for the communication of all pages
//**************************************************//

Communication::Communication()
{
  page_person_          = NULL;
  page_buildings_       = NULL;
  page_resource_        = NULL;
  page_galaxy_          = NULL;
  page_boatyard_        = NULL;
  page_reseach_center_  = NULL;
  page_information_     = NULL;
  page_commander_       = NULL;
  page_docs_            = NULL;
}

Communication::~Communication()
{

}

bool Communication::Spy(Star& star)
{
  return page_commander_->SpyFleetOut(star);
}

void Communication::PrepareAttack(int target_index)
{
  page_commander_->Prepare_Attack(target_index);
}

void Communication::PrepareRecycle(int target_index)
{
  page_commander_->Prepare_Recycle(target_index);
}

void Communication::AttackPlayer(Star& s)
{
  page_commander_->EnemyAttackComing(s);
}

void Communication::ReportSpyInfo(const Spy_info& spy_info)
{
  page_information_->ReportSpyInfo(spy_info);
}

void Communication::ReportWarInfo(const War_info& war_info)
{
  page_information_->ReportWarInfo(war_info);
}

void Communication::ReportFleetReach(const COMMAND_TASK& task)
{
  page_information_->ReportFleetReach(task);
}

void Communication::ReportRecycleInfo(const COMMAND_TASK& task)
{
  page_information_->ReportRecycleInfo(task);
}

void Communication::ReportTransferInfo(const COMMAND_TASK& task)
{
  page_information_->ReportTransferInfo(task);
}

void Communication::ReportColonyInfo(const COMMAND_TASK& task , bool bSucess)
{
  page_information_->ReportColonyInfo(task , bSucess);
}

Star& Communication::GetStar(int index)
{
  return page_galaxy_->GetStar(index);
}

ulong Communication::GetRefreshMinutes()
{
  return page_galaxy_->get_refresh_mimutes();
}

void  Communication::UpdateShowStarInfo()
{
  page_galaxy_->UpdateShowStarInfo();
}

vector<Sort_Table_t>& Communication::GetStarsTable()
{
  return page_galaxy_->GetStarTable();
}

void Communication::UpdateGalaxyRank()
{
  page_galaxy_->UpdateSortTable();
}

void Communication::DoneAttacking()
{
  page_galaxy_->DoneAttacking();
}

void Communication::ShowDocument(int first, int second)
{
  page_docs_->ShowDocument(first , second);
}

void Communication::ViewRank(PlaniPos pos , bool is_self)
{
  page_person_->ViewRank(pos , is_self);
}

void Communication::Initialize(
    CPagePersonInfo*     page_person,
    CPageBuildings*      page_buildings,
    CPageResource*       page_resource,
    CPageGalaxy*         page_galaxy,
    CPageBoatyard*       page_boatyard,
    CPageResreachCenter* page_reseach_center,
    CPageInformation*    page_information,
    CPageCommander*      page_commander,
    CPageDocuments*      page_docs)
{
  page_person_          = page_person;
  page_buildings_       = page_buildings;
  page_resource_        = page_resource;
  page_galaxy_          = page_galaxy;
  page_boatyard_        = page_boatyard;
  page_reseach_center_  = page_reseach_center;
  page_information_     = page_information;
  page_commander_       = page_commander;
  page_docs_            = page_docs;
}

ulong Communication::GetAllFleetNumber()
{
  return page_commander_->GetAllFleetNumber();
}