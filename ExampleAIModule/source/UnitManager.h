#pragma once
#include <BWAPI.h>
#include "BuildingManager.h"
#include "GatheringManager.h"
#include "ConstructionManager.h"
class UnitManager
{
	BuildingManager* buildingManager;
	GatheringManager* gatheringManager;
	ConstructionManager* constructionManager;
public:
	void UnitManager::setManagers(BuildingManager* buildingManager, GatheringManager* gatheringManager, ConstructionManager* constructionManager);
	~UnitManager();
	UnitManager();
	void UnitManager::executeOrders();
	void UnitManager::newWorker(const BWAPI::Unit* worker);
	void UnitManager::buildConstruction(BWAPI::UnitType building);
	void UnitManager::eventConstructionInitiated();
	void UnitManager::eventConstructionComplete();
};

