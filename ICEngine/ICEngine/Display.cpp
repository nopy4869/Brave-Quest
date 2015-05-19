#ifndef LINUX
	#include <stdio.h>
	#include <stdlib.h>
	#include <ctype.h>
	#include <time.h>
	#include <ncurses.h>
	#include "unidefs.cpp"
	#include "gamelogictypedefs.cpp"
#endif

extern WINDOW *special[5];
extern char dbug;
extern char showmenu;
extern char gamestate;
extern struct mapdata currmap;
extern struct player self;
extern int lastframetime;
extern int stuffdone;					//Stuff done is only non zero if you didsomething between frames

signed int dispmaprunx;
signed int dispmapruny;

int dispmenu();

int clearscreen ()
{
	clear();
	refresh();
	return 0;
};

int display ()
{
	int widthbufmin;
	int heightbufmin;
	int widthbufmax;
	int heightbufmax;
	if((unsigned)time(NULL) == lastframetime)
		 if(stuffdone == 0)	
			return 0;
	lastframetime = (unsigned)time(NULL);
	stuffdone = 0;
	if(dbug)
		wprintw(special[3], "display has been called\n");
	if(showmenu == TRUE)
	{
		dispmenu();
	}
	clear();
	
	if(LINES != self.config.screenheight)
	{
		delwin(special[2]);
		delwin(special[3]);
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
	}
	
	widthbufmin = self.x - self.config.halfscreenwidth;

	heightbufmin = self.y - self.config.halfscreenheight;

	widthbufmax = self.x + self.config.halfscreenwidth;

	heightbufmax = self.y + self.config.halfscreenheight;
		
	wprintw(stdscr, "\n\n");

	for(dispmapruny = heightbufmin; dispmapruny < heightbufmax; dispmapruny++)
	{
		for(dispmaprunx = widthbufmin; dispmaprunx < widthbufmax; dispmaprunx++)
			{
				if((dispmaprunx < 0) || (dispmapruny < 0))
				{
					wprintw(stdscr, " ");
					goto endloop;
				}
				else
				{
					if((dispmaprunx == self.x) && (dispmapruny == self.y))
					{
						if(self.face == 'u')
							wprintw(stdscr, "%c",self.config.letteru);
						if(self.face == 'd')
							wprintw(stdscr, "%c",self.config.letterd);
						if(self.face == 'l')
							wprintw(stdscr, "%c",self.config.letterl);
						if(self.face == 'r')
							wprintw(stdscr, "%c",self.config.letterr);
					}
					else
					{
						wprintw(stdscr, "%c",currmap.map[dispmaprunx][dispmapruny]);
					}
				}
				endloop:;
			}
			wprintw(stdscr, "\n");
	}
	for(dispmaprunx = 0; dispmaprunx < 20; dispmaprunx++){
		mvwprintw(special[0], 0, dispmaprunx,"%c", currmap.mapname[dispmaprunx]);
	}
	refresh();
	return 0;
};
