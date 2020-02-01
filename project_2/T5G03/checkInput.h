#pragma once

#include <iostream>
#include <string>
#include <regex>

#include "Date.h"
#include "Packet.h"

using namespace std;

int checkinputchoice(string& test, int lowerlimit, int upperlimit);
//check client's info input
int checkStringInput(string& test);
int checkLocationInput(string& test);
int checkStreetInput(string& test);
int checkFamilySizeInput(string& test);
int checkNumberInput(string& test);
int checkFloorInput(string& test);
int checkPostalCodeInput(string& test);
int checkNumPacketsInput(string& test);
int checkOneSiteInput(string & test);
bool checkDateInput(unsigned& year, unsigned& month, unsigned& day);
bool compareDates(Date date1, Date date2);
int checkDestinationInput(string& test);
bool compareChar(char& c1, char& c2);
bool caseInsensitiveStringCompare(string& str1, string& str2);
int checkinputchoiceid(string& test, vector<Packet> packets, vector<Packet> clientspackets, unsigned int familysize);