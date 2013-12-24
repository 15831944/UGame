// NaniteFactory.h: interface for the NaniteFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(NANITEFACTORY_HEADER)
#define NANITEFACTORY_HEADER

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Building.h"
class NaniteFactory : public Building
{
public:
	NaniteFactory(const CString& name  , const CString& des, int index , int level);
	virtual ~NaniteFactory();

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


};

#endif // !defined(NANITEFACTORY_HEADER)
