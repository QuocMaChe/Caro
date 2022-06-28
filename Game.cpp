#include "game.h"
#include "common.h"
#include "lib.h"
#include <time.h>
//
// Constructor
//
game::game(int size, int top, int left) {
	myBoard = new Board(size, top, left);
	loopGame = 1;
	turn = 1; // Player 1 play first in default
	command = -1; // key-input is nothing now 
	cX = myBoard->getXat(0, 0);
	cY = myBoard->getYat(0, 0);
	scoreX = scoreO = 0;
	botMode = 0;
}
//
// Destructor
//
game::~game() {
	if (myBoard != NULL) {
		delete myBoard;
		myBoard = NULL;
	}
}
//
// Filter
//
// Getter key-input
int game::getCommand() { return command; }

// Getter loopGame 
bool game::isContinue() { return loopGame; }

// Random move of Bot
void game::botMove() {
	int tmp = rand() % 6;
	if (tmp == 0) command = 'W';
	if (tmp == 1) command = 'A';
	if (tmp == 2) command = 'S';
	if (tmp == 3) command = 'D';
	if (tmp >= 4) command = KEY_ENTER;
}

// Wait and receive key-input from players, then return key-input in char
char game::waitKeyboard() {
	command = toupper(_getch());
	return command;
}

// Wait and receive key-input from players in order to decide 
// continue game or not when it finish
char game::askContinue() {
	Common::fixFontColor(3);
	Common::gotoXY(myBoard->getXat(0, myBoard->getSize() - 1) + 10, 16);
	cout << "PRESS Y TO PLAY A NEW GAME...";
	return waitKeyboard();
}

// Start-game function
void game::startGame() {
	system("cls");
	srand(time_t(NULL));
	myBoard->resetData();
	myBoard->drawBoard();
	turn = 0;
	loopGame = 1;
	command = -1;
	cX = myBoard->getXat(0, 0);
	cY = myBoard->getYat(0, 0);

	// Show number of game have played/ how many win - draw ...
	int size = myBoard->getSize();
	Common::gotoXY(myBoard->getXat(0, size - 1) + 10, myBoard->getYat(0, size - 1) - 1);
	Common::fixFontColor(7);
	cout << "Total:";

	Common::gotoXY(myBoard->getXat(0, size - 1) + 30, myBoard->getYat(0, size - 1) - 1);
	cout << "Draw:";

	Common::gotoXY(myBoard->getXat(0, size - 1) + 10, myBoard->getYat(0, size - 1));
	Common::fixFontColor(4);
	cout << "X";
	Common::fixFontColor(7);
	cout << " score: ";

	Common::gotoXY(myBoard->getXat(0, size - 1) + 30, myBoard->getYat(0, size - 1));
	Common::fixFontColor(2);
	cout << "O";
	Common::fixFontColor(7);
	cout << " score: ";
	updatePI();
}

// Load game
void game::loadGame(string fileName) {
	system("cls");
	myBoard->resetData();

	fstream F;
	F.open("Saved game\\" + fileName + ".txt", ios::in);

	F >> myBoard->p1_moved >> myBoard->p2_moved >> turn >> cX >> cY >> botMode >> scoreX >> scoreO >> scoreDraw;
	for (int i = 0; i <= myBoard->getSize() - 1; i++)
		for (int j = 0; j <= myBoard->getSize() - 1; j++) {
			int tmp;
			F >> tmp;
			myBoard->pArr[i][j].setCheck(tmp);
		}

	F.close();
	myBoard->drawBoard();
	myBoard->updatePS();
	myBoard->showTurn(turn);
	updatePI();
	Common::gotoXY(cX, cY);
}

// Ask to save game
void game::askSaveGame() {
	Common::fixFontColor(7);
	Common::gotoXY(myBoard->getXat(0, myBoard->getSize() - 1) + 10, 15);
	cout << "Do you want to save this game";
	Common::gotoXY(myBoard->getXat(0, myBoard->getSize() - 1) + 10, 16);
	cout << "before leaving ? ";

	Common::gotoXY(myBoard->getXat(0, myBoard->getSize() - 1) + 10, 17);
	Common::fixFontColor(3); cout << "PRESS ";
	Common::fixFontColor(4);  cout << "L";
	Common::fixFontColor(3); cout << " TO SAVE GAME...";

	if (waitKeyboard() == 'L') saveGame();
}

// Save game
void game::saveGame() {
	Common::gotoXY(myBoard->getXat(0, myBoard->getSize() - 1) + 10, 17);
	Common::fixFontColor(7);
	cout << "Please enter file-name:          ";
	Common::gotoXY(myBoard->getXat(0, myBoard->getSize() - 1) + 10, 18);
	string fileName;
	getline(cin, fileName);

	fstream F;
	F.open("Saved game\\" + fileName + ".txt", ios::out);

	F << myBoard->p1_moved << ' ' << myBoard->p2_moved << ' ' << turn << ' ' << cX << ' ' << cY << ' '
		<< botMode << ' ' << scoreX << ' ' << scoreO << ' ' << scoreDraw << endl;
	for (int i = 0; i <= myBoard->getSize() - 1; i++)
		for (int j = 0; j <= myBoard->getSize() - 1; j++)
			F << myBoard->getDetail(i, j) << ' ';

	F.close();

	F.open("Saved game\\database.txt", ios::app);
	F << fileName << '\n';
	F.close();
	Common::gotoXY(myBoard->getXat(0, myBoard->getSize() - 1) + 10, 20);
	cout << "SAVING...";
	Sleep(1000);
}

// Exit-game function
void game::exitGame() {
	system("cls");
	// Save-game function (*)
	loopGame = 0;
}

// Processing WIN-DRAW, exit game or continue a new game
int game::processFinishGame() {
	// Move to the resonable place to show noftication about WIN/LOSE/DRAW if it finish
	Common::gotoXY(myBoard->getXat(0, myBoard->getSize() - 1) + 10, 14);
	pii tmp = myBoard->cv_to_matrix_coord(cX, cY);
	int pWin = myBoard->testBoard(tmp.first, tmp.second, myBoard->getDetail(tmp.first, tmp.second));
	switch (pWin) {
	case 1: // WIN GAME 
		system("Color 01"); Sleep(100);
		system("Color 02"); Sleep(100);
		system("Color 03"); Sleep(100);
		system("Color 04"); Sleep(100);
		system("Color 05"); Sleep(100);
		system("Color 06"); Sleep(100);
		system("Color 08"); Sleep(100);
		system("Color 09"); Sleep(100);
		system("Color 11"); Sleep(100);
		system("Color 07"); Sleep(100);
		if (!turn) {

			Common::fixFontColor(2);
			cout << "PLAYER 1: ";
			cout << "WIN!";
			Common::gotoXY(myBoard->getXat(0, myBoard->getSize() - 1) + 10, 15);
			Common::fixFontColor(4);
			cout << "PLAYER 2: ";
			cout << "LOSE!";
			Common::gotoXY(myBoard->getXat(0, myBoard->getSize() - 1) + 10, 16);
			scoreX++;
		}
		else {
			Common::fixFontColor(4);
			cout << "PLAYER 1: ";
			cout << "LOSE!";
			Common::gotoXY(myBoard->getXat(0, myBoard->getSize() - 1) + 10, 15);
			Common::fixFontColor(2);
			cout << "PLAYER 2: ";
			cout << "WIN!";
			Common::gotoXY(myBoard->getXat(0, myBoard->getSize() - 1) + 10, 16);
			scoreO++;
		}
		break;
	case -1: // DRAW GAME
		system("Color 07");
		Common::fixFontColor(7);
		cout << "PLAYER 1 ";
		Common::fixFontColor(3);
		cout << "DRAW";
		Common::fixFontColor(7);
		cout << " WITH PLAYER 2!";
		Common::gotoXY(myBoard->getXat(0, myBoard->getSize() - 1) + 10, 15);
		scoreDraw++;
		break;
	case 0: // CONTINUE 
		turn = !turn;
		break;
	}

	Common::gotoXY(cX, cY); // Return to current cursor position after processing
	return pWin;
}

// Processing fill detail of cell
bool game::processCheckBoard() {
	switch (myBoard->checkBoard(cX, cY, turn)) {
	case -1:
		Common::fixFontColor(4);
		cout << "X";
		myBoard->updatePS();
		myBoard->showTurn(1);
		Common::gotoXY(cX, cY);
		break;
	case 1:
		Common::fixFontColor(2);
		cout << "O";
		myBoard->updatePS();
		myBoard->showTurn(0);
		Common::gotoXY(cX, cY);
		break;
	case 0: return 0; // Already marked
	}
	return 1;
}

// Move right
void game::moveRight() {
	if (cX < myBoard->getXat(myBoard->getSize() - 1, myBoard->getSize() - 1)) {
		cX += 4;
		Common::gotoXY(cX, cY);
	}
	return;
}

// Move left
void game::moveLeft() {
	if (cX > myBoard->getXat(0, 0)) {
		cX -= 4;
		Common::gotoXY(cX, cY);
	}
	return;
}

// Move down
void game::moveDown() {
	if (cY < myBoard->getYat(myBoard->getSize() - 1, myBoard->getSize() - 1)) {
		cY += 2;
		Common::gotoXY(cX, cY);
	}
	return;
}

// Move up
void game::moveUp() {
	if (cY > myBoard->getYat(0, 0)) {
		cY -= 2;
		Common::gotoXY(cX, cY);
	}
	return;
}

// Update playing interface
void game::updatePI() {
	int size = myBoard->getSize();
	Common::fixFontColor(3);
	Common::gotoXY(myBoard->getXat(0, size - 1) + 20, myBoard->getYat(0, size - 1) - 1);
	cout << scoreX + scoreO + scoreDraw + 1;

	Common::gotoXY(myBoard->getXat(0, size - 1) + 40, myBoard->getYat(0, size - 1) - 1);
	cout << scoreDraw;

	Common::gotoXY(myBoard->getXat(0, size - 1) + 20, myBoard->getYat(0, size - 1));
	cout << scoreX;
	Common::gotoXY(myBoard->getXat(0, size - 1) + 40, myBoard->getYat(0, size - 1));
	cout << scoreO;

	Common::gotoXY(cX, cY);
}