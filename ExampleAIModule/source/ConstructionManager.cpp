#include "ConstructionManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;

std::list<const BWAPI::Unit*> workers;

void ConstructionManager::executeOrders() {

}

void ConstructionManager::createBuilding(BWAPI::UnitType building, const BWAPI::Unit* worker) {
	//Receive an order to build a building, using a specific worker

	workers.push_back(worker);

	
	//S�rg for, at n�r denne funktion kaldes, s� skal bygningen fors�ges bygges, indtil den succesfuldt bygges.
	//OBS RETURNERER BUILD EN BOOLEAN OM DET LYKKEDES??
	TilePosition targetBuildLocation = Broodwar->getBuildLocation(building, (*worker)->getTilePosition());
	(*worker)->build(building, targetBuildLocation);

}

const BWAPI::Unit* ConstructionManager::removeWorkersDoneConstructing()
{
	for (auto &u : workers)
	{
		if ((*u)->isIdle()) {
			const BWAPI::Unit* worker = u;
			workers.remove(u);
		
			return worker;
		}
	}
	return nullptr;
}

ConstructionManager::ConstructionManager()
{
}

ConstructionManager::~ConstructionManager()
{
}