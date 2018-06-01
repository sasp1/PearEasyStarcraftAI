#include "StrategyManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;

bool supplyDepotsAreNotUnderConstruction = true;
bool desireBuildingBarracks = true;
int refineriesOrdered = 0;
int factoriesOrdered = 0;
int starportsOrdered = 0; 
int basesOrdered = 0; 
int strategy = 1;
int numberOfWorkersLimit = 30;
int supplyUsed = 0; 

void StrategyManager::calculateOrders() {
	supplyUsed = Broodwar->self()->supplyUsed() / 2;

	//Set executionManager orders
	if (strategy == 1) {
		executeTwoFactory();
	}
	else if (strategy == 2) {
		executeExpandWithTwoFactories();
	}




	executionManager->executeOrders();

}

void StrategyManager::executeTwoFactory() {
	//Build strategy 1 
	int unusedSupplies = (Broodwar->self()->supplyTotal()) - Broodwar->self()->supplyUsed();
	
	
	//___________________________Moving units________________________________
	//Maintain 1 soldier for scouting
	if (scoutingManager->scoutingUnits.size() > 0) {
		buildingManager->barrackBuild = NULL; 
	} else {
		buildingManager->barrackBuild = UnitTypes::Terran_Marine;
	}

	//Maintain 20 workers
	if (unitManager->unitWorkers.size() > numberOfWorkersLimit) {
		buildingManager->setIsDesiredToTrainWorkers(false);
	}
	else {
		buildingManager->setIsDesiredToTrainWorkers(true);
	}
	
	
	//___________________________Building strategy________________________________


	//Construct supply depots when needed (2 supplies left)
	if (  ((unusedSupplies <= 4) || (unusedSupplies <=20 && factoriesOrdered>=1))   && supplyDepotsAreNotUnderConstruction) {

		BWAPI::UnitType building = Broodwar->self()->getRace().getSupplyProvider();

			executionManager->addPriorityItem(building);
			supplyDepotsAreNotUnderConstruction = false;
	}

	//Build barracks
	if (Broodwar->self()->supplyUsed() >= 22 && desireBuildingBarracks) {
		BWAPI::UnitType building = UnitTypes::Terran_Barracks;

		Broodwar->sendText("adding barracks to priorityQueue");
		executionManager->addPriorityItem(building);
		desireBuildingBarracks = false;
	}

	//Order a refinery
	if (Broodwar->self()->supplyUsed() >= 22 && refineriesOrdered == 0) {
		Broodwar->sendText("adding refinerty to priorityQueue");
		BWAPI::UnitType building = UnitTypes::Terran_Refinery;
		executionManager->addPriorityItem(building);
		refineriesOrdered++;
	}

	//Order two factories
	if (Broodwar->self()->supplyUsed() >= 30 && factoriesOrdered < 2) {
		Broodwar->sendText("adding factory to priorityQueue");
		BWAPI::UnitType building = UnitTypes::Terran_Factory;
		executionManager->addPriorityItem(building);
		factoriesOrdered++;
	}


	//___________________________Attacking strategy________________________________

	//Check if enough voltures for attack
	/*
	if (combatManager->combatUnits.size() >= 8) {
		combatManager->attackEnemyBaseWithAllCombatUnits(scoutingManager->lastEnemyBuildingPosition);
		strategy = 2;
		Broodwar->sendText("PHASE TWO");
		numberOfWorkersLimit = 40;
	}
	*/

	//Continue pressure with 2 extra factories STRATEGY
	if (!desireBuildingBarracks && factoriesOrdered == 2 && Broodwar->enemy()->getRace() == Races::Protoss) {
		combatManager->attackEnemyBaseWithAllCombatUnits(scoutingManager->lastEnemyBuildingPosition);
		strategy = 2;
		Broodwar->sendText("TWO EXTRA FACTORIES EXPANDING");
	
	}

}


void StrategyManager::executeExpandWithTwoFactories() {

	//Order three factories
	//if (unitManager->unitWorkers.size() >= 25 && factoriesOrdered < 3) {
	//	Broodwar->sendText("adding factory to priorityQueue");
	//	BWAPI::UnitType building = UnitTypes::Terran_Factory;
	//	executionManager->addPriorityItem(building);
	//	factoriesOrdered++;
	//}

	int unusedSupplies = (Broodwar->self()->supplyTotal()) - Broodwar->self()->supplyUsed();

	//___________________________Moving units________________________________
	//Maintain 1 soldier for scouting
	if (scoutingManager->scoutingUnits.size() > 0) {
		buildingManager->barrackBuild = NULL;
	}
	else {
		buildingManager->barrackBuild = UnitTypes::Terran_Marine;
	}

	//Maintain 20 workers
	if (unitManager->unitWorkers.size() > numberOfWorkersLimit) {
		buildingManager->setIsDesiredToTrainWorkers(false);
	}
	else {
		buildingManager->setIsDesiredToTrainWorkers(true);
	}

	//Spam voltures
	buildingManager->factoryBuild = UnitTypes::Terran_Vulture;;


	//___________________________Building strategy________________________________


	//Construct supply depots when needed (2 supplies left)
	if (((unusedSupplies <= 4) || (unusedSupplies <= 20 && factoriesOrdered >= 1)) && supplyDepotsAreNotUnderConstruction) {

		BWAPI::UnitType building = Broodwar->self()->getRace().getSupplyProvider();

		executionManager->addPriorityItem(building);
		supplyDepotsAreNotUnderConstruction = false;
	}

	if (combatManager->combatUnits.size() >= 2) {
		combatManager->attackEnemyBaseWithAllCombatUnits(scoutingManager->lastEnemyBuildingPosition);
	}

	//Order two factories
	if (Broodwar->self()->minerals() >= 500 && factoriesOrdered < 4) {
		Broodwar->sendText("adding factory to priorityQueue");
		BWAPI::UnitType building = UnitTypes::Terran_Factory;
		executionManager->addPriorityItem(building);
		factoriesOrdered++;
	}

	if (factoriesOrdered >= 4) {

		buildingManager->barrackBuild = UnitTypes::Terran_Marine;
		
	}
	
	
	

}

void StrategyManager::unitComplete(const BWAPI::Unit* unit) {

	if ((*unit)->getType() == UnitTypes::Terran_Supply_Depot) {
		supplyDepotsAreNotUnderConstruction = true;
	}
}


// Iniitial class setup
void StrategyManager::referenceManagers(ExecutionManager* executionManager, UnitManager* unitManager, BuildingManager* buildingManager, CombatManager* combatManager) {
	this->executionManager = executionManager;
	this->unitManager = unitManager;
	this->buildingManager = buildingManager;
	this->combatManager = combatManager;
}

StrategyManager::~StrategyManager()
{
}

StrategyManager::StrategyManager()
{
}