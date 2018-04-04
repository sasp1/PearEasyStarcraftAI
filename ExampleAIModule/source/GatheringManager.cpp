#include "GatheringManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;

//std::list<const BWAPI::Unit*> mineralWorkers;
//std::list<const BWAPI::Unit*> gasWorkers;
BWAPI::Unit* gas = NULL;
int gasWorkerLimit = 3; 

void GatheringManager::addWorker(const BWAPI::Unit* worker) {
	//Receive control of a new worker

	if (gasWorkers.size() < gasWorkerLimit && gas != NULL) {
		gasWorkers.push_back(worker); 
		Broodwar->sendText("added worker to gas list"); 
	}
	else {
		mineralWorkers.push_back(worker); 
		Broodwar->sendText("added worker to mineral list");
	}
}

void GatheringManager::addGasworker() {
	//Add unit to gas gathering from mineral gathering
	gasWorkers.push_back(mineralWorkers.back());
	mineralWorkers.pop_back();
	Broodwar->sendText("gas worker was taken from mineral workers"); 
}

const BWAPI::Unit* GatheringManager::removeWorker() {
	//Lose control of a worker
	const BWAPI::Unit* worker = mineralWorkers.back();
	mineralWorkers.pop_back();
	return worker;
}

void GatheringManager::executeOrders() {
	//Execute own orders. "Main" of this class

	//Simple look for refinery (handling if the gas is not defined)
	if (gas == NULL) {
		for (auto &u : Broodwar->getAllUnits()) {
			if (u->getType().isBuilding()) {
				if (u->getType() == UnitTypes::Terran_Refinery && (u->isCompleted())) {
					gas = new Unit();
					*gas = u;
					Broodwar->sendText("Gas refinery found and set.");
				}
			}
		}
	}



	//Make mineral gatherers work
	for (auto &u : mineralWorkers)
	{
		BWAPI::Unit mine = (*u)->getClosestUnit(IsMineralField);
		if (u != NULL && (*u)->getHitPoints() == 0) {
			mineralWorkers.remove(u); 
			Broodwar->sendText("removed unit from mineral worker list"); 
		}
		else if ((*u)->isIdle()) {
			if ((*u)->isCarryingGas() || (*u)->isCarryingMinerals())
				(*u)->returnCargo();

			else (*u)->gather(mine);
		}
		else if ((*u)->isCarryingGas()) {
			(*u)->gather(mine); 
		}
	}
	
	//Make gas workers work
	for (auto &u : gasWorkers)
	{
		// Delete units from lists if they don't exist anymore: 
		/*if (u != NULL && (*u)->getHitPoints()==0) {
			gasWorkers.remove(u); 
			Broodwar->sendText("removed unit from gas worker list");
		} else*/ if ((*u)->isIdle()) { 
			if ((*u)->isCarryingGas() || (*u)->isCarryingMinerals())
				(*u)->returnCargo();

			else if (gas != NULL) {
				(*u)->rightClick(*gas);
				Broodwar->sendText("Right clicked gas on unit");	
			}
		}
		else if ((*u)->isCarryingMinerals() ){
			(*u)->rightClick(*gas); 
		}
	}	

	// Update limit to number of gasworkers: 
	if (Broodwar->self()->supplyUsed() >= 30) {
		gasWorkerLimit = 6; 
	}

	// Clean up gathering units (if some were destroyed) 

}



//Initial class setup
GatheringManager::GatheringManager()
{
}

GatheringManager::~GatheringManager()
{
}

