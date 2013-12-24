
#if !defined(_OVERBASE_HEADER_)
#define _OVERBASE_HEADER_

class GameData;
class CXGameDlg;
class Building;
class BuildingsKeeper;
class ResearchTechnics;
class ResearchKeeper;
class Spaceship;
class BoatsKeeper;
class Defense;
class DefensesKeeper;
class Communication;

#define Buildings_Entry(x) (GetBuilding(x))
#define Researchs_Entry(x) (GetResearch(x))
#define Boats_Entry(x)     (GetBoat(x))
#define Defenses_Entry(x)  (GetDefense(x))

class ObserverBase  
{
public:
	ObserverBase();
	virtual ~ObserverBase() = 0;

public:
  GameData* GetDataPtr();
  CXGameDlg* GetCommander();
  void SetDataPtr(GameData* d);  
  void SetParentPtr(CXGameDlg* p);
  void SetCommPtr(Communication* p);

  void SetBuildingsKeeper(BuildingsKeeper* k);
  void SetResearchsKeeper(ResearchKeeper* k);
  void SetBoatsKeeper(BoatsKeeper* k);
  void SetDefensesKeeper(DefensesKeeper* k);

  Building* GetBuilding(int index);  
  ResearchTechnics* GetResearch(int index);
  Spaceship* GetBoat(int index);
  Defense* GetDefense(int index);
  const CString& GetTipInfo();

  //notify
  virtual void Notify_Score_Changed();
  virtual void Notify_Building_LevelUp();
  virtual void Notify_Building_ProducePercent_Changed();
  virtual void Notify_Resource_Changed();
  virtual void Notify_Technics_LevelUp();
  virtual void Notify_Exit();
  virtual void Notify_Ships_Changed();
  virtual void Notify_Init();
  virtual void Notify_Galaxy_Update();
  virtual void Notify_Defense_Changed();
  

  //working flag
  void SetWorkFlag(bool bw)
  {
    bWorking_ = bw;
    if(!bw)
    {
      tip_ = "";
    }
  }

  bool GetWorkFlag()
  {
    return bWorking_;
  }

private:
  GameData*  data_;
  CXGameDlg* parent_;
  bool       bWorking_;      

protected:
  BuildingsKeeper* building_keeper_;
  ResearchKeeper * research_keeper_;
  BoatsKeeper    * boat_keeper_;
  DefensesKeeper * defense_keeper_;
  Communication  * comm_;
  CString          tip_;
};

#endif // !defined(_OVERBASE_HEADER_)
