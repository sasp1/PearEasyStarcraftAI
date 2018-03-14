#include "ScoutingManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;

std::list<const BWAPI::Unit*> scoutingUnits;

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

void ScoutingManager::moveScoutToTile(const BWAPI::Unit* scout, int x, int y) {
	//Moves unit to given tile in given tilescale
	(*scout)->move(Position(x, y));
}

void ScoutingManager::executeOrders() {
	int size = scoutingUnits.size(); 
	if (size==1) {
		moveScoutToTile(scoutingUnits.back(), 4000, 0);
	}
}
