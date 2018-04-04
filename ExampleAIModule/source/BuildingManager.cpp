#include "BuildingManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;
using namespace std;

std::list<const BWAPI::Unit*> buildings;

/**
* @file
* @author  Sebastian Arcos Specht <sebastian.a.specht@gmail.com>
* @version 1.0
*
* @section DESCRIPTION
*
* The time class represents a moment of time.
*/
void BuildingManager::buildingCreated(const BWAPI::Unit* u) {

	if ((*u)->getType() != UnitTypes::Terran_Supply_Depot)
	{
		buildings.push_back(u);
		Broodwar->sendText("%s", "Building completed");
	}

	Broodwar->sendText("%s", "Depot completed");
}

void BuildingManager::executeOrders() {
	//"Main" of this class
	for (auto &b : buildings) {

		if (*b != NULL) {

			if ((*b)->getType() == UnitTypes::Terran_Command_Center && isDesiredToTrainWorkers) {
				if ((*b)->isIdle()) {
					(*b)->train(UnitTypes::Terran_SCV);
				}
			}
			if (((*b)->getType() == UnitTypes::Terran_Barracks && isDesiredToTrainMarines)) {
				if ((*b)->isIdle()) {
					(*b)->train(UnitTypes::Terran_Marine);
				}
			}
			if (((*b)->getType() == UnitTypes::Terran_Factory && isDesiredToTrainVultures)) {
				if ((*b)->isIdle()) {
					(*b)->train(UnitTypes::Terran_Vulture);
				}
			}
		}
	}
}

/**
* Execute orders for build manager
*
* @param buildWorkers that tells if a worker should be built.
*/
void BuildingManager::setIsDesiredToTrainWorkers(bool buildWorkers) {
	//Change request to build borkers or not
	this->isDesiredToTrainWorkers = buildWorkers;
}

void BuildingManager::setIsDesiredToTrainMarines(bool trainWorkers) {
	//Change request to build borkers or not
	this->isDesiredToTrainMarines = trainWorkers;
}

void BuildingManager::setIsDesiredToTrainVultures(bool trainVultures) {
	//Change request to build borkers or not
	this->isDesiredToTrainVultures = trainVultures;
}

//Initial class setup
BuildingManager::BuildingManager()
{
}

BuildingManager::~BuildingManager()
{
}