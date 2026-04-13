#include "GameManager.h"

#include <cstdlib>
#include <iostream>
#include <limits>

#include "Exit.h"
#include "Guard.h"
#include "Camera.h"

/************************************************************
 * GameManager Constructor
 * ----------------------------------------------------------
 * Initializes the game manager with specified ammo amounts
 * and creates the game map with default configuration.
 ************************************************************/
GameManager::GameManager(int empAmmo, int flashbangAmmo) : map_(2, 2, 1, 1, empAmmo, flashbangAmmo), debugMode_(false) {
}

/************************************************************
 * GameManager Destructor
 * ----------------------------------------------------------
 * Cleans up game manager resources.
 ************************************************************/
GameManager::~GameManager() {}

/************************************************************
 * GameManager::gameplayLoop
 * ----------------------------------------------------------
 * Main game loop that handles player input, game state updates,
 * and win/lose conditions.
 ************************************************************/
void GameManager::gameplayLoop() {
    while (true) {
        map_.print();
        
        if (debugMode_) {
            printRoomMap();
        }
        
        checkSurroundings();
        displayAmmo();

        char input = getPlayerInput();

        if (input == 'q') {
            std::cout<<"Quitting game...\n";
            break;
        }
        
        if (input == 'm') {
            debugMode_ = !debugMode_;
            std::cout << "Debug mode " << (debugMode_ ? "enabled" : "disabled") << "\n";
            continue;
        }
        
        if (input == 'e' || input == 'f') {
            handleWeaponUse(input);
        } else {
            handlePlayerMove(input);
        }

        auto [x, y] = map_.getPlayer()->getPosition();
        Room* room = map_.getRoom(x, y);
        if (room) {
            room->activate(map_);
        }

        if (checkLose()) {
            std::cout << "*         GAME OVER *\n";
            std::cout << "*    You were caught by a guard! *\n";

            std::cout << "\nPress any key to exit...\n";
            std::cin.ignore();
            std::cin.get();
            break;
        }

        moveGuards();
        if (checkLose()) {
            std::cout << "*         GAME OVER *\n";
            std::cout << "*    A guard caught you! *\n";

            std::cout << "\nPress any key to exit...\n";
            std::cin.ignore();
            std::cin.get();
            break;
        }
        if (checkWin()) {
            std::cout << "*         VICTORY *\n";
            std::cout << "*    You found the exit! *\n";

            std::cout << "\nPress any key to exit...\n";
            std::cin.ignore();
            std::cin.get();
            break;
        }
        updateTurnCounters();
    }
}

/************************************************************
 * GameManager::handlePlayerMove
 * ----------------------------------------------------------
 * Processes player movement input and updates player position.
 ************************************************************/
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

/************************************************************
 * GameManager::handleWeaponUse
 * ----------------------------------------------------------
 * Processes weapon usage input and applies weapon effects.
 ************************************************************/
void GameManager::handleWeaponUse(char input) {
    Player* player = map_.getPlayer();
    
    if (input == 'e') {
        if (player->useWeapon(WeaponType::EMP)) {
            useEMP();
            std::cout << "EMP pulse activated! Cameras in 1-block radius deactivated for 2 turns.\n";
        } else {
            std::cout << "No EMP ammo remaining!\n";
        }
    } else if (input == 'f') {
        if (player->useWeapon(WeaponType::FLASHBANG)) {
            useFlashbang();
            std::cout << "Flashbang deployed! Guards stunned for 4 turns.\n";
        } else {
            std::cout << "No flashbang ammo remaining!\n";
        }
    }
}

/************************************************************
 * GameManager::useEMP
 * ----------------------------------------------------------
 * Applies EMP weapon effect to deactivate cameras in
 * 1-block radius around the player.
 ************************************************************/
void GameManager::useEMP() {
    auto [px, py] = map_.getPlayer()->getPosition();
    
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            int x = px + dx;
            int y = py + dy;
            
            Room* room = map_.getRoom(x, y);
            if (room) {
                Camera* camera = dynamic_cast<Camera*>(room);
                if (camera) {
                    camera->deactivate(4);
                }
            }
        }
    }
}

/************************************************************
 * GameManager::useFlashbang
 * ----------------------------------------------------------
 * Applies flashbang weapon effect to stun guards in
 * 1-block radius around the player.
 ************************************************************/
void GameManager::useFlashbang() {
    auto [px, py] = map_.getPlayer()->getPosition();
    
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

/************************************************************
 * GameManager::updateTurnCounters
 * ----------------------------------------------------------
 * Updates turn-based counters for cameras and guards
 * to handle deactivation and stun durations.
 ************************************************************/
void GameManager::updateTurnCounters() {
    // Update camera deactivation counters
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
    
    // Update guard stun counters
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

/************************************************************
 * GameManager::displayAmmo
 * ----------------------------------------------------------
 * Displays current ammo counts for EMP and flashbang weapons.
 ************************************************************/
void GameManager::displayAmmo() {
    Player* player = map_.getPlayer();
    std::cout << "Ammo - EMP: " << player->getEmpAmmo() 
              << ", Flashbang: " << player->getFlashbangAmmo() << "\n";
}

/************************************************************
 * GameManager::printRoomMap
 * ----------------------------------------------------------
 * Displays debug room map showing room types instead of
 * character positions for debugging purposes.
 ************************************************************/
void GameManager::printRoomMap() {
    std::cout << "\n=== ROOM MAP (DEBUG) ===\n";
    for (int y = 0; y < 7; y++) {
        for (int x = 0; x < 7; x++) {
            Room* room = map_.getRoom(x, y);
            if (room) {
                room->print();
            } else {
                std::cout << "?";
            }
            std::cout << " ";
        }
        std::cout << "\n";
    }
    std::cout << "========================\n\n";
}

/************************************************************
 * GameManager::checkWin
 * ----------------------------------------------------------
 * Checks if player has reached the exit room to win the game.
 ************************************************************/
bool GameManager::checkWin() {
    auto [x, y] = map_.getPlayer()->getPosition();
    Room* room = map_.getRoom(x, y);

    return dynamic_cast<Exit*>(room) != nullptr;
}

/************************************************************
 * GameManager::checkLose
 * ----------------------------------------------------------
 * Checks if player has been caught by a guard to lose the game.
 ************************************************************/
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

/************************************************************
 * GameManager::checkSurroundings
 * ----------------------------------------------------------
 * Checks adjacent cells for characters and rooms to provide
 * player with environmental feedback.
 ************************************************************/
void GameManager::checkSurroundings() {
    auto [x, y] = map_.getPlayer()->getPosition();

    // Check all four adjacent directions
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

/************************************************************
 * GameManager::moveGuards
 * ----------------------------------------------------------
 * Moves all guards toward the player or alert position,
 * respecting stun status and movement rules.
 ************************************************************/
void GameManager::moveGuards() {
    auto [px, py] = map_.getPlayer()->getPosition();

    int rows = 7;
    int cols = 7;

    std::vector<Guard*> guards;

    // Collect all guards on the map
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

/************************************************************
 * GameManager::getPlayerInput
 * ----------------------------------------------------------
 * Gets and processes player input, clearing the input buffer
 * to prevent multiple character processing.
 ************************************************************/
char GameManager::getPlayerInput() {
    char input;
    std::cout << "Move (WASD) or use weapon (E=EMP, F=Flashbang, Q=Quit): ";
    std::cin >> input;
    
    // Clear any additional characters from input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    return tolower(input);
}
