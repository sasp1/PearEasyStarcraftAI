#include "StrategyManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;

bool desireBuildingSupplyDepot = true;
bool desireBuildingBarracks = true;


void StrategyManager::calculateOrders() {
	
	//Set executionManager orders
	calculateStrategy();
	executionManager->executeOrders();

}

void StrategyManager::calculateStrategy() {
	//Build strategy 1 
	int unusedSupplies = (Broodwar->self()->supplyTotal()) - Broodwar->self()->supplyUsed();

	//Spam supply depots when needed
	if (unusedSupplies <= 4 && desireBuildingSupplyDepot) {

		BWAPI::UnitType building = Broodwar->self()->getRace().getSupplyProvider();
		Broodwar->sendText("Want To build supply depot");

		//if (Broodwar->self()->minerals() > building.mineralPrice()) {
			Broodwar->sendText("adding supply depot to priorityQueue");
			executionManager->addPriorityItem(building);
			desireBuildingSupplyDepot = false;
		//}
	}

	//Build barracks
	if (Broodwar->self()->supplyUsed() >= 22 && desireBuildingBarracks) {
		BWAPI::UnitType building = UnitTypes::Terran_Barracks;
		Broodwar->sendText("Want To build barracks %i", Broodwar->self()->supplyUsed());

		//if (Broodwar->self()->minerals() > building.mineralPrice()) {
			Broodwar->sendText("adding barracks to priorityQueue");
			executionManager->addPriorityItem(building);
			desireBuildingBarracks = false;
		//}
	}
}

void StrategyManager::unitComplete(const BWAPI::Unit* unit) {

	if ((*unit)->getType() == UnitTypes::Terran_Supply_Depot) {
		desireBuildingSupplyDepot = true;
	}
}


// Iniitial class setup
void StrategyManager::referenceManagers(ExecutionManager* executionManager) {
	this->executionManager = executionManager;
}

StrategyManager::~StrategyManager()
{
}

StrategyManager::StrategyManager()
{
}