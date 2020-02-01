// Exercicio_2_14.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <iomanip> // format manipulators
#include <fstream> // file I/O
#include <string> // standard C++ strings
#include <cmath> // math functions
#include <climits> // various properties of the various variable types  
#include <cfloat> // various platform-dependent constants related to floating point values
using namespace std;
#define PI 3.14159265

int main()
{
	double n = 0, delta = 0, dif = 0, rqn = 0, rq = 1;
	int nMaxIter = 0, nIter = 0, counter = 0;
	cout << "Insira n, delta & numero Max de Iteracoes: ";
	cin >> n >> delta >> nMaxIter;

	do
	{
		rqn = (rq + n / rq) / 2;
		dif = sqrt(pow(n - pow(rqn, 2), 2));
		rq = rqn;
		nIter++;
		if (nIter == nMaxIter)
			break;
		if (dif <= delta)
			break;
	} while (true);
	cout << "N de iteracoes: " << nIter << endl << "dif: " << dif << endl;
	cout << "raiz aproximada: " << rq;

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
