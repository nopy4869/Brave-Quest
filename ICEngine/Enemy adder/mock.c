#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ncurses.h>

#include "Common functions.cpp"

int eqnum;
int enemynum;
int characternum;
int workingeqnum;
int workingennum;
int workingchnum;
char workingeq [8];
char workingen [16];
char workingch [16];
char equatable [16] [8];
char enemytable [256] [16];
char charactable [16] [16];
extern char filename [13];
int frunx;
int fruny;
char trash;
int input [3];

int main()
{
	initscr();
	cbreak();
	nodelay(stdscr, FALSE);
	scrollok(stdscr, TRUE);
	wprintw(stdscr, "Go back? y/n\n");
	if (bie() == 'y')
		return 2;
	workingeqnum = eqnum;
	clear();
	refresh();
	wprintw(stdscr, "Type the numbers as required!\n_x^7+_x^6+_x^5+_x^4+_x^3+_x^2+_x^1+_\n");
	workingeq[0] = sintimp();
	workingeq[1] = sintimp();
	workingeq[2] = sintimp();
	workingeq[3] = sintimp();
	workingeq[4] = sintimp();
	workingeq[5] = sintimp();
	workingeq[6] = sintimp();
	workingeq[7] = sintimp();
	wprintw(stdscr, "Comitting to equation table now.\n");
	for(frunx = 0; frunx < 8; frunx++)
	{
		equatable [workingeqnum][frunx] = workingeq[frunx];
	}
	eqnum = workingeqnum + 1;
	input[1] = 0;
	for(frunx = 0; frunx < 8; frunx++)
	{
		workingeq[frunx] = 0;
	}
	wprintw(stdscr, "Done.\n");
	return 0;
};
