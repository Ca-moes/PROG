// Exercicio_2_6.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	bool isprime = true;
	int tempnumber = 2, counter = 0;
	do
	{
		for (int i = 2; i <= sqrt(tempnumber); i++)
		{
			if (tempnumber % i == 0)
			{
				isprime = false;
				break;
			}
		}
		if (tempnumber == 2 || tempnumber == 4)
			isprime = false;
		if (isprime)
		{
			cout << "prime number: " << counter << " with value: " << tempnumber << endl;
			counter = counter + 1;
		}
		tempnumber = tempnumber + 1;
		isprime = true;
	} while (counter<=100);


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
