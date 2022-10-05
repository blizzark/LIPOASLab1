#include <Windows.h>
#include "Menu.h"
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <sstream>


using namespace std;

HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);

// �����
enum ConsoleColor {
	LightGray = 7,
	LightGreen = 10,
	LightRed = 12,
	Yellow = 14,
};

// ������ ����.
enum InternalMenu {
	Yes = 1,
	No,
	Again,
};

enum Menu {
	ManualInput = 1,
	FileInput,
};

enum Numbers {
	NumberItemsMin = 1,
	NumberItemsMax,
};



int YesNo() {
	cout << "1. ��." << endl;
	cout << "2. ���." << endl;
	cout << "��� �����: ";
	
	return IntegerCheck(Yes, No);
}

// ��������� �����
void ColorChange(string text, int color) {
	if (color == LightRed) {
		SetConsoleTextAttribute(hOUTPUT, LightRed);
		cout << text << endl;
		SetConsoleTextAttribute(hOUTPUT, LightGray);
	}
	if (color == LightGreen) {
		SetConsoleTextAttribute(hOUTPUT, LightGreen);
		cout << text << endl;
		SetConsoleTextAttribute(hOUTPUT, LightGray);
	}
	if (color == Yellow) {
		SetConsoleTextAttribute(hOUTPUT, Yellow);
		cout << text << endl;
		SetConsoleTextAttribute(hOUTPUT, LightGray);
	}

}



// �������� ����� �� ���������
int AskSave() {

	cout << "������ ��������� ����� � ����?" << endl;
		return YesNo();
	
}

//�������� ����� �������
string CheckSymbol() {
	string symbolArray;
	bool finished = false;
	cout << "������� ������ ��� ������:  ";
	do {
			cin >> symbolArray;

				if (symbolArray.length() > 1) {
					cout << "C����� ������ ���� ������ 1!";
					cout << endl;
					
					cin.clear();
					while (cin.get() != '\n'); // ����� ����� ������� �� ��������� ��� ���
					continue;
				}

				unsigned char tmp = symbolArray[0]; // ������ ���, ������ ��� ������� ����� ������� � ���������������

				// �� ������� ASCII 
				// 65 - "A"; 90 - "Z"; 97 - "a"; 122 - "z"; 192 - "A"(���); 255 - "�"; 
				if (static_cast<int>(tmp) < 65 ||
					(static_cast<int>(tmp) > 90 && static_cast<int>(tmp) < 97) ||
					((static_cast<int>(tmp) > 122 && static_cast<int>(tmp) < 192) ||
						static_cast<int>(tmp) > 255)) {
					cout << "������ ������ ���� ������! ";
					cout << endl;
					continue;
				}
				finished = true;
			
	} while (!finished);

	return symbolArray;
}



// ���������� � ����
void SaveArray(string buf) {
	bool checkStorage = false;
	string fileName;
	int first = 1;
	do {

		if (first == 1) {
			cout << endl << "���� �� ������ ������ ��� �����, �� �� ����� � ����� � ��������." << endl;
			cout << "��� ���������� ����� � ������ ����� ������� ������ ���� � �����." << endl;
			cout << "(�� ��������� � ����� ����������� .txt)" << endl;
			cout << endl << "������� ���� � �����: ";
		}
		else {
			cout << endl << "���������� ������ ������: ";
		}
		first++;
		cin >> fileName;
		fileName += ".txt";
		bool checkExists = false;
		if (ifstream(fileName)) // ��������� �� ���.
			checkExists = true;

		ofstream file;
		file.open(fileName, ios::app);

		if (file.good()) {
			if (!std::experimental::filesystem::is_regular_file(fileName)) {
				ColorChange("������������ ��� �����.", LightRed);
				file.close();
				continue;
			}

			if (checkExists) {
				cout << "������ ���� ����������! ������������?" << endl;
				if (YesNo() == No) {
					file.close();
					continue;
				}
				else {
					file.close();
					file.open(fileName, ios::trunc);
					file << buf;
					checkStorage = true;
					ColorChange("���� ������� �������!", LightGreen);
					cout << endl;

				}

			}
			else {
				file.close();
				file.open(fileName, ios::out);
				file << buf;
				checkStorage = true;
				ColorChange("���� ������� �������!", LightGreen);
				cout << endl;
			}
		}
		else {
			ColorChange("������ ��� �������� �����.", LightRed);
		}
		file.close();
	} while (!checkStorage);

}



// �������� �����
bool FileCheck(string fileName) {
	ifstream file;
	file.open(fileName);

	long fileSize;
	file.seekg(0, ios::end);
	fileSize = (long)file.tellg(); // �������� ���� static_cast<long>.. ������� �� ����
	if (fileSize == 0) {
		ColorChange("���� ����!", LightRed);
		return false;
	}

	file.close();
	return true;
}


// ���������� �� �����
string FileEnter() {
	string fileName;
	

	cout << "������� ������ ���� � �����: ";
	getline(cin, fileName);
	ifstream file;
	file.open(fileName);
	if (std::experimental::filesystem::is_regular_file(fileName) && file.good()) {
		if (FileCheck(fileName) == true) {
			ColorChange("���� ������!", LightGreen);
			cout << endl;
			if (!file.eof()) {

				string buf;
				if (!file.eof()) {
					getline(file, buf, '\0');
			
				}

				cout << "�������� ������:" << endl;

				ColorChange(buf, LightGreen);

				cout << endl;

				return buf;
			}
		}
	}
	else {
		ColorChange("������ �������� �����!", LightRed);
		cout << endl;
		return "0";
	}
	file.close();
	return "0";
	
}

// ������ ������� � ������� �� ������

string �hangeString(string buf) {

	string newBuf = "";
	unsigned char tmp;
	for (int i = 0; i < buf.length(); i++)
	{
		tmp = buf[i];
		// �� ������� ASCII 
		// 65 - "A"; 90 - "Z"; 97 - "a"; 122 - "z"; 192 - "A"(���); 255 - "�"; 45 - "-"
		if (static_cast<int>(tmp) < 65 ||
			(static_cast<int>(tmp) > 90 && static_cast<int>(tmp) < 97) ||
			((static_cast<int>(tmp) > 122 && static_cast<int>(tmp) < 192) ||
				static_cast<int>(tmp) > 255)) {

			if (static_cast<int>(tmp) == 45) { // ���� ��� �����
				newBuf += tmp;
				continue;
			}

			newBuf += " ";
		}
		else {
			newBuf += tmp;
		}
	}
	return newBuf;
}

string FindWord(string buf, string symbolArray) {

	string word;
	istringstream ist(buf);
	string wordExit = "";
	int numWords = 0;
	while (ist >> word) {
		for (auto symbol : symbolArray)
		{
			if (word.find(symbol) != string::npos)
			{

				int numWord = 0;
				for (int i = 0; i < word.length(); i++)
				{
					if (word[i] == symbol) {
						numWord++;
					}
				}
				if (numWords < numWord) {
					numWords = numWord;
					wordExit = word;
				}
				break;
			}
		}
	}

	return wordExit;
}


// ���������������� �����
void User�hoice(int choice) {


	string buf, symbolArray, word;

	if (choice == ManualInput) {
		cout << "������� ����� (��� ���������� ����� ��������� ������ ';' � ������� Enter): ";
		SetConsoleTextAttribute(hOUTPUT, LightGreen);
		getline(cin, buf, ';');
		SetConsoleTextAttribute(hOUTPUT, LightGray);
		cin.clear();
		cin.ignore(INT_MAX, '\n');

	}
	if (choice == FileInput) {
		buf = FileEnter();
	}
	if ((buf != "0") && (buf.length() != 0)) {
		if (choice == ManualInput) {
			if (AskSave() == Yes) {
				SaveArray(buf);
			}
		}

	
		buf = �hangeString(buf); // ������ �� ����� "!@#$%^&*"
		cout << endl;
		
		symbolArray = CheckSymbol(); // ���� � �������� �������

		
		cout << "������� �����:  " << endl;
		word = FindWord(buf, symbolArray);
		ColorChange(word, Yellow);
		string saveArray = word;
		if (saveArray.size() != 0) {
			if (AskSave() == Yes) {
				SaveArray(saveArray);
			}
		}
		else {
			ColorChange("������ �� �������!!!", LightRed);
		}
	}
	else {
		if (choice == ManualInput) {
			ColorChange("������ ������!", LightRed);
		}
	}
}

// ���� ������
bool MainProgram(bool check) {

	if (check == true) {
		cout << "1. ������ ����." << endl;
		cout << "2. ���� �� �����." << endl;

		cout << endl << "��� �����: ";
		switch (IntegerCheck(NumberItemsMin, NumberItemsMax)) {
		case(ManualInput):
			User�hoice(ManualInput);
			break;
		case(FileInput):
			User�hoice(FileInput);
			break;
		}

		MainMenu(false);
	}
	return false;
}



