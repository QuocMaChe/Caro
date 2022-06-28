#pragma once
#include "point.h"
#include "lib.h"

class Board {
public:
	int size;
	int top, left;
	int p1_moved, p2_moved;
	bool** checkArrived;
	Point** pArr;

	// Constructor - Destructor
	Board(int, int, int); // size-top-left
	~Board();

	// Getter
	int getSize();
	int getTop();
	int getLeft();
	int getXat(int, int);
	int getYat(int, int);
	int getDetail(int, int);

	// Filter
	void resetData();
	void drawBoard();
	int checkBoard(int, int, bool); // bool: player turn (0-p1/1-p2)
	int testBoard(int, int, int);      // |
	int testVertical(int, int, int);   // |
	int testHorizontal(int, int, int); // |3rd int: symbol(X/O)-(-1/1)
	int testCross_1(int, int, int);    // |
	int testCross_2(int, int, int);    // |
	pii cv_to_matrix_coord(int, int); // Converse coord-in-console-window of caro-cell to coord-in-matrix of caro-cell
	void playerStat();
	void updatePS();
	void showTurn(bool);
};