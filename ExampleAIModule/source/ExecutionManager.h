#pragma once
#include <BWAPI.h>
#include "UnitManager.h"
#include "BuildingManager.h"

class ExecutionManager : public BWAPI::AIModule
{
	UnitManager* unitManager;
	BuildingManager* buildingManager;

public:
	ExecutionManager();
	~ExecutionManager();
	void ExecutionManager::addPriorityItem(BWAPI::UnitType unit);
	void ExecutionManager::executeOrders();
	void ExecutionManager::referenceManagers(UnitManager* unitManager, BuildingManager* buildingManager);
	void ExecutionManager::eventConstructionInitiated(BWAPI::Unit unit);
};

