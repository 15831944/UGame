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
  _T("金属提炼厂"),
  _T("晶体提炼厂"),
  _T("重氢提炼厂"),
  _T("太阳能工厂"),
  _T("机器人工厂"),
  _T("研究实验室"),
  _T("造船厂"),
  _T("纳米机器人工厂"),
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
  _T("金属矿提供了帝国所需的基本资源，而且被用于建造建筑物和飞船."),
  _T("晶体是生产电子元件和生产合金的主要资源."),
  _T("重氢是飞船的燃料，可以从深海中提取。重氢属于稀有物质，相当珍贵."),
  _T("太阳能发电站将光子能量转换为电力以提供几乎所有的建筑物使用."),
  _T("机器人工厂提供便宜且高效的劳动力用于基础建设。每提升一级，建筑物升级的速度也就越快."),
  _T("如果要研究新技术，必须先建造研究室."),
  _T("造船厂用来建造所有的太空船和星球防御设施，每提升一級,飞船生产的速度也就越快."),
  _T("纳米机器人工厂是机器人技术的终极革命，每提升一个等级就可以提供更多的纳米机器人以提高生成速度.")
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
  _T("空间探测技术"),
  _T("计算机技术"),
  _T("武器技术"),
  _T("防御盾系统 "),
  _T("装甲技术"),
  _T("能量技术"),
  _T("超空间技术"),
  _T("燃烧引擎"),
  _T("脉冲引擎"),  
  _T("超空间引擎"),
  _T("等离子技术"),
  _T("引力技术"),
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
  _T("使用空间这个技术，可以探测别的星球的讯息."),
  _T("越高级的计算机技术提供你更多的舰队指令数目。每提升一个等级，您可以多指挥一支舰队."),
  _T("此类技术增进了武器系统的效能，提高武器的破坏力造成的伤害。每提升一级，武器攻击力在基础值增加10%"),
  _T("防御盾系统用来在你的船舰周围产生防护性的粒子护盾。每提升一个等级可以为防护盾增加10%的效率."),
  _T("特殊的合金使装甲更加强大。装甲的效力在每升一级船舰装甲化后在基础值上升10%."),
  _T("凭借着对各种不同能量技术的理解，很多新技术得以实现。对于现代科技来说，能量技术极为重要."),
  _T("通过结合四维和五维的推进技术，可以创造出一种新的推进系统－效率更高，更节省燃料."),
  _T("研究这个技术可以使燃烧引擎更为快速，每提升一个等级可以为特定船舰在基础值上增加10%的速度."),
  _T("脉冲引擎基于反作用力的原理而设计。此种推进系统所用的燃料是核融合炉生产能量后产生的垃圾."),
  _T("超空间引擎提供了进入时空传送的手段，得以大幅缩减飞行时间。超空间指的是三维空间以外的替代空间."),
  _T("由离子技术打下的基础进行深入研究，高加速的等离子团被开发成为威力强大的武器，对它的目标造成毁灭性的伤害."),
  _T("帝国最高级的技术，用来研究死星."),
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
  _T("小型运输舰"),
  _T("大型运输舰"),
  _T("轻型战斗机"),
  _T("重型战斗机"),
  _T("巡洋舰"),
  _T("战列舰"),
  _T("殖民船"),
  _T("回收船"),
  _T("探测器"),
  _T("轰炸机"),
  _T("太阳能卫星"),
  _T("毁灭者"),
  _T("死星"),
  _T("")
};

//short name
const CString BOATS_SHORT_NAME[] =
{
  _T("小运"),
  _T("大运"),
  _T("轻战"),
  _T("重歼"),
  _T("巡洋"),
  _T("战列"),
  _T("殖民船"),
  _T("回收船"),
  _T("探测器"),
  _T("轰炸机"),
  _T("太卫"),
  _T("毁灭者"),
  _T("死星"),
  _T("")
};

//description
const CString BOATS_SIMPLE_DISP[] =
{
  _T("小型运输舰是一种轻巧的舰艇，用来将资源从一个星球运送到另一个星球."),
  _T("大型运输舰是从小型运输舰发展来的，拥有更大的货仓和更快的速度."),
  _T("轻型战斗机是一种灵活的舰艇，能在几乎所有的星球上找到。它的花费并不昂贵，它的防护盾能源和装载量也不高."),
  _T("重型战斗机是在轻型战斗机的改进过程中出现的革命性的产物，拥有更强的防护盾和火力."),
  _T("巡洋舰的装甲大约是重型战斗机的3倍，火力强2倍。它的速度也是所有船舰中最快的. "),
  _T("战列舰是舰队的脊梁。它的重型防护，高速，超大的装载空间能让他对抗不断增加的敌人."),
  _T("这种船舰的存在意义，就是为了要探索人类过去从未到达之处，并开拓新世界."),
  _T("回收船用来回收飘浮在宇宙空间里的船舰残骸，再制成可用的资源."),
  _T("小巧灵活的探测器，搭载高效能的推进机构，它能够提供遥远的星球上的信息."),
  _T("轰炸机专门用来摧毁星球上的重型防御装置."),
  _T("太阳能卫星装备了太阳能电池，是构造简单的轨道卫星，它会把搜集到的能量传回到星球的地表上."),
  _T("毀滅者是現知最重型的船艦,搭載的火力強度也是史無前例的."),
  _T("帝国舰队终极王者，威力无尽，当然也需要相当多的资源来制造."),
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
  _T("火箭发射装置"),
  _T("轻型激光炮"),
  _T("重型激光炮"),
  _T("高斯炮"),
  _T("中子炮"),
  _T("等离子武器"),
  _T("小型防护罩"),
  _T("大型防护罩"),
  _T("")
};

//description
const CString DEFENSE_SIMPLE_DISP[] =
{
  _T("火箭发射装置是一种造价低廉，构造简单的防御系统."),
  _T("通过光子集中射击能造成比弹道武器更大的伤害."),
  _T("和轻型激光炮相比，重型激光炮增强了攻击力，其结构也更加坚固."),
  _T("高斯炮能把笨重的炮弹用巨大的电磁场加速并发射出去."),
  _T("中子炮利用发射高能中子束来打击目标，使防护盾不稳定并且烧毁电子设备."),
  _T("等离子武器射出的炮弹，其威力可以媲美小型的太阳爆发。这股破坏性的能量甚至比毁灭者还要强大."),
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