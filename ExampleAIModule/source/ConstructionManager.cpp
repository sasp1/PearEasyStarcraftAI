#include "ConstructionManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;

BWAPI::UnitType orderedBuilding;



void ConstructionManager::executeOrders() {
	
	
		if (NULL != (constructionsWorker) && (*constructionsWorker)->isIdle()) {
			Broodwar->sendText("%s", "WANTS TO BUILD!");

			//tilf�j dannys kode

			TilePosition targetBuildLocation = Broodwar->getBuildLocation(orderedBuilding, (*constructionsWorker)->getTilePosition());
			(*constructionsWorker)->build(orderedBuilding, targetBuildLocation);				
				
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

	BWAPI::UnitType building = Broodwar->self()->getRace().getRefinery();

	TilePosition targetBuildLocation = Broodwar->getBuildLocation(building, (*worker)->getTilePosition());
	(*worker)->build(building, targetBuildLocation);

}

ConstructionManager::ConstructionManager()
{
	constructionsWorker = NULL;
}

ConstructionManager::~ConstructionManager()
{
}