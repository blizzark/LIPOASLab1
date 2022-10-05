#include <iostream>
#include "Menu.h"
#include "Source.h"
#include <Windows.h>

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");

	Greeting();
	do {
	} while (MainProgram(MainMenu(true)));
	return 0;
}
