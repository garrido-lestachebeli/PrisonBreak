//
// Created by garrido-lestachebeli on 4/8/2026.
//

#ifndef WUMPUSHUNT_EMPTYROOM_H
#define WUMPUSHUNT_EMPTYROOM_H


class EmptyRoom : public Room{
public:
    EmptyRoom();

    void activate() override;
    void print() const override;
};


#endif //WUMPUSHUNT_EMPTYROOM_H