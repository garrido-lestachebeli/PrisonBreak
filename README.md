# Wumpus Hunt - Build and Usage Guide

## Build System

This project uses **Make** as its build system with a Makefile located in the `src/` directory.

### Compiler Version
- **g++ version**: 15.2.0 (x86_64-posix-seh-rev1, Built by MinGW-Builds project)
- **Standard**: C++17
- **Build flags**: `-Wall -g` (enables all warnings and includes debug information)

## Build Instructions

### Prerequisites
- g++ compiler (version 15.2.0 or compatible)
- Make utility
- Windows environment (MinGW/MSYS2 recommended)

### Build Steps

1. **Navigate to the source directory:**
   ```bash
   cd src
   ```

2. **Build the executable:**
   ```bash
   make
   ```
   This compiles all source files and creates the executable named `game.exe` (on Windows) or `game` (on Linux/Unix).

3. **Alternative: Build and run in one step:**
   ```bash
   make run
   ```

4. **Clean build artifacts:**
   ```bash
   make clean
   ```

### Executable Location
After building, the executable will be located at:
- **Windows**: `src/game.exe`
- **Linux/Unix**: `src/game`

## Game Controls and Features

### Basic Controls
- **Movement**: WASD keys (W=up, S=down, A=left, D=right)
- **Weapons**: 
  - E = Use EMP (deactivates cameras in 1-block radius for 2 turns)
  - F = Use Flashbang (stuns guards in 1-block radius for 4 turns)
- **Quit**: Q key
- **Debug Mode**: M key (toggle debug mode on/off)

### Debug Mode
To enter debug mode:
1. Start the game
2. Press the **M key** during gameplay
3. Debug mode will be toggled on/off (confirmation message will appear)

### Game Objective
- Navigate through the map to find the **Exit** room to win
- Avoid being caught by **Guards** (causes game over)
- Use weapons strategically to avoid detection and capture

## Source Files Structure
  Implemented by German:
- `main.cpp` - Entry point
- `GameManager.cpp` - Main game loop and logic
- `Map.cpp` - Map generation and management
- `Player.cpp` - Player character and weapons
- `Guard.cpp` - Enemy AI and movement
  Implemented by Fintan:
- `Exit.cpp` - Win condition room
- `Camera.cpp` - Detection system
- `Tunnel.cpp` - Transportation system
- `EmptyRoom.cpp` - Basic room type

## Troubleshooting

### Common Issues
1. **Make command not found**: Install Make utility (MinGW/MSYS2 on Windows)
2. **g++ not found**: Install g++ compiler with C++17 support
3. **Permission denied**: Ensure write permissions in the src directory
4. **Build fails**: Check that all source files are present in the src directory

### Debug Build
The Makefile includes the `-g` flag, producing debug information. Use a debugger like GDB to debug issues:
```bash
gdb ./game
```
