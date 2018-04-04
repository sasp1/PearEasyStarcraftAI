#include "StrategyManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;

bool supplyDepotsAreNotUnderConstruction = true;
bool desireBuildingBarracks = true;
int refineriesOrdered = 0;
int factoriesOrdered = 0;


void StrategyManager::calculateOrders() {
	
	//Set executionManager orders
	calculateStrategy();
	executionManager->executeOrders();

}

void StrategyManager::calculateStrategy() {
	//Build strategy 1 
	int unusedSupplies = (Broodwar->self()->supplyTotal()) - Broodwar->self()->supplyUsed();

	
	//Maintain 1 soldier for scouting
	if (scoutingManager->scoutingUnits.size() > 0) {
		buildingManager->setIsDesiredToTrainMarines(false); 
	} else {
		buildingManager->setIsDesiredToTrainMarines(true);
	}

	if (unitManager->unitWorkers.size() > 20) {
		buildingManager->setIsDesiredToTrainMarines(false);
	}
	else {
		buildingManager->setIsDesiredToTrainWorkers(true);
	}
	

	//Construct supply depots when needed (2 supplies left)
	if ((unusedSupplies <= 4) || (unusedSupplies <=8 && factoriesOrdered>1) && supplyDepotsAreNotUnderConstruction) {

		BWAPI::UnitType building = Broodwar->self()->getRace().getSupplyProvider();

			Broodwar->sendText("adding supply depot to priorityQueue");
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

	//Order a factory
	if (Broodwar->self()->supplyUsed() >= 30 && factoriesOrdered < 2) {
		Broodwar->sendText("adding factory to priorityQueue");
		BWAPI::UnitType building = UnitTypes::Terran_Factory;
		executionManager->addPriorityItem(building);
		factoriesOrdered++;
	}


	

}

void StrategyManager::unitComplete(const BWAPI::Unit* unit) {

	if ((*unit)->getType() == UnitTypes::Terran_Supply_Depot) {
		supplyDepotsAreNotUnderConstruction = true;
	}
}


// Iniitial class setup
void StrategyManager::referenceManagers(ExecutionManager* executionManager, UnitManager* unitManager, BuildingManager* buildingManager) {
	this->executionManager = executionManager;
	this->unitManager = unitManager;
	this->buildingManager = buildingManager;
}

StrategyManager::~StrategyManager()
{
}

StrategyManager::StrategyManager()
{
}