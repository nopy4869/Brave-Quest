int main(int argc, char *argv[])
{
	initscr();
	cbreak();
	special[0] = derwin(stdscr, 1, 0, 0, 0);
	special[1] = derwin(stdscr, 1, 0, 1, 0);
	special[4] = derwin(stdscr, 1, 0, LINES - 3, 0);
	special[2] = derwin(stdscr, 1, 0, LINES - 2, 0);
	special[3] = derwin(stdscr, 1, 0, LINES - 1, 0);
	scrollok(stdscr, TRUE);
	scrollok(special[0], FALSE);
	scrollok(special[1], FALSE);
	scrollok(special[2], FALSE);
	scrollok(special[3], TRUE);
	scrollok(special[4], FALSE);
	loadgamedata();
	configuration();
	bi();
	for(;;)
	{
		justwarped = 0;
		lastframetime = 0;
		if(strcmp(dauthnum, "4869") == 0)
			debug();
		newgamemenu();
		gameloop();
	}
	return 0;
}
