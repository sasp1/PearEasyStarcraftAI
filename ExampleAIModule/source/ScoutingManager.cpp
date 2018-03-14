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
	//Receive control of a new worker
	scoutingUnits.push_back(scout);
}