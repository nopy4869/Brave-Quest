#ifndef LINUX
	#include "unidefs.cpp"
#endif
#ifdef LINUX
	time_t temploctim;
#endif
char input [5];  //change if necessary
char dbug;
struct gameinfo currgame;
//struct gameinfo gameextentions [8];
struct mapdata currmap;
struct npc menumove;
char showmenu;
char loadgamemenu;
char usebit;

int lastframetime;
int stuffdone;
char justwarped;

struct player self;
struct character battleen [8];

WINDOW *special[5];
WINDOW *bannerwin;
WINDOW *begwin;
WINDOW *botlin;
