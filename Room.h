#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <vector>
#include <map>
#include "Exit.h"
#include "Item.h"


using namespace std;

class Room {
 public:
  Room();
  Room(const char nDescription[200]);
  void setDescription(const char nDescription[200]);
  char* getDescription();

  void addLinkedRoom(Room* nRoom, Exit e);
  vector<map<Exit, Room*>> getLinkedRooms();

 private:
  char* description;
  vector<map<Exit, Room*>> linkedRooms;

};

#endif
