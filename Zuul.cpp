#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include "Exit.h"
#include "Item.h"
#include "Room.h"


using namespace std;

bool isValidInput(char* input);

int main() {

  vector<Item> inventory;  
  vector<Room> rooms;

  //define and setup all the rooms
  Room* r1 = new Room("Room 1");
  Room* r2 = new Room("Room 2");

  r1 -> addLinkedRoom(r2, NORTH);
  r2 -> addLinkedRoom(r1, SOUTH);

  cout << (((r1 -> getLinkedRooms()).at(0).at(NORTH)) -> getDescription()) << endl;
  
  char* input = new char[80];
  strcpy(input, "GET north");
  bool n = isValidInput(input);


  return 0;
}

bool isValidInput(char* input) {
  //if there is no space its invalid by default
  if (strchr(input, ' ') == NULL) {
    return false;
  }

  //isolate the keyword of the input
  char* inKey = new char[sizeof(input)];
  strncpy(inKey, input, strchr(input, ' ') - input);
  cout << inKey << endl;

  
  /*
    VALID KEYWORDS:
    - GO
    - GET
    - DROP
    - INVENTORY
    - QUIT
   */
  if (strcmp(inKey, "GO") == 0) {
    return true;
  }
  if (strcmp(inKey, "GET") == 0) {
    return true;
  }
  if (strcmp(inKey, "DROP") == 0) {
    return true;
  }
  if (strcmp(inKey, "INVENTORY") == 0) {
    return true;
  }
  if (strcmp(inKey, "QUIT") == 0) {
    return true;
  }

  return false;
  
}
