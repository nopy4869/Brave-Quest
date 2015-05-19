#include <stdio.h>

int sortlist(char list[10][3], char listsorted[10][3])
{
	int x;
	int linenum = 0;
	char temp = 0;
	int listcount = 0;
	int listsortedcount = 0;
	char dn[10];
	int dncount = 0;
	char skip = 0;
	for(listsortedcount=0;listsortedcount<10;listsortedcount++)
	{
		for(listcount=0;listcount<10;listcount++)
		{
			for(x=0;x<dncount;x++)
			{
				if(listcount == dn[x])
				{
					skip = 1;
					break;
				}
			}
			if((list[listcount][2] >= temp)&&(skip != 1))
			{
				temp = list[listcount][2];
				linenum = listcount;
			}
			skip = 0;
		}
		listsorted[listsortedcount][0] = list[linenum][0];
		listsorted[listsortedcount][1] = list[linenum][1];
		listsorted[listsortedcount][2] = list[linenum][2];
		list[linenum][0] = 0;
		list[linenum][1] = 0;
		list[linenum][2] = 0;
		dn[dncount] = linenum;
		dncount++;
		temp = 0;
	}
//	int *i = 0;		//break here
//	putchar(*i);
	return 0;
}

int main()
{
	int x;
	char bl[10][3];
	char bls[10][3];
	for(x=0;x<10;x++)
	{
		bl[x][0] = x+1;
		bl[x][1] = 32;
		bl[x][2] = (x*5);
	}
	for(x=0;x<10;x++)
	{
		bls[x][0] = 0;
		bls[x][1] = 0;
		bls[x][2] = 0;
	}
	printf("Original list:\n");
	for(x=0;x<10;x++)
	{
		printf("%d %d %d\n", bl[x][0], bl[x][1], bl[x][2]);
	}
	sortlist(bl, bls);
	printf("\nFinal list:\n");
	for(x=0;x<10;x++)
	{
		printf("%d %d %d\n", bls[x][0], bls[x][1], bls[x][2]);
	}
	return 0;
}
