#include "Worker.h"
using namespace BWAPI;
using namespace Filter;

/*Workstates:
0: Collecting mineral, 1: Collecting gas, 2: Constructing building.
*/


Worker::Worker(const BWAPI::Unit* u) : CustomUnit(u) {
}

bool Worker::isOverTime(int t) {
	return (time + t) < Broodwar->getFrameCount();
}

bool Worker::isUnitIdle() {
	return (*unit)->isIdle();
}

void Worker::updateCommandCenter(const BWAPI::Unit cc) {

}

void Worker::collect() {

	if (center != NULL) {

		if (workState == 0) {
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
		else if (workState == 1) {
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
	else Broodwar->sendText("Idle");
}
