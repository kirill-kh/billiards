#include <stdio.h>
#include <conio.h>

main()
{
	int c, i, nwhite, nother;
	int ndigit[10];

	clrscr();
	//�������������
	nwhite = nother = 0;
	for (i = 0; i < 10; i++) {
		ndigit[i] = 0;
	}
	//�������������

	//�������
	while ((c = getchar()) != '\n'){
		if ((c >= '0') && (c <= '9'))
			++ndigit[c - '0'];
		else
			if (c == ' ' || c == '\t')
				++nwhite;
			else
				++nother;
	}
	//�������
	//�����
	printf("nwhite = %d \nnother = %d \n", nwhite, nother);
	for (i = 0; i < 10; i++) {
		 printf("%d = %d \n", i, ndigit[i]);
	}
	//�����
	getchar();
	return 0;
}
