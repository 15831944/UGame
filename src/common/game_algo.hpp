#ifndef _GAME_ALGO_HEADER_
#define _GAME_ALGO_HEADER_
#include "math.h"

extern float _speed_adjust_;

//round up double
inline
double roundup(double r)
{
  if(r < 1.0)
    return r;
  if( r - int64(r) >= 0.5 )
    return int64(r) + 1.0;
  return int64(r);
}

////////Factorys
////produce factory
//upgrade resource needed
inline
double get_produce_factory_upgrade_resource(ulong base , ulong level)
{
  return base * pow(1.5 , level);
}

//produce resource per minute
inline
double get_produce_factory_produce_resource_per_minute(ulong addition , ulong base , ulong level , double self_p , double total_p)
{
  double r = 1.13;
  if(level <= 30)
  {
    r = 1.13;
  }
  else if(level > 30 && level <= 35)
  {
    r = 1.15;
  }
  else if(level > 35 && level <= 40)
  {
    r = 1.17;
  }
  else if(level > 40)
  {
    r = 1.19;
  }
  return ADJUST_RESOURCE_PARAMETER * _speed_adjust_ * (addition + base * level * pow(r , level) * self_p * total_p) / 60.0;
}

//produce power number
inline
unsigned long get_produce_factory_produce_power(int base , ulong level , double self_p)
{
  return base * level * pow(1.1 , level) * self_p;
}

//consume power number
inline
unsigned long get_produce_factory_consume_power(int base , ulong level , double self_p)
{
  return base * level * pow(1.1 , level) * self_p;
}

////others factory
//upgrade resource needed
inline
double get_other_factory_upgrade_resource(ulong base , ulong level)
{
  return base * pow(2 , level);
}

////all factory upgrade time (seconds)
inline
double get_factory_upgrade_seconds(ulong ass_level , ulong nanite_level , double metal , double crystal , double factor = 1.0 )
{
  double t = factor * 3600 * ( metal + crystal) / (3600.0 * (1 + ass_level)) * pow(0.5 , nanite_level) / (_speed_adjust_);
  t = roundup(t);
  return (t < 1.5 ? 1.0 : t);
}

////////research
//upgrade resource needed
inline
double get_research_upgrade_resource(ulong base , ulong level)
{
  return base * pow(2 , level);
}

//all upgrade time (seconds)
inline
double get_research_upgrade_seconds(ulong robot_level , ulong nanite_level , double metal , double crystal , double factor = 1.0 )
{
  double t = factor * 3600 * ( metal + crystal) / (3600.0 * (1 + robot_level)) * pow(0.5 , nanite_level) / (_speed_adjust_);
  t = roundup(t);
  return (t < 1.5 ? 1.0 : t);
}

////////boats
//all produce time (seconds)
inline
double get_boat_produce_seconds(ulong robot_level , ulong nanite_level , double metal , double crystal , double factor = 1.0 )
{
  double t = factor * 3600 * ( metal + crystal) / (3600.0 * (1 + robot_level)) * pow(0.5 , nanite_level) / (_speed_adjust_);
  double min_frequency = TIMER_BASE_HIGH_FREQUENCY / 1000.0;
  t = roundup(t / min_frequency) * min_frequency;
  //min 100ms
  return  (t < min_frequency ? min_frequency : t);
}
#endif//_GAME_ALGO_HEADER_