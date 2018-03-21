#include "UnitManager.h"
#include "BuildingManager.h"
#include "GatheringManager.h"
#include "ConstructionManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;

std::list<const BWAPI::Unit*> unitWorkers;
std::list<const BWAPI::Unit*> soldiers;
int timer = 0;


void UnitManager::eventConstructionComplete() {
	//When building of a construction is completed
	//isBuilding = false;
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
		if ((*u)->isIdle() && (*u)->getID != (*constructionManager->constructionsWorker)->getID) {
			Broodwar->sendText("ID IDLE WORKER: %i", (*u)->getID);
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
