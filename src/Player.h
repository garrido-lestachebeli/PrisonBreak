//
// Created by garrido-lestachebeli on 4/8/2026.
//

#ifndef WUMPUSHUNT_PLAYER_H
#define WUMPUSHUNT_PLAYER_H

#include "Character.h"
#include <utility>

enum class WeaponType {
    EMP,
    FLASHBANG
};

class Player : public Character {
public:
    Player(int empAmmo = 3, int flashbangAmmo = 2);
    
    void move(char direction, int spaces) override;
    void detectHazard() override;

    void print() const override;
    void setPosition(int x, int y)  override;

    std::pair<int, int> getPosition() override;
    void printPhrase() const override;
    
    bool useWeapon(WeaponType type);
    int getEmpAmmo() const { return empAmmo_; }
    int getFlashbangAmmo() const { return flashbangAmmo_; }
    
private:
    int empAmmo_;
    int flashbangAmmo_;
};


#endif //WUMPUSHUNT_PLAYER_H
