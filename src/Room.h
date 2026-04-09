//
// Created by garrido-lestachebeli on 4/8/2026.
//

#ifndef WUMPUSHUNT_ROOM_H
#define WUMPUSHUNT_ROOM_H

#include "GridObject.h"

class Room : public GridObject {
public:
    Room();
    Room(int x, int y);
    virtual ~Room() = default;
};


#endif //WUMPUSHUNT_ROOM_H