// Scripted.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#ifndef LINUX
	#include <stdio.h>
	#include <stdlib.h>
	#include "strings.h"
	#include <ctype.h>
	#include <time.h>
	#include <ncurses.h>
	#include "unidefs.cpp"
#endif

extern char input [5];  //change if necessary
//extern char screen [80][25];
extern char dbug;
extern struct gameinfo currgame;
extern struct gameinfo gameextentions [8];
extern struct mapdata currmap;
extern struct mapdata nextmap;
extern struct npc menumove;
extern char showmenu;
extern char loadgamemenu;
extern char usebit;
extern int lastframetime;
extern int stuffdone;

extern struct player self;

char filename [13];
FILE *savefile, *loadfile;

int linenum;
int nextlinenum;
int currlinenum;

char trash;
int frunx;
int fruny;

struct scriptstuff filebuff [1024];
struct scriptstuff currlinebuff;

int loadscript (char openfile [13]);
int parsescript(char scriptname[13]);
void cleanlinebuff ();

int give();
int take();
int say();
int flag();
int mmove();
int battle();
int dobattle(int group_number, int base_level);
int checkflag();
int checkitem();
int warp();
int checkexp();
int giveexp();
int makeexp();
int execscript();
int screeneffect();
int userinput();
int goline();
int makehealth();
int partyadd();
int partyrm();
int checkparty();

int loadscript (char openfile [13])
{
	if(dbug)
		wprintw(special[1], "Loading ");
	loadfile = fopen(openfile,"r");
	if(loadfile == FALSE)
	{
		if(dbug)
			wprintw(special[1], "failed.\n");
		return 1;
	}
	else
	fread(&trash,1,1,loadfile);
	fread(&trash,1,1,loadfile);
	fread(&linenum,1,1,loadfile);
	for(frunx = 0; frunx < linenum; frunx++)
	{
		fread(&filebuff[frunx].command,1,1,loadfile);
		fread(&filebuff[frunx].argintone,4,1,loadfile);
		fread(&filebuff[frunx].arginttwo,4,1,loadfile);
		fread(&filebuff[frunx].argintthree,4,1,loadfile);
		fread(&filebuff[frunx].argintfour,4,1,loadfile);
		fread(&filebuff[frunx].argintfive,4,1,loadfile);
		fread(&filebuff[frunx].argstringone,13,1,loadfile);
		fread(&filebuff[frunx].argstringtwo,80,1,loadfile);
	};
	fclose(loadfile);
	if(dbug)
		wprintw(special[1], "sucessful.\n");
	return 0;
}
int movenpcscript()
{
	if(currlinebuff.argintone == -1)
	{
		if(currlinebuff.arginttwo == 1)
			moveme(self.config.upbut);
		if(currlinebuff.arginttwo == 2)
			moveme(self.config.rightbut);
		if(currlinebuff.arginttwo == 3)
			moveme(self.config.downbut);
		if(currlinebuff.arginttwo == 4)
			moveme(self.config.leftbut);
	}
	else
	{
		npcstep(currlinebuff.argintone, currlinebuff.arginttwo);
	}
	return 0;
}

void runline ()
{
	if(currlinebuff.command == 'g')
		give();
	if(currlinebuff.command == 't')
		take();
	if(currlinebuff.command == 's')
		say();
	if(currlinebuff.command == 'f')
		flag();
	if(currlinebuff.command == 'm')
		mmove();
	if(currlinebuff.command == 'b')
		battle();
	if(currlinebuff.command == 'F')
		checkflag();
	if(currlinebuff.command == 'I')
		checkitem();
	if(currlinebuff.command == 'w')
		warp();
	if(currlinebuff.command == 'E')
		checkexp();
	if(currlinebuff.command == 'e')
		giveexp();
	if(currlinebuff.command == 'M')
		makeexp();
	if(currlinebuff.command == 'x')
		execscript();
	if(currlinebuff.command == 'C')
		screeneffect();
	if(currlinebuff.command == 'u')
		userinput();
	if(currlinebuff.command == 'G')
		goline();
	if(currlinebuff.command == 'a')
		partyadd();
	if(currlinebuff.command == 'd')
		partyrm();
	if(currlinebuff.command == 'c')
		checkparty();
	if(currlinebuff.command == '\0')
		currlinenum++;
};
int give()
{
	self.inventory[currlinebuff.argintone] += currlinebuff.arginttwo;
	currlinenum++;
	return 0;
};

int take()
{
	self.inventory[currlinebuff.argintone] -= currlinebuff.arginttwo;
	currlinenum++;
	return 0;
};
int say()
{
	delwin(special[2]);
	delwin(special[3]);
	special[3] = derwin(stdscr, 1, 0, LINES - 2, 0);
	scrollok(special[3], TRUE);
	char checker = 0;
	wprintw(special[3], "\n%s", currlinebuff.argstringtwo);
	wrefresh(special[3]);
//	for(checker = 0; checker <= COLS; checker++)
//	{
//		mvwprintw(special[4], 0, checker, " ");
//	}
//	hang(2);
	while(checker != ERR)
	{
		checker = nbi();
	}
	bi();
//	wclear(special[4]);
	wrefresh(special[4]);
	special[2] = derwin(stdscr, 1, 0, LINES - 2, 0);
	special[3] = derwin(stdscr, 1, 0, LINES - 1, 0);
	currlinenum++;
	return 0;
};
int flag()
{
	currgame.gameflags[currlinebuff.argintone][currlinebuff.arginttwo] = currlinebuff.argintthree;
	currlinenum++;
	return 0;
};
int mmove()
{
	movenpcscript();
	currlinenum++;
	return 0;
};
int battle()
{
	dobattle(currlinebuff.argintone, currlinebuff.arginttwo);
	currlinenum++;
	return 0;
};
int checkflag()
{
	if(currgame.gameflags[currlinebuff.argintone][currlinebuff.arginttwo] == currlinebuff.argintthree)
	{
		currlinebuff.argintone = currlinebuff.argintfour;
		goline();
	}
	else
	{
		currlinebuff.argintone = currlinebuff.argintfive;
		goline();
	}
	return 0;
};
int checkitem()
{
	if((self.inventory[currlinebuff.argintone] > currlinebuff.arginttwo) && (self.inventory[currlinebuff.argintone] < currlinebuff.argintthree))
	{
		currlinebuff.argintone = currlinebuff.argintfour;
		goline();
	}
	else
	{
		currlinebuff.argintone = currlinebuff.argintfive;
		goline();
	}
	return 0;
};
int warp()
{
	self.x = currlinebuff.argintone;
	self.y = currlinebuff.arginttwo;
	if(loadmap(currlinebuff.argstringone) != 0)
	{
		wprintw(special[3], "Map load failed!!!!!\n");
	}
	currlinenum++;
	return 0;
};
int checkexp()
{
	if((currgame.characters[currlinebuff.argintone].exp > currlinebuff.arginttwo) && (currgame.characters[currlinebuff.argintone].exp < currlinebuff.argintthree))
	{
		currlinebuff.argintone = currlinebuff.argintfour;
		goline();
	}
	else
	{
		currlinebuff.argintone = currlinebuff.argintfive;
		goline();
	}
	return 0;
};
int giveexp()
{
	currgame.characters[currlinebuff.argintone].exp += currlinebuff.argintone;
	currlinenum++;
	return 0;
};
int makeexp()
{
	currgame.characters[currlinebuff.argintone].exp = currlinebuff.argintone;
	currlinenum++;
	return 0;
};
int makehealth()
{
	if(currlinebuff.argintone == -1)
		currgame.characters[currlinebuff.argintone].currhealth = currgame.characters[currlinebuff.argintone].currhealth;
	if(currlinebuff.argintone != -1)
		currgame.characters[currlinebuff.argintone].currhealth = currlinebuff.argintone;
	currlinenum++;
	return 0;
};
int execscript()
{
	parsescript(currlinebuff.argstringone);
	currlinenum++;
	return 0;
};
int screeneffect()
{
	if(currlinebuff.argintone == 0)
		clearscreen();
	if(currlinebuff.argintone == 1)
		display();
	currlinenum++;
	return 0;
};
int userinput()
{
	currgame.gameflags[currlinebuff.argintone][currlinebuff.arginttwo] = bie();
	currlinenum++;
	return 0;
};
int goline()
{
	currlinenum = currlinebuff.argintone;
	return 0;
};
int partyadd()
{
	int temporary;
	for(temporary = 0; temporary < 4; temporary++)
	{
		if(self.partyids[temporary] == currlinebuff.argintone)
		{
			currlinenum++;
			return 0;
		}
	}
	for(temporary = 0; temporary < 4; temporary++)
	{
		if(self.partyids[temporary] == 32) 								//signifies empty slot!!!
			{
				self.partyids[temporary] = currlinebuff.argintone;
				break;
			}
	}
	currlinenum++;
	return 0;
};
int partyrm()
{
	int temporary;
	for(temporary = 0; temporary < 4; temporary++)
	{
		if(self.partyids[temporary] == currlinebuff.argintone)
		{
			self.partyids[temporary] = 32;
			break;
		}
	}
	for(temporary = 0; temporary < 4; temporary++)
	{
//		if((self.partyids[3] == 32)&&(self.partyids[4] != 32))
//		{
//			self.partyids[3] = self.partyids[4];
//			self.partyids[4] = 32;
//		}
		if((self.partyids[2] == 32)&&(self.partyids[3] != 32))
		{
			self.partyids[2] = self.partyids[3];
			self.partyids[3] = 32;
		}
		if((self.partyids[1] == 32)&&(self.partyids[2] != 32))
		{
			self.partyids[1] = self.partyids[2];
			self.partyids[2] = 32;
		}
		if((self.partyids[0] == 32)&&(self.partyids[1] != 32))
		{
			self.partyids[0] = self.partyids[1];
			self.partyids[1] = 32;
		}
	}
	currlinenum++;
	return 0;
};
int checkparty()
{
	if(currlinebuff.argintone == 0)
	{
		if((self.partyids[0] == currlinebuff.arginttwo)||(self.partyids[1] == currlinebuff.arginttwo)||(self.partyids[2] == currlinebuff.arginttwo)||(self.partyids[3] == currlinebuff.arginttwo))
		{
			currlinebuff.argintone = currlinebuff.argintfour;
			goline();
		}
		else
		{
			currlinebuff.argintone = currlinebuff.argintfive;
			goline();
		}
	}
	if(currlinebuff.argintone == 1)
	{
		if((self.partyids[0] == 32)||(self.partyids[1] == 32)||(self.partyids[2] == 32)||(self.partyids[3] == 32))
		{
			currlinebuff.argintone = currlinebuff.argintfour;
			goline();
		}
		else
		{
			currlinebuff.argintone = currlinebuff.argintfive;
			goline();
		}
	}
	return 0;
};

void cleanlinebuff ()
{
	currlinebuff.command = 0;
	currlinebuff.argintone = 0;
	currlinebuff.arginttwo = 0;
	currlinebuff.argintthree = 0;
	currlinebuff.argintfour = 0;
	currlinebuff.argintfive = 0;
	for(fruny = 0; fruny < 13; fruny++)
	{
		currlinebuff.argstringone [fruny] = 0;
	};
	for(fruny = 0; fruny < 80; fruny++)
	{
		currlinebuff.argstringtwo [fruny] = 0;
	};
};

int parsescript(char scriptname[13])
{
	int count = 0;
	currlinenum = 0;
	if (loadscript(scriptname) == 1)
		return 1;
	for(;currlinenum <= linenum;)
	{
		if(dbug)
		{
			wclear(special[1]);
			count++;
			wprintw(special[1], "Line: %d",count);
			wrefresh(special[1]);
		}	
		cleanlinebuff();
		currlinebuff.command = filebuff[currlinenum].command;
		currlinebuff.argintone = filebuff[currlinenum].argintone;
		currlinebuff.arginttwo = filebuff[currlinenum].arginttwo;
		currlinebuff.argintthree = filebuff[currlinenum].argintthree;
		currlinebuff.argintfour = filebuff[currlinenum].argintfour;
		currlinebuff.argintfive = filebuff[currlinenum].argintfive;
		strcpy(currlinebuff.argstringone, filebuff[currlinenum].argstringone);
		strcpy(currlinebuff.argstringtwo, filebuff[currlinenum].argstringtwo);
		runline();
	};
	return 0;
};
