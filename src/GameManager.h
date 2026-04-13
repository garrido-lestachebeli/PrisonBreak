//
// Created by garrido-lestachebeli on 4/10/2026.
//

#ifndef WUMPUSHUNT_GAMEMANAGER_H
#define WUMPUSHUNT_GAMEMANAGER_H


#include "Map.h"

class GameManager {
public:
    GameManager(int empAmmo = 3, int flashbangAmmo = 2);
    ~GameManager();
    void gameplayLoop();
private:
    Map map_;
    bool debugMode_;
    char getPlayerInput();
    void handlePlayerMove(char input);
    void handleWeaponUse(char input);
    bool checkWin();
    bool checkLose();
    void checkSurroundings();
    void moveGuards();
    void updateTurnCounters();
    void useEMP();
    void useFlashbang();
    void displayAmmo();
    void printRoomMap();
};

#endif //WUMPUSHUNT_GAMEMANAGER_H
