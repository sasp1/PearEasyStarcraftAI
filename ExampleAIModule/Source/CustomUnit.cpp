#include "CustomUnit.h"

/**
* @file CustomUnit.cpp
* @brief Parent class used to represent unit in unit-specifc child-classes.
* @author Sebastian Arcos Specht
*/

bool CustomUnit::isValid()
{
	return !(unit == NULL);
}

CustomUnit::CustomUnit(BWAPI::UnitInterface * u) {
	unit = u;
	targetEnemy = NULL;
}

bool CustomUnit::unitIsNewTarget(BWAPI::UnitInterface* unit) {
	return  targetEnemy == NULL || ((unit)->getID() != (targetEnemy)->getID());
}
