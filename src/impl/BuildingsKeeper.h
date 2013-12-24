// BuildingsKeeper.h: interface for the BuildingsKeeper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BUILDINGSKEEPER_H__DAFE2AFC_53A5_4D28_89AB_4681638F3022__INCLUDED_)
#define AFX_BUILDINGSKEEPER_H__DAFE2AFC_53A5_4D28_89AB_4681638F3022__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Building;

class BuildingsKeeper  
{
private:
  std::vector<Building*> entry_buildings_;
  GameData* data_;

public:
	BuildingsKeeper(GameData* d);
	~BuildingsKeeper();
  void CreateBuildings();
  Building* GetBuilding(int index);
  int Size() {return entry_buildings_.size();}

  void SetProductPercent(int index , double percent);
  void SetTotalPercent();
  
};

#endif // !defined(AFX_BUILDINGSKEEPER_H__DAFE2AFC_53A5_4D28_89AB_4681638F3022__INCLUDED_)
