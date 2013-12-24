
#if !defined(AFX_BUILDING_H__38007F73_D49D_4CAD_9359_369C70D7594A__INCLUDED_)
#define AFX_BUILDING_H__38007F73_D49D_4CAD_9359_369C70D7594A__INCLUDED_

#include "GameDataRecorder.h"

class Building  
{
protected:
  CString        name_;
  CString        description_;
  unsigned short index_;
  int            level_;
  double         self_produce_Percent_;
  double          upgrade_time_;
  static double  total_produce_Percent_;

  GameData*      data_;
public:
	Building(const CString& name , const CString& des, int index , int level);
	virtual ~Building() = 0;

  ////consume
  //consume resource needed
  virtual double GetUpgradeMinal() = 0;
  virtual double GetUpgradeCrystal() = 0;
  virtual double GetUpgradeDiplogen() = 0;  

  //total upgrade resource
  virtual double GetTotalUpgradeMinal() = 0;
  virtual double GetTotalUpgradeCrystal() = 0;
  virtual double GetTotalUpgradeDiplogen() = 0;

  //consume Power
  virtual unsigned long GetConsumePower() = 0;

  ////produce
  virtual double        ProduceMinal() = 0;
  virtual double        ProduceCrystal() = 0;
  virtual double        ProduceDiplogen() = 0;
  virtual unsigned long ProducePower() = 0;

  //upgrade time
  double GetUpgradeTime();

  //save & load object
  void Load() ;
  void Save() ;

  //level up
  virtual bool CanLevelUp();
  void LevelUp();  

  //gets
  CString GetName() {return name_;}
  int GetIndex()    {return index_;}
  int GetLevel()    {return level_;}
  CString GetSimpleDisp(){return description_;}
  void SetDataPtr(GameData* d){data_ = d;}

  //self percent
  virtual void SetProducePercent(double p){self_produce_Percent_ = p;}
  double GetProducePercent(){ return self_produce_Percent_;}
  
  //
  CString GetCanlevelString();

  //total percent
  static void SetTotalProducePercent(double p);
  static double GetTotalProducePercent();
};

#endif // !defined(AFX_BUILDING_H__38007F73_D49D_4CAD_9359_369C70D7594A__INCLUDED_)
