#pragma once
#include <BWAPI.h>

class Building
{
public:
	Building(const BWAPI::Unit* u);
	~Building();
	const BWAPI::Unit* unit;
	bool Building::isUnitIdle();
	BWAPI::UnitType Building::getType();
	bool buildAddon = true;
	bool Building::isUnitValid();

	BWAPI::Unit Building::getUnit();
};