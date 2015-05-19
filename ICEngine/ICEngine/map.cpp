#ifndef LINUX
	#include <stdio.h>
	#include <stdlib.h>
	#include <ctype.h>
	#include <conio.h>
	#include <string.h>
	#include <time.h>
	#include "unidefs.cpp"
	#include "gamelogictypedefs.cpp"
#endif

extern char input[5];
extern char dbug;
extern char scoord;
extern char gamestate;
extern char justwarped;
extern struct mapdata nextmap;
extern struct mapdata currmap;
extern struct gameinfo currgame;
extern struct player self;

FILE *loadmapf, *loadmapch;
int readmap(char mqp []);
char mapendtest;
int tempint;
int loadmaprunx;
int loadmapruny;
int loadmaprunz;
int lastparnum;
char qwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiop;

int loadmap(char mqp[])
{
	if(LINES != self.config.screenheight)
	{
		delwin(special[2]);
		delwin(special[3]);
		delwin(special[4]);
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
	int check;
	tempint = lastparnum;
	while(tempint == lastparnum)
	{
		#ifndef LINUX
			srand (_time32(NULL));
		#endif
		#ifdef LINUX
			srand (time(&temploctim));
		#endif
		tempint = rand() % currgame.parablenum;
		#ifndef LINUX
			srand (_time32(NULL));
		#endif
		#ifdef LINUX
			srand (time(&temploctim));
		#endif
	}
	lastparnum = tempint;
	clear();
	if(LINES != self.config.screenheight)
	{
		delwin(special[2]);
		delwin(special[3]);
		delwin(special[4]);
		special[4] = derwin(stdscr, 1, 0, LINES - 2, 0);
		special[2] = derwin(stdscr, 1, 0, LINES - 2, 0);
		special[3] = derwin(stdscr, 1, 0, LINES - 1, 0);
		scrollok(special[2], FALSE);
		scrollok(special[3], TRUE);
		scrollok(special[4], FALSE);
	}
	if (dbug)
		wprintw(stdscr, "\nLoading map %s...\n",mqp);
	if (!dbug)
		wprintw(stdscr, "\nLoading map...\n");
	wclear(special[2]);
	wclear(special[3]);
	wclear(special[4]);
	for(loadmaprunz = 0; loadmaprunz < 1024; loadmaprunz++)
	{
		if(currgame.loadmapstrings[tempint][loadmaprunz] == '\n')
		{
			loadmaprunx = loadmaprunz;
		}
		if(currgame.loadmapstrings[tempint][loadmaprunz] == '-')
		{
			loadmapruny = loadmaprunz;
		}
	}
	int lolasdf = strlen(currgame.loadmapstrings[lastparnum]);
	tempint = lolasdf - loadmaprunx;
	tempint++;
	for(check = loadmaprunx; check > 0; check--);
	{
//		if(currgame.loadmapstrings[lastparnum][(loadmaprunx - check)] != '\n')
//		{
			mvwprintw(special[2], 0, COLS - check, "%c",currgame.loadmapstrings[lastparnum][(loadmaprunx - check)]);
//			mvwprintw(special[2], 0, COLS - check, "a");
//		}
	}
	for(check = loadmapruny; check <= lolasdf; check++);
	{
//		if(currgame.loadmapstrings[lastparnum][(int) check] != '\n')
//		{
			mvwprintw(special[3], 0, (COLS - lolasdf) + check, "%c", currgame.loadmapstrings[lastparnum][(int) check]);
//			mvwprintw(special[3], 0, (COLS - lolasdf) + check, "b");
//		}
	}
//	mvwprintw(special[2], 0, 0, "%s",currgame.loadmapstrings[tempint]);
//	mvwprintw(special[3], 0, 0, "%s", &currgame.loadmapstrings[tempint][loadmapruny]);
	refresh();
	if(LINES != self.config.screenheight)
	{
		delwin(special[2]);
		delwin(special[3]);
		delwin(special[4]);
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
	loadmapch =fopen(mqp, "r");
	if (loadmapch == 0)
	{
		wprintw(stdscr, "Map not found.\n");
		if (dbug)
			wprintw(stdscr, "Because the map development tools are made,\nyou can make a new map file with this name.\n");
		if(gamestate != 1)
			wprintw(stdscr, "Returning to previous map.\n");
		scoord = 0;
		hang(3);
		wprintw(stdscr, "Press any key to continue.\n");
		bi();
		justwarped = TRUE;
		return 1;
	}
	if (loadmapch != 0)
	{
		if (dbug)
			wprintw(stdscr, "Map found\n");
		fclose (loadmapch);
		if (dbug)
			wprintw(stdscr, "Map read start\n");
		refresh();
		qwertyuiopqwertyuiopqwertyuiopqwertyuiopqwertyuiop = readmap (mqp);
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
			justwarped = TRUE;
			if(currmap.isloaded == 0)
				return 3;
			else if(currmap.isloaded == 1)
				return 1;
		}
	}
	wprintw(stdscr, "Map sucessfully read.\n");
	hang(3);
	wprintw(stdscr, "Press any key to continue.\n");
	while(check != ERR)
	{
		check = nbi();
	}
	bi();
	justwarped = TRUE;
	return 0;
};

int readmap (char mqp [])
{
	loadmapf = fopen(mqp,"r");
	if(loadmapf == FALSE)
	{
		return 1;
	}
	else
	{
		currmap.isloaded = 1;
		fread(&currmap.vernum,1,1,loadmapf);
		//fread(&sep,1,1,loadmapf);
		if(currmap.vernum == 1)
			{
				fread(&currmap.scripts,1,1,loadmapf);
				//fread(&sep,1,1,loadmapf);
				fread(&currmap.enemytf,1,1,loadmapf);
				//fread(&sep,1,1,loadmapf);
				fread(&currmap.npctf,1,1,loadmapf);
				//fread(&sep,1,1,loadmapf);
				if (currmap.npctf == TRUE)
				{
					fread(&currmap.npcnum,4,1,loadmapf);
					//fread(&sep,1,1,loadmapf);
				}
				fread(&currmap.warpnum,4,1,loadmapf);
				//fread(&sep,1,1,loadmapf);
				for (loadmaprunx = 0; loadmaprunx < 20; loadmaprunx++)
				{
					fread(&currmap.mapname [loadmaprunx],1,1,loadmapf);
				}
				currmap.mapname[20] = 0;
				//fread(&sep,1,1,loadmapf);
				fread(&currmap.mapx,4,1,loadmapf);
				//fread(&sep,1,1,loadmapf);
				fread(&currmap.mapy,4,1,loadmapf);
				//fread(&sep,1,1,loadmapf);
				if (dbug)
					wprintw(stdscr, "This map is size %d,%d.\n",currmap.mapx,currmap.mapy);
				currmap.fixedx = currmap.mapx - 1;
				currmap.fixedy = currmap.mapy - 1;
				for (loadmapruny = 0; loadmapruny < currmap.mapy; loadmapruny++)
				{
					for (loadmaprunx = 0; loadmaprunx < currmap.mapx; loadmaprunx++)
						{
							fread(&currmap.map [loadmaprunx][loadmapruny],1,1,loadmapf);
							if (dbug)
								wprintw(stdscr, "%c",currmap.map [loadmaprunx][loadmapruny]);
							if (dbug)
								if (loadmaprunx == currmap.fixedx)
									wprintw(stdscr, "\n");
						}
				}
				tempint = 0;
				for (loadmapruny = 0; loadmapruny < currmap.mapy; loadmapruny++)
				{
					for (loadmaprunx = 0; loadmaprunx < currmap.mapx; loadmaprunx++)
						{
							fread(&currmap.maperm [loadmaprunx][loadmapruny],1,1,loadmapf);
							if((currmap.maperm [loadmaprunx][loadmapruny] == 2)||(currmap.maperm [loadmaprunx][loadmapruny] == 4))
							{
								currmap.scriptfilename[tempint].x = loadmaprunx;
								currmap.scriptfilename[tempint].y = loadmapruny;
								tempint++;
							}
						}
				}
				//fread(&sep,1,1,loadmapf);
				for (loadmapruny = 0; loadmapruny < currmap.warpnum; loadmapruny++)
					{
						for (loadmaprunx = 0; loadmaprunx < 13; loadmaprunx++)
							{
								fread(&currmap.mapwarps [loadmapruny].mapname [loadmaprunx],1,1,loadmapf);
							}
							fread(&currmap.mapwarps [loadmapruny].mwx [0],4,1,loadmapf);
							//fwrite(&sep,1,1,loadmapf);
							fread(&currmap.mapwarps [loadmapruny].mwy [0],4,1,loadmapf);
							//fwrite(&sep,1,1,loadmapf);
							fread(&currmap.mapwarps [loadmapruny].mwx [1],4,1,loadmapf);
							//fwrite(&sep,1,1,loadmapf);
							fread(&currmap.mapwarps [loadmapruny].mwy [1],4,1,loadmapf);
							//fwrite(&sep,1,1,loadmapf);
					}
				//fread(&sep,1,1,loadmapf);
				for (loadmapruny = 0; loadmapruny < currmap.scripts; loadmapruny++)
				{
					for (loadmaprunx = 0; loadmaprunx < 13; loadmaprunx++)
					{
						fread(&currmap.scriptfilename [loadmapruny].scriptfile[loadmaprunx],1,1,loadmapf);
					}
					//fread(&sep,1,1,loadmapf);
				}
				fread(&currmap.enemytf,1,1,loadmapf);
				//fread(&sep,1,1,loadmapf);
				if (currmap.enemytf == TRUE)
					{
						for (loadmapruny = 0; loadmapruny < 10; loadmapruny++)
						{
							fread(&currmap.enemyent [0][loadmapruny],4,1,loadmapf);
							//fread(&sep,1,1,loadmapf);
							fread(&currmap.enemyent [1][loadmapruny],4,1,loadmapf);
							//fread(&sep,1,1,loadmapf);
						}
					}
				if (currmap.npctf == TRUE)
					{
					for (loadmaprunz = 0;loadmaprunz < currmap.npcnum; loadmaprunz++)
						{
							fread(&currmap.people [loadmaprunz].name [0],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [1],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [2],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [3],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [4],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [5],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [6],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [7],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [8],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [9],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [10],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [11],1,1,loadmapf);
								for (loadmaprunx = 0; loadmaprunx < 13; loadmaprunx++)
									{
										fread(&currmap.people [loadmaprunz].scriptfile [loadmaprunx],1,1,loadmapf);
									}
							fread(&currmap.people [loadmaprunz].x,4,1,loadmapf);
							fread(&currmap.people [loadmaprunz].y,4,1,loadmapf);
							fread(&currmap.people [loadmaprunz].movetype,1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].fdependsnum,4,1,loadmapf);
							fread(&currmap.people [loadmaprunz].fnotifnum,4,1,loadmapf);
								for (loadmaprunx = 0; loadmaprunx < currmap.people [loadmaprunz].fdependsnum; loadmaprunx++)
								{
									fread(&currmap.people [loadmaprunz].fdepends[loadmaprunx],4,1,loadmapf);
								}
							fread(&currmap.people [loadmaprunz].fnotifnum,4,1,loadmapf);
								for (loadmaprunx = 0; loadmaprunx < currmap.people [loadmaprunz].fnotifnum; loadmaprunx++)
								{
									fread(&currmap.people [loadmaprunz].fnotif[loadmaprunx],4,1,loadmapf);
								}
		
						}
					}
				}
		if(currmap.vernum == 2)
			{
			fread(&currmap.vernum2,1,1,loadmapf);
			//fread(&sep,1,1,loadmapf);
			if(currmap.vernum2 == 0)
				{
				fread(&currmap.scripts,1,1,loadmapf);
				//fread(&sep,1,1,loadmapf);
				fread(&currmap.enemytf,1,1,loadmapf);
				//fread(&sep,1,1,loadmapf);
				fread(&currmap.npctf,1,1,loadmapf);
				//fread(&sep,1,1,loadmapf);
				if (currmap.npctf == TRUE)
				{
					fread(&currmap.npcnum,1,1,loadmapf);
					//fread(&sep,1,1,loadmapf);
				}
				fread(&currmap.startmaptf,1,1,loadmapf);
				//fread(&sep,1,1,loadmapf);
				if (currmap.startmaptf == TRUE)
				{
					fread(&currmap.startx,1,1,loadmapf);
					if(scoord == 1)
						self.x = currmap.startx;
					//fread(&sep,1,1,loadmapf);
					fread(&currmap.starty,1,1,loadmapf);
					if(scoord == 1)
						self.y = currmap.starty;
					if(dbug)
						wprintw(stdscr, "Start position for this map %d,%d.\n", currmap.startx, currmap.starty);
					//fread(&sep,1,1,loadmapf);
				}
				fread(&currmap.warpnum,1,1,loadmapf);
				//fread(&sep,1,1,loadmapf);
				for (loadmaprunx = 0; loadmaprunx < 20; loadmaprunx++)
				{
					fread(&currmap.mapname [loadmaprunx],1,1,loadmapf);
				}
				//fread(&sep,1,1,loadmapf);
				fread(&currmap.mapx,1,1,loadmapf);
				//fread(&sep,1,1,loadmapf);
				fread(&currmap.mapy,1,1,loadmapf);
				//fread(&sep,1,1,loadmapf);
				if (dbug)
					wprintw(stdscr, "This map is size %d,%d.\n",currmap.mapx,currmap.mapy);
				currmap.fixedx = currmap.mapx - 1;
				currmap.fixedy = currmap.mapy - 1;
				for (loadmapruny = 0; loadmapruny < currmap.mapy; loadmapruny++)
				{
					for (loadmaprunx = 0; loadmaprunx < currmap.mapx; loadmaprunx++)
						{
							fread(&currmap.map [loadmaprunx][loadmapruny],1,1,loadmapf);
							if (dbug)
								wprintw(stdscr, "%c",currmap.map [loadmaprunx][loadmapruny]);
							if (dbug)
								if (loadmaprunx == currmap.fixedx)
									wprintw(stdscr, "\n");
						}
				}
				//fread(&sep,1,1,loadmapf);
				for (loadmapruny = 0; loadmapruny < currmap.mapy; loadmapruny++)
				{
					for (loadmaprunx = 0; loadmaprunx < currmap.mapx; loadmaprunx++)
						{
							fread(&currmap.maperm [loadmaprunx][loadmapruny],1,1,loadmapf);
							if (dbug)
								wprintw(stdscr, "%c",currmap.maperm [loadmaprunx][loadmapruny]);
							if (dbug)
								if (loadmaprunx == currmap.fixedx)
									wprintw(stdscr, "\n");
						}
				}
				//fread(&sep,1,1,loadmapf);
				if (dbug)
					wprintw(stdscr, "Has %d warps at:\n", currmap.warpnum);
				for (loadmapruny = 0; loadmapruny < currmap.warpnum; loadmapruny++)
					{
						for (loadmaprunx = 0; loadmaprunx < 13; loadmaprunx++)
							{
								fread(&currmap.mapwarps [loadmapruny].mapname [loadmaprunx],1,1,loadmapf);
							}
							fread(&currmap.mapwarps [loadmapruny].mwx [0],1,1,loadmapf);
							//fwrite(&sep,1,1,loadmapf);
							fread(&currmap.mapwarps [loadmapruny].mwy [0],1,1,loadmapf);
							//fwrite(&sep,1,1,loadmapf);
							if (dbug)
								wprintw(stdscr, "%d, %d\n", currmap.mapwarps[loadmapruny].mwx [0],currmap.mapwarps[loadmapruny].mwy [0]);
							fread(&currmap.mapwarps [loadmapruny].mwx [1],1,1,loadmapf);
							//fwrite(&sep,1,1,loadmapf);
							fread(&currmap.mapwarps [loadmapruny].mwy [1],1,1,loadmapf);
							//fwrite(&sep,1,1,loadmapf);
							if (dbug)
								wprintw(stdscr, "%d, %d\n", currmap.mapwarps[loadmapruny].mwx [1],currmap.mapwarps[loadmapruny].mwy [1]);
					}
				//fread(&sep,1,1,loadmapf);
				for (loadmapruny = 0; loadmapruny < currmap.scripts; loadmapruny++)
				{
					for (loadmaprunx = 0; loadmaprunx < 13; loadmaprunx++)
							{
								fread(&currmap.scriptfilename [loadmapruny].scriptfile[loadmaprunx],1,1,loadmapf);
							}
					//fread(&sep,1,1,file);
					fread(&currmap.scriptfilename [loadmapruny].fdependsnum,1,1,loadmapf);
					fread(&currmap.scriptfilename [loadmapruny].fnotifnum,1,1,loadmapf);
					for (loadmaprunx = 0; loadmaprunx < currmap.scriptfilename [loadmapruny].fdependsnum; loadmaprunx++)
					{
						fread(&currmap.scriptfilename [loadmapruny].fdepends[loadmaprunx],1,1,loadmapf);
					}
					for (loadmaprunx = 0; loadmaprunx < currmap.scriptfilename [loadmapruny].fnotifnum; loadmaprunx++)
					{
						fread(&currmap.scriptfilename [loadmapruny].fnotif[loadmaprunx],1,1,loadmapf);
					}
				}
				fread(&currmap.enemytf,1,1,loadmapf);
				//fread(&sep,1,1,loadmapf);
				if (currmap.enemytf == TRUE)
					{
						for (loadmapruny = 0; loadmapruny < 10; loadmapruny++)
						{
							fread(&currmap.enemyent [0][loadmapruny],1,1,loadmapf);
							//fread(&sep,1,1,loadmapf);
							fread(&currmap.enemyent [1][loadmapruny],1,1,loadmapf);
							//fread(&sep,1,1,loadmapf);
						}
					}
				if (currmap.npctf == TRUE)
					{
					for (loadmaprunz = 0;loadmaprunz < currmap.npcnum; loadmaprunz++)
						{
							fread(&currmap.people [loadmaprunz].name [0],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [1],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [2],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [3],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [4],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [5],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [6],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [7],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [8],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [9],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [10],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [11],1,1,loadmapf);
								for (loadmaprunx = 0; loadmaprunx < 13; loadmaprunx++)
									{
										fread(&currmap.people [loadmaprunz].scriptfile [loadmaprunx],1,1,loadmapf);
									}
							fread(&currmap.people [loadmaprunz].x,1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].y,1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].movetype,1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].fdependsnum,1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].fnotifnum,1,1,loadmapf);
								for (loadmaprunx = 0; loadmaprunx < currmap.people [loadmaprunz].fdependsnum; loadmaprunx++)
								{
									fread(&currmap.people [loadmaprunz].fdepends[loadmaprunx],1,1,loadmapf);
								}
							fread(&currmap.people [loadmaprunz].fnotifnum,1,1,loadmapf);
								for (loadmaprunx = 0; loadmaprunx < currmap.people [loadmaprunz].fnotifnum; loadmaprunx++)
								{
									fread(&currmap.people [loadmaprunz].fnotif[loadmaprunx],1,1,loadmapf);
								}
		
						}
					}
			}
			if(currmap.vernum2 == 1)
				{
				fread(&currmap.scripts,1,1,loadmapf);
				//fread(&sep,1,1,loadmapf);
				fread(&currmap.enemytf,1,1,loadmapf);
				//fread(&sep,1,1,loadmapf);
				fread(&currmap.npctf,1,1,loadmapf);
				//fread(&sep,1,1,loadmapf);
				if (currmap.npctf == TRUE)
				{
					fread(&currmap.npcnum,4,1,loadmapf);
					//fread(&sep,1,1,loadmapf);
				}
				fread(&currmap.startmaptf,1,1,loadmapf);
				//fread(&sep,1,1,loadmapf);
				if (currmap.startmaptf == TRUE)
				{
					fread(&currmap.startx,4,1,loadmapf);
					if(scoord == 1)
						self.x = currmap.startx;
					//fread(&sep,1,1,loadmapf);
					fread(&currmap.starty,4,1,loadmapf);
					if(scoord == 1)
						self.y = currmap.starty;
					if(dbug)
						wprintw(stdscr, "Start position for this map %d,%d.\n", currmap.startx, currmap.starty);
					//fread(&sep,1,1,loadmapf);
				}
				fread(&currmap.warpnum,4,1,loadmapf);
				//fread(&sep,1,1,loadmapf);
				for (loadmaprunx = 0; loadmaprunx < 20; loadmaprunx++)
				{
					fread(&currmap.mapname [loadmaprunx],1,1,loadmapf);
				}
				//fread(&sep,1,1,loadmapf);
				fread(&currmap.mapx,4,1,loadmapf);
				//fread(&sep,1,1,loadmapf);
				fread(&currmap.mapy,4,1,loadmapf);
				//fread(&sep,1,1,loadmapf);
				if (dbug)
					wprintw(stdscr, "This map is size %d,%d.\n",currmap.mapx,currmap.mapy);
				currmap.fixedx = currmap.mapx - 1;
				currmap.fixedy = currmap.mapy - 1;
				for (loadmapruny = 0; loadmapruny < currmap.mapy; loadmapruny++)
				{
					for (loadmaprunx = 0; loadmaprunx < currmap.mapx; loadmaprunx++)
						{
							fread(&currmap.map [loadmaprunx][loadmapruny],1,1,loadmapf);
							if (dbug)
								wprintw(stdscr, "%c",currmap.map [loadmaprunx][loadmapruny]);
							if (dbug)
								if (loadmaprunx == currmap.fixedx)
									wprintw(stdscr, "\n");
						}
				}
				//fread(&sep,1,1,loadmapf);
				for (loadmapruny = 0; loadmapruny < currmap.mapy; loadmapruny++)
				{
					for (loadmaprunx = 0; loadmaprunx < currmap.mapx; loadmaprunx++)
						{
							fread(&currmap.maperm [loadmaprunx][loadmapruny],1,1,loadmapf);
							if (dbug)
								wprintw(stdscr, "%c",currmap.maperm [loadmaprunx][loadmapruny]);
							if (dbug)
								if (loadmaprunx == currmap.fixedx)
									wprintw(stdscr, "\n");
						}
				}
				//fread(&sep,1,1,loadmapf);
				if (dbug)
					wprintw(stdscr, "Has %d warps at:\n", currmap.warpnum);
				for (loadmapruny = 0; loadmapruny < currmap.warpnum; loadmapruny++)
					{
						for (loadmaprunx = 0; loadmaprunx < 13; loadmaprunx++)
							{
								fread(&currmap.mapwarps [loadmapruny].mapname [loadmaprunx],1,1,loadmapf);
							}
							fread(&currmap.mapwarps [loadmapruny].mwx [0],4,1,loadmapf);
							//fwrite(&sep,1,1,loadmapf);
							fread(&currmap.mapwarps [loadmapruny].mwy [0],4,1,loadmapf);
							//fwrite(&sep,1,1,loadmapf);
							if (dbug)
								wprintw(stdscr, "%d, %d\n", currmap.mapwarps[loadmapruny].mwx [0],currmap.mapwarps[loadmapruny].mwy [0]);
							fread(&currmap.mapwarps [loadmapruny].mwx [1],4,1,loadmapf);
							//fwrite(&sep,1,1,loadmapf);
							fread(&currmap.mapwarps [loadmapruny].mwy [1],4,1,loadmapf);
							//fwrite(&sep,1,1,loadmapf);
							if (dbug)
								wprintw(stdscr, "%d, %d\n", currmap.mapwarps[loadmapruny].mwx [1],currmap.mapwarps[loadmapruny].mwy [1]);
					}
				//fread(&sep,1,1,loadmapf);
				for (loadmapruny = 0; loadmapruny < currmap.scripts; loadmapruny++)
				{
					for (loadmaprunx = 0; loadmaprunx < 13; loadmaprunx++)
							{
								fread(&currmap.scriptfilename [loadmapruny].scriptfile[loadmaprunx],1,1,loadmapf);
							}
					//fread(&sep,1,1,file);
					fread(&currmap.scriptfilename [loadmapruny].fdependsnum,4,1,loadmapf);
					fread(&currmap.scriptfilename [loadmapruny].fnotifnum,4,1,loadmapf);
					for (loadmaprunx = 0; loadmaprunx < currmap.scriptfilename [loadmapruny].fdependsnum; loadmaprunx++)
					{
						fread(&currmap.scriptfilename [loadmapruny].fdepends[loadmaprunx],4,1,loadmapf);
					}
					for (loadmaprunx = 0; loadmaprunx < currmap.scriptfilename [loadmapruny].fnotifnum; loadmaprunx++)
					{
						fread(&currmap.scriptfilename [loadmapruny].fnotif[loadmaprunx],4,1,loadmapf);
					}
				}
				fread(&currmap.enemytf,1,1,loadmapf);
				//fread(&sep,1,1,loadmapf);
				if (currmap.enemytf == TRUE)
					{
						for (loadmapruny = 0; loadmapruny < 10; loadmapruny++)
						{
							fread(&currmap.enemyent [0][loadmapruny],4,1,loadmapf);
							//fread(&sep,1,1,loadmapf);
							fread(&currmap.enemyent [1][loadmapruny],4,1,loadmapf);
							//fread(&sep,1,1,loadmapf);
						}
					}
				if (currmap.npctf == TRUE)
					{
					for (loadmaprunz = 0;loadmaprunz < currmap.npcnum; loadmaprunz++)
						{
							fread(&currmap.people [loadmaprunz].name [0],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [1],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [2],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [3],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [4],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [5],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [6],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [7],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [8],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [9],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [10],1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].name [11],1,1,loadmapf);
								for (loadmaprunx = 0; loadmaprunx < 13; loadmaprunx++)
									{
										fread(&currmap.people [loadmaprunz].scriptfile [loadmaprunx],1,1,loadmapf);
									}
							fread(&currmap.people [loadmaprunz].x,4,1,loadmapf);
							fread(&currmap.people [loadmaprunz].y,4,1,loadmapf);
							fread(&currmap.people [loadmaprunz].movetype,1,1,loadmapf);
							fread(&currmap.people [loadmaprunz].fdependsnum,4,1,loadmapf);
							fread(&currmap.people [loadmaprunz].fnotifnum,4,1,loadmapf);
								for (loadmaprunx = 0; loadmaprunx < currmap.people [loadmaprunz].fdependsnum; loadmaprunx++)
								{
									fread(&currmap.people [loadmaprunz].fdepends[loadmaprunx],4,1,loadmapf);
								}
							fread(&currmap.people [loadmaprunz].fnotifnum,4,1,loadmapf);
								for (loadmaprunx = 0; loadmaprunx < currmap.people [loadmaprunz].fnotifnum; loadmaprunx++)
								{
									fread(&currmap.people [loadmaprunz].fnotif[loadmaprunx],4,1,loadmapf);
								}
		
						}
					}
			}
	}
				if(dbug)
				{
					wprintw(stdscr, "Map read finished.\n");
					wprintw(stdscr, "Map was compiled with map maker version ");
					wprintw(stdscr, "%d.",currmap.vernum);
					wprintw(stdscr, "%d\n",currmap.vernum2);
					wprintw(stdscr, "The fixed x and y values are: %d,%d.\n",currmap.fixedx,currmap.fixedy);
				};
				fread(&mapendtest,1,1,loadmapf);
				fclose(loadmapf);
				scoord = 0;
				if(mapendtest != ENDINGBYTE)
				{
					currmap.isloaded = 0;
					return 1;
				}
				if (currmap.startmaptf == TRUE)
				{
					if(scoord == 1)
						self.x = currmap.startx;
					if(scoord == 1)
						self.y = currmap.starty;
				}
				return 0;
				}
	};
