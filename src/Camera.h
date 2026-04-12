//
// Created by garrido-lestachebeli on 4/8/2026.
//

#ifndef WUMPUSHUNT_CAMERA_H
#define WUMPUSHUNT_CAMERA_H


#include "Map.h"
#include "Room.h"

class Camera : public Room {
public:
    Camera();

    void activate(Map& map) override;
    void setPosition(int x, int y) override;
    void print() const override;
    void printPhrase() const override;
    
    void deactivate(int turns);
    void updateTurn();
    bool isDeactivated() const { return deactivatedTurns_ > 0; }
    
private:
    int deactivatedTurns_;
};



#endif //WUMPUSHUNT_CAMERA_H
