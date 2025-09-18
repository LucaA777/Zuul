#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <vector>
#include <map>
#include "Exit.h"

using namespace std;

class Room {
 public:

  Room(const char nDescription[200]);

  void setDescription(const char nDescription[200]);
  char* getDescription();

  void addLinkedRoom(Room* nRoom, Exit e);
  vector<map<Exit, Room*>> getLinkedRooms();

  void addItem(const char nName[25]);
  void addItem(char* nName);
  char* removeItem(char* nName);
  vector<char*> getItems();
  void printItems();
  
 private:
  
  char* description;

  vector<map<Exit, Room*>> linkedRooms;

  vector<char*> items;
};

#endif
