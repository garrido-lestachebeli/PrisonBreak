//
// Created by garrido-lestachebeli on 4/8/2026.
//

#ifndef WUMPUSHUNT_PLAYER_H
#define WUMPUSHUNT_PLAYER_H

#include "Character.h"

class Player : public Character {
public:
    void move(char direction, int space) override;
    void detectHazard() override;

    void useBow(char direction);
    void usePulse();
};


#endif //WUMPUSHUNT_PLAYER_H