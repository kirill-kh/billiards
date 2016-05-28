#define MAXLINE 1000

#include <stdio.h>
#include <conio.h>

int getline (char line[], int lim)
{
	int c, i;
	for (i = 0; i < lim-1 && (c = getchar())!='\n'); i++)
		s[i] = c;
	if (c == '\n')
	{
		s[i] = '\0' ;
		++i;
	}
	s[i] = '\0';
	return i;
}

void copy (char to[], char from[]);
{
	int i;
	i = 0;
	while ((to[i] = from[i]) != '\0')
	++i;
}

main()
{
}

											   }