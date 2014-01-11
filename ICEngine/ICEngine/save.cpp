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

int writesave();
int readsave();
int debug();

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
	if(writesave() == 1)
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
					savefile =fopen("3.isg", "r"); // NOT DONE!!!!!
		}
	if(savefile == 0)
		return 1;
	if(readsave() == 1)
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

int writesave()
{
	fwrite(&self.x,4,1,savefile);
	fwrite(&self.y,4,1,savefile);
	fwrite(&self.step,4,1,savefile);
	fwrite(&self.face,1,1,savefile);
	fwrite(&self.gold,4,1,savefile);
	fwrite(self.partyids,1,4,savefile);
	fwrite(&self.y,1,1,savefile);
	fwrite(&self.x,1,1,savefile);
	
	fwrite(&self.y,1,1,savefile);
	fwrite(&dbug,1,1,savefile);
	return 0;
}

int readsave()
{
	return 0;
}
