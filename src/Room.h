//
// Created by garrido-lestachebeli on 4/8/2026.
//

#ifndef WUMPUSHUNT_ROOM_H
#define WUMPUSHUNT_ROOM_H
class Map;

class Room {
public:
    Room() = default;
    virtual ~Room() = default;
    virtual void activate(Map& map) = 0;
    virtual void print() const = 0;
    virtual void printPhrase() const = 0;
};


#endif //WUMPUSHUNT_ROOM_H
