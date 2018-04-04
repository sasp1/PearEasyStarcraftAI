#include "CombatManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;

CombatManager::CombatManager() {
	bool wantToAttackEnemyBase = false;
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
	if (wantToAttackEnemyBase) {
		for (auto &u : combatUnits) {
			(*u)->move(pos);
			attackNearestEnemy(u);
		}
	}
}

void CombatManager::defendBase(){
	//find min distance to defend base (commandcenter to closest enemy)
	/*if (BWAPI::Broodwar->self()->getStartLocation().getDistance() {
		for (auto &u : combatUnits) {
			attackNearestEnemy(u);
		}
	}*/
}


void CombatManager::executeOrders() {

}


