// Printcharset.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <conio.h>
#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	unsigned char q;
	for(q = 0; q < 255; q++)
		printf("%c",q);
	q = 255;
	printf("%c",q);
	q = 16;				//r
	printf("%c",q);
	q = 17;				//l
	printf("%c",q);
	q = 30;				//u
	printf("%c",q);
	q = 31;				//d
	printf("%c",q);
	_getch();
	return 0;
}
