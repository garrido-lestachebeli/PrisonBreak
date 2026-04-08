//
// Created by garrido-lestachebeli on 4/8/2026.
//

#ifndef WUMPUSHUNT_EXIT_H
#define WUMPUSHUNT_EXIT_H


#include "Room.h"

class Exit : public Room {
public:
    Exit();

    void activate() override;
    void print() override;
};


#endif //WUMPUSHUNT_EXIT_H