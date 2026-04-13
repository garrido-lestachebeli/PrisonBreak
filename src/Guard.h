//
// Created by garrido-lestachebeli on 4/8/2026.
//

#ifndef WUMPUSHUNT_GUARD_H
#define WUMPUSHUNT_GUARD_H

#include "Character.h"


class Guard : public Character {
public:
    Guard();
    void printPhrase() const override;
    void print() const override;
    void setPosition(int x, int y)  override;
    void stun(int turns);
    void updateTurn();
    std::pair<int, int> getPosition() override;
    bool isStunned() const { return stunnedTurns_ > 0; }
private:
    int stunnedTurns_;
};


#endif //WUMPUSHUNT_GUARD_H
