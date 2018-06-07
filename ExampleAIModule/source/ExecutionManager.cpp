#include "ExecutionManager.h"
#include <BWAPI.h>
#include "UnitManager.h"
#include "BuildingManager.h"

using namespace BWAPI;
using namespace Filter;

std::list <UnitType> priorityQueue;
int reservedMinerals;
int reservedGas;

void ExecutionManager::executeOrders() {

	//Check for new desires
	if (priorityQueue._Mysize() > 0) {
		BWAPI::UnitType building = priorityQueue.front();
		if (unitManager->requestBuilding(building, reservedMinerals, reservedGas))
		{
			priorityQueue.pop_front();
			reservedMinerals = reservedMinerals + building.mineralPrice();
			reservedGas = reservedGas + building.gasPrice();

		}
	}

	//Check if minerals is reserved for buildings, and if then stop producing moving units
	controlTrainingOfMovingUnits();
	buildingManager->executeOrders();
	unitManager->executeOrders();
}

void ExecutionManager::addPriorityItem(BWAPI::UnitType unit) {
	priorityQueue.push_back(unit);
}

void ExecutionManager::controlTrainingOfMovingUnits() {
	/*
	if (Broodwar->self()->minerals() - reservedMinerals < UnitTypes::Terran_SCV.mineralPrice()) {
		buildingManager->setIsDesiredToTrainWorkers(false);
	}
	else {
		buildingManager->setIsDesiredToTrainWorkers(true);
	}
	if (Broodwar->self()->minerals() - reservedMinerals < UnitTypes::Terran_Marine.mineralPrice()) {
		buildingManager->setIsDesiredToTrainMarines(false);
	}
	else {
		buildingManager->setIsDesiredToTrainMarines(true);
	}
	*/
}

void ExecutionManager::eventConstructionInitiated(BWAPI::Unit unit) {
	//When a construction has begun building
	if (unit->getType().isBuilding()) {
		reservedMinerals = reservedMinerals - unit->getType().mineralPrice();
		reservedGas = reservedGas - unit->getType().gasPrice();
	}
}

void ExecutionManager::referenceManagers(UnitManager* unitManager, BuildingManager* buildingManager) {
	this->buildingManager = buildingManager;
	this->unitManager = unitManager;
}

//Initial setup of class
ExecutionManager::ExecutionManager()
{
	reservedMinerals = 0;
	reservedGas = 0;
}

ExecutionManager::~ExecutionManager()
{
}

