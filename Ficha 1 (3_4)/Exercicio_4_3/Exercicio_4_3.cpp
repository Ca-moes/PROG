// Exercicio_4_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
using namespace std;

void decompose(string compound) 
{
	string tempc;
	// H 2 O, K O H, H2 O2, Na Cl, Na O H, C9 H8 O4 e Mg O H
	int len = compound.length();
	for (int i = 0; i < len; i++)
	{
		if (isdigit(compound[i+1]))
		{
			tempc = tempc + compound[i] + " ";
			continue;
		}
		if (islower(compound[i+1]))
		{
			tempc = tempc + compound[i] + compound[i + 1] + " ";
			continue;
		}
		if (isupper(compound[i+1]) && isupper(compound[i]))
		{
			tempc = tempc + compound[i] + " ";
		}
		if (isupper(compound[i]) && i == len -1)
		{
			tempc = tempc + compound[i];
		}
	}
	cout << tempc;
}

int main()
{
	string compound;
    cout << "CMP: ";
	cin >> compound;
	decompose(compound);
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
