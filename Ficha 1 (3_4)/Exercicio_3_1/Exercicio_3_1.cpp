// Exercicio_3_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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


double distance(double x1, double y1, double x2, double y2)
{ // calcular a distância entre dois pontos cujas coordenadas são (x1, y1) e(x2, y2)

	return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

double area(double x1, double y1, double x2, double y2, double x3, double y3) 
{ // calcular a área de um triângulo cujos vértices têm coordenadas (x1,y1), (x2,y2) e (x3,y3)

	double sperimetro = 0;
	sperimetro = (distance(x1, y1, x2, y2) + distance(x2, y2, x3, y3) + distance(x3, y3, x1, y1)) /2 ;
	return sqrt(sperimetro * (sperimetro - distance(x1, y1, x2, y2)) * (sperimetro - distance(x2, y2, x3, y3)) * (sperimetro - distance(x3, y3, x1, y1)));
}



int main()
{
	double va1, va2, vb1, vb2, vc1, vc2;
	cout << "Coordenadas do 1o vértice: ";
	cin >> va1 >> va2;
	cout << "Coordenadas do 2o vértice: ";
	cin >> vb1 >> vb2;
	cout << "Coordenadas do 3o vértice: ";
	cin >> vc1 >> vc2;

	cout << "A area do triangulo = " << area(va1, va2, vb1, vb2, vc1, vc2);

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
