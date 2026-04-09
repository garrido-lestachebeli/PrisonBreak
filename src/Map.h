//
// Created by garrido-lestachebeli on 4/8/2026.
//

#ifndef WUMPUSHUNT_MAP_H
#define WUMPUSHUNT_MAP_H


#include <memory>
#include <vector>
#include "Room.h"

class Map {
public:
    Map(int aGuards, int bCameras, int cExits, int dTunnelPairs);
    ~Map();
    char get(int index);
    void move(Room room1, Room room2);
    void print();
    std::pair<int,int> getRandomEmptyCell() const;

private:
    template <typename T>
    void populate(int n);
    void populateTunnelPairs(int n);
    std::vector<std::vector<GridObject*>> map;
};


#endif //WUMPUSHUNT_MAP_H