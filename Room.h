#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <vector>
#include "Exit.h"
#include "LinkedRoom.h"

using namespace std;

class Room {
 public:
  Room();
  void setDescription(char*);
  char* getDescription();

  void addLinkedRoom(LinkedRoom nLR);
  vector<LinkedRoom> getLinkedRooms();

 private:
  char* decription;
  vector<LinkedRoom> linkedRooms;

};

#endif
