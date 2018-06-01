#pragma once
#include <BWAPI.h>
class BuildingManager
{

public:
	BuildingManager();
	~BuildingManager();
	void BuildingManager::buildingCreated(const BWAPI::Unit* u);
	void BuildingManager::executeOrders();
	void BuildingManager::setIsDesiredToTrainWorkers(bool buildWorkers);
	BWAPI::TilePosition BuildingManager::spiralSearch();
	bool expandFactory = true;
	std::list<BWAPI::TechType> desiredResearchs;
	std::list<BWAPI::UpgradeType> desiredUpgrades;
	bool isDesiredToTrainWorkers = false;
	const BWAPI::Unit* commandCenter;
	BWAPI::UnitType factoryBuild;
	BWAPI::UnitType barrackBuild;

};