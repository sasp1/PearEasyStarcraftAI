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
* @version 1.0
*
* @section DESCRIPTION
*
* The time class represents a moment of time.
*/
void BuildingManager::buildingCreated(const BWAPI::Unit* u) {
	//Tilf�j bygning til liste over ejede bygninger, hvis den ikke er et supply depot.
	//Send besked om at bygning er bygget.

	if ((*u)->getType() == UnitTypes::Terran_Command_Center) {
		commandCenter = u;
	}

	if ((*u)->getType() == UnitTypes::Terran_Machine_Shop && expandFactory) {
		Broodwar->sendText("%s built Exp");
		desiredResearchs.push_front(TechTypes::Spider_Mines);
		desiredUpgrades.push_front(UpgradeTypes::Ion_Thrusters);
		expandFactory = false;
	}

	if ((*u)->getType() != UnitTypes::Terran_Supply_Depot)
	{
		buildings.push_back(u);
	
	}
}

void BuildingManager::executeOrders() {
	//"Main" of this class
	//G�r igennem alle bygninger i buildings, og udf�rer handlinger baseret p� bygningstype og spilstate
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
					if((*b)->isResearching()) desiredResearchs.pop_front();
				}
				else if ((*b)->isIdle() && desiredUpgrades.front() == UpgradeTypes::Ion_Thrusters) {
						(*b)->upgrade(UpgradeTypes::Ion_Thrusters);
						if((*b)->isUpgrading())desiredUpgrades.pop_front();
				}
			}

			if ((*b)->getType() == UnitTypes::Terran_Factory) {
				if ((*b)->isIdle()) {
					if ((*b)->getAddon() == NULL){

						(*b)->buildAddon(UnitTypes::Terran_Machine_Shop);

						if ((*b)->isIdle()) {

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

						TilePosition f = (*b)->getTilePosition();
						f.y = f.y + y;
						f.x = f.x + x;

						TilePosition targetBuildLocation = Broodwar->getBuildLocation(UnitTypes::Terran_Machine_Shop, f);

						if (targetBuildLocation.isValid()) {
							(*b)->build(UnitTypes::Terran_Machine_Shop, f);
						}
						
						}
					}

					else if (isDesiredToTrainVultures) {
						(*b)->train(UnitTypes::Terran_Vulture);
					}
				}

				if (foundFactory) {
					(*b)->setRallyPoint((*factory)->getRallyPosition());
				}
				else factory = b;

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