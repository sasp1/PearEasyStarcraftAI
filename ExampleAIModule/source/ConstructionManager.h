#pragma once
#include <BWAPI.h>
#include "BuildingManager.h"

class UnitManager;
class ScoutingManager; 
class GatheringManager;
class Worker;

class ConstructionManager
{	

public:
	ConstructionManager();
	~ConstructionManager();
	//void ConstructionManager::setManagers(BuildingManager* b, UnitManager* u);
	void ConstructionManager::createBuilding(BWAPI::UnitType building, const BWAPI::Unit* worker);
	const BWAPI::Unit* ConstructionManager::removeWorkersDoneConstructing();
	void ConstructionManager::executeOrders();
	void ConstructionManager::buildRefinery(const BWAPI::Unit* worker);
	void ConstructionManager::expandBase(const BWAPI::Unit* worker);
	BuildingManager* buildingManager;
	UnitManager* unitManager;
	ScoutingManager* scoutingManager; 
	GatheringManager* gatheringManager;
	bool shouldExpandBase;
	void ConstructionManager::requestFromDead(Worker* w);
	void ConstructionManager::constructiondBegun(BWAPI::Unit build);
};

