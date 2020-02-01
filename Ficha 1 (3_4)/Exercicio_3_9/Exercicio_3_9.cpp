// Exercicio_3_9.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

double f1(double x)
{
	return x * x;
}
double f2(double x)
{
	return sqrt(4-x*x);
}
double integrateTR(double f(double), double a, double b, int n) 
{
	// f ,a, b e n   e dá return ao valor do integral
	double soma = 0, h = (b - a) / n;
	for (int i = 1; i <= n; i++)
	{
		soma = soma + ((h / 2)*(f(a + (i - 1)*h) + f(a + i * h)));
	}
	return soma;
}


int main()
{
    // n regioes = n trapezios
	// largura de cada regiao/trapezio : h=(b-a)/n
	// area do i-esimo trapezio: (h/2) * (f(a+(i-1)*h) + f(a + ih))

	for (int i = 1;i <= 7;i++)
	{
		cout << "Integral de x^2 com n = " << i << " : " << integrateTR(f1, 0, 10, pow(2,i)) << endl ;
	}
	cout << endl;
	for (int i = 1;i <= 7;i++)
	{
		cout << "Integral de raiz(4-x^2) com n = " << i << " : " << integrateTR(f2, -2, 2, pow(2,i)) << endl;
	}

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
