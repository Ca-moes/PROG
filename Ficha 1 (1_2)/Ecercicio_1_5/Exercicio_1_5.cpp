// Ecercicio_1_5.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
	int seg1, min1, hor1, seg2, min2, hor2, segundos, minutos, horas, dias;
	cout << "Tempo 1 (horas minutos segundos) ? ";
	cin >> hor1 >> min1 >> seg1;
	cout << "Tempo 2 (horas minutos segundos) ? ";
	cin >> hor2 >> min2 >> seg2;

	segundos = (seg1 + seg2) % 60;
	minutos = (min1 + min2) % 60 + ((seg1 + seg2) / 60) ;
	horas = (hor1 + hor2 + ((min1 + min2) / 60))%24;
	dias = ((hor1 + hor2) + ((min1 + min2) / 60)) / 24;

	cout << "Soma dos tempos: " << dias << " dia(s), " << horas << " horas, " << minutos << " minutos e " << segundos << " segundos;" << endl;

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
