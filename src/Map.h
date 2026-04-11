//
// Created by garrido-lestachebeli on 4/8/2026.
//

#ifndef WUMPUSHUNT_MAP_H
#define WUMPUSHUNT_MAP_H


#include <vector>
class Room;
#include "Character.h"
#include "Player.h"


class Map {
public:
    Map(int aGuards, int bCameras, int cExits, int dTunnelPairs);

    ~Map();
    Room* getRoom(int index) const;
    Character* getCharacter(int index) const;

    void move(int x1, int y1, int x2, int y2);
    std::pair<int,int> getRandomEmptyCellRoomMap() const;
    std::pair<int,int> getRandomEmptyCellCharacterMap() const;
    void print();
    std::pair<int,int> getOtherTunnel(int x, int y) ;
    void setAlert(int x, int y) {alertActive_ = true;  alertPosition_ = {x, y}; }
    bool isAlertActive() const {return alertActive_;}
    std::pair<int,int> getAlertPosition() const {return alertPosition_;}
    void clearAlert() {alertActive_ = false;}
private:
    bool alertActive_ = false;
    std::pair<int,int> alertPosition_;

    void generateRoomMap(int bCameras, int cExits, int dTunnelPairs);
    void generateCharacterMap(int aGuard);
    template <typename T>
    void populateRoom(int n);
    void populateTunnelPairs(int n);
    void populateCharacter(int n);
    std::vector<std::vector<Room*>> roomMap;
    std::vector<std::vector<Character*>> characterMap;
    Player *player = new Player;
    std::vector<std::pair<int,int>> tunnelPositions_;
};


#endif //WUMPUSHUNT_MAP_H