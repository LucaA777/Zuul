#ifndef ROOM_H
#define ROOM_H

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Room {
 public:

  Room(const char nDescription[200]);

  void setDescription(const char nDescription[200]);
  char* getDescription();

  void addLinkedRoom(Room* nRoom, const char nExit[20]);
  void removeLinkedRoom(const char nExit[20]);
  map<char*, Room*> getLinkedRooms();
  void printExits();
  
  void addItem(const char nName[25]);
  void addItem(char* nName);
  char* removeItem(char* nName);
  vector<char*> getItems();
  void printItems();

  void printRoom();
  
 private:
  
  char* description;

  map<char*, Room*> linkedRooms;

  vector<char*> items;
};

#endif
