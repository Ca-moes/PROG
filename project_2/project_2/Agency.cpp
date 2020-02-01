#include "Agency.h"
#include <iomanip>

Agency::Agency(string filename) {
	int numline = 0;
	string line;
	string clientsFile;
	ifstream agencyfile;
	Address address;

	  cout << "Choose .txt agency file: ";
	  cin >> filename;
	  agencyfile.open(filename + ".txt");
      if (agencyfile.fail()) {
        cerr << "Error opening agency file!" << endl;
        exit(0);
      }

	while (getline(agencyfile, line))
	{
		numline++;

		switch (numline)
		{
		case 1:
			line = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			setName(line);
			break;
		case 2:
			line = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			setVATnumber(stol(line));
			break;

		case 3:
			line = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			setURL(line);
			break;
		case 4:
			address = Address(line);
			setAddress(address);
			break;
		case 5:
			clientsfilename = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			break;
		case 6:
			packetsfilename = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			loadPackets(packetsfilename);
			break;
		default:
			break;
		}
	}
	loadClients(clientsfilename);//primeiro é necessário conhecer os packs disponiveis, para o caso de algum dos packs do cliente nao existir
	agencyfile.close();
}

// metodos GET
string Agency::getName() const {
	return name;
}
unsigned Agency::getVATnumber() const {
	return VATnumber;
}
Address Agency::getAddress() const {
	return address;
}
string Agency::getURL() const {
	return URL;
}
vector<Client> Agency::getClients() const {
	return clients;
}
vector<Packet> Agency::getPackets() const {
	return packets;
}

// SET Methods
void Agency::setName(string name) {
	this->name = name;
}
void Agency::setVATnumber(unsigned VATnumber) {
	this->VATnumber = VATnumber;
}
void Agency::setAddress(Address address) {
	this->address = address;
}
void Agency::setURL(string url) {
	URL = url;
}
void Agency::setClients(vector<Client> const& clients) {
	for (unsigned i = 0; i < clients.size(); i++) {
		this->clients.push_back(clients[i]);
	}
} //not being used
void Agency::setPackets(vector<Packet> const& packets) {
	for (unsigned i = 0; i < packets.size(); i++) {
		this->packets.push_back(packets[i]);
	}
} //not being used

//file managemnet
void Agency::loadClients(string filename) {
	string dots = "::::::::::";
	string line;
	int linecounter = 1;
	ifstream clientsfile(filename);
	if (clientsfile.fail())
	{
		cerr << "Error opening clients file!" << endl;
		system("pause");
		exit(2);
	}
	//client's temporary variables
	string name;
	unsigned VATnumber = 0;
	unsigned short familySize = 0;
	Address address;
	vector<Packet> clientPackets;
    vector <unsigned> inexistentPackets;
	double totalPurchased = 0;
	Client client;

	while (getline(clientsfile, line)) {

		switch (linecounter)
		{
		case 1:
			line = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			name = line;
			break;
		case 2:
			line = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			VATnumber = stol(line);
			break;
		case 3:
			line = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			familySize = stoi(line);
			break;
		case 4:
			line = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			address = Address(line);
			break;
		case 5:
			line = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			loadClientPackets(line, clientPackets, inexistentPackets);
			break;
		case 6:
			line = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			totalPurchased = stof(line);
			break;
		}
		linecounter++;

		if (line == dots) {
			client = Client(name, VATnumber, familySize, address, clientPackets, inexistentPackets, totalPurchased);
			clients.push_back(client);
			clientPackets.clear();
            inexistentPackets.clear();
			linecounter = 1;
		}

	};
	client = Client(name, VATnumber, familySize, address, clientPackets,inexistentPackets, totalPurchased);
	clients.push_back(client);
	clientsfile.close();

};
void Agency::loadPackets(string filename) {
	string dots = "::::::::::";
	string line;
	int linecounter = 1;
	ifstream packsfile(filename);
	if (packsfile.fail())
	{
		cerr << "Error opening packs file!" << endl;
		system("pause");
		exit(3);
	}
	//pack's temporary variables
	int id = 0;
	vector<string> sites;
	Date begin;
	Date end;
	double pricePerPerson = 0;
	unsigned maxPeople = 0;
	unsigned reservedSeats = 0;
	bool available = true;
	Packet pack;

	getline(packsfile, line);
	lastmodifiedpack = stoi(line);

	while (getline(packsfile, line))
	{
		switch (linecounter)
		{
		case 1:
			line = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			if (stoi(line) < 0) {
				id = abs(stoi(line));
				available = false;
			}
			else
				id = stoi(line);
			break;
		case 2:
			line = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			loadPacketSites(line, sites);
			break;
		case 3:
			line = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			begin = Date(line);
			break;
		case 4:
			line = regex_replace(line, regex("^ +| +$|( ) +"), "$1");
			end = Date(line);
			break;
		case 5:
			line = regex_replace(line, regex("^ +| +$|( ) +"), "$1");
			pricePerPerson = stof(line);
			break;
		case 6:
			line = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			maxPeople = stoi(line);
			break;
		case 7:
			line = regex_replace(line, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
			reservedSeats = stoi(line);
			break;
		}
		linecounter++;

		if (line == dots) {
			if (reservedSeats >= maxPeople) {
				available = false;
			}
			pack = Packet(id, sites, begin, end, pricePerPerson, maxPeople, reservedSeats, available);
			packets.push_back(pack);
			sites.clear();
			linecounter = 1;
			available = true;
		}
	}

	pack = Packet(id, sites, begin, end, pricePerPerson, maxPeople, reservedSeats, available);
	packets.push_back(pack);
	packsfile.close();

};
void Agency::loadClientPackets(string idsLine, vector<Packet>& clientPackets, vector<unsigned> & inexistentPackets) {
	string temp = "";
    bool inexistent;
    for (unsigned i = 0; i < idsLine.length(); i++)
    {
      inexistent = true;
      if (idsLine[i] != ';')
        temp += idsLine[i];
      else
      {
        temp = regex_replace(temp, regex("^ +| +$|( ) +"), "$1");
        for (unsigned j = 0; j < packets.size(); j++) {
          if (packets[j].getId() == stoi(temp)) {
            clientPackets.push_back(packets[j]);
            inexistent = false;
          }
        }
        if (inexistent && stoi(temp) != 0) {
          inexistentPackets.push_back(stoi(temp));
        }
        temp = "";
      }
    }
    inexistent = true;
    for (unsigned i = 0; i < packets.size(); i++) {
      if (packets[i].getId() == stoi(temp)) {
        clientPackets.push_back(packets[i]);
        inexistent = false;
      }
    }
    if (inexistent && stoi(temp) != 0) {
      inexistentPackets.push_back(stoi(temp));
    }
};
void Agency::loadPacketSites(string sitesStr, vector<string>& sites) {
	stringstream ssin;
	string site;
	char comma = ',';
	char hifen = '-';
	size_t found = sitesStr.find(hifen);
	string temp;

	if (found != string::npos) {
		temp = regex_replace(sitesStr.substr(0, found), regex("^ +| +$|( ) +"), "$1");
		sites.push_back(temp);
        found = found + 1;
		sitesStr = regex_replace(sitesStr.substr(found), regex("^ +| +$|( ) +"), "$1");
		stringstream ssin(sitesStr);
		while (getline(ssin, site, comma)) {
			sites.push_back(regex_replace(site, regex("^ +| +$|( ) +"), "$1"));
		}
	}
	else { 
	  sites.push_back(regex_replace(sitesStr, regex("^ +| +$|( ) +"), "$1"));
	}
	ssin.clear();
};
void Agency::saveClients() {
	ofstream myfile(clientsfilename);  // É preciso guardar nome do ficheiro dos clients
	for (unsigned int i = 0; i < clients.size(); i++)
	{
		myfile << clients[i].getName() << endl;
		myfile << clients[i].getVATnumber() << endl;
		myfile << clients[i].getFamilySize() << endl;
		myfile << clients[i].getAddress().getStreet() << " / " << clients[i].getAddress().getDoorNumber() << " / " << clients[i].getAddress().getFloor() << " / " << clients[i].getAddress().getPostalCode() << " / " << clients[i].getAddress().getLocation() << endl;

		if (clients[i].getPacketList().size() == 0)
			myfile << "0" << endl;
		for (unsigned int j = 0; j < clients[i].getPacketList().size(); j++)
		{
			if (j == clients[i].getPacketList().size() - 1 && clients.at(i).getInexistentPackets().size() == 0)
				myfile << clients[i].getPacketList().at(j).getId() << endl;
			else
				myfile << clients[i].getPacketList().at(j).getId() << " ; ";
		}
		for (unsigned int j = 0; j < clients.at(i).getInexistentPackets().size(); j++)
		{
			if (j == clients[i].getInexistentPackets().size() - 1)
				myfile << clients.at(i).getInexistentPackets().at(j) << endl;
			else
				myfile << clients.at(i).getInexistentPackets().at(j) << " ; ";
		}
		
		if (i != clients.size() - 1)
			myfile << clients[i].getTotalPurchased() << endl;
		else
			myfile << clients[i].getTotalPurchased();
		if (i != clients.size() - 1)
			myfile << "::::::::::" << endl;
	}
	myfile.close();
};
void Agency::savePackets() {
	ofstream myfile(packetsfilename);

	myfile << lastmodifiedpack << endl;
	for (unsigned int i = 0; i < getPackets().size(); i++)
	{

		if (!getPackets().at(i).getAvailable())
			myfile << int(getPackets().at(i).getId()) * (-1) << endl;
		else
			myfile << int(getPackets().at(i).getId()) << endl;
		if (getPackets().at(i).getSites().size() > 1) {
			myfile << getPackets().at(i).getSites().at(0) << " - ";
			for (unsigned int j = 1; j < getPackets().at(i).getSites().size(); j++) {
				myfile << getPackets().at(i).getSites().at(j);
				if (j != getPackets().at(i).getSites().size() - 1)
					myfile << ", ";
				else
					myfile << endl;
			}
		}
		else
			myfile << getPackets().at(i).getSites().at(0) << endl;

		myfile << getPackets().at(i).getBeginDate().getYear() << "/" << setfill('0') << setw(2) << getPackets().at(i).getBeginDate().getMonth() << "/" << setfill('0') << setw(2) << getPackets().at(i).getBeginDate().getDay() << endl;
		myfile << getPackets().at(i).getEndDate().getYear() << "/" << setfill('0') << setw(2) << getPackets().at(i).getEndDate().getMonth() << "/" << setfill('0') << setw(2) << getPackets().at(i).getEndDate().getDay() << endl;
		myfile << getPackets().at(i).getPricePerPerson() << endl;
		myfile << getPackets().at(i).getMaxPeople() << endl;
		myfile << getPackets().at(i).getReservedSeats();
		if (i != getPackets().size() - 1)
			myfile << endl;
		if (i != getPackets().size() - 1)
			myfile << "::::::::::" << endl;
	}
};

//input check
int Agency::checkVATInput(string& test) {
  // 0 - tá bom
  // 1 - não tá bom
  // 2 - já existe cliente 
  do {
    getline(cin, test);
    if (cin.eof()) {
      cin.clear();
      return 5;
    }
  } while (test.length() == 0);
  test = regex_replace(test, regex("^ +| +$|( ) +"), "$1"); // remove espaços no fim, inicio e meio
  if (test.length() != 9)
    return 1;
  for (unsigned int i = 0; i < test.length(); i++)
  {
    if (!isdigit(test[i]) || test[i] == ' ')
      return 1;
  }
  // check if it already exists
  /*if (!validnif(test))
    return 3;*/
  for (unsigned i = 0; i < clients.size(); i++)
  {
    if (stoi(test) == clients[i].getVATnumber())
      return 2;
  }
  return 0;
};
int Agency::checkIdInput(string & test) {
  //0- pack doesn't exist
  //1- pack exists and it is available
  //2- pack input is invalid
  //3- pack exists but it is unavailable
    //se for um número
  int temp = checkNumberInput(test);
  if (temp == 0) {
    for (unsigned i = 0; i < packets.size(); i++)
    {
      if (stoi(test) == packets.at(i).getId() && !packets.at(i).getAvailable())
        return 3;  // found identifier with same number as input but pack is unavailable
      else if (stoi(test) == packets.at(i).getId() && packets.at(i).getAvailable())
        return 1; // found identifier with same number as input
    }
    if (stoi(test) == 0)
      return 2; // 0 is not a valid identifier
    return 0;
  }
  else if (temp == 5)
    return 5;
  else
    return 2;  // invalid input
}

// CLIENT MANAGEMENT
// add client
void Agency::addClient() {
  int test = 0; string input = ""; int temp = 0, numPackets = 0, numPacketsAvailable;
  bool existingPack, alreadyExists, available;
  vector <Packet> packetList;
  Address address;
  Client client;
  double totalPurchased;

  do {
    totalPurchased = 0;
    numPacketsAvailable = 0;
    packetList.clear();

    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t\t   Create Client " << endl;
    cout << "_____________________________________________________" << endl << endl;
    cout << "(Press Ctrl+z to go back)" << endl << endl;
    do
    {
      cout << "Client's Name: ";
      test = checkStringInput(input);
      if (test == 1)
        cout << "Invalid Name! Please try again." << endl;
    } while (test != 0 && test != 5);
    if (test == 5)
      break;
    client.setName(input);
    do {
      cout << "Client's VAT: ";
      test = checkVATInput(input);
      if (test == 3)
        cout << "Not a Valid VAT number! Try again." << endl;
      else if (test == 2)
        cout << "VAT already exists, insert another one." << endl;
      else if (test == 1)
        cout << "Invalid VAT. Please try again." << endl;
    } while (test != 0 && test != 5);
    if (test == 5)
      break;
    client.setVATnumber(stol(input));
    do {
      cout << "Family Size: ";
      test = checkFamilySizeInput(input);
      if (test == 1)
        cout << "Invalid Family Size! Please try again." << endl;
    } while (test != 0 && test != 5);
    if (test == 5)
      break;
    client.setFamilySize(stoi(input));
    do {
      cout << "Street Name: ";
      test = checkStreetInput(input);
      if (test == 1)
        cout << "Invalid Street! Please try again." << endl;
    } while (test != 0 && test != 5);
    if (test == 5)
      break;
    address.setStreet(input);
    do {
      cout << "House's Number: ";
      test = checkNumberInput(input);
      if (test == 1)
        cout << "Invalid House Number! Please try again." << endl;
    } while (test != 0 && test != 5);
    if (test == 5)
      break;
    address.setDoorNumber(stoi(input));
    do {
      cout << "(e.g. 1, 3, - , 6Esq, 9Dir, 2Mei)" << endl;
      cout << "Floor's Number: ";
      test = checkFloorInput(input);
      if (test == 1)
        cout << "Invalid Floor Number! Please try again." << endl;
    } while (test != 0 && test != 5);
    if (test == 5)
      break;
    address.setFloor(input);
    do {
      cout << "Postal Code (xxxx-xxx): ";
      test = checkPostalCodeInput(input);
      if (test == 1)
        cout << "Invalid Postal Code! Please try again." << endl;
    } while (test != 0 && test != 5);
    if (test == 5)
      break;
    address.setPostalCode(input);
    do {
      cout << "State/Location: ";
      test = checkLocationInput(input);
      if (test == 1)
        cout << "Invalid Location! Please try again." << endl;
    } while (test != 0 && test != 5);
    if (test == 5)
      break;
    address.setLocation(input);
    client.setAddress(address);

    //check how many available packs exist
    for (unsigned i = 0; i < packets.size(); i++) {
      if (packets.at(i).getAvailable() && packets.at(i).getMaxPeople()-packets.at(i).getReservedSeats() >= client.getFamilySize())
        numPacketsAvailable++;
    }

    do {
      cout << "How many bought packs? ";
      test = checkNumPacketsInput(input);
      if (test == 5)
        break;
      else if (test == 1)
        cout << "Invalid Number of Packs! Please try again." << endl;
      else {
      if((stoi(input) > numPacketsAvailable))
      {
        test = 2;
        cout << "There are only " << numPacketsAvailable << " different packets available for " << client.getFamilySize() << " people! Please try again." << endl;
      }
      }
    } while (test != 0 && test != 5);
    if (test == 5)
      break;
    numPackets = stoi(input);
    if (numPackets != 0)
    {
      for (int i = 0; i < numPackets; i++)
      {
        do {
          test = 0;
          existingPack = true;
          alreadyExists = false;
          available = true;
          cout << "Insert Packet Id: ";
          test = checkNumberInput(input);
          if (test != 0 && test != 5)
            cerr << "Invalid Id! Please try again." << endl;
          else {
            if (test == 5)
              break;
            for (unsigned j = 0; j < packets.size(); j++) {
              if (packets.at(j).getId() == stoi(input)) {
                existingPack = true;
                if (packets.at(j).getAvailable()) {
                  available = true;
                  for (unsigned k = 0; k < packetList.size(); k++) {
                    if (packetList.at(k).getId() == stoi(input)) {
                      alreadyExists = true;
                      break;
                    }
                    else
                      alreadyExists = false;
                  }
                  if (!alreadyExists) {
                    packetList.push_back(packets.at(j));
                    totalPurchased += packets.at(j).getPricePerPerson() * client.getFamilySize();
                  }
                  break;
                }
                else {
                  available = false;
                  break;
                }
              }
              else
                existingPack = false;
            }
          }
          if (!existingPack) {
            cerr << "No Packet with that Id exists! Please try again." << endl;
            test = 1;
          }
          if (alreadyExists) {
            cerr << "That packet was added already! Please try again." << endl;
            test = 1;
          }
          if (!available) {
            cerr << "That packet is unavailable! Please try again." << endl;
            test = 1;
          }
        } while (test != 0);
        if (test == 5)
          break;
      }
    }
    if (test == 5)
      break;
    client.setPacketList(packetList);
    client.setTotalPurchased(totalPurchased);

    //added
    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t\t   Create Client " << endl;
    cout << "_____________________________________________________" << endl << endl;
    cout << "---------------- New client data ----------------" << endl << endl;
    client.showClient();
    cout << endl << "Do you confirm this data?" << endl;
    cout << "1 - Yes" << endl;
    cout << "2 - No" << endl;
    do {
      test = checkinputchoice(input, 1, 2);
      if (test != 0)
        cerr << "Invalid option! Please try again." << endl;
    } while (test != 0);
    temp = stoi(input);
    if (stoi(input) == 1) {
      clients.push_back(client);
      for (unsigned i = 0; i < client.getPacketList().size();i++){
        for (unsigned j = 0; j < packets.size(); j++) {
          if (client.getPacketList().at(i).getId() == packets.at(j).getId()){
            packets.at(j).setReservedSeats((packets.at(j).getReservedSeats() + client.getFamilySize()));
            if (packets.at(j).getReservedSeats() == packets.at(j).getMaxPeople())
              packets.at(j).setAvailable(false);
            break;
          }
        }
      }
      temp = 0;
      cout << "The client was successfully created!" << endl << endl;
    }
    else {
      cout << "The client was not created!" << endl << endl;
    }

    cout << "1 - New Client" << endl;
    cout << "0 - Exit" << endl;
    do {
      test = checkinputchoice(input, 0, 1);
      if (test != 0)
        cerr << "Invalid option! Please try again." << endl;
    } while (test != 0 && test!=2);
    if (test == 2)
      temp = 0;
    else
      temp = stoi(input);
  } while (temp != 0);
};
//remove client
void Agency::removeClientByClientList() {
	int test = 0, index = 0; string input = ""; int temp = 0;
	do
	{
		system("cls");
		cout << "_____________________________________________________" << endl << endl;
		cout << "\t\t   Remove Client " << endl;
		cout << "_____________________________________________________" << endl << endl;
        cout << "(Press Ctrl+z to go back)" << endl << endl;
		if (clients.size() != 0) {

			for (unsigned int i = 0; i < clients.size(); i++)
			{
				cout << i + 1 << " - Client's Name: " << clients.at(i).getName() << endl;
				cout << "Client's VAT: " << clients.at(i).getVATnumber() << endl << endl;
			}
			do {
				cout << "Choose a number: ";
				test = checkinputchoice(input, 1, (int)clients.size());
				if (test != 0)
					cerr << "Invalid number! Please try again." << endl;
			} while (test != 0 && test!=2);
            if (test == 2)
              break;

			index = stoi(input) - 1;

			system("cls");
			cout << "_____________________________________________________" << endl << endl;
			cout << "\t\t   Remove Client " << endl;
			cout << "_____________________________________________________" << endl << endl;
			cout << "-----Data of Client to Delete-----" << endl << endl;
			clients.at(index).showClient();

			cout << endl << "Do you want to delete this client?" << endl;
			cout << "1 - Yes" << endl;
			cout << "2 - No" << endl;

			do {
				test = checkinputchoice(input, 1, 2);
				if (test != 0)
					cerr << "Invalid option! Please try again." << endl;
			} while (test != 0);

			if (stoi(input) == 1)
			{
				clients.erase(clients.begin() + index);
				temp = 0;
				cout << "The client was successfully deleted!" << endl << endl;
			}
			else {
				cout << "The client was not removed!" << endl << endl;
			}

			cout << "Delete another client?" << endl;
			cout << "1 - Yes" << endl;
			cout << "0 - No" << endl;
			do {
				test = checkinputchoice(input, 0, 1);
				cerr << "Invalid option! Please try again." << endl;
			} while (test != 0 && test!=2);
            if (test == 2)
              temp = 0;
            else
              temp = stoi(input);
		}
		else {
			cerr << "No clients to remove!" << endl;
			sleep_for(nanoseconds(10));
			sleep_until(system_clock::now() + seconds(1));
			temp = 0;
		}

	} while (temp != 0);
};
void Agency::removeClientByVAT() {
	int test = 0, index = 0; string input = ""; int temp = 0;
	do
	{
		system("cls");
		cout << "_____________________________________________________" << endl << endl;
		cout << "\t\t   Remove Client " << endl;
		cout << "_____________________________________________________" << endl << endl;
        cout << "(Press Ctrl+z to go back)" << endl << endl;
		if (clients.size() != 0) {
			do {
				cout << "Client's VAT: ";
				test = checkVATInput(input);
				if (test != 2)
					cout << "No client was found with that VAT number. Please try again." << endl;
			} while (test != 2 && test!=5);
            if (test == 5)
              break;
			test = 0;

			for (unsigned int i = 0; i < clients.size(); i++) {
				if (clients.at(i).getVATnumber() == stoi(input)) {
					index = i;
					break;
				}
			}
			system("cls");
			cout << "_____________________________________________________" << endl << endl;
			cout << "\t\t   Remove Client " << endl;
			cout << "_____________________________________________________" << endl << endl;

			cout << "-----Data of Client to Delete-----" << endl << endl;
			clients.at(index).showClient();

			cout << endl << "Do you want to delete this client?" << endl;
			cout << "1 - Yes" << endl;
			cout << "2 - No" << endl;

			do {
				test = checkinputchoice(input, 1, 2);
				if (test != 0)
					cerr << "Invalid option! Please try again." << endl;
			} while (test != 0);

			if (stoi(input) == 1)
			{
				clients.erase(clients.begin() + index);
				temp = 0;
				cout << "The client was successfully deleted!" << endl << endl;
			}
			else {
				cout << "The client was not removed!" << endl << endl;
			}

			cout << "Delete another client?" << endl;
			cout << "1 - Yes" << endl;
			cout << "0 - No" << endl;
			do {
				test = checkinputchoice(input, 0, 1);
				if (test != 0)
					cerr << "Invalid option! Please try again." << endl;
			} while (test != 0 && test!=2);
            if (test == 2)
              temp = 0;
            else
              temp = stoi(input);
		}
		else {
			cerr << "No clients to remove!" << endl;
			sleep_for(nanoseconds(10));
			sleep_until(system_clock::now() + seconds(1));
			temp = 0;
		}
	} while (temp != 0);

}
//change client
void Agency::changeClientName(unsigned index) {
	string input = "";
	int test = 0;
	do
	{
		if (test == 1)
			cout << "Invalid Name! Please try again." << endl;
		cout << "Client's Name: ";
		test = checkStringInput(input);
	} while (test != 0 && test!=5);
    if (test != 5) {
      clients.at(index).setName(input);
      cout << endl << "Data Modified" << endl;
    }
}
void Agency::changeClientVAT(unsigned index) {
	string input = "";
	int test = 0;
	do {
      cout << "Client's VAT: ";
      test = checkVATInput(input);
		if (test == 3)
			cout << "Not a Valid VAT number! Try again." << endl;
		else if (test == 2)
			cout << "Client already exists, create another one." << endl;
		else if (test == 1)
			cout << "Invalid name. Please try again." << endl;
	} while (test != 0 && test != 5);
    if (test != 5) {
      clients.at(index).setVATnumber(stol(input));
      cout << endl << "Data Modified" << endl;
    }
}
void Agency::changeClientFamilySize(unsigned index) {
	string input = "";
	int test = 0;
	do {
      cout << "Family Size: ";
      test = checkFamilySizeInput(input);
		if (test == 1)
			cout << "Invalid Family Size! Please try again." << endl;
	} while (test != 0 && test != 5);
    if (test != 5) {
	  clients.at(index).setFamilySize(stoi(input));
      cout << endl << "Data Modified" << endl;
    }
}
void  Agency::changeClientAddress(unsigned index) {
	Address newAddr;
	string input = "";
	int test = 0;

	do {
		if (test == 1)
			cout << "Invalid Street! Please try again." << endl;
		cout << "Street Name: ";
		test = checkStreetInput(input);
	} while (test != 0);
	newAddr.setStreet(input);
	do {
		if (test == 1)
			cout << "Invalid House Number! Please try again." << endl;
		cout << "House's Number: ";
		test = checkNumberInput(input);
	} while (test != 0);
	newAddr.setDoorNumber(stoi(input));
	do {
		if (test == 1)
			cout << "Invalid Floor Number! Please try again." << endl;
		cout << "(e.g. 1, 3, - , 6Esq, 9Dir, 2Mei)" << endl;
		cout << "Floor's Number: ";
		test = checkFloorInput(input);
	} while (test != 0);
	newAddr.setFloor(input);
	do {
		if (test == 1)
			cout << "Invalid Postal Code! Please try again." << endl;
		cout << "Postal Code (xxxx-xxx): ";
		test = checkPostalCodeInput(input);
	} while (test != 0);
	newAddr.setPostalCode(input);
	do {
		if (test == 1)
			cout << "Invalid Location! Please try again." << endl;
		cout << "State/Location: ";
		test = checkLocationInput(input);
	} while (test != 0);
	address.setLocation(input);
	clients.at(index).setAddress(newAddr);
};
void  Agency::changeClientStreetName(unsigned index) {
	Address newAddr = clients.at(index).getAddress();
	string input = "";
	int test = 0;
	do {
      cout << "Street Name: ";
      test = checkStreetInput(input);
		if (test == 1)
			cout << "Invalid Street! Please try again." << endl;
	} while (test != 0 && test!=5);
	newAddr.setStreet(input);
    if(test != 5){
      clients.at(index).setAddress(newAddr);
      cout << endl << "Data Modified" << endl;
    }
};
void  Agency::changeClientDoorNumber(unsigned index) {
	Address newAddr = clients.at(index).getAddress();
	string input = "";
	int test = 0;
	do {
		if (test == 1)
			cout << "Invalid House Number! Please try again." << endl;
		cout << "House's Number: ";
		test = checkNumberInput(input);
	} while (test != 0 && test != 5);
    newAddr.setDoorNumber(stoi(input));
    if (test != 5) {
      clients.at(index).setAddress(newAddr);
      cout << endl << "Data Modified" << endl;
    }
};
void  Agency::changeClientFloor(unsigned index) {
	Address newAddr = clients.at(index).getAddress();
	string input = "";
	int test = 0;
	do {
		if (test == 1)
			cout << "Invalid Floor Number! Please try again." << endl;
		cout << "(e.g. 1, 3, - , 6Esq, 9Dir, 2Mei)" << endl;
		cout << "Floor's Number: ";
		test = checkFloorInput(input);
	} while (test != 0 && test!=5);
	newAddr.setFloor(input);
    if(test!=5){
      clients.at(index).setAddress(newAddr);
      cout << endl << "Data Modified" << endl;
    }
};
void  Agency::changeClientPostalCode(unsigned index) {
	Address newAddr = clients.at(index).getAddress();
	string input = "";
	int test = 0;
	do {
		if (test == 1)
			cout << "Invalid Postal Code! Please try again." << endl;
		cout << "Postal Code (xxxx-xxx): ";
		test = checkPostalCodeInput(input);
	} while (test != 0 && test!=5);
	newAddr.setPostalCode(input);
    if(test!=5){
      clients.at(index).setAddress(newAddr);
      cout << endl << "Data Modified" << endl;
    }
};
void  Agency::changeClientLocation(unsigned index) {
	Address newAddr = clients.at(index).getAddress();
	string input = "";
	int test = 0;
	do {
		if (test == 1)
			cout << "Invalid Location! Please try again." << endl;
		cout << "State/Location: ";
		test = checkLocationInput(input);
	} while (test != 0 && test!=5);
	newAddr.setLocation(input);
    if(test != 5){
      clients.at(index).setAddress(newAddr);
      cout << endl << "Data Modified" << endl;
    }
};
void Agency::changeClientPackets(unsigned index) {
	string input = "";
	int test = 0;
	int numPackets,numPacketsAvailable = 0;
    bool existingPack, alreadyExists, available;
	vector <Packet> packetList;
	double totalPurchased = 0;

    //check how many available packs exist
    for (unsigned i = 0; i < packets.size(); i++) {
      if (packets.at(i).getAvailable() && packets.at(i).getMaxPeople() - packets.at(i).getReservedSeats() >= clients.at(index).getFamilySize())
        numPacketsAvailable++;
    }

    do {
      cout << "How many bought packs? ";
      test = checkNumPacketsInput(input);
      if (test == 5)
        break;
      else if (test == 1)
        cout << "Invalid Number of Packs! Please try again." << endl;
      else {
        if ((stoi(input) > numPacketsAvailable))
        {
          test = 2;
          cout << "There are only " << numPacketsAvailable << " different packets available for " << clients.at(index).getFamilySize() << " people! Please try again." << endl;
        }
      }
    } while (test != 0 && test != 5);
    if (test != 5){
      numPackets = stoi(input);
      if (numPackets != 0)
      {
        for (int i = 0; i < numPackets; i++)
        {
          do {
            test = 0;
            existingPack = true;
            alreadyExists = false;
            available = true;
            cout << "Insert Packet Id: ";
            test = checkNumberInput(input);
            if (test != 0 && test != 5)
              cerr << "Invalid Id! Please try again." << endl;
            else {
              if (test == 5)
                break;
              for (unsigned j = 0; j < packets.size(); j++) {
                if (packets.at(j).getId() == stoi(input)) {
                  existingPack = true;
                  if (packets.at(j).getAvailable()) {
                    available = true;
                    for (unsigned k = 0; k < packetList.size(); k++) {
                      if (packetList.at(k).getId() == stoi(input)) {
                        alreadyExists = true;
                        break;
                      }
                      else
                        alreadyExists = false;
                    }
                    if (!alreadyExists) {
                      packetList.push_back(packets.at(j));
                      totalPurchased += packets.at(j).getPricePerPerson() * clients.at(index).getFamilySize();
                    }
                    break;
                  }
                  else {
                    available = false;
                    break;
                  }
                }
                else
                  existingPack = false;
              }
            }
            if (!existingPack) {
              cerr << "No Packet with that Id exists! Please try again." << endl;
              test = 1;
            }
            if (alreadyExists) {
              cerr << "That packet was added already! Please try again." << endl;
              test = 1;
            }
            if (!available) {
              cerr << "That packet is unavailable! Please try again." << endl;
              test = 1;
            }
          } while (test != 0);
          if (test == 5)
            break;
        }
        /*elimina as vagas ocupadas pelos packets antigos*/
        for (unsigned i = 0; i < clients.at(index).getPacketList().size(); i++) {
          for (unsigned j = 0; j < packets.size(); j++) {
            if (clients.at(index).getPacketList().at(i).getId() == packets.at(j).getId()) {
              if (packets.at(j).getReservedSeats() >= clients.at(index).getFamilySize())
                packets.at(j).setReservedSeats(packets.at(j).getReservedSeats() - clients.at(index).getFamilySize());
              break;
            }
          }
        }
        clients.at(index).setPacketList(packetList);
        clients.at(index).setTotalPurchased(totalPurchased);
      }
    }
}
// show
void Agency::showClientInfo() {
	int test = 0, index = 0; string input = ""; int temp = 0;
	do
	{
		system("cls");
		cout << "_____________________________________________________" << endl << endl;
		cout << "\t\t   Show Client " << endl;
		cout << "_____________________________________________________" << endl << endl;
        cout << "(Press Ctrl+z to go back)" << endl << endl;
		if (clients.size() != 0) {
			do {
				cout << "Client's VAT: ";
				test = checkVATInput(input);
				if (test != 2)
					cout << "No client was found with that VAT number. Please try again." << endl;
			} while (test != 2 && test!=5);
            if (test == 5)
              break;
			test = 0;

			for (unsigned int i = 0; i < clients.size(); i++) {
				if (clients.at(i).getVATnumber() == stoi(input)) {
					index = i;
					break;
				}
			}

			system("cls");
			cout << "_____________________________________________________" << endl << endl;
			cout << "\t\t   Show Client " << endl;
			cout << "_____________________________________________________" << endl << endl;
			cout << "-----Data of Client with VAT " << clients.at(index).getVATnumber() << "-----" << endl << endl;
			clients.at(index).showClient();

			cout << endl << "Show another client?" << endl;
			cout << "1 - Yes" << endl;
			cout << "0 - No" << endl;
			do {
				test = checkinputchoice(input, 0, 1);
				if (test != 0)
					cerr << "Invalid option! Please try again." << endl;
			} while (test != 0 && test!=2);
			temp = stoi(input);
		}
		else {
			cerr << "No clients to show!" << endl;
			sleep_for(nanoseconds(10));
			sleep_until(system_clock::now() + seconds(1));
			temp = 0;
		}
	} while (temp != 0);
}
void Agency::showAllClientsInfo() {
	int test = 0;
	string input = "";

	system("cls");
	cout << "_____________________________________________________" << endl << endl;
	cout << "\t\t   Clients List " << endl;
	cout << "_____________________________________________________" << endl << endl;
    cout << "(* - No data is available on this Packet )" << endl << endl;
	if (clients.size() != 0) {
		for (unsigned i = 0; i < clients.size(); i++) {
			cout << "Client " << i + 1 << ":" << endl;
			clients.at(i).showClient();
			cout << endl;
		}
	}
	else {
		cerr << "No clients to show!" << endl;
		sleep_for(nanoseconds(10));
		sleep_until(system_clock::now() + seconds(1));
	}

	cout << endl << "0 - BACK" << endl;
	do {
		test = checkinputchoice(input, 0, 0);
		if (test != 0 )
			cerr << "Invalid option! Press 0 to go back." << endl;
    } while (test != 0 && test != 2);
}

// PACKET MANAGMENT
// add packet - falta validar destinos secundarios
void Agency::addPacket() {
	int test = 0; string input = ""; int temp = 0, numPackets = 0;
	double pricePerPerson;
	char comma = ',';
	vector <string> destinations = {};
	stringstream ssin;
	string sites, site;
	Packet packet;
    bool validDate1, validDate2, validDates, back,invalidDestinations;
	unsigned int year1, month1, day1, year2, month2, day2;
	Date date1, date2;

	do {
        invalidDestinations = false;
        back = false;
		system("cls");
		cout << "_____________________________________________________" << endl << endl;
		cout << "\t\t   Create Packet " << endl;
		cout << "_____________________________________________________" << endl << endl;
        cout << "(Press Ctrl+z to go back)" << endl << endl;
		do
		{
          cout << "Packet's Id: ";
          test = checkIdInput(input);
          if (test == 3 || test == 1)
            cout << "A Packet with that Id already exists! Please try again." << endl;
          if (test == 2)
            cout << "Invalid Id! Please try again!" << endl;
        } while (test != 0 && test != 5);
        if (test == 5)
          break;
		packet.setId(stoi(input));
		destinations.clear();
		do {
          cout << "Main Destination/Site: ";
          test = checkDestinationInput(input);
			if (test == 1)
				cout << "Invalid Destination! Please try again." << endl;
		} while (test != 0 && test!=5);
        if (test == 5)
          break;
		destinations.push_back(input);
		do {
			ssin.clear();
			sites = "";
			site = "";
			if (test != 0)
				cout << "Invalid Turistic Attractions! Please try again." << endl;
			cout << "Turistic Attractions (if not applied enter - , otherwise site1, site2, ...): ";
			getline(cin, sites);
            if (cin.eof()) {
              cin.clear();
              back = true;
              break;
            }
			stringstream ssin(sites);
			while (getline(ssin, sites, comma)) {
				site = regex_replace(sites, regex("^ +| +$|( ) +"), "$1");
                test = checkOneSiteInput(site);
                if(test == 1){
                  invalidDestinations = true;
                  break;
                }
				if (site == "-") {
					test = 0;
					break;
				}
				destinations.push_back(site);
			}
            if (invalidDestinations)
              test = 1;
		} while (test != 0);
        if (back)
          break;
		packet.setSites(destinations);
		do {
			do {
				cout << "Departure date (yyyy/mm/dd): ";
				validDate1 = checkDateInput(year1, month1, day1);
				if (!validDate1)
					cerr << "Invalid date! Try again!" << endl;
			} while (!validDate1);

			date1.setYear(year1);
			date1.setMonth(month1);
			date1.setDay(day1);

			do {
				cout << "Arrival date (yyyy/mm/dd): ";
				validDate2 = checkDateInput(year2, month2, day2);
				if (!validDate2)
					cerr << "Invalid date! Try again!" << endl;
			} while (!validDate2);

			date2.setYear(year2);
			date2.setMonth(month2);
			date2.setDay(day2);

			validDates = (compareDates(date1, date2));

			if (!validDates) {
				cerr << "Invalid dates! Try again!" << endl << endl;
			}
		} while (!validDates);
		packet.setBeginDate(date1);
		packet.setEndDate(date2);
		do {
          cout << "Price per Person: ";
          cin >> pricePerPerson;
		  if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "Invalid Price per Person! Please try again." << endl;
			} 
          else if (cin.eof()) {
            back = true;
          }
		} while (cin.fail());
        if (back)
          break;
		packet.setPricePerPerson(pricePerPerson);
		do {
			if (test == 1)
				cout << "Invalid Maximum People! Please try again." << endl;
			cout << "Maximum People: ";
			test = checkNumberInput(input);
		} while (test != 0 && test!=5);
        if (test == 5)
          break;
		packet.setMaxPeople(stoi(input));
		do {
          cout << "Reserved Seats: ";
          test = checkNumberInput(input);
          if (test == 5)
            break;
          else if (test == 1)
            cout << "Invalid Reserved Seats! Please try again." << endl;
          else if (packet.getMaxPeople() < stoul(input))
            cout << "Invalid! More Reserved Seats than Maximum People!" << endl;
		} while (test != 0 || (packet.getMaxPeople() < stoul(input)));
        if (test == 5) {
          break;
        }
		packet.setReservedSeats(stoi(input));
		if (packet.getReservedSeats() == packet.getMaxPeople()) {
			cout << "The Pack was set as Unavailable!" << endl;
			packet.setAvailable(false);
		}
		else {
			cout << "Is the new pack available?" << endl;
			cout << "1 - Yes" << endl;
			cout << "2 - No" << endl;
			do {
				test = checkinputchoice(input, 1, 2);
				if (test != 0)
					cerr << "Invalid option! Please try again." << endl;
			} while (test != 0 && test!=2);
            if (test == 2)
              break;
			if (stoi(input) == 1) {
				packet.setAvailable(true);
				cout << "The Pack was set as Available!" << endl;
			}
			else {
				packet.setAvailable(false);
				cout << "The Pack was set as Unavailable!" << endl;
			}
		}
		//added
		system("cls");
		cout << "_____________________________________________________" << endl << endl;
		cout << "\t\t   Create Packet " << endl;
		cout << "_____________________________________________________" << endl << endl;
		cout << "---------------- New Packet data ----------------" << endl << endl;
		packet.showPacket();
		cout << endl << "Do you confirm this data?" << endl;
		cout << "1 - Yes" << endl;
		cout << "2 - No" << endl;
		do {
			test = checkinputchoice(input, 1, 2);
			if (test != 0)
				cerr << "Invalid option! Please try again." << endl;
		} while (test != 0);
		temp = stoi(input);
		if (stoi(input) == 1) {
			packets.push_back(packet);
            for (unsigned i = 0; i < clients.size(); i++) {
              for (unsigned j = 0; j < clients.at(i).getInexistentPackets().size(); j++) {
                if (packet.getId() == clients.at(i).getInexistentPackets().at(j)) {
                  clients.at(i).inexistentPacketToExistent(packet.getId(),packet);
                }
              }
            }
			lastmodifiedpack = packet.getId();
			temp = 0;
			cout << "The Packet was successfully created!" << endl << endl;
		}
		else {
			cout << "The Packet was not created!" << endl << endl;
		}

		cout << "1 - New Packet" << endl;
		cout << "0 - Exit" << endl;
		do {
			test = checkinputchoice(input, 0, 1);
			if (test != 0)
				cerr << "Invalid option! Please try again." << endl;
		} while (test != 0 && test !=2);
        if (test == 2)
          temp = 0;
        else
		  temp = stoi(input);
	} while (temp != 0);
}
//"remove" packet = set packet as unavailable
void Agency::removePacketByPacketList() {
	int test = 0, index = 0; string input = ""; int temp = 0;
	do
	{
		system("cls");
		cout << "_____________________________________________________" << endl << endl;
		cout << "\t\t   Remove Packet " << endl;
		cout << "_____________________________________________________" << endl << endl;
        cout << "(Press Ctrl+z to go back)" << endl << endl;
		if (packets.size() != 0) {

			for (unsigned int i = 0; i < packets.size(); i++)
			{
				cout << i + 1 << " - Packet's Id: " << packets.at(i).getId() << endl;
				cout << "Packet's Sites: ";
				packets.at(i).showSites();
				cout << endl;
			}
			do {
				cout << "Choose a number: ";
				test = checkinputchoice(input, 1, (int)packets.size());
				if (test != 0)
					cerr << "Invalid number! Please try again." << endl;
			} while (test != 0 && test != 2);
            if (test == 2)
              break;
			index = stoi(input) - 1;

			system("cls");
			cout << "_____________________________________________________" << endl << endl;
			cout << "\t\t   Remove Packet " << endl;
			cout << "_____________________________________________________" << endl << endl;
			cout << "-----Data of Packet to Delete-----" << endl << endl;
			packets.at(index).showPacket();

			cout << endl << "Do you want to set this packet as unavailable?" << endl;
			cout << "1 - Yes" << endl;
			cout << "2 - No" << endl;

			do {
				test = checkinputchoice(input, 1, 2);
				if (test != 0)
					cerr << "Invalid option! Please try again." << endl;
			} while (test != 0);

			if (stoi(input) == 1)
			{
				packets.at(index).setAvailable(false);
				lastmodifiedpack = packets.at(index).getId();
				temp = 0;
				cout << "The packet was successfully set as unavilable!" << endl << endl;
			}
			else {
				cout << "The packet was not removed!" << endl << endl;
			}

			cout << "Delete another packet?" << endl;
			cout << "1 - Yes" << endl;
			cout << "0 - No" << endl;
			do {
				test = checkinputchoice(input, 0, 1);
				cerr << "Invalid option! Please try again." << endl;
			} while (test != 0 && test !=2);
            if (test == 2)
              temp = 0;
            else
			  temp = stoi(input);
		}
		else {
			cerr << "No packets to remove!" << endl;
			sleep_for(nanoseconds(10));
			sleep_until(system_clock::now() + seconds(1));
			temp = 0;
		}

	} while (temp != 0);
}
void Agency::removePacketById() {
	int test = 0, index = 0; string input = ""; int temp = 0;
	bool available=false;
	do
	{
		system("cls");
		cout << "_____________________________________________________" << endl << endl;
		cout << "\t\t   Remove Packet " << endl;
		cout << "_____________________________________________________" << endl << endl;
        cout << "(Press Ctrl+z to go back)" << endl << endl;
		if (packets.size() != 0) {
			do {
				cout << "Packet's Id: ";
				test = checkIdInput(input);
				if (test != 1 && test != 3)
					cout << "No packet was found with that Id number. Please try again." << endl;
			} while (test != 1 && test!= 3 && test!=5);
            if (test == 5)
              break;
            else
			  test = 0;

			for (unsigned int i = 0; i < packets.size(); i++) {
				if (packets.at(i).getId() == stoi(input)) {
					if (packets.at(i).getAvailable()) {
						available = true;
						index = i;
						break;
					}
					else
						available = false;
				}
			}

			system("cls");
			cout << "_____________________________________________________" << endl << endl;
			cout << "\t\t   Remove Packet " << endl;
			cout << "_____________________________________________________" << endl << endl;

			if (available) {
				cout << "-----Data of Packet to Delete-----" << endl << endl;
				packets.at(index).showPacket();

				cout << endl << "Do you want to delete this packet?" << endl;
				cout << "1 - Yes" << endl;
				cout << "2 - No" << endl;

				do {
					test = checkinputchoice(input, 1, 2);
					if (test != 0)
						cerr << "Invalid option! Please try again." << endl;
				} while (test != 0);

				if (stoi(input) == 1)
				{
					packets.at(index).setAvailable(false);
					lastmodifiedpack = packets.at(index).getId();
					temp = 0;
					cout << "The packet was successfully set as unavailable!" << endl << endl;
				}
				else {
					cout << "The packet was not removed!" << endl << endl;
				}
			}
			else
				cout << "That packet is already unavailable!" << endl;

			cout << "Delete another packet?" << endl;
			cout << "1 - Yes" << endl;
			cout << "0 - No" << endl;
			do {
				test = checkinputchoice(input, 0, 1);
				if (test != 0)
					cerr << "Invalid option! Please try again." << endl;
			} while (test != 0 && test!=2);
            if (test == 2)
              temp = 0;
            else
			  temp = stoi(input);
		}
		else {
			cerr << "No packets to remove!" << endl;
			sleep_for(nanoseconds(10));
			sleep_until(system_clock::now() + seconds(1));
			temp = 0;
		}
	} while (temp != 0);
}
//change packet
void Agency::changePacketId(unsigned index) {
	string input = "";
	int test = 0;
	do {
      cout << "Packet's Id: ";
      test = checkIdInput(input);
		if (test == 2)
			cout << "Not a Valid Id! Try again." << endl;
		else if (test == 1 || test == 3)
			cout << "A Packet with that Id already exists!" << endl;
	} while (test != 0 && test!=5);
    if (test != 5) {
      packets.at(index).setId(stoi(input));
      lastmodifiedpack = packets.at(index).getId();
      cout << endl << "Data Modified" << endl;
    }
}
//falta validar destinos secundarios
void Agency::changePacketSites(unsigned index) {
  string input = "", sites,site;
  stringstream ssin;
  bool back = false,invalidDestinations;
  int test = 0;
  vector <string> destinations;
  char comma = ',';
  do {
    if (test == 1)
      cout << "Invalid Destination! Please try again." << endl;
    cout << "Main Destination/Site: ";
    test = checkDestinationInput(input);
  } while (test != 0 && test !=5);
  if(test != 5){
    destinations.push_back(input);
    do {
      invalidDestinations = false;
      ssin.clear();
      sites = "";
      site = "";
      if (test != 0)
        cout << "Invalid Turistic Attractions! Please try again." << endl;
      cout << "Turistic Attractions (if not applied enter - , otherwise site1, site2, ...): ";
      getline(cin, sites);
      if (cin.eof()) {
        cin.clear();
        back = true;
        break;
      }
      stringstream ssin(sites);
      while (getline(ssin, sites, comma)) {
        site = regex_replace(sites, regex("^ +| +$|( ) +"), "$1");
        test = checkOneSiteInput(site);
        if (test == 1) {
          invalidDestinations = true;
          break;
        }
        if (site == "-") {
          test = 0;
          break;
        }
        destinations.push_back(site);
      }
      if (invalidDestinations)
        test = 1;
    } while (test != 0);
    if (!back) {
      packets.at(index).setSites(destinations);
      lastmodifiedpack = packets.at(index).getId();
      cout << endl << "Data Modified" << endl;
    }
  }
}
void Agency::changePacketDates(unsigned index) {
  string input = "";
  int test = 0;
  bool validDate1, validDate2, validDates;
  unsigned int year1, month1, day1, year2, month2, day2;
  Date date1, date2;
  do {
    do {
      cout << "Departure date (yyyy/mm/dd): ";
      validDate1 = checkDateInput(year1, month1, day1);
      if (!validDate1)
        cerr << "Invalid date! Try again!" << endl;
    } while (!validDate1);

    date1.setYear(year1);
    date1.setMonth(month1);
    date1.setDay(day1);

    do {
      cout << "Arrival date (yyyy/mm/dd): ";
      validDate2 = checkDateInput(year2, month2, day2);
      if (!validDate2)
        cerr << "Invalid date! Try again!" << endl;
    } while (!validDate2);

    date2.setYear(year2);
    date2.setMonth(month2);
    date2.setDay(day2);

    validDates = (compareDates(date1, date2));

    if (!validDates) {
      cerr << "Invalid dates! Try again!" << endl << endl;
    }
  } while (!validDates);
  packets.at(index).setBeginDate(date1);
  packets.at(index).setEndDate(date2);
  lastmodifiedpack = packets.at(index).getId();
}
void Agency::changePacketBeginDate(unsigned index) {
  string input = "";
  int test = 0;
  bool validDate1, validDates;
  unsigned int year1, month1, day1;
  Date date1;
  do {
    do {
      cout << "Departure date (yyyy/mm/dd): ";
      validDate1 = checkDateInput(year1, month1, day1);
      if (!validDate1)
        cerr << "Invalid date! Try again!" << endl;
    } while (!validDate1);

    date1.setYear(year1);
    date1.setMonth(month1);
    date1.setDay(day1);


    validDates = (compareDates(date1, packets.at(index).getEndDate()));

    if (!validDates) {
      cerr << "Begin date must be before End date: ";
      packets.at(index).getEndDate().showDate();
      cout << "! Try again!" << endl << endl;
    }
  } while (!validDates);
  packets.at(index).setBeginDate(date1);
  lastmodifiedpack = packets.at(index).getId();
}
void Agency::changePacketEndDate(unsigned index) {
  string input = "";
  int test = 0;
  bool validDate2, validDates;
  unsigned int year2, month2, day2;
  Date date2;
  do {
    do {
      cout << "Arrival date (yyyy/mm/dd): ";
      validDate2 = checkDateInput(year2, month2, day2);
      if (!validDate2)
        cerr << "Invalid date! Try again!" << endl;
    } while (!validDate2);

    date2.setYear(year2);
    date2.setMonth(month2);
    date2.setDay(day2);

    validDates = (compareDates(packets.at(index).getBeginDate(), date2));

    if (!validDates) {
      cerr << "End date must be after Begin date: ";
      packets.at(index).getBeginDate().showDate();
      cout << "! Try again!" << endl << endl;
    }
  } while (!validDates);
  packets.at(index).setEndDate(date2);
  lastmodifiedpack = packets.at(index).getId();
}
void Agency::changePacketPrice(unsigned index) {
  string input = "";
  int test = 0;
  double pricePerPerson;
  do {
    if (cin.fail()) {
      cin.clear();
      cin.ignore(1000, '\n');
      cout << "Invalid Price per Person! Please try again." << endl;
    }
    cout << "Price per Person: ";
    cin >> pricePerPerson;
  } while (cin.fail());
  packets.at(index).setPricePerPerson(pricePerPerson);
  lastmodifiedpack = packets.at(index).getId();
}
void Agency::changePacketMaxPeople(unsigned index) {
  string input = "";
  int test = 0;
  do {
    cout << "Maximum People: ";
    test = checkNumberInput(input);
    if (test == 1)
      cout << "Invalid Maximum People! Please try again." << endl;
  } while (test != 0 && test!=5);
  if (test != 5) {
    packets.at(index).setMaxPeople(stoi(input));
    lastmodifiedpack = packets.at(index).getId();
    cout << endl << "Data Modified" << endl;
  }
}
void Agency::changePacketReservedSeats(unsigned index) {
  string input = "";
  int test = 0;
  do {
    cout << "Reserved Seats: ";
    test = checkNumberInput(input);
    if (test == 5)
      break;
    else if (test == 1)
      cout << "Invalid Reserved Seats! Please try again." << endl;
    if (packets.at(index).getMaxPeople() < stoul(input))
      cout << "Invalid! More Reserved Seats than Maximum People!" << endl;
  } while (test != 0 || (packets.at(index).getMaxPeople() < stoul(input)));
  if(test != 5){
    packets.at(index).setReservedSeats(stoi(input));
    lastmodifiedpack = packets.at(index).getId();
    cout << endl << "Data Modified" << endl;
  }
}
void Agency::changePacketAvailability(unsigned index) {
  string input = "";
  int test = 0;
  if (packets.at(index).getAvailable()) {
    cout << "1 - Set Packet " << packets.at(index).getId() << " as Unavailable!" << endl;
    cout << "0 - BACK (Change Packet's Menu)" << endl;
    do {
      test = checkinputchoice(input, 0, 1);
      if (test != 0)
        cerr << "Invalid option! Please try again." << endl;
    } while (test != 0 && test!=2);

    if (stoi(input) == 1) {
      packets.at(index).setAvailable(false);
      lastmodifiedpack = packets.at(index).getId();
      cout << "Packet " << packets.at(index).getId() << " is now Unavailable!" << endl;
    }
  }
  else if ((packets.at(index).getAvailable() == false) && (packets.at(index).getMaxPeople() > packets.at(index).getReservedSeats())) {
    cout << "1 - Set Packet " << packets.at(index).getId() << " as Available!" << endl;
    cout << "0 - BACK (Change Packet's Menu)" << endl;
    do {
      test = checkinputchoice(input, 0, 1);
      if (test != 0)
        cerr << "Invalid option! Please try again." << endl;
    } while (test != 0 && test!=2);
    if (test == 2)
      input = "0";
    if (stoi(input) == 1) {
      packets.at(index).setAvailable(true);
      lastmodifiedpack = packets.at(index).getId();
      cout << "Packet " << packets.at(index).getId() << " is now Available!" << endl;
    }
  }
  else
    cout << "No actions available! Unavailable Packet has all it's seats reserved!";
}
// show
void Agency::showPacketsByDate() {
	int test = 0, index = 0; string input = ""; int temp = 0;
	unsigned int year1, month1, day1, year2, month2, day2;
	Date date1, date2;
	bool noPacks;
	bool validDate1, validDate2, validDates;

	do
	{
		noPacks = true;
		system("cls");
		cout << "_____________________________________________________" << endl << endl;
		cout << "\t\t   Show Packet " << endl;
		cout << "_____________________________________________________" << endl << endl;
		cout << "-----Show available Packets between two dates-----" << endl << endl;

		if (packets.size() != 0) {
			//ask dates until valid
			do {
				do {
					cout << "Departure date (yyyy/mm/dd): ";
					validDate1 = checkDateInput(year1, month1, day1);
					if (!validDate1)
						cerr << "Invalid date! Try again!" << endl;
				} while (!validDate1);

				date1.setYear(year1);
				date1.setMonth(month1);
				date1.setDay(day1);

				do {
					cout << "Arrival date (yyyy/mm/dd): ";
					validDate2 = checkDateInput(year2, month2, day2);
					if (!validDate2)
						cerr << "Invalid date! Try again!" << endl;
				} while (!validDate2);

				date2.setYear(year2);
				date2.setMonth(month2);
				date2.setDay(day2);

				validDates = (compareDates(date1, date2));

				if (!validDates) {
					cerr << "Invalid dates! Try again!" << endl << endl;
				}
			} while (!validDates);

			system("cls");
			cout << "_____________________________________________________" << endl << endl;
			cout << "\t\t   Show Packet " << endl;
			cout << "_____________________________________________________" << endl << endl;
			cout << "-----Show available Packets between two dates-----" << endl << endl;

			//checks if there are packets between the dates
			for (unsigned i = 0; i < packets.size(); i++) {
				if (compareDates(date1, packets.at(i).getBeginDate()) && compareDates(packets.at(i).getEndDate(), date2)) {
					packets.at(i).showPacket();
					cout << endl;
					noPacks = false;
				}
			}
			if (noPacks) {
				cout << "No packs were found between ";
				date1.showDate();
				cout << " and ";
				date2.showDate();
				cout << "!" << endl << endl;
			}

			cout << "1 - Change Dates" << endl;
			cout << "0 - Exit" << endl;
			do {
				test = checkinputchoice(input, 0, 1);
				if (test != 0)
					cerr << "Invalid option! Please try again." << endl;
			} while (test != 0 && test!=2);
            if (test == 2)
              temp = 0;
            else
			  temp = stoi(input);
		}
		else {
			cerr << "No packets to show!" << endl;
			sleep_for(nanoseconds(10));
			sleep_until(system_clock::now() + seconds(1));
			temp = 0;
		}
	} while (temp != 0);
};
void Agency::showPacketInfo() {
	int test = 0, index = 0; string input = ""; int temp = 0;
	do
	{
		system("cls");
		cout << "_____________________________________________________" << endl << endl;
		cout << "\t\t   Show Packet " << endl;
		cout << "_____________________________________________________" << endl << endl;

		if (packets.size() != 0) {
			do {
				cout << "Packet's Id: ";
				test = checkIdInput(input);
				if (test != 1 && test != 3)
					cout << "No packet was found with that Id. Please try again." << endl;
			} while (test != 1 && test!=5 && test != 3);
            if (test == 5)
              break;
            else
			  test = 0;

			for (unsigned int i = 0; i < packets.size(); i++) {
				if (packets.at(i).getId() == stoi(input)) {
					index = i;
					break;
				}
			}

			system("cls");
			cout << "_____________________________________________________" << endl << endl;
			cout << "\t\t   Show Packet " << endl;
			cout << "_____________________________________________________" << endl << endl;
			cout << "-----Data of Packet " << packets.at(index).getId() << "-----" << endl << endl;
			packets.at(index).showPacket();

			cout << endl << "Show another packet?" << endl;
			cout << "1 - Yes" << endl;
			cout << "0 - No" << endl;
			do {
				test = checkinputchoice(input, 0, 1);
				if (test != 0)
					cerr << "Invalid option! Please try again." << endl;
			} while (test != 0 && test!=2);
            if (test == 2)
              break;
            else
			  temp = stoi(input);
		}
		else {
			cerr << "No packets to show!" << endl;
			sleep_for(nanoseconds(10));
			sleep_until(system_clock::now() + seconds(1));
			temp = 0;
		}
	} while (temp != 0);
}
void Agency::showAllPacketsInfo() {
	int test = 0;
	string input = "";

	system("cls");
	cout << "_____________________________________________________" << endl << endl;
	cout << "\t\t   Packets List " << endl;
	cout << "_____________________________________________________" << endl << endl;

	if (packets.size() != 0) {
		for (unsigned i = 0; i < packets.size(); i++) {
			cout << "Packet " << i + 1 << ":" << endl;
			packets.at(i).showPacket();
			cout << endl;
		}
	}
	else {
		cerr << "No packets to show!" << endl;
		sleep_for(nanoseconds(10));
		sleep_until(system_clock::now() + seconds(1));
	}

	cout << endl << "0 - BACK" << endl;
	do {
		test = checkinputchoice(input, 0, 0);
		if (test != 0 && test!=2)
			cerr << "Invalid option! Press 0 to go back." << endl;
	} while (test != 0 && test !=2);
}
void Agency::showPacketsByDestination() {
	int test = 0, index = 0; string input = ""; int temp = 0;
	string destination;
	bool found;
	int invalidDestination;

	do
	{
		found = false;
		system("cls");
		cout << "_____________________________________________________" << endl << endl;
		cout << "\t\t   Show Packet " << endl;
		cout << "_____________________________________________________" << endl << endl;
		cout << "-----Show available Packets by Destination-----" << endl << endl;

		if (packets.size() != 0) {
			//ask Destination until valid
			do {
				cout << "Destination: ";
				invalidDestination = checkDestinationInput(destination);
				if (invalidDestination == 1) {
					cerr << "Invalid Destination! Try again!" << endl << endl;
				}
			} while (invalidDestination!=0 && invalidDestination != 5);
            if (invalidDestination == 5)
              break;
			system("cls");
			cout << "_____________________________________________________" << endl << endl;
			cout << "\t\t   Show Packet " << endl;
			cout << "_____________________________________________________" << endl << endl;
			cout << "-----Show available Packets by Destination-----" << endl << endl;

			//checks if there are packets with input destination
			for (unsigned i = 0; i < packets.size(); i++) {
				for (unsigned j = 0; j < packets.at(i).getSites().size(); j++) {
					if (caseInsensitiveStringCompare(packets.at(i).getSites().at(j), destination)) {
						packets.at(i).showPacket();
						cout << endl;
						found = true;
						break;
					}
				}
			}
			if (!found) {
				cout << "No packets were found with Destination: " << destination;
				cout << "!" << endl << endl;
			}

			cout << "1 - Change Destination" << endl;
			cout << "0 - Exit" << endl;
			do {
				test = checkinputchoice(input, 0, 1);
				if (test != 0)
					cerr << "Invalid option! Please try again." << endl;
			} while (test != 0 && test!=2);
            if (test == 2)
              temp = 0;
            else
			  temp = stoi(input);
		}
		else {
			cerr << "No packets to show!" << endl;
			sleep_for(nanoseconds(10));
			sleep_until(system_clock::now() + seconds(1));
			temp = 0;
		}
	} while (temp != 0);
};
void Agency::showPacketsByDateAndDestination() {
	int test = 0, index = 0; string input = ""; int temp = 0;
	string destination;
	bool found, validDate1, validDate2, validDates;
    int invalidDestination;
	unsigned int year1, month1, day1, year2, month2, day2;
	Date date1, date2;

	do
	{
		found = false;
		system("cls");
		cout << "_____________________________________________________" << endl << endl;
		cout << "\t\t   Show Packet " << endl;
		cout << "_____________________________________________________" << endl << endl;
		cout << "-----Show available Packets by Date and Destination-----" << endl << endl;

		if (packets.size() != 0) {
			//ask dates until valid
			do {
				do {
					cout << "Departure date (yyyy/mm/dd): ";
					validDate1 = checkDateInput(year1, month1, day1);
					if (!validDate1)
						cerr << "Invalid date! Try again!" << endl;
				} while (!validDate1);

				date1.setYear(year1);
				date1.setMonth(month1);
				date1.setDay(day1);

				do {
					cout << "Arrival date (yyyy/mm/dd): ";
					validDate2 = checkDateInput(year2, month2, day2);
					if (!validDate2)
						cerr << "Invalid date! Try again!" << endl;
				} while (!validDate2);

				date2.setYear(year2);
				date2.setMonth(month2);
				date2.setDay(day2);

				validDates = (compareDates(date1, date2));

				if (!validDates) {
					cerr << "Invalid dates! Try again!" << endl << endl;
				}
			} while (!validDates);

			//ask Destination until valid
			do {
				cout << "Destination: ";
				invalidDestination = checkDestinationInput(destination);
                if (invalidDestination == 1) {
                  cerr << "Invalid Destination! Try again!" << endl << endl;
                }
            } while (invalidDestination != 0 && invalidDestination != 5);
            if (invalidDestination == 5)
              break;
			system("cls");
			cout << "_____________________________________________________" << endl << endl;
			cout << "\t\t   Show Packet " << endl;
			cout << "_____________________________________________________" << endl << endl;
			cout << "-----Show available Packets by Date and Destination-----" << endl << endl;

			//checks if there are packets between the dates
			for (unsigned i = 0; i < packets.size(); i++) {
				if (compareDates(date1, packets.at(i).getBeginDate()) && compareDates(packets.at(i).getEndDate(), date2)) {
					for (unsigned j = 0; j < packets.at(i).getSites().size(); j++) {
						if (caseInsensitiveStringCompare(packets.at(i).getSites().at(j), destination)) {
							packets.at(i).showPacket();
							cout << endl;
							found = true;
							break;
						}
					}
				}
			}

			if (!found) {
				cout << "No packs were found between ";
				date1.showDate();
				cout << " and ";
				date2.showDate();
				cout << " with Destination: " << destination;
				cout << "!" << endl << endl;
			}

			cout << "1 - Change Dates and Destination" << endl;
			cout << "0 - Exit" << endl;
			do {
				test = checkinputchoice(input, 0, 1);
				if (test != 0)
					cerr << "Invalid option! Please try again." << endl;
			} while (test != 0 && test != 2);
            if (test == 2)
              temp = 0;
            else
              temp = stoi(input);
		}
		else {
			cerr << "No packets to show!" << endl;
			sleep_for(nanoseconds(10));
			sleep_until(system_clock::now() + seconds(1));
			temp = 0;
		}
	} while (temp != 0);
}
void Agency::packetsSoldToSpecificClient() {
  int test = 0, index = 0;
  string input = "";

  do
  {
    system("cls");
    if (clients.size() != 0) {

      cout << "_____________________________________________________" << endl << endl;
      cout << "\t\t   Sold Packets " << endl;
      cout << "_____________________________________________________" << endl << endl;

      do {
        cout << "Client's VAT: ";
        test = checkVATInput(input);
        if (test != 2)
          cout << "No client was found with that VAT number. Please try again." << endl;
      } while (test != 2 && test!=5);
      if (test == 5)
        break;
      else
        test = 0;
  
      for (unsigned i = 0; i < clients.size(); i++) {
        if (clients.at(i).getVATnumber() == stoi(input)) {
          index = i;
          break;
        }
      }

      system("cls");
      cout << "_____________________________________________________" << endl << endl;
      cout << "\t\t   Sold Packets " << endl;
      cout << "_____________________________________________________" << endl << endl;
      cout << "-----Packets Sold to " << clients.at(index).getName() << " - VAT " << clients.at(index).getVATnumber() << "-----" << endl << endl;

      if (clients.at(index).getPacketList().empty() && clients.at(index).getInexistentPackets().empty()) {
        cout << "No Packets to show!" << endl;
      }
      else if(clients.at(index).getPacketList().empty()){
        for (unsigned i = 0; i < clients.at(index).getInexistentPackets().size();i++){
          cout << "No data available on packet " << clients.at(index).getInexistentPackets().at(i) << "!" << endl << endl;
        }
      }
      else if (clients.at(index).getInexistentPackets().empty()) {
        for (unsigned i = 0; i < clients.at(index).getPacketList().size(); i++) {
          clients.at(index).getPacketList().at(i).showPacket();
          cout << endl;
        }
      }
      else {
        for (unsigned i = 0; i < clients.at(index).getInexistentPackets().size(); i++) {
          cout << "No data available on packet " << clients.at(index).getInexistentPackets().at(i) << "!" << endl << endl;
        }
        for (unsigned i = 0; i < clients.at(index).getPacketList().size(); i++) {
          clients.at(index).getPacketList().at(i).showPacket();
          cout << endl;
        }
      }

      cout << "1 - Show Packets sold to other client" << endl;
      cout << "0 - Exit (Sold Packets Menu)" << endl;
      do{
        test = checkinputchoice(input, 0, 1);
        if (test != 0)
          cerr << "Invalid option! Please try again." << endl;
      } while (test != 0 && test!=2);
      if (test == 2)
        break;
      if(stoi(input) == 1){
        input = "2";
      }
    }
    else {
      cerr << "No packets to show!" << endl;
      sleep_for(nanoseconds(10));
      sleep_until(system_clock::now() + seconds(1));
      exit(0);
    }
  } while (stoi(input) == 2);
};
void Agency::packetsSoldToAllClients() {
  int test = 0;
  string input = "";

  system("cls");
  if (clients.size() != 0) {

    cout << "_____________________________________________________" << endl << endl;
    cout << "\t\t   All Sold Packets " << endl;
    cout << "_____________________________________________________" << endl << endl;

    for (unsigned j = 0; j < clients.size(); j++) {
      cout << "-----Packets Sold to " << clients.at(j).getName() << " - VAT " << clients.at(j).getVATnumber() << "-----" << endl << endl;

      if (clients.at(j).getPacketList().empty() && clients.at(j).getInexistentPackets().empty()) {
        cout << "No Packets to show!" << endl;
      }
      else if (clients.at(j).getPacketList().empty()) {
        for (unsigned i = 0; i < clients.at(j).getInexistentPackets().size(); i++) {
          cout << "No data available on packet " << clients.at(j).getInexistentPackets().at(i) << "!" << endl << endl;
        }
      }
      else if (clients.at(j).getInexistentPackets().empty()) {
        for (unsigned i = 0; i < clients.at(j).getPacketList().size(); i++) {
          clients.at(j).getPacketList().at(i).showPacket();
          cout << endl;
        }
      }
      else {
        for (unsigned i = 0; i < clients.at(j).getInexistentPackets().size(); i++) {
          cout << "No data available on packet " << clients.at(j).getInexistentPackets().at(i) << "!" << endl << endl;
        }
        for (unsigned i = 0; i < clients.at(j).getPacketList().size(); i++) {
          clients.at(j).getPacketList().at(i).showPacket();
          cout << endl;
        }
      }
    }
      cout << endl << "0 - Exit (Sold Packets Menu)" << endl;
      do {
        test = checkinputchoice(input, 0, 0);
        if (test != 0)
          cerr << "Invalid option! Please try again." << endl;
      } while (test != 0 && test!=2);
  }
  else {
    cerr << "No packets to show!" << endl;
    sleep_for(nanoseconds(10));
    sleep_until(system_clock::now() + seconds(1));
    exit(0);
  }
};

void Agency::showSoldPacketsDataByClients() {
	double soma = 0;
	int agregado = 0;
    int test = 0;
    string input = "";
	for (unsigned int i = 0; i < clients.size(); i++)
		soma = soma + (int)clients.at(i).getPacketList().size();
	system("cls");
	cout << "_________________________________________________________________________" << endl << endl;
	cout << "\t\t  Sold Packet Data (According To Clients) " << endl;
	cout << "_________________________________________________________________________" << endl << endl;
	if (soma == 0)
		cout << "No Pack was sold" << endl;
	else
	{
		if (soma == 1)
			cout << "1 Pack was sold" << endl;
		else
			cout << "In total, there were " << soma << " packs sold" << endl;
	}
	soma = 0;
	for (unsigned int i = 0; i < clients.size(); i++)
	{
		agregado = clients.at(i).getFamilySize();
		for (unsigned int j = 0; j < clients.at(i).getPacketList().size(); j++)
		{
			soma = soma + agregado * clients.at(i).getPacketList().at(j).getPricePerPerson();
		}
	}
	cout << "Total value by sold packs: " << soma << endl ;
    cout << endl << "0 - BACK" << endl;
    do {
      test = checkinputchoice(input, 0, 0);
      if (test != 0 && test != 2)
        cerr << "Invalid option! Press 0 to go back." << endl;
    } while (test != 0 && test != 2);
}
void Agency::showSoldPacketsDataByPacks() {
	//Número total de pacotes vendidos :
	//Pelo packets.txt -> soma dos lugares reservados em cada pacote
  int test = 0;
  string input = "";
	double soma = 0;
	for (unsigned int i = 0; i < packets.size(); i++)
		soma = soma + packets.at(i).getReservedSeats();
	system("cls");
	cout << "_________________________________________________________________________" << endl << endl;
	cout << "\t\t  Sold Packet Data (According To Packets) " << endl;
	cout << "_________________________________________________________________________" << endl << endl;
	if (soma == 0)
		cout << "No Pack was sold" << endl;
	else
	{
		if (soma == 1)
			cout << "1 Pack was sold" << endl;
		else
			cout << "In total, there were " << soma << " packs sold" << endl;
	}
	soma = 0;

	for (unsigned int i = 0; i < packets.size(); i++)
		soma = soma + packets.at(i).getReservedSeats() * packets.at(i).getPricePerPerson();
	cout << "Total value by sold packs: " << soma << endl;
    cout << endl << "0 - BACK" << endl;
    do {
      test = checkinputchoice(input, 0, 0);
      if (test != 0 && test != 2)
        cerr << "Invalid option! Press 0 to go back." << endl;
    } while (test != 0 && test != 2);
	//Valor total de pacotes vendidos :
	//Pelo packets.txt -> para cada pack multiplicar o numero de lugares reservados pelo preço por pessoa, somar os valores de cada pack
}
void Agency::showNMostVisistedPlaces() {
	map <string, int> map1;
	int n = 0, testinput = 0;
	string input = "";
	system("cls");
	cout << "_____________________________________________________" << endl << endl;
	cout << "\t\t  N Most Visited Places " << endl;
	cout << "_____________________________________________________" << endl << endl;

	for (unsigned int i = 0; i < packets.size(); i++)
	{
		for (unsigned int j = 0; j < packets.at(i).getSites().size(); j++)
		{
			if (map1.find(packets.at(i).getSites().at(j)) == map1.end()) {
				// not found
				map1.insert(pair<string, int>(packets.at(i).getSites().at(j), packets.at(i).getReservedSeats()));
			}
			else {
				// found
				int temp = 0;
				temp = map1[packets.at(i).getSites().at(j)];
				temp = temp + packets.at(i).getReservedSeats();
				map1[packets.at(i).getSites().at(j)] = temp;
			}
		}
	}

	cout << "Choose a number N between 1 and " << map1.size() << " (0 to exit) : ";
	do {
		testinput = checkinputchoice(input, 0, (int)map1.size());
		if (testinput != 0 && testinput != 2)
			cerr << "Invalid option! Please try again." << endl;
	} while (testinput != 0 && testinput != 2); if (testinput == 2) { input = "0"; }
	if (stoi(input) != 0)
	{
		n = stoi(input);
		//// Organizar por ordem decrescente
		typedef pair<string, int> pair;

		// create a empty vector of pairs
		vector<pair> vec;

		// copy key-value pairs from the map to the vector
		copy(map1.begin(), map1.end(), back_inserter<vector<pair>>(vec));

		// sort the vector by increasing order of its pair's second value
		// if second value are equal, order by the pair's first value
		sort(vec.begin(), vec.end(),
			[](const pair & l, const pair & r) {
				if (l.second != r.second)
					return l.second > r.second;

				return l.first > r.first;
			});

		// print the vector
		cout << endl << left << setw(25) << "Site";
		cout << left << setw(15) << "Number of seats bought" << endl;
		for (auto const& pair : vec) {

			cout << left << setw(25) << pair.first;
			cout << left << setw(15) << pair.second << endl;
			n = n - 1;
			if (n == 0) {
				cout << endl;
				break;
			}
		}

		// printing map map1 
		/*map<string, int>::iterator itr;
		cout << "\nThe map map1 is : \n";
		cout << "\tKEY\tELEMENT\n";
		for (itr = map1.begin(); itr != map1.end(); ++itr)
			cout << '\t' << itr->first << '\t' << itr->second << '\n';*/


        cout << endl << "0 - BACK" << endl;
        do {
          testinput = checkinputchoice(input, 0, 0);
          if (testinput != 0 && testinput != 2)
            cerr << "Invalid option! Press 0 to go back." << endl;
        } while (testinput != 0 && testinput != 2);
	}
}
void Agency::showNMostVisistedPlaces(vector<string>& v1, bool &exit) {
	map <string, int> map1;
	int n = 0, testinput = 0;
	string input = "";
	system("cls");
	cout << "_____________________________________________________" << endl << endl;
	cout << "\t\t  Recommended Packs " << endl;
	cout << "_____________________________________________________" << endl << endl;

	for (unsigned int i = 0; i < packets.size(); i++)
	{
		for (unsigned int j = 0; j < packets.at(i).getSites().size(); j++)
		{
			if (map1.find(packets.at(i).getSites().at(j)) == map1.end()) {
				// not found
				map1.insert(pair<string, int>(packets.at(i).getSites().at(j), packets.at(i).getReservedSeats()));
			}
			else {
				// found
				int temp = 0;
				temp = map1[packets.at(i).getSites().at(j)];
				temp = temp + packets.at(i).getReservedSeats();
				map1[packets.at(i).getSites().at(j)] = temp;
			}
		}
	}

	cout << "Choose a number N between 1 and " << map1.size() << " (0 to exit) : ";
	do {
		testinput = checkinputchoice(input, 0, (int)map1.size());
		if (testinput != 0 && testinput != 2)
			cerr << "Invalid option! Please try again." << endl;
	} while (testinput != 0 && testinput != 2); if (testinput == 2) { input = "0"; }
	if (input == "0") { exit = true; }
	if (stoi(input) != 0)
	{
		n = stoi(input);
		//// Organizar por ordem decrescente
		typedef pair<string, int> pair;

		// create a empty vector of pairs
		vector<pair> vec;

		// copy key-value pairs from the map to the vector
		copy(map1.begin(), map1.end(), back_inserter<vector<pair>>(vec));

		// sort the vector by increasing order of its pair's second value
		// if second value are equal, order by the pair's first value
		sort(vec.begin(), vec.end(),
			[](const pair & l, const pair & r) {
				if (l.second != r.second)
					return l.second > r.second;

				return l.first > r.first;
			});

		// print the vector
		/*cout << endl << left << setw(25) << "Site";
		cout << left << setw(15) << "Number of seats bought" << endl;*/
		for (auto const& pair : vec) {

			/*cout << left << setw(25) << pair.first;
			cout << left << setw(15) << pair.second << endl;*/
			v1.push_back(pair.first);
			n = n - 1;
			if (n == 0) {
				cout << endl;
				break;
			}
		}

		// printing map map1 
		/*map<string, int>::iterator itr;
		cout << "\nThe map map1 is : \n";
		cout << "\tKEY\tELEMENT\n";
		for (itr = map1.begin(); itr != map1.end(); ++itr)
			cout << '\t' << itr->first << '\t' << itr->second << '\n';*/


	}
}
void Agency::specialOption() {
  /*Gerar uma listagem de todos os clientes na qual se indica, para cada cliente,
      um dos pacotes em que seja visitado um dos N locais mais visitados(ver ponto 9) que ele ainda não visitou.*/
  int test = 0;
  string input = "";
  vector<string> v1;
  vector<string> lugaresvisitadosdev1;
  vector<string> lugaresnaovisitadosdev1;
  bool exit = false;
  showNMostVisistedPlaces(v1, exit);
  if (!exit)
  {
    cout << v1.size() << " most visited sites: " << endl;
    for (auto const& pair : v1)
      cout << right << setw(25) << pair << endl;
    cout << endl;
    for (unsigned int i = 0; i < clients.size(); i++)
    {
      // ir client a client
      lugaresvisitadosdev1.clear();
      lugaresnaovisitadosdev1.clear();
      //cout << clients.at(i).getName() << " ";
      for (unsigned int j = 0; j < clients.at(i).getPacketList().size(); j++)
      {
        // ir a cada um dos pacotes do client
        for (unsigned int k = 0; k < clients.at(i).getPacketList().at(j).getSites().size(); k++)
        {
          //cout << "SITIO NUMERO " << k + 1 << endl;
          // ir a cada um dos sitios do pacote

          for (unsigned int l = 0; l < v1.size(); l++)
          {
            // comparar com os sitios mais visitados
            //cout << "comparando " << v1.at(l) << " com " << clients.at(i).getPacketList().at(j).getSites().at(k) << endl;
            if (v1.at(l) == clients.at(i).getPacketList().at(j).getSites().at(k))
            {
              //cout << "Visitado = true" << endl;
              lugaresvisitadosdev1.push_back(clients.at(i).getPacketList().at(j).getSites().at(k));
              break;
            }
          }
        }
      }
      cout << endl;
      if (lugaresvisitadosdev1.size() == 0)
        cout << "Client " << clients.at(i).getName() << " hasn't visited any sites from the list above ";
      else
      {
        if (lugaresvisitadosdev1.size() == 1)
          cout << "Client " << clients.at(i).getName() << " visited this sites from the list above: " << lugaresvisitadosdev1.at(0);
        else
        {
          cout << "Client " << clients.at(i).getName() << " visited this sites from the list above: ";
          for (unsigned int j = 0; j < lugaresvisitadosdev1.size(); j++) {
            if (j == lugaresvisitadosdev1.size() - 1)
              cout << lugaresvisitadosdev1.at(j);
            else
              cout << lugaresvisitadosdev1.at(j) << ", ";
          }

        }

      }
      cout << endl;
      //cout << "Lista de v1: ";
      //for (unsigned int j = 0; j < v1.size(); j++)
      //	cout << v1.at(j) << ", ";
      //cout << endl;

      lugaresnaovisitadosdev1.clear();
      bool adicionar = true;
      for (unsigned int j = 0; j < v1.size(); j++)
      {
        adicionar = true;
        for (unsigned int k = 0; k < lugaresvisitadosdev1.size(); k++)
        {
          //cout << "comparando " << v1.at(j) << " com " << lugaresvisitadosdev1.at(k) << endl;
          if (v1.at(j) == lugaresvisitadosdev1.at(k))
          {
            adicionar = false;
            break;
          }
          // Por cada um de v1, ver se esta em lugares visitados, se nao estiver adiciona, se estiver dá continue
        }
        //cout << "Com " << v1.at(j) << " o valor de adicionar = " << adicionar << endl;
        if (adicionar == true) {
          lugaresnaovisitadosdev1.push_back(v1.at(j));
        }
      }

      /*cout << "Lista de lugaresnaovisitadosdev1: ";
      for (unsigned int j = 0; j < lugaresnaovisitadosdev1.size(); j++) {
          cout << lugaresnaovisitadosdev1.at(j) << ", ";
      }
      cout << endl;*/

      bool encontrou = false;
      int packetid = 0;
      for (unsigned int j = 0; j < lugaresnaovisitadosdev1.size(); j++) {
        // Por cada lugar não visitado
        encontrou = false;
        packetid = 0;
        for (unsigned int k = 0; k < packets.size(); k++) {
          // Vai a cada pack
          for (unsigned int l = 0; l < packets.at(k).getSites().size(); l++) {
            // Em cada pack verifica se o destino está lá
            if (lugaresnaovisitadosdev1.at(j) == packets.at(k).getSites().at(l))
            {
              encontrou = true;
              packetid = packets.at(k).getId();
              break;
            }

          }
          if (encontrou)
            break;
        }
        if (encontrou)
        {
          cout << "For the Client: " << clients.at(i).getName() << " the recommended packet as the ID " << packetid << endl;
          break;
        }
        //else
        //{
        //	cout << "The Client: " << clients.at(i).getName() << " has no packets available" << endl;
        //}
        // por cada destino, procurar um pack, se encontrar um pack, dá cout desse pack e dá break no for,se não encontrar um pack, passa para o proximo destino
      }
      if (!encontrou)
        cout << "The Client: " << clients.at(i).getName() << " has no packets recommended" << endl;
    }
    cout << endl << "0 - BACK" << endl;
    do {
      test = checkinputchoice(input, 0, 0);
      if (test != 0 && test != 2)
        cerr << "Invalid option! Press 0 to go back." << endl;
    } while (test != 0 && test != 2);
  }
}
void Agency::buyPacket() {
  int testinput = 0, index = 0, identifier = 0, packindex = 0, familysize = 0; string input = ""; int test = 0;
  // Necessário actualizar dados do pacote, seats bought +1
  system("cls");
  cout << "_____________________________________________________\n" << endl;
  cout << "\t\t      BUY PACKS " << endl;
  cout << "_____________________________________________________" << endl << endl;
  cout << "INSTRUCTIONS" << endl;
  cout << "1 - Choose a Client from the shown list\n2 - Insert the Pack's Identifier number\n3 - Confirm" << endl;
  cout << "(If you do not know the pack's idenfier number you can go back and check)\n\n";
  cout << "\t1 - Continue\n\t2 - Exit\n";
  do {
    testinput = checkinputchoice(input, 1, 2);
    if (testinput != 0 && testinput != 2)
      cerr << "Invalid option! Please try again." << endl;
  } while (testinput != 0 && testinput != 2); if (testinput == 2) { input = "0"; }
  if (stoi(input) == 1)
  {
    // do stuff
    system("cls");
    cout << "--------------------- Clients List ---------------------\n";
    cout << "Enter 0 To Exit\n" << endl;
    for (unsigned int i = 0; i < clients.size(); i++)
    {
      cout << i + 1 << " - Client's Name: " << clients.at(i).getName() << endl;
      cout << "    Client's NIF: " << clients.at(i).getVATnumber() << endl << endl;
    }
    do {
      testinput = checkinputchoice(input, 0, (int)clients.size());
      if (testinput != 0 && testinput != 2)
        cerr << "Invalid option! Please try again." << endl;
    } while (testinput != 0 && testinput != 2); if (testinput == 2) { input = "0"; }

    if (stoi(input) != 0)
    {
      index = stoi(input) - 1;  // index of client
      familysize = clients.at(index).getFamilySize();
      cout << "Input the pack identifier: ";
      do {
        testinput = checkinputchoiceid(input, packets, clients.at(index).getPacketList(), familysize);
        if (testinput == 1)
          cerr << "Invalid option! Please try again." << endl;
        if (testinput == 3)
          cerr << "Packet is Unavailable" << endl;
        if (testinput == 5)
          cerr << "Packet Does not Exist" << endl;
        if (testinput == 6)
          cerr << "Client Already Bought that Pack" << endl;
        if (testinput == 7)
          cerr << "Packet does not have enough available seats" << endl;
      } while (testinput != 4 && testinput != 2); if (testinput == 2) { input = "0"; }
      if (stoi(input) != 0)
      {
        identifier = stoi(input);
        system("cls");
        cout << "_____________________________________________________\n" << endl;
        cout << "\t\t      BUY PACKS " << endl;
        cout << "_____________________________________________________" << endl << endl;
        cout << clients[index].getName() << " will buy this pack:\n\n";
        for (unsigned int i = 0; i < packets.size(); i++)
        {
          if (identifier == packets.at(i).getId()) {
            packets.at(i).showPacket();
            packindex = i;
            break;
          }
        }
        cout << "\n1 - Confirm\n2 - Discard and EXIT\n";
        do {
          testinput = checkinputchoice(input, 1, 2);
        } while (testinput != 0); if (testinput == 2) { input = "2"; }
        if (stoi(input) == 1) {
          /*3 coisas
              acrescentar ao cliente
              +1 nos packs comprados
              verificar se ficou indisponivel e caso sim mudar identifier*/
          for (unsigned int i = 0; i < packets.size(); i++)
          {
            if (packets.at(i).getId() == identifier) {
              identifier = i;  // identifier = index do pack em packs
              break;
            }
          }
          clients.at(index).setTotalPurchased(clients.at(index).getTotalPurchased() + clients.at(index).getFamilySize() * packets.at(identifier).getPricePerPerson());

          vector<Packet> packetstemp = clients.at(index).getPacketList();
          packetstemp.push_back(packets.at(identifier));
          clients.at(index).setPacketList(packetstemp); // adiciona packet ao comprados por client

          packets.at(identifier).setReservedSeats(packets.at(identifier).getReservedSeats() + 1);  // +1 nos packs comprados
          if (packets.at(identifier).getReservedSeats() == packets.at(identifier).getMaxPeople())
            packets.at(identifier).setAvailable(false);

          system("cls");
          cout << "_____________________________________________________\n" << endl;
          cout << "\t\t      BUY PACKS " << endl;
          cout << "_____________________________________________________" << endl << endl;
          cout << "PACK BOUGHT SUCCESSFULLY\n";
          
          cout << endl << "0 - BACK" << endl;
          do {
            test = checkinputchoice(input, 0, 0);
            if (test != 0 && test != 2)
              cerr << "Invalid option! Press 0 to go back." << endl;
          } while (test != 0 && test != 2);
        }
      }
    }
  }
}
/*
ostream& operator<<(ostream& out, const Agency & agency) {

  // A IMPLEMENTATION REQUIRED
}*/