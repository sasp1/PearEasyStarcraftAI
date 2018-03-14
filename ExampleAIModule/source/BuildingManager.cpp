#include "BuildingManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;

const BWAPI::Unit* commandCenter;

BuildingManager::BuildingManager()
{
}

BuildingManager::~BuildingManager()
{
}

void BuildingManager::addCommandCenter(const BWAPI::Unit* unit) {
	//Receive info about existing commandcenter (Change to all buildings)
	commandCenter = unit;
}

void BuildingManager::executeOrders() {
	//"Main" of this class
	BuildingManager::handleCommandCenter();
}


void BuildingManager::setBuildWorkers(bool buildWorkers) {
	//Change request to build borkers or not
	this->buildWorkers = buildWorkers;
}

void BuildingManager::handleCommandCenter() {
	//Issue orders for command center
	if (buildWorkers) {

	BWAPI::UnitType type = BWAPI::Broodwar->self()->getRace().getWorker();

	if ((*commandCenter)->isIdle())
		(*commandCenter)->train(type);
	}
}
