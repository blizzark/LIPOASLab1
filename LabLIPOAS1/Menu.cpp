#include "Source.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

enum InternalMenuMenu {
	Start = 1,
	Exit = 2,
};

// Приветствие
void Greeting() {
	cout << "Студент группы № 475: Овчинников Роман" << endl << endl;
	cout << "Задан текст. Определить слово с наибольшим вхождением заданного символа." << endl << endl;
}

// Проверка на целочисленность. Принимает минимальное и максимальное значение.
int IntegerCheck(int min, int max) {
	int tmp;
	cin >> tmp;

	while (cin.fail()) {
		cout << "Неверный ввод. Повторите ввод:";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> tmp;
	}

	if ((tmp >= min) && (tmp <= max)) {
		cin.ignore(INT_MAX, '\n');
		return tmp;
	}
	else {
		cin.ignore(INT_MAX, '\n');
		cout << "Неверный ввод. Повторите ввод:";
		IntegerCheck(min, max);
	}

	return 0;
}

// Главное меню
bool MainMenu(bool сhoice) {
	if (сhoice) {
		cout << "1. Начать работу." << endl;
	}

	else {
		cout << endl << "Попробовать еще раз?" << endl;
		cout << "1. Начать заново" << endl;
	}

	cout << "2. Выход." << endl << endl;
	cout << "Ваш выбор: ";
	int const NumberItemsMin = 1;
	int const NumberItemsMax = 2;

	switch (IntegerCheck(NumberItemsMin, NumberItemsMax)) {
	case(Start):
		cout << endl;
		MainProgram(true);
		break;
	case(Exit):
		return false;
	}
	return false;
}
