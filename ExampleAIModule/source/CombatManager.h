#pragma once
#include <BWAPI.h>
class CombatManager
{
public:
	std::list<const BWAPI::Unit*> combatUnits;

	void CombatManager::addCombatUnit(const BWAPI::Unit* unit);
	void CombatManager::attackNearestEnemy(const BWAPI::Unit* unit);

	CombatManager();
	~CombatManager();
	void CombatManager::executeOrders();
};

