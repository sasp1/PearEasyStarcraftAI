#pragma once
#include <BWAPI.h>
#include "ExecutionManager.h"

class StrategyManager
{
	ExecutionManager* executionManager;
	UnitManager* unitManager;
	BuildingManager* buildingManager;
	CombatManager* combatManager;

public:
	ScoutingManager* scoutingManager;
	StrategyManager();
	~StrategyManager();
	void StrategyManager::calculateOrders();
	void StrategyManager::referenceManagers(ExecutionManager* executionManager, UnitManager* unitManager, BuildingManager* buildingManager, CombatManager* combatManager);
	void StrategyManager::calculateStrategyOne();
	void StrategyManager::calculateStrategyTwo();
	void StrategyManager::unitComplete(const BWAPI::Unit* unit);
};

