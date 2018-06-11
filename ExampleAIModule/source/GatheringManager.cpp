#include "GatheringManager.h"
#include <BWAPI.h>
#include "BuildingManager.h"
#include "Worker.h"

using namespace BWAPI;
using namespace Filter;

BWAPI::Unit* gas = NULL;
int gasWorkerLimit = 3;
int gasWorkers = 0;
int mineralWorkers = 0;

void GatheringManager::addWorker(const BWAPI::Unit* worker) {

	//Set new worker as collecting minreals
	Worker* w = new Worker(worker);
	w->workState = 0;

	//Set virtual commandcenter to unlimited distance away
	int tempDist = 10000;
	const BWAPI::Unit* nextCenter = NULL;

	//Find closest commandcenter
	for (auto &c : (*buildingManager).commandCenters) {
		const BWAPI::Unit* center = c->unit;
		int dist = (*center)->getDistance(*worker);

		if (dist < tempDist) {

			nextCenter = center;
			dist = tempDist;
		}
	}

	//Set closest commandcenter as "home", and add worker to list.
	w->center = nextCenter;
	workers.push_back(w);
}

void GatheringManager::allocateWorker(bool addToGas) {
	bool alloc = false;
	for (auto &w : workers) {
		// If requested, assign first worker who collects minerals to collect gas
		if (addToGas && !alloc) {
			if (w->workState == 0) {
				w->workState = 1;
				w->gas = gas;
				w->stop();
				alloc = true;
			}
		}
		// If requested, assign first worker who collects gas to collect monerals
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

	//Split workers evenly between commandcenters
	for (auto &m : buildingManager->commandCenters) {
		for (auto &u : workers) {
			if (countA % totalCommand == countB) {
				u->center = m->unit;
			}
			countA++;
		}
		countB++;
	}
}

const BWAPI::Unit* GatheringManager::removeWorker() {

	// Lose control of first found mineral collector.
	const BWAPI::Unit* u = new Unit();
	for (auto &w : workers) {
		if (w->workState == 0) {
			u = w->unit;
			workers.remove(w);
			return u;
		}
	}
}

void GatheringManager::executeOrders() {

	//Assign workers to commandcenter on game start
	if (Broodwar->getFrameCount() == 20) {
		splitWorkers();
	}

	//Prepare worker list cleanup
	bool foundError = false;
	gasWorkers = 0;
	mineralWorkers = 0;
	std::list<Worker*> workersToBeRemoved;


	for (auto &w : workers) {
		//Add invalid workers to temp list
		if (w == NULL) workersToBeRemoved.push_back(w);
		else if (!w->isValid()) workersToBeRemoved.push_back(w);
		else if (!((w->workState == 0) || (w->workState == 1)))
			workersToBeRemoved.push_back(w);

		//If not invalid increase respective job counter
		else {
			if (w->workState == 0) mineralWorkers++;
			else if (w->workState == 1) gasWorkers++;
			w->collect();
		}
	}

	//Remove invalid workers 
	for (auto &w : workersToBeRemoved) workers.remove(w);

	//Distribute workers between gas and minerals.
	if (gasWorkers < gasWorkerLimit && gas != NULL)
		allocateWorker(true);
	else if (gasWorkers > gasWorkerLimit)
		allocateWorker(false);

	//If refinery is built, set at refinery to collect from.
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

