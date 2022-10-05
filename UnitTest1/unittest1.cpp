#include "stdafx.h"
#include "CppUnitTest.h"
#include "../LabLIPOAS1/Source.h" 
#include "../LabLIPOAS1/Source.cpp" 
#include "../LabLIPOAS1/Menu.cpp" 
#include "../LabLIPOAS1/Menu.h" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethodEnglishLetter)
		{
			std::string text = "abb aba bba bbb aaa bbab bbbab";
			std::string symbol = "a";
			std::string word = "aaa";
			Assert::AreEqual(FindWord(text, symbol), word);
		}
		TEST_METHOD(TestMethodRussianLetter)
		{
			std::string text = "��� ��� ������ ���� �������";
			std::string symbol = "�";
			std::string word = "������";
			Assert::AreEqual(FindWord(text, symbol), word);
		}
		TEST_METHOD(TestMethodEnter)
		{
			std::string text = "jhdf\n hhhjjj\n jjkkyyyyyyy\n ooo";
			std::string symbol = "j";
			std::string word = "hhhjjj";
			Assert::AreEqual(FindWord(text, symbol), word);
		}
		TEST_METHOD(TestMethodHyphen)
		{
			std::string text = "����� �����-�� ���� ���� ������";
			std::string symbol = "�";
			std::string word = "�����-��";
			Assert::AreEqual(FindWord(text, symbol), word);
		}
	};
}