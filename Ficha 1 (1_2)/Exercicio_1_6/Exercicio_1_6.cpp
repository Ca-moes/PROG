// Exercicio_1_6.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	//área sqrt( s(s - a)(s - b)(s - c))    s:semi-perimetro
	//comp1: a->b ; comp1: b->c ; comp1: c->a  
	double va1, va2, vb1, vb2, vc1, vc2, comp1, comp2, comp3, sperimetro, area;
	cout << "Coordenadas do 1o vértice: ";
	cin >> va1 >> va2;
	cout << "Coordenadas do 2o vértice: ";
	cin >> vb1 >> vb2;
	cout << "Coordenadas do 3o vértice: ";
	cin >> vc1 >> vc2;
	comp1 = sqrt(pow(vb1 - va1, 2) + pow(vb2 - va2, 2));
	comp2 = sqrt(pow(vc1 - vb1, 2) + pow(vc2 - vb2, 2));
	comp3 = sqrt(pow(va1 - vc1, 2) + pow(va2 - vc2, 2));
	sperimetro = (comp1 + comp2 + comp3) / 2.0;
	
	//cout << comp1 << " " << comp2 << " " << comp3 << endl;
	//cout << sperimetro << endl;

	area = sqrt(sperimetro * (sperimetro - comp1) * (sperimetro - comp2) * (sperimetro - comp3));
	cout << "A area do triangulo = " << area;
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
