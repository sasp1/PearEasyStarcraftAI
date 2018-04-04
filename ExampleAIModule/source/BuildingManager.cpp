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
	//Tilf�j bygning til liste over ejede bygninger, hvis den ikke er et supply depot.
	//Send besked om at bygning er bygget.


	if ((*u)->getType() == UnitTypes::Terran_Machine_Shop) {
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
				}
			}

			if (((*b)->getType() == UnitTypes::Terran_Factory) ) {

				

				if (expandFactory && (NULL == (*b)->getAddon()) && !foundFactory) {
					int x = rand() % 10;
					int y = rand() % 10;
					foundFactory = true;
					TilePosition targetBuildLocation = Broodwar->getBuildLocation(UnitTypes::Terran_Machine_Shop, (*b)->getTilePosition() + TilePosition(x,y));
					(*b)->build(UnitTypes::Terran_Machine_Shop, targetBuildLocation);

				}
				else if ((*b)->isIdle() && isDesiredToTrainVultures) {
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