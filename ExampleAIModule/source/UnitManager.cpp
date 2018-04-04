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
	if ((*unit)->getType() == UnitTypes::Terran_Refinery) {
		for (int i = 0; i <=2; i++) {
			gatheringManager->addGasworker();
		}
	}
}

bool UnitManager::requestBuilding(BWAPI::UnitType building) {

	bool mineralPriceOk = Broodwar->self()->minerals() > building.mineralPrice();
	//newConstruction is available/is sat whenever a building has started being created
	bool requestIsAccepted = mineralPriceOk && newConstructionIsAvailable;

	Broodwar->sendText("Unitmanager: request: %s", (requestIsAccepted ? "accepted" : "denied") );

	if (requestIsAccepted) {
		constructionManager->createBuilding(building, gatheringManager->removeWorker());
		newConstructionIsAvailable = false;
	}

	return requestIsAccepted;
}

void UnitManager::executeOrders() {
	// onFrame request to perform calculations. The "main" of this class

	for (auto &u : unitWorkers) {
		if ((*u)->isIdle() && (constructionManager->constructionsWorker) != NULL && (*u)->getID() != (*constructionManager->constructionsWorker)->getID()) {
			
			gatheringManager->addWorker(u);
		}
	}


	gatheringManager->executeOrders();
	scoutingManager->executeOrders();
	combatManager->executeOrders();
	constructionManager->executeOrders();
}

void UnitManager::newWorker(const BWAPI::Unit* worker) {
	//When a new worker is created in game
	unitWorkers.push_front(worker);
	gatheringManager->addWorker(worker);
}

//Initial class setup
UnitManager::UnitManager() {

}

void UnitManager::addUnit(const BWAPI::Unit * unit){

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
