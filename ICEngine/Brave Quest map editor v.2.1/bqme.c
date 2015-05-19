// Brave Quest map editor v.2.0.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define VERSION '\x02'
#define VERSION2 '\x00'

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

int writemap ();
int stufffilename();

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

#include "Common functions.cpp"

int main(int argc, char* argv[])
{
	initscr();
	scrollok(stdscr, TRUE);
	wprintw(stdscr, "Brave Quest Map editing tool ver. %d.%d\nCopyright 2012 Mad Science Inc.\nPlease do not redistrubute.\n",vernum,vernum2);
	stufffilename();
	wprintw(stdscr, "\nPlease type your map's name. Fill all unused blanks with spaces.\nDO NOT HIT ENTER!!!!!\n");
	for (maprunx = 0; maprunx < 20; maprunx++)
	{
		mapname [maprunx] = bie();
	}
	wprintw(stdscr, "\nPlease type the x of your map.\n");
	mapx = intimp();
	wprintw(stdscr, "\nPlease type the y of your map.\n");
	mapy = intimp();
	wprintw(stdscr, "\nPlease type your map.\nDO NOT HIT ENTER!!!!!\n");
	for (mapruny = 0; mapruny < mapy; mapruny++)
	{
		for (maprunx = 0; maprunx < mapx; maprunx++)
			{
				map [maprunx][mapruny] = sep;
			}
	}
	for (mapruny = 0; mapruny < mapy; mapruny++)
	{
		for (maprunx = 0; maprunx < mapx; maprunx++)
			{
				map [maprunx][mapruny] = bie();
			}
		wprintw(stdscr, "\n");
	}
	wprintw(stdscr, "\nPlease type your map's movement permissions.\nDO NOT HIT ENTER!!!!!\n");
	for (mapruny = 0; mapruny < mapy; mapruny++)
	{
		for (maprunx = 0; maprunx < mapx; maprunx++)
			{
				maperm [maprunx][mapruny] = sep;
			}
	}
	for (mapruny = 0; mapruny < mapy; mapruny++)
	{
		for (maprunx = 0; maprunx < mapx; maprunx++)
			{
				maperm [maprunx][mapruny] = bie();
			}
		wprintw(stdscr, "\n");
	}
	wprintw(stdscr, "\nIs this map the start map?Y\\N\n");
	startmaptf = bie();
	startmaptf = tolower(startmaptf);
	if (startmaptf == 'y')
	{
		startmaptf = TRUE;
		wprintw(stdscr, "\nPlease type the x of the starting point in your map.\n");
		startx = intimp();
		wprintw(stdscr, "\nPlease type the y of the starting point in your map.\n");
		starty = intimp();
	}
	else
		startmaptf = FALSE;
	wprintw(stdscr, "Please type the number of map warps in your map.\n");
	warpnum = intimp();
	for (mapruny = 0; mapruny < warpnum; mapruny++)
			{
				for (maprunx = 0; maprunx < 13; maprunx++)
				{
					mapwarps [mapruny].mapname [maprunx] = sep;
				}
			}
		for (mapruny = 0; mapruny < warpnum; mapruny++)
			{
				wprintw(stdscr, "\nPlease type the map filename for warp number %d.\nDO NOT HIT \"?\" UNLESS YOU WANT TO END FILENAME INPUT!!!!!\nPressing \"?\" right now will automatically name the file\n\"a.imf\".\nDO NOT HIT ENTER!!!!!\n",mapruny);
				for (maprunx = 0; maprunx < 13; maprunx++)
					{
						mapwarps [mapruny].mapname [maprunx] = bie();		
						if (maprunx == 8)
						{
							mapwarps [mapruny].mapname [8] = '.';
							mapwarps [mapruny].mapname [9] = 'i';
							mapwarps [mapruny].mapname [10] = 'm';
							mapwarps [mapruny].mapname [11] = 'f';
							mapwarps [mapruny].mapname [12] = sep;
							maprunx = 13;
						}
						else
						{
							if (mapwarps [mapruny].mapname [maprunx] == '?')
							{
								asdf = maprunx;
								mapwarps [mapruny].mapname [asdf] = '.';
								asdf = asdf + 1;
								mapwarps [mapruny].mapname [asdf] = 'i';
								asdf = asdf + 1;
								mapwarps [mapruny].mapname [asdf] = 'm';
								asdf = asdf + 1;
								mapwarps [mapruny].mapname [asdf] = 'f';
								asdf = asdf + 1;
								mapwarps [mapruny].mapname [asdf] = sep;
								maprunx = 13;
							}
						}
					}
					wprintw(stdscr, "\nPlease type the \"x\" of warp number %d in your map.\n",mapruny);
					capture = intimp();
					mapwarps [mapruny].x[0] = capture;
					wprintw(stdscr, "\nPlease type the \"y\" of warp number %d in your map.\n",mapruny);
					capture = intimp();
					mapwarps [mapruny].y[0] = capture;
					wprintw(stdscr, "\nPlease type the \"x\" of warp number %d in the other map.\n",mapruny);
					capture = intimp();
					mapwarps [mapruny].x[1] = capture;
					wprintw(stdscr, "\nPlease type the \"y\" of warp number %d in the other map.\n",mapruny);
					capture = intimp();
					mapwarps [mapruny].y[1] = capture;
			}
	for (mapruny = 0; mapruny < scripts; mapruny++)
	{
		for (maprunx = 0; maprunx < 13; maprunx++)
		{
			mscript [mapruny].scriptfilename [maprunx] = sep;
		}
	}
	wprintw(stdscr, "\nPlease type the number of map scripts in your map.\n");
	script = intimp();
	scripts = script;
	for (mapruny = 0; mapruny < scripts; mapruny++)
	{
		wprintw(stdscr, "Please type the filename of script number %d.\nDO NOT HIT \"?\" UNLESS YOU WANT TO END FILENAME INPUT!!!!!\nPressing \"?\" right now will automatically name the file\n\".isf\".\nDO NOT HIT ENTER!!!!!",mapruny);
		for (maprunx = 0; maprunx < 13; maprunx++)
			{
				mscript [mapruny].scriptfilename [maprunx] = bie();
				if (maprunx == 8)
				{
					mscript [mapruny].scriptfilename [8] = '.';
					mscript [mapruny].scriptfilename [9] = 'i';
					mscript [mapruny].scriptfilename [10] = 's';
					mscript [mapruny].scriptfilename [11] = 'f';
					mscript [mapruny].scriptfilename [12] = sep;
					maprunx = 13;
				}
				else
				{
					if (mscript [mapruny].scriptfilename [maprunx] == '?')
					{
						asdf = maprunx - 1;
						maprunx = asdf;
						mscript [mapruny].scriptfilename [maprunx] = '.';
						asdf = maprunx + 1;
						maprunx = asdf;
						mscript [mapruny].scriptfilename [maprunx] = 'i';
						asdf = maprunx + 1;
						maprunx = asdf;
						mscript [mapruny].scriptfilename [maprunx] = 's';
						asdf = maprunx + 1;
						maprunx = asdf;
						mscript [mapruny].scriptfilename [maprunx] = 'f';
						asdf = maprunx + 1;
						maprunx = asdf;
						mscript [mapruny].scriptfilename [maprunx] = sep;
						maprunx = 13;
					}
				}
				wprintw(stdscr, "Please type the number of flags this script depends on.\n");
				capture = intimp();
				mscript [mapruny].fdependsnum = capture;
					for (maprunx = 0; maprunx < mscript [mapruny].fdependsnum; maprunx++)
							{
								wprintw(stdscr, "Please type this flag dependency.\n");
								mscript [mapruny].fdepends[maprunx] = intimp();
							}
				wprintw(stdscr, "Please type the number of flags this script depends on not being.\n");
				capture = intimp();
				mscript [mapruny].fnotifnum = capture;
					for (maprunx = 0; maprunx < mscript [mapruny].fnotifnum; maprunx++)
							{
								wprintw(stdscr, "Please type this flag anti-dependency.\n");
								mscript [mapruny].fnotif[maprunx] = intimp();
							}
			}
	}
	for (mapruny = 0; mapruny < 10; mapruny++)
				{
					enemyent [0][mapruny] = sep;
					enemyent [1][mapruny] = sep;
				}
	wprintw(stdscr, "\nDoes this map have enemies? If so, type \"y\" right now.\n");
	if (bie() == 'y')
		{
			enemytf = TRUE;
			wprintw(stdscr, "\nIf there are no more enemies, then type \"0\" for both fields.\n");
			for (mapruny = 0; mapruny < 10; mapruny++)
				{
					wprintw(stdscr, "Please type the enemy's ID.\n");
					capture = intimp();
					enemyent [0][mapruny] = capture;
					wprintw(stdscr, "Please type the enemy's frequency.\n");
					capture = intimp();
					enemyent [1][mapruny] = capture;
					cuentos = 10 - mapruny;
					wprintw(stdscr, "Only %d more enemys left.\n",&cuentos);
				}
		}
	wprintw(stdscr, "\nDoes your map have any npcs?\ny\\n\n");
	npcs = 0;
	npctf = bie();
	wprintw(stdscr, "\n");
	npctf = tolower(npctf);
	if (npctf == 'y')
		npctf = TRUE;
	if (npctf == TRUE)
		{
			wprintw(stdscr, "Please type the number of npc's in your map.\n");
			npcnum = intimp();
			npcs = npcnum;
			for (maprunz = 0;maprunz < npcnum; maprunz++)
				{
					wprintw(stdscr, "Please type this npc's name. Fill all unused characters with spaces.\nDO NOT HIT ENTER!!!!!\n");
					people [maprunz].name [0] = bie();
					people [maprunz].name [1] = bie();
					people [maprunz].name [2] = bie();
					people [maprunz].name [3] = bie();
					people [maprunz].name [4] = bie();
					people [maprunz].name [5] = bie();
					people [maprunz].name [6] = bie();
					people [maprunz].name [7] = bie();
					people [maprunz].name [8] = bie();
					people [maprunz].name [9] = bie();
					people [maprunz].name [10] = bie();
					people [maprunz].name [11] = bie();
					wprintw(stdscr, "\nPlease type this npc's script's file name.\nDO NOT HIT \"?\" UNLESS YOU WANT TO END FILENAME INPUT!!!!!\nPressing \"?\" right now will automatically name the file\n\".isf\".\nDO NOT HIT ENTER!!!!!\n");
					for (maprunx = 0; maprunx < 13; maprunx++)
						{				
							if (maprunx == 8)
							{
								people [maprunz].scriptfile [8] = '.';
								people [maprunz].scriptfile [9] = 'i';
								people [maprunz].scriptfile [10] = 's';
								people [maprunz].scriptfile [11] = 'f';
								people [maprunz].scriptfile [12] = sep;
								maprunx = 13;
							}
							else
							{
								people [maprunz].scriptfile [maprunx] = bie();
								if (people [maprunz].scriptfile [maprunx] == '?')
								{
									asdf = maprunx - 1;
									maprunx = asdf;
									people [maprunz].scriptfile [maprunx] = '.';
									asdf = maprunx + 1;
									maprunx = asdf;
									people [maprunz].scriptfile [maprunx] = 'i';
									asdf = maprunx + 1;
									maprunx = asdf;
									people [maprunz].scriptfile [maprunx] = 's';
									asdf = maprunx + 1;
									maprunx = asdf;
									people [maprunz].scriptfile [maprunx] = 'f';
									asdf = maprunx + 1;
									maprunx = asdf;
									people [maprunz].scriptfile [maprunx] = sep;
									maprunx = 13;
								}
							}
						}
			wprintw(stdscr, "\nPlease type the \"x\" of npc number %d in your map.\n",maprunz);
			xs = intimp();
			people [maprunz].x = xs;
			wprintw(stdscr, "\nPlease type the \"y\" of npc number %d in your map.\n",maprunz);
			ys = intimp();
			people [maprunz].y = ys;
			wprintw(stdscr, "Please type the npc's movetype of your map.\nDO NOT HIT ENTER!!!!!\n");
			people [maprunz].movetype = bie();
			wprintw(stdscr, "Please type the number of flags this npc depends on.\n");
			capture = intimp();
			people [maprunz].fdependsnum = capture;
				for (maprunx = 0; maprunx < people [maprunz].fdependsnum; maprunx++)
						{
							wprintw(stdscr, "Please type this flag dependency.\n");
							people [maprunz].fdepends[maprunx] = intimp();
						}
			wprintw(stdscr, "Please type the number of flags this npc depends on not being.\n");
			capture = intimp();
			people [maprunz].fnotifnum = capture;
				for (maprunx = 0; maprunx < people [maprunz].fnotifnum; maprunx++)
						{
							wprintw(stdscr, "Please type this flag anti-dependency.\n");
							people [maprunz].fnotif[maprunx] = intimp();
						}
			}
		}
	fail = writemap();
	for (;fail == TRUE;)												//Too funny to remove XD
	{
		int local;
		wprintw(stdscr, "\nFile didn't write.\nPlease rectify the error or close the program.\nPress \"y\" to rename the file.\n");
		local = bie();
		local = tolower(local);
		if (local == 'y')
		{
			wprintw(stdscr, "Please type your map's filename.\nDO NOT HIT ENTER!!!!!\nDO NOT HIT \"?\" UNLESS YOU WANT TO END FILENAME INPUT!!!!!\nPressing \"?\" right now will automatically name the file\n\"a.imf\".\n");	
			for(local = 0; local < 13; local++)
			{
				filename[local] = '\0';
			}
			stufffilename();
			fail = writemap();
		}
	}
	wprintw(stdscr, "\nMap sucessfully written.\nPress any key to exit.\n");
	bi();
	return 0;
}

int writemap ()
{
	file = fopen(filename,"r");
	if(file == FALSE)
	{
		file = fopen(filename,"wb");
		if(file == FALSE)
			return 1;
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
	else
	{
		fclose(file);
		return 1;
	}
}
