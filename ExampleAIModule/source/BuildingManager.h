#pragma once
#include <BWAPI.h>
class BuildingManager
{

	bool isDesiredToTrainWorkers = false;
	bool isDesiredToTrainMarines = false;
	
public:
	BuildingManager();
	~BuildingManager();
	void BuildingManager::handleCommandCenter();

	void BuildingManager::addCommandCenter(const BWAPI::Unit* center);
	void BuildingManager::addBarracks(const BWAPI::Unit* center);
	void BuildingManager::buildingCreated(const BWAPI::Unit* u);
	void BuildingManager::executeOrders();
	void BuildingManager::setIsDesiredToTrainWorkers(bool buildWorkers);
	void BuildingManager::setIsDesiredToTrainMarines(bool trainWorkers);

};