// FactoryBuilding.h: interface for the FactoryBuilding class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FACTORYBUILDING_H__6550C26F_3900_4577_95A0_3ED0C352019E__INCLUDED_)
#define AFX_FACTORYBUILDING_H__6550C26F_3900_4577_95A0_3ED0C352019E__INCLUDED_


#include "Building.h"
class FactoryBuilding : public Building  
{
public:
	FactoryBuilding(const CString& name , int index , int level);
	virtual ~FactoryBuilding();

  //consume power
  virtual unsigned long GetConsumePower();

  //upgrade resource needed
  virtual unsigned long GetUpgradeMinal();
  virtual unsigned long GetUpgradeCrystal();
  virtual unsigned long GetUpgradeDiplogen();

  //total upgrade resource
  virtual unsigned long GetTotalUpgradeMinal();
  virtual unsigned long GetTotalUpgradeCrystal();
  virtual unsigned long GetTotalUpgradeDiplogen();

  //produce
  virtual unsigned long PrudeceMinal();
  virtual unsigned long PrudeceCrystal();
  virtual unsigned long PrudeceDiplogen();
  virtual unsigned long PrudecePower();

private:
  //comsume
  static const int UPGRADE_MINAL_TBL[];
  static const int UPGRADE_CRYSTAL_TBL[];
  static const int UPGRADE_DIPLOGEN_TBL[];
  static const int CONSUME_POWER_TBL[];

  //produce
  static const int PRODUCE_MINAL_TBL[];
  static const int PRODUCE_CRYSTAL_TBL[];
  static const int PRODUCE_DIPLOGEN_TBL[];
  static const int PRODUCE_POWER_TBL[];

  static double total_produce_Percent_;
  double self_produce_Percent;

  std::vector<Building*> entry_factories_;

};

#endif // !defined(AFX_FACTORYBUILDING_H__6550C26F_3900_4577_95A0_3ED0C352019E__INCLUDED_)
