#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include "Room.h"
#include "Exit.h"
#include "Item.h"


using namespace std;

Room::Room() {
  
}


/*
The reasoning for the use of the const keyword was found at
https://www.geeksforgeeks.org/cpp/why-is-conversion-from-string-constant-to-char-valid-in-c-but-invalid-in-cpp/
 */
Room::Room(const char nDescription[200]) {
  description = new char[200];
  strcpy(description, nDescription);
}

void Room::setDescription(const char nDescription[200]) {
  description = new char[200];
  strcpy(description, nDescription);
}

char* Room::getDescription() {
  return description;
}
  

void Room::addLinkedRoom(Room* nRoom, Exit e) {
  map<Exit, Room*>* m = new map<Exit, Room*>();
  m -> insert({e, nRoom});
  linkedRooms.push_back(*m);
}

vector<map<Exit, Room*>> Room::getLinkedRooms() {
  return linkedRooms;
}
