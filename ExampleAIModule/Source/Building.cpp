#include "Building.h"
using namespace BWAPI;
using namespace Filter;

Building::Building(const BWAPI::Unit* u) {
	unit = u;
}

BWAPI::UnitType Building::getType() {
	return (*unit)->getType();
}

bool Building::isUnitIdle() {
	return (*unit)->isIdle();
}

const BWAPI::Unit* Building::getUnit() {
	return unit;
}

bool Building::isUnitValid() {
	return unit != NULL;
}
