// Enemy adder.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define TRUE 1
#define FALSE 0
#define VERSION '\x01'
#define VERSION2 '\x01'

char enemytablevernum = VERSION;
char enemytablevernum2 = VERSION2;
char sep = '\x00';
char end = '\xFF';

int chartypenum;
int eqnum;
int enemynum;
int characternum;
int groupnum;
int itemnum;

int workingctnum;
int workingeqnum;
int workingennum;
int workingchnum;
int workinggrnum;
int workingitnum;

unsigned char workingct [16];
char workingeq [8];
unsigned char workingen [16];
unsigned char workingch [16];
unsigned char workinggr [16];
unsigned char workingit [16];

unsigned char chartype [272] [16];
char equatable [40] [8];
unsigned char enemytable [256] [16];
unsigned char charactable [16] [16];
unsigned char grouptable [256] [16];
unsigned char itemtable [256] [16];

extern char filename [13];
FILE *savefile, *loadfile;

int frunx;
int fruny;
char trash;

int loaden (char openfile [13]);
int saveen (char openfile [13]);
int impen();
int dumpen();

int addchart();
int addeq();
int adden();
int addcha();
int addgr();
int addit();

int charted();
int ened();
int eqed();
int chared();
int gred();
int ited();

int clearchart();
int cleareq();
int clearen();
int clearch();
int cleargr();
int clearit();

int viewchart();
int vieweq();
int viewen();
int viewch();
int viewgr();
int viewit();

void plusone (char eqench);
void minusone (char eqench);
void checkone (char eqench);

int input [3];


#include "Common functions.cpp"

int main(int argc, char* argv[])
{
	char check;
	initscr();
	cbreak();
	nodelay(stdscr, FALSE);
	scrollok(stdscr, TRUE);
	wprintw(stdscr, "This is the enemy adder ver. %d.%d for the Brave Quest engine.\nCopyright 2012 Mad Science Inc.\nPlease do not redistrubute.\nLoads .enm files!\nPress any key to continue!\n\n",enemytablevernum,enemytablevernum2);
	hang(1);
	while(check != ERR)
	{
		check = nbi();
	}
	bi();
	stufffilename();
				wprintw(stdscr, "\nWoohoo!\n");
				wrefresh(stdscr);
				hang(1);
	if(loaden(filename) == 1)
	{
		wprintw(stdscr, "File %s not Found. Would you like to make a new file?\n", filename);
		if(bie() == 'y')
		{
			enemynum = 0;
//			for(frunx = 0; frunx < 256; frunx++)
//				for(fruny = 0; fruny < 16; fruny++)
//					enemytable[frunx][fruny] = sep;
			if(saveen(filename) == 1)
			{
				wprintw(stdscr, "Your disk sucks.\n");
				bi();
				return 1;
			}
		}
	}
	
	charted();
	return 0;
};

int charted()
{
	for(;;)
	{
		clear();
		refresh();
		wprintw(stdscr, "To add a character type press 1.\nTo view an character type press 4.\nTo save the enemy file press 7.\nTo save the enemy file under a different name press 8.\nTo edit enemies press 9\nTo delete a character type press 0.\n");
		input [0] = bie();
		if(input[0] == '1')
			addchart();
		if(input[0] == '4')
			viewchart();
		if(input[0] == '7')
			saveen(filename);
		if(input[0] == '8')
		{
			stufffilename();
			saveen(filename);
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
			clearen();
		wprintw(stdscr, "Press any key to continue.\n");
		bie();
	}
	if(input[0] == '9')
		ened();
	return 0;
}

int ened()
{
	for(;;)
	{
		clear();
		refresh();
		wprintw(stdscr, "To add an enemy press 1.\nTo view an enemy press 4.\nTo save the enemy file press 7.\nTo save the enemy file under a different name press 8.\nTo edit characters press 9\nTo delete an enemy press 0.\n");
		input [0] = bie();
		if(input[0] == '1')
			adden();
		if(input[0] == '4')
			viewen();
		if(input[0] == '7')
			saveen(filename);
		if(input[0] == '8')
		{
			stufffilename();
			saveen(filename);
		}
		if(input[0] == '9')
			break;
		if(input[0] == '.')
			plusone(0);
		if(input[0] == ',')
			minusone(0);
		if(input[0] == '/')
			checkone(0);
		if(input[0] == '0')
			clearen();
		wprintw(stdscr, "Press any key to continue.\n");
		bie();
	}
	if(input[0] == '9')
		chared();
	return 0;
}

int chared()
{
	for(;;)
	{
		clear();
		refresh();
		wprintw(stdscr, "To add a character press 1.\nTo view a character press 4.\nTo save the enemy file press 7.\nTo save the enemy file under a different name press 8.\nTo edit equations press 9\nTo delete a character press 0.\n");
		input [0] = bie();
		if(input[0] == '1')
			addcha();
		if(input[0] == '4')
			viewch();
		if(input[0] == '7')
			saveen(filename);
		if(input[0] == '8')
		{
			stufffilename();
			saveen(filename);
		}
		if(input[0] == '9')
			break;
		if(input[0] == '.')
			plusone(1);
		if(input[0] == ',')
			minusone(1);
		if(input[0] == '/')
			checkone(1);
		if(input[0] == '0')
			clearch();
		wprintw(stdscr, "Press any key to continue.\n");
		bie();
	}
	if(input[0] == '9')
		eqed();
	return 0;
}

int eqed ()
{
	for(;;)
	{
		clear();
		refresh();
		wprintw(stdscr, "To add an equation press 1.\nTo view an equation press 4.\nTo save the enemy file press 7.\nTo save the enemy file under a different name press 8.\nTo edit groups press 9\nTo delete an equation press 0.\n");
		input [0] = bie();
		if(input[0] == '1')
			addeq();
		if(input[0] == '4')
			vieweq();
		if(input[0] == '7')
			saveen(filename);
		if(input[0] == '8')
		{
			stufffilename();
			saveen(filename);
		}
		if(input[0] == '9')
			break;
		if(input[0] == '.')
			plusone(2);
		if(input[0] == ',')
			minusone(2);
		if(input[0] == '/')
			checkone(2);
		if(input[0] == '0')
			cleareq();
		wprintw(stdscr, "Press any key to continue.\n");
		bie();
	}
	if(input[0] == '9')
		gred();
	return 0;
};

int gred()
{
	for(;;)
	{
		clear();
		refresh();
		wprintw(stdscr, "To add an enemy press 1.\nTo view an enemy press 4.\nTo save the enemy file press 7.\nTo save the enemy file under a different name press 8.\nTo edit items press 9\nTo delete an enemy press 0.\n");
		input [0] = bie();
		if(input[0] == '1')
			addgr();
		if(input[0] == '4')
			viewgr();
		if(input[0] == '7')
			saveen(filename);
		if(input[0] == '8')
		{
			stufffilename();
			saveen(filename);
		}
		if(input[0] == '9')
			break;
		if(input[0] == '.')
			plusone(4);
		if(input[0] == ',')
			minusone(4);
		if(input[0] == '/')
			checkone(4);
		if(input[0] == '0')
			cleargr();
		wprintw(stdscr, "Press any key to continue.\n");
		bie();
	}
	if(input[0] == '9')
		ited();
	return 0;
}

int ited()
{
	for(;;)
	{
		clear();
		refresh();
		wprintw(stdscr, "To add an enemy press 1.\nTo view an enemy press 4.\nTo save the enemy file press 7.\nTo save the enemy file under a different name press 8.\nTo edit classes press 9\nTo delete an enemy press 0.\n");
		input [0] = bie();
		if(input[0] == '1')
			addit();
		if(input[0] == '4')
			viewit();
		if(input[0] == '7')
			saveen(filename);
		if(input[0] == '8')
		{
			stufffilename();
			saveen(filename);
		}
		if(input[0] == '9')
			break;
		if(input[0] == '.')
			plusone(5);
		if(input[0] == ',')
			minusone(5);
		if(input[0] == '/')
			checkone(5);
		if(input[0] == '0')
			clearit();
		wprintw(stdscr, "Press any key to continue.\n");
		bie();
	}
	if(input[0] == '9')
		charted();
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
				wprintw(stdscr, "\nWoohoo!\n");
				wrefresh(stdscr);
				hang(1);
		fread(&trash,1,1,loadfile);
		fread(&trash,1,1,loadfile);
		if(trash == 0)
		{
			fread(&characternum,4,1,loadfile);
			fread(&eqnum,4,1,loadfile);
			fread(&enemynum,4,1,loadfile);
			fread(&characternum,4,1,loadfile);
			fread(&groupnum,4,1,loadfile);
			fread(&itemnum,4,1,loadfile);
		}
		if(trash != 0)
		{
			fread(&characternum,4,1,loadfile);
			fread(&eqnum,4,1,loadfile);
			fread(&enemynum,4,1,loadfile);
			fread(&characternum,4,1,loadfile);
			fread(&groupnum,4,1,loadfile);
			fread(&itemnum,4,1,loadfile);
		}
		for(frunx = 0; frunx < chartypenum ; frunx++)
		{
			for(fruny = 0; fruny < 16; fruny++)
			{
				fread(&chartype[frunx][fruny],1,1,loadfile);
			};
		};
		for(frunx = 0; frunx < eqnum ; frunx++)
		{
			for(fruny = 0; fruny < 8; fruny++)
			{
				fread(&equatable[frunx][fruny],1,1,loadfile);
			};
		};
		for(frunx = 0; frunx < enemynum; frunx++)
		{
			for(fruny = 0; fruny < 16; fruny++)
			{
				fread(&enemytable[frunx][fruny],1,1,loadfile);
			};
		};
		for(frunx = 0; frunx < characternum; frunx++)
		{
			for(fruny = 0; fruny < 16; fruny++)
			{
				fread(&charactable[frunx][fruny],1,1,loadfile);
			};
		};
		for(frunx = 0; frunx < groupnum ; frunx++)
		{
			for(fruny = 0; fruny < 16; fruny++)
			{
				fread(&grouptable[frunx][fruny],1,1,loadfile);
			};
		};
		for(frunx = 0; frunx < itemnum ; frunx++)
		{
			for(fruny = 0; fruny < 16; fruny++)
			{
				fread(&itemtable[frunx][fruny],1,1,loadfile);
			};
		};
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
				wprintw(stdscr, "Woohoo!!!");
				wrefresh(stdscr);
				hang(1);
		fwrite(&enemytablevernum,1,1,savefile);
		fwrite(&enemytablevernum2,1,1,savefile);
		fwrite(&characternum,4,1,savefile);
		fwrite(&eqnum,4,1,savefile);
		fwrite(&enemynum,4,1,savefile);
		fwrite(&characternum,4,1,savefile);
		fwrite(&groupnum,4,1,savefile);
		fwrite(&itemnum,4,1,savefile);
		for(frunx = 0; frunx < chartypenum ; frunx++)
		{
			for(fruny = 0; fruny < 16; fruny++)
			{
				fwrite(&chartype[frunx][fruny],1,1,savefile);
			};
		};
		for(frunx = 0; frunx < eqnum ; frunx++)
		{
			for(fruny = 0; fruny < 8; fruny++)
			{
				fwrite(&equatable[frunx][fruny],1,1,savefile);
			};
		};
		for(frunx = 0; frunx < enemynum; frunx++)
		{
			for(fruny = 0; fruny < 16; fruny++)
			{
				fwrite(&enemytable[frunx][fruny],1,1,savefile);
			};
		};
		for(frunx = 0; frunx < characternum; frunx++)
		{
			for(fruny = 0; fruny < 16; fruny++)
			{
				fwrite(&charactable[frunx][fruny],1,1,savefile);
			};
		};
		for(frunx = 0; frunx < groupnum ; frunx++)
		{
			for(fruny = 0; fruny < 16; fruny++)
			{
				fwrite(&grouptable[frunx][fruny],1,1,savefile);
			};
		};
		for(frunx = 0; frunx < itemnum ; frunx++)
		{
			for(fruny = 0; fruny < 16; fruny++)
			{
				fwrite(&itemtable[frunx][fruny],1,1,savefile);
			};
		};
				wprintw(stdscr, "\nWoohoo!!!\n");
				wrefresh(stdscr);
				hang(1);
		fclose(savefile);
	}
	wprintw(stdscr, "sucessful.\n");
	return 0;
};

int addchart()
{
	wprintw(stdscr, "Go back? y/n\n");
	if (bie() == 'y')
		return 2;
	workingctnum = chartypenum;
	wprintw(stdscr, "Please type your class's name.\nPress escape to end input.\n");
	for (frunx = 0;(input[1] != 27) && (frunx < 8);frunx++)
	{
		input[1] = bie();
		if(input[1] == 27)
		{
			break;
		}
		workingct[frunx] = input[1];
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
	workingct[8] = sep;
	wprintw(stdscr, "Please type your enemy's health equation number.\n");
	workingct[9] = intimp();
	wprintw(stdscr, "Please type your enemy's attack equation number.\n");
	workingct[10] = intimp();
	wprintw(stdscr, "Please type your enemy's defence equation number.\n");
	workingct[11] = intimp();
	wprintw(stdscr, "Please type your enemy's wisdom equation number.\n");
	workingct[12] = intimp();
	wprintw(stdscr, "Please type your enemy's resistance equation number.\n");
	workingct[13] = intimp();
	wprintw(stdscr, "Please type your enemy's speed equation number.\n");
	workingct[14] = intimp();
	wprintw(stdscr, "Please type your enemy's luck equation number.\n");
	workingct[15] = intimp();
	wprintw(stdscr, "Comitting to enemy table now.\n");
	for(frunx = 0; frunx < 16; frunx++)
	{
		chartype [workingctnum][frunx] = workingct[frunx];
	}
	chartypenum = workingctnum + 1;
	input[1] = 0;
	for(frunx = 0; frunx < 16; frunx++)
	{
		workingct[frunx] = 0;
	}
	wprintw(stdscr, "Done.\n");
	return 0;
};

int adden()
{
	wprintw(stdscr, "Go back? y/n\n");
	if (bie() == 'y')
		return 2;
	workingennum = enemynum;
	wprintw(stdscr, "Please type your enemy's name.\nPress escape to end input.\n");
	for (frunx = 0;(input[1] != 27) && (frunx < 12);frunx++)
	{
		input[1] = bie();
		if(input[1] == 27)
		{
			break;
		}
		workingen[frunx] = input[1];
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
	workingen[12] = sep;
	wprintw(stdscr, "Please type your enemy's Character.\n");
	workingen[13] = bie();
	wprintw(stdscr, "Please type your enemy's stat equation number.\n");
	workingen[14] = intimp();
	wprintw(stdscr, "Please type your enemy's AI equation number.\n");
	workingen[15] = intimp();
	wprintw(stdscr, "Comitting to enemy table now.\n");
	for(frunx = 0; frunx < 16; frunx++)
	{
		enemytable [workingennum][frunx] = workingen[frunx];
	}
	enemynum = workingennum + 1;
	input[1] = 0;
	for(frunx = 0; frunx < 16; frunx++)
	{
		workingen[frunx] = 0;
	}
	wprintw(stdscr, "Done.\n");
	return 0;
};

int addcha()
{
	wprintw(stdscr, "Go back? y/n\n");
	if (bie() == 'y')
		return 2;
	workingchnum = characternum;
	wprintw(stdscr, "Please type your character's default name.\nPress escape to end input.\n");
	for (frunx = 0;(input[1] != 27) && (frunx < 12);frunx++)
	{
		input[1] = bie();
		if(input[1] == 27)
		{
			break;
		}
		workingch[frunx] = input[1];
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

int addeq()
{
	initscr();
	cbreak();
	nodelay(stdscr, FALSE);
	scrollok(stdscr, TRUE);
	wprintw(stdscr, "Go back? y/n\n");
	if (bie() == 'y')
		return 2;
	workingeqnum = eqnum;
	clear();
	refresh();
	wprintw(stdscr, "Type the numbers as required!\n_x^7+_x^6+_x^5+_x^4+_x^3+_x^2+_x^1+_\n");
	workingeq[0] = sintimp();
	workingeq[1] = sintimp();
	workingeq[2] = sintimp();
	workingeq[3] = sintimp();
	workingeq[4] = sintimp();
	workingeq[5] = sintimp();
	workingeq[6] = sintimp();
	workingeq[7] = sintimp();
	wprintw(stdscr, "Comitting to equation table now.\n");
	for(frunx = 0; frunx < 8; frunx++)
	{
		equatable [workingeqnum][frunx] = workingeq[frunx];
	}
	eqnum = workingeqnum + 1;
	input[1] = 0;
	for(frunx = 0; frunx < 8; frunx++)
	{
		workingeq[frunx] = 0;
	}
	wprintw(stdscr, "Done.\n");
	return 0;
};

int addgr()
{
	int qwert;
	wprintw(stdscr, "Go back? y/n\n");
	if (bie() == 'y')
		return 2;
	workinggrnum = groupnum;
	wprintw(stdscr, "Follow the instructions to input the group's info.\nPress escape to end input.\n");
	for (frunx = 0; frunx < 8;frunx++)
	{
		qwert = frunx * 2;
		wprintw(stdscr, "Please type your enemy's number.\n");
		workinggr[qwert] = intimp();
		wprintw(stdscr, "Please type the level offset.\n");
		workinggr[qwert + 1] = intimp();
	}
	wprintw(stdscr, "Comitting to group table now.\n");
	for(frunx = 0; frunx < 16; frunx++)
	{
		grouptable[workinggrnum][frunx] = workinggr[frunx];
	}
	groupnum = workinggrnum + 1;
	input[1] = 0;
	for(frunx = 0; frunx < 16; frunx++)
	{
		workinggr[frunx] = 0;
	}
	wprintw(stdscr, "Done.\n");
	return 0;
};

int addit()
{
	wprintw(stdscr, "Go back? y/n\n");
	if (bie() == 'y')
		return 2;
	workingitnum = itemnum;
	wprintw(stdscr, "Please type your item's name.\nPress escape to end input.\n");
	for (frunx = 0;(input[1] != 27) && (frunx < 11);frunx++)
	{
		input[1] = bie();
		if(input[1] == 27)
		{
			break;
		}
		workingit[frunx] = input[1];
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
	workingit[11] = sep;
	wprintw(stdscr, "Please type your item's Character.\n");
	workingit[12] = bie();
	wprintw(stdscr, "Please type your item's life.\n");
	workingit[13] = intimp();
	wprintw(stdscr, "Please type your item's affected stat.\n");
	workingit[14] = intimp();
	wprintw(stdscr, "Please type how much your item affects its stat.\n");
	workingit[15] = intimp();
	wprintw(stdscr, "Comitting to enemy table now.\n");
	for(frunx = 0; frunx < 16; frunx++)
	{
		itemtable [workingitnum][frunx] = workingit[frunx];
	}
	itemnum = workingitnum + 1;
	input[1] = 0;
	for(frunx = 0; frunx < 16; frunx++)
	{
		workingit[frunx] = 0;
	}
	wprintw(stdscr, "Done.\n");
	return 0;
};

int clearchart()
{
	wprintw(stdscr, "Please type the character type number.\n");
	workingctnum = intimp();
	for(frunx = 0; frunx < 16; frunx++)
		chartype[workingctnum][frunx] = 0;
	wprintw(stdscr, "\n");
	return 0;
};

int clearen()
{
	wprintw(stdscr, "Please type the enemy number.\n");
	workingennum = intimp();
	for(frunx = 0; frunx < 16; frunx++)
		enemytable[workingennum][frunx] = 0;
	wprintw(stdscr, "\n");
	return 0;
};

int clearch()
{
	wprintw(stdscr, "Please type the character number.\n");
	workingchnum = intimp();
	for(frunx = 0; frunx < 16; frunx++)
		charactable[workingchnum][frunx] = 0;
	wprintw(stdscr, "\n");
	return 0;
};

int cleareq()
{
	wprintw(stdscr, "Please type the equation number.\n");
	workingeqnum = intimp();
	for(frunx = 0; frunx < 8; frunx++)
		equatable[workingeqnum][frunx] = 0;
	wprintw(stdscr, "\n");
	return 0;
};

int cleargr()
{
	wprintw(stdscr, "Please type the enemy number.\n");
	workinggrnum = intimp();
	for(frunx = 0; frunx < 16; frunx++)
		grouptable[workinggrnum][frunx] = 0;
	wprintw(stdscr, "\n");
	return 0;
};

int clearit()
{
	wprintw(stdscr, "Please type the item number.\n");
	workingitnum = intimp();
	for(frunx = 0; frunx < 16; frunx++)
		itemtable[workingitnum][frunx] = 0;
	wprintw(stdscr, "\n");
	return 0;
};

int viewchart()
{
	wprintw(stdscr, "Please type the character type number.\n");
	input[1] = intimp();
	wprintw(stdscr, "Character type:%s, level offset\n#1. %d\n#2. %d\n#3. %d\n#4. %d\n#5. %d\n#6. %d\n#7. %d\n", charactable[input[1]][0], charactable[input[1]][9], charactable[input[1]][10], charactable[input[1]][11], charactable[input[1]][12], charactable[input[1]][13], charactable[input[1]][14], charactable[input[1]][15]);
	refresh();
	return 0;
};

int viewen()
{
	wprintw(stdscr, "Please type the enemy number.\n");
	input[1] = intimp();
	wprintw(stdscr, "Name: %s\nChar: %c\nStat: %d\nAI:   %d\n", enemytable[input[1]][0], enemytable[input[1]][13], enemytable[input[1]][14], enemytable[input[1]][15]);
	refresh();
	return 0;
};

int viewch()
{
	wprintw(stdscr, "Please type the character number.\n");
	input[1] = intimp();
	wprintw(stdscr, "Default Name: %s\nChar: %c\nStat group: %d\n", charactable[input[1]][0], charactable[input[1]][13], charactable[input[1]][14]);
	refresh();
	return 0;
};

int vieweq()
{
	wprintw(stdscr, "Please type the equation group number (0 - 4).\n");
	input[1] = intimp();
	input[1] = input[1] % 8;
	wprintw(stdscr, "%dx^7+%dx^6+%dx^5+%dx^4+%dx^3+%dx^2+%dx+%d\n", charactable[input[1]][0], charactable[input[1]][1], charactable[input[1]][2], charactable[input[1]][3], charactable[input[1]][4], charactable[input[1]][5], charactable[input[1]][6], charactable[input[1]][7]);
	wprintw(stdscr, "%dx^7+%dx^6+%dx^5+%dx^4+%dx^3+%dx^2+%dx+%d\n", charactable[input[1]+1][0], charactable[input[1]+1][1], charactable[input[1]+1][2], charactable[input[1]+1][3], charactable[input[1]+1][4], charactable[input[1]+1][5], charactable[input[1]+1][6], charactable[input[1]+1][7]);
	wprintw(stdscr, "%dx^7+%dx^6+%dx^5+%dx^4+%dx^3+%dx^2+%dx+%d\n", charactable[input[1]+2][0], charactable[input[1]+2][1], charactable[input[1]+2][2], charactable[input[1]+2][3], charactable[input[1]+2][4], charactable[input[1]+2][5], charactable[input[1]+2][6], charactable[input[1]+2][7]);
	wprintw(stdscr, "%dx^7+%dx^6+%dx^5+%dx^4+%dx^3+%dx^2+%dx+%d\n", charactable[input[1]+3][0], charactable[input[1]+3][1], charactable[input[1]+3][2], charactable[input[1]+3][3], charactable[input[1]+3][4], charactable[input[1]+3][5], charactable[input[1]+3][6], charactable[input[1]+3][7]);
	wprintw(stdscr, "%dx^7+%dx^6+%dx^5+%dx^4+%dx^3+%dx^2+%dx+%d\n", charactable[input[1]+4][0], charactable[input[1]+4][1], charactable[input[1]+4][2], charactable[input[1]+4][3], charactable[input[1]+4][4], charactable[input[1]+4][5], charactable[input[1]+4][6], charactable[input[1]+4][7]);
	wprintw(stdscr, "%dx^7+%dx^6+%dx^5+%dx^4+%dx^3+%dx^2+%dx+%d\n", charactable[input[1]+5][0], charactable[input[1]+5][1], charactable[input[1]+5][2], charactable[input[1]+5][3], charactable[input[1]+5][4], charactable[input[1]+5][5], charactable[input[1]+5][6], charactable[input[1]+5][7]);
	wprintw(stdscr, "%dx^7+%dx^6+%dx^5+%dx^4+%dx^3+%dx^2+%dx+%d\n", charactable[input[1]+6][0], charactable[input[1]+6][1], charactable[input[1]+6][2], charactable[input[1]+6][3], charactable[input[1]+6][4], charactable[input[1]+6][5], charactable[input[1]+6][6], charactable[input[1]+6][7]);
	wprintw(stdscr, "%dx^7+%dx^6+%dx^5+%dx^4+%dx^3+%dx^2+%dx+%d\n", charactable[input[1]+7][0], charactable[input[1]+7][1], charactable[input[1]+7][2], charactable[input[1]+7][3], charactable[input[1]+7][4], charactable[input[1]+7][5], charactable[input[1]+7][6], charactable[input[1]+7][7]);
	refresh();
	return 0;
};

int viewgr()
{
	wprintw(stdscr, "Please type the enemy group number.\n");
	input[1] = intimp();
	wprintw(stdscr, "Enemy #, level offset\n#0. %d, %d\n#1. %d, %d\n#2. %d, %d\n#3. %d, %d\n#4. %d, %d\n#5. %d, %d\n#6. %d, %d\n#7. %d, %d\n", grouptable[input[1]][0], grouptable[input[1]][1], grouptable[input[1]][2], grouptable[input[1]][3], grouptable[input[1]][4], grouptable[input[1]][5], grouptable[input[1]][6], grouptable[input[1]][7], grouptable[input[1]][8], grouptable[input[1]][9], grouptable[input[1]][10], grouptable[input[1]][11], grouptable[input[1]][12], grouptable[input[1]][13], grouptable[input[1]][14], grouptable[input[1]][15]);
	refresh();
	return 0;
};

int viewit()
{
	wprintw(stdscr, "Please type the item number.\n");
	input[1] = intimp();
	wprintw(stdscr, "Name: %s\nChar: %c\nTime: %d\nStat: %d\nMod:  %d\n", itemtable[input[1]][0], itemtable[input[1]][12], itemtable[input[1]][13], itemtable[input[1]][14], itemtable[input[1]][15]);
	refresh();
	return 0;
};

void plusone (char eqench)
{
	if(eqench == 0)
		workingennum = workingennum + 1;
	if(eqench == 1)
		workingchnum = workingchnum + 1;
	if(eqench == 2)
		workingeqnum = workingeqnum + 1;
	if(eqench == 3)
		workingctnum = workingctnum + 1;
	if(eqench == 4)
		workinggrnum = workinggrnum + 1;
	if(eqench == 5)
		workingitnum = workingitnum + 1;
};

void minusone (char eqench)
{
	if(eqench == 0)
		workingennum = workingennum - 1;
	if(eqench == 1)
		workingchnum = workingchnum - 1;
	if(eqench == 2)
		workingeqnum = workingeqnum - 1;
	if(eqench == 3)
		workingctnum = workingctnum - 1;
	if(eqench == 4)
		workinggrnum = workinggrnum - 1;
	if(eqench == 5)
		workingitnum = workingitnum - 1;
};

void checkone (char eqench)
{
	if(eqench == 0)
		wprintw(stdscr, "%d", workingennum);
	if(eqench == 1)
		wprintw(stdscr, "%d", workingchnum);
	if(eqench == 2)
		wprintw(stdscr, "%d", workingeqnum);
	if(eqench == 3)
		wprintw(stdscr, "%d", workingctnum);
	if(eqench == 4)
		wprintw(stdscr, "%d", workinggrnum);
	if(eqench == 5)
		wprintw(stdscr, "%d", workingitnum);
};

