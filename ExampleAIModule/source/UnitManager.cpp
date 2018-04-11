#include "UnitManager.h"
#include "BuildingManager.h"
#include "GatheringManager.h"
#include "ConstructionManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;


int timer = 0;
bool wantToScout = true;
bool wantToAttack = false;



void UnitManager::eventConstructionComplete(const BWAPI::Unit* unit) {
	/*if ((*unit)->getType() == UnitTypes::Terran_Refinery) {
		for (int i = 0; i <=2; i++) {
			gatheringManager->addGasworker();
		}
	}*/

	if ((*unit)->getType() == UnitTypes::Terran_Refinery) {
		Broodwar->sendText("Refinery done!");
		newConstructionIsAvailable = true;
	}
}

bool UnitManager::requestBuilding(BWAPI::UnitType building, int reservedMinerals, int reservedGas) {

	bool mineralPriceOk = Broodwar->self()->minerals() >= building.mineralPrice() + reservedMinerals;
	bool gasPriceOk = Broodwar->self()->gas() >= building.gasPrice() + reservedGas;

	//newConstruction is available/is sat whenever a building has started being created
	bool requestIsAccepted = mineralPriceOk && gasPriceOk && newConstructionIsAvailable;

	//Broodwar->sendText("Unitmanager: minerals: %s    gas: %s    newConstr: %s", (mineralPriceOk ? "OK" : "denied"), (gasPriceOk ? "OK" : "denied"), (newConstructionIsAvailable ? "OK" : "denied"));

	if (requestIsAccepted) {
		constructionManager->createBuilding(building, gatheringManager->removeWorker());
		newConstructionIsAvailable = false;
	}

	return requestIsAccepted;
}

void UnitManager::executeOrders() {
	// onFrame request to perform calculations. The "main" of this class

	/*
	for (auto &u : unitWorkers) {
		if ((*u)->isIdle() && (constructionManager->constructionsWorker) != NULL && (*u)->getID() != (*constructionManager->constructionsWorker)->getID()) {
			
			gatheringManager->addWorker(u);
		}
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
}

void UnitManager::cleanUpUnits(std::list<const BWAPI::Unit*>& unitList) {

	for (auto &u : unitList) {
		if (u != NULL && (*u)->getHitPoints() == 0) {
			unitList.remove(u);
			u = NULL;
			Broodwar->sendText("Unit was removed from a manager!"); 	
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

void UnitManager::addUnit(const BWAPI::Unit* unit){
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
