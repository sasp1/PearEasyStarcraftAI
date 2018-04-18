#pragma once
#include <BWAPI.h>
#include "BuildingManager.h"

class UnitManager;


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
	const BWAPI::Unit* constructionsWorker; 
	BuildingManager* buildingManager;

	bool shouldExpandBase;
	
};

