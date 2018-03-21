#include "ScoutingManager.h"
#include <BWAPI.h>
#include <math.h>
using namespace BWAPI;
using namespace Filter;

std::list<const BWAPI::Unit*> scoutingUnits;
//The map is 4096x4096 pixels (64^2)
int corner = 0;

ScoutingManager::ScoutingManager()
{
	
}


ScoutingManager::~ScoutingManager()
{
}

void ScoutingManager::addScout(const BWAPI::Unit* scout) {
	//Receive control of a new scoutUnit
	scoutingUnits.push_back(scout);
}

void ScoutingManager::scoutCornersClockwise(const BWAPI::Unit* scout) {
	//Scout clockwise each corner of the map
	int x;
	int y;
	BWAPI::Position targetLocation = ((*scout)->getPosition());
	if (corner == 0) {
		x = abs(targetLocation.getX()-4000);
		y = targetLocation.getY();
	}
	else {
		x = targetLocation.getX();
		y = abs(targetLocation.getY()-4000);
	}
	(*scout)->move(Position(x, y));
	corner = (corner + 1) % 2;	
	Broodwar->sendText("%i: (%i,%i)", corner, x, y);
}

void ScoutingManager::executeOrders() {

		for (auto &u : scoutingUnits)
		{
			if ((*u)->isIdle()) {
				scoutCornersClockwise(u);
		}
	}
}
