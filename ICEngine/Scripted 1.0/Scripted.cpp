// Scripted.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <ncurses.h>

#define TRUE 1
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
int linenum;
char trash;
int currlinenum;

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

struct scriptstuff filebuff [1024];
struct scriptstuff currlinebuff;

int loadscript (char openfile [13]);
int savescript (char openfile [13]);

void menu ();
void cleanfilebuff ();
void cleanlinebuff ();

int blank();
int changeline();
int showline();
int give();
int take();
int say();
int flag();
int move();
int battle();
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

#include "Common functions.cpp"

int main(int argc, char* argv[])
{
	initscr();
	scrollok(stdscr, TRUE);
	wprintw(stdscr, "Welcome to Scripted ver. %d.%d for the Brave Quest engine.\nCopyright 2012 Mad Science Inc.\nPlease do not redistrubute.\n",scriptedvernum,scriptedvernum2);
	stufffilename();
	if(loadscript(filename) == 1)
	{
		wprintw(stdscr, "File not Found. Would you like to make a new file?\n");
		if(bie() == 'y')
		{
			cleanfilebuff();
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
	currlinenum = linenum;
	menu();
	wprintw(stdscr, "Press escape to go to the save menu\n");
	for(;;)
	{
		wprintw(stdscr, "q= give, w= take, e= say, r= flag, t= move, y= battle, u= check flag, i= check item, o= party add, p= party remove, [ = check character\n");
		wprintw(stdscr, "a= warp, s= check experience, d= give experience, f= make experience, g= exec script, h= screen effect, j= user input, k= goline, l= make health\n");
		wprintw(stdscr, "m= blank, ,= show line, .= change line.\n");
		input[0] = bie();
		if(input[0] == 27)
			menu();
		if(input[0] == 'q')
			give();
		if(input[0] == 'w')
			take();
		if(input[0] == 'e')
			say();
		if(input[0] == 'r')
			flag();
		if(input[0] == 't')
			move();
		if(input[0] == 'y')
			battle();
		if(input[0] == 'u')
			checkflag();
		if(input[0] == 'i')
			checkitem();
		if(input[0] == 'o')
			partyadd();
		if(input[0] == 'p')
			partyrm();
		if(input[0] == '[')
			checkparty();
		if(input[0] == 'a')
			warp();
		if(input[0] == 's')
			checkexp();
		if(input[0] == 'd')
			giveexp();
		if(input[0] == 'f')
			makeexp();
		if(input[0] == 'g')
			execscript();
		if(input[0] == 'h')
			screeneffect();
		if(input[0] == 'j')
			userinput();
		if(input[0] == 'k')
			goline();
		if(input[0] == 'l')
			makehealth();
		if(input[0] == 'm')
			blank();
		if(input[0] == ',')
			showline();
		if(input[0] == '.')
			changeline();
		if(currlinenum > linenum)
			linenum = currlinenum;
	}
	return 0;
};

void menu ()
{
	wprintw(stdscr, "To return to editing, press 1.\nTo save, press 2.\nTo save under a different name, press 3.\nTo reload the file, press 3.\nTo exit, press 0.\n");
	input [1] = bie();
	if(input[1] == '1')
		return;
	if(input[1] == '2')
		savescript(filename);
	if(input[1] == '3')
	{
		stufffilename();
		savescript(filename);
	}
	if(input[1] == '4')
		loadscript(filename);
	if(input[1] == '0')
	{
		exit(0);
	}
};

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
	fread(&linenum,4,1,loadfile);
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
	wprintw(stdscr, "sucessful.\n");
	return 0;
}

int savescript (char openfile [13])
{
	for(;filebuff[linenum].command != '\0';linenum++){}
	
	wprintw(stdscr, "Saving ");
	savefile = fopen(openfile,"wb");
	if (savefile == FALSE)
	{
		wprintw(stdscr, "failed.\n");
		return 1;
	}
	fwrite(&scriptedvernum,1,1,savefile);
	fwrite(&scriptedvernum2,1,1,savefile);
	fwrite(&linenum,4,1,savefile);
	for(frunx = 0; frunx < linenum; frunx++)
	{
		fwrite(&filebuff[frunx].command,1,1,savefile);
		fwrite(&filebuff[frunx].argintone,4,1,savefile);
		fwrite(&filebuff[frunx].arginttwo,4,1,savefile);
		fwrite(&filebuff[frunx].argintthree,4,1,savefile);
		fwrite(&filebuff[frunx].argintfour,4,1,savefile);
		fwrite(&filebuff[frunx].argintfive,4,1,savefile);
		fwrite(&filebuff[frunx].argstringone,13,1,savefile);
		fwrite(&filebuff[frunx].argstringtwo,80,1,savefile);
	};
	fclose(savefile);
	wprintw(stdscr, "sucessful.\n");
	return 0;
};

int give()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'Give'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	currlinebuff.command = 'g';
	wprintw(stdscr, "Type item ID.\n");
	currlinebuff.argintone = intimp();
	wprintw(stdscr, "Type amount of this item to give.\n");
	currlinebuff.arginttwo = intimp();
	wprintw(stdscr, "Commiting to Script file buffer\n");
	filebuff[currlinenum].command = currlinebuff.command;
	filebuff[currlinenum].argintone = currlinebuff.argintone;
	filebuff[currlinenum].arginttwo = currlinebuff.arginttwo;
	currlinenum++;
	return 0;
};

int take()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'Take'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	currlinebuff.command = 't';
	wprintw(stdscr, "Type item ID.\n");
	currlinebuff.argintone = intimp();
	wprintw(stdscr, "Type amount of this item to take.\n");
	currlinebuff.arginttwo = intimp();
	wprintw(stdscr, "Commiting to Script file buffer\n");
	filebuff[currlinenum].command = currlinebuff.command;
	filebuff[currlinenum].argintone = currlinebuff.argintone;
	filebuff[currlinenum].arginttwo = currlinebuff.arginttwo;
	currlinenum++;
	return 0;
};
int say()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'Say'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	currlinebuff.command = 's';
	wprintw(stdscr, "Type statement.\n");
	argtwo();
	wprintw(stdscr, "Commiting to Script file buffer\n");
	filebuff[currlinenum].command = currlinebuff.command;
	strcpy(filebuff[currlinenum].argstringtwo, currlinebuff.argstringtwo);
	currlinenum++;
	return 0;
};
int flag()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'Flag'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	currlinebuff.command = 'f';
	wprintw(stdscr, "Type Flag ID1.\n");
	currlinebuff.argintone = intimp();
	wprintw(stdscr, "Type Flag ID2.\n");
	currlinebuff.arginttwo = intimp();
	wprintw(stdscr, "Type Flag's new state.\n");
	currlinebuff.argintthree = intimp();
	wprintw(stdscr, "Commiting to Script file buffer\n");
	filebuff[currlinenum].command = currlinebuff.command;
	filebuff[currlinenum].argintone = currlinebuff.argintone;
	filebuff[currlinenum].arginttwo = currlinebuff.arginttwo;
	filebuff[currlinenum].argintthree = currlinebuff.argintthree;
	currlinenum++;
	return 0;
};
int move()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'Move'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	currlinebuff.command = 'm';
	wprintw(stdscr, "Move who?\n");
	currlinebuff.argintone = intimp();
	wprintw(stdscr, "Which direction.\n");
	currlinebuff.arginttwo = bie();
	wprintw(stdscr, "Commiting to Script file buffer\n");
	filebuff[currlinenum].command = currlinebuff.command;
	filebuff[currlinenum].argintone = currlinebuff.argintone;
	filebuff[currlinenum].arginttwo = currlinebuff.arginttwo;
	currlinenum++;
	return 0;
};
int battle()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'Battle'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	currlinebuff.command = 'b';
	wprintw(stdscr, "Type enemy ID.\n");
	currlinebuff.argintone = intimp();
	wprintw(stdscr, "Type base level.\n");
	currlinebuff.arginttwo = intimp();
	
	wprintw(stdscr, "Commiting to Script file buffer\n");
	filebuff[currlinenum].command = currlinebuff.command;
	filebuff[currlinenum].argintone = currlinebuff.argintone;
	filebuff[currlinenum].arginttwo = currlinebuff.arginttwo;
	currlinenum++;
	return 0;
};
int checkflag()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'Check Flag'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	currlinebuff.command = 'F';
	wprintw(stdscr, "Type Flag ID1.\n");
	currlinebuff.argintone = intimp();
	wprintw(stdscr, "Type Flag ID2.\n");
	currlinebuff.arginttwo = intimp();
	wprintw(stdscr, "Type state it should be.\n");
	currlinebuff.argintthree = intimp();
	wprintw(stdscr, "Type line to go for true case.\n");
	currlinebuff.argintfour = intimp();
	wprintw(stdscr, "Type line to go for false case.\n");
	currlinebuff.argintfive = intimp();
	wprintw(stdscr, "Commiting to Script file buffer\n");
	filebuff[currlinenum].command = currlinebuff.command;
	filebuff[currlinenum].argintone = currlinebuff.argintone;
	filebuff[currlinenum].arginttwo = currlinebuff.arginttwo;
	filebuff[currlinenum].argintthree = currlinebuff.argintthree;
	filebuff[currlinenum].argintfour = currlinebuff.argintfour;
	filebuff[currlinenum].argintfive = currlinebuff.argintfive;
	currlinenum++;
	return 0;
};
int checkitem()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'Check Item'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	currlinebuff.command = 'I';
	wprintw(stdscr, "Type Item number.\n");
	currlinebuff.argintone = intimp();
	wprintw(stdscr, "Type lower bound.\n");
	currlinebuff.arginttwo = intimp();
	wprintw(stdscr, "Type upper bound.\n");
	currlinebuff.argintthree = intimp();
	wprintw(stdscr, "Type line to go for true case.\n");
	currlinebuff.argintfour = intimp();
	wprintw(stdscr, "Type line to go for false case.\n");
	currlinebuff.argintfive = intimp();
	wprintw(stdscr, "Commiting to Script file buffer\n");
	filebuff[currlinenum].command = currlinebuff.command;
	filebuff[currlinenum].argintone = currlinebuff.argintone;
	filebuff[currlinenum].arginttwo = currlinebuff.arginttwo;
	filebuff[currlinenum].argintthree = currlinebuff.argintthree;
	filebuff[currlinenum].argintfour = currlinebuff.argintfour;
	filebuff[currlinenum].argintfive = currlinebuff.argintfive;
	currlinenum++;
	return 0;
};
int warp()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'Warp'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	currlinebuff.command = 'w';
	wprintw(stdscr, "Type filename of next map (INCLUDE EXTENSION).\n");
	argone();
	wprintw(stdscr, "Type 'x' coordinate.\n");
	currlinebuff.argintone = intimp();
	wprintw(stdscr, "Type 'y' coordinate.\n");
	currlinebuff.arginttwo = intimp();
	wprintw(stdscr, "Commiting to Script file buffer\n");
	filebuff[currlinenum].command = currlinebuff.command;
	strcpy(filebuff[currlinenum].argstringone, currlinebuff.argstringone);
	filebuff[currlinenum].argintone = currlinebuff.argintone;
	filebuff[currlinenum].arginttwo = currlinebuff.arginttwo;
	currlinenum++;
	return 0;
};
int checkexp()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'Check Experience'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	currlinebuff.command = 'E';
	wprintw(stdscr, "Type Character ID.\n");
	currlinebuff.argintone = intimp();
	wprintw(stdscr, "Type lower bound.\n");
	currlinebuff.arginttwo = intimp();
	wprintw(stdscr, "Type upper bound.\n");
	currlinebuff.argintthree = intimp();
	wprintw(stdscr, "Type line to go for true case.\n");
	currlinebuff.argintfour = intimp();
	wprintw(stdscr, "Type line to go for false case.\n");
	currlinebuff.argintfive = intimp();
	wprintw(stdscr, "Commiting to Script file buffer\n");
	filebuff[currlinenum].command = currlinebuff.command;
	filebuff[currlinenum].argintone = currlinebuff.argintone;
	filebuff[currlinenum].arginttwo = currlinebuff.arginttwo;
	filebuff[currlinenum].argintthree = currlinebuff.argintthree;
	filebuff[currlinenum].argintfour = currlinebuff.argintfour;
	filebuff[currlinenum].argintfive = currlinebuff.argintfive;
	currlinenum++;
	return 0;
};
int giveexp()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'Give Experience'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	currlinebuff.command = 'e';
	wprintw(stdscr, "Type Character ID.\n");
	currlinebuff.argintone = intimp();
	wprintw(stdscr, "Type amount.\n");
	currlinebuff.arginttwo = intimp();
	wprintw(stdscr, "Commiting to Script file buffer\n");
	filebuff[currlinenum].command = currlinebuff.command;
	filebuff[currlinenum].argintone = currlinebuff.argintone;
	filebuff[currlinenum].arginttwo = currlinebuff.arginttwo;
	currlinenum++;
	return 0;
};
int makeexp()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'Make Experience'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	currlinebuff.command = 'M';
	wprintw(stdscr, "Type Character ID.\n");
	currlinebuff.argintone = intimp();
	wprintw(stdscr, "Type amount(NOTE: An amount of -1 means FULL HEALTH!!!).\n");
	currlinebuff.arginttwo = intimp();
	wprintw(stdscr, "Commiting to Script file buffer\n");
	filebuff[currlinenum].command = currlinebuff.command;
	filebuff[currlinenum].argintone = currlinebuff.argintone;
	filebuff[currlinenum].arginttwo = currlinebuff.arginttwo;
	currlinenum++;
	return 0;
};
int makehealth()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'Make Health'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	currlinebuff.command = 'H';
	wprintw(stdscr, "Type Character ID.\n");
	currlinebuff.argintone = intimp();
	wprintw(stdscr, "Type amount.\n");
	currlinebuff.arginttwo = intimp();
	wprintw(stdscr, "Commiting to Script file buffer\n");
	filebuff[currlinenum].command = currlinebuff.command;
	filebuff[currlinenum].argintone = currlinebuff.argintone;
	filebuff[currlinenum].arginttwo = currlinebuff.arginttwo;
	currlinenum++;
	return 0;
};
int execscript()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'Execute Script'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	currlinebuff.command = 'x';
	wprintw(stdscr, "Type filename.\n");
	argone();
	wprintw(stdscr, "Commiting to Script file buffer\n");
	filebuff[currlinenum].command = currlinebuff.command;
	strcpy(filebuff[currlinenum].argstringone, currlinebuff.argstringone);
	currlinenum++;
	return 0;
};
int screeneffect()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'Screen Effect'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	currlinebuff.command = 'C';
	wprintw(stdscr, "Type Screen Effect number.\n");
	currlinebuff.argintone = intimp();
	wprintw(stdscr, "Commiting to Script file buffer\n");
	filebuff[currlinenum].command = currlinebuff.command;
	filebuff[currlinenum].argintone = currlinebuff.argintone;
	currlinenum++;
	return 0;
};
int userinput()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'User Input'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	currlinebuff.command = 'u';
	wprintw(stdscr, "Type Flag ID1 to store input in.\n");
	currlinebuff.argintone = intimp();
	wprintw(stdscr, "Type Flag ID2 to store input in.\n");
	currlinebuff.arginttwo = intimp();
	wprintw(stdscr, "Commiting to Script file buffer\n");
	filebuff[currlinenum].command = currlinebuff.command;
	filebuff[currlinenum].argintone = currlinebuff.argintone;
	filebuff[currlinenum].arginttwo = currlinebuff.arginttwo;
	currlinenum++;
	return 0;
};
int goline()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'User Input'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	currlinebuff.command = 'G';
	wprintw(stdscr, "Type line number.\n");
	currlinebuff.argintone = intimp();
	wprintw(stdscr, "Commiting to Script file buffer\n");
	filebuff[currlinenum].command = currlinebuff.command;
	filebuff[currlinenum].argintone = currlinebuff.argintone;
	currlinenum++;
	return 0;
};
int partyadd()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'Add Character'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	currlinebuff.command = 'a';
	wprintw(stdscr, "Type character number to add.\n");
	currlinebuff.argintone = intimp();
	wprintw(stdscr, "Commiting to Script file buffer\n");
	filebuff[currlinenum].command = currlinebuff.command;
	filebuff[currlinenum].argintone = currlinebuff.argintone;
	currlinenum++;
	return 0;
};
int partyrm()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'Remove Character'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	currlinebuff.command = 'd';
	wprintw(stdscr, "Type character number to remove.\n");
	currlinebuff.argintone = intimp();
	wprintw(stdscr, "Commiting to Script file buffer\n");
	filebuff[currlinenum].command = currlinebuff.command;
	filebuff[currlinenum].argintone = currlinebuff.argintone;
	currlinenum++;
	return 0;
};
int checkparty()
{
	cleanlinebuff();
	wprintw(stdscr, "Insert 'Check Party'?\n Press 'n' to go back.\n");
	if(bie() == 'n')
		return 2;
	currlinebuff.command = 'c';
	wprintw(stdscr, "Type check type.\n");
	currlinebuff.argintone = intimp();
	wprintw(stdscr, "Type Character number.\n");
	currlinebuff.arginttwo = intimp();
	wprintw(stdscr, "Type check state.\n");
	currlinebuff.argintthree = intimp();
	wprintw(stdscr, "Type line to go for true case.\n");
	currlinebuff.argintfour = intimp();
	wprintw(stdscr, "Type line to go for false case.\n");
	currlinebuff.argintfive = intimp();
	wprintw(stdscr, "Commiting to Script file buffer\n");
	filebuff[currlinenum].command = currlinebuff.command;
	filebuff[currlinenum].argintone = currlinebuff.argintone;
	filebuff[currlinenum].arginttwo = currlinebuff.arginttwo;
	filebuff[currlinenum].argintthree = currlinebuff.argintthree;
	filebuff[currlinenum].argintfour = currlinebuff.argintfour;
	currlinenum++;
	return 0;
};

void cleanfilebuff()
{
	linenum = 0;
	trash = 0;
	currlinenum = 0;
	for(frunx = 0; frunx < 1024; frunx++)
	{
		filebuff [frunx].command = 0;
		filebuff [frunx].argintone = 0;
		filebuff [frunx].arginttwo = 0;
		filebuff [frunx].argintthree = 0;
		filebuff [frunx].argintfour = 0;
		filebuff [frunx].argintfive = 0;
		for(fruny = 0; fruny < 13; fruny++)
		{
			filebuff [frunx].argstringone [fruny] = 0;
		};
		for(fruny = 0; fruny < 80; fruny++)
		{
			filebuff [frunx].argstringtwo [fruny] = 0;
		};
	};
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

int blank()
{
	filebuff[currlinenum].command = 0;
	filebuff[currlinenum].argintone = 0;
	filebuff[currlinenum].arginttwo = 0;
	filebuff[currlinenum].argintthree = 0;
	filebuff[currlinenum].argintfour = 0;
	filebuff[currlinenum].argintfive = 0;
	for(fruny = 0; fruny < 13; fruny++)
	{
		filebuff[currlinenum].argstringone [fruny] = 0;
	};
	for(fruny = 0; fruny < 80; fruny++)
	{
		filebuff[currlinenum].argstringtwo [fruny] = 0;
	};
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
	wprintw(stdscr, "Command: %c\nInt 1: %d\nInt 2: %d\nInt 3: %d\nInt 4: %d\nInt 5: %d\nString 1: %s\nString 2: %s\n",filebuff[tempcurrline].command, filebuff[tempcurrline].argintone, filebuff[tempcurrline].arginttwo, filebuff[tempcurrline].argintthree, filebuff[tempcurrline].argintfour, filebuff[tempcurrline].argintfive, filebuff[tempcurrline].argstringone, filebuff[tempcurrline].argstringtwo);
	refresh();
	return 0;
}
