
#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include "stdlib.h"
#include <conio.h>
#include <locale>
#include <windows.h>


char bufRus[256];
char* Rus(const char*text) //������� �� �������
{
	CharToOemA(text, bufRus);
	return bufRus;
}


int isDiniedName(char name[]) //��������� �� ��������� ���������
{
	char* deniedNames[] =
	{ "con", "prn", "aux", "nul", "com1", "com2", "com3", "com4", "com5", "com6", "com7", "com8", 
	  "com9", "lpt1", "lpt2", "lpt3", "lpt4", "lpt5",  "lpt6", "lpt7", "lpt8", "lpt9" };

	for (int i = 0; i < sizeof(deniedNames)/sizeof(char*); i++)
	{
		if (strcmp(name, deniedNames[i]) == 0)
			return 0;
	}
	return 1;
}

int find(const char* where, char what)
{
  int whereLength = strlen(where);

  for(int offset = 0; offset < whereLength; offset++) {
    if(where[offset] == what)
      return offset;
  }
  return -1;
}

void removeSymbolsFromString(char* where, char symbol)
{
  int length = strlen(where);
  for(int i = 0; i < length; i++) {
    for(int j = i + 1; j < length; j++) {
      if(where[j] != symbol) {
        where[i] = where[j];
        break;
      }
    }
  }
}

int name(char str[]) //������� ����� ���� �������� �����,��� ����� ����� ������
{
  int length = 0, q = 0, i, k, c;
	for (c = 0; str[c] == ' '; c++);
	if (str[c] == '\n' || str[c] == '\0')
		return 0;
	char pro[1000];
	memset(pro, '\0', sizeof(pro));

  length = strlen(str);
  i = length;
	while (str[i] != '\\' && i != -1)
		i--;
	i++;
	while (str[i] == ' ')
		i++;
	k = i;
  k += find(str+k, '.');
	k--;
	while (str[k] == ' ')
		k--;
	while (str[i] == ' ')
		i++;
	for (; i <= k; i++, q++)
	{
		pro[q] = str[i];
	}
	return isDiniedName(pro);
}

int search(char string[], char a) //���� ��������� ������� � ������
{
	for (int i = 0; string[i] != '\0'; i++)
	{
		if (a == string[i])
			return 1;
	}
	return 0;
}

void length(char a[], int &n, char glas[], char soglas[], int &i) //����� ������, ������� ���� ����������
{
	n = 0;
	int p = i;
	while (search(glas, a[p]) != 0 || search(soglas, a[p]) != 0)
	{
		n++;
		p++;
	}
}

void prob(char a[], int &i, char glas[], char soglas[]) //������� ���� "�� ����".
{
	while (search(glas, a[i]) == 0 && search(soglas, a[i]) == 0)
	{
		i++;
	}
}

void change(char a[], int n, int &i, char glas[], char soglas[]) //��������� �����. �������-������, ���������-�����
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


char strok[1000]; //���������������� ���������� �����
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

bool Test_FindSymbolInString()
{
  return find("   con.tre   ", '.') == 6;
}

bool Test_name()
{
  return name("     con.  templ") == 0
      && name(" abc.templ") == 1;
}

bool Test_removeSymbolsFromString()
{
  char* str = "a    df   v";
  removeSymbolsFromString(str, ' ');
  return strcmp(str, "adfv") == 0;
}

#define RUN_TEST(name) \
  if(!Test_##name()) {  \
    fprintf(stderr, "Test "#name" FAILED!\n");  \
    return 1;                                              \
  }

int main()
{
  RUN_TEST(FindSymbolInString);
  RUN_TEST(name);
  RUN_TEST(removeSymbolsFromString);


	FILE *fin, *fout;

	char glas[] = "AEIOUYaeiouy��������ި����������";
	char soglas[] = "BCDFGHJKLMNPQRSTVWXZbcdfghjklmnpqrstvwxz����������������������������������������������";
	char filename1[1000], filename2[1000];
	int i = 0, n = 0, l = 0;
	
one:
	do
	{
		if (l == 0)
		{
			printf(Rus("������ �������� �������� �����:\n"));

			l++;
		}
		else
		{
			printf(Rus("��� �������� �������� �������� �����!\n������� ���������� �������� �������� �����:\n"));
		}
    gets(filename1);

	} while (name(filename1) == 0);

	if (!(fin = fopen(filename1, "r")))
	{
		printf(Rus("���� � ������ ������� ���������� �������!\n"));
		goto one;
	}

two:
	l = 0;
	do
	{
		if (l == 0)
		{
			printf(Rus("������ �������� ��������� �����:\n"));
			l++;
		}
		else
		{
			printf(Rus("��� �������� �������� ��������� �����!\n������� ���������� �������� ��������� �����:\n"));
		}
    gets(filename2);
	} while (name(filename2) == 0);

	if (!(fout = fopen(filename2, "w"))) 
	{ 
		printf(Rus("���� � ������ ������� ���������� �������!\n"));
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


