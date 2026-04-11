//
// Created by garrido-lestachebeli on 4/10/2026.
//

#ifndef WUMPUSHUNT_GAMEMANAGER_H
#define WUMPUSHUNT_GAMEMANAGER_H


#include "Map.h"

class GameManager {
public:
    GameManager();
    ~GameManager();

    void gameplayLoop();

private:
    Map map_;

    void printVisibleMap();
    char getPlayerInput();
    void handlePlayerMove(char input);
    bool checkWin();
    bool checkLose();
    void checkSurroundings();
    void moveGuards();
};

#endif //WUMPUSHUNT_GAMEMANAGER_H