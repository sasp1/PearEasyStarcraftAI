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
	ConstructionManager* constructionManager;
	ScoutingManager* scoutingManager;
	StrategyManager();
	~StrategyManager();
	void StrategyManager::calculateOrders();
	void StrategyManager::referenceManagers(ExecutionManager* executionManager, UnitManager* unitManager, BuildingManager* buildingManager, CombatManager* combatManager);
	void StrategyManager::executeTwoFactory();
	void StrategyManager::executeExpandWithOneFactory();
	void StrategyManager::unitComplete(const BWAPI::Unit* unit);
	bool StrategyManager::EnemyHasAStructureMakingTanksRequired();

};

