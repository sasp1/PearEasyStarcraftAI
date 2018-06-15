#include "Marine.h"

using namespace BWAPI; 

/**
* @file Marine.cpp
* @brief Class representing a marine unit.
* @author Asger Græsholt
*/

Marine::Marine(UnitInterface * u) : CustomUnit(u) 
{
	if (u->getType() != UnitTypes::Terran_Marine) {
		Broodwar->sendText("ERROR, tried to assign non-marine unit to marine object!!!");
	}
}

bool Marine::isOcupied()
{
	return false;
}




