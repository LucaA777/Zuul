#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include "Room.h"


using namespace std;

void processInput(char* input, Room* &room, vector<char*> &inventory);
void printInventory(vector<char*> inventory);

int main() { 

  //create player information variables
  vector<char*> inventory;  
  Room* currentRoom = NULL;

  //define all the rooms
  Room* Dorm1 = new Room("You are in a sleeping space. It's really small and there are way too many things hanging everywhere.");

  Room* HallB = new Room("You are in an open hallway, There are a lot of doors, I wonder where they might lead.");
  
  Room* Storage1 = new Room("You are in a cramped storage closet. There are drawers everywhere and racks with packets tied down.");

  Room* SpaceToilet1 = new Room("You are in a tiny room with a giant harness and a seat like hole in the middle. I wonder what that could be...");

  Room* Dorm2 = new Room("You find yourself in another dormitory. This one isn't yours, you shouldn't be intruding like this.");

  Room* Storage2 = new Room("You are in another storage space. This one is concerningly empty");

  Room* HallC = new Room("You are in an open hallway, this one is mysteriously very clean.");

  Room* SpaceToilet2 = new Room("You are standing in front of a space toilet!");

  Room* MainSpace = new Room("You find yourself in a large open space. It looks like things were left in a mess.");

  Room* Gym = new Room("You are in the gym. There are a lot of fancy machines here, must  have been expensive.");

  Room* HallA = new Room("You are in a long hallway, there are locked doors on either side, looks like you might need some kind of identification...");

  Room* BioLab = new Room("Wow! You are floating in the middle of a high-tech laboratory. There are plants growing in small dishes and UV lights in containment spaces.");

  Room* Airlock = new Room("You are in a strangely empty room. Theres a large door with a lot of locks on one side.");

  Room* Space = new Room("This is incredible! You are in space! And you're alive too! Wait, is that a floating body...");

  Room* ObservationDeck = new Room("You find yourself mesmerized by the view, you are standing in a bubble of glass, looking down at the earth.");

  Room* HallD = new Room("You are in a small hallway. Locked doors on all sides.");

  Room* ShuttleDock = new Room("Woah! You're in a weird chamber. Theres a huge door with a ton of bolts on one wall.");

  Room* Shuttle = new Room("Congratulations! You've made it to the space shuttle!");


  //connect all the rooms
  Dorm1 -> addLinkedRoom(HallB, "EAST");

  HallB -> addLinkedRoom(Dorm1, "WEST");
  HallB -> addLinkedRoom(Storage1, "NORTH");
  HallB -> addLinkedRoom(SpaceToilet1, "EAST");
  HallB -> addLinkedRoom(MainSpace, "SOUTH");

  Storage1 -> addLinkedRoom(HallB, "SOUTH");

  SpaceToilet1 -> addLinkedRoom(HallB, "WEST");

  Dorm2 -> addLinkedRoom(HallC, "EAST");

  HallC -> addLinkedRoom(Dorm2, "WEST");
  HallC -> addLinkedRoom(Storage2, "SOUTH");
  HallC -> addLinkedRoom(SpaceToilet2, "EAST");
  HallC -> addLinkedRoom(MainSpace, "NORTH");

  Storage2 -> addLinkedRoom(HallC, "NORTH");

  SpaceToilet2 -> addLinkedRoom(HallC, "WEST");

  MainSpace -> addLinkedRoom(HallB, "NORTH");
  MainSpace -> addLinkedRoom(HallC, "SOUTH");
  MainSpace -> addLinkedRoom(Gym, "WEST");
  MainSpace -> addLinkedRoom(HallA, "EAST");

  Gym -> addLinkedRoom(MainSpace, "EAST");

  HallA -> addLinkedRoom(MainSpace, "WEST");
  HallA -> addLinkedRoom(ObservationDeck, "EAST");

  ObservationDeck -> addLinkedRoom(HallA, "WEST");

  
  //add items to rooms
  Storage1 -> addItem("SPACE_FOOD");
  Storage1 -> addItem("HYDRATION_PACK");
  
  Gym -> addItem("DUMBELL");

  Dorm2 -> addItem("ID_CARD");

  BioLab -> addItem("PLANT");
  BioLab -> addItem("UV_LIGHT");

  ObservationDeck -> addItem("TELESCOPE");

  HallD -> addItem("SPACE_SUIT");

  Space -> addItem("SHUTTLE_KEY");


  //setup for input
  char* input = new char[80];

  cout << endl << "You wake up with a jolt. The alarms are blaring." << endl;
  cout << "Quickly, you remove yourself from the straps that" << endl;
  cout << "hold you to the wall. Where are you? Right, you're" << endl;
  cout << "on a space station in orbit right now." << endl << endl;
  cout << "OBJECTIVE: find a way out of the space station as fast as possible." << endl << endl;

  
  //setup current room
  currentRoom = Dorm1;
  cout << endl << endl;
  currentRoom -> printRoom();
  cout << endl;

  //setup room dependencies checks
  bool openedID = false; //ID_CARD
  bool openedSS = false; //SPACE_SUIT
  bool openedSK = false; //SHUTTLE_KEY

  
  //game loop
  do {
   
    //get input
    if (cin.fail()) {
      cin.clear();
      cin.ignore(10000, '\n');
    }
    
    cout << "Enter command ('HELP' for instruction): " << endl;
    cin.get(input, 80);
    cin.get();

    cout << endl;

    //process input
    processInput(input, currentRoom, inventory);


    //update room-item dependencies
    bool hasID_CARD = false;
    bool hasSPACE_SUIT = false;
    bool hasSHUTTLE_KEY = false;

    //check if the inventory contains the items
    for (char* i : inventory) {
      if (strcmp(i, "ID_CARD") == 0) {
	hasID_CARD = true;
      }
      if (strcmp(i, "SPACE_SUIT") == 0) {
	hasSPACE_SUIT = true;
      }
      if (strcmp(i, "SHUTTLE_KEY") == 0) {
	hasSHUTTLE_KEY = true;
      }
    }

    //update room exits
    if (hasID_CARD && !openedID) {
      //means the player has the ID_CARD
      HallA -> addLinkedRoom(BioLab, "NORTH");
      HallA -> addLinkedRoom(Airlock, "SOUTH");
      BioLab -> addLinkedRoom(HallA, "SOUTH");
      Airlock -> addLinkedRoom(HallA, "NORTH");
      ObservationDeck -> addLinkedRoom(HallD, "EAST");
      HallD -> addLinkedRoom(ObservationDeck, "WEST");
      openedID = true;
    }
    else if (!hasID_CARD && openedID) {
      //the player doesn't have the ID_CARD;
      HallA -> removeLinkedRoom("NORTH");
      HallA -> removeLinkedRoom("SOUTH");
      BioLab -> removeLinkedRoom("SOUTH");
      Airlock -> removeLinkedRoom("NORTH");
      ObservationDeck -> removeLinkedRoom("EAST");
      HallD -> removeLinkedRoom("WEST");
      openedID = false;
    }


    if (hasSPACE_SUIT && !openedSS) {
      //it means the player has the SPACE_SUIT
      Airlock -> addLinkedRoom(Space, "SOUTH");
      Space -> addLinkedRoom(Airlock, "NORTH");
      ShuttleDock -> addLinkedRoom(HallD, "WEST");
      HallD -> addLinkedRoom(ShuttleDock, "EAST");
      openedSS = true;
    }
    else if (!hasSPACE_SUIT && openedSS) {
      Airlock -> removeLinkedRoom("SOUTH");
      Space -> removeLinkedRoom("NORTH");
      ShuttleDock -> removeLinkedRoom("WEST");
      HallD -> removeLinkedRoom("EAST");
      openedSS = false;
    }


    if (hasSHUTTLE_KEY && !openedSK) {
      //the player has the shuttle key
      Shuttle -> addLinkedRoom(ShuttleDock, "WEST");
      ShuttleDock -> addLinkedRoom(Shuttle, "EAST");
      openedSK = true;
    }
    else if (!hasSHUTTLE_KEY && openedSK) {
      Shuttle -> removeLinkedRoom("WEST");
      ShuttleDock -> removeLinkedRoom("EAST");
      openedSK = false;
    }
		    
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


  //process "GO"
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
	cout << endl;
	room -> printRoom();
	cout << endl;
	return;
      }
    }

    //no rooms matched, reprint exits
    cout << "That's not an exit!" << endl;
    room -> printExits();
    cout << endl;
    return;
  }


  //process "GET"
  if (strcmp(inKey, "GET") == 0 && hasSpace) {
    //checks if the item matches an item in the room
    char* item = new char[20];
    //this assumes that there are only two words in the input
    //technically, the user could put GET _______ BROOM, and that would work.
    strcpy(item, strrchr(input, ' ') + 1); 

    //function removes item if it exits and returns it
    char* tempItem = room -> removeItem(item);
    
    if (tempItem != NULL) {
      //if the item was in the room, add it to inventory
      inventory.push_back(tempItem);

      cout << endl;
      printInventory(inventory);
      cout << endl;
      room -> printItems();
      cout << endl;
    }
    else {
      //no matching item
      cout << "That's not in this room!" << endl;
      room -> printItems();
      cout << endl;
    }
    
    return;
  }


  //process "DROP"
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

	cout << endl;
	printInventory(inventory);
	cout << endl;
	room -> printItems();
	cout << endl;
	return;
      }
    }

    //item not in inventory
    cout << "You don't have that!" << endl;
    printInventory(inventory);
    cout << endl;
    return;
  }


  //process "INVENTORY"
  if (strcmp(inKey, "INVENTORY") == 0 && !hasSpace) {
    printInventory(inventory);
    cout << endl;
    return;
  }


  //process "QUIT"
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
