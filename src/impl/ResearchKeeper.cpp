// ResearchKeeper.cpp: implementation of the ResearchKeeper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "xgame.h"
#include "ResearchKeeper.h"
#include "ResearchTechnics.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

ResearchKeeper::ResearchKeeper(GameData* d)
:data_(d)
{
  assert(data_ != NULL);
  CreateResearchs();
}

ResearchKeeper::~ResearchKeeper()
{
  for(int i = 0 ; i < entry_researchs_.size() ; ++i)
  {
    delete entry_researchs_[i];
  }
}

void ResearchKeeper::CreateResearchs()
{
  for(int i = RESEARCH_START ; i < RESEARCH_MAX ; ++i)
  {
    ResearchTechnics* res = new ResearchTechnics(RESEARCHS_NAME[i] , RESEARCHS_SIMPLE_DISP[i] , i , 0);
    res->SetDataPtr(data_);
    res->Load();
    entry_researchs_.push_back(res);
  }
}

ResearchTechnics* ResearchKeeper::GetResearch(int index)
{
  assert(index >= 0 && index < entry_researchs_.size());
  return entry_researchs_[index];
}