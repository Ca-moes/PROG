#include "Client.h"

Client::Client() {

};

Client::Client(string name, unsigned VATnumber, unsigned short familySize, Address address) {
  setName(name);
  setVATnumber(VATnumber);
  setFamilySize(familySize);
  setAddress(address);
}

Client::Client(string name, unsigned VATnumber, unsigned short familySize, Address address, vector<Packet>& packets, vector<unsigned> &inexistentPackets, double totalPurchased) {
  setName(name);
  setVATnumber(VATnumber);
  setFamilySize(familySize);
  setAddress(address);
  setPacketList(packets);
  setInexistentPackets(inexistentPackets);
  setTotalPurchased(totalPurchased);
}

// GET methods

string Client::getName() const {
  return name;
}

unsigned Client::getVATnumber() const {
  return VATnumber;
}

unsigned short Client::getFamilySize() const {
  return familySize;
}

Address Client::getAddress() const {
  return address;
}

vector<Packet> Client::getPacketList() const {
  return packets;
}

vector <unsigned> Client::getInexistentPackets() const {
  return inexistentPackets;
}

double Client::getTotalPurchased() const {
  return totalPurchased;
}

// SET methods

void Client::setName(string name) {
  this->name = name;
}

void Client::setVATnumber(unsigned VATnumber) {
  this->VATnumber = VATnumber;
}

void Client::setFamilySize(unsigned short familySize) {
  this->familySize = familySize;
}
void Client::setAddress(Address address) {
  this->address = address;
}
void Client::setPacketList(vector<Packet>& packets) {
  this->packets.clear();
  for (unsigned i = 0; i < packets.size(); i++) {
    this->packets.push_back(packets[i]);
  }
}

void Client::setInexistentPackets(vector<unsigned>& inexistentPackets) {
  this->inexistentPackets.clear();
  for (unsigned i = 0; i < inexistentPackets.size(); i++) {
    this->inexistentPackets.push_back(inexistentPackets[i]);
  }
}

void Client::setTotalPurchased(double totalPurchased) {
  this->totalPurchased = totalPurchased;
}

// SHOW methods

void Client::showClient() {
  cout << "Name ----------- " << name << endl;
  cout << "VAT number ----- " << VATnumber << endl;
  cout << "Family Size ---- " << familySize << endl;
  cout << "Address: " << endl;
  address.showAddress();
  cout << "Packets: ";
  showPacketList();
  cout << endl;
  cout << "Total Purchased: " << totalPurchased << endl;
};
void Client::showPacketList(){
  for (unsigned i = 0; i < packets.size();i++){
    cout << packets.at(i).getId();
    if (i != (packets.size() - 1))
      cout << ", ";
  }
  if(!inexistentPackets.empty()){
    cout << ", ";
  }
  for (unsigned i = 0; i < inexistentPackets.size(); i++) {
    cout << inexistentPackets.at(i) << "*";
    if (i != (inexistentPackets.size() - 1))
      cout << ", ";
  }

  if (packets.empty() && inexistentPackets.empty()) {
    cout << 0;
  }
}

//
void Client::inexistentPacketToExistent(unsigned inexistentPacket,Packet packet) {
  for (unsigned i = 0; i < inexistentPackets.size(); i++) {
    if (inexistentPacket == inexistentPackets.at(i)) {
      inexistentPackets.erase(inexistentPackets.begin() + i);
    }
  }
  packets.push_back(packet);
};
/*ostream& operator<<(ostream& out, const Client & client) {

  // REQUIRES IMPLEMENTATION
}*/