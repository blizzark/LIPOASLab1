#include <Windows.h>
#include "Menu.h"
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <sstream>


using namespace std;

HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);

// Цвета
enum ConsoleColor {
	LightGray = 7,
	LightGreen = 10,
	LightRed = 12,
	Yellow = 14,
};

// Пункты меню.
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
	cout << "1. Да." << endl;
	cout << "2. Нет." << endl;
	cout << "Ваш выбор: ";
	
	return IntegerCheck(Yes, No);
}

// Изменение цвета
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



// Спросить нужно ли сохранять
int AskSave() {

	cout << "Хотите сохранить текст в файл?" << endl;
		return YesNo();
	
}

//Проверка ввода символа
string CheckSymbol() {
	string symbolArray;
	bool finished = false;
	cout << "Введите символ для поиска:  ";
	do {
			cin >> symbolArray;

				if (symbolArray.length() > 1) {
					cout << "Cимвол должен быть только 1!";
					cout << endl;
					
					cin.clear();
					while (cin.get() != '\n'); // чтобы после пробела не считывало ещё раз
					continue;
				}

				unsigned char tmp = symbolArray[0]; // сделал это, потому что русские буквы уходили в отрицательность

				// по таблице ASCII 
				// 65 - "A"; 90 - "Z"; 97 - "a"; 122 - "z"; 192 - "A"(рус); 255 - "я"; 
				if (static_cast<int>(tmp) < 65 ||
					(static_cast<int>(tmp) > 90 && static_cast<int>(tmp) < 97) ||
					((static_cast<int>(tmp) > 122 && static_cast<int>(tmp) < 192) ||
						static_cast<int>(tmp) > 255)) {
					cout << "Символ должен быть буквой! ";
					cout << endl;
					continue;
				}
				finished = true;
			
	} while (!finished);

	return symbolArray;
}



// Сохранение в файл
void SaveArray(string buf) {
	bool checkStorage = false;
	string fileName;
	int first = 1;
	do {

		if (first == 1) {
			cout << endl << "Если вы введёте только имя файла, то он будет в папке с проектом." << endl;
			cout << "Для сохранения файла в другом месте укажите полный путь к файлу." << endl;
			cout << "(По умолчанию в конец добавляется .txt)" << endl;
			cout << endl << "Введите путь к файлу: ";
		}
		else {
			cout << endl << "Попробуйте ввести другой: ";
		}
		first++;
		cin >> fileName;
		fileName += ".txt";
		bool checkExists = false;
		if (ifstream(fileName)) // проверяем на сущ.
			checkExists = true;

		ofstream file;
		file.open(fileName, ios::app);

		if (file.good()) {
			if (!std::experimental::filesystem::is_regular_file(fileName)) {
				ColorChange("Недопустимое имя файла.", LightRed);
				file.close();
				continue;
			}

			if (checkExists) {
				cout << "Данный файл существует! Перезаписать?" << endl;
				if (YesNo() == No) {
					file.close();
					continue;
				}
				else {
					file.close();
					file.open(fileName, ios::trunc);
					file << buf;
					checkStorage = true;
					ColorChange("Файл успешно записан!", LightGreen);
					cout << endl;

				}

			}
			else {
				file.close();
				file.open(fileName, ios::out);
				file << buf;
				checkStorage = true;
				ColorChange("Файл успешно записан!", LightGreen);
				cout << endl;
			}
		}
		else {
			ColorChange("Ошибка при открытии файла.", LightRed);
		}
		file.close();
	} while (!checkStorage);

}



// Проверка файла
bool FileCheck(string fileName) {
	ifstream file;
	file.open(fileName);

	long fileSize;
	file.seekg(0, ios::end);
	fileSize = (long)file.tellg(); // возможно надо static_cast<long>.. Разницы не вижу
	if (fileSize == 0) {
		ColorChange("Файл пуст!", LightRed);
		return false;
	}

	file.close();
	return true;
}


// Заполнение из файла
string FileEnter() {
	string fileName;
	

	cout << "Введите полный путь к файлу: ";
	getline(cin, fileName);
	ifstream file;
	file.open(fileName);
	if (std::experimental::filesystem::is_regular_file(fileName) && file.good()) {
		if (FileCheck(fileName) == true) {
			ColorChange("Файл открыт!", LightGreen);
			cout << endl;
			if (!file.eof()) {

				string buf;
				if (!file.eof()) {
					getline(file, buf, '\0');
			
				}

				cout << "Введённая строка:" << endl;

				ColorChange(buf, LightGreen);

				cout << endl;

				return buf;
			}
		}
	}
	else {
		ColorChange("Ошибка открытия файла!", LightRed);
		cout << endl;
		return "0";
	}
	file.close();
	return "0";
	
}

// Убираю символы и заменяю на пробел

string СhangeString(string buf) {

	string newBuf = "";
	unsigned char tmp;
	for (int i = 0; i < buf.length(); i++)
	{
		tmp = buf[i];
		// по таблице ASCII 
		// 65 - "A"; 90 - "Z"; 97 - "a"; 122 - "z"; 192 - "A"(рус); 255 - "я"; 45 - "-"
		if (static_cast<int>(tmp) < 65 ||
			(static_cast<int>(tmp) > 90 && static_cast<int>(tmp) < 97) ||
			((static_cast<int>(tmp) > 122 && static_cast<int>(tmp) < 192) ||
				static_cast<int>(tmp) > 255)) {

			if (static_cast<int>(tmp) == 45) { // если это дефис
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


// Пользовательский выбор
void UserСhoice(int choice) {


	string buf, symbolArray, word;

	if (choice == ManualInput) {
		cout << "Введите текст (для завершения ввода поставьте символ ';' и нажмите Enter): ";
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

	
		buf = СhangeString(buf); // очищаю от хлама "!@#$%^&*"
		cout << endl;
		
		symbolArray = CheckSymbol(); // Ввод и проверка символа

		
		cout << "Найдено слово:  " << endl;
		word = FindWord(buf, symbolArray);
		ColorChange(word, Yellow);
		string saveArray = word;
		if (saveArray.size() != 0) {
			if (AskSave() == Yes) {
				SaveArray(saveArray);
			}
		}
		else {
			ColorChange("Ничего не найдено!!!", LightRed);
		}
	}
	else {
		if (choice == ManualInput) {
			ColorChange("Строка пустая!", LightRed);
		}
	}
}

// Меню выбора
bool MainProgram(bool check) {

	if (check == true) {
		cout << "1. Ручной ввод." << endl;
		cout << "2. Ввод из файла." << endl;

		cout << endl << "Ваш выбор: ";
		switch (IntegerCheck(NumberItemsMin, NumberItemsMax)) {
		case(ManualInput):
			UserСhoice(ManualInput);
			break;
		case(FileInput):
			UserСhoice(FileInput);
			break;
		}

		MainMenu(false);
	}
	return false;
}



