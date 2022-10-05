#include "Source.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

enum InternalMenuMenu {
	Start = 1,
	Exit = 2,
};

// �����������
void Greeting() {
	cout << "������� ������ � 475: ���������� �����" << endl << endl;
	cout << "����� �����. ���������� ����� � ���������� ���������� ��������� �������." << endl << endl;
}

// �������� �� ���������������. ��������� ����������� � ������������ ��������.
int IntegerCheck(int min, int max) {
	int tmp;
	cin >> tmp;

	while (cin.fail()) {
		cout << "�������� ����. ��������� ����:";
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
		cout << "�������� ����. ��������� ����:";
		IntegerCheck(min, max);
	}

	return 0;
}

// ������� ����
bool MainMenu(bool �hoice) {
	if (�hoice) {
		cout << "1. ������ ������." << endl;
	}

	else {
		cout << endl << "����������� ��� ���?" << endl;
		cout << "1. ������ ������" << endl;
	}

	cout << "2. �����." << endl << endl;
	cout << "��� �����: ";
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
