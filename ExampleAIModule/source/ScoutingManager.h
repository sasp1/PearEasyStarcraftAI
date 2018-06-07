#pragma once
#include <BWAPI.h>
#include "MapData.h"
using namespace BWAPI; 
class BuildingManager;

class ScoutingManager
{
	
public:
	BWAPI::Position lastEnemyBuildingPosition;
	BWAPI::Position secondaryMineralFieldPosition;
	BWAPI::Position defendBasePosition;
	BWAPI::Position startingChokePosition;
	BWAPI::Position attackBasePosition;
	BWAPI::Position enemyChokePosition;
	BWAPI::Position expandBasePosition;
	Position inEnemyBasePosition;
	Position defendInBasePosition; 
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
	bool enemyHasLurker = false; 
	Unit enemyLurker = NULL;
	BuildingManager* buildingManager;
	MapData* mapData;
};

