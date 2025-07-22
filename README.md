# Simple Console Tetris in C++

This is a minimal, console-based implementation of the classic Tetris game, written entirely in C++ without external dependencies. It runs directly in your terminal and uses standard keyboard inputs.

## Features

- Simple ASCII-based graphics
- Basic gameplay mechanics: movement, rotation, and line clearing
- Uses `*` symbols to indicate left and right boundaries
- Runs smoothly on macOS terminal

## Controls

- **←**: Move left  
- **→**: Move right  
- **↑**: Rotate piece  
- **↓**: Soft drop  
- **q**: Quit game

## Project Structure

- `main.cpp`: Entry point of the game. Manages the game loop, timing, input handling, and game logic coordination.
- `tetris.h`, `tetris.cpp`: Contains the core game logic, including collision detection, line clearing, piece locking, and rotation.
- `renderer.h`, `renderer.cpp`: Handles rendering the game state to the terminal screen using simple ASCII graphics.
- `terminal.h`, `terminal.cpp`: Manages terminal input/output behavior, enabling raw mode for real-time keyboard input without the need to press Enter.


## Compilation and Execution

Ensure you're using a POSIX-compatible system (tested on macOS with clang):

```bash
clang++ main.cpp terminal.cpp tetris.cpp renderer.cpp -std=c++11 -o tetris
./tetris
``` 
## Requirements

- POSIX-compatible terminal (macOS/Linux)
- C++ compiler (tested with clang 17.0.0 on macOS)
