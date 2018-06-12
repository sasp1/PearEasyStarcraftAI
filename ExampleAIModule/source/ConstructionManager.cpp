#include "ConstructionManager.h"
#include <BWAPI.h>
#include "Worker.h"
#include "BuildingManager.h"
#include "UnitManager.h"

/**
* @file ConstructionManager.cpp
* @brief Handles construction of requested buildings, 
* and workers assigned to build them.
* @author Daniel Fjordhøj <s133198gstudent.dtu.dk>
*/

using namespace BWAPI;
using namespace Filter;

std::list<Worker*> builders; //List of workers in the process of constructing buildings.
std::list<Worker*> removeBuilders;
/**
* Clean up, and assign orders to controlled units
* @author Daniel Fjordhøj <s133198@dstudent.dtu.dk>
*/
void ConstructionManager::executeOrders() {

	//Prepare temp list
	removeBuilders.clear();

	//Find invalid workers, and add them to temp list
	for (auto &b : builders) {
		if (b == NULL) removeBuilders.push_back(b);

		else if (!b->isValid()) removeBuilders.push_back(b);

		//If not invalid continue with construction
		else if (b->handleBuild()) {
			const BWAPI::Unit* u = new Unit();
			u = b->unit;
			unitManager->newWorker(u);
			removeBuilders.push_back(b);
		}
	}

	//Remove units in temp list
	for (auto &b : removeBuilders) builders.remove(b);
}

/**
* Assigns newly begun construction to unit who is building it
* @author Daniel Fjordhøj <s133198@dstudent.dtu.dk>
* */
void ConstructionManager::constructionBegun(BWAPI::Unit build) {

	const BWAPI::Unit* newBuild = new Unit(build);
	bool isAssigned = false;

	//Assign building in construction to unit constructing building of that type 
	for (auto &u : builders) {
		if (u->construct == NULL && ((*newBuild)->getType() == u->buildOrder) && !isAssigned) {
			u->construct = newBuild;
			isAssigned = true;
		}
	}
}

/**
* Used by unitManager to request the construction of a building
* @param building UnitType type of building to construct
* @param worker Unit worker assigned to this building
* @author Daniel Fjordhøj <s133198@dstudent.dtu.dk>
*/
void ConstructionManager::createBuilding(BWAPI::UnitType building, const BWAPI::Unit* worker) {

	//Stop workers action
	if (*worker != NULL) {
		(*worker)->stop();

		//Perform unique action for special buildings
		if (building == BWAPI::UnitTypes::Terran_Command_Center) {
			expandBase(worker);
		}
		else if (building == BWAPI::UnitTypes::Terran_Refinery) {
			buildRefinery(worker);
		}
		else if (building == BWAPI::UnitTypes::Terran_Comsat_Station) {
			buildingManager->addComSat = true;
		}

		//Attempt build at location for ordinary building types, and add worker to list
		else {
			Worker* w = new Worker(worker);
			w->initBuild(building, (*worker)->getPosition());
			builders.push_back(w);
		}
	}
}

void ConstructionManager::createBuildingAtPos(BWAPI::UnitType building, const BWAPI::Unit* worker, BWAPI::Position pos) {
	//Request construction af building at a specific location, and add worker to list
	Worker* w = new Worker(worker);
	w->initBuild(building, pos);
	builders.push_back(w);
}

void ConstructionManager::requestFromDead(Worker* w) {
	//Replace worker with new from gatheringmanager
	w->unit = gatheringManager->removeWorker();
}

/**
* Initialize construction of new command center.
* @param Unit worker Worker to build construction
* @author Daniel Fjordhøj <s133198@dstudent.dtu.dk>
*/
void ConstructionManager::expandBase(const BWAPI::Unit* worker) {

	//Issue order to build commandcenter at given location, and add worker to list
	Worker* w = new Worker(worker);
	BWAPI::Position p = scoutingManager->expandBasePosition;
	w->initBuild(UnitTypes::Terran_Command_Center, p);
	builders.push_back(w);
}

void ConstructionManager::buildRefinery(const BWAPI::Unit* worker) {

	//Init geyserobject, and set compare distance to be virtual unlimited
	BWAPI::Unit* gasLocation = new Unit();
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

	//If geyser is found, construct at location, and add worker to list
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