#pragma once

class Point {
	int x, y, check;

public:
	// Constructor
	Point();
	Point(int, int);

	// Getter
	int getCheck();
	int getX();
	int getY();

	// Setter
	void setX(int);
	void setY(int);
	bool setCheck(int);
};