#pragma once
#include <BWAPI.h>
#include "ExecutionManager.h"

class StrategyManager
{
	ExecutionManager* executionManager;
	UnitManager* unitManager;
	BuildingManager* buildingManager;

public:
	ScoutingManager * scoutingManager;
	StrategyManager();
	~StrategyManager();
	void StrategyManager::calculateOrders();
	void StrategyManager::referenceManagers(ExecutionManager* executionManager, UnitManager* unitManager, BuildingManager* buildingManager);
	void StrategyManager::calculateStrategy();
	void StrategyManager::unitComplete(const BWAPI::Unit* unit);
};

