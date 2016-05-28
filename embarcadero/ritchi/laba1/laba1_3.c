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
	//перечисление переменных
	char str[NSTR][MAX];
	int c, ch;
	int i;
	int m, n, j; //координаты в таблице
	//перечисление переменных

	//инициализация
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
	//инициализация

	for (i = 0; i < NSTR ; i++)
			str[i][0] = '\0';

	//титульная страница
	gotoxy(22,12);
	printf("    Лабораторная работа №1");
	gotoxy(22,13);
	printf("Выполнил студент группы КМ-32");
	gotoxy(22,14);
	printf("       Драбчук Денис");
	//титульная страница
	getch();
	//программа
	m=0;
	n=0;
	clrscr();

	//чистая таблица
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
	//чистая таблица

	//изменение параметров м н
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
				//заполнение ячейки
				GetStr(str[m]);
				//заполнение ячейки
				//вырисовка таблицы
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
				//вырисовка таблицы
				break;
			}
			default: break;
		}
		gotoxy(13*n + 2, 2*m + 6);
	}
	//изменение параметров м н

	//программа
	return 0;
}
