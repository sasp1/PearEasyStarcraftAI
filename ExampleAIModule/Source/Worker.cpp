#include "Worker.h"
#include "SpiralSearch.h"
using namespace BWAPI;
using namespace Filter;

/*Workstates:
Gathering - 0: Collecting mineral, 1: Collecting gas,
Building - 0: Moving, 1: Attempt build, 2: Find build loc, 3: Scout, 4:Building, 5:Done
*/
bool foundLoc = true;
int lX = 0;
int lY = 0;
int mX = 1;
int mY = 1;
int delta = -1;
bool hasLoc = true;
bool isBuild = false;

Worker::Worker(const BWAPI::Unit* u) : CustomUnit(u) {
}

bool Worker::isUnitIdle() {
	return (*unit)->isIdle();
}

void Worker::stop() {
	(*unit)->stop();
}

void Worker::replaceUnit(const BWAPI::Unit* worker) {
	unit = worker;
	if (construct != NULL) {
		(*unit)->stop();
		(*unit)->repair(*construct);
		time = Broodwar->getFrameCount();
	}
}

void Worker::initBuild(BWAPI::UnitType type, BWAPI::Position pos) {
	buildOrder = type;
	spiral = new SpiralSearch(3000);
	originPos = pos;
	buildPos = pos;
	tilePos = TilePosition(buildPos);
	workState = 0;
	//if (type == UnitTypes::Terran_Refinery) workState = 1;
}

bool Worker::handleBuild() {

	//Move to origin point
	if (workState == 0 && (*unit)->isIdle()) {

		if(originPos == BWAPI::Position(0,0))  Broodwar->sendText("0,0");

		if ((*unit)->getDistance(originPos) < 150) {
			workState = 1;
			buildPos = originPos;
		}
		else (*unit)->move(originPos);
	}

	//Attempt to construct building
	if (workState == 1) {

		if ((*unit)->isConstructing()) {
			workState = 4;
			time = Broodwar->getFrameCount();
		}
		else if (!hasLoc) {
			buildPos = originPos + spiral->getNextPos();
			Broodwar->drawCircleMap(buildPos, 30, Colors::Green, true);

			tilePos = Broodwar->getBuildLocation(buildOrder, TilePosition(buildPos));
			hasLoc = (*unit)->build(buildOrder, tilePos);
			if (!hasLoc) {
				hasLoc = (*unit)->build(buildOrder, TilePosition(buildPos));
				tilePos = TilePosition(buildPos);
			}
			if (!hasLoc) {
				hasLoc = (*unit)->build(buildOrder, TilePosition(originPos));
				tilePos = TilePosition(originPos);
			}
		}
			 else hasLoc = (*unit)->build(buildOrder, tilePos);	
	}

	//Check if ready to remove
	if (workState == 4) {
		if ((*unit)->isConstructing() && Broodwar->getFrameCount() > (time + 500)) workState = 5;
		else if (!(*unit)->isConstructing()) {
			workState = 1;
		}
	}

	 if (workState == 5 && (*unit)->isIdle()) {
		 return true;
	 }
	 else return false;
}

void Worker::collect() {
	if (unit == NULL || *unit == NULL) {
		Broodwar->sendText("ERROR UNIT WAS NULL"); 
		return;
	}
	
	if (workState == 0 && (center != NULL)) {
		BWAPI::Unit mine = (*center)->getClosestUnit(IsMineralField);
		
		if ((*unit)->isIdle()) {
			if ((*unit)->isCarryingGas() || (*unit)->isCarryingMinerals())
				(*unit)->returnCargo();
			else (*unit)->gather(mine);
		}
		else if ((*unit)->isCarryingGas()) {
			(*unit)->returnCargo();
		}
	}
	else if (workState == 1 && gas != NULL) {
		if ((*unit)->isIdle()) {
			if ((*unit)->isCarryingGas() || (*unit)->isCarryingMinerals())
				(*unit)->returnCargo();
			else if (gas != NULL) {
				(*unit)->rightClick(*gas);
			}
		}
		else if ((*unit)->isCarryingMinerals()) {
			(*unit)->returnCargo();
		}
	}
}

bool Worker::isOcupied() {
	return false;
}