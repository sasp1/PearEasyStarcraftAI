#include "stdafx.h"
#include "CppUnitTest.h"
#include "../ExampleAIModule/BuildingManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			// TODO: Your test code here
			BuildingManager manager; 
			Assert::AreEqual(3, manager.hej(2)); 
		}
	};
}