#pragma once
#include <BWAPI.h>
#include "BuildingManager.h"
#include "MapData.h"
class ScoutingManager
{
	
public:
	BWAPI::Position lastEnemyBuildingPosition;
	BWAPI::Position secondaryMineralFieldPosition;
	BWAPI::Position defendBasePosition;
	BWAPI::Position startingChokePosition;
	BWAPI::Position attackBasePosition;
	BWAPI::Position enemyChokePosition;
	bool secondaryMineralFieldFound; 
	bool enemyBaseFound = false;
	int corner = 0;
	std::list<const BWAPI::Unit*> scoutingUnits;
	ScoutingManager(BWAPI::Position startingPosition, MapData* mapData);
	~ScoutingManager();
	void ScoutingManager::addScout(const BWAPI::Unit* scout);
	void ScoutingManager::scoutCornersClockwise(const BWAPI::Unit* scout);
	void ScoutingManager::executeOrders();
	void ScoutingManager::onUnitDiscover(BWAPI::Unit unit);
	void ScoutingManager::setStartingCorner(BWAPI::Position pos);
	void setEnemyCorner(BWAPI::Position pos);
	void ScoutingManager::returnToBase(const BWAPI::Unit* unit); 
	BuildingManager* buildingManager;
	MapData* mapData;
};

