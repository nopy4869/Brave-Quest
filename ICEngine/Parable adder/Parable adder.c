// Parable adder.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define VERSION '\x01'
#define VERSION2 '\x01'

#include <ncurses.h>

char parabletablevernum = VERSION;
char parabletablevernum2 = VERSION2;
char sep = '\x00';
char end = '\xFF';

int parablenum;
int workingparnum;
char workingpar [1024];
char parabletable [1024] [1024];
//char parabletablevernum;
//char parabletablevernum2;


extern char filename [13];
FILE *savefile, *loadfile, *dumpfile, *impfile;

int frunx;
int fruny;
char trash;

int loadpar (char openfile [13]);
int savepar (char openfile [13]);
int addpar();
int edpar();
int movepar();
int clearpar();
int viewpar();
void plusone ();
void minusone ();
void checkone ();
int dumppar ();
int imppar ();

char input [5];

#include "Common functions.cpp"

int main(int argc, char* argv[])
{
	initscr();
	scrollok(stdscr, TRUE);
	wprintw(stdscr, "This is the parable adder ver. %d.%d for the Brave Quest engine.\nCopyright 2012 Mad Science Inc.\nPlease do not redistrubute.\nLoads .par files!\n",parabletablevernum,parabletablevernum2);
	stufffilename();
	if(loadpar(filename) == 1)
	{
		wprintw(stdscr, "File not Found. Would you like to make a new file?\n");
		if(bie() == 'y')
		{
			parablenum = 0;
			for(frunx = 0; frunx < 1024; frunx++)
				for(fruny = 0; fruny < 1024; fruny++)
					parabletable[frunx][fruny] = sep;
			if(savepar(filename) == 1)
			{
				wprintw(stdscr, "Your disk sucks.\n");
				bi();
				return 1;
			}
		}
	}
	
	for(;;)
	{
		wprintw(stdscr, "To add a parable press 1.\nTo edit a parable press 2.\nTo move a parable press 3.\nTo view a parable press 4.\nTo save the parable file press 7.\nTo save the parable file under a different name press 8.\nTo delete a parable press 0.\n");
		input [0] = bie();
		if(input[0] == '1')
			addpar();
		if(input[0] == '2')
			edpar();
		if(input[0] == '3')
			movepar();
		if(input[0] == '4')
			viewpar();
		if(input[0] == '7')
			savepar(filename);
		if(input[0] == '8')
		{
			stufffilename();
			savepar(filename);
		}
		if(input[0] == '.')
			plusone();
		if(input[0] == ',')
			minusone();
		if(input[0] == '/')
			checkone();
		if(input[0] == 'i')
			imppar();
		if(input[0] == 'd')
			dumppar();
		if(input[0] == '0')
			clearpar();
	}
	return 0;
};

int loadpar (char openfile [13])
{
	wprintw(stdscr, "Loading ");
	loadfile = fopen(openfile,"r");
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
			fread(&parablenum,1,1,loadfile);
		if(trash != 0)
			fread(&parablenum,4,1,loadfile);
		for(frunx = 0; frunx < parablenum; frunx++)
		{
			for(fruny = 0; fruny < 1024; fruny++)
			{
				fread(&parabletable[frunx][fruny],1,1,loadfile);
			};
		};
	}
	fclose(loadfile);
	wprintw(stdscr, "sucessful.\n");
	return 0;
}

int savepar (char openfile [13])
{
	wprintw(stdscr, "Saving ");
	savefile = fopen(openfile,"wb");
	if (savefile == FALSE)
	{
		wprintw(stdscr, "failed.\n");
		return 1;
	}
	fwrite(&parabletablevernum,1,1,savefile);
	fwrite(&parabletablevernum2,1,1,savefile);
	fwrite(&parablenum,4,1,savefile);
	for(frunx = 0; frunx < parablenum; frunx++)
	{
		for(fruny = 0; fruny < 1024; fruny++)
		{
			fwrite(&parabletable[frunx][fruny],1,1,savefile);
		};
	};
	fclose(savefile);
	wprintw(stdscr, "sucessful.\n");
	return 0;
};

int addpar()
{
	wprintw(stdscr, "Go back? y/n\n");
	if (bie() == 'y')
		return 2;
	workingparnum = parablenum;
	wprintw(stdscr, "Please type your parable.\nPress escape to end input.\n");
	for (frunx = 0;(input[1] != 27) && (frunx < 1024);frunx++)
	{
		input[1] = bie();
		if(input[1] == 27)
		{
			break;
		}
		workingpar[frunx] = input[1];
		if(input[1] == 13)
		{
			wprintw(stdscr, "\n");
			workingpar[frunx] = '\n';
		}
		if(input[1] == 8)
		{
			frunx--;
			frunx--;
		}
	}
	if(input[1] == 27)
		workingpar[frunx] = sep;
	workingpar[1023] = sep;
	wprintw(stdscr, "Comitting to parable table now.\n");
	for(frunx = 0; frunx < 1023; frunx++)
	{
		parabletable [workingparnum][frunx] = workingpar[frunx];
	}
	parablenum = workingparnum + 1;
	input[1] = 0;
	for(frunx = 0; frunx < 1023; frunx++)
	{
		workingpar[frunx] = 0;
	}
	wprintw(stdscr, "Done.\n");
	return 0;
};

int edpar()
{
	return 9;
};

int movepar()
{
	return 9;
};

int clearpar()
{
	wprintw(stdscr, "Please type the parable number.\n");
	workingparnum = intimp();
	for(frunx = 0; frunx < 1024; frunx++)
		parabletable[workingparnum][frunx] = 0;
	wprintw(stdscr, "\n");
	return 0;
};

int viewpar()
{
	wprintw(stdscr, "Please type the parable number.\n");
	workingparnum = intimp();
	for(frunx = 0; frunx < 1024; frunx++)
		wprintw(stdscr, "%c",parabletable[workingparnum][frunx]);
	wprintw(stdscr, "\n");
	return 0;
};

void plusone ()
{
	parablenum = parablenum + 1;
};

void minusone ()
{
	parablenum = parablenum - 1;
};

void checkone ()
{
	wprintw(stdscr, "%d", parablenum);
};

int dumppar ()
{
	wprintw(stdscr, "Please type the parable number.\n");
	workingparnum = intimp();
	stufffilename();
	wprintw(stdscr, "Saving ");
	dumpfile = fopen(filename,"wb");
	if (dumpfile == FALSE)
	{
		wprintw(stdscr, "failed.\n");
		return 1;
	}
	for(frunx = 0; frunx < 1024; frunx++)
		fwrite(&parabletable[workingparnum][frunx],1,1,dumpfile);
	fclose(dumpfile);
	wprintw(stdscr, "sucessful\n");
	return 0;
};

int imppar ()
{
	wprintw(stdscr, "Please type the parable number.\n");
	workingparnum = intimp();
	stufffilename();
	wprintw(stdscr, "Loading ");
	impfile = fopen(filename,"rb");
	if (impfile == FALSE)
	{
		wprintw(stdscr, "failed.\n");
		return 1;
	}
	for(frunx = 0; frunx < 1024; frunx++)
		fread(&parabletable[workingparnum][frunx],1,1,dumpfile);
	fclose(impfile);
	wprintw(stdscr, "sucessful\n");
	return 0;
};
