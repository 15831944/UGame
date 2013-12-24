#if !defined(_USTAR_H_)
#define _USTAR_H_

class GameData;

class Star 
{
public:
  GameData* data_;
  Computer_Planet_Ram* computer_info_;
  //normal data member
  uchar  type_;   
  PlaniPos position_;
  uchar   bitmap_index_;
  CString name_;
  bool    is_npc_player;
  uchar   double_res_hero;
  bool    is_salve_planet;

  USHORT index_;
  double rank_;

  //resource
  double metal_;
  double crystal_;
  double diplogen_;

  //fleet number
  ulong fleet_number_;

  //resource
  int64  recycled_metal_;
  int64  recycled_crystal_;

  //fleets and defenses
  vector<SItem> fleet_and_defense_;

  //techs
  ShipTechs ship_techs_;  

  //others
  USHORT spy_level_;
  float  elpase_;

  //is out
  bool is_fleet_out;

  Star(GameData* gamedata , UINT index);
  void Update();
  ulong UpdateFleetNumber();
  void UpdateComputerRAM();
private:
  void generate();  
};

inline ulong Star::UpdateFleetNumber()
{
  //calc fleet number
  ulong temp = 0L;
  for(int i = T_KT ; i < T_RAK ; ++i)
  {
    temp += fleet_and_defense_[i].Num;
  }
  fleet_number_ = temp;
  return fleet_number_;
}

inline void Star::UpdateComputerRAM()
{
  computer_info_->ruin_crystal = recycled_crystal_;
  computer_info_->ruin_metal   = recycled_metal_;
  computer_info_->is_slave_planet = is_salve_planet;
  computer_info_->num_double_res_hero = double_res_hero;
  computer_info_->owner_type = type_;
  computer_info_->score = rank_;
}

#endif // !defined(_USTAR_H_)
