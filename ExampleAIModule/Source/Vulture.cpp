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
