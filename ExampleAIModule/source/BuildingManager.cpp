#include "BuildingManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;
using namespace std;

std::list<const BWAPI::Unit*> buildings;
int startBuildFrame;
int maxX = 0;
int maxY = 0;
bool startedBuild;
const BWAPI::Unit* factory;

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

	//Adds researchs upon machine shop build.
	if ((*u)->getType() == UnitTypes::Terran_Machine_Shop && expandFactory) {
		desiredResearchs.push_front(TechTypes::Spider_Mines);
		desiredUpgrades.push_front(UpgradeTypes::Ion_Thrusters);
		expandFactory = false;
	}

	//Adds building, if not supply depot, to owned list.
	if ((*u)->getType() != UnitTypes::Terran_Supply_Depot)
	{
		buildings.push_back(u);
	}
}

/**
* Issues orders to buildings based on type and state of the game.
* @author Daniel Fjordhøj <s133198@dstudent.dtu.dk>
*/
void BuildingManager::executeOrders() {

	bool foundFactory = false;
	for (auto &b : buildings) {

		if (*b != NULL) {
			//Command center orders
			if ((*b)->getType() == UnitTypes::Terran_Command_Center && isDesiredToTrainWorkers) {
				if ((*b)->isIdle()) {
					(*b)->train(UnitTypes::Terran_SCV);
				}
			}
			//Barrack orders
			if ((*b)->getType() == UnitTypes::Terran_Barracks) {
				if (barrackBuild != NULL && (*b)->isIdle()) {
					(*b)->train(barrackBuild);
				}
			}

			//Machine shop orders
			if (((*b)->getType() == UnitTypes::Terran_Machine_Shop)) {
				if ((*b)->isIdle() && desiredResearchs.front() == TechTypes::Spider_Mines) {
					(*b)->research(TechTypes::Spider_Mines);
					if ((*b)->isResearching()) desiredResearchs.pop_front();
				}
				else if ((*b)->isIdle() && desiredUpgrades.front() == UpgradeTypes::Ion_Thrusters) {
					(*b)->upgrade(UpgradeTypes::Ion_Thrusters);
					if ((*b)->isUpgrading())desiredUpgrades.pop_front();
				}
			}
			//Factory orders
			if ((*b)->getType() == UnitTypes::Terran_Factory) {
				if ((*b)->isIdle()) {

					//Handle machiine shop build
					if ((*b)->getAddon() == NULL) {

						//Build if possible at location, else initiate spiral search
						(*b)->buildAddon(UnitTypes::Terran_Machine_Shop);

						if ((*b)->isIdle()) {
							TilePosition loc = (*b)->getTilePosition() + spiralSearch();
							TilePosition targetBuildLocation = Broodwar->getBuildLocation(UnitTypes::Terran_Machine_Shop, loc);

							if (targetBuildLocation.isValid()) {
								(*b)->build(UnitTypes::Terran_Machine_Shop, targetBuildLocation);
							}
						}
					}
				
					//Handle unit production
					else if (factoryBuild != NULL) {
						(*b)->train(factoryBuild);
					}
				}
				foundFactory = true;
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
	factoryBuild = NULL;
	barrackBuild = UnitTypes::Terran_Marine;;
}

BuildingManager::~BuildingManager()
{
}