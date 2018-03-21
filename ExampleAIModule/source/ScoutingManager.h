#pragma once
#include <BWAPI.h>
class ScoutingManager
{
public:
	std::list<const BWAPI::Unit*> scoutingUnits;
	ScoutingManager();
	~ScoutingManager();
	void ScoutingManager::addScout(const BWAPI::Unit* scout);
	void ScoutingManager::scoutCornersClockwise(const BWAPI::Unit* scout);
	void ScoutingManager::executeOrders();
};

