//
// Created by garrido-lestachebeli on 4/8/2026.
//

#ifndef WUMPUSHUNT_PLAYER_H
#define WUMPUSHUNT_PLAYER_H

#include "Character.h"
#include <utility>

class Player : public Character {
public:
    void move(char direction, int spaces) override;
    void detectHazard() override;

    void print() const override;
    void setPosition(int x, int y)  override;

    std::pair<int, int> getPosition() override;
    void printPhrase() const override;
};


#endif //WUMPUSHUNT_PLAYER_H