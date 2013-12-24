// DefensesKeeper.h: interface for the DefensesKeeper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_DEFNSE_KEEPER_)
#define _DEFNSE_KEEPER_

class Defense;
class GameData;

class DefensesKeeper  
{
private:
  std::vector<Defense*> entry_defenses_;
  GameData* data_;
  
public:
	DefensesKeeper(GameData* d);
	virtual ~DefensesKeeper();
  Defense* GetDefense(int index);
  int Size() {return entry_defenses_.size();}

private:
  void CreateDefenses();

};

#endif // !defined(_DEFNSE_KEEPER_)
