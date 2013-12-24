// MetalFactory.h: interface for the MetalFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_CRYSTAL_FACTORY_HEADER_)
#define _CRYSTAL_FACTORY_HEADER_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Building.h"
class CrystalFactory : public Building
{
public:
	CrystalFactory(const CString& name  , const CString& des, int index , int level);
	virtual ~CrystalFactory();

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

  virtual void SetProducePercent(double p);
};

#endif // !defined(_CRYSTAL_FACTORY_HEADER_)
