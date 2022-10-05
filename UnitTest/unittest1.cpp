#include "stdafx.h"
#include "CppUnitTest.h"
#include "../LabLIPOAS1/Source.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			/*std::string text = "abb aab bba bbb aaa bbaba";
			std::string symbol = "a";
			std::string word = "aaa";*/

			Assert::AreEqual(1, 1);
			
		}

	};
}