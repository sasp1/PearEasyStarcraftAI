#include "TimedUnit.h"
using namespace BWAPI;
using namespace Filter;

/*Workstates: 
0: Collecting mineral, 1: Collecting gas, 2: Constructing building. 
*/


TimedUnit::TimedUnit(const BWAPI::Unit* u, int t) {
	unit = u;
	time = t;
}

bool TimedUnit::isOverTime(int t){
	return (time + t) < Broodwar->getFrameCount() ;
}

bool TimedUnit::isUnitValid() {
	return (*unit) == NULL ;
}

bool TimedUnit::isUnitIdle() {
	return (*unit)->isIdle();
}