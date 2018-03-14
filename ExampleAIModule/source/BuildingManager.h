#pragma once
#include <BWAPI.h>
class BuildingManager
{

	bool buildWorkers = true;
	
public:
	BuildingManager();
	~BuildingManager();
	void BuildingManager::handleCommandCenter();
	void BuildingManager::addCommandCenter(const BWAPI::Unit* center);
	void BuildingManager::executeOrders();
	void BuildingManager::setBuildWorkers(bool buildWorkers);
};