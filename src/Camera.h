//
// Created by garrido-lestachebeli on 4/8/2026.
//

#ifndef WUMPUSHUNT_CAMERA_H
#define WUMPUSHUNT_CAMERA_H



#include "Room.h"

class Camera : public Room {
public:
    Camera();

    void activate() override;
    void print() const override;
};



#endif //WUMPUSHUNT_CAMERA_H