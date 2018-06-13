#include "Vulture.h"
using namespace BWAPI;
using namespace Filter;

int counter = 0; 

/**
* @file Vulture.cpp
* @brief Class representing a vulture unit.
* @author Daniel Fjordhøj <s133198@student.dtu.dk>
*/

Vulture::Vulture(BWAPI::UnitInterface* u,  BWAPI::Position basePosition) : CustomUnit::CustomUnit(u){
	if (u->getType() == UnitTypes::Terran_Vulture) {
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

	//Attempt placement of mine, if time has passed since last placement
	if (time + 20 < Broodwar->getFrameCount()) {
		time = Broodwar->getFrameCount();

		BWAPI::Position position = unit->getPosition() + Position(1, 1);

		if (basePos.getDistance(unit->getPosition()) > 700.0 + counter) {
			unit->useTech(BWAPI::TechTypes::Spider_Mines, position); 
			counter = counter + 30.0;
			if (counter > 4000.0)
				counter = 0;
		}
	}
}


bool Vulture::isUnitIdle() {
	return unit->isIdle();
}

bool Vulture::canUseMine() {
	return unit->canUseTechWithOrWithoutTarget(TechTypes::Spider_Mines); 
}

UnitInterface*  Vulture::nearestHydra(int radius)
{
	//Return nearest hydralisk if any exist
	if (unit->getClosestUnit(Filter::GetType == UnitTypes::Zerg_Hydralisk) == NULL)
		return NULL; 
	return unit->getClosestUnit(Filter::GetType == UnitTypes::Zerg_Hydralisk);
}

bool Vulture::isOcupied() {
	return  !(startTime + 10 < Broodwar->getFrameCount()); 
}

void Vulture::layDownMine(BWAPI::Position targetPosition, int frameCount)
{	
	//Place mine at location, and update placement timer
	hasBeenOcupied++; 
	startTime = frameCount;
	unit->useTech(BWAPI::TechTypes::Spider_Mines, targetPosition);	
}
