#pragma once
#include <BWAPI.h>
#include "BuildingManager.h"
class CombatManager
{
public:
	BuildingManager* buildingManager;


	
	std::list<const BWAPI::Unit*> combatUnits;

	void CombatManager::addCombatUnit(const BWAPI::Unit* unit);
	void CombatManager::attackNearestEnemy(const BWAPI::Unit* unit);
	void CombatManager::attackEnemy(const BWAPI::Unit* unit, const BWAPI::Unit target);
	bool CombatManager::attackEnemyIfInRange(const BWAPI::Unit* unit, BWAPI::UnitType target, int range);
	void CombatManager::attackEnemyBaseWithAllCombatUnits(BWAPI::Position pos);
	void CombatManager::defendBase();

	CombatManager();
	~CombatManager();
	void CombatManager::executeOrders();
};

