#include "Marine.h"

using namespace BWAPI; 



Marine::Marine(const Unit * u) : CustomUnit(u) 
{
	if ((*u)->getType() != UnitTypes::Terran_Marine) {
		Broodwar->sendText("ERROR, tried to assign non-marine unit to marine object!!!");
	}
}

bool Marine::isOcupied()
{
	return false;
}




