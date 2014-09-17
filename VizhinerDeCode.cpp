#include "stdafx.h"
#include "windows.h"
#include "conio.h"
#include <fstream>
#include <iostream>
using namespace std;
#include <string.h>
#include <string>
char key[300];//ключ
char tmp[300];//для заполнения ключа
struct koord
{
	int a;
	int b;
};

int _tmain(int argc, _TCHAR* argv[])
{
	SetConsoleCP(1251);//подключение русского языка
	SetConsoleOutputCP(1251);//подключение русского языка
	char line[26]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
	char tabula_recta[26][26];//квадрат Вижинера
	char vhod[300];//входное сообщение
	int count=0;//длина входного сообщения
	int LenOfKey=0;//длина ключа
	int ProverkaKey=0;//проверка ключа для его заполнения
	
	
	//-строим табулуректу
	int TmpRect=0;
	for(int i=0;i<26;i++)
	{
		for(int j=0;j<26;j++)
		{
			TmpRect=i+j;
			if (TmpRect >= 26) TmpRect = TmpRect % 26;
			tabula_recta[i][j]=line[TmpRect];
		}
	}

	//-показываем табулу ректу
	for (int i = 0; i < 26; i++)
	{
		for (int j = 0; j < 26; j++)
		{
			cout<<tabula_recta[i][j];
		}
		cout<<"\n";
	}
	
	//-------подготовка входного файла
	FILE *file;
	char *infile="outfile.txt";
	file = fopen(infile,"r");
	
	//----выход из программы, если нету входного файла
	if (file==0) {
		cout<<"Входного файла не существует\n";
		getch();
		return 0;
	}
	//-первое,считаем длину файла
	char ch=0;
	int i=0;
	while(ch!=EOF)
	{
		ch=getc(file);
		if (ch!='\n' && ch!=EOF)
		{
			vhod[i]=ch;
			i++;
		}
	}
	cout<<"длина файла равна: "<<i;
	count=i;

	//--создадим строковый массив равный кол-ву символов в входном файле
	char* a=0;
	a=new char[i];

	//--переведем указатель текущего символа файла на начало файла с помощью функции fseek
	fseek(file,0,SEEK_SET);
	
	//--ввод и формирование ключа
	
	cout<<"Введите ключ:";
	gets(key);
	LenOfKey=strlen(key);
	for (int i = 0; i < LenOfKey; i++)
	{
		tmp[i]=key[i];
	}
	
	
	while(ProverkaKey<count)
	{
		for (int i = 0; i < LenOfKey; i++)
		{
			key[i+ProverkaKey]=tmp[i];
		}
		ProverkaKey=strlen(key);
	}


	
	
	
	//реализация алгоритма
	koord nabor[100];
	for(int i=0;i<count;i++)
	{
		for(int j=0;j<26;j++)
		{
			if (line[j]==key[i])
			{
				nabor[i].a=j;
			}
		}
	}
	
	
	char Coding[100];
	for(int ii=0;ii<count;ii++)
	{
		for(int i=0;i<26;i++)
		{
			if (i==nabor[ii].a)
			{
				for(int j=0;j<26;j++)
				{
					if (tabula_recta[i][j]==vhod[ii])
					{
						//cout<<tabula_recta[i][j];
						Coding[ii]=j;
					}
				}
			}
		}
	}

	//отправка выходного файла
	//-------подготовка входного файла
	FILE *file2;
	char *outfile="OutfileIshod.txt";
	file2 = fopen(outfile,"w");
	for(int i=0;i<count;i++)
	{
		for(int j=0;j<26;j++)
		{
			if (Coding[i]==j)
			{
				putc(line[j],file2);
			}
		}
	}
	
	getch();
	return 0;
}

