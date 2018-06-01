#include "Vulture.h"
using namespace BWAPI;
using namespace Filter;

Vulture::Vulture(const BWAPI::Unit* u,  BWAPI::Position basePosition) {
	unit = u;
	time = Broodwar->getFrameCount(); 
	basePos = basePosition; 
}

Vulture::~Vulture()
{
}

void Vulture::putDownMineIfOutsideOfBase() {

	// return (time + t) < Broodwar->getFrameCount();
	if (time + 20 < Broodwar->getFrameCount()) {
		time = Broodwar->getFrameCount();

		BWAPI::Position position = (*unit)->getPosition() + Position(1, 1);
		Broodwar->sendText("%d", (int)basePos.getDistance((*unit)->getPosition()));
		if (basePos.getDistance((*unit)->getPosition()) > 800.0) {
			(*unit)->useTech(BWAPI::TechTypes::Spider_Mines, position);
			Broodwar->sendText("Tried to put down spider mine");
		}
	}
}

bool Vulture::isUnitIdle() {
	return (*unit)->isIdle();

}