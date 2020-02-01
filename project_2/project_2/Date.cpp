#include "Date.h"

Date::Date() {
}

Date::Date(string date) {
  string temp = "";
  int counter = 1;
  bool year = false;
  for (unsigned int i = 0; i < date.length(); i++)
  {
    if (date[i] != '/')
      temp += date[i];
    else
    {
      if (!year) {
        temp = regex_replace(temp, regex("^ +| +$|( ) +"), "$1");
        setYear(stoi(temp));
        year = true;
      }
      else
      {
        temp = regex_replace(temp, regex("^ +| +$|( ) +"), "$1");
        setMonth(stoi(temp));
      }
      temp = "";
    }
  }
  temp = regex_replace(temp, regex("^ +| +$|( ) +"), "$1");
  setDay(stoi(temp));
}

Date::Date(unsigned short day, unsigned short month, unsigned year) {

  // REQUIRES IMPLEMENTATION
}

 //GET Methods
unsigned short Date::getDay() const {
  return day;
}
unsigned short Date::getMonth() const {
  return month;
}
unsigned Date::getYear() const {
  return year;
}


 //SET Methods
void Date::setDay(unsigned short day) {
  this->day = day;
}
void Date::setMonth(unsigned short month) {
  this->month = month;
}
void Date::setYear(unsigned year) {
  this->year = year;

}


//Show methods
void Date::showDate(){
  cout << year << "/" << month << "/" << day;
}

 // disply a Date in a nice format
/*ostream& operator<<(ostream& out, const Date & date) {

  // REQUIRES IMPLEMENTATION

}*/
