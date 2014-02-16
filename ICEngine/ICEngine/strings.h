// This is a simple group of functions dealing with strings :D

int stringlength(char *string)
{
	int count;
	for(count = 0;;count++)
	{
		string += count;
		if(*string == '\0')
			break;
	}
	return count;
};

int copystring(char *stringone[], char *stringtwo[])
{
	int count;
	for(count = 0;;count++)
	{
		*stringtwo[count] = *stringone[count];
		if(*stringtwo[count] == '\0')
			break;
	};
	return count;
}

int compstring(char *stringone[], char *stringtwo[])
{
	int count;
	for(count = 0;;count++)
	{
		if(*stringtwo[count] != *stringone[count])
			return 1;
		if(*stringone == '\0')
			if(*stringtwo == '\0')
				break;
	};
	return 0;
}
