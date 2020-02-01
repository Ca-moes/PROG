// Exercicio_2_10_b.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	int num = 0, comp = 0, newnumb = 0, ajuda = 0, temp = 0;
	cout << "Insira um numero: ";
	cin >> num;

	comp = to_string(num).length();
	//cout << comp << endl;
	//cout << num % 10 << endl;
	//cout << (num/10) % 10 << endl;

	ajuda = num;
	comp = pow(10, comp-1);
	do
	{
		temp = ajuda % 10;
		temp = temp * comp;
		newnumb = newnumb + temp;
		comp = comp / 10;
		ajuda = ajuda / 10;
	} while (comp);
	//cout << newnumb;
	if (newnumb == num)
		cout << "E capicua";
	else
		cout << "Nao e capicua";
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
