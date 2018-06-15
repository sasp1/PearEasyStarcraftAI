#pragma once
#include <BWAPI.h>
#include "CombatManager.h"
#include "GatheringManager.h"
#include "ConstructionManager.h"
#include "ScoutingManager.h"
class UnitManager
{

public:
	void UnitManager::setManagers(CombatManager* combatManager, GatheringManager* gatheringManager, ConstructionManager* constructionManager, ScoutingManager* scoutingManager);
	~UnitManager();
	UnitManager();
	bool UnitManager::requestSupply();
	void UnitManager::addUnit(BWAPI::UnitInterface* unit);
	void UnitManager::executeOrders();
	void UnitManager::newWorker(BWAPI::UnitInterface* worker);
	void UnitManager::makeASCVHelpArmy();
	void UnitManager::eventConstructionComplete(BWAPI::UnitInterface* unit);
	void UnitManager::cleanUpUnits(std::list<BWAPI::UnitInterface*>& unitList); 
	void UnitManager::cleanUpUnits(std::list<CustomUnit*>& unitList);
	bool UnitManager::requestBuilding(BWAPI::UnitType building, int reservedMinerals, int reservedGas, int minerals, int gas);
	bool newConstructionIsAvailable = true;
	CombatManager* combatManager;
	GatheringManager* gatheringManager;
	ConstructionManager* constructionManager;
	ScoutingManager* scoutingManager;
	
};

