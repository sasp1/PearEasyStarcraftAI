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

	//Creates building class if not supply depot.
	if ((*u)->getType() != UnitTypes::Terran_Supply_Depot)
	{
		Building* b = new Building(u);

		//Adds command center as separate variable
		if ((*u)->getType() == UnitTypes::Terran_Command_Center) {
			commandCenters.push_back(b);
			commandCenter = (commandCenters.front()->unit);
			gatheringManager->splitWorkers();
		}
		else {
			buildings.push_back(b);

			//If factory, adds request machine shop addon for first two factories.
			if ((*u)->getType() == UnitTypes::Terran_Factory) {
				factories++;
				b->buildAddon = factories < 3;
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

		for (auto &b : commandCenters) {

			if (!b->isUnitValid()) {
				buildings.remove(b);
			}
		}

		if (addComSat && (*commandCenters.front()->unit)->isIdle())
		{
			if ((*commandCenters.front()->unit)->getAddon() == NULL)
				(*commandCenters.front()->unit)->buildAddon(UnitTypes::Terran_Comsat_Station);
		}

		for (auto &b : commandCenters) {
			//Command center orders
			if (isDesiredToTrainWorkers && (*b->unit)->isIdle()) {
				const BWAPI::Unit* u = b->unit;
				(*u)->train(UnitTypes::Terran_SCV);
			}
		}

		for (auto &b : buildings) {

			if (!b->isUnitValid()) {
				buildings.remove(b);
			}
			else if ((*b->unit)->isIdle()) {
				const BWAPI::Unit* u = b->unit;

				//Barrack orders
				if (b->getType() == UnitTypes::Terran_Barracks) {
					if (barrackBuild != UnitTypes::None) {
						(*u)->train(barrackBuild);
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
				if (b->getType() == UnitTypes::Terran_Factory) {
					//Handle machiine shop build
					if ((*u)->getAddon() == NULL && b->buildAddon) {

						//Build if possible at location, else initiate spiral search
						if ((*u)->buildAddon(UnitTypes::Terran_Machine_Shop)) {
						}
						else if ((*b->unit)->isIdle()) {
							TilePosition loc = (*u)->getTilePosition() + spiralSearch();
							TilePosition targetBuildLocation = Broodwar->getBuildLocation(UnitTypes::Terran_Machine_Shop, loc);

							if (targetBuildLocation.isValid()) {
								(*u)->build(UnitTypes::Terran_Machine_Shop, targetBuildLocation);
							}
						}
					}

					//Handle unit production
					else if (factoryBuild != NULL) {
						(*u)->train(factoryBuild);
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