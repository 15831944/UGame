#if !defined(_COMMUNICATION_HEADER_)
#define _COMMUNICATION_HEADER_

class CPagePersonInfo;     
class CPageBuildings;     
class CPageResource ;      
class CPageGalaxy;        
class CPageBoatyard;       
class CPageResreachCenter; 
class CPageInformation;    
class CPageCommander;     
class CPageDocuments; 

class Star;

class Communication  
{
private:
  CPagePersonInfo*     page_person_;
  CPageBuildings*      page_buildings_;
  CPageResource*       page_resource_;
  CPageGalaxy*         page_galaxy_;
  CPageBoatyard*       page_boatyard_;
  CPageResreachCenter* page_reseach_center_;
  CPageInformation*    page_information_;
  CPageCommander*      page_commander_;
  CPageDocuments*      page_docs_;

public:
	Communication();
	virtual ~Communication();
  //commander
  bool Spy(Star& star);
  void PrepareAttack(int target_index);
  void PrepareRecycle(int target_index);
  void AttackPlayer(Star& s);

  //infomation
  void ReportSpyInfo(const Spy_info& spy_info);
  void ReportWarInfo(const War_info& war_info);
  void ReportFleetReach(const COMMAND_TASK& task);
  void ReportRecycleInfo(const COMMAND_TASK& task);
  void ReportTransferInfo(const COMMAND_TASK& task);
  void ReportColonyInfo(const COMMAND_TASK& task , bool bSucess);

  //galaxy
  Star& GetStar(int index);
  ulong GetRefreshMinutes();
  void  UpdateShowStarInfo();
  vector<Sort_Table_t>& GetStarsTable();
  void UpdateGalaxyRank();
  void DoneAttacking();

  //docs
  void ShowDocument(int first, int second);

  //persons
  void ViewRank(PlaniPos pos , bool is_self);

  //fleet number
  ulong GetAllFleetNumber();

  void Initialize(
    CPagePersonInfo*     page_person,
    CPageBuildings*      page_buildings,
    CPageResource*       page_resource,
    CPageGalaxy*         page_galaxy,
    CPageBoatyard*       page_boatyard,
    CPageResreachCenter* page_reseach_center,
    CPageInformation*    page_information,
    CPageCommander*      page_commander,
    CPageDocuments*      page_docs);
};

#endif // !defined(_COMMUNICATION_HEADER_)
