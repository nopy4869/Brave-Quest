char filename [13];
extern struct scriptstuff currlinebuff;
char tempstring[20];

#define COMMON_FUNCTIONS_MAJOR_VERSION '0x01'
#define COMMON_FUNCTIONS_MINOR_VERSION '0x00'

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

float floimp()
{
	int count;
	float result;
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
	result = strtof(tempstring, &first);
	return result;
};

int floatpacker(float f)
{
	union int_to_float {
		float f;
		int i;
	} itf;
	itf.f = f;
	return itf.i;
}

float intpacker(int i)
{
	union int_to_float {
		float f;
		int i;
	} itf;
	itf.i = i;
	return itf.f;
}
