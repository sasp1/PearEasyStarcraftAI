#include "stdafx.h"
#include "../ExampleAIModule/Source/SpiralSearch.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SpiralSearchTests
{
	TEST_CLASS(FindLocation) {
		
		SpiralSearch* spiralSearch; 


		TEST_METHOD_INITIALIZE(init2) {
			spiralSearch = new SpiralSearch(30000);
		}


		TEST_METHOD(shouldBeAtPosition) {
			Assert::AreEqual(0, spiralSearch->x); 
			Assert::AreEqual(0, spiralSearch->y);

			for (int i = 0; i < 9; i++)
			{
				spiralSearch->getNextPos(); 
			}
			
			Assert::AreEqual(30, spiralSearch->x);
			Assert::AreEqual(-30, spiralSearch->y);

		}
		TEST_METHOD(shouldReset) {

			for (int i = 0; i < 9; i++)
			{
				spiralSearch->getNextPos();
			}
			Assert::AreEqual(30, spiralSearch->maxX);
			Assert::AreEqual(30, spiralSearch->maxY);
			Assert::AreEqual(15, spiralSearch->attempt); 

			spiralSearch->reset(); 
			Assert::AreEqual(0, spiralSearch->maxX);
			Assert::AreEqual(0, spiralSearch->maxY);
			Assert::AreEqual(6, spiralSearch->attempt);

		}
	}; 
}