// Bqmc.c
//
//I got tired of not being able to do jack shit with my buggy-ass map making tool,
//so I made a converter ^.^ it strips out line breaks automagically!!!
//

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>
#include <time.h>

#define TRUE 1
#define FALSE 0
#define VERSION '\x02'
#define VERSION2 '\x00'
#define LINUX 1

#ifdef LINUX
	time_t temploctim;
#endif

char vernum = VERSION;
char vernum2 = VERSION2;
char sep = '\x00';
char end = '\xFF';

struct npc
	{
		char name [12];
		int x;
		int y;
		char scriptfile [13];
		char movetype;
		int fdepends [1024];
		int fnotif [1024];
		int fdependsnum;
		int fnotifnum;
	};

struct warp
	{
		int x [2];
		int y [2];
		char mapname [13];
	};

struct mapscript
	{
		char scriptfilename [13];
		int fdepends [1024];
		int fnotif [1024];
		int fdependsnum;
		int fnotifnum;
	};

int middleman();
int writemap ();
int readmap ();
int stufffilename();
int hang (int howlonghang);

int asdf;
char mapname [20];
struct warp mapwarps [1024];
char map [1024][1024];
char maperm [1024][1024];
extern char filename [13];
struct mapscript mscript [1024];
char startmaptf;

char fail;
char scripttf;
int script;
unsigned char scripts;
int npcnum;
unsigned char npcs;
int warpnum;
FILE *file;
FILE *file2;
int maprunx;
int mapruny;
int maprunz;
int cuentos;
int capture;
int mapx;
int mapy;
int startx;
int starty;
char enemytf;
int enemyent [2][10];
char npctf;
struct npc people [1024];
int xs;
int ys;

char ts[11];
char temp [13] = { 'T', 'E', 'M', 'P', 'O', '~', '0', '1', '.', 't', 'm', 'p', '\0'};
char las;

#include "Common functions.cpp"

int main(int argc, char* argv[])
{
	initscr();
	scrollok(stdscr, TRUE);
	stufffilename();
	wprintw(stdscr, "\n");
	if(middleman() != 0)
	{
		wprintw(stdscr, "Failed to open input or temp file!\n");
		refresh();
		hang(2);
		endwin();
		return 1;
	}
	if(readmap() != 0)
	{
		wprintw(stdscr, "Failed to open temporary map file!\n");
		refresh();
		hang(2);
		endwin();
		return 1;
	}
	stufffilename();
	wprintw(stdscr, "\n");
	if(writemap() != 0)
	{
		wprintw(stdscr, "Failed to write map file!\n");
		refresh();
		hang(2);
		endwin();
		return 1;
	}
	wprintw(stdscr, "Happily finished!\n");
	refresh();
	hang(2);
	endwin();
	return 0;
}

int middleman()
{
	int x;
	file = fopen(filename, "r");
	if(file == FALSE)
		return 1;
	file2 = fopen(temp, "w");
	if(file == FALSE)
		return 1;
	for(;x != 0;)
	{
		x = fread(&las,1,1,file);
		if(las != 10)
			fwrite(&las,1,1,file2);
	}
	fclose(file);
	fclose(file2);
	return 0;
}

int readmap ()
{
	int x;
	file = fopen(temp,"r");
	if(file == FALSE)
		return 1;
		
	for(x = 0; x < 10; x++)
	{
		fread(&ts[x],1,1,file);
	}
	scripts = intread(ts);
	
	fread(&enemytf,1,1,file);
	if(enemytf == 'y')
		enemytf = TRUE;
	
	fread(&npctf,1,1,file);
	if(npctf == 'y')
		npctf = TRUE;
	
	if (npctf == TRUE)
	{
		for(x = 0; x < 10; x++)
		{
			fread(&ts[x],1,1,file);
		}
		npcnum = intread(ts);
	}
	
	fread(&startmaptf,1,1,file);
	if(startmaptf == 'y')
		startmaptf = TRUE;
	
	if (startmaptf == TRUE)
	{
		for(x = 0; x < 10; x++)
		{
			fread(&ts[x],1,1,file);
		}
		startx = intread(ts);
		for(x = 0; x < 10; x++)
		{
			fread(&ts[x],1,1,file);
		}
		starty = intread(ts);
	}
	
	for(x = 0; x < 10; x++)
	{
		fread(&ts[x],1,1,file);
	}
	warpnum = intread(ts);
	
	for (maprunx = 0; maprunx < 20; maprunx++)
	{
		fread(&mapname [maprunx],1,1,file);
	}
	
	for(x = 0; x < 10; x++)
	{
		fread(&ts[x],1,1,file);
	}
	mapx = intread(ts);
	
	for(x = 0; x < 10; x++)
	{
		fread(&ts[x],1,1,file);
	}
	mapy = intread(ts);
	
	for (mapruny = 0; mapruny < mapy; mapruny++)
	{
		for (maprunx = 0; maprunx < mapx; maprunx++)
			{
				fread(&map [maprunx][mapruny],1,1,file);
			}
	}
	for (mapruny = 0; mapruny < mapy; mapruny++)
	{
		for (maprunx = 0; maprunx < mapx; maprunx++)
			{
				fread(&maperm [maprunx][mapruny],1,1,file);
			}
	}
	for (mapruny = 0; mapruny < warpnum; mapruny++)
		{
			for (maprunx = 0; maprunx < 12; maprunx++)
				{
					fread(&mapwarps [mapruny].mapname [maprunx],1,1,file);
				}
				mapwarps[mapruny].mapname[12] = '\0';
				
				for(x = 0; x < 10; x++)
				{
					fread(&ts[x],1,1,file);
				}
				mapwarps [mapruny].x [0] = intread(ts);
				
				for(x = 0; x < 10; x++)
				{
					fread(&ts[x],1,1,file);
				}
				mapwarps [mapruny].y [0] = intread(ts);
				
				for(x = 0; x < 10; x++)
				{
					fread(&ts[x],1,1,file);
				}
				mapwarps [mapruny].x [1] = intread(ts);
				
				for(x = 0; x < 10; x++)
				{
					fread(&ts[x],1,1,file);
				}
				mapwarps [mapruny].y [1] = intread(ts);
		}
	for (mapruny = 0; mapruny < scripts; mapruny++)
	{
		for (maprunx = 0; maprunx < 12; maprunx++)
		{
			fread(&mscript [mapruny].scriptfilename [maprunx],1,1,file);
		}
		mscript [mapruny].scriptfilename [12] = '\0';
		
		for(x = 0; x < 10; x++)
		{
			fread(&ts[x],1,1,file);
		}
		mscript [mapruny].fdependsnum = intread(ts);
		
		for(x = 0; x < 10; x++)
		{
			fread(&ts[x],1,1,file);
		}
		mscript [mapruny].fnotifnum = intread(ts);

		for (maprunx = 0; maprunx < mscript [mapruny].fdependsnum; maprunx++)
		{
			for(x = 0; x < 10; x++)
			{
				fread(&ts[x],1,1,file);
			}
			mscript [mapruny].fdepends[maprunx] = intread(ts);
		}

		for (maprunx = 0; maprunx < mscript [mapruny].fnotifnum; maprunx++)
		{
			for(x = 0; x < 10; x++)
			{
				fread(&ts[x],1,1,file);
			}
			mscript [mapruny].fnotif[maprunx] = intread(ts);
		}

	}
	fread(&enemytf,1,1,file);
	if(enemytf == 'y')
		enemytf = TRUE;
	if (enemytf == TRUE)
		{
			for (mapruny = 0; mapruny < 10; mapruny++)
			{
				for(x = 0; x < 10; x++)
				{
					fread(&ts[x],1,1,file);
				}
				enemyent [0][mapruny] = intread(ts);
				
				for(x = 0; x < 10; x++)
				{
					fread(&ts[x],1,1,file);
				}
				enemyent [1][mapruny] = intread(ts);
			}
		}
	if (npctf == TRUE)
		{
		for (maprunz = 0;maprunz < npcnum; maprunz++)
			{
				fread(&people [maprunz].name [0],1,1,file);
				fread(&people [maprunz].name [1],1,1,file);
				fread(&people [maprunz].name [2],1,1,file);
				fread(&people [maprunz].name [3],1,1,file);
				fread(&people [maprunz].name [4],1,1,file);
				fread(&people [maprunz].name [5],1,1,file);
				fread(&people [maprunz].name [6],1,1,file);
				fread(&people [maprunz].name [7],1,1,file);
				fread(&people [maprunz].name [8],1,1,file);
				fread(&people [maprunz].name [9],1,1,file);
				fread(&people [maprunz].name [10],1,1,file);
				fread(&people [maprunz].name [11],1,1,file);
					for (maprunx = 0; maprunx < 13; maprunx++)
						{
							fread(&people [maprunz].scriptfile [maprunx],1,1,file);
						}
				for(x = 0; x < 10; x++)
				{
					fread(&ts[x],1,1,file);
				}
				people [maprunz].x = intread(ts);
				
				for(x = 0; x < 10; x++)
				{
					fread(&ts[x],1,1,file);
				}
				people [maprunz].y = intread(ts);
				
				for(x = 0; x < 10; x++)
				{
					fread(&ts[x],1,1,file);
				}
				people [maprunz].movetype = intread(ts);
				
				for(x = 0; x < 10; x++)
				{
					fread(&ts[x],1,1,file);
				}
				people [maprunz].fdependsnum = intread(ts);
				
				for(x = 0; x < 10; x++)
				{
					fread(&ts[x],1,1,file);
				}
				people [maprunz].fnotifnum = intread(ts);
				
					for (maprunx = 0; maprunx < people [maprunz].fdependsnum; maprunx++)
					{
						for(x = 0; x < 10; x++)
						{
							fread(&ts[x],1,1,file);
						}
						people [maprunz].fdepends[maprunx] = intread(ts);
						
					}
					for (maprunx = 0; maprunx < people [maprunz].fnotifnum; maprunx++)
					{
						for(x = 0; x < 10; x++)
						{
							fread(&ts[x],1,1,file);
						}
						people [maprunz].fnotif[maprunx] = intread(ts);
						
					}
			}
		}
	fclose(file);
	return 0;
}

int writemap ()
{
	char x;
	file = fopen(filename,"r");
	if(file != FALSE)
	{
		wprintw(stdscr, "File already exists!\nContinue? (y/n)\n");
		refresh();
		x = bie();
		fclose(file);
		file = FALSE;
		if((x != 'y') && (x != 'Y'))
		{
			wprintw(stdscr, "Y not typed");
			return 1;
		}
	}
	if(file == FALSE)
	{
		file = fopen(filename,"wb+");
		if(file == FALSE)
		{
			wprintw(stdscr, "Unable to open file wb+\n");
			return 1;
		}
		fwrite(&vernum,1,1,file);
		//fwrite(&sep,1,1,file);
		fwrite(&vernum2,1,1,file);
		//fwrite(&sep,1,1,file);
		fwrite(&scripts,1,1,file);
		//fwrite(&sep,1,1,file);
		fwrite(&enemytf,1,1,file);
		//fwrite(&sep,1,1,file);
		fwrite(&npctf,1,1,file);
		//fwrite(&sep,1,1,file);
		if (npctf == TRUE)
		{
			fwrite(&npcnum,4,1,file);
			//fwrite(&sep,1,1,file);
		}
		fwrite(&startmaptf,1,1,file);
		//fwrite(&sep,1,1,file);
		if (startmaptf == TRUE)
		{
			fwrite(&startx,4,1,file);
			//fwrite(&sep,1,1,file);
			fwrite(&starty,4,1,file);
			//fwrite(&sep,1,1,file);
		}
		fwrite(&warpnum,4,1,file);
		//fwrite(&sep,1,1,file);
		for (maprunx = 0; maprunx < 20; maprunx++)
		{
			fwrite(&mapname [maprunx],1,1,file);
		}
		//fwrite(&sep,1,1,file);
		fwrite(&mapx,4,1,file);
		//fwrite(&sep,1,1,file);
		fwrite(&mapy,4,1,file);
		//fwrite(&sep,1,1,file);
		for (mapruny = 0; mapruny < mapy; mapruny++)
		{
			for (maprunx = 0; maprunx < mapx; maprunx++)
				{
					fwrite(&map [maprunx][mapruny],1,1,file);
				}
		}
		//fwrite(&sep,1,1,file);
		for (mapruny = 0; mapruny < mapy; mapruny++)
		{
			for (maprunx = 0; maprunx < mapx; maprunx++)
				{
					fwrite(&maperm [maprunx][mapruny],1,1,file);
				}
		}
		for (mapruny = 0; mapruny < warpnum; mapruny++)
			{
				for (maprunx = 0; maprunx < 13; maprunx++)
					{
						fwrite(&mapwarps [mapruny].mapname [maprunx],1,1,file);
					}
					fwrite(&mapwarps [mapruny].x [0],4,1,file);
					//fwrite(&sep,1,1,file);
					fwrite(&mapwarps [mapruny].y [0],4,1,file);
					//fwrite(&sep,1,1,file);
					fwrite(&mapwarps [mapruny].x [1],4,1,file);
					//fwrite(&sep,1,1,file);
					fwrite(&mapwarps [mapruny].y [1],4,1,file);
					//fwrite(&sep,1,1,file);
			}
		//fwrite(&sep,1,1,file);
		for (mapruny = 0; mapruny < scripts; mapruny++)
		{
			for (maprunx = 0; maprunx < 13; maprunx++)
			{
				fwrite(&mscript [mapruny].scriptfilename [maprunx],1,1,file);
			}
			//fwrite(&sep,1,1,file);
			fwrite(&mscript [mapruny].fdependsnum,4,1,file);
			fwrite(&mscript [mapruny].fnotifnum,4,1,file);
			for (maprunx = 0; maprunx < mscript [mapruny].fdependsnum; maprunx++)
			{
				fwrite(&mscript [mapruny].fdepends[maprunx],4,1,file);
			}
			for (maprunx = 0; maprunx < mscript [mapruny].fnotifnum; maprunx++)
			{
				fwrite(&mscript [mapruny].fnotif[maprunx],4,1,file);
			}
		}
		fwrite(&enemytf,1,1,file);
		//fwrite(&sep,1,1,file);
		if (enemytf == TRUE)
			{
				for (mapruny = 0; mapruny < 10; mapruny++)
				{
					fwrite(&enemyent [0][mapruny],4,1,file);
					//fwrite(&sep,1,1,file);
					fwrite(&enemyent [1][mapruny],4,1,file);
					//fwrite(&sep,1,1,file);
				}
			}
		if (npctf == TRUE)
			{
			for (maprunz = 0;maprunz < npcnum; maprunz++)
				{
					fwrite(&people [maprunz].name [0],1,1,file);
					fwrite(&people [maprunz].name [1],1,1,file);
					fwrite(&people [maprunz].name [2],1,1,file);
					fwrite(&people [maprunz].name [3],1,1,file);
					fwrite(&people [maprunz].name [4],1,1,file);
					fwrite(&people [maprunz].name [5],1,1,file);
					fwrite(&people [maprunz].name [6],1,1,file);
					fwrite(&people [maprunz].name [7],1,1,file);
					fwrite(&people [maprunz].name [8],1,1,file);
					fwrite(&people [maprunz].name [9],1,1,file);
					fwrite(&people [maprunz].name [10],1,1,file);
					fwrite(&people [maprunz].name [11],1,1,file);
						for (maprunx = 0; maprunx < 13; maprunx++)
							{
								fwrite(&people [maprunz].scriptfile [maprunx],1,1,file);
							}
					fwrite(&people [maprunz].x,4,1,file);
					fwrite(&people [maprunz].y,4,1,file);
					fwrite(&people [maprunz].movetype,1,1,file);
					fwrite(&people [maprunz].fdependsnum,4,1,file);
					fwrite(&people [maprunz].fnotifnum,4,1,file);
						for (maprunx = 0; maprunx < people [maprunz].fdependsnum; maprunx++)
						{
							fwrite(&people [maprunz].fdepends[maprunx],4,1,file);
						}
					fwrite(&people [maprunz].fnotifnum,4,1,file);
						for (maprunx = 0; maprunx < people [maprunz].fnotifnum; maprunx++)
						{
							fwrite(&people [maprunz].fnotif[maprunx],4,1,file);
						}

				}
			}
		fwrite(&end,1,1,file);
		fclose(file);
		return 0;
	}
	return 0;
}

int hang (int howlonghang)
{
	int lol;
	int templocaltime;
	#ifndef LINUX
		templocaltime = _time32(NULL);
	#endif
	#ifdef LINUX
		templocaltime = time(&temploctim);
	#endif
	lol = templocaltime + howlonghang;
	for(;;)
	{
		#ifndef LINUX
			templocaltime = _time32(NULL);
		#endif
		#ifdef LINUX
			templocaltime = time(&temploctim);
		#endif
		if(lol == templocaltime)
			break;
	}
	return 0;
};
