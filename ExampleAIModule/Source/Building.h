#pragma once
#include <BWAPI.h>

class Building
{
public:
	Building(const BWAPI::Unit* u);
	const BWAPI::Unit* unit;
	BWAPI::UnitType Building::getType();
	bool shouldBuildAddon = false;
	BWAPI::UnitType addOnType;
	BWAPI::UnitType trainType;
	bool Building::isUnitValid();
	BWAPI::Position landingLocation;
	void Building::doCenterOrder();
	void Building::buildAddon();
	BWAPI::Position buildPos;
	BWAPI::Position originPos;
	void Building::initAddon(BWAPI::UnitType type);
};