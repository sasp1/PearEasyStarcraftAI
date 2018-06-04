#pragma once
#include <BWAPI.h>
class BuildingManager;

class GatheringManager
{
public:
	std::list<const BWAPI::Unit*> mineralWorkers;
	std::list<const BWAPI::Unit*> gasWorkers;
	GatheringManager();
	~GatheringManager();
	void GatheringManager::addWorker(const BWAPI::Unit* worker);
	void GatheringManager::executeOrders();
	const BWAPI::Unit* GatheringManager::removeWorker();
	void GatheringManager::addGasworker();
	void GatheringManager::splitWorkers(int centers);
	BuildingManager* buildingManager;
	
};

