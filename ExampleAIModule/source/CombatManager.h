#pragma once
#include <BWAPI.h>
#include "BuildingManager.h"
#include "Vulture.h"
class CombatManager
{
public:
	BuildingManager* buildingManager;


	
	std::list<const BWAPI::Unit*> combatUnits;
	std::list<const Vulture*> vultures; 

	void CombatManager::addCombatUnit(const BWAPI::Unit* unit);
	void CombatManager::attackNearestEnemy(const BWAPI::Unit* unit);
	
	BWAPI::Unit CombatManager::attackEnemyIfInRange(const BWAPI::Unit* unit, BWAPI::UnitType target, int range);

	bool stayOutOfRange(const BWAPI::Unit* unit, int range);
	
	void CombatManager::attackEnemyBaseWithAllCombatUnits(BWAPI::Position pos);
	void CombatManager::defendBase(int range);

	void CombatManager::returnAllUnitsToBase();

	CombatManager();
	~CombatManager();
	void CombatManager::executeOrders();
};

