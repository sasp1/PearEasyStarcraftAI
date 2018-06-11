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
	std::list<CustomUnit*> wraiths;

	std::list<CustomUnit*> minesInDefensiveChokePosition; 
	std::list<CustomUnit*> minesAtEnemeyBase;
	std::list<CustomUnit*> workers;
	bool shouldAttack = false;



	void CombatManager::addCombatUnit(const BWAPI::Unit* unit);
	BWAPI::Unit CombatManager::findMostWantedEnemyToKill(const BWAPI::Unit* unit);
	void attackDesiredUnit(CustomUnit* myUnit, BWAPI::Unit desiredUnitToAttack);

	BWAPI::Unit CombatManager::attackEnemyIfInRange(const BWAPI::Unit* unit, BWAPI::UnitType target, int range);

	bool shallMoveAwayFromEnemyInCriticalRange(const BWAPI::Unit* unit, int range);
	
	void CombatManager::attackEnemyBaseWithAllCombatUnits(BWAPI::Position pos);
	void CombatManager::attackEnemyBaseWhenVulturesAreGrouped(BWAPI::Position enemyBasePosition, int groupSize);
	bool CombatManager::shouldDefendBase(int range, CustomUnit* unit);
	void CombatManager::analyzeEnemyArmy();

	void CombatManager::returnAllUnitsToBase();
	bool CombatManager::isInEnemyCriticalRange(const BWAPI::Unit * unit, const BWAPI::Unit* enemyUnit);
	bool CombatManager::isMelee(const BWAPI::Unit* unit);
	bool CombatManager::repairNearbyInjuredVehicles(const BWAPI::Unit * worker);
	bool shouldSetMine(Vulture* vulture); 
	bool shouldMoveAwayFromFriendlyUnits(const Unit* unit); 
	std::list<CustomUnit*> CombatManager::getAllCombatUnits();

	CombatManager();
	~CombatManager();
	void CombatManager::executeOrders();
	bool CombatManager::fleeIfOutNumbered(Vulture* vulture);
	bool canScanLurker = false; 
	bool wantsToScanLurker = false; 

	ScoutingManager* scoutingManager; 
};

