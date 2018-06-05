#pragma once
#include <BWAPI.h>

class Building
{
public:
	Building(const BWAPI::Unit* u);
	const BWAPI::Unit* unit;
	bool Building::isUnitIdle();
	BWAPI::UnitType Building::getType();
	bool buildAddon = true;
	bool Building::isUnitValid();
	const BWAPI::Unit* Building::getUnit();
};