#define IN 1
#define OUT 0

#include <stdio.h>;
#include <conio.h>;

main()
{
	int num, state;
	char c;

	num = 0;
	state = OUT;
	clrscr();
	c = getchar();
	while ((c = getchar()) != '\n')
	{
		if (c == ' ' || c == '\t')
			state = OUT;
		else if (state == OUT)
		{
			state = IN;
			++num;
		}
	}
	printf("%d", num);
	getch();
	return 0;
}
