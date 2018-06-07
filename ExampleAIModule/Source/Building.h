#pragma once
#include <BWAPI.h>

class Building
{
public:
	Building(const BWAPI::Unit* u);
	const BWAPI::Unit* unit;
	BWAPI::UnitType Building::getType();
	bool buildAddon = true;
	BWAPI::UnitType addOnType;
	bool Building::isUnitValid();
	BWAPI::Position landingLocation;
	void Building::doCenterOrder();
};