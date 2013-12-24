
#if !defined(PRODUCE_IMPROVE_CENTER_H)
#define PRODUCE_IMPROVE_CENTER_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Building.h"

class ProduceImproveCenter : public Building
{
public:
	ProduceImproveCenter(const CString& name  , const CString& des, int index , int level);
	virtual ~ProduceImproveCenter();

  ////consume
  //consume resource needed
  virtual double GetUpgradeMinal();
  virtual double GetUpgradeCrystal();
  virtual double GetUpgradeDiplogen();

  //total upgrade resource
  virtual double GetTotalUpgradeMinal();
  virtual double GetTotalUpgradeCrystal();
  virtual double GetTotalUpgradeDiplogen();

  //consume Power
  virtual unsigned long GetConsumePower();

  ////produce
  virtual double        ProduceMinal();
  virtual double        ProduceCrystal();
  virtual double        ProduceDiplogen();
  virtual unsigned long ProducePower();

  virtual bool CanLevelUp();

  virtual double GetUpgradeTime();

  virtual void Load();
  virtual void Save();

};

#endif // !defined(PRODUCE_IMPROVE_CENTER_H)
