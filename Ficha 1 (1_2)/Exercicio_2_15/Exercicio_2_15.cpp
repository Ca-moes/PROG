// Exercicio_2_15.cpp : This file contains the 'main' function. Program execution begins and ends there.
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


int main()
{
	srand(time(NULL));
	double t1, t2, n1 = (rand() / 1000) % 10, n2 = (rand() / 1000) % 10, resultado = 0;
	int valor = 0;
	while (n1 < 2) n1 = (rand() / 1000) % 10;
	while (n2 < 2) n2 = (rand() / 1000) % 10;

	cout << "Qual e o resultado de " << n1 << " * " << n2 << " ?\t";
	t1 = time(NULL);
	cin >> valor;
	t2 = time(NULL);
	cout << "Resultado: " << n1 * n2 << "\nValor de input: " << valor << "\nIntervalo de tempo: " << t2 - t1;
	cout << endl;
	if (valor != n1 * n2)
		cout << "Errou, muito mau.";
	else
	{
		if (t2 - t1 < 5)
			cout << "Bom";
		if (t2 - t1 <= 10 && t2 - t1 >=5)
			cout << "Satisfaz";
		if (t2 - t1 > 10)
			cout << "Insuficiente";
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
