#include "ExecutionManager.h"
#include <BWAPI.h>
#include "UnitManager.h"
#include "BuildingManager.h"

using namespace BWAPI;
using namespace Filter;

std::list <UnitType> priorityQueue;

void ExecutionManager::executeOrders() {

	if (priorityQueue.size() > 0) {

		BWAPI::UnitType building = priorityQueue.front();
		if (unitManager->requestBuilding(building))
		{
			priorityQueue.pop_front();
			Broodwar->sendText("Queue size now %i after build is put in progress", priorityQueue.size());
		}
	}
	
	buildingManager->executeOrders();
	unitManager->executeOrders();
}

void ExecutionManager::addPriorityItem(BWAPI::UnitType unit) {
	priorityQueue.push_back(unit);
}

void ExecutionManager::handleWorker(const BWAPI::Unit* u) {


}

void ExecutionManager::eventConstructionInitiated() {
	//When a construction has begun building
	buildingManager->setIsDesiredToBuildWorkers(true);
}


//Initial setup of class
ExecutionManager::ExecutionManager()
{
}

ExecutionManager::~ExecutionManager()
{
}

void ExecutionManager::referenceManagers(UnitManager* unitManager, BuildingManager* buildingManager) {
	this->buildingManager = buildingManager;
	this->unitManager = unitManager;
}