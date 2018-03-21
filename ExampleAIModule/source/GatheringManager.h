#pragma once
#include <BWAPI.h>
class GatheringManager
{
public:
	GatheringManager();
	~GatheringManager();
	void GatheringManager::addWorker(const BWAPI::Unit* worker);
	void GatheringManager::executeOrders();
	const BWAPI::Unit* GatheringManager::removeWorker();
	void GatheringManager::addGasworker();
};

