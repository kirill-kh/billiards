#define MAX 9
#define NSTR 3

#include <stdio.h>
#include <conio.h>

int GetStr(char *str[MAX])
{
	char c;
	int i;
	i = 0;
	while ((i < 9) && ((c = getch()) != '\n'))
	{
		putchar(c);
		str[i] = c;
		++i;
	}
	str[i] = '\0';
	return i;
}

main()
{
	//������������ ����������
	char str[NSTR][MAX];
	int c, ch;
	int i;
	int m, n, j; //���������� � �������
	//������������ ����������

	//�������������
	/*for (i = 0; i < NSTR ; i++) {
		for (j = 0; j < MAXLONG; j++) {
			str[i][j] = ' ';
		}
	}
	for (i = 0; i < NSTR ; i++) {
		for (j = 0; j < MAXLONG; j++) {
			str[i][j] = ' ';
		}
	} */
	//�������������

	for (i = 0; i < NSTR ; i++)
			str[i][0] = '\0';

	//��������� ��������
	gotoxy(22,12);
	printf("    ������������ ������ �1");
	gotoxy(22,13);
	printf("�������� ������� ������ ��-32");
	gotoxy(22,14);
	printf("       ������� �����");
	//��������� ��������
	getch();
	//���������
	m=0;
	n=0;
	clrscr();

	//������ �������
	printf("|--------------------------------------------------|\n");
	printf("|            Charackteristics of PECM              |\n");
	printf("|--------------------------------------------------|\n");
	printf("| Processor  |     Mgz    |    RAM     | Type      |\n");
	printf("|--------------------------------------------------|\n");
	printf("|            |            |            |           |\n");
	printf("|--------------------------------------------------|\n");
	printf("|            |            |            |           |\n");
	printf("|--------------------------------------------------|\n");
	printf("|            |            |            |           |\n");
	printf("|--------------------------------------------------|\n");
	printf("| Type C - CISC processor, R - RISC processor      |\n");
	printf("|--------------------------------------------------|\n");
	//������ �������

	//��������� ���������� � �
	while ((c = getch()) != 27)
	{
		switch (c)
		{
			case 72: m =(m + NSTR - 1) % (NSTR); break;
			case 80: m =(m + NSTR + 1) % (NSTR); break;
			case 75: n = (n + 3) % 4; break;
			case 77: n = (n + 5) % 4; break;
			case 13:
			{
				//���������� ������
				GetStr(str[m]);
				//���������� ������
				//��������� �������
				clrscr();
				printf("|--------------------------------------------------|\n");
				printf("|            Charackteristics of PECM              |\n");
				printf("|--------------------------------------------------|\n");
				printf("| Processor  |     Mgz    |    RAM     | Type      |\n");
				printf("|--------------------------------------------------|\n");
				printf("|            |            |            |           |\n");
				printf("|--------------------------------------------------|\n");
				printf("|            |            |            |           |\n");
				printf("|--------------------------------------------------|\n");
				printf("|            |            |            |           |\n");
				printf("|--------------------------------------------------|\n");
				printf("| Type C - CISC processor, R - RISC processor      |\n");
				printf("|--------------------------------------------------|\n");
				for (j = 0; j < NSTR; ++j)
				{
					gotoxy( 2, 2*j + 6);
					printf("%9s", str[j]);
				}
				//��������� �������
				break;
			}
			default: break;
		}
		gotoxy(13*n + 2, 2*m + 6);
	}
	//��������� ���������� � �

	//���������
	return 0;
}
