// Exercicio_3_5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <stdlib.h> // atoi() accepts string - converts to int
#include <iomanip> // format manipulators
#include <fstream> // file I/O
#include <string> // standard C++ strings
#include <cstring> // strings em C - arrays de chars
#include <cmath> // math functions
#include <climits> // various properties of the various variable types  
#include <cfloat> // various platform-dependent constants related to floating point values
#include <ctime> // função time(), que retorna o número de segundos que decorreram desde as zero horas do dia 1 / Jan / 1970
using namespace std;

/*///////////////////////////////////////

IMCOMPLETO MAS FEITO EM 4.5

///////////////////////////////////////*/

int gcd(int a, int b) {
	int q = 0;
	int r = 0;
	/*   b = qa + r   */
	do {
		q = b / a;
		r = b % a;
		b = a;
		if (r) a = r;
	} while (r != 0);
	return a;
}
// finds greatest common divisor between a and b;
bool readFracc(int &numerator, int &denominator)
{
	/*O valor de retorno da função deve ser true caso os valores introduzidos para o numerador e para o
	denominador sejam válidos e o separador também seja válido, isto é '/', e false no caso contrário.*/
	bool checknum = false, checkden = false, checkmiddle = false;
	string intro = "a";
	cin >> intro;
	int barrapos = intro.find("/");
	if (barrapos == -1)
		return false;
	string n1 = intro.substr(0, barrapos), n2 = intro.substr(barrapos + 1, intro.length() - barrapos);
	bool check1 = true, check2 = true;
	for (int i = 0; i < n1.length(); i++)
	{
		if (isalpha(n1[i]) != 0) {
			check1 = false;
			break;
		}
	}
	for (int i = 0; i < n2.length(); i++)
	{
		if (isalpha(n2[i]) != 0) {
			check2 = false;
			break;
		}
	}
	if (check1 == 0 || check2 == 0)
		return false;

	numerator = stoi(n1);
	denominator = stoi(n2);
	return true;

}
// returns true case: numerator, / and deominator are accepted and refreshes num and den values
void writeFracc(int numerator, int denominator) {
	cout << numerator << "/" << denominator << endl;
}
// writes fraction on screen
void reduceFracc(int &numerator, int &denominator) {
	int divisor = gcd(numerator, denominator);
	numerator = numerator / divisor;
	denominator = denominator / divisor;
}
// reduces fraction
void main(void)
{
	int numerator = 0, denominator = 0;
	cout << "Insira funcao do genero \"N/D\" (e.g. 2/3): ";
	cout << readFracc(numerator, denominator) << endl;
	if (true)
	{

	}
	writeFracc(numerator, denominator);
	reduceFracc(numerator, denominator);
	writeFracc(numerator, denominator);
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
