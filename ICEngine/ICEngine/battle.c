WINDOW *battlewin[7];
char windowstrings [7][512][512];

int chartypenum;
int eqnum;
int enemynum;
int characternum;
int groupnum;
int itgroupnum;
int itemnum;
char batdone;

int en[8];
char charactable [16][16];
extern struct gameinfo currgame;
extern struct baten battleen [6];
extern char gamestate;

int oldlines, oldcols;

int checklev(statis exp, int leveq);
statis parseeq(char equation_number, int level);
int detenstats(int group_number, int base_level);
int readen (char openfile [13]);

int batdisp(char dispmode, char dispwin)
{
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
	int x, y;
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
	
	/*
	battlewin[0] = derwin(stdscr, 2, COLS/2, 0, 0);
	battlewin[1] = derwin(stdscr, 2, COLS/2, 0, COLS/2);
	battlewin[2] = derwin(stdscr, LINES - 7, 0, 3, 0);
	battlewin[3] = derwin(stdscr, 4, COLS/2, LINES - 4, 0);
	battlewin[4] = derwin(stdscr, 4, COLS/2, LINES - 4, COLS/2);
	battlewin[5] = derwin(stdscr, 1, 0, 2, 0);
	battlewin[6] = derwin(stdscr, 1, 0, LINES - 5, 0);
	*/
	
	wprintw(battlewin[0], "What would you\nlike to do?");
	mvwprintw(battlewin[1], 0, 1, "|Attack");
	mvwprintw(battlewin[1], 0, (COLS/4)+1, "Magic");
	mvwprintw(battlewin[1], 1, 1, "|Item");
	mvwprintw(battlewin[1], 1, (COLS/4)+1, "Run");
	wprintw(battlewin[2], "Everyone");
	wprintw(battlewin[3], "Party");
	wprintw(battlewin[4], "|Enemies\n|\n|");
	refresh();
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

int batinp(char partychar)
{
	char done;
	unsigned short int result = 0;
	char menu[3];
	while(done != 2)
	{
		
	}
	return result;
};

unsigned short int enemythink(char battlechar)
{
	unsigned short int result = 0;
	return result;
};

int batthink(statis entry[3])
{
	if(entry[0] < 4)
	{
		batinp(entry[0]);
		return 0;
	}
	if((entry[0] > 3)&&(entry[0] < 10))
	{
		enemythink(entry[0]-4);
		return 0;
	}
	return 1;
}

int sortlist(statis list[10][2], statis listsorted[10][2])
{
	int x;
	int linenum = 0;
	char temp = 0;
	int listcount = 0;
	int listsortedcount = 0;
	char dn[10];
	int dncount = 0;
	char skip = 0;
	for(listsortedcount=0;listsortedcount<10;listsortedcount++)
	{
		for(listcount=0;listcount<10;listcount++)
		{
			for(x=0;x<dncount;x++)
			{
				if(listcount == dn[x])
				{
					skip = 1;
					break;
				}
			}
			if((list[listcount][1] >= temp)&&(skip != 1))
			{
				temp = list[listcount][1];
				linenum = listcount;
			}
			skip = 0;
		}
		listsorted[listsortedcount][0] = list[linenum][0];
		listsorted[listsortedcount][1] = list[linenum][1];
		list[linenum][0] = 0;
		list[linenum][1] = 0;
		dn[dncount] = linenum;
		dncount++;
		temp = 0;
	}
	return 0;
}

int dobattle(int group_number, int base_level)
{
	char tempgamestate;
	statis battlelist[10][2];
	statis battlelistsorted[10][2];
	int x;
	char batdone = 0;
    detenstats(group_number, base_level);
    batinitscr();
    tempgamestate = gamestate;
    gamestate = BATTLE;
	for(;batdone == 0;)
    {
		for(x=0;x<10;x++)
		{
			battlelist[x][0] = 32;
			battlelist[x][1] = 0;
		}
		for(x=0;x<10;x++)
		{
			battlelistsorted[x][0] = 32;
			battlelistsorted[x][1] = 0;
		}
		batdisp(0,7);
		if((self.partyids[0] != 32)&&(currgame.characters[(int) self.partyids[0]].currhealth > 0))
		{
			battlelist[0][0] = 0;
			battlelist[0][1] = currgame.characters[(int) self.partyids[0]].currspeed;
		}
		if((self.partyids[1] != 32)&&(currgame.characters[(int) self.partyids[1]].currhealth > 0))
		{
			battlelist[1][0] = 1;
			battlelist[1][1] = currgame.characters[(int) self.partyids[1]].currspeed;
		}
		if((self.partyids[2] != 32)&&(currgame.characters[(int) self.partyids[2]].currhealth > 0))
		{
			battlelist[2][0] = 2;
			battlelist[2][1] = currgame.characters[(int) self.partyids[2]].currspeed;
		}
		if((self.partyids[3] != 32)&&(currgame.characters[(int) self.partyids[3]].currhealth > 0))
		{
			battlelist[3][0] = 3;
			battlelist[3][1] = currgame.characters[(int) self.partyids[3]].currspeed;
		}
		if((battleen[0].symbol != 0) && (battleen[0].currhealth > 0))
		{
			battlelist[4][0] = 4;
			battlelist[4][1] = battleen[0].currspeed;
		}
		if((battleen[1].symbol != ' ') && (battleen[1].currhealth > 0))
		{
			battlelist[5][0] = 5;
			battlelist[5][1] = battleen[1].currspeed;
		}
		if((battleen[2].symbol != ' ') && (battleen[2].currhealth > 0))
		{
			battlelist[6][0] = 6;
			battlelist[6][1] = battleen[2].currspeed;
		}
		if((battleen[3].symbol != ' ') && (battleen[3].currhealth > 0))
		{
			battlelist[7][0] = 7;
			battlelist[7][1] = battleen[3].currspeed;
		}
		if((battleen[4].symbol != ' ') && (battleen[4].currhealth > 0))
		{
			battlelist[8][0] = 8;
			battlelist[8][1] = battleen[4].currspeed;
		}
		if((battleen[5].symbol != ' ') && (battleen[5].currhealth > 0))
		{
			battlelist[9][0] = 9;
			battlelist[9][1] = battleen[5].currspeed;
		}
		sortlist(battlelist, battlelistsorted);
		for(x=0;x<10;x++)
		{
			if(battlelistsorted[x][0] != 32)
				batthink(battlelistsorted[x]);
		}
    }
    //unresolved subfunctions, probably involving the development of a
    //scripting system for the enemy ai, not to mention the coding of the
    //user input routines.
    currgame.battleflag = batdone;
    gamestate = tempgamestate;
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
	for(x = 0; x < 6; x++)
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
		battleen[x].currhealth = battleen[x].health;
		battleen[x].attack = parseeq(currgame.chartype [battleen[x].type][10],battleen[x].level);
		battleen[x].currattack = battleen[x].attack;
		battleen[x].defence = parseeq(currgame.chartype [battleen[x].type][11],battleen[x].level);
		battleen[x].currdefence = battleen[x].defence;
		battleen[x].wisdom = parseeq(currgame.chartype [battleen[x].type][12],battleen[x].level);
		battleen[x].currwisdom = battleen[x].wisdom;
		battleen[x].resistance = parseeq(currgame.chartype [battleen[x].type][13],battleen[x].level);
		battleen[x].currresistance = battleen[x].resistance;
		battleen[x].speed = parseeq(currgame.chartype [battleen[x].type][14],battleen[x].level);
		battleen[x].currspeed = battleen[x].speed;
		battleen[x].luck = parseeq(currgame.chartype [battleen[x].type][15],battleen[x].level);
		battleen[x].currluck = battleen[x].luck;
	}
	return 0;
};

int parsecharactable()
{
//----------------------------------------------------------------------//
// ORDER OF OPERATIONS!!                                                //
//                                                                      //
// step 1: Copy character data from defaults to player character tables //
// step 1a: Write default stats to character table                      //
//          a: Determine equations                                      //
//          b: use equations to determine each stat                     //
// step 1b: store final enemy data in struct character battleen         //
// step 2: repeat for next character                                    //
//                                                                      //
// USE AT YOUR OWN RISK!!!!! ;)                      DONE               //
//----------------------------------------------------------------------//
	int x;
	int y;
	for(x = 0; x < 16; x++)
	{
		currgame.characters[x].exp = 0;
		currgame.characters[x].level = 0;
		for(y=0;y<13;y++)
		{
			currgame.characters[x].name[y] = currgame.charactable[x][y];
		}
		currgame.characters[x].symbol = currgame.charactable[x][13];
		currgame.characters[x].leveq = currgame.enemytable [x][14];
		currgame.characters[x].type = currgame.enemytable [x][15];
		for(y=0;y<9;y++)
		{
			currgame.characters[x].classname[y] = currgame.chartype [currgame.characters[x].type][y];
		}
		currgame.characters[x].level = checklev(currgame.characters[x].exp, currgame.characters[x].leveq);
		currgame.characters[x].health = parseeq(currgame.chartype[currgame.characters[x].type][9],currgame.characters[x].level);
		currgame.characters[x].attack = parseeq(currgame.chartype[currgame.characters[x].type][10],currgame.characters[x].level);
		currgame.characters[x].defence = parseeq(currgame.chartype[currgame.characters[x].type][11],currgame.characters[x].level);
		currgame.characters[x].wisdom = parseeq(currgame.chartype[currgame.characters[x].type][12],currgame.characters[x].level);
		currgame.characters[x].resistance = parseeq(currgame.chartype[currgame.characters[x].type][13],currgame.characters[x].level);
		currgame.characters[x].speed = parseeq(currgame.chartype[currgame.characters[x].type][14],currgame.characters[x].level);
		currgame.characters[x].luck = parseeq(currgame.chartype[currgame.characters[x].type][15],currgame.characters[x].level);
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
//	char check = 100;
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
			nbi();
			hang(3);
			endwin();
			exit(1);
			return 1;
		}
	}
	parsecharactable();	//Character table is built BEFORE the save files are loaded!!!!!
	return 0;
};

int readen (char openfile [13])
{
	unsigned int tempint;
	unsigned char tempchar;
	loadfile = fopen(openfile,"r");
	if(loadfile == FALSE)
	{
		return 1;
	}
	else
	{
		fread(&trash,1,1,loadfile);
		fread(&trash,1,1,loadfile);
		if(trash == 0)
		{
			fread(&characternum,1,1,loadfile);
			fread(&eqnum,1,1,loadfile);
			fread(&enemynum,1,1,loadfile);
			fread(&characternum,1,1,loadfile);
			fread(&groupnum,1,1,loadfile);
			fread(&itemnum,1,1,loadfile);
		}
		if(trash != 0)
		{
			fread(&characternum,4,1,loadfile);
			fread(&eqnum,4,1,loadfile);
			fread(&enemynum,4,1,loadfile);
			fread(&characternum,4,1,loadfile);
			fread(&groupnum,4,1,loadfile);
			if(trash >= 2)
			{
				fread(&itgroupnum,4,1,loadfile);
			}
			fread(&itemnum,4,1,loadfile);
		}
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
				fread(&currgame.equatable[frunx][fruny],8,1,loadfile);
			};
		};
		for(frunx = 0; frunx < enemynum; frunx++)
		{
			for(fruny = 0; fruny < 16; fruny++)
			{
				fread(&currgame.enemytable[frunx][fruny],1,1,loadfile);
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
			for(fruny = 0; fruny < 13; fruny++)
			{
				fread(&currgame.grouptable[frunx][fruny],1,1,loadfile);
			};
			fread(&tempchar,1,1,loadfile);
			tempint = tempchar;
			tempint = tempint << 8;
			fread(&tempchar,1,1,loadfile);
			tempint += tempchar;
			fread(&tempchar,1,1,loadfile);
			tempint = tempint << 8;
			tempint += tempchar;
			currgame.grouptableexp[frunx] = tempint;
		};
		if(trash >= 2)
		{
			for(frunx = 0; frunx < itgroupnum ; frunx++)
			{
				for(fruny = 0; fruny < 16; fruny++)
				{
					fread(&currgame.itemgrouptable[frunx][fruny],1,1,loadfile);
				};
			};
		}
		for(frunx = 0; frunx < itemnum ; frunx++)
		{
			for(fruny = 0; fruny < 16; fruny++)
			{
				fread(&currgame.itemtable[frunx][fruny],1,1,loadfile);
			};
		};
		fclose(loadfile);
	}
	return 0;
};

int checklev(statis exp, int leveq)										//I'm going to do the stupid thing and trust that there will be no equations that place the experience for any level below 255 over UNSIGNED LONG.
{
	int x;
	int tempint;
	for(x = 0; x < 256;x++)
	{
		tempint = parseeq(leveq, x);
		if(tempint > exp)
		{
			x--;
			break;
		}
	}
	return x;
};
