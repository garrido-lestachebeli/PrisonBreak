//
// Created by garrido-lestachebeli on 4/8/2026.
//

#ifndef WUMPUSHUNT_ROOM_H
#define WUMPUSHUNT_ROOM_H

class Room {
public:
    int xpos;
    int ypos;

    Room();
    Room(int x, int y);
    virtual ~Room() = default;

    virtual void activate() = 0;
    virtual void print() = 0;
};




#endif //WUMPUSHUNT_ROOM_H