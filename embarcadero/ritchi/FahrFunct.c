#define low 0
#define high 150
#definr step 10

#include <stdio.h>
#include <conio.h>

float celsium ( float c)
{
	float f;
	f = (9.0/5.0)*c + 32.0;
	return f;
}

main()
{
	float c, f;
	clrscr();
	for (c = low; c < high; c = c + step)
	{
		printf("%6.1f %6.1f \n", celsium(c), c);
	}
	getch();
	return 0;
}
