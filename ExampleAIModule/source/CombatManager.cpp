#include "CombatManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;

CombatManager::CombatManager() {
	std::list<const BWAPI::Unit*> combatUnits;
}

CombatManager::~CombatManager() {
}

void CombatManager::addCombatUnit(const BWAPI::Unit* unit) {
	//Receive control of a new combatUnit
	combatUnits.push_back(unit);
}

void CombatManager::attackNearestEnemy(const BWAPI::Unit* unit) {
		(*unit)->attack((*unit)->getClosestUnit(IsEnemy), false);
}

void CombatManager::attackEnemyBaseWithAllCombatUnits(BWAPI::Position pos) {
	for (auto &u : combatUnits) {
			attackNearestEnemy(u);
			(*u)->move(pos);
	}
}


void CombatManager::defendBase(){
	//find min distance to defend base (commandcenter to closest enemy)
	if (BWAPI::Unit(*buildingManager->commandCenter)->getDistance(BWAPI::Unit(*buildingManager->commandCenter)->getClosestUnit(IsEnemy))<1000) {
		Broodwar->sendText("DEFEND");
		for (auto &u : combatUnits) {
			attackNearestEnemy(u);
		}
	}
}

void CombatManager::executeOrders() {

	defendBase();

}


