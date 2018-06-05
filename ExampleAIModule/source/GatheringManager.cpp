#include "GatheringManager.h"
#include <BWAPI.h>
#include "BuildingManager.h"
#include "Worker.h"

using namespace BWAPI;
using namespace Filter;

BWAPI::Unit* gas = NULL;
int gasWorkerLimit = 2;
int gasWorkers = 0;
int mineralWorkers = 0;

void GatheringManager::addWorker(const BWAPI::Unit* worker) {
	//Receive control of a new worker

	Worker* w = new Worker(worker);
	w->workState = 0;

	int tempDist = 10000;
	const BWAPI::Unit* nextCenter = NULL;

	for (auto &c : (*buildingManager).commandCenters) {
		const BWAPI::Unit* center = c->unit;
		int dist = (*center)->getDistance(*worker);

		if (dist < tempDist) {

			nextCenter = center;
			dist = tempDist;
		}
	}

	w->center = nextCenter;
	workers.push_back(w);
}

void GatheringManager::allocateWorker(bool addToGas) {
	bool alloc = false;
	for (auto &w : workers) {

		if (addToGas && !alloc) {
			if (w->workState == 0)
				w->workState = 1;
			w->gas = gas;
			alloc = true;
		}
		else if (!addToGas && !alloc) {
			if (w->workState == 1)
				w->workState = 0;
			alloc = true;
		}
	}
}

void GatheringManager::splitWorkers() {

	for (auto &m : buildingManager->commandCenters) {
		for (auto &u : workers) {
		}
	}
}


const BWAPI::Unit* GatheringManager::removeWorker() {
	//Lose control of a worker

	Worker* w = workers.back();

	const BWAPI::Unit* u = w->unit;
	workers.pop_back();
	return u;
}

void GatheringManager::executeOrders() {
	//Distribute gas and mineral-workers
	const BWAPI::Unit* worker;
	if (gasWorkers > 0 && gasWorkers < gasWorkerLimit && gas != NULL) {
		allocateWorker(true);
		Broodwar->sendText("added worker to gas list");
	}
	else if (mineralWorkers > 0 && gasWorkers > gasWorkerLimit && gas != NULL) {
		allocateWorker(false);
		Broodwar->sendText("added worker to mineral list");
	}

	//Simple look for refinery (handling if the gas is not defined)
	if (gas == NULL) {
		for (auto &u : Broodwar->getAllUnits()) {
			if (u->getType().isBuilding()) {
				if (u->getType() == UnitTypes::Terran_Refinery && (u->isCompleted())) {
					gas = new Unit();
					*gas = u;
				}
			}
		}
	}

	//Update count
	gasWorkers = 0;
	mineralWorkers = 0;

	//Make workers collect respective rescource
	for (auto &w : workers) {

		if (!w->isUnitValid()) {
			workers.remove(w);
		}
		else
			if (w->workState == 0) mineralWorkers++;
			else if (w->workState == 1) gasWorkers++;
		w->collect();
	}
	
	// Update limit to number of gasworkers: 
	if (Broodwar->self()->gatheredGas() > 800) {
		gasWorkerLimit = 0; 
	}
}

//Initial class setup
GatheringManager::GatheringManager()
{
}

GatheringManager::~GatheringManager()
{
}

