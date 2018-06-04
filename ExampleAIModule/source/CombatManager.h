#pragma once
#include <BWAPI.h>
#include "BuildingManager.h"
#include "Vulture.h"
#include "SiegeTank.h"
class CombatManager
{
public:
	BuildingManager* buildingManager;


	
	std::list<const BWAPI::Unit*> combatUnits;
	std::list<CustomUnit*> vultures; 
	std::list<CustomUnit*> tanks;

	void CombatManager::addCombatUnit(const BWAPI::Unit* unit);
	void CombatManager::attackNearestEnemy(const BWAPI::Unit* unit);
	
	BWAPI::Unit CombatManager::attackEnemyIfInRange(const BWAPI::Unit* unit, BWAPI::UnitType target, int range);

	bool stayOutOfRange(const BWAPI::Unit* unit, int range);
	
	void CombatManager::attackEnemyBaseWithAllCombatUnits(BWAPI::Position pos);
	void CombatManager::defendBase(int range);

	void CombatManager::returnAllUnitsToBase();
	bool CombatManager::isInEnemyCriticalRange(const BWAPI::Unit * unit, const BWAPI::Unit* enemyUnit);

	CombatManager();
	~CombatManager();
	void CombatManager::executeOrders();
};

