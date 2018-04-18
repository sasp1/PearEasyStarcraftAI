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
int numberOfWorkersLimit = 20;

void StrategyManager::calculateOrders() {

	//Set executionManager orders
	if (strategy == 1) {
		calculateStrategyOne();
	}
	else if (strategy == 2) {
		calculateStrategyTwo();
	}




	executionManager->executeOrders();

}

void StrategyManager::calculateStrategyOne() {
	//Build strategy 1 
	int unusedSupplies = (Broodwar->self()->supplyTotal()) - Broodwar->self()->supplyUsed();

	//___________________________Moving units________________________________
	//Maintain 1 soldier for scouting
	if (scoutingManager->scoutingUnits.size() > 0) {
		buildingManager->setIsDesiredToTrainMarines(false); 
	} else {
		buildingManager->setIsDesiredToTrainMarines(true);
	}

	//Maintain 20 workers
	if (unitManager->unitWorkers.size() > numberOfWorkersLimit) {
		buildingManager->setIsDesiredToTrainWorkers(false);
	}
	else {
		buildingManager->setIsDesiredToTrainWorkers(true);
	}

	//Spam voltures
	buildingManager->setIsDesiredToTrainVultures(true);
	
	
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




	/*if (Broodwar->self()->supplyUsed() >= 35 && starportsOrdered == 0) {
		Broodwar->sendText("adding starport to priorityQueue"); 
		BWAPI::UnitType building = UnitTypes::Terran_Starport; 
		executionManager->addPriorityItem(building); 
		starportsOrdered++; 
	}*/
	//___________________________Attacking strategy________________________________

	//Check if enough voltures for attack
	if (combatManager->combatUnits.size() >= 8) {
		combatManager->attackEnemyBaseWithAllCombatUnits(scoutingManager->lastEnemyBuildingPosition);
		strategy = 2;
		Broodwar->sendText("PHASE TWO");
		numberOfWorkersLimit = 40;
	}
}


void StrategyManager::calculateStrategyTwo() {

	//Order three factories
	//if (unitManager->unitWorkers.size() >= 25 && factoriesOrdered < 3) {
	//	Broodwar->sendText("adding factory to priorityQueue");
	//	BWAPI::UnitType building = UnitTypes::Terran_Factory;
	//	executionManager->addPriorityItem(building);
	//	factoriesOrdered++;
	//}

	//Broodwar->sendText("TROLOLOLOLOL");

	int unusedSupplies = (Broodwar->self()->supplyTotal()) - Broodwar->self()->supplyUsed();

	//___________________________Moving units________________________________
	//Maintain 1 soldier for scouting
	if (scoutingManager->scoutingUnits.size() > 0) {
		buildingManager->setIsDesiredToTrainMarines(false);
	}
	else {
		buildingManager->setIsDesiredToTrainMarines(true);
	}

	//Maintain 20 workers
	if (unitManager->unitWorkers.size() > 20) {
		buildingManager->setIsDesiredToTrainWorkers(false);
	}
	else {
		buildingManager->setIsDesiredToTrainWorkers(true);
	}

	//Spam voltures
	buildingManager->setIsDesiredToTrainVultures(true);


	//___________________________Building strategy________________________________


	//Construct supply depots when needed (2 supplies left)
	if (((unusedSupplies <= 4) || (unusedSupplies <= 20 && factoriesOrdered >= 1)) && supplyDepotsAreNotUnderConstruction) {

		BWAPI::UnitType building = Broodwar->self()->getRace().getSupplyProvider();

		executionManager->addPriorityItem(building);
		supplyDepotsAreNotUnderConstruction = false;
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