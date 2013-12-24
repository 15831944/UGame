// Defense.h: interface for the Defense class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DEFENSES_H_)
#define _DEFENSES_H_

class GameData;
class Defense  
{
private:
  CString name_;
  CString desprition_;
  int index_;
  double produce_time_;

  GameData* data_;
  const static CString TECH_NEEDED_STRING[];

  int Defenses_Number_;
  
public:
	Defense(const CString& name , const CString& des , int index);
	virtual ~Defense();

  CString GetName(){return name_;}
  void SetName(const CString& n){name_ = n;}

  int GetIndex(){return index_;}
  void SetIndex(int i){index_ = i;}

  CString GetSimpleDisp(){return desprition_;}

  bool CanProduce();
  void ProduceDefenses(int number);

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

#endif // !defined(_DEFENSES_H_)
