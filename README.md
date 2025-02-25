<h1 align="center">Cascade-Match</h1>



This project implements a single-player game where the player manipulates a 2D matrix of shapes to create matching groups. The game features a simple yet engaging gameplay mechanic of swapping adjacent elements to create matches of three or more same-shape elements.

## Table of Contents
- [Game Description](#game-description)
- [Implementation Details](#implementation-details)
- [How to Play](#how-to-play)
- [Input Validation](#input-validation)
- [Error Handling](#error-handling)
- [Acknowledgements](#acknowledgements)

## Game Description

In this game, the player is presented with a matrix containing different shape characters ('X', 'O', and 'S'). The objective is to create matches by swapping adjacent elements. When a match of three or more identical shapes is formed (either horizontally or vertically), those shapes are removed from the matrix, and the remaining elements fall down due to gravity.

### Game Mechanics:
1. The game board is a 2D matrix read from a text file
2. Valid shapes are 'X', 'O', and 'S'
3. Players swap adjacent elements by specifying:
   - Row index (starting from 0)
   - Column index (starting from 0)
   - Direction ('r' for right, 'l' for left, 'u' for up, 'd' for down)
4. A valid swap must result in a match of three or more identical shapes
5. After matches are cleared, gravity is applied, causing elements to fall down
6. This may trigger chain reactions with new matches being automatically cleared

## Implementation Details

The game is implemented in C++ using:
- 2D vectors for the game board (vector of vector of char)
- File I/O operations for reading the initial game state
- User input validation and error handling
- Match detection in both horizontal and vertical directions
- Gravity simulation to fill empty spaces

### Key Components:
- **Matrix Reading and Validation**: Ensures the input file has a valid matrix with consistent dimensions and only allowed characters.
- **Move Validation**: Checks if the player's move is valid (within bounds, not involving empty cells, and resulting in a match).
- **Match Detection**: Identifies and clears horizontal matches first, then vertical matches.
- **Gravity Application**: Makes elements fall down to fill empty spaces after matches are cleared.
- **Continuous Matching**: Automatically detects and clears new matches formed after gravity is applied.

## How to Play

1. Run the program
2. Enter the filename containing the initial matrix
3. The game will display the current state of the matrix
4. Enter moves in the format: `row column direction`
   - Example: `2 3 r` (swaps the element at row 2, column 3 with the element to its right)
5. Valid directions are:
   - 'r' (right)
   - 'l' (left)
   - 'u' (up)
   - 'd' (down)
6. To exit the game, enter `0 0 q`

### Installation
1. Ensure you have a C++ compiler (e.g., `g++`).
2. Clone the repository: `git clone <repo-url>`
3. Compile the code: `g++ -o cascade_match main.cpp`
4. Run the game: `./cascade_match`

## Input Validation

The program performs extensive validation on both file input and user commands:
- **File Validation**:
  - Checks if the file can be opened
  - Ensures all rows have the same length
  - Verifies that only valid characters ('X', 'O', 'S') are present
- **Move Validation**:
  - Validates that coordinates are within the matrix boundaries
  - Ensures the direction is valid
  - Checks that the swap doesn't involve empty cells
  - Verifies that the swap results in a valid match

## Error Handling

The program provides clear error messages for various scenarios:
- File couldn't be opened
- Invalid matrix dimensions or characters
- Invalid coordinates (negative or out of bounds)
- Invalid direction
- Moves that don't result in matches
- Attempts to swap with empty cells

## Future Enhancements
- Add a scoring system based on match size and chains.
- Create a graphical interface with SFML or SDL.
- Introduce new shapes or power-ups (e.g., wildcards).

## Acknowledgements

This project was developed as part of the CS204 Advanced Programming course at Sabancı University. The implementation follows the requirements specified in the homework assignment.

