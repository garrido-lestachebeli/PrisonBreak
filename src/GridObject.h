//
// Created by garrido-lestachebeli on 4/8/2026.
//

#ifndef WUMPUSHUNT_GRIDOBJECT_H
#define WUMPUSHUNT_GRIDOBJECT_H


class GridObject {
public:
    GridObject();
    GridObject(int x, int y);
    virtual ~GridObject() = default;

    int getX() const;
    int getY() const;
    void setPosition(int newX, int newY);

    virtual void print() const = 0;
};


#endif //WUMPUSHUNT_GRIDOBJECT_H