char filename [13];
extern struct scriptstuff currlinebuff;
char tempstring[20];

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


int stufffilename()
{
	int count;
	wprintw(stdscr, "Please type the file's filename.\n");
	for(count = 0; count < 12; count++){
		filename[count] = bie();
		if((filename[count] == '\n') || (filename[count] == 10) || (filename[count] == 13) || (filename[count] == 27)){
			filename[count] = '\0';
			count = 12;
		}
	}
	filename[12] = '\0';
	return 0;
};

int argone()
{
	int count;
	wprintw(stdscr, "Please type the first argument.\n");
	for(count = 0; count < 12; count++){
		currlinebuff.argstringone[count] = bie();
		if((currlinebuff.argstringone[count] == '\n') || (currlinebuff.argstringone[count] == 10) || (currlinebuff.argstringone[count] == 13) || (currlinebuff.argstringone[count] == 27)){
			currlinebuff.argstringone[count] = '\0';
			count = 13;
		}
	}
	currlinebuff.argstringone[12] = '\0';
	return 0;
};

int argtwo()
{
	int count;
	wprintw(stdscr, "Please type the second argument.\n");
	for(count = 0; count < 79; count++){
		currlinebuff.argstringtwo[count] = bie();
		if((currlinebuff.argstringtwo[count] == '\n') || (currlinebuff.argstringtwo[count] == 10) || (currlinebuff.argstringtwo[count] == 13) || (currlinebuff.argstringtwo[count] == 27)){
			currlinebuff.argstringtwo[count] = '\0';
			count = 79;
		}
	}
	currlinebuff.argstringtwo[79] = '\0';
	return 0;
};

int intimp()
{
	long int count;
	char *first;
//	wprintw(stdscr, "Please type the second argument.\n");
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
