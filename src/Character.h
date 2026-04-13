//
// Created by garrido-lestachebeli on 4/8/2026.
//

#ifndef WUMPUSHUNT_CHARACTER_H
#define WUMPUSHUNT_CHARACTER_H
#include <utility>


class Character {
public:
    Character() : x(0), y(0) {}
    Character(const int x, const int y) : x(x), y(y) {}
    virtual ~Character() = default;
    virtual void setPosition(int x, int y) = 0;
    virtual std::pair<int, int> getPosition() = 0;
    virtual void print() const = 0;
    virtual void printPhrase() const = 0;
protected: int x, y;
};


#endif //WUMPUSHUNT_CHARACTER_H