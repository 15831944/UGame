// LabFactory.h: interface for the LabFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(LABFACTORY_HEADER)
#define LABFACTORY_HEADER

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Building.h"
class LabFactory : public Building
{
public:
	LabFactory(const CString& name  , const CString& des, int index , int level);
	virtual ~LabFactory();

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

};

#endif // !defined(LABFACTORY_HEADER)
