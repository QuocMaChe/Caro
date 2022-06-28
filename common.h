#pragma once

class Common {
public:
	static void fixConsolewindow();
	static void gotoXY(int, int);
	static void fixFontSize(int);
	static void fixFontColor(int);
	static void setCursor(bool);
	static void getConsoleSize();
	//  0 = Black       8 = Gray
	//	1 = Blue        9 = Light Blue
	//	2 = Green       A = Light Green
	//	3 = Aqua        B = Light Aqua
	//	4 = Red         C = Light Red
	//	5 = Purple      D = Light Purple
	//	6 = Yellow      E = Light Yellow
	//	7 = White       F = Bright White
};
