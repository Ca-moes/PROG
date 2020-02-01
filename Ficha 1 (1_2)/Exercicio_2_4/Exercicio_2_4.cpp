// Exercicio_2_3.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

int main()
{	
	double peso = 0;
	cout << "500e			-> 5e" << endl;
	cout << ">=500e && <=1000e	-> 5e    + 1.5e por cada 100g acima de 500g" << endl;
	cout << ">1000e 			-> 12.5e + 5.0e por cada 250g acima de 1000g\n" << endl;


	cout << "Peso para transportar? " << endl;
	cin >> peso;

	if (peso < 500)
		cout << "Custo de transporte: 5 euros";
	if (peso >= 500 && peso <= 1000)
		cout << "Custo de transporte: " << 5 + ceil(((peso - 500) / 100)) * 1.5 << " euros";
	if (peso > 1000)
		cout << "Custo de transporte: " << 12.5 + ceil(((peso - 1000) / 250)) * 5 << " euros.";

	return 0;
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
