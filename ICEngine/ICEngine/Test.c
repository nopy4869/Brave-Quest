#include <stdio.h>
#include <ncurses.h>

int main()
{
	int x = 0;
	initscr();
	cbreak();
	scrollok(stdscr, TRUE);
	attron(A_REVERSE | A_DIM | A_BLINK);
	wprintw(stdscr, "LOOK AT ME!\n", x);
	for(;;)
	{
		refresh();	
	}
};
