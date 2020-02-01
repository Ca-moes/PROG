// Exercicio_4_6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <stdlib.h> // atoi() accepts string - converts to int
#include <iomanip> // format manipulators
#include <fstream> // file I/O
#include <string> // standard C++ strings
#include <cstring> // strings em C - arrays de chars
#include <cmath> // math functions
#include <climits> // various properties of the various variable types  
#include <cfloat> // various platform-dependent constants related to floating point values
#include <ctime> // função time(), que retorna o número de segundos que decorreram desde as zero horas do dia 1 / Jan / 1970
#include <sstream> 
using namespace std;

bool checkint(string teste)
{
	for (int i = 0; i <= (teste.length() - 1); i++) {
		if (teste[i] == ' ')
			return false;
	}
	if (teste.length() == 1)
	{
		if (isdigit(teste[0]))
			return true;
		else return false;
	}
	else
	{
		for (int i = 0; i <= (teste.length() - 1); i++)
		{
			if (isdigit(teste[i]) == 0)
				return false;
		}
		return true;
	}

}
// checks if string is a valid int;

//////////////////////////////////////////////////////////////////
void readIntArray(int a[], int nElem) {

	// 1ª - ler inputs com strings SEMPRE.
	// 2ª - ler com getline e não cin.
	// 3ª - criar função que verifica se <string> é valida (cheia de if's para todos os casos) e devolte um bool
	// 4ª - criar ciclo com valor de bool, caso falso volta a pedir
	// 5ª - Com valor de input correto, continuar 

	string temp = "";
	for (int i = 0; i < nElem; i++)
	{
		do
		{
			temp = "";
			cout << "Index " << i << ", value? ";
			while (temp.length() == 0)     // caso dê enter sem nada, pede outra vez
				getline(cin, temp);

		} while (checkint(temp) == false);
		a[i] = stoi(temp);
	}
}
//////////////////////////////////////////////////////////////////

int searchValueInIntArray(const int a[], int nElem, int value) {
	for (int i = 0; i < nElem - 1; i++)
	{
		if (a[i] == value)
			return i;
	}
	return -1;
}

int searchMultValuesInIntArray(const int a[], int nElem, int value, int index[]) {
	int counterindex = 0;
	for (int i = 0; i < nElem - 1; i++)
	{
		if (a[i] == value) {
			index[counterindex] = i;
			counterindex++;
		}
	}
	if (counterindex == 0)
		return -1;
	else
		return counterindex;

}

int main()
{
	int const nElem = 10;
	int a[nElem], index[nElem];

	readIntArray(a, nElem);
	cout << searchMultValuesInIntArray(a, nElem, 4, index) << endl;

	//cout << searchValueInIntArray(a, nElem, 3);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
