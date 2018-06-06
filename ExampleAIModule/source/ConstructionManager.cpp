#include "ConstructionManager.h"
#include <BWAPI.h>
#include "Worker.h"
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
std::list<Worker*> builders; //List of workers in the process of constructing buildings.

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
		if (b == NULL) {
			builders.remove(b);
			break;
		}
		else if (b->unit == NULL) {
			builders.remove(b);
			break;
		} 
		else if (b->handleBuild()) {
			const BWAPI::Unit* u = new Unit();
			u = b->unit;
			unitManager->newWorker(u);
			builders.remove(b);
			break;
		}
	}
}

void ConstructionManager::constructiondBegun(BWAPI::Unit build) {

	const BWAPI::Unit* newBuild = new Unit(build);
	bool isAssigned = false;

	for (auto &u : builders) {
		if (u->construct == NULL && ((*newBuild)->getType() == u->buildOrder)) {
			u->construct = newBuild;
			isAssigned = true;
		}
		if (isAssigned) break;
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
	(*worker)->stop();

	//Save order params, and stops worker action
	if (building == BWAPI::UnitTypes::Terran_Command_Center) {
		expandBase(worker);
	}
	//Save order params, and stops worker action
	else if (building == BWAPI::UnitTypes::Terran_Refinery) {
		buildRefinery(worker);
	}
	else {
		Worker* t = new Worker(worker);
		t->buildOrder = building;
		t->workState = 2;
		builders.push_back(t);
	}
}

void ConstructionManager::requestFromDead(Worker* w) {

	w->unit = gatheringManager->removeWorker();


}

void ConstructionManager::expandBase(const BWAPI::Unit* worker) {

	BWAPI::Position p = scoutingManager->expandBasePosition;

	Worker* w = new Worker(worker);
	w->buildOrder = UnitTypes::Terran_Command_Center;
	w->pos = p;
	w->workState = 2;
	builders.push_back(w);
}

void ConstructionManager::buildRefinery(const BWAPI::Unit* worker) {

	BWAPI::Unit* gasLocation = new Unit();
	int distance = 10000;

	const BWAPI::Unit* cc = buildingManager->commandCenters.back()->unit;

	//Loop through all geysers, and if distance is smaller than last target, set this as new build target.
	for (auto &u : Broodwar->getGeysers())
	{
		if ((*cc)->getDistance(u) < distance) {
			*gasLocation = u;
			distance = (*cc)->getDistance(u);
		}
	}


	//If geyser is found, construct at location
	if (distance != 10000) {
		BWAPI::Position pos = (*gasLocation)->getPosition();
		TilePosition tLoc = Broodwar->getBuildLocation(UnitTypes::Terran_Refinery, (*gasLocation)->getTilePosition());
		Worker* w = new Worker(worker);
		w->buildOrder = UnitTypes::Terran_Refinery;
		w->tilePos = tLoc;
		w->pos = (*gasLocation)->getPosition();
		w->workState = 2;
		builders.push_back(w);
	}
}

ConstructionManager::ConstructionManager()
{
}

ConstructionManager::~ConstructionManager()
{
}