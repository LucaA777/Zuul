//THIS CLASS HAS BEEN DISCARDED AND IS NO LONGER IN USE

#ifndef LINKEDROOM_H
#define LINKEDROOM_H

#include "Exit.h"
#include "Room.h"

/*
The "class Room;" is a forward declared dependency
I learned this prom Disch's response in
https://cplusplus.com/forum/general/82427/
 */
class Room; 

struct LinkedRoom {
  Room* room;
  Exit exit;
};

#endif
