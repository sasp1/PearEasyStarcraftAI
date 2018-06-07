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
	std::list<CustomUnit*> workers;


	void CombatManager::addCombatUnit(const BWAPI::Unit* unit);
	void CombatManager::attackNearestEnemy(const BWAPI::Unit* unit);
	
	BWAPI::Unit CombatManager::attackEnemyIfInRange(const BWAPI::Unit* unit, BWAPI::UnitType target, int range);

	bool shallMoveAwayFromEnemyInCriticalRange(const BWAPI::Unit* unit, int range);
	
	void CombatManager::attackEnemyBaseWithAllCombatUnits(BWAPI::Position pos);
	bool CombatManager::shouldDefendBase(int range, const BWAPI::Unit * unit);

	void CombatManager::returnAllUnitsToBase();
	bool CombatManager::isInEnemyCriticalRange(const BWAPI::Unit * unit, const BWAPI::Unit* enemyUnit);
	bool CombatManager::isMelee(const BWAPI::Unit* unit);
	bool CombatManager::repairNearbyInjuredVehicles(const BWAPI::Unit * worker);


	std::list<CustomUnit*> CombatManager::getAllCombatUnits();

	CombatManager();
	~CombatManager();
	void CombatManager::executeOrders();
	bool CombatManager::fleeIfOutNumbered(Vulture* vulture);
	bool canScanLurker = false; 
	bool wantsToScanLurker = false; 

	ScoutingManager* scoutingManager; 
};

