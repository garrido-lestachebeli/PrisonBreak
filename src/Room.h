//
// Created by garrido-lestachebeli on 4/8/2026.
//

#ifndef WUMPUSHUNT_ROOM_H
#define WUMPUSHUNT_ROOM_H


class Room {
public:
    Room();
    Room(int x, int y);
    virtual ~Room() = default;
    virtual void activate() = 0;
    virtual void setPosition(int x, int y) = 0;
    virtual void print() const = 0;
};


#endif //WUMPUSHUNT_ROOM_H