// Sensei.cpp : Defines the entry point for the console application.
//

#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define VERSION '\x01'
#define VERSION2 '\x00'

char spelltablevernum = VERSION;
char spelltablevernum2 = VERSION2;
char sep = '\x00';
char end = '\xFF'; 

extern char filename [13];
FILE *savefile, *loadfile;

int frunx;
int fruny;
int stnum;
int workingstnum;
char trash;

int loadst (char openfile [13]);
int savest (char openfile [13]);
int impst();
int dumpst();

int addst();
int sted();
int clearst();
int viewst();

void plusone (char eqench);
void minusone (char eqench);
void checkone (char eqench);

int input [3];
int metatable[544];
int workingst[1024][2];
int spelltable[544][1024][2];

#include "Common functions.cpp"

int main(int argc, char* argv[])
{
	char check; 
	initscr();
	cbreak();
	nodelay(stdscr, FALSE);
	scrollok(stdscr, TRUE);
	wprintw(stdscr, "This is Sensei ver. %d.%d for the Brave Quest engine.\nCopyright 2015 Mad Science Inc.\nPlease do not redistrubute.\nLoads .gst files!\nPress any key to continue!\n\n",spelltablevernum,spelltablevernum2);
	hang(1);
	while(check != ERR)
	{
		check = nbi();
	}
	bi();
	stufffilename();
	if(loadst(filename) == 1)
	{
		wprintw(stdscr, "File %s not Found. Would you like to make a new file?\n", filename);
		if(bie() == 'y')
		{
			stnum = 0;
//			for(frunx = 0; frunx < 256; frunx++)
//				for(fruny = 0; fruny < 16; fruny++)
//					enemytable[frunx][fruny] = sep;
			if(savest(filename) == 1)
			{
				wprintw(stdscr, "Your disk sucks.\n");
				bi();
				return 1;
			}
		}
	}
	
	sted();
	return 0;
};

int sted()
{
	for(;;)
	{
		clear();
		refresh();
		wprintw(stdscr, "To add a character type press 1.\nTo view an character type press 4.\nTo save the enemy file press 7.\nTo save the enemy file under a different name press 8.\nTo edit enemies press 9\nTo delete a character type press 0.\n");
		input [0] = bie();
		if(input[0] == '1')
			addst();
		if(input[0] == '4')
			viewst();
		if(input[0] == '7')
			savest(filename);
		if(input[0] == '8')
		{
			stufffilename();
			savest(filename);
		}
		if(input[0] == '9')
			break;
		if(input[0] == '.')
			plusone(3);
		if(input[0] == ',')
			minusone(3);
		if(input[0] == '/')
			checkone(3);
		if(input[0] == '0')
			clearst();
		wprintw(stdscr, "Press any key to continue.\n");
		bie();
	}
	return 0;
}

int loaden (char openfile [13])
{
	wprintw(stdscr, "Loading %s ",filename);
	wrefresh(stdscr);
	loadfile = fopen(openfile,"rb");
	if(loadfile == FALSE)
	{
		wprintw(stdscr, "failed.\n");
		return 1;
	}
	else
	{
		fread(&trash,1,1,loadfile);
		fread(&trash,1,1,loadfile);
		if(trash == 0)
		{
		}
		fclose(loadfile);
	}
	wprintw(stdscr, "sucessful.\n");
	return 0;
}

int saveen (char openfile [13])
{
	wprintw(stdscr, "Saving ");
	wrefresh(stdscr);
	savefile = fopen(openfile,"wb+");
	if (savefile == FALSE)
	{
		wprintw(stdscr, "failed.\n");
		return 1;
	}
	else
	{
		fwrite(&spelltablevernum,1,1,savefile);
		fwrite(&spelltablevernum2,1,1,savefile);
		fclose(loadfile);
	}
	wprintw(stdscr, "sucessful.\n");
	return 0;
};

int addst()
{
	wprintw(stdscr, "Go back? y/n\n");
	if (bie() == 'y')
		return 2;
	workingstnum = stnum;
	wprintw(stdscr, "Please type your character's default name.\nPress escape to end input.\n");
	for (frunx = 0;(input[1] != 27) && (frunx < 12);frunx++)
	{
		input[1] = bie();
		if(input[1] == 27)
		{
			break;
		}
		workingst[frunx] = input[1];
		if(input[1] == 13)
		{
			break;
		}
		if(input[1] == 8)
		{
			frunx--;
			frunx--;
		}
	}
	workingch[12] = sep;
	wprintw(stdscr, "Please type your character's Character.\n");
	workingch[13] = bie();
	wprintw(stdscr, "Please type your character's Level from experience equation number.\n");
	workingch[14] = intimp();
	wprintw(stdscr, "Please type your character's class number.\n");
	workingch[15] = intimp();
	wprintw(stdscr, "Comitting to character table now.\n");
	for(frunx = 0; frunx < 16; frunx++)
	{
		charactable [workingchnum][frunx] = workingch[frunx];
	}
	characternum = workingchnum + 1;
	input[1] = 0;
	for(frunx = 0; frunx < 16; frunx++)
	{
		workingch[frunx] = 0;
	}
	wprintw(stdscr, "Done.\n");
	return 0;
};

int clearst()
{
	wprintw(stdscr, "Go back? y/n\n");
	if (bie() == 'y')
		return 2;
	wprintw(stdscr, "Which table do you want to wipe?");
	workingstnum = intimp();
	metatable[workingstnum] = 0;
	for(frunx = 0; frunx < 1024; frunx++)
	{
		for(fruny = 0; fruny < 2; fruny++)
		{
			spelltable[workingstnum][frunx][fruny] = 0;
		}
	}
	wprintw(stdscr, "Wiped table %d.\n", workingstnum);
	return 0;
};

int viewst()
{
	wprintw(stdscr, "Please type the character number.\n");
	workingstnum = intimp();
	for(frunx = 0; frunx < metatable[workingstnum]; frunx++)
	{
			wprintw(stdscr, "Level: %d\n Spell number: %d\n\n",spelltable[workingstnum][frunx][0], spelltable[workingstnum][frunx][1]);
	}
	refresh();
	return 0;
};

void plusone (char eqench)
{
		workingstnum += 1;
};

void minusone (char eqench)
{
		workingstnum -= 1;
};

void checkone (char eqench)
{
	if(eqench == 1)
		wprintw(stdscr, "%d\n", workingstnum);
};

void checkline (char eqench)
{
	if(eqench == 1)
		wprintw(stdscr, "Line: %d\n Level: %d\n Spell: %d\n\n", eqench, spelltable[workingstnum][eqench][0], spelltable[workingstnum][eqench][1]);
};

