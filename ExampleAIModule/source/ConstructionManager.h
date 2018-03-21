#pragma once
#include <BWAPI.h>
class ConstructionManager
{
public:
	ConstructionManager();
	~ConstructionManager();
	void ConstructionManager::createBuilding(BWAPI::UnitType building, const BWAPI::Unit* worker);
	const BWAPI::Unit* ConstructionManager::removeWorkersDoneConstructing();
	void ConstructionManager::executeOrders();
	void ConstructionManager::buildRefinery(const BWAPI::Unit* worker);
	const BWAPI::Unit* constructionsWorker;



};

