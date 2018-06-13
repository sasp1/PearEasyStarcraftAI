#include "UnitManager.h"
#include "BuildingManager.h"
#include "GatheringManager.h"
#include "ConstructionManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;

bool wantToScout = true;
bool canAct = true;

/**
* @file UnitManager.cpp
* @brief Handles allocation of all units to and between all lower unit controlling managers.
* @author Daniel Fjordhøj <s133198@student.dtu.dk>
*/


void UnitManager::eventConstructionComplete(BWAPI::UnitInterface* unit) {
	//Save state if refinery is built
	if (unit->getType() == UnitTypes::Terran_Refinery) {
		newConstructionIsAvailable = true;
	}
}

/**
* Tries to initiate construction af a supply depot, if there is enough rescources available
* @author Daniel Fjordhøj <s133198@dstudent.dtu.dk>
*/
bool UnitManager::requestSupply() {
	//Request construction of a supply depot if resources allow it

	BWAPI::UnitType b = UnitTypes::Terran_Supply_Depot;
	bool mineralPriceOk = Broodwar->self()->minerals() >= b.mineralPrice();
	bool gasPriceOk = Broodwar->self()->gas() >= b.gasPrice();
	bool isBuildOk = mineralPriceOk && gasPriceOk;

	if (isBuildOk) constructionManager->createBuilding(b, gatheringManager->removeWorker());
	return isBuildOk;
}

bool UnitManager::requestBuilding(BWAPI::UnitType building, int reservedMinerals, int reservedGas) {
	//Requests construction of a building

	//Checks rescources
	bool mineralPriceOk = Broodwar->self()->minerals() >= building.mineralPrice() + reservedMinerals;
	bool gasPriceOk = Broodwar->self()->gas() >= building.gasPrice() + reservedGas;
	bool requestIsAccepted = mineralPriceOk && gasPriceOk && newConstructionIsAvailable && canAct;

	//If rescources allow get construction manager to construct building
	if (requestIsAccepted) {
		constructionManager->createBuilding(building, gatheringManager->removeWorker());
		newConstructionIsAvailable = false;
	}
	return requestIsAccepted;
}

void UnitManager::executeOrders() {

	//Get lower managers to execute orders
	gatheringManager->executeOrders();
	scoutingManager->executeOrders();
	combatManager->executeOrders();
	constructionManager->executeOrders();

	//Clean up units for each manager (if they are dead, remove them from lists): 
	cleanUpUnits(scoutingManager->scoutingUnits);
	cleanUpUnits(combatManager->vultures); 
	cleanUpUnits(combatManager->tanks);
	cleanUpUnits(combatManager->workers);
	cleanUpUnits(combatManager->marines);
	cleanUpUnits(combatManager->minesInDefensiveChokePosition); 
	cleanUpUnits(combatManager->minesAtEnemeyBase);

}

void UnitManager::cleanUpUnits(std::list<BWAPI::UnitInterface*>& unitList) {
	//Clean up a list of units, that is if unit is null or dead
	for (auto &u : unitList) {
		if (u != NULL && u->getHitPoints() == 0) {
			unitList.remove(u);
			u = NULL;
		}
	}
}

void UnitManager::cleanUpUnits(std::list<CustomUnit*>& unitList) {
	// Clean up a list of custom units, that is if unit is null or dead
	for (auto &u : unitList) {
		if (u->unit != NULL && u->unit->getHitPoints() == 0) {
			unitList.remove(u);
			u->unit = NULL;
		}
	}
}

void UnitManager::makeASCVHelpArmy() {
	//Request SCV to be used in battle
	BWAPI::UnitInterface* worker = gatheringManager->removeWorker();
	combatManager->addCombatUnit(worker);
}

void UnitManager::newWorker(BWAPI::UnitInterface* worker) {
	//Add worker to gathering manager when created
	gatheringManager->addWorker(worker);
}

UnitManager::UnitManager() {
}

void UnitManager::addUnit(BWAPI::UnitInterface* unit) {
	//Add unit as scout if there isn't any, and unit is a marine. Else add them as a combat unit
	if ((scoutingManager->scoutingUnits._Mysize() < 1) & unit->getType() == UnitTypes::Terran_Marine) {
		(*scoutingManager).addScout(unit);
	}
	else (*combatManager).addCombatUnit(unit);
}

void UnitManager::setManagers(CombatManager* combatManager, GatheringManager* gatheringManager, ConstructionManager* constructionManager, ScoutingManager* scoutingManager) {
	//Make unitmanager aware of the lower managers
	this->gatheringManager = gatheringManager;
	this->combatManager = combatManager;
	this->constructionManager = constructionManager;
	this->scoutingManager = scoutingManager;
}

UnitManager::~UnitManager()
{
}
