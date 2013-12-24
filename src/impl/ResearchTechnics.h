// ResearchTechnics.h: interface for the ResearchTechnics class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RESEARCHTECHNICS_H__C2BE568C_1909_4D58_8A25_C65BF5BE2372__INCLUDED_)
#define AFX_RESEARCHTECHNICS_H__C2BE568C_1909_4D58_8A25_C65BF5BE2372__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class GameData;

class ResearchTechnics  
{
private:
  CString name_;
  CString desprition_;
  int index_;
  int level_;
  unsigned long upgrade_time_;

  GameData* data_;
  const static CString TECH_NEEDED_STRING[];

public:
	ResearchTechnics(const CString& name , const CString& des , int index , int level);
	virtual ~ResearchTechnics();

  CString GetName(){return name_;}
  void SetName(const CString& n){name_ = n;}

  int GetIndex(){return index_;}
  void SetIndex(int i){index_ = i;}

  CString GetSimpleDisp(){return desprition_;}

  int GetLevel(){return level_;}
  void SetLevel(int l){level_ = l;}
  bool CanLevelUp();
  void LevelUp(){++level_;}


  //consume resource needed
  double GetUpgradeMinal() ;
  double GetUpgradeCrystal() ;
  double GetUpgradeDiplogen() ;
  //time
  ulong GetUpgradeTime();
  //need
  CString GetTechNeeded();

  void SetDataPtr(GameData* d){data_ = d;}

  void Load();
  void Save();

};

#endif // !defined(AFX_RESEARCHTECHNICS_H__C2BE568C_1909_4D58_8A25_C65BF5BE2372__INCLUDED_)
