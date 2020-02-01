// Exercicio_2_2_a.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	int used1 = 0, used2 = 0, used3 = 0;
	double num1, num2, num3, maior, meio, menor;
	cout << "Insira 3 numeros: " << endl;
	cin >> num1 >> num2 >> num3;
	maior = num1;
	meio = num2;
	menor = num3;
	// Det. o maior
	if (num2 > maior)
	{
		maior = num2;
		used2 = 1;
	}
	if (num3 > maior)
	{
		maior = num3;
		used2 = 0;
		used3 = 1;
	}
	//Det. o menor
	if (num2 < menor)
	{
		menor = num2;
		used2 = 1;
	}
	if (num1 < menor)
	{
		menor = num1;
		used2 = 0;
		used1 = 1;
	}
	//Det. o meio
	if (num1 < maior && num1 > menor)
		meio = num1;
	if (num2 < maior && num2 > menor)
		meio = num2;
	if (num3 < maior && num3 > menor)
		meio = num3;
	if (num1 == num3 && num1 != num2)
		meio = num1;

	cout << "1 usado: " << used1 << endl << "2 usado: " << used2 << endl << "3 usado: " << used3 << endl;
	cout << "maior: " << maior << endl << "meio: " << meio << endl << "menor: " << menor;
	

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
