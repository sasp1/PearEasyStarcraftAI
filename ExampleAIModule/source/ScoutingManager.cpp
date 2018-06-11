#include "ScoutingManager.h"
#include <BWAPI.h>
#include <math.h>
#include <algorithm>
#include "BuildingManager.h"
#include "ConstructionManager.h"

using namespace BWAPI;
using namespace Filter;

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

void ScoutingManager::addScout(const BWAPI::Unit* scout) {
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
	}
	else if (pos.getDistance(cornerCoords1) < 1000) {
		corner = 2;
		defendBasePosition = (*mapData).northeastAttack;
		startingChokePosition = (*mapData).northeastChokePointMid;
		expandBasePosition = (*mapData).northeastExpand;
	}
	else if (pos.getDistance(cornerCoords2) < 1000) {
		corner = 3; 
		defendBasePosition = (*mapData).southeastAttack;
		startingChokePosition = (*mapData).southeastChokePointMid;
		expandBasePosition = (*mapData).southeastExpand;
	}
	else {
		corner = 0;
		defendBasePosition = (*mapData).southwestAttack;
		startingChokePosition = (*mapData).southwestChokePointMid;
		expandBasePosition = (*mapData).southwestExpand;
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

void ScoutingManager::scoutCornersClockwise(const BWAPI::Unit* scout) {
	//Scout clockwise each corner of the map

	//Set enemy corner as missing corner, if others are scouted.
	if (scoutedCorners == 3 && enemyBaseFound == false) {
		 
		enemyBaseFound = true;
		if (corner == 0) lastEnemyBuildingPosition = cornerCoords0; 
		else if (corner == 1)lastEnemyBuildingPosition = cornerCoords1;
		else if (corner == 2)lastEnemyBuildingPosition = cornerCoords2;
		else lastEnemyBuildingPosition = cornerCoords3;

		setEnemyCorner(lastEnemyBuildingPosition);
	}

	if (corner == 0) {
		(*scout)->move(cornerCoords0);
		checkIfCornerDiscovered(scout, cornerCoords0);
	}
	else if (corner == 1) {
		(*scout)->move(cornerCoords1);
		checkIfCornerDiscovered(scout, cornerCoords1);
	}
	else if (corner == 2) {
		(*scout)->move(cornerCoords2);
		checkIfCornerDiscovered(scout, cornerCoords2);
	}
	else {
		(*scout)->move(cornerCoords3);
		checkIfCornerDiscovered(scout, cornerCoords3);
	}
}

void ScoutingManager::checkIfCornerDiscovered(const BWAPI::Unit * unit, BWAPI::Position cornerCord) {
	if ((*unit)->getDistance(cornerCord) < 300) {
		corner = (corner + 1) % 4;
	}
}


bool ScoutingManager::isAvoidingNearbyEnemiesWithinRange(const BWAPI::Unit * unit, int range) {
	bool enemiesInCriticalRange = false;

	//otherwise juke as normal
	BWAPI::Position centerOfMass = Position(0, 0);
	for (auto &eu : (*unit)->getUnitsInRadius(range, IsEnemy)) {

		centerOfMass = centerOfMass + ((*eu).getPosition() - (*unit)->getPosition());
		enemiesInCriticalRange = true;

	}

	
	//Broodwar->sendText("Center of mass was: %d, %d", centerOfMass.x, centerOfMass.y);

	//int centerOfMassDistance = Position(0, 0).getDistance(centerOfMass);
	//centerOfMass.x = (centerOfMass.x * 150 / centerOfMassDistance);
	//centerOfMass.y = (centerOfMass.y * 150 / centerOfMassDistance);

	BWAPI::Position movePosition = (*unit)->getPosition() - centerOfMass;

	if (enemiesInCriticalRange) {
		(*unit)->move(movePosition);
		
	}

	return enemiesInCriticalRange;
	
}





void ScoutingManager::executeOrders() {

	for (auto &u : scoutingUnits) {
		if (!enemyBaseFound || !isAvoidingNearbyEnemiesWithinRange(u, 500)) {
			if (!enemyBaseFound) {
				scoutCornersClockwise(u);
				

			} else {
				
				(*u)->move(lastEnemyBuildingPosition);
			}

		}
	}
}

void ScoutingManager::returnToBase(const BWAPI::Unit* unit) {
	
	if ((*unit)->getTargetPosition() != (*buildingManager->commandCenter)->getPosition()) {
		(*unit)->move((*buildingManager->commandCenter)->getPosition());
	}

}

void ScoutingManager::onUnitDiscover(BWAPI::Unit unit)
{

	 if ((BWAPI::Broodwar->self()->isEnemy(unit->getPlayer()) && (unit->getType().isBuilding()))){
		//Broodwar->sendText("Enemy contruction found!");
		enemyBaseFound = true;
		lastEnemyBuildingPosition = unit->getPosition();
		setEnemyCorner(lastEnemyBuildingPosition);
	}

	 if (unit->getType() == UnitTypes::Zerg_Lurker || unit->getType() == UnitTypes::Zerg_Lurker_Egg) {
		 enemyLurker = unit; 
		 enemyHasLurker = true;
		 Broodwar->sendText("ENEMY HAS LURKER AT POSITION: %d, %d", unit->getPosition().x, unit->getPosition().y);
		 buildingManager->scan(unit->getPosition());

	 }

	 if (!secondaryMineralFieldFound && unit->getType() == UnitTypes::Resource_Mineral_Field && (*buildingManager->commandCenter)->getDistance(unit) > 350) {
		 secondaryMineralFieldFound = false; 
		 secondaryMineralFieldPosition = unit->getPosition(); 
		 /*Broodwar->sendText("Found secondary mineralField"); 
		 Broodwar->sendText("distance to mineral field%d", (*buildingManager->commandCenter)->getDistance(unit)); 
		 Broodwar->sendText("%d", (*buildingManager->commandCenter)->getPosition().x);
		 Broodwar->sendText("%d", (*buildingManager->commandCenter)->getPosition().y);
		 Broodwar->sendText("mineral x %d", unit->getPosition().x);
		 Broodwar->sendText("mineral y %d", unit->getPosition().y);*/
	 }
}