#pragma once
#pragma once
#include "lib.h"

class Menu {
	int cX, cY;
	int command;
	vector<string> detail;

public:
	Menu();
	void drawBorder();
	void menuScreen();
	void newGameScreen();
	void loadGameScreen();
	void guideScreen(); // How to play
	void aboutScreen();
	void gamePlayScreen(bool, bool, string); // 0-newgame 1-loadgame 
	void quit();
};