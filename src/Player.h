//
// Created by garrido-lestachebeli on 4/8/2026.
//

#ifndef WUMPUSHUNT_PLAYER_H
#define WUMPUSHUNT_PLAYER_H

#include "Character.h"

class Player : public Character {
public:
    void move(char direction, int spaces) override;
    void detectHazard() override;

    void print() const override;
    void activate() override;
    void setPosition(int x, int y)  override;
};


#endif //WUMPUSHUNT_PLAYER_H