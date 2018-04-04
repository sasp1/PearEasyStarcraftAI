#pragma once
#include <BWAPI.h>
#include "CombatManager.h"
#include "GatheringManager.h"
#include "ConstructionManager.h"
#include "ScoutingManager.h"
class UnitManager
{
	CombatManager* combatManager;
	GatheringManager* gatheringManager;
	ConstructionManager* constructionManager;
	ScoutingManager* scoutingManager;


public:
	void UnitManager::setManagers(CombatManager* combatManager, GatheringManager* gatheringManager, ConstructionManager* constructionManager, ScoutingManager* scoutingManager);
	~UnitManager();
	UnitManager();
	void UnitManager::executeOrders();
	void UnitManager::newWorker(const BWAPI::Unit* worker);
	void UnitManager::eventConstructionComplete(const BWAPI::Unit* unit);
	bool UnitManager::requestBuilding(BWAPI::UnitType building);
	bool newConstructionIsAvailable = true;

	std::list<const BWAPI::Unit*> unitWorkers;
	std::list<const BWAPI::Unit*> soldiers;
};

