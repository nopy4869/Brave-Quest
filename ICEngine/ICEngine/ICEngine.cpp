// ICEngine.cpp : Defines the entry point for the console application.
//

#ifndef LINUX
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#include <time.h>
	#include <ncurses.h>
	#include "unidefs.cpp"
	#include "gamelogictypedefs.cpp"
#endif

extern char input [5];  //change if necessary
extern char dbug;
extern struct gameinfo currgame;

FILE *gameinfotxt;

int loadgamedata();
int showcharset();
int configuration();
int savegame();
int loadgame();
int display();
int gameloop();
int viewpar();
int viewbanner();
int loadpar(char openfile [21]);
int loadbanner(char openfile [20]);
int loadigi(char openfile [20]);
int loadmap(char mqp[]);
char mname [13];
char scoord;
int maprunx;
extern char showmenu;
extern char loadgamemenu;
extern WINDOW *special[5];
char trash;
char igipath [22];
char bannerpath [20];
char parablepath [21];
char ginfname [13];
char dauthnum [5];
int frunx;
int fruny;

extern int lastframetime;
extern struct player self;
extern char alreadybeendone;
extern char justwarped;

int debug()
{
	int asdf;
	char check;
	for (;;)
		{
			scrollok(stdscr, TRUE);
			dbug = 1;
			wprintw(stdscr, "\n\n");
			wprintw(special[0], "Woohoo DEBUG MODE!");
			wprintw(stdscr, "Turn debug off?\n y/n\n");
			while(check != ERR)
			{
				check = nbi();
			}
			input [0] = bie ();
			wprintw(stdscr, "\n");
			input [0] = tolower (input [0]);
			if (input [0] == 'y')
			{
				dbug = 0;
				wprintw(stdscr, "Debug is off.\n");
			}
			if (input [0] == 27)
			{
					wprintw(stdscr, "Exiting...\n");
					endwin();
					exit(0);
			}
			wprintw(stdscr, "Type 1 to test the savegame function.\nType 2 to test the Loadmap function\nType 3 to test the Display function\nType 4 to test the Input function\nType 5 to enter the gameloop\nType 6 to view charset\nType 7 to view a parable\nType 8 to view the banner\nType 0 to continue the load game sequence\nPressing escape will exit the game\n");
			input [0] = bie ();
			wprintw(stdscr, "\n");
			if (input [0] == '1')
			{
					clear();
					scrollok(stdscr, FALSE);
					savegame ();
					wprintw(stdscr, "Back to debug.\n");
			}
			if (input [0] == '2')
			{
				wprintw(stdscr, "Please type the name of the map.\n");
				for (maprunx = 0; maprunx < 13; maprunx++)
				{	
					mname [maprunx] = bie();
					if (maprunx == 8)
					{
						mname [8] = '.';
						mname [9] = 'i';
						mname [10] = 'm';
						mname [11] = 'f';
						mname [12] = sep;
						maprunx = 13;
					}
					else
					{
						if (mname [maprunx] == '?')
						{
							asdf = maprunx;
							mname [asdf] = '.';
							asdf = asdf + 1;
							mname [asdf] = 'i';
							asdf = asdf + 1;
							mname [asdf] = 'm';
							asdf = asdf + 1;
							mname [asdf] = 'f';
							asdf = asdf + 1;
							mname [asdf] = sep;
							maprunx = 13;
						}
					}
				}
					wprintw(stdscr, "Turn \"set coord\" on?\n y/n\n");
					input [0] = getch ();
					wprintw(stdscr, "\n");
					input [0] = tolower (input [0]);
					if (input [0] == 'y')
					{
						scoord = 1;
						wprintw(stdscr, "Set coord is on.\n");
					}
					clear();
					scrollok(stdscr, FALSE);
					wprintw(stdscr, "Loadmap returned code %d\n", loadmap (mname));
					wprintw(stdscr, "Back to debug.\n");
			}
			if (input [0] == '3')
			{
					wprintw(stdscr, "Type \"y\" to turn menu mode off.\n");
					if(getch() == 'y')
						showmenu = FALSE;
					clear();
					scrollok(stdscr, FALSE);
					display ();
					wprintw(stdscr, "Back to debug.\n");
			}
			if (input [0] == '4')
			{
					wprintw(stdscr, "Removed because it was and will never be used.\nBack to debug.\n");
			}
			if (input [0] == '5')
			{
					clear();
					scrollok(stdscr, FALSE);
					configuration();
					gameloop();
					wprintw(stdscr, "Back to debug.\n");
			}
			if (input [0] == '6')
			{
					wprintw(stdscr, "Printing char set\n");
					clear();
					showcharset();
					wprintw(stdscr, "Back to debug.\n");
			}
			if (input [0] == '7')
			{
					clear();
					viewpar();
					wprintw(stdscr, "Back to debug.\n");
			}
			if (input [0] == '8')
			{
					clear();
					scrollok(stdscr, FALSE);
					viewbanner();
					wprintw(stdscr, "Back to debug.\n");
			}
			if (input [0] == '0')
			{
					return 0;
			}
			if (input [0] == 27)
			{
					wprintw(stdscr, "Exiting...\n");
					endwin();
					exit(0);
			}

		}
	return 0;
}

int configuration()
{
	self.config.screenheight = LINES;
	self.config.halfscreenheight = (self.config.screenheight / 2) - 2;
//	self.config.halfscreenheight += 1;
	self.config.screenwidth = COLS - 4;
	self.config.halfscreenwidth = self.config.screenwidth / 2;
	self.config.upbut = 'w';
	self.config.downbut = 's';
	self.config.leftbut = 'a';
	self.config.rightbut = 'd';
	self.config.usebut = 'e';
	self.config.menubut = '`';
	self.config.letteru = '^';				//u
//	wprintw(stdscr, "%c",self.config.letteru);
	self.config.letterd = 'v';				//d
//	wprintw(stdscr, "%c",self.config.letterd);
	self.config.letterl = '<';				//l
//	wprintw(stdscr, "%c",self.config.letterl);
	self.config.letterr = '>';				//r
//	wprintw(stdscr, "%c",self.config.letterr);
	self.face = 'u';
	if(dbug)
		wprintw(stdscr, "Config stuff written to memory\n");
	alreadybeendone = 0;
//	hang(3);
	return 0;
}

int loadgamedata()
{
//	wprintw(stdscr, "Loading gameinfo data...\n");
	ginfname [0] = 'g';
	ginfname [1] = 'a';
	ginfname [2] = 'm';
	ginfname [3] = 'e';
	ginfname [4] = 'i';
	ginfname [5] = 'n';
	ginfname [6] = 'f';
	ginfname [7] = 'o';
	ginfname [8] = '.';
	ginfname [9] = 't';
	ginfname [10] = 'x';
	ginfname [11] = 't';
	ginfname [12] = '\0';
//	nbi();
	gameinfotxt = fopen(ginfname, "r");
	if (gameinfotxt == FALSE)
	{
		wprintw(stdscr, "Failed.\n\"gameinfo.txt\" not found.\n");
		nbi();
		hang(3);
		endwin();
		exit(1);
	}
	fread(&trash,1,1,gameinfotxt);
	if(trash == '4')
	{
		dauthnum [0] = '4';
	}
	fread(&trash,1,1,gameinfotxt);
	if(trash == '8')
	{
		dauthnum [1] = '8';
	}
	fread(&trash,1,1,gameinfotxt);
	if(trash == '6')
	{
		dauthnum [2] = '6';
	}
	fread(&trash,1,1,gameinfotxt);
	if(trash == '9')
	{
		dauthnum [3] = '9';
	}
	fread(&trash,1,1,gameinfotxt);
	dauthnum [4] = '\0';
	fread(&igipath,21,1,gameinfotxt);
	igipath [21] = '\0';
	fread(&trash,1,1,gameinfotxt);
	fread(&trash,1,1,gameinfotxt);
	fread(&trash,1,1,gameinfotxt);
	fread(&trash,1,1,gameinfotxt);
	fread(&trash,1,1,gameinfotxt);
	fread(&trash,1,1,gameinfotxt);
	fread(&trash,1,1,gameinfotxt);
	fread(&trash,1,1,gameinfotxt);
	fread(&trash,1,1,gameinfotxt);
	fread(&bannerpath,19,1,gameinfotxt);
	bannerpath [19] = '\0';
	fread(&trash,1,1,gameinfotxt);
	fread(&trash,1,1,gameinfotxt);
	fread(&trash,1,1,gameinfotxt);
	fread(&trash,1,1,gameinfotxt);
	fread(&trash,1,1,gameinfotxt);
	fread(&trash,1,1,gameinfotxt);
	fread(&trash,1,1,gameinfotxt);
	fread(&trash,1,1,gameinfotxt);
	fread(&trash,1,1,gameinfotxt);
	fread(&trash,1,1,gameinfotxt);
	fread(&parablepath,20,1,gameinfotxt);
	parablepath [20] = '\0';
//	wprintw(stdscr, "   %s\n",bannerpath);
//	wprintw(stdscr, "   %s\n",igipath);
//	wprintw(stdscr, "   %s\n",parablepath);
//	nbi();
//	hang(5);
	loadbanner(bannerpath);
	loadigi(igipath);
	loadpar(parablepath);
	fclose(gameinfotxt);
//	wprintw(stdscr, "Complete\n");
	refresh();
	return 0;
}

int loadpar (char openfile [])
{
	FILE *loadfile;
	int frunx;
	int fruny;
	loadfile = fopen(openfile,"r");
	if(loadfile == FALSE)
	{
		wprintw(stdscr, "   Loading parable file failed.\n");
		nbi();
		hang(3);
		endwin();
		exit(1);
		return 1;
	}
	else
	{
		fread(&trash,1,1,loadfile);
		fread(&trash,1,1,loadfile);
		fread(&currgame.parablenum,4,1,loadfile);
		for(frunx = 0; frunx < currgame.parablenum; frunx++)
		{
			for(fruny = 0; fruny < 1024; fruny++)
			{
				fread(&currgame.loadmapstrings [frunx][fruny],1,1,loadfile);
			};
		};
	}
	fclose(loadfile);
	return 0;
}

int loadbanner (char openfile [])
{
	FILE *loadfile;
	int frunx;
	int fruny;
	loadfile = fopen(openfile,"r");
	if(loadfile == FALSE)
	{
		wprintw(stdscr, "   Loading banner file failed.\n");
		nbi();
		hang(3);
		endwin();
		exit(1);
		return 1;
	}
	else
	{
		bannerwin = derwin(stdscr, 5, 36, self.config.halfscreenheight - 4, self.config.halfscreenwidth - 18);
		botlin = derwin(stdscr, 1, 0, self.config.halfscreenheight, 0);
		if(bannerwin == 0)
			wprintw(stdscr, "\n\nBanner Window unable to be created.");
		for(frunx = 0; frunx < 5; frunx++)
		{
			for(fruny = 0; fruny < 36; fruny++)
			{
				fread(&currgame.banner [frunx][fruny],1,1,loadfile);
				mvwprintw(bannerwin, frunx, fruny, "%c", currgame.banner[frunx][fruny]);
			};
		};
	}
	fclose(loadfile);
	refresh();
	return 0;
}

int loadigi (char openfile [])
{
	FILE *loadfile;
//	int frunx;
	int fruny;
	loadfile = fopen(openfile,"r");
	if(loadfile == FALSE)
	{
		wprintw(stdscr, "   Loading igi file failed.\n");
		nbi();
		hang(3);
		endwin();
		exit(1);
		return 1;
	}
	else
	{
		char readfile;
		readfile = sep;
		for(fruny = 0;(fruny < 20) && (readfile != '\n'); fruny++)
		{
			fread(&readfile,1,1,loadfile);
			currgame.name[fruny] = readfile;
			if(readfile == '\n')
				currgame.name[fruny] = sep;
		};
		
		currgame.startmap[19] = sep;
		readfile = sep;
		for(fruny = 0;(fruny < 22) && (readfile != '\n'); fruny++)
		{
			fread(&readfile,1,1,loadfile);
			currgame.startscript[fruny] = readfile;
			if(readfile == '\n')
				currgame.startscript[fruny] = sep;
		};
		currgame.startscript[21] = sep;
		readfile = sep;
		for(fruny = 0;(fruny < 22) && (readfile != '\n'); fruny++)
		{
			fread(&readfile,1,1,loadfile);
			currgame.startmap[fruny] = readfile;
			if(readfile == '\n')
				currgame.startmap[fruny] = sep;
		};
		currgame.startmap[21] = sep;
		readfile = sep;
		for(fruny = 0;(fruny < 22) && (readfile != '\n'); fruny++)
		{
			fread(&readfile,1,1,loadfile);
			currgame.enemyfile[fruny] = readfile;
			if(readfile == '\n')
				currgame.enemyfile[fruny] = sep;
		};
		currgame.startmap[21] = sep;
	}
	fclose(loadfile);
	return 0;
}

int viewpar()
{
	int workingparnum = 0;
	wprintw(stdscr, "Please type the parable number.\n");
	nbi();
	workingparnum = intimp();
	for(frunx = 0; frunx < 1024; frunx++)
		wprintw(stdscr, "%c",currgame.loadmapstrings[workingparnum][frunx]);
	wprintw(stdscr, "\n");
	nbi();
	return 0;
};

int viewbanner()
{
	int brunx;
	int bruny;
	wprintw(stdscr, "\n\n");
	for(brunx = 0; brunx < 5; brunx++){
		for(bruny = 0; bruny < 36; bruny++){
			mvwprintw(stdscr, brunx + 2, bruny, "%c",currgame.banner[bruny][brunx]);
		}
		wprintw(stdscr, "\n");
	}
	nbi();
	return 0;
};

int main(int argc, char *argv[])
{
	if(argc > 1)
		if(strcmp(argv[1], "gac") == 0)
			dbug = 1;
	initscr();
	cbreak();
	leaveok(stdscr, TRUE);
	special[0] = derwin(stdscr, 1, 0, 0, 0);
	special[1] = derwin(stdscr, 1, 0, 1, 0);
	special[4] = derwin(stdscr, 1, 0, LINES - 3, 0);
	special[2] = derwin(stdscr, 1, 0, LINES - 2, 0);
	special[3] = derwin(stdscr, 1, 0, LINES - 1, 0);
	scrollok(stdscr, TRUE);
	scrollok(special[0], FALSE);
	scrollok(special[1], FALSE);
	scrollok(special[2], FALSE);
	scrollok(special[3], TRUE);
	scrollok(special[4], FALSE);
	self.config.screenheight = LINES;
	self.config.halfscreenheight = (self.config.screenheight / 2) - 2;
	self.config.screenwidth = COLS - 4;
	self.config.halfscreenwidth = self.config.screenwidth / 2;
	loadgamedata();
	loadenemies(currgame.enemyfile);
	configuration();
	hang(3);
	char check = 0;
	while(check != ERR)
	{
		check = nbi();
	}
	bi();
	for(;;)
	{
		justwarped = 0;
		lastframetime = 0;
//		if(strcmp(dauthnum, "4869") == 0)
//			debug();
		begmen();
//		newgamemenu();
		gameloop();
	}
	return 0;
}
