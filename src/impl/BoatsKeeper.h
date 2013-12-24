// BoatsKeeper.h: interface for the BoatsKeeper class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOATSKEEPER_H__9F43A652_9E17_4D38_B108_19CE3A5DF7B2__INCLUDED_)
#define AFX_BOATSKEEPER_H__9F43A652_9E17_4D38_B108_19CE3A5DF7B2__INCLUDED_

class Spaceship;
class GameData;

class BoatsKeeper  
{
private:
  std::vector<Spaceship*> entry_boats_;
  GameData* data_;
  
public:
	BoatsKeeper(GameData* d);
	virtual ~BoatsKeeper();
  Spaceship* GetBoat(int index);
  int Size() {return entry_boats_.size();}

private:
  void CreateBoats();

};

#endif // !defined(AFX_BOATSKEEPER_H__9F43A652_9E17_4D38_B108_19CE3A5DF7B2__INCLUDED_)
