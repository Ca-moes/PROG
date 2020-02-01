// Exercicio_4_13.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <sstream> 
#include <vector>
#include <algorithm>

using namespace std;

ifstream in_stream;    // ler do ficheiro
ofstream out_stream;   // escrever no ficheiro

int main()
{
	/* Desenvolver um programa que ordene os nomes de um conjunto de pessoas contidos num ficheiro de texto. guardando
	o resultado noutro ficheiro de texto.
		O nome do ficheiro original, com a extensão.txt, deve ser indicado pelo
		utilizador(ex: names.txt); o nome do ficheiro resultante deve ser igual ao do ficheiro original, acrescentando a
		string "_sorted" e mantendo a extensão(ex: names_sorted.txt). */

	string nometxt;
	vector<string> v1;
	cout << "Indique nome do ficheiro: ";
	cin >> nometxt;
	ifstream nomes(nometxt);

	string line;
	while (getline(nomes, line))
	{
		v1.push_back(line);
		//cout << line << endl;
	}
	sort(v1.begin(), v1.end());
	nomes.close();

	ofstream outtxt("names_sorted.txt");
	for (int i = 0; i < v1.size(); i++)
	{
		outtxt << v1[i] << endl;
		//cout << i << " " << v1[i] << endl;
	}
	outtxt.close();


	
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
