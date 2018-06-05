#pragma once
#include <BWAPI.h>
#include "BuildingManager.h"
#include "Vulture.h"
#include "SiegeTank.h"
#include "Marine.h"
#include "ScoutingManager.h"
#include "Mine.h"

class CombatManager
{
public:
	BuildingManager* buildingManager;


	
	//std::list<const BWAPI::Unit*> combatUnits;
	std::list<CustomUnit*> vultures; 
	std::list<CustomUnit*> tanks;
	std::list<CustomUnit*> marines; 
	std::list<CustomUnit*> mines; 

	void CombatManager::addCombatUnit(const BWAPI::Unit* unit);
	void CombatManager::attackNearestEnemy(const BWAPI::Unit* unit);
	
	BWAPI::Unit CombatManager::attackEnemyIfInRange(const BWAPI::Unit* unit, BWAPI::UnitType target, int range);

	bool stayingOutOfRangeFromEnemy(const BWAPI::Unit* unit, int range);
	
	void CombatManager::attackEnemyBaseWithAllCombatUnits(BWAPI::Position pos);
	bool CombatManager::defendingBase(int range, const BWAPI::Unit * unit);

	void CombatManager::returnAllUnitsToBase();
	bool CombatManager::isInEnemyCriticalRange(const BWAPI::Unit * unit, const BWAPI::Unit* enemyUnit);
	std::list<CustomUnit*> CombatManager::getAllCombatUnits();

	CombatManager();
	~CombatManager();
	void CombatManager::executeOrders();

	ScoutingManager* scoutingManager; 
};

