#include "SpiralSearch.h"
#include "Building.h"
using namespace BWAPI;
using namespace Filter;

SpiralSearch* spiral;

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

	if (buildState == 0) {	
		//Broodwar->sendText("State0");
		//Can we afford building, and is building idle
		if ((Broodwar->self()->minerals() > addOnType.mineralPrice()) && (Broodwar->self()->gas() > addOnType.gasPrice()) && (*unit)->isIdle()) {
			//Attempt construction at location. Change state on result.
			(*unit)->buildAddon(addOnType);
			Broodwar->sendText(Broodwar->getLastError().c_str());
			if ((*unit)->isConstructing()) buildState = 5;
			else buildState = 1;
		}	
	}
	if (buildState == 1) {
		//Broodwar->sendText("State1");
		//Find suitable build location
		if ((*unit)->isIdle()) {
			buildPos = originPos + spiral->getNextPos();
			Broodwar->drawCircleMap(buildPos, 40, Colors::Red, true);
			if (Broodwar->canBuildHere(TilePosition(buildPos), addOnType, (*unit))) buildState = 2;
		}
	}
	if (buildState == 2) {
		//Broodwar->sendText("State2");
		//Lift off from ground
		if ((*unit)->isFlying()) buildState = 3;
		else if ((*unit)->isIdle()) (*unit)->lift();
	}

	if (buildState == 3) {
		//Broodwar->sendText("State3");
		//Move to new location and land
		if ((*unit)->isLifted()) (*unit)->land(TilePosition(buildPos));
		else buildState = 4;
	}
	if (buildState == 4) {
		//Broodwar->sendText("State4");
		//If landed, restart procedure
		if ((*unit)->isIdle()) {
			buildState = 0;
			originPos = Position((*unit)->getPosition());
			buildPos = Position(0, 0);
		}
	}
}

void Building::doCenterOrder() {
	if ((*unit)->isIdle()) {
		if (shouldBuildAddon && (*unit)->getAddon() == NULL) buildAddon();
		else (*unit)->train(trainType);
	}
}