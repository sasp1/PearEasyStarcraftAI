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
int numberOfWorkersLimit = 22;
int supplyUsed = 0; 

void StrategyManager::calculateOrders() {
	supplyUsed = Broodwar->self()->supplyUsed() / 2;

	//Set executionManager orders
	if (strategy == 1) {
		executeTwoFactory();
	}
	else if (strategy == 2) {
		executeExpandWithOneFactory();
	}


	executionManager->executeOrders();

}

void StrategyManager::executeTwoFactory() {
	//Build strategy 1 
	int unusedSupplies = (Broodwar->self()->supplyTotal()) - Broodwar->self()->supplyUsed();
	
	
	//___________________________Moving units________________________________
	//Maintain 1 soldier for scouting
	
	if (scoutingManager->scoutingUnits.size() > 0) {
		buildingManager->barrackBuild = UnitTypes::None;
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
	if (  unusedSupplies <= 4 && supplyDepotsAreNotUnderConstruction) {

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
		Broodwar->sendText("adding refinery to priorityQueue");
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


	//Continue pressure with an extra factory STRATEGY
	if (!desireBuildingBarracks && factoriesOrdered == 2 && Broodwar->enemy()->getRace() == Races::Protoss) {
		strategy = 2;
		Broodwar->sendText("Executing strategy: expandWithOneFactory");
	
	}

}


void StrategyManager::executeExpandWithOneFactory() {


	int unusedSupplies = (Broodwar->self()->supplyTotal()) - Broodwar->self()->supplyUsed();

	//___________________________Moving units________________________________
	//Maintain 1 soldier for scouting

	if (factoriesOrdered >=3  && Broodwar->self()->minerals() > 500 || (scoutingManager->scoutingUnits.size() < 1)) {
			buildingManager->barrackBuild = UnitTypes::Terran_Marine;
	}
	else {
		buildingManager->barrackBuild = UnitTypes::None;
	}

	//Maintain workers
	if (unitManager->unitWorkers.size() > numberOfWorkersLimit) {
		buildingManager->setIsDesiredToTrainWorkers(false);
	}
	else { 
		buildingManager->setIsDesiredToTrainWorkers(true);
	}

	//Spam voltures
	buildingManager->factoryBuild = UnitTypes::Terran_Vulture;;


	//___________________________Building strategy________________________________


	//Construct supply depots when needed (11 supplies left)
	if ((unusedSupplies <= 22)  && supplyDepotsAreNotUnderConstruction) {

		BWAPI::UnitType building = Broodwar->self()->getRace().getSupplyProvider();
		executionManager->addPriorityItem(building);
		supplyDepotsAreNotUnderConstruction = false;
	}

	//Maintain 3 factories  AND EXPAND BASE!!!!!!
	
	if (Broodwar->self()->supplyUsed() >= 72 && factoriesOrdered < 3) {
		Broodwar->sendText("adding factory to priorityQueue");
		BWAPI::UnitType building = UnitTypes::Terran_Factory;
		executionManager->addPriorityItem(building);
		factoriesOrdered++;
	}
	

	//___________________________Attacking strategy________________________________
	
	if ((combatManager->combatUnits.size() + combatManager->vultures.size()) >= 2 && scoutingManager->enemyBaseFound) {
		combatManager->attackEnemyBaseWithAllCombatUnits(scoutingManager->lastEnemyBuildingPosition);
		
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