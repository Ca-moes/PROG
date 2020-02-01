// Testes_Exame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <string>
#include <iostream>
#include <regex>
#include <algorithm>
using namespace std;

void toUpperStr(string &s) {
	string temp = ""; char tempchar = ' ';

	for (int i=0; i < s.length(); i++)
	{
		tempchar = static_cast<char>(toupper(s[i]));
		//cout << tempchar << endl;
		temp = temp + tempchar;
		//cout << temp << endl;
	}
	s = temp;
}
string transformLine(string s) {
	toUpperStr(s);
	string result = "";
	for (int i = 0; i < s.length(); i++) {
		if (s[i] != ' ' && isalpha(s[i]) == 0)
			result += " ";
		else
			result += s[i];
	}
	return result;
}
void decomposeLine(string line, vector<string>& words) {
	string s = transformLine(line);
	string temp = "";
	s = regex_replace(s, regex("^ +| +$|( ) +"), "$1");
	s = s + " ";
	for (int i = 0; i < s.length(); i++) {
		if (s[i] != ' ')
			temp += s[i];
		else {
			words.push_back(temp);
			temp = "";
		}
	}
}

int main()
{

	vector<string> ya;
	string s = "A very, very short sentence!";
	decomposeLine(s,ya);
	for (auto x: ya)
		std::cout << ' ' << x;
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
