//
// Created by garrido-lestachebeli on 4/8/2026.
//

#ifndef WUMPUSHUNT_GUARD_H
#define WUMPUSHUNT_GUARD_H

#include "Character.h"


class Guard : public Character {
public:
    void move(char direction, int space) override;
    void detectHazard() override;
    void print() const override;

    void moveTowardsPlayer();
};


#endif //WUMPUSHUNT_GUARD_H