#pragma once
#include <BWAPI.h>
class CombatManager
{
public:
	bool wantToAttackEnemyBase;
	std::list<const BWAPI::Unit*> combatUnits;

	void CombatManager::addCombatUnit(const BWAPI::Unit* unit);
	void CombatManager::attackNearestEnemy(const BWAPI::Unit* unit);
	void CombatManager::attackEnemyBaseWithAllCombatUnits(BWAPI::Position pos);
	void CombatManager::defendBase();

	CombatManager();
	~CombatManager();
	void CombatManager::executeOrders();
};

