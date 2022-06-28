#include "lib.h"
#include "common.h"
#include "board.h"
#include "game.h"
#include "menu.h"

// Constructor
Menu::Menu() {
	cX = 37, cY = 3;
	command = -1;
	detail.push_back("NEW GAME");
	detail.push_back("LOAD GAME");
	detail.push_back("HOW TO PLAY");
	detail.push_back("ABOUT");
	detail.push_back("EXIT");
}

// Draw border of menu
void Menu::drawBorder() {
	Common::fixFontSize(40);
	Common::fixFontColor(1);

	Common::gotoXY(1, 0);
	for (int i = 0; i <= 26; i++) {
		Sleep(15);
		cout << "*  ";
	}
	for (int i = 0; i <= 18; i++) {
		Common::gotoXY(79, 1 + i);
		Sleep(15);
		cout << "*";
	}
	for (int i = 0; i <= 26; i++) {
		Common::gotoXY(79 - (3 * i), 19);
		Sleep(15);
		cout << "* ";
	}
	for (int i = 0; i <= 18; i++) {
		Common::gotoXY(1, 19 - i);
		Sleep(15);
		cout << "*";
	}

	Common::gotoXY(39, 1);
	Common::fixFontColor(4);
	Common::gotoXY(10, 11); cout << "      |||||           |||         |||||||||        ||||||      " << endl; Sleep(100);
	Common::gotoXY(10, 12); cout << "   |||    |||        |||||        |||     ||     |||    |||    " << endl; Sleep(100);
	Common::gotoXY(10, 13); cout << "  |||               ||| |||       |||    |||    |||      |||   " << endl; Sleep(100);
	Common::gotoXY(10, 14); cout << "  |||              |||   |||      |||||||      ||          ||  " << endl; Sleep(100);
	Common::gotoXY(10, 15); cout << "  |||             |||||||||||     |||   |||     |||      |||   " << endl; Sleep(100);
	Common::gotoXY(10, 16); cout << "   |||    |||    |||       |||    |||    |||     |||    |||    " << endl; Sleep(100);
	Common::gotoXY(10, 17); cout << "      |||||     |||         |||   |||     |||      ||||||      " << endl; Sleep(100);


	Common::fixFontColor(7);
	for (int i = 0; i <= int(detail.size()) - 1; i++) {
		Common::gotoXY(37, 3 + i);
		cout << detail[i];
	}
}

// Switch Menu interface
void Menu::menuScreen() {
	Common::setCursor(0);
	system("cls");
	Menu::drawBorder();

	int preY = cY;
	Common::gotoXY(cX, cY);

	do {
		Common::gotoXY(cX, preY);
		Common::fixFontColor(7);
		cout << detail[preY - 3];


		Common::gotoXY(cX, cY);
		Common::fixFontColor(6);
		cout << detail[cY - 3];

		Common::gotoXY(cX, cY);

		int keyBoard = toupper(_getch());

		switch (keyBoard) {
		case 'W': case KEY_UP:
			if (cY > 3) {
				preY = cY;
				cY--;
				Common::gotoXY(cX, cY);
			}
			break;
		case 'S': case KEY_DOWN:
			if (cY < 7) {
				preY = cY;
				cY++;
				Common::gotoXY(cX, cY);
			}
			break;
		case KEY_ENTER: case KEY_SPACE:
			if (cY == 3) newGameScreen();
			if (cY == 4) loadGameScreen();
			if (cY == 5) guideScreen();
			if (cY == 6) aboutScreen();
			if (cY == 7) quit();
			break;
		}
	} while (true);
}

// Switch New game interface
void Menu::newGameScreen() {
	for (int i = 0; i <= int(detail.size()) - 1; i++) {
		Common::gotoXY(37, 3 + i);
		cout << "                 "; // Clear detail in the border
	}

	Common::fixFontColor(6);
	Common::gotoXY(33, 3);
	cout << "PLAYER WITH PLAYER";
	Common::fixFontColor(7);
	Common::gotoXY(33, 4);
	cout << "PLAYER WITH AI ";

	int _cX = 33, _cY = 3;
	
	do {
		int keyBoard = toupper(_getch());

		switch (keyBoard) {
		case KEY_ESC:
			menuScreen();
			break;
		case 'W': case KEY_UP:
			if (_cY > 3) {
				Common::gotoXY(_cX, _cY);
				Common::fixFontColor(7);
				cout << "PLAYER WITH AI";
				_cY--;
				Common::gotoXY(_cX, _cY);
				Common::fixFontColor(6);
				cout << "PLAYER WITH PLAYER";
			}
			break;
		case 'S': case KEY_DOWN:
			if (_cY < 4) {
				Common::gotoXY(_cX, _cY);
				Common::fixFontColor(7);
				cout << "PLAYER WITH PLAYER";
				_cY++;
				Common::gotoXY(_cX, _cY);
				Common::fixFontColor(6);
				cout << "PLAYER WITH AI";
			}
			break;
		case KEY_ENTER: case KEY_SPACE:
			if (_cY == 3) gamePlayScreen(0, 0, "");
			if (_cY == 4) gamePlayScreen(0, 1, "");
			break;
		}
	} while (true);
}

// Switch Load game interface
void Menu::loadGameScreen() {
	system("cls");
	Common::fixFontSize(30);


	Common::fixFontColor(1);
	Common::gotoXY(4, 0);
	cout << "#";
	Common::gotoXY(7, 0);
	cout << "FILE NAME";

	fstream F;
	F.open("Saved game\\database.txt", ios::in);
	vector<string> data;
	string s;
	int d = 0;
	Common::fixFontColor(7);
	while (getline(F, s)) {
		d++;
		Common::gotoXY(4, d);
		cout << d;
		Common::gotoXY(7, d);
		cout << s;
		data.push_back(s);
	}

	F.close();

	Common::gotoXY(0, d + 5);
	cout << "PRESS";
	Common::fixFontColor(4); cout << " ESC";
	Common::fixFontColor(7); cout << " TO RETURN MENU GAME...";

	int _cX = 0, _cY = 1; // Position of "==>"
	int numFile = 0; // Filename number
	Common::fixFontColor(4);

	Common::gotoXY(_cX, _cY);
	cout << "==>";

	char c = toupper(_getch());
	do {
		switch (c) {
		case KEY_ESC:
			menuScreen();
			break;
		case KEY_DOWN: case 'S':
			if (_cY < d) {
				Common::gotoXY(_cX, _cY);
				cout << "   ";
				Common::gotoXY(_cX, ++_cY);
				cout << "==>";
				numFile++;
			}
			break;
		case KEY_UP: case 'W':
			if (_cY > 1) {
				Common::gotoXY(_cX, _cY);
				cout << "   ";
				Common::gotoXY(_cX, --_cY);
				cout << "==>";
				numFile--;
			}
			break;
		case KEY_ENTER: case KEY_SPACE:
			if (d == 0) continue;
			system("cls");
			cout << "LOADING...";
			Sleep(1000);
			gamePlayScreen(1, 0, data[numFile]);
			break;
		}
	} while (c = toupper(_getch()));
}

// Switch 'How to play' interface
void Menu::guideScreen() {
	system("cls");
	Common::fixFontSize(28);
	Common::gotoXY(45, 0);
	Common::fixFontColor(4);
	cout << "=====CACH DIEU KHIEN=====\n\n";
	
	Common::gotoXY(47, 1);
	Common::fixFontColor(1);
	cout << "TRONG GIAO DIEN MENU:\n";
	
	Common::gotoXY(20, 2);
	Common::fixFontColor(7);
	cout << "Su dung 2 phim ";
	Common::fixFontColor(3); cout << "W ";
	Common::fixFontColor(3); cout << "S";

	Common::fixFontColor(7);
	cout << " hoac 2 phim mui ten ";

	Common::fixFontColor(3); cout << "UP-ARROW ";
	Common::fixFontColor(3); cout << "DOWN-ARROW";

	Common::fixFontColor(7);
	cout << " de di chuyen.\n";
	Common::gotoXY(38, 3);
	cout << "Su dung phim ";
	Common::fixFontColor(4); cout << "SPACE ";
	Common::fixFontColor(7); cout << "hoac ";
	Common::fixFontColor(4); cout << "ENTER ";
	Common::fixFontColor(7); cout << "de chon.\n\n";

	// ***
	Common::gotoXY(47, 5);
	Common::fixFontColor(9);
	cout << "TRONG GIAO DIEN GAME:\n";
	 
	Common::gotoXY(10, 6);
	Common::fixFontColor(7);
	cout << "Su dung 4 phim ";
	Common::fixFontColor(3); cout << "W ";
	Common::fixFontColor(3); cout << "A ";
	Common::fixFontColor(3); cout << "S ";
	Common::fixFontColor(3); cout << "D";

	Common::fixFontColor(7);
	cout << " hoac 4 phim mui ten ";

	Common::fixFontColor(3); cout << "UP-ARROW ";
	Common::fixFontColor(3); cout << "DOWN-ARROW ";
	Common::fixFontColor(3); cout << "LEFT-ARROW ";
	Common::fixFontColor(3); cout << "RIGHT-ARROW";

	Common::fixFontColor(7);
	cout << " de di chuyen.\n";
	Common::gotoXY(38, 7);
	cout << "Su dung phim ";
	Common::fixFontColor(9); cout << "SPACE ";
	Common::fixFontColor(7); cout << "hoac ";
	Common::fixFontColor(9); cout << "ENTER ";
	Common::fixFontColor(7); cout << "de danh dau.\n";
	Common::gotoXY(40, 8);
	cout << "Su dung phim ";
	Common::fixFontColor(9); cout << "ESC";
	Common::fixFontColor(7);
	cout << " de tro ve Menu game.\n\n";

	// ***
	Common::gotoXY(45, 10);
	Common::fixFontColor(4);
	cout << "======= CACH CHOI =======\n\n";
	Common::gotoXY(38, 12);
	Common::fixFontColor(7);
	cout << "Nguoi choi se choi tren ban co 10x10.\n";
	Common::gotoXY(30, 13);
	cout << "Nguoi di truoc duoc danh tai bat ki vi tri nao tren ban co.\n";
	Common::gotoXY(12, 14);
	cout << "Nguoi chien thang se la nguoi co du 5 quan co lien tiep theo hang ngang, hang doc hoac hang cheo.\n\n";
	Common::gotoXY(45, 15);
	cout << "Chuc ban choi game vui ve!!!"<<endl;
	Common::fixFontColor(4);
	Common::gotoXY(42, 16);
	cout << "PRESS ANY KEY TO RETURN MENU GAME...";

	_getch();
	menuScreen();
}

// Switch 'About' interface
void Menu::aboutScreen() {
	system("cls");
	Common::fixFontSize(30);
	Common::fixFontColor(4);
	cout << "Ten game: CARO\n";
	cout << "The loai: 2 Nguoi choi, Nguoi choi voi AI\n\n";

	cout << "Developer: Group 20A\n";
	cout << "20120343_TRAN MINH NHUT\n";
	cout << "20120429_NGUYEN QUOC ANH\n";
	cout << "20120430_DANG DUC BA\n";
	cout << "Office: KHOA CONG NGHE THONG TIN - DAI HOC KHOA HOC TU NHIEN - DAI HOC QUOC GIA TP.HCM (FIT-HCMUS)\n";


	Common::fixFontColor(8);
	cout << "PRESS ANY KEY TO RETURN MENU GAME...";

	_getch();
	menuScreen();
}

// Switch Gameplay interface
void Menu::gamePlayScreen(bool doLoad, bool mode, string fileName) {
	game myGame(10, 0, 0);
	myGame.botMode = mode;
	Common::fixFontSize(40);
	if (!doLoad) myGame.startGame();
	else myGame.loadGame(fileName);
	Common::setCursor(1);
	while (myGame.isContinue()) {
		if (myGame.turn == 1 && myGame.botMode == 1) {
			Sleep(50);
			myGame.botMove();
		}
		else myGame.waitKeyboard();
		if (myGame.getCommand() == KEY_ESC) {
			myGame.askSaveGame();
			myGame.exitGame();
		}
		else {
			switch (myGame.getCommand()) {
			case 'W': case KEY_UP:
				myGame.moveUp();
				break;
			case 'A': case KEY_LEFT:
				myGame.moveLeft();
				break;
			case 'S': case KEY_DOWN:
				myGame.moveDown();
				break;
			case 'D': case KEY_RIGHT:
				myGame.moveRight();
				break;
			case KEY_ENTER: case KEY_SPACE:
				if (myGame.processCheckBoard()) {
					switch (myGame.processFinishGame()) {
					case 1: case -1:
						if (myGame.askContinue() != 'Y') myGame.exitGame();
						else {
							myGame.startGame();
							myGame.updatePI();
						}
						break;
					}
				}
			}
		}
	}
	menuScreen();
}

void Menu::quit() {
	system("cls");
	exit(0);
}