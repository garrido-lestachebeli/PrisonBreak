//
// Created by garrido-lestachebeli on 4/8/2026.
//

#include "Map.h"
#include "Player.h"
#include "Guard.h"
#include "Camera.h"
#include "Exit.h"
#include "Tunnel.h"
#include "EmptyRoom.h"

#include <algorithm>
#include <random>
#include <vector>


Map::Map(int nGuards, int kCameras, int bExits, int mTunnelPairs){
    constexpr int SIZE = 7;
    constexpr int CENTER = 3;

    //populate with empty rooms
    map.resize(SIZE);
    for (int y = 0; y < SIZE; ++y) {
        map[y].resize(SIZE);
        for (int x = 0; x < SIZE; ++x) {
            map[y][x] = new EmptyRoom();
            map[y][x]->setPosition(x, y);
        }
    }

    //place the player in the middle
    delete map[CENTER][CENTER];
    map[CENTER][CENTER] = new Player();
    map[CENTER][CENTER]->setPosition(CENTER, CENTER);

    populate<Guard>(nGuards);
    populate<Camera>(kCameras);
    populate<Exit>(bExits);
    populateTunnelPairs(mTunnelPairs);
}


Map::~Map()
{
    for (auto& row : map) {
        for (auto& cell : row) {
            delete cell;
        }
    }
}


void Map::print() const
{
    for (const auto& row : map) {
        for (const auto& cell : row) {
            std::cout << cell->print() << ' ';
        }
        std::cout << '\n';
    }
}


std::pair<int,int> Map::getRandomEmptyCell() const{
    constexpr int SIZE = 7;

    while (true) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;

        if (dynamic_cast<EmptyRoom*>(map[y][x]) != nullptr) {
            return {x, y};
        }
    }
}


template <typename T>
void Map::populate(int n){
    for (int i = 0; i < n; ++i) {
        auto [x, y] = getRandomEmptyCell();

        delete map[y][x];
        map[y][x] = new T();
        map[y][x]->setPosition(x, y);
    }
}

void Map::populateTunnelPairs(int n) {
    for (int i = 0; i < n; ++i) {
        auto [x1, y1] = getRandomEmptyCell();
        auto [x2, y2] = getRandomEmptyCell();

        Tunnel* t1 = new Tunnel();
        Tunnel* t2 = new Tunnel();

        t1->setExit(t2);
        t2->setExit(t1);

        t1->setPosition(x1, y1);
        t2->setPosition(x2, y2);

        delete map[y1][x1];
        delete map[y2][x2];

        map[y1][x1] = t1;
        map[y2][x2] = t2;
    }
}