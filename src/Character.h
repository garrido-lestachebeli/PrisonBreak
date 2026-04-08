//
// Created by garrido-lestachebeli on 4/8/2026.
//

#ifndef WUMPUSHUNT_CHARACTER_H
#define WUMPUSHUNT_CHARACTER_H


class Character {
public:
    int xpos;
    int ypos;

    Character();
    virtual ~Character() = default;

    virtual void move(char direction, int space) = 0;
    virtual void detectHazard() = 0;
};


#endif //WUMPUSHUNT_CHARACTER_H