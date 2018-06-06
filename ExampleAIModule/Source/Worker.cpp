#include "Worker.h"
using namespace BWAPI;
using namespace Filter;

/*Workstates:
0: Collecting mineral, 1: Collecting gas, 2: Moving. 3: Request build, 4: Constructing, 5 Complete
*/
bool foundLoc = true;
int lX = 0;
int lY = 0;
int mX = 1;
int mY = 1;
int delta = -1;

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

bool Worker::handleBuild() {


	if ((*unit)->getBuildType() != BWAPI::UnitTypes::None && (*unit)->getTarget() != NULL)
		Broodwar->sendText("%s", (*unit)->getBuildType().c_str());

	if (buildOrder == BWAPI::UnitTypes::Terran_Command_Center)
	{
		if (workState == 2) {
			int dist = (*unit)->getDistance(pos);
			if (dist < 20) workState = 3;
			else (*unit)->move(pos);
		}
		else if (workState == 3) {
			if ((*unit)->isConstructing()) {
				workState = 4;
				time = Broodwar->getFrameCount();
			}
			else {
				tilePos = BWAPI::TilePosition(pos);
				TilePosition targetBuildLocation = Broodwar->getBuildLocation(buildOrder, tilePos);
				(*unit)->build(buildOrder, targetBuildLocation);
			}
		}
	}
	else if (buildOrder == BWAPI::UnitTypes::Terran_Refinery) {
		if (workState == 2) {
			int dist = (*unit)->getDistance(pos);
			if (dist < 2000) workState = 3;
			else (*unit)->move(pos);
		}
		else if (workState == 3) {
			if ((*unit)->isConstructing()) {
				workState = 4;
				time = Broodwar->getFrameCount();
			}
			else (*unit)->build(UnitTypes::Terran_Refinery, tilePos);
		}
	}
	else {
		if (workState == 2) workState = 3;
		else if (workState == 3) {
			if ((*unit)->isConstructing()) {
				workState = 4;
				time = Broodwar->getFrameCount();
			}
			else if (!foundLoc) {
				addToSpiral();
				tilePos = Broodwar->getBuildLocation(buildOrder, (*unit)->getTilePosition() + TilePosition(lX, lY));
				foundLoc = (*unit)->build(buildOrder, tilePos);
			}
			else {
				foundLoc = (*unit)->build(buildOrder, tilePos);
			}
		}
	}

	if (workState == 4) {
		int curFrame = Broodwar->getFrameCount();
		if ((*unit)->isConstructing() && curFrame > time + 600) workState = 5;
		else if (!(*unit)->isConstructing()) {
			workState = 3;
		}
	}
	return (workState == 5) && ((*unit)->isIdle());
}

bool Worker::isOcupied()
{
	return false;
}

void Worker::collect() {

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

void Worker::addToSpiral() {

	if (delta == 0) {
		mX += 1;
		mY += 1;
		lX = mX;
		lY = mY;
	}

	else if (delta == 1) lX = 0;
	else if (delta == 2) lX = -mX;
	else if (delta == 3) lY = 0;
	else if (delta == 4) lY = -mY;
	else if (delta == 5) lX = 0;
	else if (delta == 6) lX = mX;
	else if (delta == 7) lY = 0;
	else delta = 0;

	if (mX > 20) mX = 0;
	if (mY > 20) mY = 0;

	delta++;
}
