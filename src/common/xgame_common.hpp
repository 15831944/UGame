#ifndef _XGAME_COMMON_HPP_
#define _XGAME_COMMON_HPP_

#include "ElapsedTimer.h"
class Star;

//CSpeedKernel interface
extern CSpeedKernel& kernel_;

//---------------------------------- typedef ----------------------------------//
typedef __int64  int64;
typedef unsigned long ulong;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef const char cchar;

typedef std::vector<SItem> FLEET;
typedef FLEET::iterator    ITOR_FLEET;

//---------------------------------- common value ----------------------------------//
#define IDC_MYLIST         0x1234
#define HIGH_LIGHT_COLOR   "#00FF00"
#define GRAY_COLOR         "#A0A0A0"
#define NO_SIZE_COLOR      "#FF0000"
#define NO_RESOURCE_COLOR  "#FF8040"
#define CUR_OPER_COLOR     "#008000"
#define NORMAL_TEXT_COLOR  "#E6EBFB"

//mill second
const int TIMER_BASE = 1000;
const int TIMER_BASE_HIGH_FREQUENCY = 50;

//power base
const int SUN_POWER_PLANET_BASE_POWER = 38;

//max speed
const int MAX_GAME_SPEED = 100;
const int MAX_PRODUCED_BOAT = 999999;

//additional parameter
const int ADJUST_RESOURCE_PARAMETER = 3;
const int MAX_DOUBLE_RES_HERO_NUM   = 3;

//Galaxy, nomal
#ifndef USE_FOR_SMALL_GALAXY_VERSION
const ushort    MAX_GALAXY_GALA = 3;
const ushort    MAX_GALAXY_SYS  = 50;
const ushort    MAX_GALAXY_POS  = 15;
//small galaxy
#else
const ushort    MAX_GALAXY_GALA = 1;
const ushort    MAX_GALAXY_SYS  = 20;
const ushort    MAX_GALAXY_POS  = 15;
#endif

//SetTimer(...) timer IDs
enum{ 
 TIMER_TASKBASE      = 0  ,       //for fleet task
 TIMER_PRODUCE       = 512,       //for resource produce
 TIMER_BUILDING_LEVEL_UP  ,       //for building level up
 TIMER_RESEARCH_LEVEL_UP  ,       //for research level up
 TIMER_PRODUCE_BOAT       ,       //for produce boat
 TIMER_PRODUCE_DEFENSE    ,       //for produce defense
 TIMER_FOR_GATE           ,       //for transfer gate
 TIMER_FOR_TRADE          ,       //for trade
 TIMER_FOR_EXIT           ,       //for exit
 TIMER_FOR_SAVE           ,       //for save data
 TIMER_FOR_GALAXY         ,       //for galaxy update
 TIMER_FOR_TIPDLG         ,       //for tip dialog exit
 TIMER_FOR_CHECK_ATTACKING,       //for enemy attacking
 TIMER_FOR_ENEMY_ATTACKING,       //for check galaxy attack
};

//computer settings
enum{
  COMPUTER_T_LOW,
  COMPUTER_T_MID,
  COMPUTER_T_HIGH,
};

//---------------------------------- gui ----------------------------------//
//pages
enum
{
  PAGE_PERSON,
  PAGE_GALAXY,
  PAGE_COMMAND,
  PAGE_INFOMATION,
  PAGE_RESOURCE,
  PAGE_BUILDING,
  PAGE_RESEARCH,
  PAGE_BOATYARD,  
  PAGE_DEFENSE,
  PAGE_DOCUMENTS,
};

//---------------------------------- game info----------------------------------//
//colonys
enum
{
  HOMESTAR,
  COLONY_STAR1,
  COLONY_STAR2,
  COLONY_STAR3,
  STAR_MAX,
};


//resource
enum
{
  RESOURCE_METAL,
  RESOURCE_CRYSTAL,
  RESOURCE_DIPLOGEN,
  RESOURCE_MAX
};

//product
enum
{
  PRODUCT_METAL,
  PRODUCT_CRYSTAL,
  PRODUCT_DIPLOGEN,
  PRODUCT_SOLAR,
  PRODUCT_MAX,
};

////BuildFactory
//id
enum
{
  FACTORY_BUILDING_START = 0,
  FACTORY_BUILDING_MINAL = 0,
  FACTORY_BUILDING_CRYSTAL = 1,
  FACTORY_BUILDING_DIPLOGEN = 2,
  FACTORY_BUILDING_SUNPOWER = 3,
  FACTORY_BUILDING_PRODUCE_MAX = 3,
  FACTORY_BUILDING_ROBOT = 4,
  FACTORY_BUILDING_LAB = 5,
  FACTORY_BUILDING_BOATYARD = 6,
  FACTORY_BUILDING_NANITE,
  FACTORY_BUILDINGS_MAX
};

//chs name
const CString FACTORY_BUILDS_NAME[] =
{
  _T("����������"),
  _T("����������"),
  _T("����������"),
  _T("̫���ܹ���"),
  _T("�����˹���"),
  _T("�о�ʵ����"),
  _T("�촬��"),
  _T("���׻����˹���"),
  _T("")
};

//name
const CString FACTORY_BUILDS_NAME_ENGLISH[] =
{
  _T("Metal Mine"),
  _T("Crystal Mine"),
  _T("Deuterium Synthesiser"),
  _T("Solar Plant"),
  _T("Robotic Factory"),
  _T("Research Lab"),
  _T("Ship Yard"),
  _T("Nanite Factory"),
  _T("")
};

const int FACTORY_DATA[][8] = 
{
//metal    crystal diplogen  c-power p-metal  p-cry p-hh p-power 
  {60     ,  15   ,   0   ,   10  ,   30 ,    0   , 0 ,   0   }, //metal
  {60     ,  30   ,   0   ,   10  ,   0  ,    20  , 0 ,   0   }, //crystal
  {225    ,  75   ,   0   ,   20  ,   0  ,    0   , 10,   0    },//diplogen
  {75     ,  30   ,   0   ,   20  ,   0  ,    0   , 0 ,   20   }, //sunpower
  {400    , 120   ,  200  ,   0   ,   0  ,    0   , 0 ,   0    }, //robot
  {200    , 400   ,  200  ,   0   ,   0  ,    0   , 0 ,   0    }, //lab
  {400    , 200   ,  100  ,   0   ,   0  ,    0   , 0 ,   0    }, //boatyard
  {1000000 ,500000 , 100000 ,   0   ,   0  ,    0   , 0 , 0    }  //nanite
};

enum
{
  FACTORY_TBL_N_METAL,
  FACTORY_TBL_N_CRYSTAL,
  FACTORY_TBL_N_DIPLOGEN,
  FACTORY_TBL_POWER,
  FACTORY_TBL_P_METAL,
  FACTORY_TBL_P_CRYSTAL,
  FACTORY_TBL_P_DIPLOGEN,
  FACTORY_TBL_P_POWER,
};

//description
const CString FACTORY_BUILDS_SIMPLE_DISP[] =
{
  _T("�������ṩ�˵۹�����Ļ�����Դ�����ұ����ڽ��콨����ͷɴ�."),
  _T("��������������Ԫ���������Ͻ����Ҫ��Դ."),
  _T("�����Ƿɴ���ȼ�ϣ����Դ������ȡ����������ϡ�����ʣ��൱���."),
  _T("̫���ܷ���վ����������ת��Ϊ�������ṩ�������еĽ�����ʹ��."),
  _T("�����˹����ṩ�����Ҹ�Ч���Ͷ������ڻ������衣ÿ����һ�����������������ٶ�Ҳ��Խ��."),
  _T("���Ҫ�о��¼����������Ƚ����о���."),
  _T("�촬�������������е�̫�մ������������ʩ��ÿ����һ��,�ɴ��������ٶ�Ҳ��Խ��."),
  _T("���׻����˹����ǻ����˼������ռ�������ÿ����һ���ȼ��Ϳ����ṩ��������׻���������������ٶ�.")
  _T("")
};

////researchs
//id
enum
{
  RESEARCH_START = 0,
  RESEARCH_SPY = 0,
  RESEARCH_COMPUTER,
  RESEARCH_WEAPON,
  RESEARCH_SHEILED,
  RESEARCH_ARMOUR,
  RESEARCH_POWER,
  RESEARCH_SUPERTECH,
  RESEARCH_BURNING,
  RESEARCH_PULSE,
  RESEARCH_SUPERSPACE,
  RESEARCH_PLASM,
  RESEARCH_GRAVITION,
  RESEARCH_MAX,
};

//name
const CString RESEARCHS_NAME[] =
{
  _T("�ռ�̽�⼼��"),
  _T("���������"),
  _T("��������"),
  _T("������ϵͳ "),
  _T("װ�׼���"),
  _T("��������"),
  _T("���ռ似��"),
  _T("ȼ������"),
  _T("��������"),  
  _T("���ռ�����"),
  _T("�����Ӽ���"),
  _T("��������"),
  _T("")
};

const ulong RESEARCH_RESOURCE_NEED_BASE[][3] = 
{
  {200  , 1000 , 200},  //spy
  {0    , 400  , 600},  //computer
  {800  , 200  , 0  },  //attack
  {200  , 600  , 0  },  //sheiled
  {1000 , 0    , 0  },  //defense
  {0    , 800  , 400},  //power
  {0    , 4000 , 2000},  //super tech
  {400  , 0    , 600},  //burning
  {2000 , 4000 , 600},  //pulse
  {10000, 20000, 6000},  //super space
  {2000 , 4000 , 1000},  //plasm
  {0 , 0 , 0},  //gravition
};


//description
const CString RESEARCHS_SIMPLE_DISP[] =
{
  _T("ʹ�ÿռ��������������̽���������ѶϢ."),
  _T("Խ�߼��ļ���������ṩ�����Ľ���ָ����Ŀ��ÿ����һ���ȼ��������Զ�ָ��һ֧����."),
  _T("���༼������������ϵͳ��Ч�ܣ�����������ƻ�����ɵ��˺���ÿ����һ���������������ڻ���ֵ����10%"),
  _T("������ϵͳ��������Ĵ�����Χ���������Ե����ӻ��ܡ�ÿ����һ���ȼ�����Ϊ����������10%��Ч��."),
  _T("����ĺϽ�ʹװ�׸���ǿ��װ�׵�Ч����ÿ��һ������װ�׻����ڻ���ֵ����10%."),
  _T("ƾ���ŶԸ��ֲ�ͬ������������⣬�ܶ��¼�������ʵ�֡������ִ��Ƽ���˵������������Ϊ��Ҫ."),
  _T("ͨ�������ά����ά���ƽ����������Դ����һ���µ��ƽ�ϵͳ��Ч�ʸ��ߣ�����ʡȼ��."),
  _T("�о������������ʹȼ�������Ϊ���٣�ÿ����һ���ȼ�����Ϊ�ض������ڻ���ֵ������10%���ٶ�."),
  _T("����������ڷ���������ԭ�����ơ������ƽ�ϵͳ���õ�ȼ���Ǻ��ں�¯�������������������."),
  _T("���ռ������ṩ�˽���ʱ�մ��͵��ֶΣ����Դ����������ʱ�䡣���ռ�ָ������ά�ռ����������ռ�."),
  _T("�����Ӽ������µĻ������������о����߼��ٵĵ������ű�������Ϊ����ǿ���������������Ŀ����ɻ����Ե��˺�."),
  _T("�۹���߼��ļ����������о�����."),
  _T("")
};

////boats
//id
enum
{
  BOAT_START = 0,
  BOAT_SMALL_SCUTTER = 0,
  BOAT_LARGE_SCUTTER,
  BOAT_LIGHT_FIGHTER,
  BOAT_HEAVY_FIGHTER,
  BOAT_CRUISER,
  BOAT_WARSHIP,
  BOAT_CONOLY,
  BOAT_RECYCLE,
  BOAT_SPY_PLANET,
  BOAT_BOMBER,
  BOAT_SUNPOWER_PLANET,
  BOAT_DESTROYER,
  BOAT_DS,
  BOAT_MAX,
};

//name
const CString BOATS_NAME[] =
{
  _T("С�����佢"),
  _T("�������佢"),
  _T("����ս����"),
  _T("����ս����"),
  _T("Ѳ��"),
  _T("ս�н�"),
  _T("ֳ��"),
  _T("���մ�"),
  _T("̽����"),
  _T("��ը��"),
  _T("̫��������"),
  _T("������"),
  _T("����"),
  _T("")
};

//short name
const CString BOATS_SHORT_NAME[] =
{
  _T("С��"),
  _T("����"),
  _T("��ս"),
  _T("�ؼ�"),
  _T("Ѳ��"),
  _T("ս��"),
  _T("ֳ��"),
  _T("���մ�"),
  _T("̽����"),
  _T("��ը��"),
  _T("̫��"),
  _T("������"),
  _T("����"),
  _T("")
};

//description
const CString BOATS_SIMPLE_DISP[] =
{
  _T("С�����佢��һ�����ɵĽ�ͧ����������Դ��һ���������͵���һ������."),
  _T("�������佢�Ǵ�С�����佢��չ���ģ�ӵ�и���Ļ��ֺ͸�����ٶ�."),
  _T("����ս������һ�����Ľ�ͧ�����ڼ������е��������ҵ������Ļ��Ѳ����������ķ�������Դ��װ����Ҳ����."),
  _T("����ս������������ս�����ĸĽ������г��ֵĸ����ԵĲ��ӵ�и�ǿ�ķ����ܺͻ���."),
  _T("Ѳ�󽢵�װ�״�Լ������ս������3��������ǿ2���������ٶ�Ҳ�����д���������. "),
  _T("ս�н��ǽ��ӵļ������������ͷ��������٣������װ�ؿռ��������Կ��������ӵĵ���."),
  _T("���ִ����Ĵ������壬����Ϊ��Ҫ̽�������ȥ��δ����֮����������������."),
  _T("���մ���������Ʈ��������ռ���Ĵ����к������Ƴɿ��õ���Դ."),
  _T("С������̽���������ظ�Ч�ܵ��ƽ����������ܹ��ṩңԶ�������ϵ���Ϣ."),
  _T("��ը��ר�������ݻ������ϵ����ͷ���װ��."),
  _T("̫��������װ����̫���ܵ�أ��ǹ���򵥵Ĺ�����ǣ�������Ѽ������������ص�����ĵر���."),
  _T("�������ǬF֪�����͵Ĵ�Ş,���d�Ļ�������Ҳ��ʷ�oǰ����."),
  _T("�۹������ռ����ߣ������޾�����ȻҲ��Ҫ�൱�����Դ������."),
  _T("")
};

const ulong BOATS_RESOURCE_NEED_BASE[][3] = 
{
  {2000  , 2000 , 0   },  //Small Cargo Ship
  {6000  , 6000 , 0   },  //large Cargo Ship
  {3000  , 1000 , 0   },  //light fighter
  {6000  , 4000 , 0   },  //heavy fighter
  {20000 , 7000,  2000},  //Cruiser
  {45000  ,15000 ,0   },  //Battleship
  {10000  ,20000 ,10000   },  //conoly
  {10000  , 6000 ,2000   },  //recycle
  {0  ,1000 ,0   },  //spy
  {50000  ,25000 ,15000   },  //bomber
  {0     , 2000 , 500 },  //Solar Satellite
  {60000  ,50000 ,15000   },  //destroyer
  {5000000  ,4000000 ,1000000   },  //ds
};

//force
const ulong SHIP_ATTACK_FORCE_BASE[] = 
{
  5,    //Small Cargo Ship
  5,    //large Cargo Ship
  50,   //light fighter
  150,  //heavy fighter
  400,  //Cruiser
  1000, //Battleship
  50,  //conoly
  1,  //recycle
  1,    //Espionage Probe
  1000,//bomber
  1  , //Solar Satellite
  2000,//destroyer
  200000,//ds  
}; 

//capacity
const ulong SHIP_TRANSFER_CAPACITY[] = 
{
  5000,   //Small Cargo Ship
  25000,  //large Cargo Ship
  50,     //light fighter
  100,    //heavy fighter
  800,    //Cruiser
  1500,   //Battleship
  7500,  //conoly
  20000,  //recycle
  5,      //Espionage Probe
  500,//bomber
  0 ,      //Solar Satellite
  2000,//destroyer
  1000000,//ds
}; 

//speed
const ulong SHIP_BASE_SPEED[] = 
{
  10000,  //Small Cargo Ship
  7500,   //large Cargo Ship
  12500,  //light fighter
  10000,  //heavy fighter
  15000,  //Cruiser
  10000,  //Battleship
  2500,  //conoly
  2000,  //recycle
  100000000,//Espionage Probe
  5000,//bomber
  0,       //Solar Satellite
  5000,//destroyer
  100, //ds

}; 

//consume HH
const ulong SHIP_BASE_OIL[] = 
{
  10,   //Small Cargo Ship
  20,   //large Cargo Ship
  10,   //light fighter
  20,   //heavy fighter
  100,  //Cruiser
  200,  //Battleship
  100,  //conoly
  100,  //recycle
  1,    //Espionage Probe
  200,//bomber
  0 ,    //Solar Satellite
  400, //destroyer
  1,  //ds
}; 

////defense
//id
enum
{
  DEFENSE_START = 0,
  DEFENSE_MISS = 0,
  DEFENSE_SLASER,
  DEFENSE_HLASER,
  DEFENSE_GAUSS,
  DEFENSE_ICON,
  DEFENSE_PC,
  DEFENSE_MAX,
};

//name
const CString DEFENSES_NAME[] =
{
  _T("�������װ��"),
  _T("���ͼ�����"),
  _T("���ͼ�����"),
  _T("��˹��"),
  _T("������"),
  _T("����������"),
  _T("С�ͷ�����"),
  _T("���ͷ�����"),
  _T("")
};

//description
const CString DEFENSE_SIMPLE_DISP[] =
{
  _T("�������װ����һ����۵���������򵥵ķ���ϵͳ."),
  _T("ͨ�����Ӽ����������ɱȵ�������������˺�."),
  _T("�����ͼ�������ȣ����ͼ�������ǿ�˹���������ṹҲ���Ӽ��."),
  _T("��˹���ܰѱ��ص��ڵ��þ޴�ĵ�ų����ٲ������ȥ."),
  _T("���������÷�����������������Ŀ�꣬ʹ�����ܲ��ȶ������ջٵ����豸."),
  _T("����������������ڵ�����������������С�͵�̫������������ƻ��Ե����������Ȼ����߻�Ҫǿ��."),
  _T("")
};

const ulong DEFENSES_RESOURCE_NEED_BASE[][3] = 
{
  {2000  , 0 , 0   },  //miss
  {1500  , 500 , 0   },  //slaser
  {6000  , 2000 , 0   },  //hlaser
  {20000  , 15000 , 2000   },  //gauss
  {2000 , 6000,  0},  //iconc
  {50000  ,50000 ,30000   },  //pc
};

////struct
enum
{
  TASK_T_NONE = -1,
  TASK_T_SPY = 0,
  TASK_T_ATTACK,
  TASK_T_RECYCLE,
  TASK_T_TRANSPORT,
  TASK_T_DISPATCH,
  TASK_T_COLONIZE,
};

enum{
  COM_AI_T_BY_TIME,
  COM_AI_T_BY_PLAYER,
};
//spy info
struct Spy_info{
  Star* star_;
  unsigned long refresh_minuter_;
  ulong spynumber_;
};

//war info
struct War_info{
  int attack_star_index_;
  int64 self_lost_;
  int64 target_lost_;
  int64 recycled_res_;
  bool  get_double_res_hero;
  char battle_report_file_[256];
};

//ships number
struct Ships_NUMs
{
  int small_scutter;
  int large_scutter;
  int light_fighter;
  int heavy_fighter;
  int cruisor;
  int warship;
  int spy_planet;
  int sunpower_planet;
};

//resouce
struct Resource{
  int64 metal_;
  int64 crystal_;
  int64 diplogen_;
  Resource() : metal_(0) , crystal_(0) , diplogen_(0){}
};

//star type
enum{
  STAR_T_NONE,
  STAR_T_ENEMY,
  STAR_T_SELF,
};

//command task
struct COMMAND_TASK{
  int index;
  PlaniPos     leave_pos;
  uchar        leave_star_index;
  ElapsedTimer timer;  //timer
  ulong cycle;         //cycles
  char  task;          //task
  Star* star;          //target star
  std::vector<SItem> fleet; //ships
  bool  is_go;
  Resource res;
  Resource loss_res;
  bool  is_can_back;
  double fuel;
  COMMAND_TASK::COMMAND_TASK();
};

//battle result
struct BattleRes{
  Resource catch_resource_;
  Resource recycled_resource_;
  Resource loss_resource_;
  Resource target_loss_resource_;
  FLEET self_fleet_;
  FLEET target_fleet_;
  uchar bat_number;
  char report_file_[256];
};

//sort item
struct Sort_Table_t{
  double  rank;
  CString name;
  ulong   fleet;
  ulong   position;
};

//functor by rank
template<class T>
struct greater_by_rank_functor
{
  bool operator()(T x , T y) const
  {
    return x.rank > y.rank;
  }
};

//functor by fleet
template<class T>
struct greater_by_fleet_functor
{
  bool operator()(T x , T y) const
  {
    return x.fleet > y.fleet;
  }
};

//functor by position
template<class T>
struct lower_by_position_functor
{
  bool operator()(T x , T y) const
  {
    return x.position < y.position;
  }
};

//functor for find rank
template<class T>
struct find_rank_functor
{
  bool operator()(T x , T y) const
  {
    return x.position == y.position;
  }
};


////account entry RAM
struct Colonize_Planet_Ram
{
  //resources
  double metal;             //metal
  double crystal;           //crystal
  double diplogen;          //diplogen
  //position  
  ULONG  position;          //star position
  struct  
  {
    UCHAR has_moon;
    UCHAR has_gate;
    UCHAR is_exist;
    UCHAR reserved;
  };  
  //boats
  ULONG star_boats[BOAT_MAX];
};

struct Computer_Planet_Ram{
  double score;          //score
  double lost_score;     //destroy score
  double ruin_metal;
  double ruin_crystal;  
  struct  
  {
    UCHAR  owner_type;
    UCHAR  is_npc_target;
    UCHAR  num_double_res_hero;
    UCHAR  is_slave_planet;
  };  
  UINT   reserved;        //reserved for future
};

struct Account_Entry_Ram{
  ////player mapping
  //base info
  TCHAR  ident[32];         //ident
  TCHAR  account_name[32];  //account name
  TCHAR  star_name[32];     //star name
  TCHAR  password[32];      //password
  ULONG  position;          //star position
  double score;             //game score
  ULONG  default_spy_num;   //default_spy_num
  double account_money;     //account_money

  //resources
  double resources[RESOURCE_MAX];
  //produce percent
  struct  
  {
    UCHAR metal_percent;
    UCHAR cryst_percent;
    UCHAR diplo_percent;
    UCHAR solar_percent;
  };
  
  //buildings level
  ULONG  star_buildings[FACTORY_BUILDINGS_MAX];
  //researches level
  ULONG  star_researchs[RESEARCH_MAX];
  //boats
  ULONG star_boats[BOAT_MAX];
  //defenses
  ULONG star_defenses[DEFENSE_MAX];
  //last logout time
  LONG   last_logout_time;
  //register time
  LONG   register_time;
  //moon,gate,up resource when off line, temp , circumference , game speed
  struct 
  {
    UCHAR  has_moon;
    UCHAR  has_gate;
    UCHAR  is_not_up_resource_offline;
    CHAR   temp;
    USHORT ciru;     
    USHORT speed; 
  };  
 
  //hero
  ULONG double_res_hero;

  //NPC name
  TCHAR npc_name[32];

  //computer AI setting
  struct 
  {
    UCHAR computer_rank;
    UCHAR computer_is_attack_player;
    UCHAR computer_ai_mode;
    UCHAR reserved_1;
  };

  //reserved for future
  UCHAR reserved_buff[256];

  ////colonize planet info
  Colonize_Planet_Ram conolize_planets[STAR_MAX - 1];

  ////computer mapping
  Computer_Planet_Ram compters_info[MAX_GALAXY_GALA * MAX_GALAXY_SYS * MAX_GALAXY_POS];
};

//utility function
ULONG RandomNumber(ULONG Max);
void  InitRand();
LPTSTR AddPointsToNumber(__int64 value, LPTSTR out);
bool  CheckPosValid(const PlaniPos& pos );
PlaniPos Index2Pos(ulong index);
ulong Pos2Index(const PlaniPos& pos);
char RandomHighTemp(uchar pos);
ushort RandomStarSize(uchar pos);

#endif//_XGAME_COMMON_HPP_