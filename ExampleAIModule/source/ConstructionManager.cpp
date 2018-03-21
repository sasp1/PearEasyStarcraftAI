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
	bool hasBuilt = false;

	if (building.isRefinery()) {
		ConstructionManager::buildRefinery(worker);
	}
	else {

		while (!hasBuilt) {
			//Sørg for, at når denne funktion kaldes, så skal bygningen forsøges bygges, indtil den succesfuldt bygges.
			//OBS RETURNERER BUILD EN BOOLEAN OM DET LYKKEDES??
			TilePosition targetBuildLocation = Broodwar->getBuildLocation(building, (*worker)->getTilePosition());
			hasBuilt = (*worker)->build(building, targetBuildLocation);
		}
	}
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

void ConstructionManager::buildRefinery(const BWAPI::Unit* worker) {

	BWAPI::UnitType building = Broodwar->self()->getRace().getRefinery();

	TilePosition targetBuildLocation = Broodwar->getBuildLocation(building, (*worker)->getTilePosition());
	(*worker)->build(building, targetBuildLocation);

}

ConstructionManager::ConstructionManager()
{
}

ConstructionManager::~ConstructionManager()
{
}