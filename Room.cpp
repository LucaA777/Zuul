#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include "Room.h"
#include "Exit.h"

using namespace std;

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
  linkedRooms.insert({e, nRoom});
}

map<Exit, Room*> Room::getLinkedRooms() {
  return linkedRooms;
}

void Room::addItem(const char nName[25]) {
  char* name = new char[25];
  strcpy(name, nName);
  items.push_back(name);
}

void Room::addItem(char* nName) {
  char* name = new char[25];
  strcpy(name, nName);
  items.push_back(name);
}

char* Room::removeItem(char* nName) {
  //loop through items to see if it exists
  vector<char*>::iterator it;
  
  for (int i = 0; i < items.size(); i++) {
    if (strcmp(items.at(i), nName) == 0) {
      //item found
      items.erase(items.begin() + i);
      return nName;
    }
  }

  //no matches
  return NULL;
}

vector<char*> Room::getItems() {
  return items;
}

void Room::printItems() {
  for (char* i : items) {
    cout << i << " ";
  }
  cout << endl;
}

void Room::printRoom() {
  cout << description << endl << endl;
  cout << "There are exits:" << endl;
  
  for (auto e : linkedRooms) {
    cout << (e.first == 0 ? "NORTH" : (e.first == 1 ? "EAST" : (e.first == 2 ? "SOUTH" : "WEST"))) << " ";
  }

  cout << endl << endl;

  cout << "There are items:" << endl;
  printItems();
  
}
