#pragma once
#include "board.h"

class game {
public:
	Board* myBoard;
	bool turn; // Turn of players (Player 1: false(0) / Player 2: true(1))
	int cX, cY; // Current position of cursor
	int command; // input-key from players
	bool loopGame; // exit game or not
	int scoreX, scoreO, scoreDraw;
	bool botMode;

	// Constructor - Destructor
	game(int, int, int);
	~game();

	// Filter
	int getCommand();
	bool isContinue();
	void botMove();
	char waitKeyboard(); // Receive key-input from players
	char askContinue();
	void startGame();
	void loadGame(string);
	void askSaveGame();
	void saveGame();
	void exitGame();
	int processFinishGame(); // Processing WIN - DRAW, exit game or continue a new game
	bool processCheckBoard(); // Processing fill detail of cell
	void moveRight();
	void moveLeft();
	void moveDown();
	void moveUp();
	void updatePI();
};