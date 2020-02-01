#include "Packet.h"

Packet::Packet() {};

Packet::Packet(unsigned id, vector<string> sites, Date begin, Date end, double pricePerPerson, unsigned maxPeople, unsigned reservedSeats, bool available) {
  setId(id);
  setSites(sites);
  setBeginDate(begin);
  setEndDate(end);
  setPricePerPerson(pricePerPerson);
  setMaxPeople(maxPeople);
  setReservedSeats(reservedSeats);
  setAvailable(available);
}

// metodos GET

unsigned Packet::getId() const {
  return id;
}
vector<string> Packet::getSites() const {
  return sites;
}
Date Packet::getBeginDate() const {
  return begin;
}
Date Packet::getEndDate() const {
  return end;
}
double Packet::getPricePerPerson() const {
  return pricePerPerson;
}
unsigned Packet::getMaxPeople() const {
  return maxPeople;
}
unsigned Packet::getReservedSeats() const {
  return reservedSeats;
}
bool Packet::getAvailable() const {
  return available;
}

// metodos SET
void Packet::setId(unsigned id) {
  this->id = id;
}
void Packet::setSites(vector<string> sites) {
  this->sites.clear();
  for (size_t i = 0; i < sites.size(); i++) {
    this->sites.push_back(sites[i]);
  }
}
void Packet::setBeginDate(Date begin) {
  this->begin = begin;
}
void Packet::setEndDate(Date end) {
  this->end = end;
}
void Packet::setPricePerPerson(double pricePerPerson) {
  this->pricePerPerson = pricePerPerson;
}
void Packet::setMaxPeople(unsigned maxPeople) {
  this->maxPeople = maxPeople;
}
void Packet::setReservedSeats(unsigned reservedSeats) {
  this->reservedSeats = reservedSeats;
}
void Packet::setAvailable(bool available) {
  this->available = available;
}

//show methods
void Packet::showPacket() {
  cout << "Id ----------------- " << id << endl;
  cout << "Availability ------- ";
  if (available)
    cout << "Available";
  else
    cout << "Unavailable";
  cout << endl;
  cout << "Sites -------------- ";
  showSites();
  cout << "Begin Date --------- ";
  begin.showDate(); cout << endl;
  cout << "End Date ----------- ";
  end.showDate(); cout << endl;
  cout << "Price per person --- " << pricePerPerson << endl;
  cout << "Maximum people ----- " << maxPeople << endl;
  cout << "Reserved seats ----- " << reservedSeats << endl;
};
void::Packet::showSites(){
  if (sites.size() > 1) {
    cout << sites.at(0) << " - ";
    for (unsigned int i = 1; i < sites.size(); i++) {
      cout << sites.at(i);
      if (i != sites.size() - 1)
        cout << ", ";
      else
        cout << endl;
    }
  }
  else
    cout << sites.at(0) << endl;
}
 /* // shows a packet content
 ostream& operator<<(ostream& out, const Packet & packet) {

   // REQUIRES IMPLEMENTATION
 }*/
