#include "GameManager.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Exit.h"
#include "Guard.h"
#include "Camera.h"

GameManager::GameManager(int empAmmo, int flashbangAmmo) : map_(2, 2, 1, 1, empAmmo, flashbangAmmo) {
}

GameManager::~GameManager() {}

void GameManager::gameplayLoop() {
    while (true) {
        // 1) print map
        map_.print();
        
        // 2) display ammo
        displayAmmo();

        // 3) input
        char input = getPlayerInput();
        
        if (input == 'e' || input == 'f') {
            handleWeaponUse(input);
        } else {
            handlePlayerMove(input);
        }

        // 4) activate room
        auto [x, y] = map_.getPlayer()->getPosition();
        Room* room = map_.getRoom(x, y);
        if (room) {
            room->activate(map_);
        }

        // 5) check lose
        if (checkLose()) {
            std::cout << "You were caught by a guard. Game Over.\n";
            break;
        }

        // 6) move guards
        moveGuards();

        // 7) check lose again
        if (checkLose()) {
            std::cout << "A guard caught you. Game Over.\n";
            break;
        }

        // 8) check win
        if (checkWin()) {
            std::cout << "You found the exit! You win!\n";
            break;
        }

        // 9) update turn counters
        updateTurnCounters();

        // 10) surroundings
        checkSurroundings();
    }
}

void GameManager::handlePlayerMove(char input) {
    Player* player = map_.getPlayer();

    auto [x, y] = player->getPosition();

    int newX = x;
    int newY = y;

    switch (input) {
        case 'w': newY--; break;
        case 's': newY++; break;
        case 'a': newX--; break;
        case 'd': newX++; break;
        default: return;
    }

    map_.move(x, y, newX, newY);
}

void GameManager::handleWeaponUse(char input) {
    Player* player = map_.getPlayer();
    
    if (input == 'e') {
        // EMP
        if (player->useWeapon(WeaponType::EMP)) {
            useEMP();
            std::cout << "EMP pulse activated! Cameras in 1-block radius deactivated for 2 turns.\n";
        } else {
            std::cout << "No EMP ammo remaining!\n";
        }
    } else if (input == 'f') {
        // Flashbang
        if (player->useWeapon(WeaponType::FLASHBANG)) {
            useFlashbang();
            std::cout << "Flashbang deployed! Guards stunned for 4 turns.\n";
        } else {
            std::cout << "No flashbang ammo remaining!\n";
        }
    }
}

void GameManager::useEMP() {
    auto [px, py] = map_.getPlayer()->getPosition();
    
    // Check all rooms in 1-block radius
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            int x = px + dx;
            int y = py + dy;
            
            Room* room = map_.getRoom(x, y);
            if (room) {
                Camera* camera = dynamic_cast<Camera*>(room);
                if (camera) {
                    camera->deactivate(2);
                }
            }
        }
    }
}

void GameManager::useFlashbang() {
    auto [px, py] = map_.getPlayer()->getPosition();
    
    // Stun all guards in 1-block radius
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            int x = px + dx;
            int y = py + dy;
            
            Character* character = map_.getCharacter(x, y);
            if (character) {
                Guard* guard = dynamic_cast<Guard*>(character);
                if (guard) {
                    guard->stun(4);
                }
            }
        }
    }
}

void GameManager::updateTurnCounters() {
    // Update all cameras
    for (int y = 0; y < 7; y++) {
        for (int x = 0; x < 7; x++) {
            Room* room = map_.getRoom(x, y);
            if (room) {
                Camera* camera = dynamic_cast<Camera*>(room);
                if (camera) {
                    camera->updateTurn();
                }
            }
        }
    }
    
    // Update all guards
    for (int y = 0; y < 7; y++) {
        for (int x = 0; x < 7; x++) {
            Character* character = map_.getCharacter(x, y);
            if (character) {
                Guard* guard = dynamic_cast<Guard*>(character);
                if (guard) {
                    guard->updateTurn();
                }
            }
        }
    }
}

void GameManager::displayAmmo() {
    Player* player = map_.getPlayer();
    std::cout << "Ammo - EMP: " << player->getEmpAmmo() 
              << ", Flashbang: " << player->getFlashbangAmmo() << "\n";
}

bool GameManager::checkWin() {
    auto [x, y] = map_.getPlayer()->getPosition();
    Room* room = map_.getRoom(x, y);

    return dynamic_cast<Exit*>(room) != nullptr;
}

bool GameManager::checkLose() {
    auto [px, py] = map_.getPlayer()->getPosition();

    int rows = 7;
    int cols = 7;

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            Character* c = map_.getCharacter(x, y);

            Guard* g = dynamic_cast<Guard*>(c);
            if (g) {
                auto [gx, gy] = g->getPosition();
                if (gx == px && gy == py) {
                    return true;
                }
            }
        }
    }

    return false;
}

void GameManager::checkSurroundings() {
    auto [x, y] = map_.getPlayer()->getPosition();

    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        Character* c = map_.getCharacter(nx, ny);
        if (c) c->printPhrase();

        Room* room = map_.getRoom(nx, ny);
        if (room) room->printPhrase();
    }
}

void GameManager::moveGuards() {
    auto [px, py] = map_.getPlayer()->getPosition();

    int rows = 7;
    int cols = 7;

    std::vector<Guard*> guards;

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < cols; x++) {
            Guard* g = dynamic_cast<Guard*>(map_.getCharacter(x, y));
            if (g) {
                guards.push_back(g);
            }
        }
    }

    for (Guard* guard : guards) {
        // Skip stunned guards
        if (guard->isStunned()) {
            continue;
        }
        
        auto [gx, gy] = guard->getPosition();

        int newX = gx;
        int newY = gy;

        int targetX = px;
        int targetY = py;

        if (map_.isAlertActive()) {
            auto alert = map_.getAlertPosition();
            targetX = alert.first;
            targetY = alert.second;
        }

        int dx = targetX - gx;
        int dy = targetY - gy;

        if (abs(dx) + abs(dy) <= 3) {
            if (abs(dx) > abs(dy))
                newX += (dx > 0 ? 1 : -1);
            else
                newY += (dy > 0 ? 1 : -1);
        } else {
            int dir = rand() % 4;
            if (dir == 0) newY--;
            if (dir == 1) newY++;
            if (dir == 2) newX--;
            if (dir == 3) newX++;
        }

        if (newX < 0 || newX >= cols || newY < 0 || newY >= rows)
            continue;

        Character* target = map_.getCharacter(newX, newY);

        if (target == nullptr || target == map_.getPlayer()) {
            map_.move(gx, gy, newX, newY);
        }
    }

    map_.clearAlert();
}

char GameManager::getPlayerInput() {
    char input;
    std::cout << "Move (WASD) or use weapon (E=EMP, F=Flashbang): ";
    std::cin >> input;
    return tolower(input);
}
