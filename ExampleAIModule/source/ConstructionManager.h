#pragma once
#include <BWAPI.h>
class ConstructionManager
{
public:
	ConstructionManager();
	~ConstructionManager();
	void ConstructionManager::createBuilding(BWAPI::UnitType building, const BWAPI::Unit* worker);
};

