//
// Created by garrido-lestachebeli on 4/8/2026.
//

#ifndef WUMPUSHUNT_MAP_H
#define WUMPUSHUNT_MAP_H


#include <memory>
#include <vector>
#include "Room.h"
#include "Character.h"


class Map {
public:
    Map(int aGuards, int bCameras, int cExits, int dTunnelPairs);


    ~Map();
    Room* getRoom(int index) const;
    Character* getCharacter(int index) const;

    void move(int x1, int y1, int x2, int y2);
    std::pair<int,int> getRandomEmptyCellRoomMap() const;
    std::pair<int,int> getRandomEmptyCellCharacterMap() const;


private:
    void generateRoomMap(int bCameras, int cExits, int dTunnelPairs);
    void generateCharacterMap(int aGuard);
    template <typename T>
    void populateRoom(int n);
    void populateTunnelPairs(int n);
    void populateCharacter(int n);
    std::vector<std::vector<Room*>> roomMap;
    std::vector<std::vector<Character*>> characterMap;
};


#endif //WUMPUSHUNT_MAP_H