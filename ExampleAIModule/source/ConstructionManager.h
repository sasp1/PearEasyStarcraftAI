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
	void ConstructionManager::createBuilding(BWAPI::UnitType building, BWAPI::UnitInterface* worker);
	void ConstructionManager::createBuildingAtPos(BWAPI::UnitType building, BWAPI::UnitInterface* worker, BWAPI::Position pos);
	void ConstructionManager::executeOrders();
	void ConstructionManager::buildRefinery(BWAPI::UnitInterface* worker);
	void ConstructionManager::expandBase(BWAPI::UnitInterface* worker);
	void ConstructionManager::requestFromDead(Worker* w);
	void ConstructionManager::constructionBegun(BWAPI::Unit build);
	BuildingManager* buildingManager;
	UnitManager* unitManager;
	ScoutingManager* scoutingManager; 
	GatheringManager* gatheringManager;
	bool shouldExpandBase;

};

