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
#include <iostream>
#include <random>
#include <vector>


/************************************************************
 * Map Constructor
 * ----------------------------------------------------------
 * Initializes the game map by first generating the static
 * room layout, then placing all characters.
 ************************************************************/
Map::Map(int nGuards, int kCameras, int bExits, int mTunnelPairs, int empAmmo, int flashbangAmmo){
    player = new Player(empAmmo, flashbangAmmo);

    generateRoomMap(kCameras, bExits, mTunnelPairs);
    generateCharacterMap(nGuards);
}

/************************************************************
 * Map Destructor
 * ----------------------------------------------------------
 * Frees all dynamically allocated Room and Character objects.
 ************************************************************/
Map::~Map(){
    for (auto& row : roomMap) {
        for (auto& cell : row) {
            delete cell;
        }
    }

    for (auto& row : characterMap) {
        for (auto& cell : row) {
            delete cell;
        }
    }
}

void Map::print() {
    if (characterMap.empty()) return;

    int rows = characterMap.size();
    int cols = characterMap[0].size();

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            if (characterMap[r][c] != nullptr) {
                characterMap[r][c]->print();  // prints P or G
            } else {
                std::cout << "."; // hidden room
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }
}

/************************************************************
 * generateCharacterMap
 * ----------------------------------------------------------
 * Initializes the character grid, places the player in the
 * center of the map, and randomly populates guards in empty
 * cells.
 ************************************************************/
void Map::generateCharacterMap(int nGuards){
    constexpr int SIZE = 7;
    constexpr int CENTER = 3;

    /* Initialize character grid with nullptrs */
    characterMap.resize(SIZE);
    for (int y = 0; y < SIZE; ++y) {
        characterMap[y].resize(SIZE);
        for (int x = 0; x < SIZE; ++x) {
            characterMap[y][x] = nullptr;
        }
    }

    /* Create and place player at the center */
    player->setPosition(CENTER, CENTER);
    characterMap[CENTER][CENTER] = player;

    /* Populate guards in remaining empty cells */
    populateCharacter(nGuards);
}

/************************************************************
 * generateRoomMap
 * ----------------------------------------------------------
 * Initializes the static room grid with EmptyRoom objects,
 * then replaces some with Camera, Exit, and Tunnel rooms.
 ************************************************************/
void Map::generateRoomMap(int bCameras, int cExits, int dTunnelPairs){
    constexpr int SIZE = 7;

    /* Fill entire map with EmptyRoom objects */
    roomMap.resize(SIZE);
    for (int y = 0; y < SIZE; ++y) {
        roomMap[y].resize(SIZE);
        for (int x = 0; x < SIZE; ++x) {
            roomMap[y][x] = new EmptyRoom();
            roomMap[y][x]->setPosition(x, y);
        }
    }

    /* Populate special rooms */
    populateRoom<Camera>(bCameras);
    populateRoom<Exit>(cExits);
    populateTunnelPairs(dTunnelPairs);
}

/************************************************************
 * move
 * ----------------------------------------------------------
 * Moves a character from (x1, y1) to (x2, y2) if the move
 * is valid. After movement, activates the room at the
 * destination location.
 ************************************************************/
void Map::move(int x1, int y1, int x2, int y2) {
    int rows = (int)characterMap.size();
    int cols = (int)characterMap[0].size();

    // bounds check
    if (x2 < 0 || x2 >= cols || y2 < 0 || y2 >= rows)
        return;

    Character* c = characterMap[y1][x1];
    if (!c) return;

    if (characterMap[y2][x2] != nullptr && characterMap[y2][x2] != player)
        return;

    characterMap[y2][x2] = c;
    characterMap[y1][x1] = nullptr;

    c->setPosition(x2, y2);
}

/************************************************************
 * getRandomEmptyCellRoomMap
 * ----------------------------------------------------------
 * Returns the coordinates of a random cell containing an
 * EmptyRoom. Used for placing special room objects.
 ************************************************************/
std::pair<int,int> Map::getRandomEmptyCellRoomMap() const{
    constexpr int SIZE = 7;

    while (true) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;

        if (dynamic_cast<EmptyRoom*>(roomMap[y][x]) != nullptr) {
            return {x, y};
        }
    }
}

/************************************************************
 * getRandomEmptyCellCharacterMap
 * ----------------------------------------------------------
 * Returns the coordinates of a random unoccupied character
 * cell (nullptr). Used for placing guards.
 ************************************************************/
std::pair<int,int> Map::getRandomEmptyCellCharacterMap() const{
    constexpr int SIZE = 7;

    while (true) {
        int x = rand() % SIZE;
        int y = rand() % SIZE;

        if (characterMap[y][x] == nullptr) {
            return {x, y};
        }
    }
}

/************************************************************
 * populateRoom<T>
 * ----------------------------------------------------------
 * Template function that replaces EmptyRoom cells with
 * instances of a specific Room subtype.
 ************************************************************/
template <typename T>
void Map::populateRoom(int n){
    for (int i = 0; i < n; ++i) {
        auto [x, y] = getRandomEmptyCellRoomMap();

        delete roomMap[y][x];
        roomMap[y][x] = new T();
        roomMap[y][x]->setPosition(x, y);
    }
}

/************************************************************
 * populateCharacter
 * ----------------------------------------------------------
 * Randomly places Guard objects in empty character cells,
 * ensuring the player’s starting position is not overwritten.
 ************************************************************/
void Map::populateCharacter(int n){
    constexpr int CENTER = 3;

    for (int i = 0; i < n; ++i) {
        auto [x, y] = getRandomEmptyCellCharacterMap();

        if (x == CENTER && y == CENTER) {
            --i;
            continue;
        }

        Guard* g = new Guard();
        g->setPosition(x, y);
        characterMap[y][x] = g;
    }
}

/************************************************************
 * populateTunnelPairs
 * ----------------------------------------------------------
 * Places pairs of Tunnel rooms in distinct EmptyRoom cells
 * and links each pair together.
 ************************************************************/
void Map::populateTunnelPairs(int n){
    for (int i = 0; i < n; ++i) {
        auto [x1, y1] = getRandomEmptyCellRoomMap();

        int x2, y2;
        do {
            auto temp = getRandomEmptyCellRoomMap();
            x2 = temp.first;
            y2 = temp.second;
        } while (x2 == x1 && y2 == y1);

        Tunnel* t1 = new Tunnel();
        Tunnel* t2 = new Tunnel();

        t1->setExit(t2);
        t2->setExit(t1);

        t1->setPosition(x1, y1);
        t2->setPosition(x2, y2);

        delete roomMap[y1][x1];
        delete roomMap[y2][x2];

        roomMap[y1][x1] = t1;
        roomMap[y2][x2] = t2;
    }
}

/************************************************************
 * getRoom / getCharacter
 * ----------------------------------------------------------
 * Provides linear index access to the room and character
 * grids using row-major ordering.
 ************************************************************/
Room* Map::getRoom(int x, int y) const {
    int rows = (int)roomMap.size();
    int cols = (int)roomMap[0].size();

    if (x < 0 || x >= cols || y < 0 || y >= rows)
        return nullptr;

    return roomMap[y][x];
}

Character* Map::getCharacter(int x, int y) const {
    int rows = (int)characterMap.size();
    int cols = (int)characterMap[0].size();

    if (x < 0 || x >= cols || y < 0 || y >= rows)
        return nullptr;

    return characterMap[y][x];
}

Player* Map::getPlayer() const {
    return player;
}

std::pair<int,int> Map::getOtherTunnel(int x, int y) {
    for (auto& pos : tunnelPositions_) {
        if (pos.first != x || pos.second != y) {
            return pos;
        }
    }
    return {x, y}; // fallback
}
