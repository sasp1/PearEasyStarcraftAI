#include "ScoutingManager.h"
#include <BWAPI.h>
#include <math.h>
#include <algorithm>
#include "BuildingManager.h"
#include "ConstructionManager.h"

using namespace BWAPI;
using namespace Filter;

/**
* @file ScoutingManager.cpp
* @brief Handles scouting of the map, and enemy base.
* @author Asger Græsholt
*/

//The map is 4096x4096 pixels (64^2)
BWAPI::Position lastEnemyBuildingPosition = BWAPI::Position(0, 0);
BWAPI::Position cornerCoords0= Position(100, 100);
BWAPI::Position cornerCoords1 = Position(4000, 100);
BWAPI::Position cornerCoords2 = Position(4000, 4000);
BWAPI::Position cornerCoords3 = Position(100, 4000);
int scoutedCorners = 0; 
int enemeyMarinesSpotted = 0;


ScoutingManager::ScoutingManager(BWAPI::Position startingPosition, MapData* mapData)
{
	this->mapData = mapData; 
	setStartingCorner(startingPosition);
	scoutingUnits.clear(); 
}

ScoutingManager::~ScoutingManager()
{
}

void ScoutingManager::addScout(BWAPI::UnitInterface* scout) {
	//Receive control of a new scoutUnit 
	scoutingUnits.push_back(scout);
}

void ScoutingManager::setStartingCorner(BWAPI::Position pos) {

	//Set key positions based on starting coordinate

	if (pos.getDistance(cornerCoords0) < 1000) {
		corner = 1;
		defendBasePosition = (*mapData).northwestAttack;
		startingChokePosition = (*mapData).northwestChokePointMid;
		expandBasePosition = (*mapData).northwestExpand;
		simCityTilePositionBarracks = (*mapData).northwestSimCityTilePositionBarracks;
		simCityTilePositionSupplyDepots1 = (*mapData).northwestSimCityTilePositionSupplyDepots1;
		simCityTilePositionSupplyDepots2 = (*mapData).northwestSimCityTilePositionSupplyDepots2;
	}
	else if (pos.getDistance(cornerCoords1) < 1000) {
		corner = 2;
		defendBasePosition = (*mapData).northeastAttack;
		startingChokePosition = (*mapData).northeastChokePointMid;
		expandBasePosition = (*mapData).northeastExpand;
		simCityTilePositionBarracks = (*mapData).northeastSimCityTilePositionBarracks;
		simCityTilePositionSupplyDepots1 = (*mapData).northeastSimCityTilePositionSupplyDepots1;
		simCityTilePositionSupplyDepots2 = (*mapData).northeastSimCityTilePositionSupplyDepots2;
	}
	else if (pos.getDistance(cornerCoords2) < 1000) {
		corner = 3; 
		defendBasePosition = (*mapData).southeastAttack;
		startingChokePosition = (*mapData).southeastChokePointMid;
		expandBasePosition = (*mapData).southeastExpand;
		simCityTilePositionBarracks = (*mapData).southeastSimCityTilePositionBarracks;
		simCityTilePositionSupplyDepots1 = (*mapData).southeastSimCityTilePositionSupplyDepots1;
		simCityTilePositionSupplyDepots2 = (*mapData).southeastSimCityTilePositionSupplyDepots2;
	}
	else {
		corner = 0;
		defendBasePosition = (*mapData).southwestAttack;
		startingChokePosition = (*mapData).southwestChokePointMid;
		expandBasePosition = (*mapData).southwestExpand;
		simCityTilePositionBarracks = (*mapData).southwestSimCityTilePositionBarracks;
		simCityTilePositionSupplyDepots1 = (*mapData).southwestSimCityTilePositionSupplyDepots1;
		simCityTilePositionSupplyDepots2 = (*mapData).southwestSimCityTilePositionSupplyDepots2;
	}
}

void ScoutingManager::setEnemyCorner(BWAPI::Position pos) {

	//Set key locations based on found enemy location

	if (pos.getDistance(cornerCoords0) < 1000) {
		attackBasePosition = (*mapData).northwestDefend;
		enemyChokePosition = (*mapData).northwestChokePointMid;
		inEnemyBasePosition = (*mapData).northwestMinePosition;
	}
	else if (pos.getDistance(cornerCoords1) < 1000) {
		corner = 2;
		attackBasePosition = (*mapData).northeastDefend;
		enemyChokePosition = (*mapData).northeastChokePointMid;
		inEnemyBasePosition = (*mapData).northeastMinePosition;
	}
	else if (pos.getDistance(cornerCoords2) < 1000) {
		corner = 3;
		attackBasePosition = (*mapData).southeastDefend;
		enemyChokePosition = (*mapData).southeastChokePointMid;
		inEnemyBasePosition = (*mapData).southeastMinePosition;
	}
	else {
		corner = 0;
		attackBasePosition = (*mapData).southwestDefend;
		enemyChokePosition = (*mapData).southwestChokePointMid;
		inEnemyBasePosition = (*mapData).southwestMinePosition;
	}
}

void ScoutingManager::scoutCornersClockwise(BWAPI::UnitInterface* scout) {
	//Scout clockwise each corner of the map

	//Set enemy corner as remaining corner, if 3 are scouted.
	if (scoutedCorners == 3 && enemyBaseFound == false) {
		 
		enemyBaseFound = true;
		if (corner == 0) lastEnemyBuildingPosition = cornerCoords0; 
		else if (corner == 1)lastEnemyBuildingPosition = cornerCoords1;
		else if (corner == 2)lastEnemyBuildingPosition = cornerCoords2;
		else lastEnemyBuildingPosition = cornerCoords3;

		setEnemyCorner(lastEnemyBuildingPosition);
	}

	//Send scout to corner
	if (corner == 0) {
		scout->move(cornerCoords0);
		checkIfCornerDiscovered(scout, cornerCoords0);
	}
	else if (corner == 1) {
		scout->move(cornerCoords1);
		checkIfCornerDiscovered(scout, cornerCoords1);
	}
	else if (corner == 2) {
		scout->move(cornerCoords2);
		checkIfCornerDiscovered(scout, cornerCoords2);
	}
	else {
		scout->move(cornerCoords3);
		checkIfCornerDiscovered(scout, cornerCoords3);
	}
}

void ScoutingManager::checkIfCornerDiscovered(BWAPI::UnitInterface* unit, BWAPI::Position cornerCord) {
	// Set corner as discovered if scout is nearby
	if (unit->getDistance(cornerCord) < 300) {
		corner = (corner + 1) % 4;
	}
}

bool ScoutingManager::isAvoidingNearbyEnemiesWithinRange(BWAPI::UnitInterface * unit, int range) {
	//Prepare enemy search
	bool enemiesInCriticalRange = false;
	BWAPI::Position centerOfMass = Position(0, 0);

	//Calculate evasion area if enemies are too close
	for (auto &eu : unit->getUnitsInRadius(range, IsEnemy)) {
		centerOfMass = centerOfMass + ((*eu).getPosition() - unit->getPosition());
		enemiesInCriticalRange = true;
	}

	//Move unit to evasion area
	BWAPI::Position movePosition = unit->getPosition() - centerOfMass;
	if (enemiesInCriticalRange) unit->move(movePosition);
	return enemiesInCriticalRange;
}

void ScoutingManager::executeOrders() {
	//Make unit scout enemy base, or unscouted corners.
	for (auto &u : scoutingUnits) {
		if (u->getHitPoints() == 0) {
			corner = (corner + 1) % 4;
			Broodwar->sendText("NEW CORNER");
		}

		if (!enemyBaseFound || !isAvoidingNearbyEnemiesWithinRange(u, 500)) {
			if (!enemyBaseFound) scoutCornersClockwise(u);
			else u->move(lastEnemyBuildingPosition);
		}
	}
}

void ScoutingManager::returnToBase(BWAPI::UnitInterface* unit) {
	//Return scout to base
	if (unit->getTargetPosition() != buildingManager->commandCenter->getPosition()) {
		unit->move(buildingManager->commandCenter->getPosition());
	}
}

void ScoutingManager::onUnitDiscover(BWAPI::Unit unit) {
	//If unit is enemy building, update enemy location.
	 if ((BWAPI::Broodwar->self()->isEnemy(unit->getPlayer()) && (unit->getType().isBuilding()))){
		enemyBaseFound = true;
		lastEnemyBuildingPosition = unit->getPosition();
		setEnemyCorner(lastEnemyBuildingPosition);
	 
}
	 //If unit is lurker, request scan at location.
	 if (unit->getType() == UnitTypes::Zerg_Lurker || unit->getType() == UnitTypes::Zerg_Lurker_Egg) {
		 enemyLurker = unit; 
		 enemyHasLurker = true;
		 Broodwar->sendText("Lurker at: %d, %d", unit->getPosition().x, unit->getPosition().y);
		 buildingManager->scan(unit->getPosition());
	 }
}