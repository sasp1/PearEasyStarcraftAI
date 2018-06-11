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
	void ConstructionManager::createBuilding(BWAPI::UnitType building, const BWAPI::Unit* worker);
	void ConstructionManager::createBuildingAtPos(BWAPI::UnitType building, const BWAPI::Unit* worker, BWAPI::Position pos);
	void ConstructionManager::executeOrders();
	void ConstructionManager::buildRefinery(const BWAPI::Unit* worker);
	void ConstructionManager::expandBase(const BWAPI::Unit* worker);
	void ConstructionManager::requestFromDead(Worker* w);
	void ConstructionManager::constructionBegun(BWAPI::Unit build);
	BuildingManager* buildingManager;
	UnitManager* unitManager;
	ScoutingManager* scoutingManager; 
	GatheringManager* gatheringManager;
	bool shouldExpandBase;

};

