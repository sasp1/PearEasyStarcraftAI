#pragma once
#include <BWAPI.h>
#include "ExecutionManager.h"
#include "GatheringManager.h"

class StrategyManager
{
	ExecutionManager* executionManager;
	UnitManager* unitManager;
	BuildingManager* buildingManager;
	CombatManager* combatManager;
	int startTime; 
	Game* broodWar;
	int ZERG_RUSH_TIME = 400; 
	int MAX_ZERGLINGS_FOR_RUSH = 4; 
	Race enemyRace; 

public:
	ConstructionManager* constructionManager;
	ScoutingManager* scoutingManager;
	StrategyManager(Game* _broodWar);
	~StrategyManager();
	void StrategyManager::calculateOrders();
	void StrategyManager::referenceManagers(ExecutionManager* executionManager, UnitManager* unitManager, BuildingManager* buildingManager, CombatManager* combatManager);
	void StrategyManager::executeTwoFactory();
	void StrategyManager::executeExpandWithOneFactory();
	void StrategyManager::unitComplete(BWAPI::UnitInterface* unit);
	void StrategyManager::onUnitDestroy(BWAPI::Unit unit);
	void StrategyManager::attackingStrategyProtoss();
	void StrategyManager::attackingStrategyTerran();
	void StrategyManager::attackingStrategyZerg();
	bool StrategyManager::EnemyHasAStructureMakingTanksRequired();
	bool StrategyManager::enemyHasLurkers();
	bool isEnemyRushing(); 
	GatheringManager* gatheringManager;
	int lastSupply;
	bool zergRush; 

};

