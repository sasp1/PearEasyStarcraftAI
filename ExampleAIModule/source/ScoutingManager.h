#pragma once
#include <BWAPI.h>
#include "MapData.h"
using namespace BWAPI; 
class BuildingManager;

class ScoutingManager
{
	
public:
	BWAPI::Position lastEnemyBuildingPosition = BWAPI::Position(0, 0);
	BWAPI::Position secondaryMineralFieldPosition = BWAPI::Position(0, 0);
	BWAPI::Position defendBasePosition = BWAPI::Position(0, 0);
	BWAPI::Position startingChokePosition = BWAPI::Position(0, 0);
	BWAPI::Position attackBasePosition = BWAPI::Position(0, 0);
	BWAPI::Position enemyChokePosition = BWAPI::Position(0, 0);
	BWAPI::Position expandBasePosition = BWAPI::Position(0, 0);
	TilePosition SimCityTilePositionBarracks = TilePosition(0,0);
	TilePosition SimCityTilePositionSupplyDepots1 = TilePosition(0, 0);
	TilePosition SimCityTilePositionSupplyDepots2 = TilePosition(0, 0);
	Position inEnemyBasePosition = BWAPI::Position(0, 0);;
	Position defendInBasePosition; 
	Unit enemyLurker = NULL;
	BuildingManager* buildingManager;
	MapData* mapData;
	bool secondaryMineralFieldFound; 
	bool enemyBaseFound = false;
	bool enemyHasLurker = false;
	int corner = 0;
	std::list<const BWAPI::Unit*> scoutingUnits;
	ScoutingManager(BWAPI::Position startingPosition, MapData* mapData);
	~ScoutingManager();
	void setEnemyCorner(BWAPI::Position pos);
	void ScoutingManager::addScout(const BWAPI::Unit* scout);
	void ScoutingManager::scoutCornersClockwise(const BWAPI::Unit* scout);
	void ScoutingManager::checkIfCornerDiscovered(const BWAPI::Unit * unit, BWAPI::Position cornerCord);
	void ScoutingManager::executeOrders();
	void ScoutingManager::onUnitDiscover(BWAPI::Unit unit);
	void ScoutingManager::setStartingCorner(BWAPI::Position pos);
	void ScoutingManager::returnToBase(const BWAPI::Unit* unit); 
	bool ScoutingManager::isAvoidingNearbyEnemiesWithinRange(const BWAPI::Unit * unit, int range);

};

