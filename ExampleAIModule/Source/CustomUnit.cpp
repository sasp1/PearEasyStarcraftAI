#include "CustomUnit.h"

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
