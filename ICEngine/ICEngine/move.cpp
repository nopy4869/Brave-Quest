#ifndef LINUX
	#include <stdio.h>
	#include <stdlib.h>
	#include <ctype.h>
	#include <time.h>
	#include <ncurses.h>
	#include "unidefs.cpp"
	#include "gamelogictypedefs.cpp"
#endif

#include "tables.c"

extern char input [5];  //change if necessary
extern char dbug;

extern struct gameinfo currgame;
extern struct mapdata currmap;
extern struct npc menumove;
extern struct player self;
extern struct npc menumove;
extern struct scriptstuff currlinebuff;
extern char showmenu;
extern char usebit;
extern char justwarped;
extern int stuffdone;

int display ();
int moveme (char q);
int movemenu (char q);
int movenpc ();
int use (int x,int y);
int bi ();
int bie ();
int nbi ();
int nbie ();
int npcstep (int num, char dir);

char stepcount = 0;

char alreadybeendone;


int movenpc ()
{	
	stepcount %= 8;
	int moverunx;
	for(moverunx = 0; moverunx < currmap.npcnum; moverunx++){
		npcstep(moverunx, movepat[(currmap.people[moverunx].movetype * 8) + stepcount]);
	}
	return 0;
}

int npcstep (int num, char dir)
{
	if (dir == 1)
		{
			if(currmap.people[num].y > 0)
			{
				if(currmap.people[num].face == 'u')
				{
					if(currmap.maperm[currmap.people[num].x][currmap.people[num].y - 1] == '0')
						currmap.people[num].y = currmap.people[num].y - 1;
				}
				if(currmap.people[num].face != 'u')
					currmap.people[num].face = 'u';
			}
		}
	else if (dir == 3)
		{
			if(currmap.people[num].y <= currmap.fixedy)
			{
				if(currmap.people[num].face == 'd')
				{
					if(currmap.maperm[currmap.people[num].x][currmap.people[num].y + 1] == '0')
						currmap.people[num].y = currmap.people[num].y + 1;
				}
				if(currmap.people[num].face != 'd')
					currmap.people[num].face = 'd';
			}
		}
	else if (dir == 4)
		{
			if(currmap.people[num].x >= 0)
			{
				if(currmap.people[num].face == 'l')
				{
					if(currmap.maperm[currmap.people[num].x - 1][currmap.people[num].y] == '0')
						currmap.people[num].x = currmap.people[num].x - 1;
				}
				if(currmap.people[num].face != 'l')
					currmap.people[num].face = 'l';
			}
		}
	else if (dir == 2)
		{
			if(currmap.people[num].x <= currmap.fixedx)
			{
				if(currmap.people[num].face == 'r')
				{
					if(currmap.maperm[currmap.people[num].x + 1][currmap.people[num].y] == '0')
						currmap.people[num].x = currmap.people[num].x + 1;
				}
				if(currmap.people[num].face != 'r')
					currmap.people[num].face = 'r';
			}
		}
	stuffdone = 1;
	return 0;		//not done
};

int movemenu (char q)
{
	if (showmenu == FALSE)
		moveme(q);
	if (q == 'u')
		{
			menumove.y = menumove.y - 1;
			return 0;
		}
	if (q == 'd')
		{
			menumove.y = menumove.y + 1;
			return 0;
		}
	if (q == 'l')
		{
			menumove.y = menumove.y + 1;
			return 0;
		}
	if (q == 'r')
		{
			menumove.y = menumove.y - 1;
			return 0;
		}
	else
		{
			menumove.x = menumove.x + menumove.y;
			return 0;
		}
	stuffdone = 1;
};

int moveme (char q)
{
	char fail;
	if (showmenu == TRUE)
		movemenu(q);
	justwarped = FALSE;
	if (q == self.config.upbut)
		{
			if(self.y > 0)
			{
				if(self.face == 'u')
				{
					if(currmap.mapermol[self.x][self.y - 1] == '4'){
						scriptexec(self.x, self.y - 1);
						stuffdone = 1;
						return 0;
					}
					else if(currmap.maperm[self.x][self.y - 1] == '3')
						warpfollow(self.x, self.y - 1, 0);
					else if(currmap.maperm[self.x][self.y - 1] == '2')
					{
						self.y = self.y - 1;
						stuffdone = 1;
						display();
						scriptexec(self.x, self.y);
					}
					else if(currmap.maperm[self.x][self.y - 1] == '1')
						wprintw(stdscr, "ouch");
					else if(currmap.maperm[self.x][self.y - 1] == '0')
						self.y = self.y - 1;
				}
				if(self.face != 'u')
					self.face = 'u';
			}
		}
	else if (q == self.config.downbut)
		{
			if(self.y <= currmap.fixedy)
			{
				if(self.face == 'd')
				{
					if(currmap.mapermol[self.x][self.y + 1] == '4'){
						scriptexec(self.x, self.y + 1);
						stuffdone = 1;
						return 0;
					}
					else if(currmap.maperm[self.x][self.y + 1] == '3')
						warpfollow(self.x, self.y + 1, 0);
					else if(currmap.maperm[self.x][self.y + 1] == '2')
					{
						self.y = self.y + 1;
						stuffdone = 1;
						display();
						scriptexec(self.x, self.y);
					}
					else if(currmap.maperm[self.x][self.y + 1] == '1')
						wprintw(stdscr, "ouch");
					else if(currmap.maperm[self.x][self.y + 1] == '0')
						self.y = self.y + 1;
				}
				if(self.face != 'd')
					self.face = 'd';
			}
		}
	else if (q == self.config.leftbut)
		{
			if(self.x >= 0)
			{
				if(self.face == 'l')
				{
					if(currmap.mapermol[self.x - 1][self.y] == '4'){
						scriptexec(self.x - 1, self.y);
						stuffdone = 1;
						return 0;
					}
					else if(currmap.maperm[self.x - 1][self.y] == '3')
						warpfollow(self.x - 1, self.y, 0);
					else if(currmap.maperm[self.x - 1][self.y] == '2')
					{
						self.x = self.x - 1;
						stuffdone = 1;
						display();
						scriptexec(self.x, self.y);
					}
					else if(currmap.maperm[self.x - 1][self.y] == '1')
						wprintw(stdscr, "ouch");
					else if(currmap.maperm[self.x - 1][self.y] == '0')
						self.x = self.x - 1;
				}
				if(self.face != 'l')
					self.face = 'l';
			}
		}
	else if (q == self.config.rightbut)
		{
			if(self.x <= currmap.fixedx)
			{
				if(self.face == 'r')
				{
					if(currmap.mapermol[self.x + 1][self.y] == '4'){
						scriptexec(self.x + 1, self.y);
						stuffdone = 1;
						return 0;
					}
					else if(currmap.maperm[self.x + 1][self.y] == '3')
						warpfollow(self.x + 1, self.y, 0);
					else if(currmap.maperm[self.x + 1][self.y] == '2')
					{
						self.x = self.x + 1;
						stuffdone = 1;
						display();
						scriptexec(self.x, self.y);
					}
					else if(currmap.maperm[self.x + 1][self.y] == '1')
						wprintw(stdscr, "ouch");
					else if(currmap.maperm[self.x + 1][self.y] == '0')
						self.x = self.x + 1;
				}
				if(self.face != 'r')
					self.face = 'r';
			}
		}
	else if (q == self.config.menubut)
		{
			if(showmenu == 1)
			{showmenu = 0;}
			else if(showmenu == 0)
			{showmenu = 1;}
		}
	else if (q == self.config.usebut)
		{
			fail = use(self.x,self.y);
			if (fail == TRUE)
				{
					if (dbug == TRUE)
						wprintw(stdscr, "User's use failed.\n");
					return 3;
				}
		}
	else
	{
		if(alreadybeendone == 0)
		{
			alreadybeendone = 1;
			moveme(tolower(q));			//try try again
		}
		if(alreadybeendone == 1)
		{
			alreadybeendone = 0;
			if (dbug == TRUE)
				wprintw(stdscr, "Player didn't hit a valid key.\n");
			stuffdone = 1;
			return 3;
		}
	}
	stuffdone = 1;
	return 0;
};

int use (int x,int y)
{
	if(self.face == 'u')
	{
		if(currmap.mapermol[self.x][self.y - 1] == '4'){
			scriptexec(self.x, self.y - 1);
			stuffdone = 1;
			return 0;
		}
	}
	if(self.face == 'd')
	{
		if(currmap.mapermol[self.x][self.y + 1] == '4'){
			scriptexec(self.x, self.y + 1);
			stuffdone = 1;
			return 0;
		}
	}
	if(self.face == 'l')
	{
		if(currmap.mapermol[self.x - 1][self.y] == '4'){
			scriptexec(self.x - 1, self.y - 1);
			stuffdone = 1;
			return 0;
		}
	}
	if(self.face == 'r')
	{
		if(currmap.mapermol[self.x + 1][self.y] == '4'){
			scriptexec(self.x + 1, self.y);
			stuffdone = 1;
			return 0;
		}
	}
	return 1;
};

int gameloop ()
{
	char fail;
	int read;
	char axetra;
	for(;;)
	{
		read = nbi();
		if (read == ERR)
		{
			fail = movenpc(1);
			if (fail == TRUE)
				{
					if (dbug == TRUE)
						wprintw(stdscr, "npcs didn't move\n");
//					return 3;
				}
			fail = display();
			if (fail == TRUE)
				{
					if (dbug == TRUE)
						wprintw(stdscr, "display didn't work.\n");
//					return 3;
				}
		}
		if (read != ERR)
		{
			axetra = read;
			if(dbug)
			{
				if (axetra == 27)
				{
						printf ("Press the Escape key to return.\n");
						if (bie() == 27)
						{
								printf ("Returning...\n");
								return 2;
						}
				}
			}
			fail = moveme(axetra);
			if (fail == TRUE)
				{
					if (dbug == TRUE)
						wprintw(stdscr, "Player didn't move\n");
//					return 3;
				}
			if (fail == FALSE)
				{
					if (dbug == TRUE)
						wprintw(stdscr, "Player is now at %d,%d.\n", self.x, self.y);
				}
			fail = movenpc();
			if (fail == TRUE)
				{
					if (dbug == TRUE)
						wprintw(stdscr, "npcs didn't move\n");
//					return 3;
				}
			fail = display();
			if (fail == TRUE)
				{
					if (dbug == TRUE)
						wprintw(stdscr, "display didn't work.\n");
//					return 3;
				}
		}
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
	}
	}
};

int bi ()
{
	noecho();
	cbreak();
	nodelay(stdscr, FALSE);
	int read = getch();
	return read;
};

int bie ()
{
	echo();
	cbreak();
	nodelay(stdscr, FALSE);
	int read = getch();
	noecho();
	return read;
};

int nbi ()
{
	noecho();
	cbreak();
	nodelay(stdscr, TRUE);
	int read = getch();
	noecho();
	return read;
};

int nbie ()
{
	echo();
	cbreak();
	nodelay(stdscr, TRUE);
	int read = getch();
	return read;
};
int intimp()
{
	long int count;
	char *first;
	char tempstring[20];
	wprintw(stdscr, "Please type the second argument.\n");
	for(count = 0; count < 19; count++){
		tempstring[count] = bie();
		if((tempstring[count] == '\n') || (tempstring[count] == 10) || (tempstring[count] == 13) || (tempstring[count] == 27)){
			tempstring[count] = '\0';
			count = 19;
		}
	}
	tempstring[19] = '\0';
	count = strtol(tempstring, &first, 10);
	return count;
};

