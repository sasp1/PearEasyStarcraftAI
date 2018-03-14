#include "GatheringManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;

std::list<const BWAPI::Unit*> gatheringWworkers;


GatheringManager::GatheringManager()
{
}

GatheringManager::~GatheringManager()
{
}

void GatheringManager::addWorker(const BWAPI::Unit* worker) {
	//Receive control of a new worker
	gatheringWworkers.push_back(worker);
}

const BWAPI::Unit* GatheringManager::removeWorker() {
	//Lose control of a worker
	const BWAPI::Unit* worker = gatheringWworkers.back();
	gatheringWworkers.pop_back();
	return worker;
}

void GatheringManager::executeOrders() {
	//Execute own orders. "Main" of this class

	for (auto &u : gatheringWworkers)
	{
		BWAPI::Unit mine = (*u)->getClosestUnit(IsMineralField);

		if ((*u)->isIdle()) {
			if ((*u)->isCarryingGas() || (*u)->isCarryingMinerals())
				(*u)->returnCargo();
			else (*u)->gather(mine);
		}
	}
}
