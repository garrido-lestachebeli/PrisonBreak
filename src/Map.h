//
// Created by garrido-lestachebeli on 4/8/2026.
//

#ifndef WUMPUSHUNT_MAP_H
#define WUMPUSHUNT_MAP_H



#include <vector>
#include "Room.h"

class Map {
public:
    std::vector<std::vector<char>> map;

    void generate();
    char get(int index);
    void move(Room room1, Room room2);
};


#endif //WUMPUSHUNT_MAP_H