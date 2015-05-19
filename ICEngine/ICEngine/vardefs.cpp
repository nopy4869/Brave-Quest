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
char gamestate;


/*
 * 
 * Currently defined GAMESTATES:
 * 
 * 			0 (no game mode)
 * 			1 (first game menu)
 * 			2 (in game)
 * 			3 (pause menu)
 * 			4 (script)
 * 			5 (battle)
 * 
 */
enum states {OUT_OF_GAME, BANNER_MENU, GAME, PAUSE, SCRIPT, BATTLE};



char usebit;

int lastframetime;
int stuffdone;
char justwarped;

struct player self;
struct baten battleen [6];

WINDOW *special[5];
WINDOW *bannerwin;
WINDOW *begwin;
//WINDOW *botlin;
