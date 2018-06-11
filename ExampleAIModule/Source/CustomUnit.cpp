#include "CustomUnit.h"

bool CustomUnit::isValid()
{
	if (*unit == NULL)
		return false;
	//if ((*unit)->getHitPoints() == 0)
	//	return false;
	return true;

}

CustomUnit::CustomUnit(const BWAPI::Unit * u)
{
	unit = u;
	targetEnemy = NULL;

}

bool CustomUnit::unitIsNewTarget(BWAPI::Unit unit) {
	return  targetEnemy == NULL || ((unit)->getID() != (targetEnemy)->getID());
}
