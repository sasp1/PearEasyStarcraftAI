#include "ScoutingManager.h"
#include <BWAPI.h>
#include <math.h>
#include <algorithm>

using namespace BWAPI;
using namespace Filter;

// std::list<const BWAPI::Unit*> scoutingUnits;
bool enemyBaseFound = false;
BWAPI::Position lastEnemyBuildingPosition;
//The map is 4096x4096 pixels (64^2)
int corner = 0;
int enemeyMarinesSpotted = 0; 
BWAPI::Position cornerCoords0= Position(100, 100);
BWAPI::Position cornerCoords1 = Position(4000, 100);
BWAPI::Position cornerCoords2 = Position(4000, 4000);
BWAPI::Position cornerCoords3 = Position(100, 4000);


ScoutingManager::ScoutingManager()
{
	lastEnemyBuildingPosition = BWAPI::Position(0,0);
	setStartingCorner(BWAPI::Position(BWAPI::Broodwar->self()->getStartLocation()));
}

ScoutingManager::~ScoutingManager()
{
}

void ScoutingManager::addScout(const BWAPI::Unit* scout) {
	//Receive control of a new scoutUnit
	scoutingUnits.push_back(scout);
	
}

void ScoutingManager::setStartingCorner(BWAPI::Position pos) {
	
	if (pos.getDistance(cornerCoords0) < 1000) {
		corner = 1; 
	}
	else if (pos.getDistance(cornerCoords1) < 1000) {
		corner = 2; 
	}
	else if (pos.getDistance(cornerCoords2) < 1000) {
		corner = 3; 
	}
	else {
		corner = 0;
	}
}

void ScoutingManager::scoutCornersClockwise(const BWAPI::Unit* scout) {
	//Scout clockwise each corner of the map
	
	if (corner == 0) {
		(*scout)->move(cornerCoords0);
	}
	else if (corner == 1) {
		(*scout)->move(cornerCoords1);
	}
	else if (corner == 2) {
		(*scout)->move(cornerCoords2);
	}
	else {
		(*scout)->move(cornerCoords3);
	}
	corner = (corner + 1) % 4;
	}


void ScoutingManager::executeOrders() {

	for (auto &u : scoutingUnits)
	{
		if ((*u)->isIdle()) {
			scoutCornersClockwise(u);
		}	

		if ((*u)->isUnderAttack() && enemyBaseFound) {
			returnToBase(u); 
		}
	}
}

void ScoutingManager::returnToBase(const BWAPI::Unit* unit) {
	
	if ((*unit)->getTargetPosition() != (*buildingManager->commandCenter)->getPosition()) {
		(*unit)->move((*buildingManager->commandCenter)->getPosition());
		Broodwar->sendText("Scouting unit is returning to the base");
	}

}

void ScoutingManager::onUnitDiscover(BWAPI::Unit unit)
{
	 if ((BWAPI::Broodwar->self()->isEnemy(unit->getPlayer()) && (unit->getType().isBuilding()))){
		Broodwar->sendText("FJENDE!");
		enemyBaseFound = true;
		lastEnemyBuildingPosition = unit->getPosition();
	}
}