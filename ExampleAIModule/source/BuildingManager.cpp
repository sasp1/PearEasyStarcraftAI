#include "BuildingManager.h"
#include <BWAPI.h>
#include "Building.h"
#include "GatheringManager.h"
using namespace BWAPI;
using namespace Filter;
using namespace std;


int startBuildFrame;
int maxX = 0;
int maxY = 0;
int factories = 0;
bool addedMachineTech = false;
bool addedArmoryTech = false;


/**
* @file
* @author  Sebastian Arcos Specht <sebastian.a.specht@gmail.com>
*/

/**
* Adds building, if not a supply depot, to list of owned building upon construction.
* @param u Unit the building that is constructed
* @author Daniel Fjordhøj <s133198@dstudent.dtu.dk>
*/
void BuildingManager::buildingCreated(const BWAPI::Unit* u) {

	//Creates building class if not supply depot.
	if ((*u)->getType() != UnitTypes::Terran_Supply_Depot)
	{
		Building* b = new Building(u);
		if ((*u)->getType() == UnitTypes::Terran_Academy) addComSat = true;

		//Adds command center as separate variable
		if ((*u)->getType() == UnitTypes::Terran_Command_Center) {
			commandCenters.push_back(b);
			commandCenter = (commandCenters.front()->unit);
			gatheringManager->splitWorkers();
		}
		else {
			buildings.push_back(b);
			if ((*u)->getType() == UnitTypes::Terran_Armory) {
				if (!addedArmoryTech) {
					desiredUpgrades.push_back(UpgradeTypes::Terran_Vehicle_Weapons);
					desiredUpgrades.push_back(UpgradeTypes::Terran_Vehicle_Plating);
					addedArmoryTech = true;
				}
			}
			//If factory, adds request machine shop addon for first two factories.
			if ((*u)->getType() == UnitTypes::Terran_Factory) {
				factories++;
				if (factories < 3) {
					b->shouldBuildAddon = true;
					b->initAddon(UnitTypes::Terran_Machine_Shop);
				}
				(*u)->setRallyPoint((*scoutingManager).defendBasePosition);
			}
			//If machine shop, add researchs for first one.
			if ((*u)->getType() == UnitTypes::Terran_Machine_Shop) {
				if (!addedMachineTech) {
					desiredResearchs.push_front(TechTypes::Spider_Mines);
					desiredUpgrades.push_front(UpgradeTypes::Ion_Thrusters);
					addedMachineTech = true;
				}
			}
		}
	}
}


/**
* Issues orders to buildings based on type and state of the game.
* @author Daniel Fjordhøj <s133198@dstudent.dtu.dk>
*/

void BuildingManager::executeOrders() {

	if (drawTimer != -1) draw();

	//Clean command centers
	for (auto &b : commandCenters) if (!b->isUnitValid()) buildings.remove(b);


	if (addComSat)
	{
		commandCenters.front()->initAddon(UnitTypes::Terran_Comsat_Station);
		commandCenters.front()->shouldBuildAddon = true;
		addComSat = false;
	}

	for (auto &b : commandCenters) {
		//Command center orders
		if (isDesiredToTrainWorkers) b->trainType = UnitTypes::Terran_SCV;
		else b->trainType = UnitTypes::None;
		b->doCenterOrder();
	}

	for (auto &b : buildings) {

		if (!b->isUnitValid()) buildings.remove(b);
		else if ((*b->unit)->isIdle()) {
			const BWAPI::Unit* u = b->unit;

			//Barrack orders
			if (b->getType() == UnitTypes::Terran_Barracks) {
				if (barrackBuild != UnitTypes::None) {
					(*u)->train(barrackBuild);
				}
			}

			//Armory orderrs
			if ((*u)->getType() == UnitTypes::Terran_Armory) {
				if (desiredUpgrades.front() == UpgradeTypes::Terran_Vehicle_Weapons) {
					(*u)->upgrade(UpgradeTypes::Terran_Vehicle_Weapons);
					if ((*u)->isUpgrading()) desiredUpgrades.pop_front();
				}
				else if (desiredUpgrades.front() == UpgradeTypes::Terran_Vehicle_Plating) {
					(*u)->upgrade(UpgradeTypes::Terran_Vehicle_Plating);
					if ((*u)->isUpgrading()) desiredUpgrades.pop_front();
				}
				if (b->getType() == UnitTypes::Terran_Starport) {
					if (starportBuild != UnitTypes::None) {
						(*u)->train(starportBuild);
					}
				}
			}

				//Machine shop orders
				if ((b->getType() == UnitTypes::Terran_Machine_Shop)) {
					if (desiredResearchs.front() == TechTypes::Spider_Mines) {
						(*u)->research(TechTypes::Spider_Mines);
						if ((*u)->isResearching()) desiredResearchs.pop_front();
					}
					else if (desiredUpgrades.front() == UpgradeTypes::Ion_Thrusters) {
						(*u)->upgrade(UpgradeTypes::Ion_Thrusters);
						if ((*u)->isUpgrading())desiredUpgrades.pop_front();
					}
					else if (desiredResearchs.front() == TechTypes::Tank_Siege_Mode) {
						(*u)->research(TechTypes::Tank_Siege_Mode);
						if ((*u)->isUpgrading())desiredResearchs.pop_front();
					}
				}

				//Factory orders
				if (b->getType() == UnitTypes::Terran_Factory && (*b->unit)->isIdle()) {
					//Handle machiine shop build
					b->trainType = factoryBuild;
					b->doCenterOrder();
				}
			}
		}
	}



/**
* Execute orders for build manager
* @param buildWorkers that tells if a worker should be built.
*/
void BuildingManager::setIsDesiredToTrainWorkers(bool buildWorkers) {

	this->isDesiredToTrainWorkers = buildWorkers;
}


BuildingManager::BuildingManager()
{
	factoryBuild = UnitTypes::None;
	barrackBuild = UnitTypes::Terran_Marine;
	starportBuild = UnitTypes::None;

}

bool BuildingManager::scan(BWAPI::Position pos) {

	const BWAPI::Unit* u = new Unit((*commandCenter)->getAddon());

	if ((*u) == NULL) return false;

	bool res = (*u)->useTech(TechTypes::Scanner_Sweep, pos);
	if (res) {
		Broodwar->sendText("Scanned");
		drawTimer = 0;
		scanPoint = pos;
	}
	return res;
}

BuildingManager::~BuildingManager()
{
}

void BuildingManager::draw() {

	drawTimer++;

	if (drawTimer == 100) drawTimer = -1;
	Broodwar->drawCircleMap(scanPoint, 100, Colors::Purple, true);

}