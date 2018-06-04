#include "SiegeTank.h"
using namespace BWAPI;
using namespace Filter;

SiegeTank::SiegeTank(const BWAPI::Unit* u) : CustomUnit(u)
{
	tank = u;
}

SiegeTank::~SiegeTank()
{
}

bool SiegeTank::isUnitIdle() {
	return (*tank)->isIdle();
}

BWAPI::Unit SiegeTank::getUnit() {
	return *tank;
}


bool SiegeTank::isSiege() {
	return BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode == (*tank)->getType();
}

bool SiegeTank::isValid()
{
	return tank != NULL;
}
