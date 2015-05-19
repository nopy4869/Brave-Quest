// Scripted.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <ncurses.h>

//#define TRUE 1
#define FALSE 0
#define VERSION '\x01'
#define VERSION2 '\x00'

char scriptedvernum = VERSION;
char scriptedvernum2 = VERSION2;
char sep = '\x00';
char end = '\xFF';

extern char filename [13];
FILE *savefile, *loadfile;

char input [5];
int frunx;
int fruny;
int linenum [512];
int spellnum;
char trash;
int currlinenum;
int currspellnum;

struct scriptstuff
{
	char command;
	unsigned int argintone;
	unsigned int arginttwo;
	unsigned int argintthree;

};

char openspells [512];
struct scriptstuff spellbuff [512][512];
struct scriptstuff currlinebuff;

int loadscript (char openfile [13]);
int savescript (char openfile [13]);

void menu (char m);
void supermenu ();
void cleanspellbuff ();
void cleanlinebuff ();
void ChangeSpells();
void ShowOpen();

int AddStat();
int SubStat();
int MultStat();
int DivStat();
int ChangeStat();
int BranchStat();
int BranchStatPartTwo();
int blank();
int changeline();
int showline();

#include "Common functions.cpp"

int main(int argc, char* argv[])
{
	initscr();
	scrollok(stdscr, TRUE);
	wprintw(stdscr, "Welcome to Speller ver. %d.%d for the Brave Quest engine.\nCopyright 2015 Mad Science Inc.\nPlease do not redistrubute.\n",scriptedvernum,scriptedvernum2);
	stufffilename();
	if(loadscript(filename) == 1)
	{
		wprintw(stdscr, "File not Found. Would you like to make a new file?\n");
		if(bie() == 'y')
		{
			cleanspellbuff();
			if(savescript(filename) == 1)
			{
				wprintw(stdscr, "Your disk sucks.\n");
				bi();
				return 1;
			}
		}
		else
		{
			wprintw(stdscr, "Goodbye.\n");
			endwin();
			return 1;
		}
	}
	currlinenum = linenum[currspellnum];
	supermenu();
	return 0;
};

int meinloop()
{
	wprintw(stdscr, "Press escape to go to the save menu\n");
	for(;;)
	{
		wprintw(stdscr, "Now editing spell: %d\n", currspellnum);
		wprintw(stdscr, "q= give, w= take, e= say, r= flag, t= move, y= battle\n");
		wprintw(stdscr, "m= blank, ,= show line, .= change line.\n");
		input[0] = bie();
		if(input[0] == 27)
			return 0;
		if(input[0] == 'q')
			AddStat();
		if(input[0] == 'w')
			SubStat();
		if(input[0] == 'e')
			MultStat();
		if(input[0] == 'r')
			DivStat();
		if(input[0] == 't')
			ChangeStat();
		if(input[0] == 'y')
			BranchStat();
		if(input[0] == 'm')
			blank();
		if(input[0] == ',')
			showline();
		if(input[0] == '.')
			changeline();
		if(currlinenum > linenum[currspellnum])
			linenum[currspellnum] = currlinenum;
	}
	return 0;
}

void menu (char m)
{
	if(m == 'm')
		meinloop();
	wprintw(stdscr, "To return to editing, press 1.\nTo save all open spells, press 2.\nTo discard changes to all open spells and reload the file, press 3.\nTo save and switch spells, press 4\nTo switch spells without saving, press 5\nTo exit, press 0.\n");
	input [1] = bie();
	if(input[1] == '1')
		meinloop();
	if(input[1] == '2')
		savescript(filename);
	if(input[1] == '3')
		loadscript(filename);
	if(input[1] == '4')
	{
		savescript(filename);
		openspells[currspellnum] = 'n';
		return;
	}
	if(input[1] == '5')
		return;
	if(input[1] == '0')
	{
		openspells[currspellnum] = 'y';
		return;
	}
};

void supermenu()
{
	wprintw(stdscr, "To return to editing, press 1.\nTo select a new spell, press 2.\nTo show open spells, press 3.\nTo save the file, press 4.\nTo save under a different name, press 5.\nTo reload the file, press 6.\nTo exit, press 0.\n");
	input [1] = bie();
	if(input[1] == '1')
		menu('m');
	if(input[1] == '2')
		ChangeSpells();
	if(input[1] == '3')
		ShowOpen();
	if(input[1] == '4')
		savescript(filename);
	if(input[1] == '5')
	{
		stufffilename();
		savescript(filename);
	}
	if(input[1] == '6')
		loadscript(filename);
	if(input[1] == '0')
	{
		exit(0);
	}
};

void ChangeSpells()
{
	wprintw(stdscr, "Spell number?\n");
	currspellnum = intimp();
}

void ShowOpen()
{
	int x;
	for(x = 0; x < 512; x++)
	{
		if(openspells[x] == 'y')
			printf("Spell %d\n",x);
	}
}

int loadscript (char openfile [13])
{
	wprintw(stdscr, "Loading ");
	loadfile = fopen(openfile,"r");
	if(loadfile == FALSE)
	{
		wprintw(stdscr, "failed.\n");
		return 1;
	}
	else
	fread(&trash,1,1,loadfile);
	fread(&trash,1,1,loadfile);
	fread(&spellnum,4,1,loadfile);
	for(frunx = 0; frunx < spellnum; frunx++)
	{
		fread(&linenum[frunx],4,1,loadfile);
		for(fruny = 0; fruny < spellnum; fruny++)
		{
			fread(&spellbuff[frunx][fruny].command,1,1,loadfile);
			fread(&spellbuff[frunx][fruny].argintone,4,1,loadfile);
			fread(&spellbuff[frunx][fruny].arginttwo,4,1,loadfile);
			fread(&spellbuff[frunx][fruny].argintthree,4,1,loadfile);
		}
	};
	fclose(loadfile);
	wprintw(stdscr, "sucessful.\n");
	return 0;
}

int savescript (char openfile [13])
{
//	for(;spellbuff[linenum].command != '\0';linenum++){}
	
	wprintw(stdscr, "Saving ");
	savefile = fopen(openfile,"wb");
	if (savefile == FALSE)
	{
		wprintw(stdscr, "failed.\n");
		return 1;
	}
	fwrite(&scriptedvernum,1,1,savefile);
	fwrite(&scriptedvernum2,1,1,savefile);
	fwrite(&spellnum,4,1,savefile);
	for(frunx = 0; frunx < spellnum; frunx++)
	{
		fwrite(&linenum[frunx],4,1,savefile);
		for(fruny = 0; fruny < linenum[frunx]; fruny++)
		{
			fwrite(&spellbuff[frunx][fruny].command,1,1,savefile);
			fwrite(&spellbuff[frunx][fruny].argintone,4,1,savefile);
			fwrite(&spellbuff[frunx][fruny].arginttwo,4,1,savefile);
			fwrite(&spellbuff[frunx][fruny].argintthree,4,1,savefile);
		}
	};
	fclose(savefile);
	wprintw(stdscr, "sucessful.\n");
	return 0;
};

void cleanspellbuff()
{
	linenum[currspellnum] = 0;
	trash = 0;
	currlinenum = 0;
	for(frunx = 0; frunx < 512; frunx++)
	{
		spellbuff[currspellnum][frunx].command = 0;
		spellbuff[currspellnum][frunx].argintone = 0;
		spellbuff[currspellnum][frunx].arginttwo = 0;
		spellbuff[currspellnum][frunx].argintthree = 0;
	};
};

void cleanlinebuff ()
{
	currlinebuff.command = 0;
	currlinebuff.argintone = 0;
	currlinebuff.arginttwo = 0;
	currlinebuff.argintthree = 0;
};

int blank()
{
	spellbuff[currspellnum][currlinenum].command = 0;
	spellbuff[currspellnum][currlinenum].argintone = 0;
	spellbuff[currspellnum][currlinenum].arginttwo = 0;
	spellbuff[currspellnum][currlinenum].argintthree = 0;
	return 0;
}

int changeline()
{
	wprintw(stdscr, "Current line is %d. What line do you want to change to?\n", currlinenum);
	currlinenum = intimp();
	return 0;
}

int showline()
{
	int tempcurrline;
	wprintw(stdscr, "What line do you want to view?\n", currlinenum);
	tempcurrline = intimp();
	wprintw(stdscr, "Command: %c\nInt 1: %d\nInt 2: %d\nInt 3: %d\n",spellbuff[currspellnum][tempcurrline].command, spellbuff[currspellnum][tempcurrline].argintone, spellbuff[currspellnum][tempcurrline].arginttwo, spellbuff[currspellnum][tempcurrline].argintthree);
	refresh();
	return 0;
}

int AddStat()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'AddStat'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	wprintw(stdscr, "Stat number?\n");
	currlinebuff.argintone = intimp();
	wprintw(stdscr, "Random number for the range?\n Press 'y' for yes.\n");
	if(bie() == 'y')
	{
		currlinebuff.command = 'A';
		wprintw(stdscr, "Upper bound?\n");
		currlinebuff.arginttwo = intimp();
	}
	else
	{
		currlinebuff.command = 'a';
		wprintw(stdscr, "How much?.\n");
		currlinebuff.arginttwo = intimp();
	}
	wprintw(stdscr, "Commiting to Script file buffer\n");
	spellbuff[currspellnum][currlinenum].command = currlinebuff.command;
	spellbuff[currspellnum][currlinenum].argintone = currlinebuff.argintone;
	spellbuff[currspellnum][currlinenum].arginttwo = currlinebuff.arginttwo;
	spellbuff[currspellnum][currlinenum].argintthree = currlinebuff.argintthree;
	currlinenum++;
	return 0;
};

int SubStat()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'SubStat'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	wprintw(stdscr, "Stat number?\n");
	currlinebuff.argintone = intimp();
	wprintw(stdscr, "Random number for the range?\n Press 'y' for yes.\n");
	if(bie() == 'y')
	{
		currlinebuff.command = 'S';
		wprintw(stdscr, "Upper bound?\n");
		currlinebuff.arginttwo = intimp();
		wprintw(stdscr, "Lower bound?\n");
		currlinebuff.argintthree = intimp();
	}
	else
	{
		currlinebuff.command = 's';
		wprintw(stdscr, "How much?\n");
		currlinebuff.arginttwo = intimp();
	}
	wprintw(stdscr, "Commiting to Script file buffer\n");
	spellbuff[currspellnum][currlinenum].command = currlinebuff.command;
	spellbuff[currspellnum][currlinenum].argintone = currlinebuff.argintone;
	spellbuff[currspellnum][currlinenum].arginttwo = currlinebuff.arginttwo;
	spellbuff[currspellnum][currlinenum].argintthree = currlinebuff.argintthree;
	currlinenum++;
	return 0;
};

int MultStat()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'MultStat'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	wprintw(stdscr, "Stat number?\n");
	currlinebuff.argintone = intimp();
	wprintw(stdscr, "Random number for the range?\n Press 'y' for yes.\n");
	if(bie() == 'y')
	{
		currlinebuff.command = 'M';
		wprintw(stdscr, "Upper bound?\n");
		currlinebuff.arginttwo = floimp();
		wprintw(stdscr, "Lower bound?\n");
		currlinebuff.argintthree = floimp();
	}
	else
	{
		currlinebuff.command = 'm';
		wprintw(stdscr, "How much?\n");
		currlinebuff.arginttwo = floimp();
	}
	wprintw(stdscr, "Commiting to Script file buffer\n");
	spellbuff[currspellnum][currlinenum].command = currlinebuff.command;
	spellbuff[currspellnum][currlinenum].argintone = currlinebuff.argintone;
	spellbuff[currspellnum][currlinenum].arginttwo = floatpacker(currlinebuff.arginttwo);
	spellbuff[currspellnum][currlinenum].argintthree = floatpacker(currlinebuff.argintthree);
	currlinenum++;
	return 0;
};

int DivStat()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'DivStat'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	wprintw(stdscr, "Stat number?\n");
	currlinebuff.argintone = intimp();
	wprintw(stdscr, "Random number for the range?\n Press 'y' for yes.\n");
	if(bie() == 'y')
	{
		currlinebuff.command = 'D';
		wprintw(stdscr, "Upper bound?\n");
		currlinebuff.arginttwo = floimp();
		wprintw(stdscr, "Lower bound?\n");
		currlinebuff.argintthree = floimp();
	}
	else
	{
		currlinebuff.command = 'd';
		wprintw(stdscr, "How much?\n");
		currlinebuff.arginttwo = floimp();
	}
	wprintw(stdscr, "Commiting to Script file buffer\n");
	spellbuff[currspellnum][currlinenum].command = currlinebuff.command;
	spellbuff[currspellnum][currlinenum].argintone = currlinebuff.argintone;
	spellbuff[currspellnum][currlinenum].arginttwo = floatpacker(currlinebuff.arginttwo);
	spellbuff[currspellnum][currlinenum].argintthree = floatpacker(currlinebuff.argintthree);
	currlinenum++;
	return 0;
};

int ChangeStat()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'ChangeStat'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	wprintw(stdscr, "Stat number?\n");
	currlinebuff.argintone = intimp();
	wprintw(stdscr, "Random number for the range?\n Press 'y' for yes.\n");
	if(bie() == 'y')
	{
		currlinebuff.command = 'C';
		wprintw(stdscr, "Upper bound?\n");
		currlinebuff.arginttwo = intimp();
		wprintw(stdscr, "Lower bound?\n");
		currlinebuff.argintthree = intimp();
	}
	else
	{
		currlinebuff.command = 'c';
		wprintw(stdscr, "How much?\n");
		currlinebuff.arginttwo = intimp();
	}
	wprintw(stdscr, "Commiting to Script file buffer\n");
	spellbuff[currspellnum][currlinenum].command = currlinebuff.command;
	spellbuff[currspellnum][currlinenum].argintone = currlinebuff.argintone;
	spellbuff[currspellnum][currlinenum].arginttwo = currlinebuff.arginttwo;
	spellbuff[currspellnum][currlinenum].argintthree = currlinebuff.argintthree;
	currlinenum++;
	return 0;
};

int BranchStat()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'BranchStat'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	BranchStatPartTwo();
	return 0;
}
int BranchStatPartTwo()
{
	char temp;
	wprintw(stdscr, "What kind of branch condition (type this letter):\n    Less than    (l)\n    Equal to     (e)\n    Greater than (g)\n");
	temp = bie();
	if(temp == 'l')
	{
		currlinebuff.command = 'b';
	}
	else if(temp == 'e')
	{
		currlinebuff.command = 'u';
	}
	else if(temp == 'g')
	{
		currlinebuff.command = 'B';
	}
	else
	{
		wprintw(stdscr, "Letter is CaSe SeNsItIvE! Try again.\n");
		return 0;
	}
	wprintw(stdscr, "Stat number?\n");
	currlinebuff.argintone = intimp();
	wprintw(stdscr, "Condition's number?\n");
	currlinebuff.arginttwo = intimp();
	wprintw(stdscr, "Line number?\n");
	currlinebuff.argintthree = intimp();
	wprintw(stdscr, "Commiting to Script file buffer\n");
	spellbuff[currspellnum][currlinenum].command = currlinebuff.command;
	spellbuff[currspellnum][currlinenum].argintone = currlinebuff.argintone;
	spellbuff[currspellnum][currlinenum].arginttwo = currlinebuff.arginttwo;
	spellbuff[currspellnum][currlinenum].argintthree = currlinebuff.argintthree;
	currlinenum++;
	return 0;
};
