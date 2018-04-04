#pragma once
#include <BWAPI.h>
class BuildingManager
{

	bool isDesiredToTrainWorkers = false;
	bool isDesiredToTrainMarines = false;
	bool isDesiredToTrainVultures = false;
	
public:
	BuildingManager();
	~BuildingManager();
	void BuildingManager::buildingCreated(const BWAPI::Unit* u);
	void BuildingManager::executeOrders();
	void BuildingManager::setIsDesiredToTrainWorkers(bool buildWorkers);
	void BuildingManager::setIsDesiredToTrainMarines(bool trainWorkers);
	void BuildingManager::setIsDesiredToTrainVultures(bool trainVultures);

};