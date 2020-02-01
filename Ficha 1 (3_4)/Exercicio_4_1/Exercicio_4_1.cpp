// Exercicio_4_1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <iostream>
#include <iomanip> // format manipulators
#include <fstream> // file I/O
#include <string> // standard C++ strings
#include <cstring> // strings em C - arrays de chars
#include <cmath> // math functions
#include <climits> // various properties of the various variable types  
#include <cfloat> // various platform-dependent constants related to floating point values
#include <ctime> // função time(), que retorna o número de segundos que decorreram desde as zero horas do dia 1 / Jan / 1970

using namespace std;

bool isHydroxide(char compound[]) 
{
	if ((char)toupper(compound[strlen(compound) - 2]) == 'O' && (char)toupper(compound[strlen(compound) - 1]) == 'H')
		return true;
	return false;
}


int main()
{
	string testes[] = { "KOH", "H2O2", "NaCl", "NaOH", "C9H8O4", "MgOH"};
	int size = sizeof(testes) / sizeof(*testes);
	for (int i = 0; i < size; i++)
	{
		char *cstr = &testes[i][0u];
		cout << "Testando " << testes[i] << ": resultado -> " << isHydroxide(cstr) << endl;
	}

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
