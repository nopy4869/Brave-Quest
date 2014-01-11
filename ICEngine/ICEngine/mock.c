#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

WINDOW *battlewin[7];

int oldlines, oldcols;

int main(int argc, char *argv[])
{
	initscr();
	cbreak();
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
	wprintw(stdscr, "%d, %d", COLS/2, LINES - 6);
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
	endwin();
	return 0;
};
