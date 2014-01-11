#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>

typedef unsigned short STAT;
struct player{
		char name[6];/*change if necessary*/
		stat level;
		stat health;
		stat attack;
		stat defense;
		stat mp;
		stat accuracy;
		stat evasiveness;
		unsigned long exp;
		};
struct you{
		int x;
		int y;
		int map;
		int step;
		char party;
		};

extern char game[12]
extern char input[2];  /*change if necessary*/
extern int done;

char input();

int display();

int savegame()
{
	printf("\aWould you like to save the game?\n");
	printf("Type \"y\" or \"n\".\n");
	input = getche();
	tolower(input);
	switch(input[0])
		{
			case 'n':
				printf("OK.\n");
				return(2);
				break;
			case 'y':
				printf ("Ok, which file would you like to save to?/n1, 2, or 3?");
				input[1] = getche();
				FILE *savefile, *savefilech;
				while(!done)
					{
						switch(input[1])
						{
							case '1':
								savefilech =fopen("1.isg");
								done = TRUE;
								break;
							case '2':
								savefilech =fopen("2.isg");
								done = TRUE;
								break;
							case '3':
								savefilech =fopen("3.isg");
								done = TRUE;
								break;
							default:
								printf("Please type your file number,/n1, 2, or 3.");
								break;
						}
					}
		}
};

int loadgame();
{
	FILE *gameinfo;
	gameinfo =fopen("gameinfo.txt")
	
};

int loadsavegame();

int main()
{
	int check;
	check = loadgame(game);
	if 
};

