// Exercicio_2_11_a.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	double num = 0, factorial = 1, x = 0;
	int denominador = 1, counter = 0, limite = 0;
	cout << "Escolha n: ";
	cin >> limite;
	cout << "Escolha x: ";
	cin >> x;

	do
	{
		if (counter % 2 == 0)
			num = num + (pow(x, counter) * 1.0 / factorial);
		else
			num = num - (pow(x, counter) * 1.0 / factorial);
		factorial = factorial * (counter + 1);
		counter++;
	} while (counter != limite);
	cout << num;
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
