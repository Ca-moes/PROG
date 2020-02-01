// Exercicio_1_4.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	double a, b, c, d, e, f, x = 0, y = 0;
	cout << "a*x + b*y = c" << endl;
	cout << "d*x + e*y = f" << endl;
	cout << "x = (c*e - b*f) / (a*e - b*d)" << endl;
	cout << "y = (a*f - c*d) / (a*e - b*d)\n" << endl;

	cout << "Indique os valores de a, b, c, d, e, f: " << endl;
	cin >> a >> b >> c >> d >> e >> f;

	if (((a * e - b * d) == 0 && (c*e - b * f) == 0) || ((a * e - b * d) == 0 && (a*f - c * d) == 0))
	{
		cout << "Sistema indeterminado.";
	}
	else
	{
		if ((a*e - b * d) == 0)
		{
			cout << "Sistema impossivel.";
		}
		else
		{
			x = (c * e - b * f) / (a * e - b * d);
			y = (a * f - c * d) / (a * e - b * d);

			cout << "x = " << x << endl;
			cout << "y = " << y;
		}
	}

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
