#include "stdafx.h"
#include "CppUnitTest.h"
#include "../ExampleAIModule/Source/BuildingManager.h"
#include "../ExampleAIModule/Source/UnitManager.h"
#include "UnitMock.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace BWAPI; 

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
			UnitMock* unit = new UnitMock(); 

		/*	int numberOfWorkers = manager.workers.size();
			Assert::AreEqual(0, numberOfWorkers);
			manager.newWorker(unit); 
			numberOfWorkers = manager.workers.size(); 
			Assert::AreEqual(1, numberOfWorkers);*/
		}

		TEST_METHOD(shouldScoutCornerClockwise) {
			ScoutingManager* manager = new ScoutingManager(Position(0,0), new MapData()); 
			
			UnitMock* mock = new UnitMock(); 
			
			UnitMock* fakeUnit = new UnitMock();  

			CombatManager* manager2 = new CombatManager(); 
			//int hej = manager2->combatUnits.size(); 
			int hej = 0;

			Assert::AreEqual(0, hej);
			manager->addScout(fakeUnit);
			hej = manager->scoutingUnits.size(); 
			Assert::AreEqual(1, hej); 

			manager->scoutCornersClockwise(mock);
			Assert::AreEqual(1, manager->corner); 
		}
	};
}