#pragma once
#include <BWAPI.h>
#include "BWAPI/Game.h"



class Building
{
public:
	Building(BWAPI::UnitInterface* u);
	BWAPI::UnitInterface* unit;
	int time = 0;
	int buildState = 0;
	bool startedBuild = false;
	bool shouldBuildAddon = false;
	BWAPI::UnitType Building::getType();
	BWAPI::UnitType addOnType;
	BWAPI::UnitType trainType;
	BWAPI::Position buildPos;
	BWAPI::Position originPos;
	bool Building::isUnitValid();
	void Building::doCenterOrder();
	void Building::buildAddon(BWAPI::Game* broodWar, int frameCount, int mineralsAvailable, int gasAvailable);
	void Building::initAddon(BWAPI::UnitType type);
	
};