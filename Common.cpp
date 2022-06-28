#include "lib.h"
#include "common.h"

void Common::getConsoleSize() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	static int columns, rows;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	// printf("columns: %d\n", columns);
	// printf("rows: %d\n", rows);
}

// Fix Console Window
void Common::fixConsolewindow() {
	HWND consoleWindow = GetConsoleWindow();
	long style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, NULL);
}

void Common::fixFontSize(int fontSize) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = fontSize;            // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void Common::fixFontColor(int fontColor) {
	//  0 = Black       8 = Gray
	//	1 = Blue        9 = Light Blue
	//	2 = Green       A = Light Green
	//	3 = Aqua        B = Light Aqua
	//	4 = Red         C = Light Red
	//	5 = Purple      D = Light Purple
	//	6 = Yellow      E = Light Yellow
	//	7 = White       F = Bright White
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fontColor);
}

// Go to position {X,Y} in console window
void Common::gotoXY(int pX, int pY) {
	COORD coord;
	coord.X = pX;
	coord.Y = pY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Common::setCursor(bool visible) // set bool visible = 0 - invisible, bool visible = 1 - visible
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 10;
	SetConsoleCursorInfo(consoleHandle, &lpCursor);
}

//
// *****************
//


