#include "lib.h"
#include "board.h"
#include "common.h"
//
// Constructor
//
Board::Board(int _size, int _top, int _left) {
	p1_moved = p2_moved = 0;
	size = _size;
	top = _top;
	left = _left;
	pArr = new Point * [size];
	checkArrived = new bool* [size];
	fu(i, 0, size - 1) {
		pArr[i] = new Point[size];
		checkArrived[i] = new bool[size];
	}
	fu(i, 0, size - 1)
		fu(j, 0, size - 1) checkArrived[i][j] = 0;

}
//
// Destructor
//
Board::~Board() {
	fu(i, 0, size - 1) {
		delete[] pArr[i], checkArrived[i];
		pArr[i] = NULL;
		checkArrived[i] = NULL;
	}
	delete pArr, checkArrived;
	pArr = NULL;
	checkArrived = NULL;
	p1_moved = 0;
	p2_moved = 0;
}
//
// Getter
//
int Board::getSize() { return size; }
int Board::getTop() { return top; }
int Board::getLeft() { return left; }
int Board::getXat(int i, int j) { return pArr[i][j].getX(); }
int Board::getYat(int i, int j) { return pArr[i][j].getY(); }
int Board::getDetail(int i, int j) { return pArr[i][j].getCheck(); }
// 
// Filter
//
// Reset data of Board
void Board::resetData() {
	if (size == 0) return; // Dont exist
	fu(i, 0, size - 1)
		fu(j, 0, size - 1) {
		pArr[i][j].setX(4 * j + left + 2); // Set X-value of cell (i,j), stored in pArr[i][j]
		pArr[i][j].setY(2 * i + top + 1); // Set Y-value of cell (i,j), stored in pArr[i][j]
		pArr[i][j].setCheck(0); // Set detail of cell to empty (0)
		p1_moved = p2_moved = 0; // Player moved
		checkArrived[i][j] = 0;
	}
}

// Draw Board
void Board::drawBoard() {
	if (pArr == NULL) return; // Dont exist
	Common::fixFontColor(7);
	fu(i, 0, size)
		fu(j, 0, size) {
		Common::gotoXY(left + 4 * i, top + 2 * j);
		cout << ".";
	}
	fu(i, 0, size - 1)
		fu(j, 0, size - 2) {
		Common::gotoXY(pArr[i][j].getX(), pArr[i][j].getY());
		if (pArr[i][j].getCheck() == -1) {
			Common::fixFontColor(4);
			cout <<"X";
		}
		if (pArr[i][j].getCheck() == 1) {
			Common::fixFontColor(8);
			cout <<"O";
		}
	}

	Common::fixFontColor(7);
	for (int i = 0; i <= size * 2; i++) {
		Common::gotoXY(getXat(0, size - 1) + 5, getYat(0, size - 1) - 1 + i);
		cout << "|||";
	}
	for (int i = 0; i <= size * 2; i++) {
		Common::gotoXY(getXat(0, size - 1) + 5, getYat(0, size - 1) - 1 + i);
		cout << " ||";
	}
    for (int i = 0; i <= size * 4 + 43; i++) {
		Common::gotoXY(i+1, size * 2 + 1);
		cout << "=";
	}

	for (int i = 0; i <= size * 2; i++) {
		Common::gotoXY(size * 4 + 42, i);
		cout << " ||";
	}

	playerStat();
	Common::gotoXY(pArr[0][0].getX(), pArr[0][0].getY()); // Move to first cell of the Board
}

// Fill detail of cell (X or O or nothing), base on turn of players
int Board::checkBoard(int pX, int pY, bool playerTurn) {
	pii tmp = cv_to_matrix_coord(pX, pY);
	int i, j;
	i = tmp.first;
	j = tmp.second;
	if (pArr[i][j].getX() == pX && pArr[i][j].getY() == pY && pArr[i][j].getCheck() == 0) {
		if (!playerTurn) {
			p1_moved++;
			pArr[i][j].setCheck(-1);
		}
		else {
			pArr[i][j].setCheck(1);
			p2_moved++;
		}
		return pArr[i][j].getCheck();
	}
	return 0;
}

// Check Win - Draw
int Board::testBoard(int X, int Y, int symbol) {
	int tmp = max(testVertical(X, Y, symbol), testHorizontal(X, Y, symbol)); // test 5 consecutive symbol(X/O)-(-1/1) follow 4 ways
	tmp = max(tmp, max(testCross_1(X, Y, symbol), testCross_2(X, Y, symbol))); //  Horizontal, Vertical, Cross 1&2
	if (tmp >= 5) return 1; // WIN GAME
	if (p1_moved + p2_moved == size * size) return -1; // DRAW GAME
	return 0; // CONTINUE GAME
}

// Vertical
int Board::testVertical(int X, int Y, int symbol) {
	if (checkArrived[X][Y]) return 0;
	checkArrived[X][Y] = 1;
	int res = 1;
	if (X - 1 >= 0)
		if (pArr[X - 1][Y].getCheck() == symbol) res += Board::testVertical(X - 1, Y, symbol);
	if (X + 1 < size)
		if (pArr[X + 1][Y].getCheck() == symbol) res += Board::testVertical(X + 1, Y, symbol);
	checkArrived[X][Y] = 0;
	return res;
}

// Horizontal
int Board::testHorizontal(int X, int Y, int symbol) {
	if (checkArrived[X][Y]) return 0;
	checkArrived[X][Y] = 1;
	int res = 1;
	if (Y - 1 >= 0)
		if (pArr[X][Y - 1].getCheck() == symbol) res += Board::testHorizontal(X, Y - 1, symbol);
	if (Y + 1 < size)
		if (pArr[X][Y + 1].getCheck() == symbol) res += Board::testHorizontal(X, Y + 1, symbol);
	checkArrived[X][Y] = 0;
	return res;
}

// Cross 1
int Board::testCross_1(int X, int Y, int symbol) {
	if (checkArrived[X][Y]) return 0;
	checkArrived[X][Y] = 1;
	int res = 1;
	if ((X - 1 >= 0) && (Y - 1 >= 0))
		if (pArr[X - 1][Y - 1].getCheck() == symbol) res += Board::testCross_1(X - 1, Y - 1, symbol);
	if ((X + 1 < size) && (Y + 1 < size))
		if (pArr[X + 1][Y + 1].getCheck() == symbol) res += Board::testCross_1(X + 1, Y + 1, symbol);
	checkArrived[X][Y] = 0;
	return res;
}

// Cross 2
int Board::testCross_2(int X, int Y, int symbol) {
	if (checkArrived[X][Y]) return 0;
	checkArrived[X][Y] = 1;
	int res = 1;
	if ((X - 1 >= 0) && (Y + 1 >= 0))
		if (pArr[X - 1][Y + 1].getCheck() == symbol) res += Board::testCross_2(X - 1, Y + 1, symbol);
	if ((X + 1 < size) && (Y - 1 < size))
		if (pArr[X + 1][Y - 1].getCheck() == symbol) res += Board::testCross_2(X + 1, Y - 1, symbol);
	checkArrived[X][Y] = 0;
	return res;
}

// Converse coord-in-console-window of caro-cell to coord-in-matrix of caro-cell
pii Board::cv_to_matrix_coord(int pX, int pY) {
	pii tmp;
	tmp.first = (pY - 1 - top) / 2;
	tmp.second = (pX - 2 - left) / 4;
	return tmp;
}

// Playing inteface
void Board::playerStat() {
	Common::gotoXY(getXat(0, size - 1) + 10, getYat(0, size - 1) + 3);
	Common::fixFontColor(4);
	cout << "X";
	Common::fixFontColor(7);
	cout << " MOVED:";

	Common::gotoXY(getXat(0, size - 1) + 30, getYat(0, size - 1) + 3);
	Common::fixFontColor(2);
	cout << "O";
	Common::fixFontColor(7);
	cout << " MOVED: ";

	updatePS();

	Common::gotoXY(getXat(0, size - 1) + 18, getYat(0, size - 1) + 5);
	Common::fixFontColor(7);
	cout << "*****TURN*****";

	showTurn(0);

	Common::fixFontColor(4);

	// Show number of game have played/ how many win - draw ...
	// int size = myBoard->getSize();
	Common::gotoXY(getXat(0, size - 1) + 10, getYat(0, size - 1) - 1);
	Common::fixFontColor(7);
	cout << "TOTAL:";

	Common::gotoXY(getXat(0, size - 1) + 30, getYat(0, size - 1) - 1);
	cout << "DRAW:";

	Common::gotoXY(getXat(0, size - 1) + 10, getYat(0, size - 1));
	Common::fixFontColor(4);
	cout << "X";
	Common::fixFontColor(4);
	cout << " SCORE: ";

	Common::gotoXY(getXat(0, size - 1) + 30, getYat(0, size - 1));
	Common::fixFontColor(8);
	cout << "O";
	Common::fixFontColor(7);
	cout << " SCORE: ";
}

// Update playing interface
void Board::updatePS() {
	Common::fixFontColor(3);
	Common::gotoXY(getXat(0, size - 1) + 20, getYat(0, size - 1) + 3);
	cout << p1_moved;
	Common::gotoXY(getXat(0, size - 1) + 40, getYat(0, size - 1) + 3);
	cout << p2_moved;
}

// Show turn of player
void Board::showTurn(bool pTurn) {
	if (pTurn == 1) {
		Common::fixFontColor(2);
		Common::gotoXY(getXat(0, size - 1) + 7, getYat(0, size - 1) + 6);
		cout << "\t\t"; cout << "    OOOOOO     ";
		Common::gotoXY(getXat(0, size - 1) + 7, getYat(0, size - 1) + 7);
		cout << "\t\t"; cout << "  OO      OO   ";
		Common::gotoXY(getXat(0, size - 1) + 7, getYat(0, size - 1) + 8);
		cout << "\t\t"; cout << " OO        OO  ";
		Common::gotoXY(getXat(0, size - 1) + 7, getYat(0, size - 1) + 9);
		cout << "\t\t"; cout << " OO        OO  ";
		Common::gotoXY(getXat(0, size - 1) + 7, getYat(0, size - 1) + 10);
		cout << "\t\t"; cout << "  OO      OO   ";
		Common::gotoXY(getXat(0, size - 1) + 7, getYat(0, size - 1) + 11);
		cout << "\t\t"; cout << "    OOOOOO     ";
	}
	else {
		Common::fixFontColor(4);
		Common::gotoXY(getXat(0, size - 1) + 7, getYat(0, size - 1) + 6);
		cout << "\t\t"; cout << "  XX      XX   ";
		Common::gotoXY(getXat(0, size - 1) + 7, getYat(0, size - 1) + 7);
		cout << "\t\t"; cout << "    XX  XX     ";
		Common::gotoXY(getXat(0, size - 1) + 7, getYat(0, size - 1) + 8);
		cout << "\t\t"; cout << "      XX       ";
		Common::gotoXY(getXat(0, size - 1) + 7, getYat(0, size - 1) + 9);
		cout << "\t\t"; cout << "      XX       ";
		Common::gotoXY(getXat(0, size - 1) + 7, getYat(0, size - 1) + 10);
		cout << "\t\t"; cout << "    XX  XX     ";
		Common::gotoXY(getXat(0, size - 1) + 7, getYat(0, size - 1) + 11);
		cout << "\t\t"; cout << "  XX      XX   " ;
		Common::fixFontColor(7);
		Common::gotoXY(getXat(0, size - 1) + 7, getYat(0, size - 1) + 15);
		cout << "\t"; cout<< "PRESS ESC TO SAVE...";
	}
}