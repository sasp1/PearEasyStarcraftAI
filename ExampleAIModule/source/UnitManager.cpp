#include "UnitManager.h"
#include "BuildingManager.h"
#include "GatheringManager.h"
#include "ConstructionManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;

std::list<const BWAPI::Unit*> workers;
std::list<const BWAPI::Unit*> soldiers;
int timer = 0;


UnitManager::UnitManager() {

}

void UnitManager::setManagers(BuildingManager* buildingManager, GatheringManager* gatheringManager, ConstructionManager* constructionManager) {
	//Make unitmanager aware of the lowaer managers
	this->gatheringManager = gatheringManager;
	this->buildingManager = buildingManager;
	this->constructionManager = constructionManager;
}

void UnitManager::eventConstructionInitiated() {
	//When a construction has begun building
	buildingManager->setIsDesiredToBuildWorkers(true);
}

void UnitManager::eventConstructionComplete() {
	//When building of a construction is completed
	//isBuilding = false;
}

void UnitManager::executeOrders() {
	// onFrame request to perform calculations. The "main" of this class

	
}

void UnitManager::newWorker(const BWAPI::Unit* worker) {
	//When a new worker is created in game
	workers.push_front(worker);
	gatheringManager->addWorker(worker);
}


UnitManager::~UnitManager()
{
}
