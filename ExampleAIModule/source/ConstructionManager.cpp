#include "ConstructionManager.h"
#include <BWAPI.h>

/**
* @file ConstructionManager.cpp
* @brief The manager who make the construction of a desired building. 
*
* @author  Thomas Dahl Heshe <s164399@gstudent.dtu.dk>

* @date 21/03/2018
*
*/


using namespace BWAPI;
using namespace Filter;

BWAPI::UnitType orderedBuilding;



void ConstructionManager::executeOrders() {
	
	
		if (NULL != (constructionsWorker) && (*constructionsWorker)->isIdle()) {

			if (orderedBuilding == UnitTypes::Terran_Refinery) {
				buildRefinery(constructionsWorker);
			}
			else
			{
				TilePosition targetBuildLocation = Broodwar->getBuildLocation(orderedBuilding, (*constructionsWorker)->getTilePosition());
				(*constructionsWorker)->build(orderedBuilding, targetBuildLocation);

			}
		}
}


void ConstructionManager::createBuilding(BWAPI::UnitType building, const BWAPI::Unit* worker) {
	//Receive an order to build a building, using a specific worker


	constructionsWorker = worker;
	(*worker)->stop();
	orderedBuilding = (building);


		
			//S�rg for, at n�r denne funktion kaldes, s� skal bygningen fors�ges bygges, indtil den succesfuldt bygges.
			//OBS RETURNERER BUILD EN BOOLEAN OM DET LYKKEDES??
			TilePosition targetBuildLocation = Broodwar->getBuildLocation(building, (*worker)->getTilePosition());
			(*worker)->build(building, targetBuildLocation);
		
	}


	/*
		//Try to build building
		if (building.isRefinery()) {
			ConstructionManager::buildRefinery(worker);
		}
		else {
		

			TilePosition targetBuildLocation = Broodwar->getBuildLocation(building, (*worker)->getTilePosition());
			(*worker)->build(building, targetBuildLocation);
			
		}

		*/
		
	
	
/*
const BWAPI::Unit* ConstructionManager::removeWorkersDoneConstructing()
{
	for (auto &u : workers)
	{
		if ((*u)->isIdle()) {
			const BWAPI::Unit* worker = u;
			workers.remove(u);
		
			return worker;
		}
	}
	return nullptr;
}
*/
void ConstructionManager::buildRefinery(const BWAPI::Unit* worker) {

	BWAPI::Unit* gasLocation = new Unit();
	int distance = 10000;

	for (auto &u : Broodwar->getGeysers())
	{
		if ((*worker)->getDistance(u) < distance) {
			*gasLocation = u;
			distance = (*worker)->getDistance(u);
		}
	}

	if (distance != 10000) {

		// Broodwar->sendText("Refinery");

		BWAPI::Position pos = (*gasLocation)->getPosition();

		TilePosition targetBuildLocation = Broodwar->getBuildLocation(UnitTypes::Terran_Refinery, (*gasLocation)->getTilePosition());
		(*worker)->build(UnitTypes::Terran_Refinery, targetBuildLocation);
	}
}

ConstructionManager::ConstructionManager()
{
	constructionsWorker = NULL;
}

ConstructionManager::~ConstructionManager()
{
}