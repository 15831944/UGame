#if !defined(_WAR_SIMULATOR_H_)
#define _WAR_SIMULATOR_H_

class WarSimulator  
{
public:
  WarSimulator();
  bool Simulate(int number , const CString& attack_name , const CString& defender_name , Resource& defnder_res ,
    bool is_elapse , FLEET& attack , FLEET& defence , ShipTechs& att_tech , ShipTechs& def_tech , BattleRes& result , bool is_be_attacked = false);
  
  //gets
  UINT GetFleetSpeed(FLEET& ships , float r = 1.0);
  double GetFleetOil(FLEET& ships , PlaniPos& selfpos , PlaniPos& targetpos , float r = 1.0);
  UINT GeFleetFlySecond(FLEET& ships , PlaniPos& selfpos , PlaniPos& targetpos , float r = 1.0);
  double GetFleetCapacity(FLEET& ships);
  UINT GetFleetShipsNumber(FLEET& ships);
  Resource GetFleetWorth(FLEET& fleet);
};

#endif // !defined(_WAR_SIMULATOR_H_)
