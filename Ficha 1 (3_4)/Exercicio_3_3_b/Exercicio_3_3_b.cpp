// Exercicio_3_3_a.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <iomanip> // format manipulators
#include <fstream> // file I/O
#include <string> // standard C++ strings
#include <cmath> // math functions
#include <climits> // various properties of the various variable types  
#include <cfloat> // various platform-dependent constants related to floating point values
#include <ctime> // fun��o time(), que retorna o n�mero de segundos que decorreram desde as zero horas do dia 1 / Jan / 1970
using namespace std;
#define PI 3.14159265

double n = 0;
double Heron(double delta, int nMaxIter)
{	// Calcula sqrt de n por algoritmo de Heron de Alexandria
	double dif = 0, rqn = 0, rq = 1;
	int nIter = 0, counter = 0;
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
	return rq;
}


int main()
{
	double delta;
	int nMaxIter;
	cout << "Insira n, delta & numero Max de Iteracoes: ";
	cin >> n >> delta >> nMaxIter;

	cout << "sqrt de Heron do num " << n << " = " << Heron(delta, nMaxIter) << endl;
	cout << "sqrt de biblio do num " << n << " = " << sqrt(n) << "\nDiferenca = " << Heron(delta, nMaxIter) - sqrt(n);
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
