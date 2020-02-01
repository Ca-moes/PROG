// Projecto_1_TESTES.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
#include <regex>
using namespace std;

ofstream file1;// escreve para ficheiro
ifstream file2;// lê do ficheiro

//struct Clientstest
//{
//	vector<string> names;
//	vector<long int> nif;
//	vector<int> numfamily;
//	struct ClientsAddress
//	{
//		vector<string> streetCA;
//		vector<int> numdoorCA;
//		vector<char> numfloorCA;  // pode ser num ou "-"
//		vector<string> postcodeCA; // tem um "-" no meio
//		vector<string> stateCA;  // localidade
//	};
//	vector<string> boughtpacks;
//};  // um vector para cada elemento do struct, cada cliente corresponde a um indice;
//Clientstest clients;
//
//struct Packs2
//{
//	int lastpack;
//	vector<int> identifier;
//	struct StartDate
//	{
//		vector<int> yearSD;
//		vector<int> monthSD;
//		vector<int> daySD;
//	};
//	struct EndDate
//	{
//		vector<int> yearED;
//		vector<int> monthED;
//		vector<int> dayED;
//	};
//	vector<int> price;  //preço por pessoa
//	vector<int> seatsavailable;
//	vector<int> seatssold;
//};
//Packs2 packs;
//
//
//struct subject {
//	string name;
//	int marks;
//	int credits;
//};
int validnif(string testnif) {
	// 1 nif valido			0 nao e valido
	int counter = 9, sum = 0;
	char lastchar = testnif[8];
	int last = lastchar - '0';

	for (unsigned int i = 0; i < testnif.length() - 1; i++)
	{
		sum = sum + testnif[i] * counter;
		counter--;
	}
	counter = sum % 11;
	if (counter == 0 || counter == 1)
	{
		if (last == 0)
			return 1;
	}
	counter = 11 - counter;
	if(last != counter)
		return 0;
	return 1;
}
int checkinputnif(string &test) {
	// 0 - tá bom
	// 1 - não tá bom
	// 2 - já existe cliente 
	do {
		getline(cin, test);
	} while (test.length() == 0);
	test = regex_replace(test, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
	if (test.length() != 9)
		return 1;
	for (unsigned int i = 0; i < test.length(); i++)
	{
		if (!isdigit(test[i]) || test[i] == ' ')
			return 1;
	}
	// check if it already exists
	if (!validnif(test))
		return 1;
	//for (unsigned int i = 0; i < ClientsList.size(); i++)
	//{
	//	if (stoi(test) == ClientsList[i].nif)
	//		return 2;
	//}
	return 0;
}
int main() {
	cout << "Hello World!" << endl;
	int test; string input;
	do {
		cout << "Client's NIF: ";
		test = checkinputnif(input);
	} while (test == 1);




	////Push back new subject created with default constructor.
	//sub.push_back(subject());

	////Vector now has 1 element @ index 0, so modify it.
	//sub[0].name = "english";

	////Add a new element if you want another:
	//sub.push_back(subject());

	////Modify its name and marks.
	//sub[1].name = "math";
	//sub[1].marks = 90;
}

