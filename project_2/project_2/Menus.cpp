#include "Menus.h"
#include "Agency.h"
#include <iostream>
#include <regex>

//main menu
void mainMenu(Agency& agency) {
	int testinput = 0;
	string input = "";
	do
	{
		system("cls");
		cout << "_____________________________________________________" << endl << endl;
		cout << "\t\t AGENCY " << agency.getName() << endl;
		cout << "_____________________________________________________" << endl << endl;

		cout << "Choose a option by typing a number and pressing Enter." << endl << endl;
		//show the main menu
		cout << "1 - Clients" << endl;
		cout << "2 - Packets" << endl;
		cout << "3 - Statistics" << endl;
		cout << "0 - EXIT" << endl;
		//checking if option is valid
		do {
			testinput = checkinputchoice(input, 0, 3);
			if (testinput != 0 && testinput != 2)
				cerr << "Invalid option! Please try again." << endl;
		} while (testinput != 0 && testinput != 2); if (testinput == 2) { input = "0"; }
		if (testinput == 2)
			input = "0";
		switch (stoi(input)) {
		case 1:
			clientsMenu(agency);
			break;
		case 2:
			packetsMenu(agency);
			break;
		case 3:
			statisticsMenu(agency);
			break;
		case 0:
			//AgencyToFile(agencychoice);
			agency.saveClients();
			agency.savePackets();
			break;
		}
	} while (stoi(input) != 0);
}

//submenus - client, packets, statistics
void clientsMenu(Agency & agency) {
	int testinput = 0;
	string input;
	do
	{
		system("cls");
		cout << "_____________________________________________________" << endl << endl;
		cout << "\t\t   Client Options " << endl;
		cout << "_____________________________________________________" << endl << endl;
        
		//show client's menu
		cout << "1 - Add Client" << endl;
		cout << "2 - Change Client" << endl;
		cout << "3 - Remove Client" << endl;
		cout << "4 - View Client Info (by VAT)" << endl;
		cout << "5 - View All Clients Info" << endl;
		cout << "6 - Buy Pack" << endl;
		cout << "0 - BACK (Main Menu)" << endl;

		do {
			testinput = checkinputchoice(input, 0, 6);
			if (testinput != 0 && testinput != 2)
				cerr << "Invalid option! Please try again." << endl;
		} while (testinput != 0 && testinput != 2); if (testinput == 2) { input = "0"; }

		switch (stoi(input)) {
		case 1:
			agency.addClient();
			break;
		case 2:
			changeClientMenu(agency);
			break;
		case 3:
			removeClientMenu(agency);
			break;
		case 4:
			agency.showClientInfo();
			break;
		case 5:
			agency.showAllClientsInfo();
			break;
		case 6:
			agency.buyPacket();
			// Por Fazer
			break;
		case 0:
			break;
		}
	} while (stoi(input) != 0);
}
void packetsMenu(Agency& agency) {
  int testinput = 0;
  string input;

  do
  {
    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t\t   Packets Options " << endl;
    cout << "_____________________________________________________" << endl << endl;
 
    //show packs's menu
    cout << "1 - Add Packet" << endl;
    cout << "2 - Change Packet" << endl;
    cout << "3 - Remove Packet" << endl;
    cout << "4 - Show Packets by" << endl;
    cout << "5 - Sold Packets" << endl;
    cout << "6 - Buy Packet" << endl;
    cout << "0 - BACK (Main Menu)" << endl;

    do {
      testinput = checkinputchoice(input, 0, 6);
      if (testinput != 0 && testinput != 2)
        cerr << "Invalid option! Please try again." << endl;
    } while (testinput != 0 && testinput != 2); if (testinput == 2) { input = "0"; }

    switch (stoi(input)) {
    case 1:
      agency.addPacket();
      break;
    case 2:
      changePacketMenu(agency);
      break;
    case 3:
      removePacketMenu(agency);
      break;
    case 4:
      showPacketsMenu(agency);
      break;
    case 5:
      showSoldPacketsMenu(agency);
      break;
    case 6:
      agency.buyPacket();
      break;
    case 0:
      break;
    }
  } while (stoi(input) != 0);
}
void statisticsMenu(Agency & agency) {
	int testinput = 0;
	string input = "";
	do
	{
		system("cls");
		cout << "_____________________________________________________" << endl << endl;
		cout << "\t\t   Statistics " << endl;
		cout << "_____________________________________________________" << endl << endl;
        
		//show statistics's menu
		cout << "1 - Sold Packets Data" << endl;
		cout << "2 - N Most Visited Places" << endl;
		cout << "3 - Special Option" << endl;
		cout << "0 - BACK (Main Menu)" << endl;

		do {
			testinput = checkinputchoice(input, 0, 3);
			if (testinput != 0 && testinput != 2)
				cerr << "Invalid option! Please try again." << endl;
		} while (testinput != 0 && testinput != 2); if (testinput == 2) { input = "0"; }

		switch (stoi(input)) {
		case 1:
			choosePacketData(agency);
			break;
		case 2:
			agency.showNMostVisistedPlaces();
			break;
		case 3:
			agency.specialOption();
			break;
		case 0:
			break;
		}
	} while (stoi(input) != 0);
}


//Client management menus
//remove client
void removeClientMenu(Agency& agency) {
	int testinput = 0;
	string input = "";
	do
	{
		system("cls");
		cout << "_____________________________________________________" << endl << endl;
		cout << "\t\t   Remove Client " << endl;
		cout << "_____________________________________________________" << endl << endl;

		cout << "1 - Remove Client by VAT number" << endl;
		cout << "2 - Choose Client to remove from Client's List" << endl;
		cout << "0 - BACK (Client Menu)" << endl;

		do {
			testinput = checkinputchoice(input, 0, 2);
			if (testinput != 0 && testinput != 2)
				cerr << "Invalid option! Please try again." << endl;
		} while (testinput != 0 && testinput != 2); if (testinput == 2) { input = "0"; }

		switch (stoi(input)) {
		case 1:
			agency.removeClientByVAT();
			break;
		case 2:
			agency.removeClientByClientList();
			break;
		case 0:
			break;
		}
	} while (stoi(input) != 0);
}
//change client
void changeClientMenu(Agency & agency) {
	int testinput = 0;
	string input;
	do
	{
		system("cls");
		cout << "_____________________________________________________" << endl << endl;
		cout << "\t\t   Change Client " << endl;
		cout << "_____________________________________________________" << endl << endl;

		cout << "1 - Change Client by VAT number" << endl;
		cout << "2 - Change Client from Client's List" << endl;
		cout << "0 - BACK (Client Menu)" << endl;

		do {
			testinput = checkinputchoice(input, 0, 2);
			if (testinput != 0 && testinput != 2)
				cerr << "Invalid option! Please try again." << endl;
		} while (testinput != 0 && testinput != 2); if (testinput == 2) { input = "0"; }

		switch (stoi(input)) {
		case 1:
			changeClientByVATMenu(agency);
			break;
		case 2:
			changeClientByClientListMenu(agency);
			break;
		case 0:
			break;
		}
	} while (stoi(input) != 0);
}
void changeClientByVATMenu(Agency& agency) {
  int test = 0, index = 0;
  string input = "";

  do
  {
    system("cls");
    if (agency.getClients().size() != 0) {

      cout << "_____________________________________________________" << endl << endl;
      cout << "\t\t   Change Client " << endl;
      cout << "_____________________________________________________" << endl << endl;
      cout << "(Press Ctrl+z to go back)" << endl << endl;
      do {
        cout << "Client's VAT: ";
        test = agency.checkVATInput(input);
        if (test != 2)
          cout << "No client was found with that VAT number. Please try again." << endl;
      } while (test != 2 && test != 5);
      if (test == 5)
        break;
      test = 0;

      for (unsigned int i = 0; i < agency.getClients().size(); i++) {
        if (agency.getClients().at(i).getVATnumber() == stoi(input)) {
          index = i;
          break;
        }
      }

      system("cls");
      cout << "_____________________________________________________" << endl << endl;
      cout << "\t\t   Change Client " << endl;
      cout << "_____________________________________________________" << endl << endl;
      cout << "-----Data of Client to Change-----" << endl << endl;
      agency.getClients().at(index).showClient();

      cout << endl << "Do you want to change data in this client?" << endl;
      cout << "1 - Yes" << endl;
      cout << "2 - No" << endl;

      do {
        test = checkinputchoice(input, 1, 2);
        if (test != 0)
          cerr << "Invalid option! Please try again." << endl;
      } while (test != 0);

      if (stoi(input) == 1)
      {
        do
        {
          system("cls");
          cout << "_____________________________________________________" << endl << endl;
          cout << "\t\t   Change Client " << endl;
          cout << "_____________________________________________________" << endl << endl;
          cout << "-----Changing Client " << agency.getClients().at(index).getName() << " - VAT " << agency.getClients().at(index).getVATnumber() << "-----" << endl << endl;
          cout << "1 - Change name" << endl;
          cout << "2 - Change VAT" << endl;
          cout << "3 - Change Family size" << endl;
          cout << "4 - Change Address" << endl;
          cout << "5 - Change Packets" << endl;
          cout << "0 - BACK" << endl;
          do {
            test = checkinputchoice(input, 0, 5);
            if (test == 1)
              cerr << "Invalid option! Please try again." << endl;
          } while (test != 0 && test != 2);
          if (test == 2)
            input = "0";

          system("cls");
          cout << "_____________________________________________________" << endl << endl;
          cout << "\t\t   Change Client " << endl;
          cout << "_____________________________________________________" << endl << endl;
          cout << "-----Changing Client " << agency.getClients().at(index).getName() << " - VAT " << agency.getClients().at(index).getVATnumber() << "-----" << endl << endl;

          switch (stoi(input))
          {
          case 1:
            agency.changeClientName(index);
            break;
          case 2:
            agency.changeClientVAT(index);
            break;
          case 3:
            agency.changeClientFamilySize(index);
            break;
          case 4:
            changeClientAddressMenu(agency, index);
            break;
          case 5:
            agency.changeClientPackets(index);
            break;
          case 0:
            break;
          default:
            break;
          }
          if (stoi(input) != 0)
          {
            cout << "1 - Modify another Detail" << endl;
            cout << "2 - Change another Client" << endl;
            cout << "0 - Exit (Change Client Menu)" << endl;
            do {
              test = checkinputchoice(input, 0, 2);
              if (test != 0)
                cerr << "Invalid option! Please try again." << endl;
            } while (test != 0 && test!=2);
            if (test == 2)
              input = "0";
          }
        } while (stoi(input) == 1);
      }
      else
      {
        cout << "1 - Change another Client" << endl;
        cout << "0 - Exit (Change Client Menu)" << endl;
        do {
          test = checkinputchoice(input, 0, 1);
          if (test != 0)
            cerr << "Invalid option! Please try again." << endl;
        } while (test != 0);
        if (input == "1")
          input = "2";
      }
    }
    else {
      cerr << "No clients to change!" << endl;
      sleep_for(nanoseconds(10));
      sleep_until(system_clock::now() + seconds(1));
      exit(0);
    }
  } while (stoi(input) == 2);
}
void changeClientByClientListMenu(Agency & agency, bool useIndex, unsigned index) {
  int test = 0;
  string input = "";

  do
  {
    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t\t   Change Client " << endl;
    cout << "_____________________________________________________" << endl << endl;
    cout << "(Press Ctrl+z to go back)" << endl << endl;
    if (agency.getClients().size() != 0) {

      if (!useIndex) {
        for (unsigned int i = 0; i < agency.getClients().size(); i++)
        {
          cout << i + 1 << " - Client's Name: " << agency.getClients().at(i).getName() << endl;
          cout << "Client's VAT: " << agency.getClients().at(i).getVATnumber() << endl << endl;
        }
        do {
          cout << "Choose a number: ";
          test = checkinputchoice(input, 1, (int)agency.getClients().size());
          if (test != 0)
            cerr << "Invalid number! Please try again." << endl;
        } while (test != 0 && test!=2);
        if (test == 2)
          break;
        index = stoi(input) - 1;
      }

      system("cls");
      cout << "_____________________________________________________" << endl << endl;
      cout << "\t\t   Change Client " << endl;
      cout << "_____________________________________________________" << endl << endl;
      cout << "-----Data of Client to Change-----" << endl << endl;
      agency.getClients().at(index).showClient();

      cout << endl << "Do you want to change data in this client?" << endl;
      cout << "1 - Yes" << endl;
      cout << "2 - No" << endl;

      do {
        test = checkinputchoice(input, 1, 2);
        if (test != 0)
          cerr << "Invalid option! Please try again." << endl;
      } while (test != 0);

      if (stoi(input) == 1)
      {
        do
        {
          system("cls");
          cout << "_____________________________________________________" << endl << endl;
          cout << "\t\t   Change Client " << endl;
          cout << "_____________________________________________________" << endl << endl;
          cout << "-----Changing Client " << agency.getClients().at(index).getName() << " - VAT " << agency.getClients().at(index).getVATnumber() << "-----" << endl << endl;
          cout << "1 - Change name" << endl;
          cout << "2 - Change VAT" << endl;
          cout << "3 - Change Family size" << endl;
          cout << "4 - Change Address" << endl;
          cout << "5 - Change Packets" << endl;
          cout << "0 - BACK" << endl;
          do {
            test = checkinputchoice(input, 0, 5);
            if (test == 1)
              cerr << "Invalid option! Please try again." << endl;
          } while (test != 0 && test != 2);
          if (test == 2)
            break;

          system("cls");
          cout << "_____________________________________________________" << endl << endl;
          cout << "\t\t   Change Client " << endl;
          cout << "_____________________________________________________" << endl << endl;
          cout << "-----Changing Client " << agency.getClients().at(index).getName() << " - VAT " << agency.getClients().at(index).getVATnumber() << "-----" << endl << endl;

          switch (stoi(input))
          {
          case 1:
            agency.changeClientName(index);
            break;
          case 2:
            agency.changeClientVAT(index);
            break;
          case 3:
            agency.changeClientFamilySize(index);
            break;
          case 4:
            changeClientAddressMenu(agency, index);
            break;
          case 5:
            agency.changeClientPackets(index);
            break;
          case 0:
            break;
          default:
            break;
          }

          if (stoi(input) != 0)
          {
            cout << "1 - Modify another Detail" << endl;
            cout << "0 - Exit (Choose another client)" << endl;
            do {
              test = checkinputchoice(input, 0, 1);
              if (test ==1)
                cerr << "Invalid option! Please try again." << endl;
            } while (test != 0 && test!=2);
            if (test == 2)
              input = "0";
          }

        } while (stoi(input) == 1);
      }

      cout << endl << "Change another client?" << endl;
      cout << "1 - Yes" << endl;
      cout << "0 - No (Change Client Menu)" << endl;
      do {
        test = checkinputchoice(input, 0, 1);
        if (test == 1)
          cerr << "Invalid option! Please try again." << endl;
      } while (test != 0 && test!=2);
      if(test==2)
        input = "0";
    }
    else {
      cerr << "No clients to change!" << endl;
      sleep_for(nanoseconds(10));
      sleep_until(system_clock::now() + seconds(1));
      exit(0);
    }
  } while (stoi(input) != 0);
}
void changeClientAddressMenu(Agency & agency, unsigned index) {
  string input = "";
  int test = 0;

  do
  {
    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t\t   Change Client's Address " << endl;
    cout << "_____________________________________________________" << endl << endl;
    cout << "-----Changing Client " << agency.getClients().at(index).getName() << " - VAT " << agency.getClients().at(index).getVATnumber() << " Address-----" << endl << endl;
    agency.getClients().at(index).getAddress().showAddress();

    cout << endl << "Do you want to change the address in this client?" << endl;
    cout << "1 - Yes" << endl;
    cout << "2 - No" << endl;

    do {
      test = checkinputchoice(input, 1, 2);
      if (test != 0)
        cerr << "Invalid option! Please try again." << endl;
    } while (test != 0);

    if (stoi(input) == 1)
    {
      do
      {
        system("cls");
        cout << "_____________________________________________________" << endl << endl;
        cout << "\t\t   Change Client's Address " << endl;
        cout << "_____________________________________________________" << endl << endl;
        cout << "-----Changing Client " << agency.getClients().at(index).getName() << " - VAT " << agency.getClients().at(index).getVATnumber() << " Address-----" << endl << endl;
        cout << "1 - Change complete Address" << endl;
        cout << "2 - Change Street Name" << endl;
        cout << "3 - Change Door Number" << endl;
        cout << "4 - Change Floor" << endl;
        cout << "5 - Change Postal Code" << endl;
        cout << "6 - Change State/Location" << endl;
        cout << "0 - BACK" << endl;
        do {
          test = checkinputchoice(input, 0, 6);
          if (test == 1 )
            cerr << "Invalid option! Please try again." << endl;
        } while (test != 0 && test !=2);
        if (test == 2)
          input = "0";

        system("cls");
        cout << "_____________________________________________________" << endl << endl;
        cout << "\t\t   Change Client's " << endl;
        cout << "_____________________________________________________" << endl << endl;
        cout << "-----Changing Client " << agency.getClients().at(index).getName() << " - VAT " << agency.getClients().at(index).getVATnumber() << " Address-----" << endl << endl;

        switch (stoi(input))
        {
        case 1:
          agency.changeClientAddress(index);
          break;
        case 2:
          agency.changeClientStreetName(index);
          break;
        case 3:
          agency.changeClientDoorNumber(index);
          break;
        case 4:
          agency.changeClientFloor(index);
          break;
        case 5:
          agency.changeClientPostalCode(index);
          break;
        case 6:
          agency.changeClientLocation(index);
          break;
        case 0:
          break;
        }

        cout << "1 - Modify another Detail in Address" << endl;
        cout << "0 - Exit" << endl;
        do {
          test = checkinputchoice(input, 0, 1);
          if (test == 1)
            cerr << "Invalid option! Please try again." << endl;
        } while (test != 0 && test!=2);
        if (test == 2)
          input = "0";
      } while (stoi(input) == 1);

    }
    else
      input = "0";
  } while (stoi(input) != 0);
}
//Packets managment menus
//remove packet
void removePacketMenu(Agency & agency) {
	int testinput = 0;
	string input = "";
	do
	{
		system("cls");
		cout << "_____________________________________________________" << endl << endl;
		cout << "\t\t   Remove Packet " << endl;
		cout << "_____________________________________________________" << endl << endl;

		cout << "1 - Remove Packet by Id" << endl;
		cout << "2 - Choose Packet to remove from Packet's List" << endl;
		cout << "0 - BACK (Packet Menu)" << endl;

		do {
			testinput = checkinputchoice(input, 0, 2);
			if (testinput != 0 && testinput != 2)
				cerr << "Invalid option! Please try again." << endl;
		} while (testinput != 0 && testinput != 2); if (testinput == 2) { input = "0"; }

		switch (stoi(input)) {
		case 1:
			agency.removePacketById();
			break;
		case 2:
			agency.removePacketByPacketList();
			break;
		case 0:
			break;
		}
	} while (stoi(input) != 0);
};
//show packets
void showPacketsMenu(Agency & agency) {
	int testinput = 0;
	string input = "";
	do
	{
		system("cls");
		cout << "_____________________________________________________" << endl << endl;
		cout << "\t\t   Show Packets " << endl;
		cout << "_____________________________________________________" << endl << endl;

		cout << "1 - All Packets" << endl;
		cout << "2 - By ID" << endl;
		cout << "3 - All with same Destination" << endl;
		cout << "4 - All between two dates" << endl;
		cout << "5 - All with same destination and between two dates" << endl;
		cout << "0 - BACK (Packets Menu)" << endl;

		do {
			testinput = checkinputchoice(input, 0, 5);
			if (testinput != 0 && testinput != 2)
				cerr << "Invalid option! Please try again." << endl;
		} while (testinput != 0 && testinput != 2); if (testinput == 2) { input = "0"; }

		switch (stoi(input)) {
		case 1:
			agency.showAllPacketsInfo();
			break;
		case 2:
			agency.showPacketInfo();
			break;
		case 3:
			agency.showPacketsByDestination();
			break;
		case 4:
			agency.showPacketsByDate();
			break;
		case 5:
			agency.showPacketsByDateAndDestination();
			break;
		case 0:
			break;
		}
	} while (stoi(input) != 0);
}
void showSoldPacketsMenu(Agency& agency) {
  int testinput = 0;
  string input;
  do
  {
    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t\t   Sold Packets " << endl;
    cout << "_____________________________________________________" << endl << endl;

    cout << "1 - To Specific Client" << endl;
    cout << "2 - To All Clients" << endl;
    cout << "0 - BACK (Show Packet Menu)" << endl;

    do {
      testinput = checkinputchoice(input, 0, 2);
      if (testinput != 0 && testinput != 2)
        cerr << "Invalid option! Please try again." << endl;
    } while (testinput != 0 && testinput != 2); if (testinput == 2) { input = "0"; }

    switch (stoi(input)) {
    case 1:
      agency.packetsSoldToSpecificClient();
      break;
    case 2:
      agency.packetsSoldToAllClients();
      break;
    case 0:
      break;
    }
  } while (stoi(input) != 0);
};

//change packet
void changePacketMenu(Agency& agency) {
  int testinput = 0;
  string input;
  do
  {
    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t\t   Change Packet " << endl;
    cout << "_____________________________________________________" << endl << endl;

    cout << "1 - Change Packet by Id" << endl;
    cout << "2 - Change Packet from Packet's List" << endl;
    cout << "0 - BACK (Packet Menu)" << endl;

    do {
      testinput = checkinputchoice(input, 0, 2);
      if (testinput != 0 && testinput != 2)
        cerr << "Invalid option! Please try again." << endl;
    } while (testinput != 0 && testinput != 2); if (testinput == 2) { input = "0"; }

    switch (stoi(input)) {
    case 1:
      changePacketByIdMenu(agency);
      break;
    case 2:
      changePacketByPacketListMenu(agency);
      break;
    case 0:
      break;
    }
  } while (stoi(input) != 0);
}
void changePacketByIdMenu(Agency& agency) {
  int test = 0, index = 0;
  string input = "";

  do
  {
    system("cls");
    if (agency.getClients().size() != 0) {

      cout << "_____________________________________________________" << endl << endl;
      cout << "\t\t   Change Packet " << endl;
      cout << "_____________________________________________________" << endl << endl;
      
      do {
        cout << "Packet's Id: ";
        test = agency.checkIdInput(input);
        if (test == 2 || test == 0)
          cout << "No packet was found with that Id. Please try again." << endl;
      } while (test != 3 && test != 1 && test!=5);
      if (test == 5)
        break;
      else
        test = 0;

      for (unsigned int i = 0; i < agency.getPackets().size(); i++) {
        if (agency.getPackets().at(i).getId() == stoi(input)) {
          index = i;
          break;
        }
      }

      system("cls");
      cout << "_____________________________________________________" << endl << endl;
      cout << "\t\t   Change Packet " << endl;
      cout << "_____________________________________________________" << endl << endl;
      cout << "-----Data of Packet to Change-----" << endl << endl;
      agency.getPackets().at(index).showPacket();

      cout << endl << "Do you want to change data in this packet?" << endl;
      cout << "1 - Yes" << endl;
      cout << "2 - No" << endl;

      do {
        test = checkinputchoice(input, 1, 2);
        if (test != 0)
          cerr << "Invalid option! Please try again." << endl;
      } while (test != 0);

      if (stoi(input) == 1)
      {
        do
        {
          system("cls");
          cout << "_____________________________________________________" << endl << endl;
          cout << "\t\t   Change Packet " << endl;
          cout << "_____________________________________________________" << endl << endl;
          cout << "-----Changing Packet " << agency.getPackets().at(index).getId() << "-----" << endl << endl;
          cout << "1 - Change Id" << endl;
          cout << "2 - Change Availability" << endl;
          cout << "3 - Change Destination/Sites" << endl;
          cout << "4 - Change Begin/End Dates" << endl;
          cout << "5 - Change Price per Person" << endl;
          cout << "6 - Change Maximum People" << endl;
          cout << "7 - Change Reserved Seats" << endl;
          cout << "0 - BACK (Packet's Menu)" << endl;
          do {
            test = checkinputchoice(input, 0, 7);
            if (test != 0)
              cerr << "Invalid option! Please try again." << endl;
          } while (test != 0);

          system("cls");
          cout << "_____________________________________________________" << endl << endl;
          cout << "\t\t   Change Packet " << endl;
          cout << "_____________________________________________________" << endl << endl;
          cout << "-----Changing Packet " << agency.getPackets().at(index).getId() << "-----" << endl << endl;

          switch (stoi(input))
          {
          case 1:
            agency.changePacketId(index);
            break;
          case 2:
            agency.changePacketAvailability(index);
            break;
          case 3:
            agency.changePacketSites(index);
            break;
          case 4:
            changePacketDatesMenu(agency, index);
            break;
          case 5:
            agency.changePacketPrice(index);
            break;
          case 6:
            agency.changePacketMaxPeople(index);
            break;
          case 7:
            agency.changePacketReservedSeats(index);
            break;
          case 0:
            break;
          default:
            break;
          }
          if (stoi(input) != 0)
          {
            cout << "1 - Modify another Detail" << endl;
            cout << "2 - Change another Packet" << endl;
            cout << "0 - Exit (Change Packet Menu)" << endl;
            do {
              test = checkinputchoice(input, 0, 2);
              if (test != 0)
                cerr << "Invalid option! Please try again." << endl;
            } while (test != 0 && test!=2);
            if (test == 2)
              input = "0";
          }
        } while (stoi(input) == 1);
      }
      else
      {
        cout << endl << "Data NOT Modified" << endl;
        cout << "1 - Change another Packet" << endl;
        cout << "0 - Exit (Change Client Packet)" << endl;
        do {
          test = checkinputchoice(input, 0, 1);
          if (test != 0)
            cerr << "Invalid option! Please try again." << endl;
        } while (test != 0);
        if (input == "2")
          input = "0";
        if (input == "1")
          input = "2";
      }
    }
    else {
      cerr << "No clients to change!" << endl;
      sleep_for(nanoseconds(10));
      sleep_until(system_clock::now() + seconds(1));
      exit(0);
    }
  } while (stoi(input) == 2);
}
void changePacketByPacketListMenu(Agency & agency, bool useIndex, unsigned index) {
  int test = 0;
  string input = "";

  do
  {
    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t\t   Change Packet " << endl;
    cout << "_____________________________________________________" << endl << endl;

    if (agency.getPackets().size() != 0) {

      if (!useIndex) {
        for (unsigned i = 0; i < agency.getPackets().size(); i++)
        {
          cout << i + 1 << " - Packet's Id: " << agency.getPackets().at(i).getId() << endl;
          cout << "Packet's Sites: ";
          agency.getPackets().at(i).showSites();
          cout << endl;
        }
        do {
          cout << "Choose a number: ";
          test = checkinputchoice(input, 1, (int)agency.getPackets().size());
          if (test != 0)
            cerr << "Invalid number! Please try again." << endl;
        } while (test != 0 && test!=2);
        if (test == 2)
          break;
        index = stoi(input) - 1;
      }

      system("cls");
      cout << "_____________________________________________________" << endl << endl;
      cout << "\t\t   Change Packet " << endl;
      cout << "_____________________________________________________" << endl << endl;
      cout << "-----Data of Packet to Change-----" << endl << endl;
      agency.getPackets().at(index).showPacket();

      cout << endl << "Do you want to change data in this packet?" << endl;
      cout << "1 - Yes" << endl;
      cout << "2 - No" << endl;

      do {
        test = checkinputchoice(input, 1, 2);
        if (test != 0)
          cerr << "Invalid option! Please try again." << endl;
      } while (test != 0);

      if (stoi(input) == 1)
      {
        do
        {
          system("cls");
          cout << "_____________________________________________________" << endl << endl;
          cout << "\t\t   Change Packet " << endl;
          cout << "_____________________________________________________" << endl << endl;
          cout << "-----Changing Packet " << agency.getPackets().at(index).getId() << "-----" << endl << endl;
          cout << "1 - Change Id" << endl;
          cout << "2 - Change Availability" << endl;
          cout << "3 - Change Destination/Sites" << endl;
          cout << "4 - Change Begin/End Dates" << endl;
          cout << "5 - Change Price per Person" << endl;
          cout << "6 - Change Maximum People" << endl;
          cout << "7 - Change Reserved Seats" << endl;
          cout << "0 - BACK (Packet's Menu)" << endl;
          do {
            test = checkinputchoice(input, 0, 7);
            if (test != 0)
              cerr << "Invalid option! Please try again." << endl;
          } while (test != 0);

          system("cls");
          cout << "_____________________________________________________" << endl << endl;
          cout << "\t\t   Change Packet " << endl;
          cout << "_____________________________________________________" << endl << endl;
          cout << "-----Changing Packet " << agency.getPackets().at(index).getId() << "-----" << endl << endl;

          switch (stoi(input))
          {
          case 1:
            agency.changePacketId(index);
            break;
          case 2:
            agency.changePacketAvailability(index);
            break;
          case 3:
            agency.changePacketSites(index);
            break;
          case 4:
            changePacketDatesMenu(agency, index);
            break;
          case 5:
            agency.changePacketPrice(index);
            break;
          case 6:
            agency.changePacketMaxPeople(index);
            break;
          case 7:
            agency.changePacketReservedSeats(index);
            break;
          case 0:
            break;
          default:
            break;
          }
          if (stoi(input) != 0)
          {
            cout << "1 - Modify another Detail" << endl;
            cout << "2 - Change another Packet" << endl;
            cout << "0 - Exit (Change Packet Menu)" << endl;
            do {
              test = checkinputchoice(input, 0, 2);
              if (test != 0)
                cerr << "Invalid option! Please try again." << endl;
            } while (test != 0 && test!=2);
            if (test == 2)
              input = "0";
          }
        } while (stoi(input) == 1);
      }
      else
      {
        cout << endl << "Data NOT Modified" << endl;
        cout << "1 - Change another Packet" << endl;
        cout << "0 - Exit (Change Client Packet)" << endl;
        do {
          test = checkinputchoice(input, 0, 1);
          if (test != 0)
            cerr << "Invalid option! Please try again." << endl;
        } while (test != 0 && test!=2);
        if (test == 2)
          input = "0";
        else if (input == "1")
          input = "2";
      }
    }
    else {
      cerr << "No packets to change!" << endl;
      sleep_for(nanoseconds(10));
      sleep_until(system_clock::now() + seconds(1));
      exit(0);
    }
  } while (stoi(input) != 0);
}
void changePacketDatesMenu(Agency & agency, unsigned index) {
  int testinput = 0;
  string input;
  do
  {
    system("cls");
    cout << "_____________________________________________________" << endl << endl;
    cout << "\t\t   Change Packet's Dates " << endl;
    cout << "_____________________________________________________" << endl << endl;

    cout << "1 - Change Packet Begin Date" << endl;
    cout << "2 - Change Packet End Date" << endl;
    cout << "3 - Change Packet Begin and End Date" << endl;
    cout << "0 - BACK (Change Packet Menu)" << endl;

    do {
      testinput = checkinputchoice(input, 0, 3);
      if (testinput != 0 && testinput != 2)
        cerr << "Invalid option! Please try again." << endl;
    } while (testinput != 0 && testinput != 2); if (testinput == 2) { input = "0"; }

    switch (stoi(input)) {
    case 1:
      agency.changePacketBeginDate(index);
      break;
    case 2:
      agency.changePacketEndDate(index);
      break;
    case 3:
      agency.changePacketDates(index);
      break;
    case 0:
      break;
    }
    break;
  } while (stoi(input) != 0);
};

//Statistics
void choosePacketData(Agency & agency) {
	string input = ""; int testinput = 0;

	do
	{
		system("cls");
		cout << "_____________________________________________________" << endl << endl;
		cout << "\t\t   Packet Data " << endl;
		cout << "_____________________________________________________" << endl << endl;

		cout << "1 - According to Clients file" << endl;
		cout << "2 - According to Packs file" << endl;
		cout << "0 - BACK (Main Menu)" << endl;

		do {
			testinput = checkinputchoice(input, 0, 2);
			if (testinput != 0 && testinput != 2)
				cerr << "Invalid option! Please try again." << endl;
		} while (testinput != 0 && testinput != 2); if (testinput == 2) { input = "0"; }

		switch (stoi(input))
		{
		case 1:
			agency.showSoldPacketsDataByClients();
			break;
		case 2:
			agency.showSoldPacketsDataByPacks();
			break;
		case 0:
			break;
		default:
			break;
		}
	} while (stoi(input) != 0);

}
