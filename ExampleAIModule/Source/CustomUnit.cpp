#include "CustomUnit.h"

/**
* @file CustomUnit.cpp
* @brief Parent class used to represent unit in unit-specifc child-classes.
* @author Sebastian Arcos Specht <@student.dtu.dk>
*/

bool CustomUnit::isValid()
{
	return !(*unit == NULL);
}

CustomUnit::CustomUnit(const BWAPI::Unit * u) {
	unit = u;
	targetEnemy = NULL;
}

bool CustomUnit::unitIsNewTarget(BWAPI::Unit unit) {
	return  targetEnemy == NULL || ((unit)->getID() != (targetEnemy)->getID());
}
