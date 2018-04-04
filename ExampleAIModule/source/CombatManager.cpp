#include "CombatManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;

std::list<const BWAPI::Unit*> combatUnits;

void CombatManager::addCombatUnit(const BWAPI::Unit* unit) {
	//Receive control of a new combatUnit
	combatUnits.push_back(unit);
}

void CombatManager::attackNearestEnemy(const BWAPI::Unit* unit) {
	(*unit)->attack((*unit)->getClosestUnit(IsEnemy), false);
}

void CombatManager::attackWithAllCombatUnits() {
	for (auto &u : combatUnits){
			attackNearestEnemy(u);
	}
}

void CombatManager::executeOrders() {
		attackWithAllCombatUnits();
}


CombatManager::CombatManager()
{
}

CombatManager::~CombatManager()
{
}
