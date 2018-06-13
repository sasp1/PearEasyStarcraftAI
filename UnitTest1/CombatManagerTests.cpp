#include "stdafx.h"
#include "UnitMock.h"
#include "VultureUnitMock.h"
#include "VultureUnitMockFarAway.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CombatManagerTests 
{

	TEST_CLASS(Mines) 
	{
	public: 

		BWAPI::UnitInterface* unitMock;
		Vulture* vulture;
		CombatManager* manager;
		MapData* mapData;

		TEST_METHOD_INITIALIZE(init) {

			unitMock = new VultureUnitMock();
			vulture = new Vulture(unitMock, BWAPI::Position(1, 1), 0);
			manager = new CombatManager();
			mapData = new MapData();
			manager->scoutingManager = new ScoutingManager(Position(1, 1), mapData);
		}

		TEST_METHOD(shouldSetMine) {
			Assert::AreEqual(true, manager->shouldSetMine(vulture, BWAPI::Races::Protoss, 0));
		}
		TEST_METHOD(shouldNotPutDownMineIfFarAwayFromChokePoint) {
			vulture = new Vulture(new VultureUnitMockFarAway(), BWAPI::Position(1, 1), 0); 
			Assert::AreEqual(false, manager->shouldSetMine(vulture, BWAPI::Races::Protoss, 0));
		}

	}; 

	TEST_CLASS(Vultures) {
		BWAPI::UnitInterface* unitMock;
		Vulture* vulture;
		CombatManager* manager;
		MapData* mapData;

		TEST_METHOD_INITIALIZE(init) {
			unitMock = new VultureUnitMock();
			vulture = new Vulture(unitMock, BWAPI::Position(1, 1), 0);
			manager = new CombatManager();
			mapData = new MapData();
			manager->scoutingManager = new ScoutingManager(Position(1, 1), mapData);
		}

		TEST_METHOD(shouldFleeIfOutNumbered) {

		}
	}; 
}