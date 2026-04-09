//
// Created by garrido-lestachebeli on 4/8/2026.
//

#ifndef WUMPUSHUNT_CHARACTER_H
#define WUMPUSHUNT_CHARACTER_H


#include "GridObject.h"

class Character : public GridObject {
public:
    Character();
    Character(int x, int y);
    virtual ~Character() = default;

    virtual void move(char direction, int spaces) = 0;
    virtual void detectHazard() = 0;
};


#endif //WUMPUSHUNT_CHARACTER_H