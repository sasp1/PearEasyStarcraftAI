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
	BWAPI::Unit CombatManager::attackEnemyIfInRange(BWAPI::UnitInterface* unit, BWAPI::UnitType target, int range);
	BWAPI::Unit CombatManager::findMostWantedEnemyToKill(BWAPI::UnitInterface* unit);
	void CombatManager::addCombatUnit(BWAPI::UnitInterface* unit);
	void CombatManager::attackEnemyBaseWithAllCombatUnits(BWAPI::Position pos);
	void CombatManager::attackEnemyBaseWhenVulturesAreGrouped(BWAPI::Position enemyBasePosition, int groupSize);
	bool CombatManager::shouldDefendBase(int range, CustomUnit* unit);
	void CombatManager::analyzeEnemyArmy();
	void CombatManager::returnAllUnitsToBase();
	bool CombatManager::isInEnemyCriticalRange(BWAPI::UnitInterface* unit, BWAPI::UnitInterface* enemyUnit);
	bool CombatManager::isMelee(BWAPI::UnitInterface* unit);
	bool CombatManager::repairNearbyInjuredVehicles(BWAPI::Unit * worker);
	void CombatManager::executeOrders();
	bool CombatManager::fleeIfOutNumbered(Vulture* vulture, bool outNumbered);
	void attackDesiredUnit(CustomUnit* myUnit, BWAPI::Unit desiredUnitToAttack);
	bool shallMoveAwayFromEnemyInCriticalRange(BWAPI::UnitInterface* unit, int range);
	bool shouldSetMine(Vulture* vulture, Race enemyRace, int frameCount);
	std::list<CustomUnit*> CombatManager::getAllCombatUnits();
	bool calcOutNumbered(UnitInterface* nearestHydra);
};

