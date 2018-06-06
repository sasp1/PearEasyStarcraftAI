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
			if (w->workState == 0) {
				w->workState = 1;
				w->gas = gas;
				w->stop();
				alloc = true;
			}
		}
		else if (!addToGas && !alloc) {
			if (w->workState == 1) {
				w->workState = 0;
				w->stop();
				alloc = true;
			}
		}
	}
}

void GatheringManager::splitWorkers() {
	int countA = 0;
	int countB = 0;
	int totalCommand = buildingManager->commandCenters.size();
	for (auto &m : buildingManager->commandCenters) {
		for (auto &u : workers) {
			if (countA % totalCommand == countB) {
				u->center = m->getUnit();
			}
				countA++;
		}
		countB++;
	}
}

const BWAPI::Unit* GatheringManager::removeWorker() {
	//Lose control of a worker

	Worker* w = workers.back();
	Worker* newW = new Worker(w->unit);
	workers.pop_back();
	return newW->unit;
}

void GatheringManager::executeOrders() {

	if (Broodwar->getFrameCount() == 20) {
		splitWorkers();
	}

	bool foundError = false;
	gasWorkers = 0;
	mineralWorkers = 0;

	for (auto &w : workers) {
		if (w == NULL) {
			workers.remove(w);
			foundError = true;
			continue;
		}
		else if (!w->isValid()) {
			workers.remove(w);
			foundError = true;
			continue;
		}
		else
			if (w->workState == 0) mineralWorkers++;
			else if (w->workState == 1) gasWorkers++;
			w->collect();
	}

	if (!foundError) {

		if ((Broodwar->self()->gas()) > (Broodwar->self()->minerals() + 500)) {
			gasWorkerLimit = 0;
		}
		else {
			gasWorkerLimit = 4;
		}

		const BWAPI::Unit* worker;
		if (gasWorkers < gasWorkerLimit && gas != NULL) {
			allocateWorker(true);
			Broodwar->sendText("added worker to gas list");
		}
		else if (gasWorkers > gasWorkerLimit) {
			allocateWorker(false);
			Broodwar->sendText("added worker to mineral list");
		}
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
}

//Initial class setup
GatheringManager::GatheringManager()
{
}

GatheringManager::~GatheringManager()
{
}

