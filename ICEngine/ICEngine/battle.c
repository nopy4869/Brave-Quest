WINDOW *battlewin[7];

int chartypenum;
int eqnum;
int enemynum;
int characternum;
int groupnum;
int itemnum;
char batdone;

int en[8];
char charactable [16][16];
extern struct gameinfo currgame;
extern struct baten battleen [8];

int oldlines, oldcols;

statis parseeq(char equation_number, int level);
int detenstats(int group_number, int base_level);
int readen (char openfile [13]);

int batdisp()
{
	delwin(special[0]);
	delwin(special[1]);
	delwin(special[2]);
	delwin(special[3]);
	delwin(special[4]);
	leaveok(stdscr, TRUE);
	battlewin[0] = derwin(stdscr, 2, COLS/2, 0, 0);
	battlewin[1] = derwin(stdscr, 2, COLS/2, 0, COLS/2);
	battlewin[2] = derwin(stdscr, LINES - 7, 0, 3, 0);
	battlewin[3] = derwin(stdscr, 4, COLS/2, LINES - 4, 0);
	battlewin[4] = derwin(stdscr, 4, COLS/2, LINES - 4, COLS/2);
	battlewin[5] = derwin(stdscr, 1, 0, 2, 0);
	battlewin[6] = derwin(stdscr, 1, 0, LINES - 5, 0);
	scrollok(stdscr, FALSE);
	scrollok(battlewin[0], FALSE);
	scrollok(battlewin[1], FALSE);
	scrollok(battlewin[2], FALSE);
	scrollok(battlewin[3], FALSE);
	scrollok(battlewin[4], FALSE);
	scrollok(battlewin[5], FALSE);
	scrollok(battlewin[6], FALSE);
	oldlines = LINES;
	oldcols = COLS;
	int x;
	for(x = 0; x !=-1; x++)
	{
		if((oldlines != LINES) || (oldcols != COLS))
		{
			clear();
			oldlines = LINES;
			oldcols = COLS;
			delwin(battlewin[0]);
			delwin(battlewin[1]);
			delwin(battlewin[2]);
			delwin(battlewin[3]);
			delwin(battlewin[4]);
			delwin(battlewin[5]);
			delwin(battlewin[6]);
			
			battlewin[0] = derwin(stdscr, 2, COLS/2, 0, 0);
			battlewin[1] = derwin(stdscr, 2, COLS/2, 0, COLS/2);
			battlewin[2] = derwin(stdscr, LINES - 7, 0, 3, 0);
			battlewin[3] = derwin(stdscr, 4, COLS/2, LINES - 4, 0);
			battlewin[4] = derwin(stdscr, 4, COLS/2, LINES - 4, COLS/2);
			battlewin[5] = derwin(stdscr, 1, 0, 2, 0);
			battlewin[6] = derwin(stdscr, 1, 0, LINES - 5, 0);
			scrollok(stdscr, FALSE);
			scrollok(battlewin[0], FALSE);
			scrollok(battlewin[1], FALSE);
			scrollok(battlewin[2], FALSE);
			scrollok(battlewin[3], FALSE);
			scrollok(battlewin[4], FALSE);
			scrollok(battlewin[5], FALSE);
			scrollok(battlewin[6], FALSE);
		}
		for(x = 0; x < COLS; x++)
		{
			mvwprintw(battlewin[5], 0, x, "-");
			mvwprintw(battlewin[6], 0, x, "-");
		}
		wprintw(battlewin[0], "What would you\nlike to do?");
		mvwprintw(battlewin[1], 0, 1, "Moves1");
		mvwprintw(battlewin[1], 0, (COLS/4)+1, "Moves2");
		mvwprintw(battlewin[1], 1, 1, "Moves3");
		mvwprintw(battlewin[1], 1, (COLS/4)+1, "Moves4");
		wprintw(battlewin[2], "Everyone");
		wprintw(battlewin[3], "Party");
		wprintw(battlewin[4], "Enemies");
		refresh();
	}
	return 0;
};

int batinitscr()
{
	delwin(special[0]);
	delwin(special[1]);
	delwin(special[2]);
	delwin(special[3]);
	delwin(special[4]);
	leaveok(stdscr, TRUE);
	battlewin[0] = derwin(stdscr, 2, COLS/2, 0, 0);
	battlewin[1] = derwin(stdscr, 2, COLS/2, 0, COLS/2);
	battlewin[2] = derwin(stdscr, LINES - 7, 0, 3, 0);
	battlewin[3] = derwin(stdscr, 4, COLS/2, LINES - 4, 0);
	battlewin[4] = derwin(stdscr, 4, COLS/2, LINES - 4, COLS/2);
	battlewin[5] = derwin(stdscr, 1, 0, 2, 0);
	battlewin[6] = derwin(stdscr, 1, 0, LINES - 5, 0);
	scrollok(stdscr, FALSE);
	scrollok(battlewin[0], FALSE);
	scrollok(battlewin[1], FALSE);
	scrollok(battlewin[2], FALSE);
	scrollok(battlewin[3], FALSE);
	scrollok(battlewin[4], FALSE);
	scrollok(battlewin[5], FALSE);
	scrollok(battlewin[6], FALSE);
	oldlines = LINES;
	oldcols = COLS;
	clear();
	refresh();
	return 0;
}


int dispinitscr()
{
	delwin(battlewin[0]);
	delwin(battlewin[1]);
	delwin(battlewin[2]);
	delwin(battlewin[3]);
	delwin(battlewin[4]);
	delwin(battlewin[5]);
	delwin(battlewin[6]);
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
	clear();
	refresh();
	return 0;
}

int aibattle()
{
	return 1;			//not done
};

int dobattle(int group_number, int base_level)
{	
    detenstats(group_number, base_level);
    batinitscr();
    //not done
    return 0;
};

int detenstats(int group_number, int base_level)
{
//----------------------------------------------------------------------//
// ORDER OF OPERATIONS!!                                                //
//                                                                      //
// step 1: take first enemy number out of list with level offset number //
// step 2: apply offset to base level                                   //
// step 3: obtain class information for first enemy                     //
// step 4: Define enemy stats                                           //
//          a: Determine equations                                      //
//          b: use equations to determine each stat                     //
// step 5: store final enemy data in struct character battleen          //
// step 6: repeat for next enemy                                        //
//                                                                      //
// USE AT YOUR OWN RISK!!!!! ;)                      DONE               //
//----------------------------------------------------------------------//
	int x;
	int y;
	int rlev = 0;
	if(base_level < 0)
	{
		rlev = 1;
		base_level *= -1;
		base_level -= 2;
	}
	char tempint = 0;
	for(x = 0; x < 8; x++)
	{
		if(rlev)
		{
			#ifndef LINUX
				srand (_time32(NULL));
			#endif
			#ifdef LINUX
				srand (time(&temploctim));
			#endif
			tempint = rand() % 5;
			#ifndef LINUX
				srand (_time32(NULL));
			#endif
			#ifdef LINUX
				srand (time(&temploctim));
			#endif
		}
		battleen[x].level = base_level + currgame.grouptable[group_number][(2*x)+1];
		if(rlev)
			battleen[x].level += tempint;
		for(y=0;y<13;y++)
		{
			battleen[x].name[y] = currgame.enemytable [currgame.grouptable[group_number][(2*x)]][y];
		}
		battleen[x].symbol = currgame.enemytable [currgame.grouptable[group_number][(2*x)]][13];
		battleen[x].type = currgame.enemytable [currgame.grouptable[group_number][(2*x)]][14];
		battleen[x].ai = currgame.enemytable [currgame.grouptable[group_number][(2*x)]][15];
		for(y=0;y<9;y++)
		{
			battleen[x].classname[y] = currgame.chartype [battleen[x].type][y];
		}
		battleen[x].health = parseeq(currgame.chartype [battleen[x].type][9],battleen[x].level);
		battleen[x].attack = parseeq(currgame.chartype [battleen[x].type][10],battleen[x].level);
		battleen[x].defence = parseeq(currgame.chartype [battleen[x].type][11],battleen[x].level);
		battleen[x].wisdom = parseeq(currgame.chartype [battleen[x].type][12],battleen[x].level);
		battleen[x].resistance = parseeq(currgame.chartype [battleen[x].type][13],battleen[x].level);
		battleen[x].speed = parseeq(currgame.chartype [battleen[x].type][14],battleen[x].level);
		battleen[x].luck = parseeq(currgame.chartype [battleen[x].type][15],battleen[x].level);
	}
	return 0;
};

statis parseeq(char equation_number, int level)
{
	int x;
	statis temps, temps2;
	for(x=7;x<=0;x--)
	{
		temps = pow(level,x);
		temps *= (statis)currgame.equatable[(int)equation_number];
		temps2 += temps;
	}
	return temps2;
}

int loadenemies(char mqp [])
{
	FILE *loadench;
	loadench =fopen(mqp, "r");
	char check = 100;
	if (loadench == 0)
	{
		wprintw(stdscr, "Enemies file not found.\n");
		if (dbug)
			wprintw(stdscr, "Because the development tools are made,\nyou can make a new enemies file with this name.\n");
		
		hang(3);
		wprintw(stdscr, "Press any key to continue.\n");
		bi();
		exit(1);
	}
	if (loadench != 0)
	{
		if (dbug)
			wprintw(stdscr, "Enemies found!\n");
		fclose (loadench);
		if (dbug)
			wprintw(stdscr, "Starting to read Enemy data!\n");
		refresh();
		qwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiop = readen (mqp);
		if(qwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiop != 0)
		{
			wprintw(stdscr, "Some kind of error occured.\n");
			hang(3);
			wprintw(stdscr, "Press any key to continue.\n");
			while(check != ERR)
			{
				check = nbi();
			}
			bi();
			return 3;
		}
	}
	return 1;			//not done yet!
};

int readen (char openfile [13])
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
		fread(&trash,1,1,savefile);
		fread(&trash,1,1,savefile);
		fread(&characternum,4,1,loadfile);
		fread(&eqnum,4,1,loadfile);
		fread(&enemynum,4,1,savefile);
		fread(&characternum,4,1,loadfile);
		fread(&groupnum,4,1,savefile);
		fread(&itemnum,4,1,savefile);
		for(frunx = 0; frunx < chartypenum ; frunx++)
		{
			for(fruny = 0; fruny < 16; fruny++)
			{
				fread(&currgame.chartype[frunx][fruny],1,1,loadfile);
			};
		};
		for(frunx = 0; frunx < eqnum ; frunx++)
		{
			for(fruny = 0; fruny < 8; fruny++)
			{
				fread(&currgame.equatable[frunx][fruny],1,1,loadfile);
			};
		};
		for(frunx = 0; frunx < enemynum; frunx++)
		{
			for(fruny = 0; fruny < 16; fruny++)
			{
				fread(&currgame.enemytable[frunx][fruny],1,1,savefile);
			};
		};
		for(frunx = 0; frunx < characternum; frunx++)
		{
			for(fruny = 0; fruny < 16; fruny++)
			{
				fread(&currgame.charactable[frunx][fruny],1,1,loadfile);
			};
		};
		for(frunx = 0; frunx < groupnum ; frunx++)
		{
			for(fruny = 0; fruny < 16; fruny++)
			{
				fread(&currgame.grouptable[frunx][fruny],1,1,loadfile);
			};
		};
		for(frunx = 0; frunx < itemnum ; frunx++)
		{
			for(fruny = 0; fruny < 16; fruny++)
			{
				fread(&currgame.itemtable[frunx][fruny],1,1,loadfile);
			};
		};
		fclose(savefile);
	}
	wprintw(stdscr, "sucessful.\n");
	return 0;
};

int parsecharactable()
{
	int x, y;
	for(x = 0; x < 4; x++)
	{
		for(y = 0; y < 13; y++)
		{
			currgame.characters[x].name[y] = charactable[x][y];
		}
		currgame.characters[x].symbol = charactable[x][13];
		currgame.characters[x].leveq = charactable[x][14];
		currgame.characters[x].type = charactable[x][15];
	}
	return 0;
};
