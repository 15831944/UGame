// BoatsKeeper.cpp: implementation of the BoatsKeeper class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "xgame.h"
#include "BoatsKeeper.h"
#include "Spaceship.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BoatsKeeper::BoatsKeeper(GameData* d)
:data_(d)
{
  assert(data_ != NULL);
  CreateBoats();
}

BoatsKeeper::~BoatsKeeper()
{
  for(int i = 0 ; i < entry_boats_.size() ; ++i)
  {
    delete entry_boats_[i];
  }
}

void BoatsKeeper::CreateBoats()
{
  for(int i = BOAT_START ; i < BOAT_MAX ; ++i)
  {
    Spaceship* ship = new Spaceship(BOATS_NAME[i] , BOATS_SIMPLE_DISP[i] , i);
    ship->SetDataPtr(data_);
    ship->Load();
    entry_boats_.push_back(ship);
  }
}

Spaceship* BoatsKeeper::GetBoat(int index)
{
  assert(index >= 0 && index < entry_boats_.size());
  return entry_boats_[index];
}
