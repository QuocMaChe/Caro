#pragma once
#include "lib.h"
#include "common.h"
#include "menu.h"

int main() 
{
	Common::fixConsolewindow();
	Common::getConsoleSize();
	Menu menu;
	menu.menuScreen();
	system("pause");
}