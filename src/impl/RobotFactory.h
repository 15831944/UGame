// RobotFactory.h: interface for the RobotFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(ROBOTFACTORY_HEADER)
#define ROBOTFACTORY_HEADER

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Building.h"
class RobotFactory : public Building
{
public:
	RobotFactory(const CString& name  , const CString& des, int index , int level);
	virtual ~RobotFactory();

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

#endif // !defined(ROBOTFACTORY_HEADER)
