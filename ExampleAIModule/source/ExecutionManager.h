#pragma once
#include <BWAPI.h>
#include "UnitManager.h"
#include "BuildingManager.h"

class ExecutionManager : public BWAPI::AIModule
{
	UnitManager* unitManager;
	BuildingManager* buildingManager;
	Game* broodWar; 
public:
	std::list <UnitType> priorityQueue;
	int reservedMinerals = 0;
	int reservedGas = 0;
	std::list<std::pair<UnitType, TilePosition>> buildingPriorityQueue; 
	ExecutionManager(Game* broodWar);
	void ExecutionManager::addPriorityItem(BWAPI::UnitType unit);
	void ExecutionManager::executeOrders();
	void ExecutionManager::referenceManagers(UnitManager* unitManager, BuildingManager* buildingManager);
	void ExecutionManager::eventConstructionInitiated(BWAPI::UnitInterface* unit);
	void ExecutionManager::addPriorityItem(UnitType unit, TilePosition unitPosition); 
};

