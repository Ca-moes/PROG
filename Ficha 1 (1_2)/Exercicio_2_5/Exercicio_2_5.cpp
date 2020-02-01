// Exercicio_2_5.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	double a, b, c, resultado;
	cout << "ax^2 + bx + c = 0 " << endl;
	cout << "b^2 - 4ac  >= 0 para ter solucao" << endl;
	cout << "Introduza os coeficientes (a b c): ";
	cin >> a >> b >> c;
	if (pow(b, 2) - 4 * a*c > 0)
		cout << "A equacao tem 2 raizes reais diferentes: " << (-b + sqrt(pow(b, 2) - 4 * a*c)) / (2 * a) << " e " << (-b - sqrt(pow(b, 2) - 4 * a*c)) / (2 * a);
	if ( pow(b, 2) - 4 * a*c == 0)
		cout << "A equacao tem 2 raizes reais iguais: " << -b / (2 * a);
	if (pow(b, 2) - 4 * a*c < 0)
		cout << setprecision(3) << "A equacao tem 2 raiz complexas conjugadas: " << -b / (2*a) << "+" << (sqrt((pow(b, 2) - 4 * a*c) * -1))/(2*a) << "i e " << -b / (2 * a) << "-" << (sqrt((pow(b, 2) - 4 * a*c) * -1)) / (2 * a) << "i";

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
