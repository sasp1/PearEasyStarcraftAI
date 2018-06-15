#include "ExecutionManager.h"
#include <BWAPI.h>
#include "UnitManager.h"
#include "BuildingManager.h"

using namespace BWAPI;
using namespace Filter;



/**
* @file ExecutionManager.cpp
* @brief The first manager to perform an action when strategy is updated.
* Controls reservation of resources, and initiation of building constructions.
* @author Daniel Fjordhøj <s133198@student.dtu.dk>
*/

void ExecutionManager::executeOrders() {

	//Request construction of a building if there is enough resources
	if (priorityQueue._Mysize() > 0) {
		BWAPI::UnitType building = priorityQueue.front();
		if (unitManager->requestBuilding(building, reservedMinerals, reservedGas, Broodwar->self()->minerals(), Broodwar->self()->gas()))
		{
			priorityQueue.pop_front();
			reservedMinerals = reservedMinerals + building.mineralPrice();
			reservedGas = reservedGas + building.gasPrice();
		}
	}

	//Execute orders for lower managers
	buildingManager->executeOrders();
	unitManager->executeOrders();
}

void ExecutionManager::addPriorityItem(BWAPI::UnitType unit) {
	//Add requested building to queue
	priorityQueue.push_back(unit);
}

void ExecutionManager::eventConstructionInitiated(BWAPI::UnitInterface* unit) {
	//Remove reserved funds when constrution of a building has begun
	if (unit->getType().isBuilding()) {
		reservedMinerals = reservedMinerals - unit->getType().mineralPrice();
		reservedGas = reservedGas - unit->getType().gasPrice();
	}
}

void ExecutionManager::referenceManagers(UnitManager* unitManager, BuildingManager* buildingManager) {
	//Make manager aware of relevant managers
	this->buildingManager = buildingManager;
	this->unitManager = unitManager;
}

ExecutionManager::ExecutionManager()
{
}
