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
	void GatheringManager::addWorker(const BWAPI::Unit* worker);
	void GatheringManager::executeOrders();
	const BWAPI::Unit* GatheringManager::removeWorker();
	void GatheringManager::addGasworker();
	void GatheringManager::splitWorkers();
	BuildingManager* buildingManager;
	void GatheringManager::allocateWorker(bool addToGas);
	
};

