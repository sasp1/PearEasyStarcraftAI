#include "SiegeTank.h"
using namespace BWAPI;
using namespace Filter;

SiegeTank::SiegeTank(const BWAPI::Unit* u)
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

bool SiegeTank::isUnitValid() {
	return tank != NULL;
}

bool SiegeTank::isSiege() {
	return BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode == (*tank)->getType();
}
