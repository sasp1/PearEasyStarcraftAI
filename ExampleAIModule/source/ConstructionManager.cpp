#include "ConstructionManager.h"
#include <BWAPI.h>
#include "TimedUnit.h"
#include "BuildingManager.h"
#include "UnitManager.h"

/**
* @file ConstructionManager.cpp
* @brief The manager who make the construction of a desired building.
*
* @author  Thomas Dahl Heshe <s164399@gstudent.dtu.dk>
*
*/

std::list<int> startTime;

using namespace BWAPI;
using namespace Filter;

BWAPI::UnitType orderedBuilding;
std::list<TimedUnit*> builders;

//void ConstructionManager::setManagers(BuildingManager* b, UnitManager* u) {
//	buildingManager =b;
//    //unitManager = u;
//}

void ConstructionManager::executeOrders() {

	for (auto &b : builders) {

		if (b->unit == NULL) {
			builders.remove(b);
			continue;
			Broodwar->sendText("Null");
		}
		if (b->isOverTime(500) && b->isUnitIdle()) {
			unitManager->newWorker(b->unit);
			builders.remove(b);
			Broodwar->sendText("Removed");
		}
	}


	//Hvis vi har kontrol over en worker, og han ikke laver noget, så sættes han igang med at bygge bygningen specificeret i orderedBuilding
	if (NULL != (constructionsWorker) && (*constructionsWorker)->isIdle()) {

		if (orderedBuilding == UnitTypes::Terran_Refinery) {
			buildRefinery(constructionsWorker);
		}
		else if (orderedBuilding == UnitTypes::Terran_Machine_Shop) {
			buildingManager->expandFactory = true;
		}
		else
		{
			TilePosition targetBuildLocation = Broodwar->getBuildLocation(orderedBuilding, (*constructionsWorker)->getTilePosition());
			(*constructionsWorker)->build(orderedBuilding, targetBuildLocation);

		}
	}
	
}

void ConstructionManager::createBuilding(BWAPI::UnitType building, const BWAPI::Unit* worker) {
	//Find et sted hvor bygningen kan placeres, og sæt worker til at bygge den.

	constructionsWorker = worker;
	(*worker)->stop();
	orderedBuilding = (building);
	TilePosition targetBuildLocation = Broodwar->getBuildLocation(building, (*worker)->getTilePosition());
	(*worker)->build(building, targetBuildLocation);


	TimedUnit* t = new TimedUnit(worker, Broodwar->getFrameCount());
	builders.push_back(t);

}

void ConstructionManager::expandBase() {

}

void ConstructionManager::buildRefinery(const BWAPI::Unit* worker) {

	BWAPI::Unit* gasLocation = new Unit();
	int distance = 10000;

	for (auto &u : Broodwar->getGeysers())
	{
		if ((*worker)->getDistance(u) < distance) {
			*gasLocation = u;
			distance = (*worker)->getDistance(u);
		}
	}

	if (distance != 10000) {

		// Broodwar->sendText("Refinery");

		BWAPI::Position pos = (*gasLocation)->getPosition();

		TilePosition targetBuildLocation = Broodwar->getBuildLocation(UnitTypes::Terran_Refinery, (*gasLocation)->getTilePosition());
		(*worker)->build(UnitTypes::Terran_Refinery, targetBuildLocation);
	}
}

ConstructionManager::ConstructionManager()
{
	constructionsWorker = NULL;
}

ConstructionManager::~ConstructionManager()
{
}