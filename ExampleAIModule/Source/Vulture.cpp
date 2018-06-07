#include "Vulture.h"
using namespace BWAPI;
using namespace Filter;

int counter = 0; 
Vulture::Vulture(const BWAPI::Unit* u,  BWAPI::Position basePosition) : CustomUnit::CustomUnit(u){
	if ((*u)->getType() == UnitTypes::Terran_Vulture) {
		time = Broodwar->getFrameCount();
		basePos = basePosition;
	}
	else {
		Broodwar->sendText("ERROR! TRIED TO ADD NON-VULTURE UNIT TO VULTURE OBJECT!");
	}
}

Vulture::~Vulture()
{
}

void Vulture::putDownMineIfOutsideOfBase() {

	// return (time + t) < Broodwar->getFrameCount();
	if (time + 20 < Broodwar->getFrameCount()) {
		time = Broodwar->getFrameCount();

		BWAPI::Position position = (*unit)->getPosition() + Position(1, 1);

		if (basePos.getDistance((*unit)->getPosition()) > 700.0 + counter) {
			(*unit)->useTech(BWAPI::TechTypes::Spider_Mines, position); 
			counter = counter + 30.0;
			if (counter > 4000.0)
				counter = 0;
			
		}
	}
}


bool Vulture::isUnitIdle() {
	return (*unit)->isIdle();
}

bool Vulture::canUseMine() {
	return (*unit)->canUseTechWithOrWithoutTarget(TechTypes::Spider_Mines); 
}

	



Unit*  Vulture::nearestHydra(int radius)
{
	if ((*unit)->getClosestUnit(Filter::GetType == UnitTypes::Zerg_Hydralisk) == NULL)
		return NULL; 
	return new Unit((*unit)->getClosestUnit(Filter::GetType == UnitTypes::Zerg_Hydralisk));
}

bool Vulture::isOcupied() {
	return  !(startTime + 50 < Broodwar->getFrameCount()); 
}

void Vulture::layDownMine(BWAPI::Position targetPosition)
{
	hasBeenOcupied++; 
	startTime = Broodwar->getFrameCount();
	(*unit)->useTech(BWAPI::TechTypes::Spider_Mines, targetPosition);	
}
