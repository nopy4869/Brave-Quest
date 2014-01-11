#ifndef LINUX
	#include <stdio.h>
	#include <stdlib.h>
	#include <ctype.h>
	#include <time.h>
	#include <ncurses.h>
	#include "unidefs.cpp"
#endif

int loadmap(char mqp[13]);
int loadsave();
int configed();
int parsescript();

extern char input [5];  //change if necessary
extern char dbug;
extern char scoord;
extern char loadgamemenu;
extern char alreadybeendone;
extern char justwarped;

extern struct gameinfo currgame;
extern struct mapdata currmap;
extern struct npc menumove;
extern struct player self;
extern struct npc menumove;

int warprunx;
int warpruny;
char mede;
char meic;
char fest;

int showcharset ()
{
	unsigned char q;
	for(q = 0; q < 255; q++)
		wprintw(stdscr, "%c",q);
	q = 255;
	wprintw(stdscr, "%c",q);
	q = 16;				//r
	wprintw(stdscr, "%c",q);
	q = 17;				//l
	wprintw(stdscr, "%c",q);
	q = 30;				//u
	wprintw(stdscr, "%c",q);
	q = 31;				//d
	wprintw(stdscr, "%c",q);
	getch();
	return 0;
}

int hang (int howlonghang)
{
	int lol;
	int templocaltime;
	#ifndef LINUX
		templocaltime = _time32(NULL);
	#endif
	#ifdef LINUX
		templocaltime = time(&temploctim);
	#endif
	lol = templocaltime + howlonghang;
	for(;;)
	{
		#ifndef LINUX
			templocaltime = _time32(NULL);
		#endif
		#ifdef LINUX
			templocaltime = time(&temploctim);
		#endif
		if(lol == templocaltime)
			break;
	}
	return 0;
};

int diceroll ()
{
	int diceroll;
	srand ((unsigned)time(NULL));
	diceroll = rand() % 100;
	diceroll = diceroll + 1;
	return (diceroll);
};

int warpfollow(int warpx, int warpy, char scoordval)
{
	if(justwarped == TRUE)
		return 0;
	wclear(special[2]);
	wclear(special[3]);
	wclear(special[4]);
	for(warprunx = 0; warprunx < currmap.warpnum; warprunx++)
	{
		if(currmap.mapwarps [warprunx].mwx [0] == warpx)
			if(currmap.mapwarps [warprunx].mwy [0] == warpy)
				break;
	}
	scoord = scoordval;
	self.x = currmap.mapwarps [warprunx].mwx [1];
	self.y = currmap.mapwarps [warprunx].mwy [1];
	loadmap(currmap.mapwarps [warprunx].mapname);
	if(!scoordval)
	{
		self.x = currmap.mapwarps [warprunx].mwx [1];
		self.y = currmap.mapwarps [warprunx].mwy [1];
	}
	return 0;
};

int scriptexec(int warpx, int warpy)
{
	wclear(special[2]);
	wclear(special[3]);
	wclear(special[4]);
	for(warprunx = 0; warprunx < currmap.warpnum; warprunx++)
	{
		if(currmap.scriptfilename [warprunx].x == warpx)
			if(currmap.scriptfilename [warprunx].y == warpy)
				break;
	}
	char flagged = 0;
	for(warpruny = 0; warpruny < currmap.scriptfilename[warprunx].fnotifnum; warpruny++)
	{
		if(currgame.gameflags[0][currmap.scriptfilename[warprunx].fnotif[warpruny]] != 0)
			flagged = 1;
	}
	for(warpruny = 0; warpruny < currmap.scriptfilename[warprunx].fdependsnum; warpruny++)
	{
		if(currgame.gameflags[0][currmap.scriptfilename[warprunx].fdepends[warpruny]] == 0)
			flagged = 1;
	}
	if (flagged == 0)
		parsescript(currmap.scriptfilename[warprunx].scriptfile);
	warprunx = 0;
	warpruny = 0;
	return 0;
};

int dispmenu()
{
	return 0;
};

int configed ()
{
	char check;
	char newchar;
	wprintw(stdscr, "To change the buttons press 1\n");
	newchar = getch();
	if(newchar == '1')
	{
		wprintw(stdscr, "\nPress your up button.\n");
		while(check != ERR)
			{
				check = nbi();
			}
		self.config.upbut = bie();
		wprintw(stdscr, "\nPress your down button.\n");
		while(check != ERR)
			{
				check = nbi();
			}
		self.config.downbut = bie();
		wprintw(stdscr, "\nPress your left button.\n");
		while(check != ERR)
			{
				check = nbi();
			}
		self.config.leftbut = bie();
		wprintw(stdscr, "\nPress your right button.\n");
		while(check != ERR)
			{
				check = nbi();
			}
		self.config.rightbut = bie();
		wprintw(stdscr, "\nPress your use button.\n");
		while(check != ERR)
			{
				check = nbi();
			}
		self.config.usebut = bie();
		wprintw(stdscr, "\nPress your menu button.\n");
		while(check != ERR)
			{
				check = nbi();
			}
		self.config.menubut = bie();
	};
	self.config.letteru = '^';				//u
	wprintw(stdscr, "%c",self.config.letteru);
	self.config.letterd = 'v';				//d
	wprintw(stdscr, "%c",self.config.letterd);
	self.config.letterl = '<';				//l
	wprintw(stdscr, "%c",self.config.letterl);
	self.config.letterr = '>';				//r
	wprintw(stdscr, "%c",self.config.letterr);
	alreadybeendone = 0;
	hang(3);
	return 0;
};

void begmen()
{
	loadgamemenu = 1;
	char inp;
	begwin = derwin(stdscr, 3, 0, self.config.halfscreenheight + 2, self.config.halfscreenwidth - 5);
	if(LINES != self.config.screenheight)
	{
		delwin(special[2]);
		delwin(special[3]);
		delwin(special[4]);
		special[4] = derwin(stdscr, 1, 0, LINES - 3, 0);
		special[2] = derwin(stdscr, 1, 0, LINES - 2, 0);
		special[3] = derwin(stdscr, 1, 0, LINES - 1, 0);
		scrollok(special[2], FALSE);
		scrollok(special[3], TRUE);
		scrollok(special[4], FALSE);
		self.config.screenheight = LINES;
		self.config.halfscreenheight = (self.config.screenheight / 2) - 2;
		self.config.screenwidth = COLS - 4;
		self.config.halfscreenwidth = self.config.screenwidth / 2;
		begwin = derwin(stdscr, 3, 0, self.config.halfscreenheight + 2, self.config.halfscreenwidth - 5);
	}
	mede = 0;
	meic = 0;
	fest = 0;
	while(fest != 127)
	{
		inp = bi();
		if(inp != ERR)
			begparseinp(inp);
		begmendisp();
	}
};

void begmenmove(char dir)
{
	char test;
	if((dir == 'u')&&(meic != 0))
		meic--;
	if((dir == 'd')&&(meic != 2))
		meic++;
	if((dir == 'r')&&(mede != 1)&&(meic == 0))
	{
		scoord = 1;
		test = loadmap(currgame.startmap);
		if(test == 0)
		{
			loadgamemenu = FALSE;
			fest = 127;
			display();
			parsescript(currgame.startscript);
			return;
		}
		if(test == 1)
		{
			wprintw(stdscr, "Loading game failed.\n");
		}
	}
	
	if((dir == 'r')&&(mede != 1)&&(meic == 1))
	{
		mede++;
		meic = 0;
	}
	if((dir == 'r')&&(mede != 1)&&(meic == 2))
		configed();
	if((dir == 'l')&&(mede == 1))
	{
		mede--;
		meic = 1;
	}
}

void begparseinp(int but)
{
	if(but == self.config.upbut)
		begmenmove('u');
	if(but == self.config.downbut)
		begmenmove('d');
	if((but == self.config.rightbut)||(but == '\n'))
		begmenmove('r');
	if((but == self.config.leftbut)||(but == 27))
		begmenmove('l');
}

void begmendisp()
{
	clear();
	wclear(botlin);
	int frunx, fruny;
	if(LINES != self.config.screenheight)
	{
		clear();
		delwin(special[2]);
		delwin(special[3]);
		delwin(special[4]);
		delwin(begwin);
		delwin(bannerwin);
		delwin(botlin);
		special[4] = derwin(stdscr, 1, 0, LINES - 3, 0);
		special[2] = derwin(stdscr, 1, 0, LINES - 2, 0);
		special[3] = derwin(stdscr, 1, 0, LINES - 1, 0);
		scrollok(special[2], FALSE);
		scrollok(special[3], TRUE);
		scrollok(special[4], FALSE);
		self.config.screenheight = LINES;
		self.config.halfscreenheight = (self.config.screenheight / 2) - 2;
		self.config.screenwidth = COLS - 4;
		self.config.halfscreenwidth = self.config.screenwidth / 2;
		begwin = derwin(stdscr, 3, 0, self.config.halfscreenheight + 2, self.config.halfscreenwidth - 5);
		bannerwin = derwin(stdscr, 5, 36, self.config.halfscreenheight - 4, self.config.halfscreenwidth - 18);
		botlin = derwin(stdscr, 1, 0, self.config.halfscreenheight, 0);
	}
	for(frunx = 0; frunx < 4; frunx++)
	{
		for(fruny = 0; fruny < 36; fruny++)
		{
			mvwprintw(bannerwin, frunx, fruny, "%c", currgame.banner[frunx][fruny]);
		};
	};
	wclear(begwin);
	if(mede == 0)
		wprintw(begwin, " New Game\n Load Game\n Edit buttons\n");
	if(mede == 1)
		wprintw(begwin, " File 1\n File 2\n File 3\n");
	mvwprintw(begwin, meic, 0, ">");
	refresh();
}

