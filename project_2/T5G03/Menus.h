#pragma once

#include <string>

class Agency;

using namespace std;

void mainMenu(Agency& agency);

void clientsMenu(Agency& agency);
void packetsMenu(Agency& agency);
void statisticsMenu(Agency& agency);

void removeClientMenu(Agency& agency);
void changeClientMenu(Agency& agency);
void changeClientByVATMenu(Agency& agency);
void changeClientByClientListMenu(Agency& agency, bool useIndex = false, unsigned index = 0);
void changeClientAddressMenu(Agency & agency, unsigned index);

void removePacketMenu(Agency& agency);
void changePacketMenu(Agency& agency);
void changePacketByIdMenu(Agency& agency);
void changePacketByPacketListMenu(Agency& agency, bool useIndex = false, unsigned index = 0);
void changePacketDatesMenu(Agency& agency, unsigned index);
void showPacketsMenu(Agency& agency);
void showSoldPacketsMenu(Agency& agency);

void choosePacketData(Agency& agency);