//
// Created by garrido-lestachebeli on 4/8/2026.
//

#ifndef WUMPUSHUNT_EMPTYROOM_H
#define WUMPUSHUNT_EMPTYROOM_H

#include "Room.h"


class EmptyRoom : public Room{
public:
    EmptyRoom();
    void activate(Map& map) override;
    void print() const override;
    void printPhrase() const override;
};


#endif //WUMPUSHUNT_EMPTYROOM_H