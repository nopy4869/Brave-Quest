// scan code finder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>
#include <ctype.h>

char input;

int _tmain(int argc, _TCHAR* argv[])
{
	printf("Type a key to find the scan code.\n");
	for(;;)
	{
		printf("Key:\n");
		input = _getche();
		printf("\nScan Code:\n%d\n",input);
		printf("Character:\n%c\n",input);
		printf("Tolower character:\n%c\n",tolower(input));
	}
	return 0;
}

