#include "lib.h"
#include "point.h"
//
// Constructor
//
Point::Point() {
	x = y = check = 0;
}
//
Point::Point(int pX, int pY) {
	x = pX;
	y = pY;
	check = 0;
}
//
// Getter
//
int Point::getCheck() { return check; }
int Point::getX() { return x; }
int Point::getY() { return y; }
//
// Setter
//
void Point::setX(int val) { x = val; }
void Point::setY(int val) { y = val; }
bool Point::setCheck(int val) {
	if (val == 1 || val == -1 || val == 0) {
		check = val;
		return 1;
	}
	return 0;
}