#include "stdafx.h"
#include "UnitMock.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace BWAPI; 

namespace CombatManagerTests 
{

	TEST_CLASS(Mines) 
	{
	public: 

		UnitMock* unitMock;
		Vulture* vulture;
		CombatManager* manager;
		MapData* mapData;
		UnitMock* vultureUnitMock; 

		TEST_METHOD_INITIALIZE(init) {

			unitMock = new UnitMock();
			unitMock->type = UnitTypes::Terran_Vulture; 
			vulture = new Vulture(unitMock, Position(1, 1), 0);
			manager = new CombatManager();
			mapData = new MapData();
			manager->scoutingManager = new ScoutingManager(Position(1, 1), mapData);
			vultureUnitMock = new UnitMock(); 
			vultureUnitMock->type = UnitTypes::Terran_Vulture; 
		}

		TEST_METHOD(shouldSetMine) {
			unitMock->useTechWithOrWithoutTarget = true;
			// setting vulture position close to defensive choke point
			unitMock->position =  Position(562, 925); 
			bool couldSetMine = manager->shouldSetMine(vulture, BWAPI::Races::Protoss, 0); 
			Assert::AreEqual(true, couldSetMine);
		}
		TEST_METHOD(shouldNotPutDownMineIfFarAwayFromChokePoint) {
			vulture = new Vulture(vultureUnitMock, BWAPI::Position(1, 1), 0); 
			Assert::AreEqual(false, manager->shouldSetMine(vulture, BWAPI::Races::Protoss, 0));
		}

	}; 
	
	TEST_CLASS(Vultures) {
		UnitMock* unitMock;
		Vulture* vulture;
		CombatManager* manager;
		MapData* mapData;

		TEST_METHOD_INITIALIZE(init) {
			unitMock = new UnitMock();
			unitMock->type = UnitTypes::Terran_Vulture; 
			vulture = new Vulture(unitMock, BWAPI::Position(1, 1), 0);
			manager = new CombatManager();
			mapData = new MapData();
			manager->scoutingManager = new ScoutingManager(Position(1, 1), mapData);
		}
		TEST_METHOD(shouldNotFindNearestHydra) {

		}

		TEST_METHOD(shouldBeOutNumbered) {
			UnitMock* hydraMock = new UnitMock(); 
			hydraMock->type = UnitTypes::Zerg_Hydralisk; 
			hydraMock->position = Position(10, 10);
			unitMock->type = UnitTypes::Terran_Vulture;
			unitMock->position = Position(11, 11);  
		}
		TEST_METHOD(shouldFleeIfOutNumbered) {
			manager->fleeIfOutNumbered(vulture, true); 
		}
	}; 
}