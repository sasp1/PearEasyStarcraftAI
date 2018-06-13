#pragma once
#include <BWAPI.h>
#include "Worker.h"
class BuildingManager;

class GatheringManager
{
public:
	std::list<Worker*> workers;
	GatheringManager();
	~GatheringManager();
	void GatheringManager::addWorker(BWAPI::UnitInterface* worker);
	void GatheringManager::executeOrders();
	void GatheringManager::allocateWorker(bool addToGas);
	void GatheringManager::addGasworker();
	void GatheringManager::splitWorkers();
	BWAPI::UnitInterface* GatheringManager::removeWorker();
	BuildingManager* buildingManager;
	
	
};

