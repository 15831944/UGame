// DefensesKeeper.cpp: implementation of the DefensesKeeper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "xgame.h"
#include "DefensesKeeper.h"
#include "defense.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DefensesKeeper::DefensesKeeper(GameData* d)
:data_(d)
{
  assert(data_ != NULL);
  CreateDefenses();
}

DefensesKeeper::~DefensesKeeper()
{
  for(int i = 0 ; i < entry_defenses_.size() ; ++i)
  {
    delete entry_defenses_[i];
  }
}

void DefensesKeeper::CreateDefenses()
{
  for(int i = DEFENSE_START ; i < DEFENSE_MAX ; ++i)
  {
    Defense* ship = new Defense(DEFENSES_NAME[i] , DEFENSE_SIMPLE_DISP[i] , i);
    ship->SetDataPtr(data_);
    ship->Load();
    entry_defenses_.push_back(ship);
  }
}

Defense* DefensesKeeper::GetDefense(int index)
{
  assert(index >= 0 && index < entry_defenses_.size());
  return entry_defenses_[index];
}
