#pragma once
#include <BWAPI.h>

class Building
{
public:
	Building(const BWAPI::Unit* u);
	const BWAPI::Unit* unit;
	int time = 0;
	bool shouldBuildAddon = false;
	BWAPI::UnitType Building::getType();
	BWAPI::UnitType addOnType;
	BWAPI::UnitType trainType;
	BWAPI::Position buildPos;
	BWAPI::Position originPos;
	bool Building::isUnitValid();
	void Building::doCenterOrder();
	void Building::buildAddon();
	void Building::initAddon(BWAPI::UnitType type);
	
};