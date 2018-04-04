#include "ConstructionManager.h"
#include <BWAPI.h>

/**
* @file ConstructionManager.cpp
* @brief The manager who make the construction of a desired building.
*
* @author  Thomas Dahl Heshe <s164399@gstudent.dtu.dk>

* @date 21/03/2018
*
*/


using namespace BWAPI;
using namespace Filter;

BWAPI::UnitType orderedBuilding;

void ConstructionManager::executeOrders() {

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