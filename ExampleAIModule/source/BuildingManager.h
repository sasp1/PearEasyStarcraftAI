#pragma once
#include <BWAPI.h>
#include "Building.h"
#include "ScoutingManager.h"

class GatheringManager;

class BuildingManager
{

public:
	BuildingManager();
	~BuildingManager();
	void BuildingManager::buildingCreated(const BWAPI::Unit* u);
	void BuildingManager::executeOrders();
	void BuildingManager::setIsDesiredToTrainWorkers(bool buildWorkers);
	std::list<BWAPI::TechType> desiredResearchs;
	std::list<BWAPI::UnitType> desiredExpansion;
	std::list<BWAPI::UpgradeType> desiredUpgrades;
	std::list<Building*> buildings;
	std::list<Building*> commandCenters;
	bool isDesiredToTrainWorkers = false;
	bool addComSat = false;
	bool haveAcademy = false;
	bool startedBuild = false;
	const BWAPI::Unit* commandCenter;
	BWAPI::UnitType factoryBuild;
	BWAPI::UnitType barrackBuild;
	int totalMachineShops = 0;
	GatheringManager* gatheringManager;
	ScoutingManager* scoutingManager;
	bool BuildingManager::scan(BWAPI::Position pos);
};