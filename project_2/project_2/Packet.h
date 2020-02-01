#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "defs.h"
#include "Date.h"

using namespace std;

class Packet {
private:
  unsigned id; // packet unique identifier
  vector<string> sites; // touristic sites to visit
  Date begin;  // begin date
  Date end;  // end date
  double pricePerPerson; // price per person
  unsigned maxPeople; // max number of people
  unsigned reservedSeats; // number of seats that are already reserved (updated whenever the packet is sold to a new client) 
  bool available; //if pack is removed or there are no more seats it is set to false

public:
  Packet();
  Packet(unsigned id, vector<string> sites, Date begin, Date end, double pricePerPerson, unsigned maxPeople, unsigned reservedseats, bool available);

  // GET methods
  unsigned getId() const;
  vector<string> getSites() const;
  Date getBeginDate() const;
  Date getEndDate() const;
  double getPricePerPerson() const;
  unsigned getMaxPeople() const;
  unsigned getReservedSeats() const;
  bool getAvailable() const;

  // SET methods
  void setId(unsigned id);  // to set negatve if "deprecated"
  void setSites(vector<string> sites);
  void setBeginDate(Date begin);
  void setEndDate(Date end);
  void setPricePerPerson(double pricePerPerson);
  void setMaxPeople(unsigned maxPeople);
  void setReservedSeats(unsigned reservedseats);
  void setAvailable(bool available);

  // Show methods

  void showPacket();
  void showSites();

  /*friend ostream& operator<<(ostream& out, const Packet & packet);*/
};
