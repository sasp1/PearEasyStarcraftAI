#pragma once
#include <BWAPI.h>

class Building
{
public:
	Building(BWAPI::UnitInterface* u);
	BWAPI::UnitInterface* unit;
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