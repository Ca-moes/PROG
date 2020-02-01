// Exercicio_1_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <iostream> // basic interactive input/output (I/O) /
#include <iomanip> // format manipulators
#include <fstream> // file I/O
#include <string> // standard C++ strings
#include <cmath> // math functions
#include <climits> // various properties of the various variable types  
#include <cfloat> // various platform-dependent constants related to floating point values

using namespace std;


int main()
{
	int a, b, c;
	double media;
	cout << "A ? ";
	cin >> a;
	cout << "B ? ";
	cin >> b;
	cout << "C ? ";
	cin >> c;
	media = (a + b + c) / 3.0;

	cout << setprecision(2) << fixed;

	cout << "media   = " << media << endl;
	cout << "A-media = " << a - media << endl;
	cout << "B-media = " << b - media << endl;
	cout << "C-media = " << c - media << endl;
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
