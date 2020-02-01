#include "Address.h"
#include <regex>

Address::Address() {
}

Address::Address(string addressStr) {
  string temp = "";
  int counter = 1;
  for (unsigned int i = 0; i < addressStr.length(); i++)
  {
    if (addressStr[i] != '/')
      temp += addressStr[i];
    else
    {
      switch (counter)
      {
      case 1:
        temp = regex_replace(temp, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
        setStreet(temp);
        break;
      case 2:
        temp = regex_replace(temp, regex("^ +| +$|( ) +"), "$1");
        setDoorNumber(stoi(temp));
        break;
      case 3:
        temp = regex_replace(temp, regex("^ +| +$|( ) +"), "$1");
        setFloor(temp);
        break;
      case 4:
        temp = regex_replace(temp, regex("^ +| +$|( ) +"), "$1");
        setPostalCode(temp);
        break;
      default:
        break;
      }
      temp = "";
      counter++;
    }
  }
  temp = regex_replace(temp, regex("^ +| +$|( ) +"), "$1");
  setLocation(temp);
}

Address::Address(string street, unsigned short doorNumber, string floor, string postalCode, string location) {

  // REQUIRES IMPLEMENTATION
}

// metodos GET


string Address::getStreet() const {
  return street;
}

unsigned short Address::getDoorNumber() const {
  return doorNumber;
}

string Address::getFloor() const {
  return floor;
}

string Address::getPostalCode() const {
  return postalCode;
}

string Address::getLocation() const {
  return location;
}


// metodos SET

void Address::setStreet(string street) {
  this->street = street;
}

void Address::setDoorNumber(unsigned short doorNumber) {
  this->doorNumber = doorNumber;
}

void Address::setFloor(string floor) {
  this->floor = floor;
}

void Address::setPostalCode(string postalCode) {
  this->postalCode = postalCode;
}

void Address::setLocation(string  location) {
  this->location = location;
}


/*********************************
 * Mostrar Address
 ********************************/

// SHOW methods

void Address::showAddress(){
  cout << "Street --------- " << street << endl;
  cout << "Door Number ---- " << doorNumber << endl;
  cout << "Floor Number --- " << floor << endl;
  cout << "Postal Code ---- " << postalCode << endl;
  cout << "Location ------- " << location << endl;
}
 // displays an address in a nice format

ostream& operator<<(ostream& out, const Address& address) {
  out << "Street: " << address.getStreet() << endl;
  out << "Door Number: " << address.getDoorNumber() << endl;
  out << "Floor Number:" << address.getFloor() << endl;
  out << "Postal Code: " << address.getPostalCode() << endl;
  out << "Location: " << address.getLocation() << endl;
  return out;
}