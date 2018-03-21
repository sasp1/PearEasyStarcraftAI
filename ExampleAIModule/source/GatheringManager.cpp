#include "GatheringManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;

std::list<const BWAPI::Unit*> mineralWorkers;
std::list<const BWAPI::Unit*> gasWorkers;
BWAPI::Unit* gas = NULL;

void GatheringManager::addWorker(const BWAPI::Unit* worker) {
	//Receive control of a new worker
	mineralWorkers.push_back(worker);
}

void GatheringManager::addGasworker() {
	//Add unit to gas gathering from mineral gathering
	gasWorkers.push_back(mineralWorkers.back());
	mineralWorkers.pop_back();
}

const BWAPI::Unit* GatheringManager::removeWorker() {
	//Lose control of a worker
	const BWAPI::Unit* worker = mineralWorkers.back();
	mineralWorkers.pop_back();
	return worker;
}

void GatheringManager::executeOrders() {
	//Execute own orders. "Main" of this class

	//Simple look for refinery
	if (gas == NULL) {
		for (auto &u : Broodwar->getAllUnits()) {
			if (u->getType().isBuilding()) {
				if (u->getType() == UnitTypes::Terran_Refinery) {
					BWAPI::Unit* gas = new Unit();
					*gas = u;
				}
			}
		}
	}


	//Make mineral gatherers work
	for (auto &u : mineralWorkers)
	{
		BWAPI::Unit mine = (*u)->getClosestUnit(IsMineralField);

		if ((*u)->isIdle()) {
			if ((*u)->isCarryingGas() || (*u)->isCarryingMinerals())
				(*u)->returnCargo();

			else (*u)->gather(mine);
		}
	}
	
	//Make gas workers work
	for (auto &u : gasWorkers)
	{
		if ((*u)->isIdle()) {
			if ((*u)->isCarryingGas() || (*u)->isCarryingMinerals())
				(*u)->returnCargo();

			else if (gas != NULL) {
				(*u)->rightClick(*gas);
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

