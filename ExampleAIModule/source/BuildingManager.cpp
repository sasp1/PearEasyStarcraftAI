#include "BuildingManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;
using namespace std;

const BWAPI::Unit* commandCenter;
const BWAPI::Unit* barracks;
int nrOfBarracks = 0;


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

	if (nrOfBarracks > 0)
	(*barracks)->train(UnitTypes::Terran_Marine);

}

void BuildingManager::setIsDesiredToBuildWorkers(bool buildWorkers) {
	//Change request to build borkers or not
	this->isDesiredToBuildWorkers = buildWorkers;
}

void BuildingManager::handleCommandCenter() {
	//Issue orders for command center
	if (isDesiredToBuildWorkers) {

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