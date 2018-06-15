#include "Wraith.h"

using namespace BWAPI;

/**
* @file Marine.cpp
* @brief Class representing a wraith unit.
* @author Thomas Heshe
*/

Wraith::Wraith(UnitInterface * u) : CustomUnit(u)
{
	if (u->getType() != UnitTypes::Terran_Wraith)
		Broodwar->sendText("ERROR, tried to assign non-wraith unit to wraith object!!!");
}

bool Wraith::isOcupied()
{
	return false;
}

