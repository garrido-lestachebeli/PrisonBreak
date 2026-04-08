//
// Created by garrido-lestachebeli on 4/8/2026.
//

#ifndef WUMPUSHUNT_TUNNEL_H
#define WUMPUSHUNT_TUNNEL_H

#include "Room.h"


class Tunnel : public Room {
public:
    Tunnel* exit;

    Tunnel();

    void activate() override;
    void print() override;
};


#endif //WUMPUSHUNT_TUNNEL_H