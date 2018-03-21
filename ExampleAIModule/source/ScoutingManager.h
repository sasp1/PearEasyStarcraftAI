#pragma once
#include <BWAPI.h>
class ScoutingManager
{
public:
	BWAPI::Position lastEnemyBuildingPosition;
	std::list<const BWAPI::Unit*> scoutingUnits;
	ScoutingManager();
	~ScoutingManager();
	void ScoutingManager::addScout(const BWAPI::Unit* scout);
	void ScoutingManager::scoutCornersClockwise(const BWAPI::Unit* scout);
	void ScoutingManager::executeOrders();
	void ScoutingManager::onUnitDiscover(BWAPI::Unit unit);
	void ScoutingManager::setStartingCorner(BWAPI::Position pos);
};

