// MetalFactory.h: interface for the MetalFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_METALFACTORY_H__BD122998_EF96_417C_B7DF_93B24E4F8667__INCLUDED_)
#define AFX_METALFACTORY_H__BD122998_EF96_417C_B7DF_93B24E4F8667__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Building.h"
class MetalFactory : public Building
{
public:
	MetalFactory(const CString& name  , const CString& des, int index , int level);
	virtual ~MetalFactory();

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

#endif // !defined(AFX_METALFACTORY_H__BD122998_EF96_417C_B7DF_93B24E4F8667__INCLUDED_)
