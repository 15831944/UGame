#ifndef _BULIDFACTORY_H_
#define _BULIDFACTORY_H_

class GameData;
class BuildFactory  
{
public:
	BuildFactory(uchar id , const CString& chs_name , const CString& eng_name , const CString& need , const CString& des, int level , double p_r , GameData* data);
	virtual ~BuildFactory();

  ////consume
  //consume resource needed
  double GetUpgradeMinal();
  double GetUpgradeCrystal();
  double GetUpgradeDiplogen();

  //total upgrade resource
  double GetTotalUpgradeMinal();
  double GetTotalUpgradeCrystal();
  double GetTotalUpgradeDiplogen(); 
  
  //consume Power
  unsigned long GetConsumePower();

  ////produce
  double        ProduceMinalOneMinute();
  double        ProduceCrystalOneMinute();
  double        ProduceDiplogenOneMinute();
  unsigned long ProducePower();

  //Upgrade time
  double GetUpgradeSecond();

  //set self product percent
  void SetProducePercent(double p);

  //set total product percent
  static void SetTotalProductPercent(double p);

private:
  uchar      slef_id_;
  CString    chs_name_;
  CString    eng_name_;
  CString    need_;
  CString    description_;
  int        level_;
  double     produce_Percent_;
  double     upgrade_time_;
  GameData*  data_;

  static     double total_produce_Percent_;
};

#endif // !defined(_BULIDFACTORY_H_)
