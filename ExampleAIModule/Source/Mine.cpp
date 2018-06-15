#include "Mine.h"

using namespace BWAPI;

/**
* @file Mine.cpp
* @brief Class representing a vulture mine.
* @author Sebastian Arcos
*/

Mine::Mine(UnitInterface * u) : CustomUnit(u)
{
	if (u->getType() != UnitTypes::Terran_Vulture_Spider_Mine) {
		Broodwar->sendText("ERROR, tried to assign non-mine unit to mine object!!!");
	}
}

bool Mine::isOcupied()
{
	return false;
}

