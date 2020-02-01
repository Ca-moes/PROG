// Exercicio_3_2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <iomanip> // format manipulators
#include <fstream> // file I/O
#include <string> // standard C++ strings
#include <cmath> // math functions
#include <climits> // various properties of the various variable types  
#include <cfloat> // various platform-dependent constants related to floating point values
#include <ctime> // função time(), que retorna o número de segundos que decorreram desde as zero horas do dia 1 / Jan / 1970
using namespace std;
#define PI 3.14159265

bool isPrime(int numb) {
	// retorna true se argumento for primo
	bool isprime = true;
	for (int i = 2; i <= sqrt(numb); i++)
	{
		if (numb % i == 0)
		{
			isprime = false;
			break;
		}
	}
	if (numb == 4)
		return false;
	else
	{
		if (isprime)
			return true;
		else
			return false;
	}
}


int main()
{
	int numb;
	cout << "Insere um numero: ";
	cin >> numb;
	if (isPrime(numb))
		cout << numb << " e primo.";
	else
		cout << numb << " nao e primo.";
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
