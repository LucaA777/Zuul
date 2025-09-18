#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include "Exit.h"
#include "Room.h"


using namespace std;

bool isValidInput(char* input);

int main() { 

  vector<char*> inventory;  
  vector<Room> rooms;

  //define and setup all the rooms
  Room* r1 = new Room("Room 1");
  Room* r2 = new Room("Room 2");

  r1 -> addLinkedRoom(r2, NORTH);
  r2 -> addLinkedRoom(r1, SOUTH);
  r1 -> addLinkedRoom(r2, EAST);
  r1 -> addItem("BROOM");
  r1 -> addItem("CHAIR");

  cout << "Items in Room 1:" << endl;
  r1 -> printItems();

  r1 -> printRoom();
  
  char* input = new char[80];

  //get input and check keyword validity
  do {
    if (cin.fail()) {
      cin.clear();
      cin.ignore(10000, '\n');
    }
    cout << "Enter command (HELP): " << endl;
    cin.get(input, 80);
    cin.get();
    
  } while (!isValidInput(input));

  
  
  return 0;
}

bool isValidInput(char* input) {
  char* inKey = new char[sizeof(input)];  
  
  if (strchr(input, ' ') != NULL) {
    strncpy(inKey, input, strchr(input, ' ') - input);  
  }
  else {
    strcpy(inKey, input);
  }
  
  cout << inKey << endl;
  
  /*
    VALID KEYWORDS:
    - HELP
    - GO
    - GET
    - DROP
    - INVENTORY
    - QUIT
   */
  if (strcmp(inKey, "HELP") == 0) {
    cout << "List of valid commands:" << endl;
    cout << " - GO" << endl;
    cout << " - GET" << endl;
    cout << " - DROP" << endl;
    cout << " - INVENTORY" << endl;
    cout << " - QUIT" << endl;
    return false;
  }
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
