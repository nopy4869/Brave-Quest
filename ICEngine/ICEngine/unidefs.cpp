#ifndef _USE_32BIT_TIME_T
#define _USE_32BIT_TIME_T
#endif
//#define ERR -1

#define ENDINGBYTE '\xFF'
#define sep '\x00'

	typedef unsigned long int statis;
	struct cfg
	{
		int screenheight;		//4
		int halfscreenheight;	//8
		int screenwidth;		//12
		int halfscreenwidth;	//16
		char upbut;
		char downbut;
		char leftbut;
		char rightbut;
		char usebut;
		char menubut;
		char letteru;
		char letterd;
		char letterl;
		char letterr;			//26
	};
	struct character
	{
		char name [13];			//13
		char classname [9]; 	//22
		char symbol;			//23
		int type;				//27
		int leveq;				//31
		char status[4];			//35
		statis level;			//39
		statis exp;				//43
		statis health;			//47
		statis currhealth;		//51
		statis attack;			//55
		statis currattack;		//59
		statis defence;			//63
		statis currdefence;		//67
		statis wisdom;			//71
		statis currwisdom;		//75
		statis resistance;		//79
		statis currresistance;	//83
		statis speed;			//87
		statis currspeed;		//91
		statis luck;			//95
		statis currluck;		//99
		char item [4];			//103
		int spells [32];		//103+32=135							207
	};
	struct baten
	{
		char name [13];
		char classname [9];
		char symbol;
		int type;
		char status[4];
		statis level;
		statis health;
		statis currhealth;
		statis attack;
		statis currattack;
		statis defence;
		statis currdefence;
		statis wisdom;
		statis currwisdom;
		statis resistance;
		statis currresistance;
		statis speed;
		statis currspeed;
		statis luck;
		statis currluck;
		char item [4];
		int spells [32];
		char ai;
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
		unsigned int grouptableexp [256];
		unsigned char itemgrouptable [256] [13];
		signed char itemtable [256] [16];
		char enemyfile [22];
		char startscript [22];
		char startmap [22];
		char banner [5][36];
		char loadmapstrings [1024][1024];
		int parablenum;
		char gameflags [1024][1024];
		char battleflag;
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
