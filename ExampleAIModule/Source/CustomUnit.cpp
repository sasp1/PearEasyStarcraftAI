#include "CustomUnit.h"

bool CustomUnit::isValid()
{
	return (unit != NULL) && ((*unit)->getHitPoints() > 0);
}

CustomUnit::CustomUnit(const BWAPI::Unit * u)
{
	unit = u; 
	targetEnemy = NULL;

}

bool CustomUnit::unitIsNewTarget(BWAPI::Unit unit) {
	return  targetEnemy == NULL || ((unit)->getID() != (targetEnemy)->getID());
}
