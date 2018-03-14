#include "BuildingManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;
using namespace std;

const BWAPI::Unit* commandCenter;
const BWAPI::Unit* barracks;
int nrOfBarracks = 0;

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

	if ((*u)->getType() == UnitTypes::Terran_Barracks) {
		Broodwar->sendText("%s", "Completed building barracks");
		addBarracks(u);
	}



	if ((*u)->getType() == UnitTypes::Terran_Supply_Depot) {
		Broodwar->sendText("%s", "Completed building supl. depot");

	}
}


void BuildingManager::addCommandCenter(const BWAPI::Unit* unit) {
	//Receive info about existing commandcenter (Change to all buildings)
	commandCenter = unit;
}

void BuildingManager::addBarracks(const BWAPI::Unit* barracksUnit) {
	barracks = (barracksUnit);
	nrOfBarracks++;
}


void BuildingManager::executeOrders() {
	//"Main" of this class
	BuildingManager::handleCommandCenter();

	if (nrOfBarracks > 0 && isDesiredToTrainMarines)
	(*barracks)->train(UnitTypes::Terran_Marine);

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

void BuildingManager::handleCommandCenter() {
	//Issue orders for command center
	if (isDesiredToTrainWorkers) {

	BWAPI::UnitType type = BWAPI::Broodwar->self()->getRace().getWorker();

	if ((*commandCenter)->isIdle())
		(*commandCenter)->train(type);
	}
}


//Initial class setup
BuildingManager::BuildingManager()
{
}

BuildingManager::~BuildingManager()
{
}