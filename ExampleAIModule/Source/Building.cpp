#include "SpiralSearch.h"
#include "Building.h"
using namespace BWAPI;
using namespace Filter;

SpiralSearch* spiral;
bool startedBuild = false;

int buildState = 0;
//Buildstates
//0: Attempt addon, 1: Find build loc, 2:Lift off 3: Move and land, 4:Landing, 5:Building, 6:Done

Building::Building(const BWAPI::Unit* u) {
	unit = u;
}

BWAPI::UnitType Building::getType() {
	return (*unit)->getType();
}

bool Building::isUnitValid() {
	return unit != NULL;
}

void Building::initAddon(BWAPI::UnitType type) {
	addOnType = type;
	spiral = new SpiralSearch(5000);
	originPos = Position((*unit)->getPosition());
	buildPos = Position(0, 0);
}

void Building::buildAddon() {

	if ((*unit)->getAddon() != NULL) buildState = 5;

	if (buildState == 0) {	

		if (startedBuild && time + 30 < Broodwar->getFrameCount()) {

			if ((*unit)->isConstructing() || (*unit)->getAddon() != NULL) buildState = 5;
			else if ((*unit)->isIdle()) buildState = 1;
	
		}

		//Can we afford building, and is building idle
		if ((Broodwar->self()->minerals() > addOnType.mineralPrice()) && (Broodwar->self()->gas() > addOnType.gasPrice()) && (*unit)->isIdle() && !startedBuild) {
			//Attempt construction at location. Change state on result.
			(*unit)->buildAddon(addOnType);
			startedBuild = true;
			time = Broodwar->getFrameCount();
			
		}	
	}
	if (buildState == 1) {
		//Find suitable build location
		if ((*unit)->isIdle()) {
			startedBuild = false;
			buildPos = originPos + spiral->getNextPos();
			Broodwar->drawCircleMap(buildPos, 40, Colors::Red, true);
			if (Broodwar->canBuildHere(TilePosition(buildPos), addOnType, (*unit))) buildState = 2;
		}
	}
	if (buildState == 2) {
		//Lift off from ground
		if ((*unit)->isFlying()) buildState = 3;
		else if ((*unit)->isIdle()) (*unit)->lift();
	}

	if (buildState == 3) {
		//Move to new location and land
		if ((*unit)->isLifted()) {
			if (!(*unit)->land(TilePosition(buildPos))) buildState = 1;
		}
		else buildState = 4;
	}
	if (buildState == 4) {
		//If landed, restart procedure
		if ((*unit)->isIdle()) {
			buildState = 0;
			originPos = Position((*unit)->getPosition());
			buildPos = Position(0, 0);
		}
	}
	if (buildState == 5) shouldBuildAddon = false;

}

void Building::doCenterOrder() {
	if ((*unit)->isIdle()) {
		if (shouldBuildAddon && (*unit)->getAddon() == NULL) buildAddon();
		else (*unit)->train(trainType);
	}
}