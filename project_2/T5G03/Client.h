#pragma once

#include <iostream>
#include <string>
#include <vector>


#include "defs.h"
#include "Packet.h"
#include "Address.h"

using namespace std;

class Client {
private:
  string name; // name of the client
  unsigned VATnumber; // VAT number of client
  unsigned short familySize;  // number of family members
  Address address; // client's address
  vector<Packet> packets; // vector to store client's packets bought
  vector <unsigned> inexistentPackets; // packets that don't exist in packets file
  double  totalPurchased; // total value spent by the client

public:
  Client();
  Client(string name, unsigned VATnumber, unsigned short familySize, Address address);  // for a new client
  Client(string name, unsigned VATnumber, unsigned short familySize, Address address, vector<Packet>& packets, vector<unsigned>&inexistentPackets, double totalPurchased);  // client read from file

  // GET methods

  string getName() const;
  unsigned getVATnumber() const;
  unsigned short getFamilySize() const;
  Address getAddress() const;
  vector<Packet> getPacketList() const;
  vector<unsigned> getInexistentPackets() const;
  double getTotalPurchased() const;

  // SET methods

  void setName(string name);
  void setVATnumber(unsigned VATnumber);
  void setFamilySize(unsigned short familySize);
  void setAddress(Address address);
  void setPacketList(vector<Packet>& packets);
  void setInexistentPackets(vector<unsigned>& inexistentPackets);
  void setTotalPurchased(double totalPurchased);

  //outros
  void inexistentPacketToExistent(unsigned inexistentPacketToExistent, Packet packet); // se um pack não existia e passou a existir

  // SHOW methods

  void showClient();
  void showPacketList();

  /*friend ostream& operator<<(ostream& out, const Client & client);*/
};