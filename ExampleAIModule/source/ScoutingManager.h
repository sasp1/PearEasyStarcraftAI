#pragma once
#include <BWAPI.h>
#include "BuildingManager.h"
class ScoutingManager
{
	
public:
	BWAPI::Position lastEnemyBuildingPosition;
	BWAPI::Position secondaryMineralFieldPosition; 
	bool secondaryMineralFieldFound; 
	int corner = 0;
	std::list<const BWAPI::Unit*> scoutingUnits;
	ScoutingManager(BWAPI::Position startingPosition);
	~ScoutingManager();
	void ScoutingManager::addScout(const BWAPI::Unit* scout);
	void ScoutingManager::scoutCornersClockwise(const BWAPI::Unit* scout);
	void ScoutingManager::executeOrders();
	void ScoutingManager::onUnitDiscover(BWAPI::Unit unit);
	void ScoutingManager::setStartingCorner(BWAPI::Position pos);
	void ScoutingManager::returnToBase(const BWAPI::Unit* unit); 
	BuildingManager* buildingManager;
};

