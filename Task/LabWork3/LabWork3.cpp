#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <string>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)

using namespace std;

void Task1()
{
	system("cls");

	cout << "\t\tЗадание №1\n";
	getchar();
		
	FILE * TextFile;
	FILE * TextFileResult;
	char *fileName = (char*)malloc(6);//переменная для записи имени файлов
	fileName[0] = 't';
	fileName[1] = 'a';
	fileName[2] = 's';
	fileName[3] = 'k';
	fileName[4] = '1';
	fileName[5] = '\0';

	TextFile = fopen(fileName, "rt");

	char* fileResult = (char*)malloc(2);
	fileResult[0] = 'R';
	fileResult[1] = '\0';

	TextFileResult = fopen(fileResult, "wt");
	char* phrase;
	phrase = (char*)malloc(200);
	
	if (TextFile != NULL && TextFileResult != NULL)
	{
		while (true)
		{
			int  i = 0;

			if (fgets(phrase, 200, TextFile) != NULL)
			{
				int numSymbol = 0;

				for (i = 0; i < strlen(phrase); i++)
				{
					if (tolower(phrase[i]) == 'o' || tolower(phrase[i]) == 'о' || tolower(phrase[i]) == 'о' || tolower(phrase[i]) == 'О')
						numSymbol++;

					if (phrase[i] == ' ')
					{
						if (numSymbol == 2)
							break;
						else
							numSymbol = 0;
					}
				}

				if (numSymbol != 2)
				{
					fseek(TextFileResult, 0, SEEK_END);

					fputs(phrase, TextFileResult);
				}
			}
			else
				break;
		}

		fclose(TextFile);
		fclose(TextFileResult);
		remove(fileName);
		rename(fileResult, fileName);
	}

	cout << "Записи в файле успешно отредактированы!";
	cout << "\nНажмите Enter чтобы выйти в меню...";
	getchar();
}

void Task2()
{
	system("cls");

	cout << "\t\tЗадание №2\n";
	getchar();

	FILE * TextFile;
	FILE * TextFileResult;
	char *fileName = (char*)malloc(6);//переменная для записи имени файлов
	fileName[0] = 't';
	fileName[1] = 'a';
	fileName[2] = 's';
	fileName[3] = 'k';
	fileName[4] = '2';
	fileName[5] = '\0';

	TextFile = fopen(fileName, "rt");

	char* fileResult = (char*)malloc(12);
	fileResult[0] = 'R';
	fileResult[1] = 'e';
	fileResult[2] = 's';
	fileResult[3] = 'u';
	fileResult[4] = 'l';
	fileResult[5] = 't';
	fileResult[6] = 'T';
	fileResult[7] = 'a';
	fileResult[8] = 's';
	fileResult[9] = 'k';
	fileResult[10] = '2';
	fileResult[11] = '\0';

	TextFileResult = fopen(fileResult, "wt");

	fileName = (char*)realloc(fileName, 0);
	fileResult = (char*)realloc(fileResult, 0);

	char* phrase;
	phrase = (char*)malloc(300);
	
	int  strin = 0, column = 0;

	while (true)
	{
		if (fgets(phrase, 300, TextFile) != NULL)
		{
			if (column == 0)
			{
				for (int j = 0; j < strlen(phrase); j++)
				{
					if (phrase[j] == ' ')
					{
						column++;
					}
				}
			}
			strin++;
		}
		else
			break;
	}

	double** matrix = new double* [strin];
	for (int j = 0; j < strin; j++)
	{
		matrix[j] = new double[column + 1];
	}

	fseek(TextFile, 0, SEEK_SET);
	int  i = 0, k = 0;

	if (TextFile != NULL && TextFileResult != NULL)
	{
		while (true)
		{
			int a = 0, j = 0;
			char* whole = (char*)malloc(30);
			bool f = false;

			if (fgets(phrase, 300, TextFile) != NULL)
			{
				int idx = 0;

				if (k == strin - 1)
					idx = 1;

				for (i = 0; i < strlen(phrase) + idx; i++)
				{
					if (isdigit(phrase[i]) || phrase[i] == '-')
					{
						whole[a] = phrase[i];
						a++;
					}
					else if (phrase[i] == '.' || phrase[i] == ',')
					{
						whole[a] = '.';
						a++;
					}
					else if (phrase[i] == '\n' || phrase[i] == '\0' || phrase[i] == ' ')
					{
						whole[a] = '\0';
						matrix[k][j] = atof(whole);
						whole = (char*)realloc(whole,0);
						whole = (char*)malloc(30);
						j++;
						a = 0;
					}
				}
			}
			else
				break;

			whole = (char*)realloc(whole, 0);
			k++;
		}

		cout << "\tМатрица до сортировки строк\n" << endl;

		for (int g = 0; g < strin; g++)
		{
			for (int y = 0; y < column + 1; y++)
			{
				cout << "|" << matrix[g][y] << "| ";
			}
			cout << endl;
		}

		for (int g = 0; g < strin; g++)
		{
			int strMax = 0, colMax = 0;
			int strMin = 0, colMin = 0;
			double max = MININT32, min = MAXINT32;

			for (int y = 0; y < column + 1; y++)
			{
				if (matrix[g][y] > max)
				{
					max = matrix[g][y];
					strMax = g;
					colMax = y;
				}
			}
			if (max != MININT32)
			{
				double v = matrix[strMax][colMax];
				matrix[strMax][colMax] = matrix[g][0];
				matrix[g][0] = v;
			}

			for (int y = 0; y < column + 1; y++)
			{
				if (matrix[g][y] < min)
				{
					min = matrix[g][y];
					strMin = g;
					colMin = y;
				}
			}
			if (min != MAXINT32)
			{
				double v = matrix[strMin][colMin];
				matrix[strMin][colMin] = matrix[g][column];
				matrix[g][column] = v;
			}
		}

		cout << "\n\tМатрица после сортировки строк\n" << endl;

		for (int g = 0; g < strin; g++)
		{
			for (int y = 0; y < column + 1; y++)
			{
				cout << "|" << matrix[g][y] << "| ";
			}
			cout << endl;
		}

		for (int g = 0; g < strin; g++)
		{
			int r = 0;
			char* phrase = (char*)malloc(300);

			for (int y = 0; y < column + 1; y++)
			{
				string str = to_string(matrix[g][y]);
				int u = 0;

				// удаляем не значащие нули в числе
				if (str[str.size() - 1] == '0')
					for (size_t i = str.size() - 1; str[i] == '0'; i--)
						str.erase(i, 1);

				if (str[str.size() - 1] == '.')
					str.erase(str.size() - 1, 1);

				int n = str.length();

				// записывааем число в char*
				for (u = 0; u < n; r++)
				{
					phrase[r] = str[u];
					u++;
				}
				
				phrase[r] = ' ';
				r++;
			}

			phrase[r] = '\0';
			fputs(phrase, TextFileResult);

			// Переходим на след строчку в файле
			fputc('\n', TextFileResult);

			phrase = (char*)realloc(phrase, 0);
		}

		fclose(TextFile);
		fclose(TextFileResult);
	}

	cout << "\nНажмите Enter чтобы выйти в меню...";
	getchar();
}

// Создаём текстовый файл
void CreateBinarFile(char* fileName)
{
	FILE * TextFile;
	const int maxLength = 20; // Количество чисел в текстовом файле
	const int firs_value = -20; // Левая граница случайных чисел
	const int last_value = 20; // Правая граница случайных чисел

	TextFile = fopen(fileName, "wb");

	char* values = (char*)malloc(maxLength*5);

	int u = 0;

	for (int i = 0; i < maxLength; i++)
	{
		int rand_value = (double)rand() / (RAND_MAX + 1) * (last_value - firs_value) + firs_value;

		string str = to_string(rand_value);

		for (int j = 0; j < str.length(); j++)
		{
			values[u] = str[j];
			u++;
		}
		values[u] = ' ';
		u++;
	}
	values[u] = '\0';

	values = (char*)realloc(values, u+1);

	fwrite(values, 1, u+1, TextFile);
	fclose(TextFile);
}

// Чтение тестового файла
void ReadBinarFile(char* fileName)
{
	FILE * TextFile;

	TextFile = fopen(fileName, "rt");

	// определяем размер файла
	fseek(TextFile, 0, SEEK_END);
	long lSize = ftell(TextFile);
	rewind(TextFile);

	char * buffer = (char*)malloc(sizeof(char) * lSize);

	fgets(buffer, 300, TextFile);

	cout << buffer << endl;

	fclose(TextFile);
}

void Task3()
{
	system("cls");

	cout << "\t\tЗадание №3\n";
	getchar();

	char *fileName = (char*)malloc(6);//переменная для записи имени файлов
	fileName[0] = 't';
	fileName[1] = 'a';
	fileName[2] = 's';
	fileName[3] = 'k';
	fileName[4] = '3';
	fileName[5] = '\0';

	CreateBinarFile(fileName); // Создаём текстовый файл

	cout << "\tДанные файла, до обработки:\n" << endl;

	ReadBinarFile(fileName); // Читаем записи текстовый файла

	FILE * TextFileRead;

	TextFileRead = fopen(fileName, "r+t");

	// определяем размер файла
	fseek(TextFileRead, 0, SEEK_END);
	long lSize = ftell(TextFileRead);
	rewind(TextFileRead);

	char * buffer = (char*)malloc(sizeof(char) * lSize);
	int * values = new int[lSize];

	int result = fread(buffer, 1, lSize, TextFileRead);
	int j = 0;
	string str = "";

	for (int i = 0; i < lSize; i++)
	{
		if (buffer[i] != ' ')
		{
			str += buffer[i];
		}
		else if (buffer[i] == ' ')
		{
			values[j] = stoi(str);
			j++;
			str = "";
		}
	}

	buffer = (char*)realloc(buffer, 0);

	int* valueNew = new int[j + 1];
	int k = 0;

	for (int i = 0; i < j + 1; i++)
	{
		if (values[i] > 0)
		{
			valueNew[k] = values[i];
			k++;
			valueNew[k] = values[i] * values[i];
			k++;
		}
	}

	delete [] values;

	fclose(TextFileRead);

	TextFileRead = fopen(fileName, "wt");

	char* numb = (char*)malloc(j * 5);

	int u = 0;

	for (int i = 0; i < k; i++)
	{
		string str = to_string(valueNew[i]);

		for (int j = 0; j < str.length(); j++)
		{
			numb[u] = str[j];
			u++;
		}
		numb[u] = ' ';
		u++;
	}
	numb[u] = '\0';

	numb = (char*)realloc(numb, u + 1);

	fwrite(numb, 1, u + 1, TextFileRead);

	fclose(TextFileRead);

	free(numb);
	delete [] valueNew;
	
	cout << "\n\n\tДанные файла, после обработки:\n" << endl;

	ReadBinarFile(fileName); // Читаем записи текстового файла
		
	cout << "\nНажмите Enter чтобы выйти в меню...";
	getchar();
}

int main()
{
	// Установка кириллицы
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	bool f = true;

	while (f)
	{
		system("cls");
		cout << "Меню: " << endl;
		cout << "1 - работа с файлом. Удалить фразы, содержащие две буквы 'О'" << endl;
		cout << "2 - работа с матрицей в текстовом файле" << endl;
		cout << "3 - работа с компонентами текстового файла" << endl;
		cout << "0 - выход из программы" << endl;
		cout << "Введите номер задания: ";
		int numLesson;
		cin >> numLesson;

		switch (numLesson)
		{
		case 1:
			Task1();
			break;
		case 2:
			Task2();
			break;
		case 3:
			Task3();
			break;
		case 0:
			f = false;
			break;
		default:
			cout << "Такого пункта не существует! нажмите любую клавишу...";
			getchar();
			getchar();
			break;
		}
	}
	system("PAUSE");
}