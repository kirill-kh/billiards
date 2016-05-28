#pragma hdrstop
#pragma argsused

#include <tchar.h>
/*turbo c*/
#include <stdio.h>
#include <conio.h>
main()
{
	int low, high, step;
	float c, f;
	clrscr();
	low = 0;
	high = 150;
	step = 10;
	for (c = low; c < high; c = c + step)
	{
		f = (9.0/5.0)*c + 32.0;
		printf("%6.1f %6.1f \n", f, c);
	}
	getch();
	return 0;
}