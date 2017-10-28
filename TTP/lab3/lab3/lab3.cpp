
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include <conio.h>
#include <locale>
#include <windows.h>


char bufRus[256];
char* Rus(const char*text) //перевод на русский
{
	CharToOemA(text, bufRus);
	return bufRus;
}


int zag(char str[], char pattern[]) //провер€ем на равенство паттернам
{
	int i = 0, q = 0, n = 0;
	while (str[n] != '|')
		n++;
	for (; i < n;)
	{
		if (str[i] == pattern[i] || str[i] == (pattern[i] + 32) || str[i] == (pattern[i] - 32))
			i++;
		else
			return 0;
	}
	if (i == n)
	return 1;
	else return 0;
}

int name(char str[]) //находим часть пути входного файла,где можно найти ошибку
{
	int n = 0, q = 0, i, k, c;
	for (c = 0; str[c] == ' '; c++);
	if (str[c] == '\n' || str[c] == '\0')
		return 0;
	char pro[1000];
	for (i = 0; i < 1000; i++)
		pro[i] = '|';
	while (str[n] != '\0')
		n++;
	i = n;
	while (str[i] != '\\' && i != -1)
		i--;
	i++;
	while (str[i] == ' ')
		i++;
	k = i;
	while (str[k] != '.' && k <= n)
		k++;
	k--;
	while (str[k] == ' ')
		k--;
	while (str[i] == ' ')
		i++;
	for (; i <= k; i++, q++)
	{
		pro[q] = str[i];
	}
	if (zag(pro, "con") == 0 && zag(pro, "prn") == 0 && zag(pro, "aux") == 0 && zag(pro, "nul") == 0 && zag(pro, "com1") == 0 && zag(pro, "com2") == 0 && zag(pro, "com3") == 0 && zag(pro, "com4") == 0 &&
		zag(pro, "com5") == 0 && zag(pro, "com6") == 0 && zag(pro, "com7") == 0 && zag(pro, "com8") == 0 && zag(pro, "com9") == 0 && zag(pro, "lpt1") == 0 && zag(pro, "lpt2") == 0 && zag(pro, "lpt3") == 0 &&
		zag(pro, "lpt4") == 0 && zag(pro, "lpt5") == 0 && zag(pro, "lpt6") == 0 && zag(pro, "lpt7") == 0 && zag(pro, "lpt8") == 0 && zag(pro, "lpt9") == 0)
		return 1;
	else
		return 0;
}

int search(char string[], char a) //ищем вхождение символа в строку
{
	for (int i = 0; string[i] != '\0'; i++)
	{
		if (a == string[i])
			return 1;
	}
	return 0;
}

void length(char a[], int &n, char glas[], char soglas[], int &i) //длина сслова, которое надо обработать
{
	n = 0;
	int p = i;
	while (search(glas, a[p]) != 0 || search(soglas, a[p]) != 0)
	{
		n++;
		p++;
	}
}

void prob(char a[], int &i, char glas[], char soglas[]) //пропуск всех "не букв".
{
	while (search(glas, a[i]) == 0 && search(soglas, a[i]) == 0)
	{
		i++;
	}
}

void change(char a[], int n, int &i, char glas[], char soglas[]) //изменение слова. √ласные-вперед, согласные-назад
{
	int y = 0;
	char c;
	i = i + n;
	do
	{
		y = 0;
		int p = i - n;
		for (; p < (n + i); p++)
		{
			if (search(soglas, a[p]) == 1 && search(glas, a[p + 1]) == 1)
			{
				c = a[p];
				a[p] = a[p + 1];
				a[p + 1] = c;
				y++;
			}
		}
		p = p - n;
	} while (y != 0);
}


char strok[1000]; //последовательное считывание строк
void ReadToStr(FILE *Fl)
{
	char D; 
	int k = 0;
	do
	{
		D = 0;
		if (fscanf(Fl, "%c", &D)) {
			strok[k] = D;
			k++;
		}
		else 
		{
			break;
			
		}
	} while (D != '\n' && D != 0 && D != '\0' && !feof(Fl) && D != ' ');
	strok[k + 1] = '\0';
}



int main()
{
	FILE *fin, *fout;

	char glas[] = "AEIOUYaeiouyј”≈џќЁя»ё®ауеыоэ€июЄ";
	char soglas[] = "BCDFGHJKLMNPQRSTVWXZbcdfghjklmnpqrstvwxz…÷ Ќ√Ўў«’Џ‘¬ѕ–Ћƒ∆„—ћ“№Ѕйцкнгшщзхъфвпрлджчсмтьб";
	char filename1[1000], filename2[1000];
	int i = 0, n = 0, l = 0;
	
one:
	do
	{
		if (l == 0)
		{
			printf(Rus("¬ведте название входного файла:\n"));

			l++;
		}
		else
		{
			printf(Rus("Ёто неверное название входного файла!\n¬ведите корректное название входного файла:\n"));
		}
		gets_s(filename1, 1000);

	} while (name(filename1) == 0);

	if (!(fin = fopen(filename1, "r")))
	{
		printf(Rus("‘айл с данным имененм невозможно открыть!\n"));
		goto one;
	}

two:
	l = 0;
	do
	{
		if (l == 0)
		{
			printf(Rus("¬ведте название выходного файла:\n"));
			l++;
		}
		else
		{
			printf(Rus("Ёто неверное название выходного файла!\n¬ведите корректное название выходного файла:\n"));
		}
		gets_s(filename2, 1000);
	} while (name(filename2) == 0);

	if (!(fout = fopen(filename2, "w"))) 
	{ 
		printf(Rus("‘айл с данным имененм невозможно открыть!\n"));
		goto two; 
	}
	
	int j = 0;

	while (!feof(fin))
	{
		ReadToStr(fin);
		while (strok[j] != '\0')
		{
			prob(strok, j, glas, soglas);
			length(strok, n, glas, soglas, j);
			change(strok, n, j, glas, soglas);
		}
		fprintf(fout, "%s", strok);
		for (int z = 0; z < 1000; z++)
			strok[z] = '\0';
		j = 0;
	}
	
	
	fclose(fin);
	fclose(fout);
	return 0;

}


