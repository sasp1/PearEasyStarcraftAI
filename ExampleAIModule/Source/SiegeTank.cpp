#include "SiegeTank.h"
using namespace BWAPI;
using namespace Filter;

SiegeTank::SiegeTank(const BWAPI::Unit* u) : CustomUnit(u)
{
	if ((*u)->getType() != UnitTypes::Terran_Siege_Tank_Tank_Mode) {
		Broodwar->sendText("ERROR, tried to assign non-siege-tank unit to siege-tank object!!!");
	}
}

SiegeTank::~SiegeTank()
{
}

bool SiegeTank::isUnitIdle() {
	return (*unit)->isIdle();
}

BWAPI::Unit SiegeTank::getUnit() {
	return *unit;
}


bool SiegeTank::isSiege() {
	return BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode == (*unit)->getType();
}

bool SiegeTank::isValid()
{
	return unit != NULL;
}
