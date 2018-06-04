#include "BuildingManager.h"
#include <BWAPI.h>
#include "Building.h"
using namespace BWAPI;
using namespace Filter;
using namespace std;

std::list<Building*> buildings;
int startBuildFrame;
int maxX = 0;
int maxY = 0;
bool startedBuild;
int factories = 0;
bool addedMachineTech = false;

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

	//Adds command center as separate variable
	if ((*u)->getType() == UnitTypes::Terran_Command_Center) {
		commandCenter = u;
	}

	//Adds building, if not supply depot, to owned list.
	if ((*u)->getType() != UnitTypes::Terran_Supply_Depot)
	{
		Building* b = new Building(u);
		buildings.push_back(b);

		//If factory, adds request machine shop addon for first two factories.
		if ((*u)->getType() == UnitTypes::Terran_Factory) {
			factories++;
			b->buildAddon = factories < 3;
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

/**
* Issues orders to buildings based on type and state of the game.
* @author Daniel Fjordhøj <s133198@dstudent.dtu.dk>
*/
void BuildingManager::executeOrders() {

	for (auto &b : buildings) {

		if (!b->isUnitValid()) {
			buildings.remove(b);
		}
		else if (b->isUnitIdle()) {
			//Command center orders
			if (b->getType() == UnitTypes::Terran_Command_Center && isDesiredToTrainWorkers) {
				b->getUnit()->train(UnitTypes::Terran_SCV);
			}
			//Barrack orders
			if (b->getType() == UnitTypes::Terran_Barracks) {
				if (barrackBuild != UnitTypes::None) {
					b->getUnit()->train(barrackBuild);
				}
			}

			//Machine shop orders
			if ((b->getType() == UnitTypes::Terran_Machine_Shop)) {
				if (desiredResearchs.front() == TechTypes::Spider_Mines) {
					b->getUnit()->research(TechTypes::Spider_Mines);
					if (b->getUnit()->isResearching()) desiredResearchs.pop_front();
				}
				else if (desiredUpgrades.front() == UpgradeTypes::Ion_Thrusters) {
					b->getUnit()->upgrade(UpgradeTypes::Ion_Thrusters);
					if (b->getUnit()->isUpgrading())desiredUpgrades.pop_front();
				}
				else if (desiredUpgrades.front() == TechTypes::Tank_Siege_Mode) {
					b->getUnit()->research(TechTypes::Tank_Siege_Mode);
					if (b->getUnit()->isUpgrading())desiredResearchs.pop_front();
				}
			}

			//Factory orders
			if (b->getType() == UnitTypes::Terran_Factory) {
				//Handle machiine shop build
				if (b->getUnit()->getAddon() == NULL && b->buildAddon) {

					//Build if possible at location, else initiate spiral search
					if (b->getUnit()->buildAddon(UnitTypes::Terran_Machine_Shop)) {
					}
					else if (b->isUnitIdle()) {
						TilePosition loc = b->getUnit()->getTilePosition() + spiralSearch();
						TilePosition targetBuildLocation = Broodwar->getBuildLocation(UnitTypes::Terran_Machine_Shop, loc);

						if (targetBuildLocation.isValid()) {
							b->getUnit()->build(UnitTypes::Terran_Machine_Shop, targetBuildLocation);
						}
					}
				}

				//Handle unit production
				else if (factoryBuild != NULL) {
					b->getUnit()->train(factoryBuild);
				}
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

BWAPI::TilePosition BuildingManager::spiralSearch() {

	if (!startedBuild) {
		startBuildFrame = 0;
		maxX = 0;
		maxY = 0;
		startedBuild = true;
	}

	startBuildFrame++;
	int frameDelta = startBuildFrame % 8;

	int x;
	int y;

	if (frameDelta == 0) {
		maxX += 0.5;
		maxY += 0.5;
		x = maxX;
		y = maxY;
	}

	else if (frameDelta == 1) x = 0;
	else if (frameDelta == 2) x = -maxX;
	else if (frameDelta == 3) y = 0;
	else if (frameDelta == 4) y = -maxY;
	else if (frameDelta == 5) x = 0;
	else if (frameDelta == 6) x = maxX;
	else if (frameDelta == 7) y = 0;

	if (maxX > 50) maxX = 0;
	if (maxY > 50) maxY = 0;

	BWAPI::TilePosition coords = TilePosition(maxX, maxY);;

	return coords;;
}

BuildingManager::BuildingManager()
{
	factoryBuild = UnitTypes::None;;
	barrackBuild = UnitTypes::Terran_Marine;;

}

BuildingManager::~BuildingManager()
{
}