#ifndef _USE_32BIT_TIME_T
#define _USE_32BIT_TIME_T
#endif
#define TRUE 1
#define FALSE 0
//#define ERR -1

#define ENDINGBYTE '\xFF'
#define sep '\x00'

	typedef unsigned long int statis;
	struct cfg
	{
		int screenheight;
		int halfscreenheight;
		int screenwidth;
		int halfscreenwidth;
		char upbut;
		char downbut;
		char leftbut;
		char rightbut;
		char usebut;
		char menubut;
		char letteru;
		char letterd;
		char letterl;
		char letterr;
	};
	struct character
	{
		char name [13];
		char symbol;
		char type;
		char leveq;
		char status[4];
		statis level;
		statis exp;
		statis health;
		statis currhealth;
		statis attack;
		statis defence;
		statis wisdom;
		statis resistance;
		statis speed;
		statis luck;
		char item [4];
		int spells [32];
	};
	struct gameinfo
	{
		char name [20];
		struct character characters[16];
		unsigned char chartype [272] [16];
		signed char equatable [40] [8];
		unsigned char enemytable [256] [16];
		unsigned char charactable [16] [16];
		unsigned char grouptable [256] [16];
		signed char itemtable [256] [16];
		char enemyfile [22];
		char startscript [22];
		char startmap [22];
		char banner [5][36];
		char loadmapstrings [1024][1024];
		int parablenum;
		char gameflags [1024][1024];
	};
//	spells
	struct player
	{
		int x;
		int y;
		int step;
		char face;
		statis gold;
		char partyids[4];
		int inventory[1024];
		struct cfg config;
	};
	struct npc
	{
		char name [13];
		char face;
		int x;
		int y;
		char scriptfile [13];
		char movetype;
		int fdepends [1024];
		int fnotif [1024];
		int fdependsnum;
		int fnotifnum;
	};
	struct warp
	{
		int mwx [2];
		int mwy [2];
		char mapname [13];
	};
	struct mapscript
	{
		char scriptfile [13];
		int fdepends [1024];
		int fnotif [1024];
		int fdependsnum;
		int fnotifnum;
		int x;
		int y;
	};
	struct mapdata
	{
		char vernum;
		char vernum2;
		int warpnum;
		char mapname [21];
		struct warp mapwarps [1024];
		int mapx;
		int mapy;
		int fixedx;
		int fixedy;
		int startx;
		int starty;
		char enemytf;
		char startmaptf;
		int enemyent [2][10];
		struct mapscript scriptfilename [1024];
		char map [1024][1024];
		char maperm [1024][1024];
		char mapermol [1024][1024];
		char filename [13];
		struct npc people [1024];
		unsigned char scripts;
		int npcnum;
		char npctf;
		char isloaded;
	};
	
	struct scriptstuff
	{
		char command;
		int argintone;
		int arginttwo;
		int argintthree;
		int argintfour;
		int argintfive;
		char argstringone [13];
		char argstringtwo [80];
	};
