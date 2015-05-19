#ifndef LINUX
	#include <stdio.h>
	#include <stdlib.h>
	#include <time.h>
	#include <ctype.h>
	#include <ncurses.h>
#endif

#define TRUE 1
#define FALSE 0

FILE *savefile, *savefilech;

extern char input [5];  //change if necessary

int saveencrypt();
int savedecrypt();
int writesave();
int readsave();
int debug();

int silentsave()
{
	savefile =fopen("autosave.isg", "wb");
	if(savefile == 0)
		return 1;
	if(saveencrypt() == 1)
	{
		fclose(savefile);
		return 1;
	}
	return 0;
}

int savegame()
{
	int done;
	int done2;
	int filenumber;
	done = 0;
	done2 = 0;
	wprintw(stdscr, "\aWould you like to save the game?\n");
	wprintw(stdscr, "Type \"y\" or \"n\".\n");
	input[1] = getch();
	wprintw(stdscr, "\n");
	input[1] = tolower(input[1]);
	switch(input[1])
		{
			case 'n':
				wprintw(stdscr, "OK.\n");
				return(2);
				break;
			case 'y':
				while(done == FALSE)
					{
						wprintw(stdscr, "Ok, which file would you like to save to?\n1, 2, or 3?\n");
						input[2] = getch();
						wprintw(stdscr, "\n");
						switch(input[2])
						{
							case '1':
								savefilech =fopen("1.isg", "r");
								done = TRUE;
								filenumber = 1;
								break;
							case '2':
								savefilech =fopen("2.isg", "r");
								done = TRUE;
								filenumber = 2;
								break;
							case '3':
								savefilech =fopen("3.isg", "r");
								done = TRUE;
								filenumber = 3;
								break;
							default:
								wprintw(stdscr, "Please type your file number,/n1, 2, or 3.");
								break;
						}
						if (savefilech == 0)
						{
							done = FALSE;
							wprintw(stdscr, "File not found. Would you like to make a new one?\n");
							wprintw(stdscr, "Type \"y\" or \"n\".\n");
							input[3] = getch();
							wprintw(stdscr, "\n");
							input[3] = tolower(input[3]);
							if (input [3] == 'n')
								return 1;
							if (filenumber == 1)
								savefilech =fopen("1.isg", "wb+");
							if (filenumber == 2)
								savefilech =fopen("2.isg", "wb+");
							if (filenumber == 3)
								savefilech =fopen("3.isg", "wb+");
							fclose (savefilech);
							if (filenumber == 1)
								savefilech =fopen("1.isg", "r");
							if (filenumber == 2)
								savefilech =fopen("2.isg", "r");
							if (filenumber == 3)
								savefilech =fopen("3.isg", "r");
							done = TRUE;
						}
						if (savefilech != 0)
						{
							wprintw(stdscr, "The selected file already exists. Would you\nlike to overwrite it?\n");
							while (done2 != TRUE)
							{
								input[3] = getch();
								wprintw(stdscr, "\n");
								input [3] = tolower(input[3]);
								if (input [3] == 'n')
									return 1;
								if (input [3] == 'y')
									done2 = TRUE;
								if ((input [3] != 'n') && (input [3] != 'y'))
									wprintw(stdscr, "Please type \"y\" or\"n\".");
							}
						}
					}
				fclose (savefilech);
				if (filenumber == 1)
					savefile =fopen("1.isg", "wb");
				if (filenumber == 2)
					savefile =fopen("2.isg", "wb");
				if (filenumber == 3)
					savefile =fopen("3.isg", "wb");
		}
	if(savefile == 0)
		return 1;
	if(saveencrypt() == 1)
	{
		fclose(savefile);
		return 1;
	}
	if(dbug)
	{
		wprintw(stdscr, "Start the dbug prompt?\ny/n\n");
		if(bie() == 'n')
			debug();
	}
	fclose(savefile);
	return 0;
};

int loadsave()
{
	int done;
	int filenumber;
	done = 0;
	wprintw(stdscr, "\aWould you like to Load a game?\n");
	wprintw(stdscr, "Type \"y\" or \"n\".\n");
	input[1] = getch();
	wprintw(stdscr, "\n");
	input[1] = tolower(input[1]);
	switch(input[1])
		{
			case 'n':
				wprintw(stdscr, "OK.\n");
				return(2);
				break;
			case 'y':
				while(done == FALSE)
					{
						wprintw(stdscr, "Ok, which file would you like to load?\n1, 2, or 3?\n");
						input[2] = getch();
						wprintw(stdscr, "\n");
						switch(input[2])
						{
							case '1':
								savefilech =fopen("1.isg", "r");
								done = TRUE;
								filenumber = 1;
								break;
							case '2':
								savefilech =fopen("2.isg", "r");
								done = TRUE;
								filenumber = 2;
								break;
							case '3':
								savefilech =fopen("3.isg", "r");
								done = TRUE;
								filenumber = 3;
								break;
							default:
								wprintw(stdscr, "Please type your file number,/n1, 2, or 3.");
								break;
						}
						if (savefilech == 0)
						{
							done = FALSE;
							return 1;
						}
					}
				fclose (savefilech);
				if (filenumber == 1)
					savefile =fopen("1.isg", "r");
				if (filenumber == 2)
					savefile =fopen("2.isg", "r");
				if (filenumber == 3)
					savefile =fopen("3.isg", "r");
		}
	if(savefile == 0)
		return 1;
	if(readsave() == 1)
	{
		fclose(savefile);
		wprintw(stdscr, "Failed to load the save file.\n");
		hang(3);
		return 1;
	}
	if(dbug)
	{
		wprintw(stdscr, "Start the dbug prompt?\ny/n\n");
		if(bie() == 'n')
			debug();
	}
	fclose(savefile);
	return 0;
};

int saveencrypt()
{
	char *pointer = currgame.characters[0].name;
	int sentryrunx;
	char tempchar = 0;
	char sentry[8];
	for(sentryrunx = 0; sentryrunx < 8; sentryrunx++)
	{
		sentry[sentryrunx] = 0;
	}
	
	for(sentryrunx = 37; sentryrunx < 1061; sentryrunx++)
	{
		tempchar -= (char)sentryrunx + currgame.gameflags[sentryrunx - 37][(sentryrunx + 37) % 1024];
	}
	
	sentry[0] = (self.gold + tempchar) % (1 + abs(self.face + 3));
	sentry[1] = (((char)self.x + (char)self.y) % (1 + abs(sentry[0])));
	sentry[3] = (self.partyids[0] + self.partyids[1] + self.partyids[2] + self.partyids[3]);
	for(sentryrunx = 37; sentryrunx < 1061; sentryrunx++)
	{
		sentry[2] -= (char)sentryrunx + self.inventory[sentryrunx - 37];
		sentry[4] += (char)sentryrunx - self.inventory[(sentryrunx + 37) % 1024];
	}
	for(sentryrunx = 15; sentryrunx < 2175; sentryrunx++)
	{
		sentry[5] -= (char)sentryrunx + *(pointer + (sentryrunx - 15));
		sentry[7] += (char)sentryrunx - *(pointer + ((sentryrunx + 15) % 2160));
	}
	for(sentryrunx = 221; sentryrunx < 242; sentryrunx++)
	{
		sentry[6] += (char)sentryrunx - currmap.mapname[(sentryrunx + 221) % 21];
	}
//	wprintw(stdscr, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", sentry[0], sentry[1], sentry[2], sentry[3], sentry[4], sentry[5], sentry[6], sentry[7]);
	return writesave(&sentry);
}

int savedecrypt(char readsentry[8])
{
	char *pointer = currgame.characters[0].name;
	int sentryrunx;
	char tempchar = 0;
	char sentry[8];
	for(sentryrunx = 0; sentryrunx < 8; sentryrunx++)
	{
		sentry[sentryrunx] = 0;
	}
	
	for(sentryrunx = 37; sentryrunx < 1061; sentryrunx++)
	{
		tempchar -= (char)sentryrunx + currgame.gameflags[sentryrunx - 37][(sentryrunx + 37) % 1024];
	}
	
	sentry[0] = (self.gold + tempchar) % (1 + abs(self.face + 3));
	sentry[1] = (((char)self.x + (char)self.y) % (1 + abs(sentry[0])));
	sentry[3] = (self.partyids[0] + self.partyids[1] + self.partyids[2] + self.partyids[3]);
	for(sentryrunx = 37; sentryrunx < 1061; sentryrunx++)
	{
		sentry[2] -= (char)sentryrunx + self.inventory[sentryrunx - 37];
		sentry[4] += (char)sentryrunx - self.inventory[(sentryrunx + 37) % 1024];
	}
	for(sentryrunx = 15; sentryrunx < 2175; sentryrunx++)
	{
		sentry[5] -= (char)sentryrunx + *(pointer + (sentryrunx - 15));
		sentry[7] += (char)sentryrunx - *(pointer + ((sentryrunx + 15) % 2160));
	}
	for(sentryrunx = 221; sentryrunx < 242; sentryrunx++)
	{
		sentry[6] += (char)sentryrunx - currmap.mapname[(sentryrunx + 221) % 21];
	}
	
//	wprintw(stdscr, "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n", sentry[0], sentry[1], sentry[2], sentry[3], sentry[4], sentry[5], sentry[6], sentry[7]);
	
	for(sentryrunx = 0; sentryrunx < 8; sentryrunx++)
	{
	
//			wprintw(stdscr, "Testing index number %d\nRead: %d\nCalculated: %d\n", sentryrunx, readsentry[sentryrunx], sentry[sentryrunx]);
//			bi();
		if(readsentry[sentryrunx] != sentry[sentryrunx])//<------------
		{
			return 1;
		}
	}
	return 0;
}

int writesave(char *checksum[])
{
	fwrite(currmap.mapname,21,1,savefile);
	fwrite(&self.x,4,1,savefile);
	fwrite(&self.y,4,1,savefile);
	fwrite(&self.step,4,1,savefile);
	fwrite(&self.face,1,1,savefile);
	fwrite(&self.gold,4,1,savefile);
	fwrite(self.partyids,1,4,savefile);
	fwrite(self.inventory,4,1024,savefile);
	fwrite(&self.config,26,1,savefile);
	fwrite(currgame.characters,135,16,savefile);
	fwrite(currgame.gameflags,1048576,1,savefile);
	fwrite(checksum,8,1,savefile);
	return 0;
}

int readsave()
{
	char checksum [8];
	fread(currmap.mapname,21,1,savefile);
	fread(&self.x,4,1,savefile);
	fread(&self.y,4,1,savefile);
	fread(&self.step,4,1,savefile);
	fread(&self.face,1,1,savefile);
	fread(&self.gold,4,1,savefile);
	fread(self.partyids,1,4,savefile);
	fread(self.inventory,4,1024,savefile);
	fread(&self.config,26,1,savefile);
	fread(currgame.characters,135,16,savefile);
	fread(currgame.gameflags,1048576,1,savefile);
	fread(&checksum,8,1,savefile);
	if(savedecrypt(checksum) == 1)
		return 1;
	return 0;
}

int clearsavemem()
{
	int csmx, csmy;
	for(csmx = 0; csmx < 21; csmx++)
	{
		currmap.mapname[csmx] = 0;
	}
	self.x = 0;
	self.y = 0;
	self.step = 0;
	self.face = 0;
	self.gold = 0;
	for(csmx = 0; csmx < 4; csmx++)
	{
		self.partyids[csmx] = 0;
	}
	for(csmx = 0; csmx < 1024; csmx++)
	{
		self.inventory[csmx] = 0;
	}
	for(csmx = 0; csmx < 1024; csmx++)
	{
		for(csmy = 0; csmy < 1024; csmy++)
		{
			currgame.gameflags[csmx][csmy] = 0;
		}
	}
	for(csmx = 0; csmx < 16; csmx++)
	{
		for(csmy = 0; csmy < 16; csmy++)
		{
			currgame.characters[csmx].name[csmy] = 0;
		}
		for(csmy = 0; csmy < 9; csmy++)
		{
			currgame.characters[csmx].classname[csmy] = 0;
		}
		currgame.characters[csmx].symbol = 0;
		currgame.characters[csmx].type = 0;
		currgame.characters[csmx].leveq = 0;
		for(csmy = 0; csmy < 4; csmy++)
		{
			currgame.characters[csmx].status[csmy] = 0;
		}
		currgame.characters[csmx].level = 0;
		currgame.characters[csmx].exp = 0;
		currgame.characters[csmx].health = 0;
		currgame.characters[csmx].currhealth = 0;
		currgame.characters[csmx].attack = 0;
		currgame.characters[csmx].defence = 0;
		currgame.characters[csmx].wisdom = 0;
		currgame.characters[csmx].resistance = 0;
		currgame.characters[csmx].speed = 0;
		currgame.characters[csmx].luck = 0;
		for(csmy = 0; csmy < 4; csmy++)
		{
			currgame.characters[csmx].item[csmy] = 0;
		}
		for(csmy = 0; csmy < 32; csmy++)
		{
			currgame.characters[csmx].spells[csmy] = 0;
		}
	}
	return 0;
}

int silentload(char slot) //0 for slot 1, 1 for slot 2, 2 for slot 3, 3 for autosave
{
	switch(slot)
	{
		case 0:
			savefile =fopen("1.isg", "wb");
			break;
		case 1:
			savefile =fopen("2.isg", "wb");
			break;
		case 2:
			savefile =fopen("3.isg", "wb");
			break;
		case 3:
			savefile =fopen("autosave.isg", "wb");
			break;
	}
	if(savefile == 0)
		return 1;
	if(readsave() == 1)
	{
		fclose(savefile);
		return 1;
	}
	return 0;
}
