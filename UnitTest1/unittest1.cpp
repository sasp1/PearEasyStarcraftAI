#include "stdafx.h"
#include "CppUnitTest.h"
#include "../ExampleAIModule/Source/BuildingManager.h"
#include "../ExampleAIModule/Source/UnitManager.h"
#include "UnitMock.h"


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
			//manager.executeOrders(); 
			Assert::AreEqual(3, 3); 
		}

		TEST_METHOD(shouldTrainWorkers)
		{
			UnitManager manager;
			BWAPI::UnitInterface* unit = new BWAPI::Unit(); 

		/*	int numberOfWorkers = manager.workers.size();
			Assert::AreEqual(0, numberOfWorkers);
			manager.newWorker(unit); 
			numberOfWorkers = manager.workers.size(); 
			Assert::AreEqual(1, numberOfWorkers);*/
		}

		TEST_METHOD(shouldScoutCornerClockwise) {
			ScoutingManager* manager = new ScoutingManager(BWAPI::Position(0,0)); 
			
			BWAPI::UnitInterface* unit = new BWAPI::Unit();
			
			BWAPI::UnitInterface* fakeUnit = new BWAPI::Unit(new UnitMock());  

			CombatManager* manager2 = new CombatManager(); 
			//int hej = manager2->combatUnits.size(); 
			int hej = 2;


			Assert::AreEqual(0, hej);
			manager->addScout(fakeUnit);
			hej = manager->scoutingUnits.size(); 
			Assert::AreEqual(1, hej); 

			manager->scoutCornersClockwise(fakeUnit); 
			Assert::AreEqual(2, manager->corner); 
		}
	};
}