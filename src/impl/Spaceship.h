// Spaceship.h: interface for the Spaceship class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPACESHIP_H__BE9C6095_E508_4844_AA1A_04AC1D58EF70__INCLUDED_)
#define AFX_SPACESHIP_H__BE9C6095_E508_4844_AA1A_04AC1D58EF70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class GameData;
class Spaceship  
{
private:
  CString name_;
  CString desprition_;
  int index_;
  double produce_time_;

  GameData* data_;
  const static CString TECH_NEEDED_STRING[];

  int Ships_Number_;
  
public:
	Spaceship(const CString& name , const CString& des , int index);
	virtual ~Spaceship();

  CString GetName(){return name_;}
  void SetName(const CString& n){name_ = n;}

  int GetIndex(){return index_;}
  void SetIndex(int i){index_ = i;}

  CString GetSimpleDisp(){return desprition_;}

  bool CanProduce();
  void ProduceShips(int number);

  //consume resource needed
  double GetProduceMinal() ;
  double GetProduceCrystal() ;
  double GetProduceDiplogen() ;
  //time
  double GetProduceTime();
  //need
  const CString& GetTechNeeded();

  //save&load
  void Save();
  void Load();

  //
  int GetNumber();

  void SetDataPtr(GameData* d){data_ = d;}
};

#endif // !defined(AFX_SPACESHIP_H__BE9C6095_E508_4844_AA1A_04AC1D58EF70__INCLUDED_)
