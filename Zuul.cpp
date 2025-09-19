#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include "Room.h"


using namespace std;

void processInput(char* input, Room* &room, vector<char*> &inventory);
void printInventory(vector<char*> inventory);

int main() { 

  vector<char*> inventory;  
  Room* currentRoom = NULL;

  //define and setup all the rooms
  Room* r1 = new Room("Room 1");
  Room* r2 = new Room("Room 2");

  r1 -> addLinkedRoom(r2, "NORTH");
  r2 -> addLinkedRoom(r1, "SOUTH");
  r1 -> addLinkedRoom(r2, "EAST");
  r1 -> addItem("BROOM");
  r1 -> addItem("CHAIR");

  
  currentRoom = r1;
  
  char* input = new char[80];

  currentRoom -> printRoom();
  cout << endl << endl;
  //game loop
  do {
   
    //get input and check keyword validity
    if (cin.fail()) {
      cin.clear();
      cin.ignore(10000, '\n');
    }
    cout << "Enter command (HELP): " << endl;
    cin.get(input, 80);
    cin.get();

    processInput(input, currentRoom, inventory);
    
  } while (strcmp(input, "QUIT") != 0);
  
  return 0;
}

void processInput(char* input, Room* &room, vector<char*> &inventory) {

  //isolates the keyword in the command
  char* inKey = new char[sizeof(input)];  

  bool hasSpace = false;
  if (strchr(input, ' ') != NULL) {
    strncpy(inKey, input, strchr(input, ' ') - input);
    hasSpace = true;
  }
  else {
    strcpy(inKey, input);
  }
  
  
  /*
    VALID KEYWORDS:
    - HELP (always works)
    - GO (must have space)
    - GET (must have space)
    - DROP (must have space)
    - INVENTORY (can't have space)
    - QUIT (can't have space)
   */

  //process the various keywords
  if (strcmp(inKey, "HELP") == 0) {
    cout << "List of valid commands:" << endl;
    cout << " - GO [DIRECTION]" << endl;
    cout << " - GET [ITEM]" << endl;
    cout << " - DROP [ITEM]" << endl;
    cout << " - INVENTORY" << endl;
    cout << " - QUIT" << endl;
    return;
  }


  
  if (strcmp(inKey, "GO") == 0 && hasSpace) {
    //checks if the exit matches an exit of the room
    char* exit = new char[20];
    //this assumes that there are only two words in the input
    //technically, the user could put GO _______ NORTH, and that would work.
    strcpy(exit, strrchr(input, ' ') + 1); 

    //check if this matches any of the exits in the room
    for (auto e : room -> getLinkedRooms()) {
      if (strcmp(e.first, exit) == 0) {
	//exit matched, update the new room, print new room
	room = e.second;
	room -> printRoom();
	return;
      }
    }

    //no rooms matched, reprint exits
    cout << "That's not an exit!" << endl;
    room -> printExits();
    
    return;
  }


  
  if (strcmp(inKey, "GET") == 0 && hasSpace) {
    //checks if the item matches an item in the room
    char* item = new char[20];
    //this assumes that there are only two words in the input
    //technically, the user could put GET _______ BROOM, and that would work.
    strcpy(item, strrchr(input, ' ') + 1); 

    char* tempItem = room -> removeItem(item);
    
    if (tempItem != NULL) {
      inventory.push_back(tempItem);
    }
    else {
      //no matching item
      cout << "That's not in this room!" << endl;
      room -> printItems();
    }
    
    return;
  }


  
  if (strcmp(inKey, "DROP") == 0 && hasSpace) {
    //checks if the item is in the inventory
    char* item = new char[20];
    
    strcpy(item, strrchr(input, ' ') + 1); 

    //check if this matches any of the exits in the room
    for (int i = 0; i < inventory.size(); i++) {
      if (strcmp(inventory.at(i), item) == 0) {
	//item matched, update the new room and inventory
	room -> addItem(inventory.at(i));
	inventory.erase(inventory.begin() + i);
	return;
      }
    }

    //item not in inventory
    cout << "You don't have that!" << endl;
    printInventory(inventory);

    return;
  }


  
  if (strcmp(inKey, "INVENTORY") == 0 && !hasSpace) {
    printInventory(inventory);
    return;
  }


  
  if (strcmp(inKey, "QUIT") == 0 && !hasSpace) {
    return;
  }

  return;
  
}


void printInventory(vector<char*> inventory) {
  //empty inventory? tell the user
  if (inventory.empty()) {
    cout << "Your inventory is empty." << endl;
    return;
  }
  //otherwise print the inventory

  cout << "Inventory:" << endl;

  for (char* i : inventory) {
    cout << i << " ";
  }
  cout << endl;
}
