#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>
#include <sstream>
#include <chrono>
#include <thread>
#include <map>
#include <set>
#include <algorithm>
#include <functional>

#include "defs.h"
#include "Address.h"
#include "Client.h"
#include "Packet.h"
#include "Menus.h"
#include "checkInput.h"
#include "Date.h"

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

class Agency {
private:
  string name; // name of the  agency
  unsigned int VATnumber; // VAT number of the agency
  Address address; // address of the agency
  string URL; // URL of the agency Web site
  vector<Client> clients; // vector to store the existing clients
  vector<Packet> packets; // vector to store the existing packets
  string clientsfilename;
  string packetsfilename;
  unsigned int lastmodifiedpack;

  bool clientsInfoHasChanged; // flag that is set to "true" if at least one client has been changed/added/deleted
  bool packetsInfoHasChanged; // flag that is set to "true" if at least one packet has been changed/added/deleted
  unsigned int maxClientsId; // maximum value among all clients identifiers
  unsigned int maxPacketsId; // maximum value among all packets identifiers

public:
  Agency(string filename);

  // methods GET
  string getName() const;
  unsigned getVATnumber() const;
  Address getAddress() const;
  string getURL() const;
  vector<Client> getClients() const;
  vector<Packet> getPackets() const;


  // methods SET
  void setName(string name);
  void setVATnumber(unsigned VATnumber);
  void setAddress(Address address);
  void setURL(string url);
  void setClients(vector<Client> const& clients); //not being used 
  void setPackets(vector<Packet> const& packets); //not being used

  // files management
  void loadClients(string filename);
  void loadPackets(string filename);
  void loadClientPackets(string idsLine, vector<Packet>& clientPackets, vector<unsigned>& inexistentPackets);
  void loadPacketSites(string sitesStr, vector<string>& sites);
  void saveClients();
  void savePackets();

  //INPUT VALIDATION FUNCTIONS
   //clients
  int checkVATInput(string& test);
  //packets
  int checkIdInput(string& test);

  // CLIENT MANAGMENT
  //add
  void addClient();
  //change
  void changeClientName(unsigned index);
  void changeClientVAT(unsigned index);
  void changeClientFamilySize(unsigned index);
  void changeClientPackets(unsigned index);
  void changeClientAddress(unsigned index);
  void changeClientStreetName(unsigned index);
  void changeClientDoorNumber(unsigned index);
  void changeClientFloor(unsigned index);
  void changeClientPostalCode(unsigned index);
  void changeClientLocation(unsigned index);
  //remove
  void removeClientByClientList();
  void removeClientByVAT();
  //show
  void showClientInfo();
  void showAllClientsInfo();

  //PACKET MANGMENT
  //add
  void addPacket();
  //change
  void changePacketId(unsigned index);
  void changePacketSites(unsigned index);
  void changePacketDates(unsigned index);
  void changePacketBeginDate(unsigned index);
  void changePacketEndDate(unsigned index);
  void changePacketPrice(unsigned index);
  void changePacketMaxPeople(unsigned index);
  void changePacketReservedSeats(unsigned index);
  void changePacketAvailability(unsigned index);

  //remove
  void removePacketByPacketList();
  void removePacketById();
  //show
  void showPacketInfo();
  void showAllPacketsInfo();
  void showPacketsByDate();
  void showPacketsByDestination();
  void showPacketsByDateAndDestination();
  void packetsSoldToSpecificClient();
  void packetsSoldToAllClients();

  //STATISTICS
  void showSoldPacketsDataByClients();
  void showSoldPacketsDataByPacks();
  void showNMostVisistedPlaces();
  void showNMostVisistedPlaces(vector<string>& v1, bool &exit);
  void specialOption();
  /*friend ostream& operator<<(ostream& out, const Agency & agency);*/

  void buyPacket();
};
