#include <iostream>
#include <string>
#include <vector>
#include "Agency.h"
#include "Menus.h"

int main() {
  string filename;
  Agency agency(filename);
  mainMenu(agency); // initial menu inicial with the major options of the application
  
  return 0;
}
