#include "ConstructionManager.h"
#include <BWAPI.h>
#include "Worker.h"
#include "BuildingManager.h"
#include "UnitManager.h"

/**
* @file ConstructionManager.cpp
* @brief Manager that handles construction of buildings,
* and forwarding of addons.
* @author  Daniel Fjordhøj <s133198gstudent.dtu.dk>
*/

using namespace BWAPI;
using namespace Filter;

std::list<Worker*> builders; //List of workers in the process of constructing buildings.

/**
* Clean up, and order assigning of all controlled units
* @author Daniel Fjordhøj <s133198@dstudent.dtu.dk>
*/
void ConstructionManager::executeOrders() {

	for (auto &b : builders) {
		if (b == NULL) {
			builders.remove(b);
			break;
		}
		else if (!b->isValid()) {
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

/**
* Assigns newly begun construction to unitwho builds it
* @author Daniel Fjordhøj <s133198@dstudent.dtu.dk>
* */
void ConstructionManager::constructionBegun(BWAPI::Unit build) {

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
* Used by unitManager to request the construction of a building
* @param building UnitType type of building to construct
* @param worker Unit worker assigned to this building
* @author Daniel Fjordhøj <s133198@dstudent.dtu.dk>
*/
void ConstructionManager::createBuilding(BWAPI::UnitType building, const BWAPI::Unit* worker) {
	
	if (*worker != NULL) {

	(*worker)->stop();

	//Execute proper build init, based on building type
	if (building == BWAPI::UnitTypes::Terran_Command_Center) {
		expandBase(worker);
	}
	else if (building == BWAPI::UnitTypes::Terran_Refinery) {
		buildRefinery(worker);
	}
	else if (building == BWAPI::UnitTypes::Terran_Comsat_Station) {
		buildingManager->addComSat = true;
	}
	else {
		Worker* w = new Worker(worker);
		if((*worker)->getPosition().isValid()) w->initBuild(building, (*worker)->getPosition());
		else w->initBuild(building, (*buildingManager->commandCenter)->getPosition());
		builders.push_back(w);
		Broodwar->sendText("worker request");
	}
	}
}

/**
* Request from Worker to replace killed unit. 
* @param w Worker Object with a killed unit
* @author Daniel Fjordhøj <s133198@dstudent.dtu.dk>
*/
void ConstructionManager::requestFromDead(Worker* w) {
	w->unit = gatheringManager->removeWorker();
}

/**
* Initialize construction of new command center.
* @param Unit worker Worker to build construction
* @author Daniel Fjordhøj <s133198@dstudent.dtu.dk>
*/
void ConstructionManager::expandBase(const BWAPI::Unit* worker) {

	BWAPI::Position p = scoutingManager->expandBasePosition;

	Worker* w = new Worker(worker);
	w->initBuild(UnitTypes::Terran_Command_Center, p);
	builders.push_back(w);
}

void ConstructionManager::buildRefinery(const BWAPI::Unit* worker) {

	//Init closest geyserobject
	BWAPI::Unit* gasLocation = new Unit();

	//Set compare distance to current target to be virtual unlimited
	int distance = 10000;

	//Get last built command center.
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

		Worker* w = new Worker(worker);
		w->initBuild(UnitTypes::Terran_Refinery, (*gasLocation)->getPosition());
		builders.push_back(w);
	}
}

ConstructionManager::ConstructionManager()
{
}

ConstructionManager::~ConstructionManager()
{
}