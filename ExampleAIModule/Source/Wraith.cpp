#include "Wraith.h"

using namespace BWAPI;

Wraith::Wraith(const Unit * u) : CustomUnit(u)
{
	if ((*u)->getType() != UnitTypes::Terran_Wraith)
		Broodwar->sendText("ERROR, tried to assign non-wraith unit to wraith object!!!");
}

bool Wraith::isOcupied()
{
	return false;
}

