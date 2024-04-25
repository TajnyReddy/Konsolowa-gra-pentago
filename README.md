# Pentago console game
Project PENTAGO is a console implementation of the popular logic game. Players compete against each other, aiming to align five of their tokens in a row, column, or diagonal on a rotating board.
![image](https://github.com/TajnyReddy/Konsolowa-gra-pentago/assets/59600478/c4dd3171-ba8e-4ab0-bc0d-7cf85dc3b84e)

## Features:
### Game Setup:
* Players can enter their names and choose their game piece (zeton).
* The default game board size is 6x6.
### Gameplay:
* Players take turns placing their game piece on the board.
* Players can rotate quadrants of the board clockwise or counterclockwise.
* Players can pause the game and resume it by pressing 'k'.
* Players can undo up to 4 moves.
### Win Condition:
* A player wins if they form a line of 5 of their game pieces horizontally, vertically, or diagonally.
* The game checks for win conditions after each move.
### Draw Condition:
* If all 36 squares are filled and no player has won, the game ends in a draw.
* If both players achieve the win condition simultaneously, the game also ends in a draw.
### Token Swap:
Players can swap their game pieces with each other.
### New Board:
Players can start a new game with a clean board.
### Tic Tac Toe Mode:
* Players can choose to play Tic Tac Toe instead of Pentago.
* In this mode, the game board is 3x3.
### Predefined Boards:
* For both Tic Tac Toe and Pentago modes, players have the option to load predefined boards.
* Predefined boards provide a specific starting configuration for the game.
## Controls:
* Placement: Players input the quadrant ('q', 'w', 'a', 's') and the position (1-9) where they want to place their game piece.
* Rotation: Players input the quadrant ('q', 'w', 'a', 's') and the direction of rotation ('z' for clockwise, 'x' for counterclockwise).
* Pause/Resume: Press 'k' to pause the game and resume it.
* Undo Moves: Players can input the number of moves they want to undo (1-4).
* Token Swap: Token swap is triggered by a specific game event, not directly controlled by the players.
* New Board: There is no direct control for starting a new game, it seems like a feature triggered outside player input, perhaps via a menu or game state.
