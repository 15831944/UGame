// Boatyard.h: interface for the Boatyard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(BOATYARD_HEADER)
#define BOATYARD_HEADER

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Building.h"
class Boatyard : public Building
{
public:
	Boatyard(const CString& name  , const CString& des, int index , int level);
	virtual ~Boatyard();

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

#endif // !defined(BOATYARD_HEADER)
