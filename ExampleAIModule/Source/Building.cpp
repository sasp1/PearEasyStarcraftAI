#include "SpiralSearch.h"
#include "Building.h"
using namespace BWAPI;
using namespace Filter;


SpiralSearch* spiral; 
//Buildstates
//0: Attempt addon, 1: Find build loc, 2:Lift off 3: Move and land, 4:Landing, 5:Building, 6:Done


/**
* @file Building.cpp
* @brief Class that represent an instance of an owned building.
* Handles construction of addons, and training of units.
* @author Daniel Fjordhøj <s133198@student.dtu.dk>
*/
Building::Building(BWAPI::UnitInterface* u) {
	unit = u;
}

BWAPI::UnitType Building::getType() {
	return unit->getType();
}

bool Building::isUnitValid() {
	return unit != NULL;
}

void Building::initAddon(BWAPI::UnitType type) {
	//Saves current position, and addon type.
	addOnType = type;
	spiral = new SpiralSearch(5000);
	originPos = Position(unit->getPosition());
	buildPos = Position(0, 0);
}

void Building::buildAddon(Game* broodWar, int frameCount, int mineralsAvailable, int gasAvailable) {
	//If we have addon, set as finished
	if (unit->getAddon() != NULL) buildState = 5;

	//State for attempting construction of addon
	if (buildState == 0) {	

		//If we are constructing, set as finished, else search for new location
		if (startedBuild && time + 30 < frameCount) {
			if (unit->isConstructing() || unit->getAddon() != NULL) buildState = 5;
			else if (unit->isIdle()) buildState = 1;
		}

		//Attempt construction if we can afford addon, and is building idle
		if ((mineralsAvailable > addOnType.mineralPrice()) && (gasAvailable > addOnType.gasPrice()) && unit->isIdle() && !startedBuild) {
			unit->buildAddon(addOnType);
			startedBuild = true;
			time = frameCount;
		}	
	}
	//State for finding  a new build location
	if (buildState == 1) {
		//If location is ok, move to new location, else spiral out and try next location
		if (unit->isIdle()) {
			startedBuild = false;
			buildPos = originPos + spiral->getNextPos();
			broodWar->drawCircleMap(buildPos, 40, Colors::Red, true);
			if (broodWar->canBuildHere(TilePosition(buildPos), addOnType, unit)) buildState = 2;
		}
	}
	//State for taking off from ground
	if (buildState == 2) {
		if (unit->isFlying()) buildState = 3;
		else if (unit->isIdle())  unit->lift();
	}
	//State for moving to new location
	if (buildState == 3) {
		//Attempt landing at new location
		if (unit->isLifted()) {
			if (!unit->land(TilePosition(buildPos))) buildState = 1;
		}
		else buildState = 4;
	}
	//State for re-initializing at new location
	if (buildState == 4) {
		//If landed, set new location as new origin point and retry construction 
		if (unit->isIdle()) {
			buildState = 0;
			originPos = Position(unit->getPosition());
			buildPos = Position(0, 0);
		}
	}
	//Finished state.
	if (buildState == 5) shouldBuildAddon = false;
}

void Building::doCenterOrder() {
	//Build addon if requested, else build unit.
	if (unit->isIdle()) {
		if (shouldBuildAddon && unit->getAddon() == NULL) buildAddon(BroodwarPtr, Broodwar->getFrameCount(), Broodwar->self()->minerals(), Broodwar->self()->gas());
		else unit->train(trainType);
	}
}