// Projecto_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
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

struct Agency
{
	string name;
	unsigned long int nif;
	string url;
	struct AgencyAddress // AA -> AgencyAddress
	{
		string street;
		unsigned int numdoor;
		string numfloor;  // pode ser num ou "-"
		string postcode; // tem um "-" no meio
		string state;  // localidade
	};
	AgencyAddress address;
	string clientsfile;
	string packsfile;
};
struct Clients
{
	string name;
	unsigned long int nif;
	unsigned int household;
	struct ClientsAddress
	{
		string street;
		unsigned int numdoor;
		string numfloor;  // pode ser string (5Esq) ou "-"
		string postcode; // tem um "-" no meio
		string state;  // localidade
	};
	ClientsAddress address;
	vector<unsigned int> boughtpacks;
};
struct Packs
{
	int identifier;
	string princplace;
	struct StartDate
	{
		unsigned int year;
		unsigned int month;
		unsigned int day;
	};
	StartDate startdate;
	struct EndDate
	{
		unsigned int year;
		unsigned int month;
		unsigned int day;
	};
	EndDate enddate;
	unsigned int price;  //preço por pessoa
	unsigned int seatsavailable;
	unsigned int seatssold;
};
Agency agency;
vector<Clients> ClientsList;
vector<Packs> PacksList;
unsigned int packs_lastpack = 0;

// From files to Mem
void AgencyAddressToMem(string line) {
	string tempdata = "";
	int counter = 1;
	for (unsigned int i = 0; i < line.length(); i++)
	{
		if (line[i] != '/')
			tempdata += line[i];
		else
		{
			switch (counter)
			{
			case 1:
				tempdata = regex_replace(tempdata, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
				agency.address.street = tempdata;
				break;
			case 2:
				tempdata = regex_replace(tempdata, regex("^ +| +$|( ) +"), "$1");
				agency.address.numdoor = stoi(tempdata);
				break;
			case 3:
				tempdata = regex_replace(tempdata, regex("^ +| +$|( ) +"), "$1");
				agency.address.numfloor = tempdata;
				break;
			case 4:
				tempdata = regex_replace(tempdata, regex("^ +| +$|( ) +"), "$1");
				agency.address.postcode = tempdata;
				break;
			default:
				break;
			}
			tempdata = "";
			counter++;
		}
	}
	tempdata = regex_replace(tempdata, regex("^ +| +$|( ) +"), "$1");
	agency.address.state = tempdata;
}
void AgencyToMem(string agencychoice) {
	/*
	Open agency file
	Read Line by line
	update struct Agency
	*/
	int numline = 0;
	string line;
	ifstream agencyfile(agencychoice + ".txt");
	while (getline(agencyfile, line))
	{
		numline++;
		//cout << "linha numero " << numline << "   conteudo: " << line << endl;
		switch (numline)
		{
		case 1:
			line = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			agency.name = line;
			break;
		case 2:
			line = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			agency.nif = stol(line);
			break;
		case 3:
			line = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			agency.url = line;
			break;
		case 4:
			AgencyAddressToMem(line);
			break;
		case 5:
			line = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			agency.clientsfile = line;
			break;
		case 6:
			line = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			agency.packsfile = line;
			break;
		default:
			break;
		}
	}
	agencyfile.close();
}
void ClientsAddressToMem(string line, int counterclient) {
	string tempdata = "";
	int counter = 1;
	for (unsigned int i = 0; i < line.length(); i++)
	{
		if (line[i] != '/')
			tempdata += line[i];
		else
		{
			switch (counter)
			{
			case 1:
				tempdata = regex_replace(tempdata, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
				ClientsList[counterclient].address.street = tempdata;
				break;
			case 2:
				tempdata = regex_replace(tempdata, regex("^ +| +$|( ) +"), "$1");
				ClientsList[counterclient].address.numdoor = stoi(tempdata);
				break;
			case 3:
				tempdata = regex_replace(tempdata, regex("^ +| +$|( ) +"), "$1");
				ClientsList[counterclient].address.numfloor = tempdata;
				break;
			case 4:
				tempdata = regex_replace(tempdata, regex("^ +| +$|( ) +"), "$1");
				ClientsList[counterclient].address.postcode = tempdata;
				break;
			default:
				break;
			}
			tempdata = "";
			counter++;
		}
	}
	tempdata = regex_replace(tempdata, regex("^ +| +$|( ) +"), "$1");
	ClientsList[counterclient].address.state = tempdata;
	/*cout << endl << "Para client n " << counterclient << " temos os seguintes dados de morada:" << endl;
	cout << "Street : " << ClientsList[counterclient].address.street << endl;
	cout << "Door Number : " << ClientsList[counterclient].address.numdoor << endl;
	cout << "Floor Number : " << ClientsList[counterclient].address.numfloor << endl;
	cout << "Post Code : " << ClientsList[counterclient].address.postcode << endl;
	cout << "State : " << ClientsList[counterclient].address.state << endl << endl;*/
}
void ClientsPacksToMem(string line, int counterclient) {
	string tempdata = "";
	int counter = 0;
	//cout << "line lenght: " << line.length() << endl;
	for (unsigned int i = 0; i < line.length(); i++)
	{
		//cout << tempdata << endl;
		if (line[i] != ';')
			tempdata += line[i];
		else
		{
			tempdata = regex_replace(tempdata, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			ClientsList[counterclient].boughtpacks.push_back(stoi(tempdata));
			tempdata = "";
		}
	}
	tempdata = regex_replace(tempdata, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
	ClientsList[counterclient].boughtpacks.push_back(stoi(tempdata));
}
void ClientsToMem(string agencychoice) {
	string clientstxt = agency.clientsfile;
	int linecounter = 1, counterclient = 0;
	bool createclient = true;
	string line;
	ifstream clientsfile(clientstxt);
	while (getline(clientsfile, line))
	{
		if (createclient) {

			ClientsList.push_back(Clients());
			createclient = false;
		}

		if (line == "::::::::::")
		{
			createclient = true;
			counterclient++;
			linecounter = 1;
			continue;
		}

		switch (linecounter)
		{
		case 1:
			line = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			ClientsList[counterclient].name = line;
			break;
		case 2:
			line = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			ClientsList[counterclient].nif = stol(line);
			break;
		case 3:
			line = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			ClientsList[counterclient].household = stoi(line);
			break;
		case 4:
			ClientsAddressToMem(line, counterclient);
			break;
		case 5:
			//cout << "Linha de pacotes comprados " << line << endl;
			ClientsPacksToMem(line, counterclient);
			break;
		default:
			break;
		}
		linecounter++;
	}

}
void PacksStartDateToMem(string line, int index) {
	string tempdata = "";
	int counter = 1;
	bool year = false;
	for (unsigned int i = 0; i < line.length(); i++)
	{
		if (line[i] != '/')
			tempdata += line[i];
		else
		{
			if (!year) {
				tempdata = regex_replace(tempdata, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
				PacksList[index].startdate.year = stoi(tempdata);
				year = true;
			}
			else
			{
				tempdata = regex_replace(tempdata, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
				PacksList[index].startdate.month = stoi(tempdata);
			}
			tempdata = "";
		}
	}
	tempdata = regex_replace(tempdata, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
	PacksList[index].startdate.day = stoi(tempdata);
}
void PacksEndDateToMem(string line, int index) {
	string tempdata = "";
	int counter = 1;
	bool year = false;
	for (unsigned int i = 0; i < line.length(); i++)
	{
		if (line[i] != '/')
			tempdata += line[i];
		else
		{
			if (!year) {
				tempdata = regex_replace(tempdata, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
				PacksList[index].enddate.year = stoi(tempdata);
				year = true;
			}
			else
			{
				tempdata = regex_replace(tempdata, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
				PacksList[index].enddate.month = stoi(tempdata);
			}
			tempdata = "";
		}
	}
	tempdata = regex_replace(tempdata, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
	PacksList[index].enddate.day = stoi(tempdata);
}
void PacksToMem(string agencychoice) {
	string packstxt = agency.packsfile;
	int linecounter = 1, counterpack = 0;
	bool createpack = true, readlastpack = true;
	string line;
	ifstream packsfile(packstxt);
	while (getline(packsfile, line))
	{
		//cout << line << endl;
		if (readlastpack)
		{
			packs_lastpack = stoi(line);
			readlastpack = false;
			continue;
		}
		if (createpack) {
			PacksList.push_back(Packs());
			createpack = false;
		}
		if (line == "::::::::::")
		{
			createpack = true;
			counterpack++;
			linecounter = 1;
			continue;
		}

		switch (linecounter)
		{
		case 1:
			line = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			PacksList[counterpack].identifier = stoi(line);
			linecounter++;
			break;
		case 2:
			PacksList[counterpack].princplace = line;
			linecounter++;
			break;
		case 3:
			PacksStartDateToMem(line, counterpack);
			linecounter++;
			break;
		case 4:
			PacksEndDateToMem(line, counterpack);
			linecounter++;
			break;
		case 5:
			PacksList[counterpack].price = stoi(line);
			linecounter++;
			break;
		case 6:
			PacksList[counterpack].seatsavailable = stoi(line);
			linecounter++;
			break;
		case 7:
			PacksList[counterpack].seatssold = stoi(line);
			linecounter++;
			break;
		default:
			break;
		}
	}

	//cout << "lastpack = " << packs_lastpack << endl;
}

/////////////Manage Clients///////////////////////
void showClientData(Clients client) {
	cout << "Name ------------------------- " << client.name << endl;
	cout << "NIF -------------------------- " << client.nif << endl;
	cout << "Household size --------------- " << client.household << endl;
	cout << "Address: " << endl;
	cout << "                 Street ------ " << client.address.street << endl;
	cout << "            Door Number ------ " << client.address.numdoor << endl;
	cout << "           Floor Number ------ " << client.address.numfloor << endl;
	cout << "              Post Code ------ " << client.address.postcode << endl;
	cout << "                  State ------ " << client.address.state << endl;
	cout << "Number of packs -------------- " << client.boughtpacks.size() << endl;
	if (client.boughtpacks[0] != 0)
	{
		cout << "Pack's Identifiers ----------- ";
		for (unsigned int i = 0; i < client.boughtpacks.size(); i++)
		{
			if (i == client.boughtpacks.size() - 1)
			{
				cout << client.boughtpacks[i] << endl;
				continue;
			}
			cout << client.boughtpacks[i] << " ; ";
		}
	}
}
int checkinputname_street_state(string &test) {
	// 0 - tá bom
	// 1 - não tá bom
	do {
		getline(cin, test);
	} while (test.length() == 0);
	if (test.length() == 1)
		return 1;
	test = regex_replace(test, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
	if (test == "")
		return 1;
	for (unsigned int i = 0; i < test.length(); i++)
	{
		if (!isalpha(test[i]) && test[i] != ' ')
			return 1;
	}
	return 0;
}
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
	if (last != counter)
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
		return 3;
	for (unsigned int i = 0; i < ClientsList.size(); i++)
	{
		if (stoi(test) == ClientsList[i].nif)
			return 2;
	}
	return 0;
}
int checkinputhousehold(string &test) {
	do {
		getline(cin, test);
	} while (test.length() == 0);
	test = regex_replace(test, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
	if (test.length() != 1)
		if (test.length() != 2)
			return 1;
	if (!isdigit(test[0]) && !isdigit(test[1]))
		return 1;
	if (stoi(test) < 1)
		return 1;
	return 0;
}
int checkinputfloornumber(string &test) {
	do {
		getline(cin, test);
	} while (test.length() == 0);
	test = regex_replace(test, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
	if (test.length() != 1 && test.length() != 4)
		return 1;
	if (test.length() == 1) {
		if (!isdigit(test[0])) // não for digito
		{
			if (test[0] != '-') // não for -
			{
				return 1;
			}
		}
	}
	if (test.length() == 4)
	{
		if (!isdigit(test[0])) // não for digito
			return 1;
		string temp = "";
		temp = test[1];
		temp = temp + test[2];
		temp = temp + test[3];
		if (temp != "Dir" && temp != "Esq" && temp != "Mei")
			return 1;
	}
	return 0;
}
int checkinputnumber(string &test) {
	do {
		getline(cin, test);
	} while (test.length() == 0);
	test = regex_replace(test, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio

	for (unsigned int i = 0; i < test.length(); i++)
	{
		if (!isdigit(test[i]))
			return 1;
	}
	if (stoi(test) <= 0)
		return 1;
	return 0;
}
int checkinputpostalcode(string &test) {
	do {
		getline(cin, test);
	} while (test.length() == 0);
	test = regex_replace(test, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
	string temp = "";
	if (test.length() != 8)
		return 1;
	for (unsigned int i = 0; i < 8; i++)
	{
		if (i == 4)
		{
			if (test[i] != '-')
				return 1;
			continue;
		}

		if (!isdigit(test[i]))
			return 1;
	}
	return 0;
}
int checkinputnumpacks(string &test) {
	do {
		getline(cin, test);
	} while (test.length() == 0);
	test = regex_replace(test, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
	for (unsigned int i = 0; i < test.length(); i++)
	{
		if (!isdigit(test[i]))
			return 1;
	}
	if (stoi(test) < 0)
		return 1;
	return 0;
}
int checkinputchoice(string &test, int lowerlimit, int upperlimit) {
	// e.g. ll = 0, ul = 3 , se num < 0 || num > 3    return 1
	do {
		getline(cin, test);
	} while (test.length() == 0);
	test = regex_replace(test, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
	for (unsigned int i = 0; i < test.length(); i++)
	{
		if (!isdigit(test[i]))
			return 1;
	}
	if (stoi(test) < lowerlimit || stoi(test) > upperlimit)
		return 1;
	return 0;
}
void CreateClient() {
	int test = 0; string input = ""; int numpacks = 0;
	Clients newclient;
	do
	{
		system("cls");
		cout << "----------Create Client----------" << endl;
		do
		{
			if (test == 2)
				cout << "Cliente already exists, create another one." << endl;
			do {
				cout << "Client's Name: ";
				test = checkinputname_street_state(input);
			} while (test != 0);
			newclient.name = input;
			do {
				if (test == 3)
					cout << "Not a Valid NIF\n";
				cout << "Client's NIF: ";
				test = checkinputnif(input);
			} while (test != 0);
			newclient.nif = stol(input);
		} while (test == 2);

		do {
			cout << "Household Size: ";
			test = checkinputhousehold(input);
		} while (test != 0);
		newclient.household = stoi(input);
		do {
			cout << "Street Name: ";
			test = checkinputname_street_state(input);
		} while (test != 0);
		newclient.address.street = input;

		do {
			cout << "House's Number: ";
			test = checkinputnumber(input);
		} while (test != 0);
		newclient.address.numdoor = stoi(input);
		do { // aceita até piso 9
			cout << "(e.g. 1, 3, - , 6Esq, 9Dir, 2Mei)" << endl;
			cout << "Floor's Number: ";
			test = checkinputfloornumber(input);
		} while (test != 0);
		newclient.address.numfloor = input;
		do {
			cout << "Postal Code: ";
			test = checkinputpostalcode(input);
		} while (test != 0);
		newclient.address.postcode = input;
		do {
			cout << "State: ";
			test = checkinputname_street_state(input);
		} while (test != 0);
		newclient.address.state = input;
		do {
			cout << "How many bought packs? ";
			test = checkinputnumpacks(input);
		} while (test != 0);
		numpacks = stoi(input);
		if (stoi(input) == 0)
			newclient.boughtpacks.push_back(0);
		else
		{
			for (int i = 0; i < numpacks; i++)
			{
				do {
					cout << "Insert pack number " << i + 1 << ":";
					test = checkinputnumber(input);   // Mudar para não aceitar packs repetidos
				} while (test != 0);
				newclient.boughtpacks.push_back(stoi(input));
			}
		}

		system("cls");
		cout << "---------------- New client data ----------------" << endl << endl;
		showClientData(newclient);
		cout << endl << "Do you confirm this data?" << endl;
		cout << "1 - Yes" << endl;
		cout << "2 - No" << endl; // Com NO pergunta se quer novo cliente ou sair
		do {
			test = checkinputchoice(input, 1, 2);
		} while (test != 0);
		numpacks = stoi(input); // numpacks é uma variavel reutilizada
		if (stoi(input) == 1) {
			ClientsList.push_back(newclient);
			numpacks = 0;
		}
		system("cls");
		cout << "--------- CLIENT CREATED ---------" << endl;
		cout << "1 - New Client" << endl;
		cout << "0 - Exit" << endl;
		do {
			test = checkinputchoice(input, 0, 1);
		} while (test != 0);
		numpacks = stoi(input);   // numpacks é uma variavel reutilizada

	} while (numpacks != 0);

}

void ManageClientPacks(int index) {
	int test = 0, flagbought = 0; string input = "";
	cout << "1 - Add Packs" << endl;
	cout << "2 - Remove Packs" << endl;
	do { test = checkinputchoice(input, 1, 2); } while (test != 0);
	if (input == "1")
	{
		do {
			cout << "Number of pack to add (0 to exit)" << endl;
			test = checkinputchoice(input, 0, 50);   // Mudar para não aceitar packs repetidos
		} while (test != 0);
		if (stoi(input) != 0) {
			for (int i = 0; i < stoi(input); i++)
			{
				do
				{
					do {
						cout << "Pack number " << i + 1 << ": " << endl;
						test = checkinputnumber(input);   // Mudar para não aceitar packs repetidos
					} while (test != 0);
					// check if já está comprado
					for (unsigned int i = 0; i < ClientsList[index].boughtpacks.size(); i++)
					{
						if (stoi(input) == ClientsList[index].boughtpacks[i])
						{
							cout << "Pack já comprado" << endl;
							flagbought = 1;
						}
					}
				} while (flagbought);
				flagbought = 0;
				ClientsList[index].boughtpacks.push_back(stoi(input));
			}
		}
	}
	if (input == "2")
	{
		cout << "Packs possiveis de eliminar e numero de escolha: " << endl;
		for (unsigned int i = 0; i < ClientsList[index].boughtpacks.size(); i++)
		{
			cout << i + 1 << " - " << ClientsList[index].boughtpacks[i] << endl;
		}
		do {
			cout << "Escolha numero: ";
			test = checkinputchoice(input, 1, ClientsList[index].boughtpacks.size());
		} while (test != 0);
		ClientsList[index].boughtpacks.erase(ClientsList[index].boughtpacks.begin() + (stoi(input) - 1));

	}
}
void ManageClientsbyList() {
	int test = 0, index = 0; string input = "";
	do
	{
		system("cls");
		for (unsigned int i = 0; i < ClientsList.size(); i++)
		{
			cout << i + 1 << " - Client's Name: " << ClientsList[i].name << endl;
			cout << "Client's NIF: " << ClientsList[i].nif << endl;
		}
		do {
			cout << "Choose a number: ";
			test = checkinputchoice(input, 1, ClientsList.size());
		} while (test != 0);

		index = stoi(input) - 1;

		cout << endl << "-----Data of Client to Manage-----" << endl;
		showClientData(ClientsList[index]);
		cout << endl << "Do you want to change data in this client?" << endl;
		cout << "1 - Yes" << endl;
		cout << "2 - No" << endl; // Com NO pergunta se quer modificar outro cliente ou sair
		do { test = checkinputchoice(input, 1, 2); } while (test != 0);
		if (stoi(input) == 1)
		{
			do
			{
				system("cls");
				cout << endl << "-----Which Data to Change?-----" << endl;
				cout << "1 - Name" << endl;
				cout << "2 - NIF" << endl;
				cout << "3 - Household size" << endl;
				cout << "4 - Address" << endl;
				cout << "5 - Packs" << endl;
				do { test = checkinputchoice(input, 0, 5); } while (test != 0);
				switch (stoi(input))
				{
				case 1:
					do {
						cout << "Client's Name: ";
						test = checkinputname_street_state(input);
					} while (test != 0);
					ClientsList[index].name = input;
					break;
				case 2:
					do {
						cout << "Client's NIF: ";
						test = checkinputnif(input);
					} while (test == 1);
					ClientsList[index].nif = stol(input);
					break;
				case 3:
					do {
						cout << "Household Size: ";
						test = checkinputhousehold(input);
					} while (test == 1);
					ClientsList[index].household = stoi(input);
					break;
				case 4:
					cout << endl << "1 - Street Name" << endl;
					cout << "2 - Door Number" << endl;
					cout << "3 - Floor" << endl;
					cout << "4 - Post Code" << endl;
					cout << "5 - State" << endl;
					do { test = checkinputchoice(input, 1, 5); } while (test != 0);
					switch (stoi(input))
					{
					case 1:
						do {
							cout << "Street Name: ";
							test = checkinputname_street_state(input);
						} while (test != 0);
						ClientsList[index].address.street = input;
						break;
					case 2:
						do {
							cout << "Door Number: ";
							test = checkinputnumber(input);
						} while (test != 0);
						ClientsList[index].address.numdoor = stoi(input);
						break;
					case 3:
						do {
							cout << "(e.g. 1, 3, - , 6Esq, 9Dir, 2Mei)" << endl;
							cout << "Floor Number: ";
							test = checkinputfloornumber(input);
						} while (test != 0);
						ClientsList[index].address.numfloor = stoi(input);
						break;
					case 4:
						do {
							cout << "Post Code: ";
							test = checkinputpostalcode(input);
						} while (test != 0);
						ClientsList[index].address.postcode = stoi(input);
						break;
					case 5:
						do {
							cout << "State: ";
							test = checkinputname_street_state(input);
						} while (test != 0);
						ClientsList[index].address.state = input;
					default:
						break;
					}
					break;
				case 5:
					ManageClientPacks(index);
					break;
				default:
					break;
				}

				cout << endl << "Data Modified" << endl;
				cout << "1 - Modify another Detail" << endl;
				cout << "0 - Exit" << endl;
				do { test = checkinputchoice(input, 0, 1); } while (test != 0);
			} while (stoi(input) == 1);

		}
		cout << endl << "1 - Modify another client" << endl;
		cout << "0 - Exit" << endl;
		do { test = checkinputchoice(input, 0, 1); } while (test != 0);
		test = 3;  // Caso dê 1, não escreva nif não encontrado

	} while (stoi(input) != 0);
}
void ManageClientsbyNIF() {
	int test = 3, index = 0; string input = "";
	do
	{
		system("cls");
		do {
			if (test == 0)
				cout << "Client's NIF does not exist" << endl;
			cout << "Insert Client's NIF: ";
			test = checkinputnif(input);
		} while (test != 2);
		for (unsigned int i = 0; i < ClientsList.size(); i++)  // finds index of client's NIF
		{
			if (stol(input) == ClientsList[i].nif) {
				index = i;
				break;
			}
		}

		cout << endl << "-----Data of Client to Manage-----" << endl;
		showClientData(ClientsList[index]);
		cout << endl << "Do you want to change data in this client?" << endl;
		cout << "1 - Yes" << endl;
		cout << "2 - No" << endl; // Com NO pergunta se quer modificar outro cliente ou sair
		do { test = checkinputchoice(input, 1, 2); } while (test != 0);
		if (stoi(input) == 1)
		{
			do
			{
				system("cls");
				cout << endl << "-----Which Data to Change?-----" << endl;
				cout << "1 - Name" << endl;
				cout << "2 - NIF" << endl;
				cout << "3 - Household size" << endl;
				cout << "4 - Address" << endl;
				cout << "5 - Packs" << endl;
				do { test = checkinputchoice(input, 0, 5); } while (test != 0);
				switch (stoi(input))
				{
				case 1:
					do {
						cout << "Client's Name: ";
						test = checkinputname_street_state(input);
					} while (test != 0);
					ClientsList[index].name = input;
					break;
				case 2:
					do {
						cout << "Client's NIF: ";
						test = checkinputnif(input);
					} while (test == 1);
					ClientsList[index].nif = stol(input);
					break;
				case 3:
					do {
						cout << "Household Size: ";
						test = checkinputhousehold(input);
					} while (test == 1);
					ClientsList[index].household = stoi(input);
					break;
				case 4:
					cout << endl << "1 - Street Name" << endl;
					cout << "2 - Door Number" << endl;
					cout << "3 - Floor" << endl;
					cout << "4 - Post Code" << endl;
					cout << "5 - State" << endl;
					do { test = checkinputchoice(input, 1, 5); } while (test != 0);
					switch (stoi(input))
					{
					case 1:
						do {
							cout << "Street Name: ";
							test = checkinputname_street_state(input);
						} while (test != 0);
						ClientsList[index].address.street = input;
						break;
					case 2:
						do {
							cout << "Door Number: ";
							test = checkinputnumber(input);
						} while (test != 0);
						ClientsList[index].address.numdoor = stoi(input);
						break;
					case 3:
						do {
							cout << "(e.g. 1, 3, - , 6Esq, 9Dir, 2Mei)" << endl;
							cout << "Floor Number: ";
							test = checkinputfloornumber(input);
						} while (test != 0);
						ClientsList[index].address.numfloor = stoi(input);
						break;
					case 4:
						do {
							cout << "Post Code: ";
							test = checkinputpostalcode(input);
						} while (test != 0);
						ClientsList[index].address.postcode = stoi(input);
						break;
					case 5:
						do {
							cout << "State: ";
							test = checkinputname_street_state(input);
						} while (test != 0);
						ClientsList[index].address.state = input;
					default:
						break;
					}
					break;
				case 5:
					ManageClientPacks(index);
					break;
				default:
					break;
				}

				cout << endl << "Data Modified" << endl;
				cout << "1 - Modify another Detail" << endl;
				cout << "0 - Exit" << endl;
				do { test = checkinputchoice(input, 0, 1); } while (test != 0);
			} while (stoi(input) == 1);

		}
		cout << endl << "1 - Modify another client" << endl;
		cout << "0 - Exit" << endl;
		do { test = checkinputchoice(input, 0, 1); } while (test != 0);
		test = 3;  // Caso dê 1, não escreva nif não encontrado

	} while (stoi(input) != 0);



}
void ManageClient() {
	int test = 3; string input = "";
	system("cls");
	cout << "----------Manage Client----------" << endl;
	cout << "1 - Show list of Clients" << endl;
	cout << "2 - Insert Client NIF" << endl;
	cout << "0 - Exit" << endl;
	do {
		test = checkinputchoice(input, 0, 2);
	} while (test != 0);

	switch (stoi(input))
	{
	case 1: // lista de clients
		ManageClientsbyList();
		break;
	case 2: // escolher nif de clients
		ManageClientsbyNIF();
		break;
	default:
		break;
	}

}

void DeleteClient() {
	//ClientsList[index].boughtpacks.erase(ClientsList[index].boughtpacks.begin() + (stoi(input) - 1));  // apagar de um vector 
	int test = 0, index = 0; string input = "";
	do
	{
		system("cls");
		for (unsigned int i = 0; i < ClientsList.size(); i++)
		{
			cout << i + 1 << " - Client's Name: " << ClientsList[i].name << endl;
			cout << "Client's NIF: " << ClientsList[i].nif << endl;
		}
		do {
			cout << "Choose Number: ";
			test = checkinputchoice(input, 1, ClientsList.size());
		} while (test != 0);
		index = stoi(input) - 1;

		cout << endl << "-----Data of Client to Delete-----" << endl;
		cout << "Name: " << ClientsList[index].name << endl;
		cout << "NIF: " << ClientsList[index].nif << endl;
		cout << "Household size: " << ClientsList[index].household << endl;
		cout << "Address: " << endl;
		cout << "                 Street: " << ClientsList[index].address.street << endl;
		cout << "            Door Number: " << ClientsList[index].address.numdoor << endl;
		cout << "           Floor Number: " << ClientsList[index].address.numfloor << endl;
		cout << "              Post Code: " << ClientsList[index].address.postcode << endl;
		cout << "                  State: " << ClientsList[index].address.state << endl;
		cout << "Number of packs: " << ClientsList[index].boughtpacks.size() << endl;
		for (unsigned int i = 0; i < ClientsList[index].boughtpacks.size(); i++)
		{
			if (i == ClientsList[index].boughtpacks.size() - 1)
			{
				cout << ClientsList[index].boughtpacks[i] << endl;
				continue;
			}
			cout << ClientsList[index].boughtpacks[i] << " ; ";
		}

		cout << endl << "Do you want to delete this client?" << endl;
		cout << "1 - Yes" << endl;
		cout << "2 - No" << endl; // Com NO pergunta se quer modificar outro cliente ou sair
		do { test = checkinputchoice(input, 1, 2); } while (test != 0);
		if (stoi(input) == 1)
		{
			ClientsList.erase(ClientsList.begin() + index);
			cout << "Client Deleted" << endl << endl;
		}
		do {
			cout << "1 - Choose Client" << endl;
			cout << "0 - Exit" << endl;
			test = checkinputchoice(input, 0, 1);
		} while (test != 0);
	} while (stoi(input) != 0);
}

void ViewClientInfo() {
	int test = 0, index = 0; string input = "";
	do
	{
		system("cls");
		cout << "--------------------- Clients List ---------------------\n\n";
		for (unsigned int i = 0; i < ClientsList.size(); i++)
		{
			cout << i + 1 << " - Client's Name: " << ClientsList[i].name << endl;
			cout << "Client's NIF: " << ClientsList[i].nif << endl << endl;
		}
		do {
			cout << "Choose Number: ";
			test = checkinputchoice(input, 1, ClientsList.size());
		} while (test != 0);
		index = stoi(input) - 1;
		system("cls");
		cout << "---------- Data of Selected Client ----------\n" << endl;
		showClientData(ClientsList[index]);

		cout << endl << "Do you want to see another client's data?" << endl;
		cout << "1 - Yes" << endl;
		cout << "2 - No" << endl; // Com NO pergunta se quer modificar outro cliente ou sair
		do { test = checkinputchoice(input, 1, 2); } while (test != 0);
	} while (stoi(input) == 1);
}
////////////////////////////////////////////////
/////////////Manage Packs///////////////////////
void ShowPackInfo(Packs pack) {
	cout << "Identifier ______________________________  " << pack.identifier << endl;
	cout << "Main Destiny ____________________________  " << pack.princplace << endl;
	cout << "Start Date ______________________________  " << pack.startdate.day << "/" << pack.startdate.month << "/" << pack.startdate.year << endl;
	cout << "End Date ________________________________  " << pack.enddate.day << "/" << pack.enddate.month << "/" << pack.enddate.year << endl;
	cout << "Price ___________________________________  " << pack.price << endl;
	cout << "Seats available (before selling) ________  " << pack.seatsavailable << endl;
	cout << "Seats sold ______________________________  " << pack.seatssold << endl << endl;
}
bool a_bissexto(int ano) {
	// devolve true se o ano for bissexto
	if (ano % 400 == 0)
		return true;
	if (ano % 4 == 0 && ano % 10 != 0)
		return true;
	return false;
}
int checkinputidentifier(string &input) {
	int ident = 0;
	if (checkinputnumber(input) == 0) {
		for (unsigned int i = 0; i < PacksList.size(); i++)
		{
			if (PacksList[i].identifier < 0)
				ident = PacksList[i].identifier * (-1);
			else
				ident = PacksList[i].identifier;

			if (stoi(input) == ident && PacksList[i].identifier < 0)
				return 3;  // found identifier with same number as input but pack is unavailable
			if (stoi(input) == ident && PacksList[i].identifier > 0)
				return 1; // found identifier with same number as input
		}
		return 0; // input doenst correspond to any identifier
	}
	else
		return 2;  // invalid input
}
int checkinputday(string &input, int month, int year) {
	// 31 - 1 3 5 7 8 10 12 
	// 30 - 4 6 9 11
	// 28/29 - 2
	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		return checkinputchoice(input, 1, 31);
	if (month == 4 || month == 6 || month == 9 || month == 11)
		return checkinputchoice(input, 1, 30);
	if (month == 2)
	{
		if (a_bissexto(year))
			return checkinputchoice(input, 1, 29);
		else
			return checkinputchoice(input, 1, 28);
	}
	return 0;
}
int checkinputenddateyear(string &input, Packs newpack) {
	if (stoul(input) < newpack.startdate.year)
		return 1;
	return 0;
}
int checkinputenddatemonth(string &input, Packs newpack) {
	if (newpack.enddate.year == newpack.startdate.year)
	{
		if (stoul(input) < newpack.startdate.month)
			return 1;
	}
	return 0;
}
int checkinputenddateday(string &input, Packs newpack) {
	if (newpack.enddate.year == newpack.startdate.year)
	{
		if (newpack.enddate.month == newpack.startdate.month)
		{
			if (stoul(input) < newpack.startdate.day)
			{
				return 1;
			}
		}
	}
	return 0;
}
int checkinputmaindestiny(string &input) {
	// 0 - tá bom
	// 1 - não tá bom
	do {
		getline(cin, input);
	} while (input.length() == 0);
	if (input.length() == 1)
		return 1;
	input = regex_replace(input, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
	if (input == "")
		return 1;
	for (unsigned int i = 0; i < input.length(); i++)
	{
		if (!isalpha(input[i]) && input[i] != ' ' && input[i] != '-' && input[i] != ',')
			return 1;
	}
	return 0;
}
void CreatePack() {
	Packs newpack;
	int test = 0, continuar = 0, temp = 0; string input = "";
	do
	{
		system("cls");
		cout << "----------Create Pack----------" << endl;
		do {
			if (test == 1)
				cout << "Identifier already in use" << endl;
			if (test == 2)
				cout << "Invalid input" << endl;
			cout << "Identifier: ";
			test = checkinputidentifier(input);
		} while (test != 0);
		newpack.identifier = stoi(input);
		/*do {
			cout << "Is the new pack available? " << endl << "1 - Yes" << endl << "2 - No" << endl;
			test = checkinputchoice(input, 1, 2);
		} while (test != 0);
		if (input == "2")
			newpack.identifier = newpack.identifier * (-1);*/
		do {
			cout << "Pack's Main Destiny Name: ";
			test = checkinputmaindestiny(input);
		} while (test != 0);
		newpack.princplace = input;

		do
		{
			if (temp != 0) {
				cout << "Invalid Dates" << endl;
				temp = 0;
			}
			do
			{
				if (temp != 0) {
					cout << "Invalid Dates" << endl;
					temp = 0;
				}
				do
				{
					if (temp != 0) {
						cout << "Invalid Dates" << endl;
						temp = 0;
					}
					cout << "Trip's Start Date: " << endl;
					do {
						cout << "                   Year: ";
						test = checkinputchoice(input, 2019, 2200);
					} while (test != 0);
					newpack.startdate.year = stoi(input);
					do {
						cout << "                   Month: ";
						test = checkinputchoice(input, 1, 12);
					} while (test != 0);
					newpack.startdate.month = stoi(input);
					do {
						cout << "                   Day: ";
						test = checkinputday(input, newpack.startdate.month, newpack.startdate.year);
					} while (test != 0);
					newpack.startdate.day = stoi(input);
					cout << "Trip's End Date: " << endl;
					do {
						cout << "                   Year: ";
						test = checkinputchoice(input, 2019, 2200);
					} while (test != 0);
					temp = checkinputenddateyear(input, newpack);
				} while (temp != 0);
				newpack.enddate.year = stoi(input);
				do {
					cout << "                   Month: ";
					test = checkinputchoice(input, 1, 12);
				} while (test != 0);
				temp = checkinputenddatemonth(input, newpack);
			} while (temp != 0);
			newpack.enddate.month = stoi(input);
			do {
				cout << "                   Day: ";
				test = checkinputday(input, newpack.enddate.month, newpack.enddate.year);
			} while (test != 0);
			temp = checkinputenddateday(input, newpack);
		} while (temp != 0);  // checks input and validity for day
		newpack.enddate.day = stoi(input);

		do {
			cout << "Price per Person: ";
			test = checkinputnumber(input);
		} while (test != 0);
		newpack.price = stoi(input);
		do {
			cout << "Inicial Number of Seats Available: ";
			test = checkinputnumber(input);
		} while (test != 0);
		newpack.seatsavailable = stoi(input);
		do {
			cout << "Number of Seats Sold: ";
			test = checkinputnumber(input);
			if (test == 0) {
				if (stoul(input) > newpack.seatsavailable)
					test = 1;
			}
		} while (test != 0);
		newpack.seatssold = stoi(input);
		if (newpack.seatssold == newpack.seatsavailable)
			newpack.identifier = newpack.identifier * (-1);

		system("cls");
		ShowPackInfo(newpack);
		cout << endl << "Do you confirm this data?" << endl;
		cout << "1 - Yes" << endl;
		cout << "2 - No" << endl; // Com NO pergunta se quer novo cliente ou sair
		do {
			test = checkinputchoice(input, 1, 2);
		} while (test != 0);
		continuar = stoi(input); // continuar é uma variavel reutilizada
		if (continuar == 1) {
			PacksList.push_back(newpack);
		}
		system("cls");
		cout << "--------- PACK CREATED ---------";
		cout << endl << "1 - New Pack" << endl;
		cout << "0 - Exit" << endl;
		do {
			test = checkinputchoice(input, 0, 1);
		} while (test != 0);
		continuar = stoi(input);   // continuar é uma variavel reutilizada
	} while (continuar != 0);
}

int checkinputstartdateyear(string &input, Packs managedpack) {
	if (stoul(input) > managedpack.enddate.year)
		return 1;
	return 0;
}
int checkinputstartdatemonth(string &input, Packs managedpack) {
	if (managedpack.startdate.year == managedpack.enddate.year) {
		if (stoul(input) > managedpack.enddate.month)
			return 1;
	}
	return 0;
}
int checkinputstartdateday(string &input, Packs managedpack) {
	if (managedpack.startdate.year == managedpack.enddate.year) {
		if (managedpack.startdate.month == managedpack.enddate.month) {
			if (stoul(input) > managedpack.enddate.day)
				return 1;
		}
	}
	return 0;
}
void ManagePack() {
	int test = 1, index = 0; string input = "";
	do {
		system("cls");
		cout << "----------Manage Pack----------" << endl;
		for (unsigned int i = 0; i < PacksList.size(); i++)
		{
			cout << i + 1 << " - Packs's Identifier: " << PacksList[i].identifier << endl;
			cout << "Packs Main Destiny: " << PacksList[i].princplace << endl;
		}
		do {
			cout << "Choose Number: ";
			test = checkinputchoice(input, 1, PacksList.size());
		} while (test != 0);
		index = stoi(input) - 1;

		cout << endl << "Details to Manage: " << endl;
		cout << "Identifier: " << PacksList[index].identifier << endl;
		cout << "1 - Main Destiny: " << PacksList[index].princplace << endl;
		cout << "2 - Start Date:   (1) Day: " << PacksList[index].startdate.day << endl;
		cout << "                  (2) Month: " << PacksList[index].startdate.month << endl;
		cout << "                  (3) Year: " << PacksList[index].startdate.year << endl;
		cout << "3 - End Date:     (1) Day: " << PacksList[index].enddate.day << endl;
		cout << "                  (2) Month: " << PacksList[index].enddate.month << endl;
		cout << "                  (3) Year: " << PacksList[index].enddate.year << endl;
		cout << "4 - Price: " << PacksList[index].price << endl;
		cout << "5 - Seats available (before selling): " << PacksList[index].seatsavailable << endl;
		cout << "6 - Seats sold: " << PacksList[index].seatssold << endl << endl;

		cout << endl << "Do you want to change data in this Pack?" << endl;
		cout << "1 - Yes" << endl;
		cout << "2 - No" << endl; // Com NO pergunta se quer modificar outro cliente ou sair
		do { test = checkinputchoice(input, 1, 2); } while (test != 0);
		if (stoi(input) == 1)
		{
			packs_lastpack = index;
			cout << "Which Detail do change (1-6): ";
			do { test = checkinputchoice(input, 1, 6); } while (test != 0);
			cout << endl;
			switch (stoi(input))
			{
			case 1:
				do {
					cout << "Main Destiny? " << endl;
					test = checkinputmaindestiny(input);
				} while (test != 0);
				PacksList[index].princplace = input;
				break;
			case 2:
				test = 1;
				do {
					cout << "Change all parts of the date (1) or just one part (2): ";
					test = checkinputchoice(input, 1, 2);
				} while (test != 0);
				if (stoi(input) == 1)
				{
					test = 1;
					cout << "Trip's Start Date: " << endl;
					do
					{
						if (test == 0)
						{
							cout << "Trip's enddate year is " << PacksList[index].enddate.year << endl;
							test = 1;
						}
						do {
							cout << "                   Year: ";
							test = checkinputchoice(input, 2019, 2200);
						} while (test != 0);
						test = checkinputstartdateyear(input, PacksList[index]);
					} while (test != 0);
					test = 1;
					PacksList[index].startdate.year = stoi(input);
					do
					{
						if (test == 0)
						{
							cout << "Trip's enddate year is " << PacksList[index].enddate.year << " and month is " << PacksList[index].enddate.month << endl;
							test = 1;
						}
						do {
							cout << "                   Month: ";
							test = checkinputchoice(input, 1, 12);
						} while (test != 0);
						test = checkinputstartdatemonth(input, PacksList[index]);
					} while (test != 0);
					test = 1;
					PacksList[index].startdate.month = stoi(input);
					do
					{
						if (test == 0)
						{
							cout << "Trip's enddate year is " << PacksList[index].enddate.year << ", month is " << PacksList[index].enddate.month << " and day is " << PacksList[index].enddate.day << endl;
							test = 1;
						}
						do {
							cout << "                   Day: ";
							test = checkinputday(input, PacksList[index].startdate.month, PacksList[index].startdate.year);
						} while (test != 0);
						test = checkinputstartdateday(input, PacksList[index]);
					} while (test != 0);
					test = 1;
					PacksList[index].startdate.day = stoi(input);
				}
				else
				{
					test = 1;
					do {
						cout << "Change day(1), month(2) or year(3): ";
						test = checkinputchoice(input, 1, 3);
					} while (test != 0);
					switch (stoi(input))
					{
					case 1:
						test = 1;
						do
						{
							if (test == 0)
							{
								cout << "Trip's enddate year is " << PacksList[index].enddate.year << ", month is " << PacksList[index].enddate.month << " and day is " << PacksList[index].enddate.day << endl;
								test = 1;
							}
							do {
								cout << "                   Day: ";
								test = checkinputday(input, PacksList[index].startdate.month, PacksList[index].startdate.year);
							} while (test != 0);
							test = checkinputstartdateday(input, PacksList[index]);
						} while (test != 0);
						test = 1;
						PacksList[index].startdate.day = stoi(input);
						break;
					case 2:
						test = 1;
						do
						{
							if (test == 0)
							{
								cout << "Trip's enddate year is " << PacksList[index].enddate.year << " and month is " << PacksList[index].enddate.month << endl;
								test = 1;
							}
							do {
								cout << "                   Month: ";
								test = checkinputchoice(input, 1, 12);
							} while (test != 0);
							test = checkinputstartdatemonth(input, PacksList[index]);
						} while (test != 0);
						test = 1;
						PacksList[index].startdate.month = stoi(input);
						break;
					case 3:
						test = 1;
						do
						{
							if (test == 0)
							{
								cout << "Trip's enddate year is " << PacksList[index].enddate.year << endl;
								test = 1;
							}
							do {
								cout << "Year: ";
								test = checkinputchoice(input, 2019, 2200);
							} while (test != 0);
							test = checkinputstartdateyear(input, PacksList[index]);
						} while (test != 0);
						test = 1;
						PacksList[index].startdate.year = stoi(input);
						break;
					default:
						break;
					}
				}
				break;
			case 3:
				do {
					cout << "Change all parts of the date (1) or just one part (2): ";
					test = checkinputchoice(input, 1, 2);
				} while (test != 0);
				if (stoi(input) == 1)
				{
					test = 1;
					cout << "Trip's End Date: " << endl;
					do
					{
						if (test == 0)
						{
							cout << "Trip's startdate year is " << PacksList[index].startdate.year << endl;
							test = 1;
						}
						do {
							cout << "                   Year: ";
							test = checkinputchoice(input, 2019, 2200);
						} while (test != 0);
						test = checkinputenddateyear(input, PacksList[index]);
					} while (test != 0);
					test = 1;
					PacksList[index].enddate.year = stoi(input);
					do
					{
						if (test == 0)
						{
							cout << "Trip's startdate year is " << PacksList[index].startdate.year << " and month is " << PacksList[index].startdate.month << endl;
							test = 1;
						}
						do {
							cout << "                   Month: ";
							test = checkinputchoice(input, 1, 12);
						} while (test != 0);
						test = checkinputenddatemonth(input, PacksList[index]);
					} while (test != 0);
					test = 1;
					PacksList[index].enddate.month = stoi(input);
					do
					{
						if (test == 0)
						{
							cout << "Trip's startdate year is " << PacksList[index].startdate.year << ", month is " << PacksList[index].startdate.month << " and day is " << PacksList[index].startdate.day << endl;
							test = 1;
						}
						do {
							cout << "                   Day: ";
							test = checkinputday(input, PacksList[index].enddate.month, PacksList[index].enddate.year);
						} while (test != 0);
						test = checkinputenddateday(input, PacksList[index]);
					} while (test != 0);
					test = 1;
					PacksList[index].enddate.day = stoi(input);
				}
				else
				{
					do {
						cout << "Change day(1), month(2) or year(3): ";
						test = checkinputchoice(input, 1, 3);
					} while (test != 0);
					test = 1;
					switch (stoi(input))
					{
					case 1:
						do
						{
							if (test == 0)
							{
								cout << "Trip's startdate year is " << PacksList[index].startdate.year << ", month is " << PacksList[index].startdate.month << " and day is " << PacksList[index].startdate.day << endl;
								test = 1;
							}
							do {
								cout << "Day: ";
								test = checkinputday(input, PacksList[index].enddate.month, PacksList[index].enddate.year);
							} while (test != 0);
							test = checkinputenddateday(input, PacksList[index]);
						} while (test != 0);
						test = 1;
						PacksList[index].enddate.day = stoi(input);
						break;
					case 2:
						do
						{
							if (test == 0)
							{
								cout << "Trip's start date year is " << PacksList[index].startdate.year << " and month is " << PacksList[index].startdate.month << endl;
								test = 1;
							}
							do {
								cout << "Month: ";
								test = checkinputchoice(input, 1, 12);
							} while (test != 0);
							test = checkinputenddatemonth(input, PacksList[index]);
						} while (test != 0);
						test = 1;
						PacksList[index].enddate.month = stoi(input);
						break;
					case 3:
						do
						{
							if (test == 0)
							{
								cout << "Trip's startdate year is " << PacksList[index].startdate.year << endl;
								test = 1;
							}
							do {
								cout << "Year: ";
								test = checkinputchoice(input, 2019, 2200);
							} while (test != 0);
							test = checkinputenddateyear(input, PacksList[index]);
						} while (test != 0);
						test = 1;
						PacksList[index].enddate.year = stoi(input);
						break;
					default:
						break;
					}
				}
				break;
			case 4:
				do {
					cout << "Price? " << endl;
					test = checkinputnumber(input);
				} while (test != 0);
				PacksList[index].price = stoi(input);
				break;
			case 5:
				test = 0;
				do
				{
					if (test)
						cout << "Number of seats available < number of seats sold";
					do {
						cout << "Seats available (before selling)? " << endl;
						test = checkinputnumber(input);
					} while (test != 0);
					test = stoul(input) < PacksList[index].seatssold;
				} while (test);
				PacksList[index].seatsavailable = stoi(input);
				break;
			case 6:
				test = 0;
				do
				{
					if (test)
						cout << "Number of seats sold < number of seats available" << endl;
					do {
						cout << "Seats sold? " << endl;
						test = checkinputnumber(input);
					} while (test != 0);
					test = stoul(input) > PacksList[index].seatsavailable;
				} while (test);
				PacksList[index].seatssold = stoi(input);
				if (PacksList[index].seatssold == PacksList[index].seatsavailable)
					PacksList[index].identifier = PacksList[index].identifier * (-1);
				break;
			default:
				break;
			}
		}
		cout << endl << "1 - Modify another pack" << endl;
		cout << "0 - Exit" << endl;
		do { test = checkinputchoice(input, 0, 1); } while (test != 0);
	} while (stoi(input) != 0);

}

void DeletePack() {
	int test = 0, index = 0; string input = "";
	do
	{
		system("cls");
		for (unsigned int i = 0; i < PacksList.size(); i++)
		{
			cout << i + 1 << " - Pack's Identifier: " << PacksList[i].identifier << endl;
			cout << "Main Destiny: " << PacksList[i].princplace << endl;
		}
		do {
			cout << "Choose Number: ";
			test = checkinputchoice(input, 1, PacksList.size());
		} while (test != 0);
		index = stoi(input) - 1;

		cout << endl << "-----Data of Pack to Delete-----" << endl;
		ShowPackInfo(PacksList[index]);

		cout << endl << "Do you want to delete this pack?" << endl;
		cout << "1 - Yes" << endl;
		cout << "2 - No" << endl; // Com NO pergunta se quer modificar outro cliente ou sair
		do { test = checkinputchoice(input, 1, 2); } while (test != 0);
		if (stoi(input) == 1)
		{
			PacksList.erase(PacksList.begin() + index);
			cout << "Pack Deleted" << endl << endl;
		}
		do {
			cout << "1 - Choose Pack" << endl;
			cout << "0 - Exit" << endl;
			test = checkinputchoice(input, 0, 1);
		} while (test != 0);
	} while (stoi(input) != 0);
}

int Findinvector(vector<string> vect, string search) {
	for (unsigned int i = 0; i < vect.size(); i++)
	{
		if (vect[i] == search)
			return i;
	}
	return -1;
}
void showpacksbydate(string test) {
	system("cls");
	int foundone = 0;
	for (unsigned int i = 0; i < PacksList.size(); i++)
	{
		if (PacksList[i].princplace.find(test) != string::npos)
		{
			if (foundone)
			{
				cout << "_______________________________________________" << endl << endl;
				ShowPackInfo(PacksList[i]);
			}
			else
			{
				ShowPackInfo(PacksList[i]);
				foundone = 1;
			}
		}
	}
}
int datetodays(int year, int month, int day) {
	int toreturn = 0;
	// 31 - 1 3 5 7 8 10 12 
	// 30 - 4 6 9 11
	// 28/29 - 2
	switch (month)
	{
	case 1:
		break;
	case 2:
		toreturn = toreturn + 31;
		break;
	case 3:
		if (a_bissexto(year))
			toreturn = toreturn + 60;
		else
			toreturn = toreturn + 59;
		break;
	case 4:
		if (a_bissexto(year))
			toreturn = toreturn + 91;
		else
			toreturn = toreturn + 90;
		break;
	case 5:
		if (a_bissexto(year))
			toreturn = toreturn + 121;
		else
			toreturn = toreturn + 120;
	case 6:
		if (a_bissexto(year))
			toreturn = toreturn + 152;
		else
			toreturn = toreturn + 151;
		break;
	case 7:
		if (a_bissexto(year))
			toreturn = toreturn + 182;
		else
			toreturn = toreturn + 181;
		break;
	case 8:
		if (a_bissexto(year))
			toreturn = toreturn + 213;
		else
			toreturn = toreturn + 212;
		break;
	case 9:
		if (a_bissexto(year))
			toreturn = toreturn + 244;
		else
			toreturn = toreturn + 243;
		break;
	case 10:
		if (a_bissexto(year))
			toreturn = toreturn + 274;
		else
			toreturn = toreturn + 273;
		break;
	case 11:
		if (a_bissexto(year))
			toreturn = toreturn + 305;
		else
			toreturn = toreturn + 304;
		break;
	case 12:
		if (a_bissexto(year))
			toreturn = toreturn + 335;
		else
			toreturn = toreturn + 334;
		break;
	default:
		break;
	}
	toreturn = toreturn + day;
	toreturn = toreturn + 365 * (year - 1);
	return toreturn;
}
void startdatepacks(int option, string destination) {
	int test = 0, day1 = 0, month1 = 0, year1 = 0, day2 = 0, month2 = 0, year2 = 0, lowerlimit = 0, upperlimit = 0; string input = "";
	system("cls");
	cout << "Trip's Start Date - First Date: " << endl;
	do {
		cout << "                   Year: ";
		test = checkinputchoice(input, 2019, 2200);
	} while (test != 0);
	year1 = stoi(input);
	do {
		cout << "                   Month: ";
		test = checkinputchoice(input, 1, 12);
	} while (test != 0);
	month1 = stoi(input);
	do {
		cout << "                   Day: ";
		test = checkinputday(input, month1, year1);
	} while (test != 0);
	day1 = stoi(input);
	lowerlimit = datetodays(year1, month1, day1);
	cout << endl << "Second Date: " << endl;
	do
	{
		do {
			cout << "                   Year: ";
			test = checkinputchoice(input, 2019, 2200);
		} while (test != 0);
		if (stoi(input) < year1)
			test = 1;
	} while (test != 0);
	year2 = stoi(input);
	do
	{
		do {
			cout << "                   Month: ";
			test = checkinputchoice(input, 1, 12);
		} while (test != 0);
		if (year2 == year1 && stoi(input) < month1)
			test = 1;
	} while (test != 0);
	month2 = stoi(input);
	do
	{
		do {
			cout << "                   Day: ";
			test = checkinputday(input, month2, year2);
		} while (test != 0);
		if (year2 == year1 && month1 == month2 && stoi(input) < day1)
			test = 1;
	} while (test != 0);
	day2 = stoi(input);
	upperlimit = datetodays(year2, month2, day2);
	system("cls");
	if (option == 3)
	{
		day1 = 1; // reutilizar variavel, 1 - não deu output a nenhum pack;
		for (unsigned int i = 0; i < PacksList.size(); i++)
		{
			test = datetodays(PacksList[i].startdate.year, PacksList[i].startdate.month, PacksList[i].startdate.day);
			if (test >= lowerlimit && test <= upperlimit)
			{
				ShowPackInfo(PacksList[i]);
				day1 = 0;
			}
		}
		if (day1)
			cout << "No Packs Available" << endl;
		system("pause");
	}
	if (option == 4)
	{
		system("cls");
		day1 = 0; // reutilizar variavel, 1 - não deu output a nenhum pack;
		for (unsigned int i = 0; i < PacksList.size(); i++)
		{
			test = datetodays(PacksList[i].startdate.year, PacksList[i].startdate.month, PacksList[i].startdate.day);
			if (test >= lowerlimit && test <= upperlimit)
			{
				if (PacksList[i].princplace.find(destination) != string::npos)
				{
					if (day1)
					{
						cout << "_______________________________________________" << endl << endl;
						ShowPackInfo(PacksList[i]);
					}
					else
					{
						ShowPackInfo(PacksList[i]);
						day1 = 1;
					}
				}
			}
		}
		if (!day1)
			cout << "No Packs Available" << endl;
		system("pause");
	}
}
void enddatepacks(int option, string destination) {
	int test = 0, day1 = 0, month1 = 0, year1 = 0, day2 = 0, month2 = 0, year2 = 0, lowerlimit = 0, upperlimit = 0; string input = "";
	system("cls");
	cout << "Trip's End Date - First Date: " << endl;
	do {
		cout << "                   Year: ";
		test = checkinputchoice(input, 2019, 2200);
	} while (test != 0);
	year1 = stoi(input);
	do {
		cout << "                   Month: ";
		test = checkinputchoice(input, 1, 12);
	} while (test != 0);
	month1 = stoi(input);
	do {
		cout << "                   Day: ";
		test = checkinputday(input, month1, year1);
	} while (test != 0);
	day1 = stoi(input);
	lowerlimit = datetodays(year1, month1, day1);
	cout << endl << "Second Date: " << endl;
	do
	{
		do {
			cout << "                   Year: ";
			test = checkinputchoice(input, 2019, 2200);
		} while (test != 0);
		if (stoi(input) < year1)
			test = 1;
	} while (test != 0);
	year2 = stoi(input);
	do
	{
		do {
			cout << "                   Month: ";
			test = checkinputchoice(input, 1, 12);
		} while (test != 0);
		if (year2 == year1 && stoi(input) < month1)
			test = 1;
	} while (test != 0);
	month2 = stoi(input);
	do
	{
		do {
			cout << "                   Day: ";
			test = checkinputday(input, month2, year2);
		} while (test != 0);
		if (year2 == year1 && month1 == month2 && stoi(input) < day1)
			test = 1;
	} while (test != 0);
	day2 = stoi(input);
	upperlimit = datetodays(year2, month2, day2);
	if (option == 3)
	{
		system("cls");
		day1 = 1; // reutilizar variavel, 1 - não deu output a nenhum pack;
		for (unsigned int i = 0; i < PacksList.size(); i++)
		{
			test = datetodays(PacksList[i].enddate.year, PacksList[i].enddate.month, PacksList[i].enddate.day);
			if (test >= lowerlimit && test <= upperlimit) {
				ShowPackInfo(PacksList[i]);
				day1 = 0;
			}

		}
		if (day1)
			cout << "No Packs Available" << endl;
		system("pause");
	}
	if (option == 4)
	{
		system("cls");
		day1 = 0; // reutilizar variavel, 0 - não deu output a nenhum pack;
		for (unsigned int i = 0; i < PacksList.size(); i++)
		{
			test = datetodays(PacksList[i].enddate.year, PacksList[i].enddate.month, PacksList[i].enddate.day);
			if (test >= lowerlimit && test <= upperlimit)
			{
				if (PacksList[i].princplace.find(destination) != string::npos)
				{
					if (day1)
					{
						cout << "_______________________________________________" << endl << endl;
						ShowPackInfo(PacksList[i]);
					}
					else
					{
						ShowPackInfo(PacksList[i]);
						day1 = 1;
					}
				}
			}
		}
		if (!day1)
			cout << "No Packs Available" << endl;
		system("pause");
	}

}
void ShowPacks() {
	int test = 0, indexfirstof = 0, index = 1; string input = "", maindestiny = "";
	vector<string> maindestinies;
	system("cls");
	cout << "---------- Show Packs ----------" << endl;
	cout << "1 - All Packs" << endl;
	cout << "2 - All with same Destiny" << endl;
	cout << "3 - All between two dates" << endl;
	cout << "4 - All with same destiny and between two dates" << endl;
	cout << "0 - EXIT" << endl;
	do {
		test = checkinputchoice(input, 0, 4);
	} while (test != 0);
	switch (stoi(input))
	{
	case 1:
		system("cls");
		for (unsigned int i = 0; i < PacksList.size(); i++)
		{
			ShowPackInfo(PacksList[i]);
			if (i != PacksList.size() - 1)

				cout << "()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()" << endl << endl;
		}
		system("pause");
		break;
	case 2:
		system("cls");
		input = "";
		cout << "Choose main Destiny: " << endl;
		for (unsigned int i = 0; i < PacksList.size(); i++)
		{
			indexfirstof = PacksList[i].princplace.find_first_of('-');
			if (indexfirstof == -1) {
				input = PacksList[i].princplace;
				input = regex_replace(input, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
				if (Findinvector(maindestinies, input) == -1)
					maindestinies.push_back(input);
				input = "";
			}
			else
			{
				for (int j = 0; j < indexfirstof - 1; j++)
					input += PacksList[i].princplace[j];
				input = regex_replace(input, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
				if (Findinvector(maindestinies, input) == -1)
					maindestinies.push_back(input);
				input = "";
			}
		}
		for (unsigned int i = 0; i < maindestinies.size(); i++)
			cout << i + 1 << " - " << maindestinies[i] << endl;
		do {
			test = checkinputchoice(input, 1, maindestinies.size());
		} while (test != 0);
		showpacksbydate(maindestinies[stoi(input) - 1]);
		system("pause");
		break;
	case 3:
		cout << endl << "1 - Start Date Between 2 dates" << endl;
		cout << "2 - End Date Between 2 dates" << endl;
		cout << "0 - EXIT" << endl;
		do {
			test = checkinputchoice(input, 0, 2);
		} while (test != 0);
		if (stoi(input) == 1)
			startdatepacks(3, "");
		if (stoi(input) == 2)
			enddatepacks(3, "");
		break;
	case 4:
		system("cls");
		input = "";
		cout << "Choose main Destiny: " << endl;
		for (unsigned int i = 0; i < PacksList.size(); i++)
		{
			indexfirstof = PacksList[i].princplace.find_first_of('-');
			if (indexfirstof == -1) {
				input = PacksList[i].princplace;
				input = regex_replace(input, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
				if (Findinvector(maindestinies, input) == -1)
					maindestinies.push_back(input);
				input = "";
			}
			else
			{
				for (int j = 0; j < indexfirstof - 1; j++)
					input += PacksList[i].princplace[j];
				input = regex_replace(input, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
				if (Findinvector(maindestinies, input) == -1)
					maindestinies.push_back(input);
				input = "";
			}
		}
		for (unsigned int i = 0; i < maindestinies.size(); i++)
			cout << i + 1 << " - " << maindestinies[i] << endl;

		do {
			test = checkinputchoice(input, 1, maindestinies.size());
		} while (test != 0);
		maindestiny = maindestinies[stoi(input) - 1];

		cout << endl << "1 - Start Date Between 2 dates" << endl;
		cout << "2 - End Date Between 2 dates" << endl;
		cout << "0 - EXIT" << endl;
		do {
			test = checkinputchoice(input, 0, 2);
		} while (test != 0);
		if (stoi(input) == 1)
			startdatepacks(4, maindestiny);
		if (stoi(input) == 2)
			enddatepacks(4, maindestiny);


		break;
	default:
		break;
	}
}

void SoldPacks() {
	int test = 0, index = 0, ident = 0, foundpack = 0; string input = "";
	system("cls");
	cout << "---------- Sold Packs ----------\n" << endl;
	cout << "1 - By Specific Client" << endl;
	cout << "2 - By All Clients" << endl;
	cout << "0 - EXIT" << endl;
	do {
		test = checkinputchoice(input, 0, 2);
	} while (test != 0);
	switch (stoi(input))
	{
	case 1:
		do
		{
			system("cls");
			cout << "--------------------- Clients List ---------------------\n\n";
			for (unsigned int i = 0; i < ClientsList.size(); i++)
			{
				cout << i + 1 << " - Client's Name: " << ClientsList[i].name << endl;
				cout << "Client's NIF: " << ClientsList[i].nif << endl << endl;
			}
			do {
				cout << "Choose Number: ";
				test = checkinputchoice(input, 1, ClientsList.size());
			} while (test != 0);
			index = stoi(input) - 1;
			system("cls");
			for (unsigned int i = 0; i < ClientsList[index].boughtpacks.size(); i++)
			{
				foundpack = 0;
				for (unsigned int j = 0; j < PacksList.size(); j++)
				{
					if (PacksList[j].identifier < 0)
						ident = PacksList[j].identifier * (-1);
					else
						ident = PacksList[j].identifier;
					if (ClientsList[index].boughtpacks[i] == ident)
					{
						cout << "Identifier _______  " << PacksList[j].identifier << endl;
						cout << "Main Destiny _____  " << PacksList[j].princplace << endl;
						cout << "Start Date________  " << PacksList[j].startdate.day << "/" << PacksList[j].startdate.month << "/" << PacksList[j].startdate.year << endl;
						cout << "End Date _________  " << PacksList[j].enddate.day << "/" << PacksList[j].enddate.month << "/" << PacksList[j].enddate.year << endl << endl;
						foundpack = 1;
						break;
					}
				}
				if (!foundpack)
					cout << "Data for pack " << ClientsList[index].boughtpacks[i] << " is not available" << endl << endl;
			}

			cout << endl << "Do you want to see another client's bough packs?" << endl;
			cout << "1 - Yes" << endl;
			cout << "2 - No" << endl;
			do { test = checkinputchoice(input, 1, 2); } while (test != 0);
		} while (stoi(input) == 1);
		break;
	case 2:
		system("cls");
		// i - index de client
		// j - index de cada pack do client i
		// k - index de Packs List
		for (unsigned int i = 0; i < ClientsList.size(); i++)
		{
			cout << "--------- Packs Bought By: ---------" << endl;
			cout << ClientsList[i].name << " - NIF: " << ClientsList[i].nif << endl << endl;

			for (unsigned int j = 0; j < ClientsList[i].boughtpacks.size(); j++)
			{
				foundpack = 0;
				for (unsigned int k = 0; k < PacksList.size(); k++)
				{
					if (PacksList[k].identifier < 0)
						ident = PacksList[k].identifier * (-1);
					else
						ident = PacksList[k].identifier;
					if (ClientsList[i].boughtpacks[j] == ident)
					{
						cout << "Identifier _______  " << PacksList[k].identifier << endl;
						cout << "Main Destiny _____  " << PacksList[k].princplace << endl;
						cout << "Start Date________  " << PacksList[k].startdate.day << "/" << PacksList[k].startdate.month << "/" << PacksList[k].startdate.year << endl;
						cout << "End Date _________  " << PacksList[k].enddate.day << "/" << PacksList[k].enddate.month << "/" << PacksList[k].enddate.year << endl << endl;
						foundpack = 1;
						break;
					}
				}
				if (!foundpack)
					cout << "Data for pack " << ClientsList[i].boughtpacks[j] << " is not available" << endl << endl;
			}
		}

		system("pause");
		break;
	default:
		break;
	}
}
////////////////////////////////////////////////
void BuyPack() {
	int test = 0, index = 0, identifier = 0, packindex = 0; string input = "";
	// Necessário actualizar dados do pacote, seats bough +1
	system("cls");
	cout << "_____________________________________________________\n" << endl;
	cout << "\t\t      BUY PACKS " << endl;
	cout << "_____________________________________________________" << endl << endl;
	cout << "INSTRUCTIONS" << endl;
	cout << "1 - Choose a Client from the shown list" << endl << "2 - Insert the Pack's Identifier number" << endl << "3 - Confirm" << endl;
	cout << "(If you do not know the pack's idenfier number you can go back and check)\n\n";
	cout << "\t1 - Continue\n\t2 - Exit\n";
	do {
		test = checkinputchoice(input, 1, 2);
	} while (test != 0);
	if (stoi(input) == 1)
	{
		system("cls");
		cout << "--------------------- Clients List ---------------------\n\n";
		for (unsigned int i = 0; i < ClientsList.size(); i++)
		{
			cout << i + 1 << " - Client's Name: " << ClientsList[i].name << endl;
			cout << "    Client's NIF: " << ClientsList[i].nif << endl << endl;
		}
		do {
			cout << "Choose a number: ";
			test = checkinputchoice(input, 1, ClientsList.size());
		} while (test != 0);
		index = stoi(input) - 1;  // index of client
		do {
			cout << "Input the pack identifier: ";
			test = checkinputidentifier(input);
		} while (test != 1);
		identifier = stoi(input);
		system("cls");
		cout << ClientsList[index].name << " will buy this pack:\n\n";
		for (unsigned int i = 0; i < PacksList.size(); i++)
		{
			if (identifier == PacksList[i].identifier) {
				ShowPackInfo(PacksList[i]);
				packindex = i;
				break;
			}
		}
		cout << "\n1 - Confirm\n2 - Discard and EXIT\n";
		do {
			test = checkinputchoice(input, 1, 2);
		} while (test != 0);
		if (stoi(input) == 1)
		{
			/*3 coisas
				acrescentar ao cliente
				+1 nos packs comprados
				verificar se ficou indisponivel e caso sim mudar identifier*/
			ClientsList[index].boughtpacks.push_back(identifier);
			PacksList[packindex].seatssold++;
			if (PacksList[packindex].seatssold == PacksList[packindex].seatsavailable)
				PacksList[packindex].identifier = PacksList[packindex].identifier * (-1);
			system("cls");
			cout << "PACK BOUGHT SUCCESSFULLY\n";
			system("pause");
		}
	}
}
void PackData() {
	int counter = 0, revenue1 = 0, revenue2 = 0, identifier = 0;
	for (unsigned int i = 0; i < ClientsList.size(); i++)
	{
		counter = counter + ClientsList[i].boughtpacks.size();
		for (unsigned int j = 0; j < ClientsList[i].boughtpacks.size(); j++)
		{
			identifier = ClientsList[i].boughtpacks[j];
			for (unsigned int k = 0; k < PacksList.size(); k++)
			{
				if (identifier == PacksList[k].identifier || identifier == PacksList[k].identifier * (-1))
					revenue1 = revenue1 + PacksList[k].price;
			}
		}
	}
	for (unsigned int l = 0; l < PacksList.size(); l++)
	{
		revenue2 = revenue2 + PacksList[l].seatssold * PacksList[l].price;
	}
	system("cls");
	cout << "Total Packs sold: " << counter;
	cout << "\nRevenue made according to clients file --  " << revenue1 << " EUR (w/o price of packs that aren't documented)";
	cout << "\nRevenue made according to packs file ----  " << revenue2 << " EUR" << endl;
	system("pause");
}
//From Mem to Files
void AgencyToFile(string agencychoice) {
	ofstream myfile(agencychoice + ".txt");
	myfile << agency.name << endl;
	myfile << agency.nif << endl;
	myfile << agency.url << endl;
	myfile << agency.address.street << " / " << agency.address.numdoor << " / " << agency.address.numfloor << " / " << agency.address.postcode << " / " << agency.address.state << endl;
	myfile << agency.clientsfile << endl;
	myfile << agency.packsfile;
	myfile.close();
}
void ClientsToFile() {
	ofstream myfile(agency.clientsfile);
	for (unsigned int i = 0; i < ClientsList.size(); i++)
	{
		myfile << ClientsList[i].name << endl;
		myfile << ClientsList[i].nif << endl;
		myfile << ClientsList[i].household << endl;
		myfile << ClientsList[i].address.street << " / " << ClientsList[i].address.numdoor << " / " << ClientsList[i].address.numfloor << " / " << ClientsList[i].address.postcode << " / " << ClientsList[i].address.state << endl;
		for (unsigned int j = 0; j < ClientsList[i].boughtpacks.size(); j++)
		{
			if (j == ClientsList[i].boughtpacks.size() - 1)
			{
				if (i == ClientsList.size() - 1)
					myfile << ClientsList[i].boughtpacks[j];
				else
					myfile << ClientsList[i].boughtpacks[j] << endl;
			}
			else
				myfile << ClientsList[i].boughtpacks[j] << " ; ";
		}
		if (i != ClientsList.size() - 1)
		{
			myfile << "::::::::::" << endl;
		}
	}
	myfile.close();
}
void PacksToFile() {
	ofstream myfile(agency.packsfile);
	myfile << packs_lastpack << endl;
	for (unsigned int i = 0; i < PacksList.size(); i++)
	{
		myfile << PacksList[i].identifier << endl;
		myfile << PacksList[i].princplace << endl;
		myfile << PacksList[i].startdate.year << "/" << setfill('0') << setw(2) << PacksList[i].startdate.month << "/" << setfill('0') << setw(2) << PacksList[i].startdate.day << endl;
		myfile << setfill('0') << setw(2) << PacksList[i].enddate.year << "/" << setfill('0') << setw(2) << PacksList[i].enddate.month << "/" << setfill('0') << setw(2) << PacksList[i].enddate.day << endl;
		myfile << PacksList[i].price << endl;
		myfile << PacksList[i].seatsavailable << endl;
		myfile << PacksList[i].seatssold;
		if (i != PacksList.size() - 1)
			myfile << endl;
		if (i != PacksList.size() - 1)
			myfile << "::::::::::" << endl;

	}
}

// Input Agency name
int checkinputagency(string &test) {
	// 0 - tá bom
	// 1 - nome não valido
	// 2 - ficheiro não existe
	test = "";
	while (test.length() == 0)
		getline(cin, test);
	if (test.length() == 1)
		return 1;
	test = regex_replace(test, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
	string line;
	ifstream file(test + ".txt");
	if (!file.is_open())
		return 2;
	else
	{
		getline(file, line);
		if (isdigit(line[0]))
			return 1;
		getline(file, line);
		getline(file, line);
		if (isdigit(line[0]))
			return 1;
	}
	return 0;
} // checks input for Read_CheckAgencyInput function 
void Read_CheckAgencyInput(string &agencyfilename) {
	int teste = 1;
	do
	{
		cout << "Enter the name of the .txt file: ";
		teste = checkinputagency(agencyfilename);
		if (teste == 1)
			cout << "Not valid" << endl;
		if (teste == 2)
			cout << "File does not exist" << endl;
	} while (teste != 0);
}

int main()
{
	string agencychoice, inputmain = "", inputlower = "";
	int testinput = 0;
	Read_CheckAgencyInput(agencychoice);
	//agencychoice = "agency";
	AgencyToMem(agencychoice);
	ClientsToMem(agencychoice);
	PacksToMem(agencychoice);
	do
	{
		system("cls");
		cout << "_____________________________________________________\n" << endl;
		cout << "\t\t AGENCY " << agency.name << endl;
		cout << "_____________________________________________________" << endl << endl;
		cout << "Choose a option by typing a number and pressing Enter.\n" << endl;


		cout << "1 - Agency Data" << endl;
		cout << "2 - Clients" << endl;
		cout << "3 - Packs" << endl;
		cout << "4 - Buy a Pack" << endl;
		cout << "0 - EXIT" << endl;
		do {
			testinput = checkinputchoice(inputmain, 0, 4);
		} while (testinput != 0);

		switch (stoi(inputmain))
		{
		case 1:
			system("cls");
			cout << "----------------- Agency Data -----------------\n" << endl;
			cout << "Name ------------------------- " << agency.name << endl;
			cout << "NIF -------------------------- " << agency.nif << endl;
			cout << "Address: " << endl;
			cout << "                 Street ------ " << agency.address.street << endl;
			cout << "            Door Number ------ " << agency.address.numdoor << endl;
			cout << "           Floor Number ------ " << agency.address.numfloor << endl;
			cout << "              Post Code ------ " << agency.address.postcode << endl;
			cout << "                  State ------ " << agency.address.state << endl;
			system("pause");
			break;
		case 2: // Sub Menu para Client
			do
			{
				system("cls");
				cout << "_____________________________________________________\n" << endl;
				cout << "\t\t   Client Options " << endl;
				cout << "_____________________________________________________" << endl << endl;
				cout << "1 - Add Client" << endl;
				cout << "2 - Modify Client" << endl;
				cout << "3 - Remove Client" << endl;
				cout << "4 - View Client Info" << endl;
				cout << "5 - View All Clients Info" << endl;
				cout << "0 - EXIT" << endl;
				do { testinput = checkinputchoice(inputlower, 0, 5); } while (testinput != 0);
				switch (stoi(inputlower))
				{
				case 1:
					CreateClient();
					break;
				case 2:
					ManageClient();
					break;
				case 3:
					DeleteClient();
					break;
				case 4:
					ViewClientInfo();
					break;
				case 5:
					system("cls");
					for (unsigned int i = 0; i < ClientsList.size(); i++) {
						showClientData(ClientsList[i]);
						if (i != ClientsList.size() - 1)
							cout << "___________________________________________" << endl << endl;
					}
					system("pause");
					break;
				case 0:
					inputlower = "0";
					break;
				default:
					break;
				}
			} while (stoi(inputlower) != 0);
			break;
		case 3: // Sub Menu para Packs
			do
			{
				system("cls");
				cout << "_____________________________________________________\n" << endl;
				cout << "\t\t   Packs Options " << endl;
				cout << "_____________________________________________________" << endl << endl;
				cout << "1 - Add Pack" << endl;
				cout << "2 - Modify Pack" << endl;
				cout << "3 - Remove Pack" << endl;
				cout << "4 - See Packs's List" << endl;
				cout << "5 - See Sold Packs" << endl;
				cout << "6 - Check Pack's overall Data" << endl;
				cout << "0 - Exit" << endl;
				do { testinput = checkinputchoice(inputlower, 0, 6); } while (testinput != 0);
				switch (stoi(inputlower))
				{
				case 1:
					CreatePack(); //FEITO
					break;
				case 2:
					ManagePack(); //FEITO
					break;
				case 3:
					DeletePack(); //FEITO
					break;
				case 4:
					ShowPacks(); //FEITO
					break;
				case 5:
					SoldPacks();
					break;
				case 6:
					PackData();
					break;
				case 0:
					inputlower = "0";
					break;
				default:
					break;
				}
			} while (stoi(inputlower) != 0);
			break;
		case 4:
			BuyPack();
			break;
		case 0:
			AgencyToFile(agencychoice);
			ClientsToFile();
			PacksToFile();
			return 0;
		default:
			break;
		}
	} while (stoi(inputmain) != 0);
}