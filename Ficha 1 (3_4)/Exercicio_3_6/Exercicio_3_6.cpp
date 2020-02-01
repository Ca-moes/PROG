// Exercicio_3_6.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

string numtomes(int mes) {
	switch (mes)
	{
	case 1:
		return "Janeiro";
	case 2:
		return "Fevereiro";
	case 3:
		return "Marco";
	case 4:
		return "Abril";
	case 5:
		return "Maio";
	case 6:
		return "Junho";
	case 7:
		return "Julho";
	case 8:
		return "Agosto";
	case 9:
		return "Setembro";
	case 10:
		return "Outubro";
	case 11:
		return "Novembro";
	case 12:
		return "Dezembro";
	}
}
// converts 1-12 to January-December
bool a_bissexto(int ano) {
	// devolve true se o ano for bissexto
	if (ano % 400 == 0)
		return true;
	if (ano % 4 == 0 && ano % 10 != 0)
		return true;
	return false;
}  // Return true if year is a leap year
// Return true if year is a leap year.
int b_numdias(int ano, int mes) {
	if (mes == 1 || mes == 4 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
		return 31;
	if (mes == 3 || mes == 6 || mes == 9 || mes == 11)
		return 30;
	if (mes == 2) {
		if (a_bissexto(ano))
			return 29;
		else
			return 28;
	}
}
// Return number of days given month and year.
int c_codigo(int ano, int mes) {
	switch (mes)
	{
	case 1:
		if (a_bissexto(ano))
			return 6;
		else
			return 0;
	case 2:
		if (a_bissexto(ano))
			return 2;
		else
			return 3;
	case 3:
		return 3;
	case 4:
		return 6;
	case 5:
		return 1;
	case 6:
		return 4;
	case 7:
		return 6;
	case 8:
		return 2;
	case 9:
		return 5;
	case 10:
		return 0;
	case 11:
		return 3;
	case 12:
		return 5;
	}
}
// Determines code according to month
int c_diasemana(int ano, int mes, int dia) {
	// ds = (floor(5*a/4.0) + c + d - 2*(s%4) + 7) % 7
	// a = dois ultimos digitos do ano   ( 2010 -> 10 )
	// c = codigo do mês -> ver tabela (depende de m - int correspondente do mes & de ser ano bissexto)
	// d = dia do mês
	// s = dois primeiros digitos do ano ( 2010 -> 20 )
	int a = ano % 100, s = ano / 100, d = dia, c = c_codigo(ano, mes);
	int ds = (floor(5 * a / 4) + c + d - 2 * (s % 4) + 7);
	return ds % 7;
}
// return 0-6; 0-Sábado, 1-Domingo, 2-Segunda-Feira
string c_nomedia(int dia) {
	switch (dia)
	{
	case 0:
		return "Sabado";
		break;
	case 1:
		return "Domingo";
		break;
	case 2:
		return "Segunda-feira";
		break;
	case 3:
		return "Terca-feira";
		break;
	case 4:
		return "Quarta-feira";
		break;
	case 5:
		return "Quinta-feira";
		break;
	case 6:
		return "Sexta-feira";
		break;
	}
}
// converts 0-6 to a string and returns it
char d_calendario(int ano, int mes) {

	int shifts = 0, dia = 1;
	cout << endl;
	cout << numtomes(mes) << "/" << ano;
	cout << "\nDom\tSeg\tTer\tQua\tQui\tSex\tSab\n";
	if (c_diasemana(ano, mes, dia) == 0)
		shifts = 5;
	else
		shifts = c_diasemana(ano, mes, dia) - 2;
	int counterlinha = 0, counterresta = (b_numdias(ano, mes) - 1), counterdias = 2;

	switch (shifts)
	{
	case -1:
		counterlinha = 6;
		break;
	case 0:
		counterlinha = 5;
		break;
	case 1:
		counterlinha = 4;
		break;
	case 2:
		counterlinha = 3;
		break;
	case 3:
		counterlinha = 2;
		break;
	case 4:
		counterlinha = 1;
		break;
	case 5:
		counterlinha = 0
			;
		break;
	default:
		break;
	}

	for (int i = 0; i <= shifts; i++)
		cout << "\t";
	cout << "1";

	bool saltarlinha = false;
	if (counterlinha == 0)
		saltarlinha = true;

	while (counterresta != 0)
	{
		if (saltarlinha)
		{
			cout << "\n" << counterdias;
			counterlinha = 6;
			saltarlinha = false;
		}
		else {
			cout << "\t" << counterdias;
			counterlinha--;
		}

		counterdias++;
		counterresta--;

		if (counterlinha == 0)
			saltarlinha = true;

		if (counterresta == 0)
			break;
	}

	return '\n';
}
// devolve um calendário dado um ano e mes
char e_fullcalendario(int ano)
{
	for (int i = 1; i <= 12; i++)
	{
		d_calendario(ano, i);
		cout << endl;
	}
	return NULL;
}

int main()
{
	// ano bissexto -> divisel por 4 e não por 100, ou divisivel por 400
	int mes = 0, ano = 0;
	cout << "Insere um ano: ";
	cin >> ano;
	cout << e_fullcalendario(ano);
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
