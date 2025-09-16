#include <iostream>
#include <cstring>
#include <vector>
#include "Room.h"
#include "Exit.h"
#include "LinkedRoom.h"

using namespace std;

Room::Room() {
  
}

void Room::addLinkedRoom(LinkedRoom nLR) {
  linkedRooms.push_back(nLR);
}

vector<LinkedRoom> Room::getLinkedRooms() {
  return linkedRooms;
}
