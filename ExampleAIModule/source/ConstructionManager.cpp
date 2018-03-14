#include "ConstructionManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;

std::list<const BWAPI::Unit*> constructionWorkers;


ConstructionManager::ConstructionManager()
{
}

ConstructionManager::~ConstructionManager()
{
}

void ConstructionManager::createBuilding(BWAPI::UnitType building, const BWAPI::Unit* worker) {
	//Receive an order to build a building, using a specific worker

	constructionWorkers.push_back(worker);

	TilePosition targetBuildLocation = Broodwar->getBuildLocation(building, (*worker)->getTilePosition());
	(*worker)->build(building, targetBuildLocation);

}

const BWAPI::Unit* ConstructionManager::removeWorkersDoneConstructing()
{
	for (auto &u : constructionWorkers)
	{
		if ((*u)->isIdle()) {
			const BWAPI::Unit* worker = u;
			constructionWorkers.remove(u);
		
			return worker;
		}
	}
	return nullptr;
}

