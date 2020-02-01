#include "checkInput.h"

int checkinputchoice(string& test, int lowerlimit, int upperlimit) {
	// e.g. ll = 0, ul = 3 , se num < 0 || num > 3    return 1
	do {
		getline(cin, test);
		if (cin.eof()) {
			cin.clear();
			return 2;
		}
	} while (test.length() == 0);
	test = regex_replace(test, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
	for (unsigned int i = 0; i < test.length(); i++)
	{
		if ((int)test[i] < -1 || (int)test[i] > 255)
			return 1;
		if (!isdigit(test[i]))
			return 1;
	}
	if (stoi(test) < lowerlimit || stoi(test) > upperlimit)
		return 1;
	return 0;
}
//check client's info input
int checkStringInput(string & test) {
	// 0 - tá bom
   // 1 - não tá bom
	do {
		getline(cin, test);
        if (cin.eof()) {
          cin.clear();
          return 5;
        }
	} while (test.length() == 0);
	if (test.length() == 1)
		return 1;
	test = regex_replace(test, regex("^ +| +$|( ) +"), "$1");
	if (test == "")
		return 1;
	for (unsigned int i = 0; i < test.length(); i++)
	{
		if (!isalpha(test[i]) && test[i] != ' ')
			return 1;
	}
	return 0;
}
int checkLocationInput(string& test) {
	// 0 - tá bom
   // 1 - não tá bom
	do {
		getline(cin, test);
		if (cin.eof()) {
			cin.clear();
			return 5;
		}
	} while (test.length() == 0);
	if (test.length() == 1)
		return 1;
	test = regex_replace(test, regex("^ +| +$|( ) +"), "$1");
	if (test == "")
		return 1;
	for (unsigned int i = 0; i < test.length(); i++)
	{
		if (!isalpha(test[i]) && test[i] != ' ')
			if (test[i] == ',')
				continue;
			else
				return 1;
	}
	return 0;
}
int checkStreetInput(string & test) {
	// 0 - tá bom
   // 1 - não tá bom
	do {
		getline(cin, test);
		if (cin.eof()) {
			cin.clear();
			return 5;
		}
	} while (test.length() == 0);
	if (test.length() == 1)
		return 1;
	test = regex_replace(test, regex("^ +| +$|( ) +"), "$1");
	if (test == "")
		return 1;
	for (unsigned int i = 0; i < test.length(); i++)
	{
		if (!isalpha(test[i]) && test[i] != ' ' && !isdigit(test[i]))
			if (test[i] == ',')
				continue;
			else
				return 1;
	}
	return 0;
}
int checkFamilySizeInput(string & test) {
	do {
		getline(cin, test);
        if (cin.eof()) {
          cin.clear();
          return 5;
        }
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
};
int checkNumberInput(string & test) {
	do {
		getline(cin, test);
        if (cin.eof()) {
          cin.clear();
          return 5;
        }
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
int checkFloorInput(string & test) {
	do {
		getline(cin, test);
        if (cin.eof()) {
          cin.clear();
          return 5;
        }
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
int checkPostalCodeInput(string & test) {
	do {
		getline(cin, test);
        if (cin.eof()) {
          cin.clear();
          return 5;
        }
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
};
int checkNumPacketsInput(string & test) {
	do {
		getline(cin, test);
        if (cin.eof()) {
          cin.clear();
          return 5;
        }
	} while (test.length() == 0);
	test = regex_replace(test, regex("^ +| +$|( ) +"), "$1");
	for (unsigned int i = 0; i < test.length(); i++)
	{
		if (!isdigit(test[i]))
			return 1;
	}
	if (stoi(test) < 0)
		return 1;
	return 0;
}
// returns true if the year is a leap year
bool leapYear(unsigned year) {
	if (year % 400 == 0)
		return true;
	if (year % 4 == 0 && year % 10 != 0)
		return true;
	return false;
}
// returns true if the date is valid and false otherwise
bool checkDateInput(unsigned& year, unsigned& month, unsigned& day) {
	char slash = '/';

	if (cin >> year >> slash >> month >> slash >> day) {
		if ((month >= 1) && (month <= 12) && (day <= 31) && (day >= 1)) {
			if (month == 2) {
				if (leapYear(year)) {
					if (day <= 29)
						return true;
					else
						return false;
				}
				else {
					if (day <= 28)
						return true;
					else
						return false;
				}
			}
			else if ((month == 4) || (month == 6) || (month == 9) || (month == 11)) {
				if (day <= 30)
					return true;
				else
					return false;
			}
			else
				return true;
		}
		else
			return false;
	}
	else {
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			return false;
		};
	}
	return false;
};
//returns true if date 2 is later than date1
bool compareDates(Date date1, Date date2) {
	if (date1.getYear() == date2.getYear()) {
		if (date1.getMonth() == date2.getMonth()) {
			if (date2.getDay() >= date1.getDay())
				return true;
			else
				return false;
		}
		else if (date2.getMonth() > date1.getMonth())
			return true;
		else
			return false;
	}
	else if (date2.getYear() > date1.getYear())
		return true;
	else
		return false;
};
int checkDestinationInput(string & test) {
	// 0 - tá bom
   // 1 - não tá bom
	do {
		getline(cin, test);
        if (cin.eof()) {
          cin.clear();
          return 5;
        }
	} while (test.length() == 0);
	if (test.length() == 1)
		return 1;
	test = regex_replace(test, regex("^ +| +$|( ) +"), "$1");
	if (test == "")
		return 1;
	for (unsigned int i = 0; i < test.length(); i++)
	{
		if (!isalpha(test[i]) && test[i] != ' ')
			return 1;
	}
	return 0;
}
int checkOneSiteInput(string & test) {
  if (test.length() == 1 && test!="-")
    return 1;
  else if (test == "")
    return 1;
  for (unsigned int i = 0; i < test.length(); i++)
  {
    if (!isalpha(test[i]) && test[i] != ' ' && test !="-")
      return 1;
  }
  return 0;
};
bool compareChar(char& c1, char& c2) {
	if (c1 == c2)
		return true;
	else if (std::toupper(c1) == std::toupper(c2))
		return true;
	return false;
}
//returns true if strings are equal
bool caseInsensitiveStringCompare(string & str1, string & str2) {
	if (str1.size() == str2.size()) {
		if (equal(str1.begin(), str1.end(), str2.begin(), &compareChar))
			return true;
		else
			return false;
	}
	return false;
};

int checkPriceInput(string & test) {
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
int checkinputchoiceid(string& test, vector<Packet> packets, vector<Packet> clientspackets, unsigned int familysize) {
  // return 1 se não for numero ou menor que 0
  // return 2 se der eof ou input for "0" (Bom caso, exit)
  // return 3 se packet existe e está unavailable
  // return 4 se packet existe e está available E tem lugares (Bom caso)
  // return 5 se não existir esse packet
  // return 6 se client já tem esse pack
  // return 7 se Não tem available seats suficientes

  do {
    getline(cin, test);
    if (cin.eof()) {
      cin.clear();
      return 2;
    }
  } while (test.length() == 0);
  test = regex_replace(test, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
  for (unsigned int i = 0; i < test.length(); i++)
  {
    if (!isdigit(test[i]))
      return 1;
  }
  if (stoi(test) < 0)
    return 1;
  if (stoi(test) == 0)
    return 2;
  for (unsigned int i = 0; i < packets.size(); i++)
  {
    if (stoi(test) == packets.at(i).getId() && !packets.at(i).getAvailable())
      return 3;  // found identifier with same number as input but pack is unavailable
    else if (stoi(test) == packets.at(i).getId() && packets.at(i).getAvailable()) {
      for (unsigned int j = 0; j < clientspackets.size(); j++)
      {
        if (clientspackets.at(j).getId() == stoi(test))
          return 6; // cliente já tem esse pack
      }
      if (packets.at(i).getMaxPeople() - packets.at(i).getReservedSeats() >= familysize)
        return 4;
      else
        return 7;
    }
  }
  return 5;
}
