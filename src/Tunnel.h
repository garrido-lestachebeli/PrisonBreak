//
// Created by garrido-lestachebeli on 4/8/2026.
//

#ifndef WUMPUSHUNT_TUNNEL_H
#define WUMPUSHUNT_TUNNEL_H

#include "Room.h"


class Tunnel : public Room {
public:
    Tunnel();
    void setExit(Tunnel* exit);
    Tunnel* getExit() const;
    void activate(Map& map) override;
    void setPosition(int x, int y) override;
    void print() const override;
    void printPhrase() const override;
private:
        Tunnel* exit;
};


#endif //WUMPUSHUNT_TUNNEL_H