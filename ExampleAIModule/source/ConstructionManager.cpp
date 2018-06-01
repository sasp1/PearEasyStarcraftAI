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

BWAPI::UnitType orderedBuilding; //Type of building to be built next.
std::list<TimedUnit*> builders; //List of workers in the process of constructing buildings.

/**
* Returns workers to gatheringManager if construction is complete.
* If worker is idle, construct requested building.
* This assures that building is constructed, even though worker might be obstructed.
* @author Daniel Fjordhøj <s133198@dstudent.dtu.dk>
*/
void ConstructionManager::executeOrders() {

	//Loops through all builders. If builder is idle, and a certain time has passed
	//it is assigned back to the gatheringManager.
	for (auto &b : builders) {
		if (b->unit == NULL) {
			builders.remove(b);
			continue;
			Broodwar->sendText("Null unit: code 20");
		}
		if (b->isOverTime(500) && b->isUnitIdle()) {
			unitManager->newWorker(b->unit);
			builders.remove(b);
			Broodwar->sendText("Removed");
		}
	}

	/* Issues order to idle worker to construct building.
	If construction is a refinery, special order is íssued.
	*/

	if (NULL != (constructionsWorker) && (*constructionsWorker)->isIdle()) {

		if (orderedBuilding == UnitTypes::Terran_Refinery) {
			buildRefinery(constructionsWorker);
		}
		else {
			TilePosition targetBuildLocation = Broodwar->getBuildLocation(orderedBuilding, (*constructionsWorker)->getTilePosition());
			(*constructionsWorker)->build(orderedBuilding, targetBuildLocation);
		}
	}
}

/**
* Used bu unitManager to request the construction of a building
* @param building UnitType type of building to construct
* @param worker Unit worker assigned to this building
* @author Daniel Fjordhøj <s133198@dstudent.dtu.dk>
*/
void ConstructionManager::createBuilding(BWAPI::UnitType building, const BWAPI::Unit* worker) {
	/*Order received from unitManager.
	Saves building and worker, and issues order to worker to begin construction at available location. */

	//Save order params, and stops worker action

	if (NULL != worker) {
		constructionsWorker = worker;
		(*worker)->stop();
		TimedUnit* t = new TimedUnit(worker, Broodwar->getFrameCount());
		builders.push_back(t);
	}

	//Passing of extensions to buildingManager
	if (building == UnitTypes::Terran_Machine_Shop) {
		
	}
	else orderedBuilding = (building);
}

void ConstructionManager::expandBase() {

}

/**
* Used to construct a refinery, which only can exist at a geyser node
* @param worker Unit worker assigned to this building
* @author Daniel Fjordhøj <s133198@dstudent.dtu.dk>
*/
void ConstructionManager::buildRefinery(const BWAPI::Unit* worker) {
	//Find location of nearest geyser, and gets worker to build refinery on top of it.

	//Initializing variable, and sets distance to be virtually unllimited units away.
	BWAPI::Unit* gasLocation = new Unit();
	int distance = 10000;

	//Loop through all geysers, and if distance is smaller than last target, set this as new build target.
	for (auto &u : Broodwar->getGeysers())
	{
		if ((*worker)->getDistance(u) < distance) {
			*gasLocation = u;
			distance = (*worker)->getDistance(u);
		}
	}

	//If geyser is found, construct at location
	if (distance != 10000) {
		Broodwar->sendText("Refinery found");
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