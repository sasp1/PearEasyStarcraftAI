#include "Worker.h"
#include "SpiralSearch.h"
using namespace BWAPI;
using namespace Filter;

/*Workstates:
Gathering - 0: Collecting mineral, 1: Collecting gas,
Building - 0: Moving, 1: Attempt build, 2: Find build loc, 3: Scout, 4:Building, 5:Done
*/
bool foundLoc = true;
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
	//Replace worker with a new, and continue to construct assigned building
	unit = worker;
	if (construct != NULL) {
		(*unit)->stop();
		(*unit)->repair(*construct);
		time = Broodwar->getFrameCount();
	}
}

void Worker::initBuild(BWAPI::UnitType type, BWAPI::Position pos) {
	//Save building type, and positions
	buildOrder = type;
	spiral = new SpiralSearch(3000);
	originPos = pos;
	buildPos = pos;
	tilePos = TilePosition(buildPos);
	workState = 0;
}

bool Worker::handleBuild() {

	//State for moving to buildsite
	if (workState == 0 && (*unit)->isIdle()) {
		//Move close to origin point and attempt construction
		if ((*unit)->getDistance(originPos) < 150) {
			buildPos = originPos;
			workState = 1;
		}
		else (*unit)->move(originPos);
	}

	//State for attempting construction
	if (workState == 1) {
		// If we are constructing, set as can be finished
		if ((*unit)->isConstructing()) {
			workState = 4;
			time = Broodwar->getFrameCount();
		}
		//If position is invalid, do spiral search for new location.
		else if (!hasLoc) {
			buildPos = originPos + spiral->getNextPos();
			Broodwar->drawCircleMap(buildPos, 30, Colors::Green, true);
			
			//Try to validate new locations
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
		//If position is valid, attempt build at that location
		else hasLoc = (*unit)->build(buildOrder, tilePos);	
	}

	//Evaluation state for if building is under construction for a longer period of time.
	if (workState == 4) {
		//If certain time has passed, and unit is constructing, consider building as being completed. Else try construction again.
		if ((*unit)->isConstructing() && Broodwar->getFrameCount() > (time + 500)) workState = 5;
		else if (!(*unit)->isConstructing()) {
			workState = 1;
		}
	}

	//If building is considered complete, and unit is idle, construction is complete.
	return (workState == 5 && (*unit)->isIdle());
}

void Worker::collect() {
	//Check if unit is valid
	if (unit == NULL || *unit == NULL) {
		return;
	}
	
	//Collect minerals, or return cargo.
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
	//Collect gas or return cargo
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