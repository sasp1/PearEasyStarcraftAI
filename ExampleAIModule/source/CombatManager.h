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
	ScoutingManager* scoutingManager;
	CombatManager();
	~CombatManager();
	std::list<CustomUnit*> vultures; 
	std::list<CustomUnit*> tanks;
	std::list<CustomUnit*> marines; 
	std::list<CustomUnit*> wraiths;
	std::list<CustomUnit*> minesInDefensiveChokePosition; 
	std::list<CustomUnit*> minesAtEnemeyBase;
	std::list<CustomUnit*> workers;
	bool shouldAttack = false;
	bool canScanLurker = false;
	bool wantsToScanLurker = false;
	BWAPI::Unit CombatManager::attackEnemyIfInRange(const BWAPI::Unit* unit, BWAPI::UnitType target, int range);
	BWAPI::Unit CombatManager::findMostWantedEnemyToKill(const BWAPI::Unit* unit);
	void CombatManager::addCombatUnit(const BWAPI::Unit* unit);
	void CombatManager::attackEnemyBaseWithAllCombatUnits(BWAPI::Position pos);
	void CombatManager::attackEnemyBaseWhenVulturesAreGrouped(BWAPI::Position enemyBasePosition, int groupSize);
	bool CombatManager::shouldDefendBase(int range, CustomUnit* unit);
	void CombatManager::analyzeEnemyArmy();
	void CombatManager::returnAllUnitsToBase();
	bool CombatManager::isInEnemyCriticalRange(const BWAPI::Unit * unit, const BWAPI::Unit* enemyUnit);
	bool CombatManager::isMelee(const BWAPI::Unit* unit);
	bool CombatManager::repairNearbyInjuredVehicles(const BWAPI::Unit * worker);
	void CombatManager::executeOrders();
	bool CombatManager::fleeIfOutNumbered(Vulture* vulture);
	void attackDesiredUnit(CustomUnit* myUnit, BWAPI::Unit desiredUnitToAttack);
	bool shallMoveAwayFromEnemyInCriticalRange(const BWAPI::Unit* unit, int range);
	bool shouldSetMine(Vulture* vulture);
	std::list<CustomUnit*> CombatManager::getAllCombatUnits();

};

