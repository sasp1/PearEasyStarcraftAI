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
	//Tilføj bygning til liste over ejede bygninger, hvis den ikke er et supply depot.
	//Send besked om at bygning er bygget.

	if ((*u)->getType() == UnitTypes::Terran_Command_Center) {
		commandCenter = u;
		Broodwar->sendText("Hejsa %s", u);
	}

	if ((*u)->getType() == UnitTypes::Terran_Machine_Shop) {
		Broodwar->sendText("%s built Exp");
		expandFactory = false;
		desiredResearchs.push_front(TechTypes::Spider_Mines);
	}

	if ((*u)->getType() != UnitTypes::Terran_Supply_Depot)
	{
		buildings.push_back(u);
	}
}

void BuildingManager::executeOrders() {
	//"Main" of this class
	//Går igennem alle bygninger i buildings, og udfører handlinger baseret på bygningstype og spilstate
	bool foundFactory = false;

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

			if (((*b)->getType() == UnitTypes::Terran_Machine_Shop)) {
				if ((*b)->isIdle() && desiredResearchs.front() == TechTypes::Spider_Mines) {
					(*b)->research(TechTypes::Spider_Mines);
				}
			}

			if ((*b)->getType() == UnitTypes::Terran_Factory) {
				if ((*b)->isIdle()) {
					if (expandFactory && !foundFactory) {

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
							maxX++;
							maxY++;
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

						if (maxX > 100) maxX = 0;
						if (maxY > 100) maxY = 0;

						TilePosition f = (*b)->getTilePosition();
						f.y = f.y + y;
						f.x = f.x + x;

						TilePosition targetBuildLocation = Broodwar->getBuildLocation(UnitTypes::Terran_Machine_Shop, f);

						if (targetBuildLocation.isValid()) {
							(*b)->build(UnitTypes::Terran_Machine_Shop, f);
						}
					}

					else if (isDesiredToTrainVultures) {
						(*b)->train(UnitTypes::Terran_Vulture);
					}
				}
				foundFactory = true;
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