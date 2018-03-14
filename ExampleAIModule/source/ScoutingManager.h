#pragma once
#include <BWAPI.h>
class ScoutingManager
{
public:
	std::list<const BWAPI::Unit*> scoutingUnits;
	ScoutingManager();
	~ScoutingManager();
	void ScoutingManager::addScout(const BWAPI::Unit* scout);
	void ScoutingManager::moveScoutToTile(const BWAPI::Unit* scout, int tileNr, int tileScale);
	void ScoutingManager::executeOrders();
};

