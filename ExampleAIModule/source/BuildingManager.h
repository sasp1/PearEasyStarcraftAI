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
	void BuildingManager::draw();
	void BuildingManager::setIsDesiredToTrainWorkers(bool buildWorkers);
	bool BuildingManager::scan(BWAPI::Position pos);
	std::list<BWAPI::TechType> desiredResearchs;
	std::list<BWAPI::UnitType> desiredExpansion;
	std::list<BWAPI::UpgradeType> desiredUpgrades;
	std::list<Building*> buildings;
	std::list<Building*> commandCenters;
	int drawTimer = -1;
	int totalMachineShops = 0;
	bool isDesiredToTrainWorkers = false;
	bool addComSat = false;
	bool haveAcademy = false;
	bool startedBuild = false;
	const BWAPI::Unit* commandCenter;
	BWAPI::UnitType factoryBuild;
	BWAPI::UnitType barrackBuild;
	BWAPI::UnitType starportBuild;
	BWAPI::Position scanPoint;
	GatheringManager* gatheringManager;
	ScoutingManager* scoutingManager;
	
};