#include "UnitManager.h"
#include "BuildingManager.h"
#include "GatheringManager.h"
#include "ConstructionManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;


int timer = 0;
bool wantToScout = true;
bool canAct = true;



void UnitManager::eventConstructionComplete(const BWAPI::Unit* unit) {
	/*if ((*unit)->getType() == UnitTypes::Terran_Refinery) {
		for (int i = 0; i <=2; i++) {
			gatheringManager->
er();
		}
	}*/

	if ((*unit)->getType() == UnitTypes::Terran_Refinery) {
		newConstructionIsAvailable = true;
	}
}

bool UnitManager::requestBuilding(BWAPI::UnitType building, int reservedMinerals, int reservedGas) {

	bool mineralPriceOk = Broodwar->self()->minerals() >= building.mineralPrice() + reservedMinerals;
	bool gasPriceOk = Broodwar->self()->gas() >= building.gasPrice() + reservedGas;

	//newConstruction is available/is sat whenever a building has started being created
	bool requestIsAccepted = mineralPriceOk && gasPriceOk && newConstructionIsAvailable && canAct;

	//Broodwar->sendText("Unitmanager: minerals: %s    gas: %s    newConstr: %s", (mineralPriceOk ? "OK" : "denied"), (gasPriceOk ? "OK" : "denied"), (newConstructionIsAvailable ? "OK" : "denied"));

	if (requestIsAccepted) {
		constructionManager->createBuilding(building, gatheringManager->removeWorker());
		newConstructionIsAvailable = false;
		timer = timer - 550;
		if (timer < 0) timer = 0;
	}

	return requestIsAccepted;
}

void UnitManager::executeOrders() {
	// onFrame request to perform calculations. The "main" of this class
	
	/*
	timer++;

	if (timer > 1080) canAct = false;
	if (timer == 1090) {

		for (auto &u : Broodwar->self()->getUnits()) {
			if (u != NULL) {
				if (u->isIdle() && u->getType().isWorker()) {

					const BWAPI::Unit* unit = new BWAPI::Unit();
					unit = (&u);

					newWorker(unit);

				}
			}
		}
	}
	if (timer > 1100) {
		canAct = true;
		timer = 0;
	}

	*/

	gatheringManager->executeOrders();
	scoutingManager->executeOrders();
	combatManager->executeOrders();
	constructionManager->executeOrders();

	// Clean up units for each manager (if they are dead, remove them from lists): 
	cleanUpUnits(scoutingManager->scoutingUnits);
	cleanUpUnits(gatheringManager->mineralWorkers);
	cleanUpUnits(gatheringManager->gasWorkers);
	cleanUpUnits(combatManager->combatUnits);
	cleanUpUnits(combatManager->vultures); 
	cleanUpUnits(combatManager->tanks);
}

void UnitManager::cleanUpUnits(std::list<const BWAPI::Unit*>& unitList) {

	for (auto &u : unitList) {
		if (u != NULL && (*u)->getHitPoints() == 0) {
			unitList.remove(u);
			u = NULL;
		}
	}
}

void UnitManager::cleanUpUnits(std::list<CustomUnit*>& unitList) {

	for (auto &u : unitList) {	
		
		if (u->unit != NULL && (*u->unit)->getHitPoints() == 0) {
			unitList.remove(u);
			 u->unit = NULL;			
		}
	}
}

void UnitManager::newWorker(const BWAPI::Unit* worker) {
	//When a new worker is created in game
	unitWorkers.push_front(worker);
	gatheringManager->addWorker(worker);
}

//Initial class setup
UnitManager::UnitManager() {

}

void UnitManager::addUnit(const BWAPI::Unit* unit) {
	if ((scoutingManager->scoutingUnits.size() < 1) & (*unit)->getType() == UnitTypes::Terran_Marine) {
		(*scoutingManager).addScout(unit);
	}
	else {
		(*combatManager).addCombatUnit(unit);
	}
}

void UnitManager::setManagers(CombatManager* combatManager, GatheringManager* gatheringManager, ConstructionManager* constructionManager, ScoutingManager* scoutingManager) {
	//Make unitmanager aware of the lowaer managers
	this->gatheringManager = gatheringManager;
	this->combatManager = combatManager;
	this->constructionManager = constructionManager;
	this->scoutingManager = scoutingManager;
}

UnitManager::~UnitManager()
{
}
