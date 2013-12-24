// DiploenFactory.h: interface for the DiploenFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DIPLOGEN_FACTORY_HEADER_)
#define _DIPLOGEN_FACTORY_HEADER_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Building.h"
class DiplogenFactory : public Building
{
public:
	DiplogenFactory(const CString& name  , const CString& des, int index , int level);
	virtual ~DiplogenFactory();

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

#endif // !defined(_DIPLOGEN_FACTORY_HEADER_)
