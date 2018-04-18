#include "TimedUnit.h"
using namespace BWAPI;
using namespace Filter;

TimedUnit::TimedUnit(const BWAPI::Unit* u, int t) {
	unit = u;
	time = t;
}

bool TimedUnit::isOverTime(int t){

	return (time + t) < Broodwar->getFrameCount() ;

}

bool TimedUnit::isUnitIdle() {
	return (*unit)->isIdle();

}