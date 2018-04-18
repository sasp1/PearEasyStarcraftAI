#include "CombatManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;


bool shouldAttack = false;
BWAPI::Position attackLocation;


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
	//focus attacking units
	(*unit)->attack((*unit)->getClosestUnit((IsEnemy && IsAttacking)));
	(*unit)->attack((*unit)->getClosestUnit(IsEnemy));
}


bool CombatManager::attackEnemyIfInRange(const BWAPI::Unit* unit, BWAPI::UnitType target, int range) {
	//Attack a given unit if in range and return whether or not this was possible
	for (auto &eu : (Broodwar->enemy()->getUnits())) {
		if (eu->getType() == target && (*unit)->getDistance(eu) < range) {
			(*unit)->attack(eu,true);
			return true;
		}
	}
	return false;
}

void CombatManager::attackEnemyBaseWithAllCombatUnits(BWAPI::Position pos) {
	attackLocation = pos;
	shouldAttack = true;
	for (auto &u : combatUnits) {
		attackEnemyIfInRange(u, UnitTypes::Terran_Marine, 10);
		attackNearestEnemy(u);
		(*u)->move(pos);
	}
}

/**
* @author Asger Græsholt <s154099@dstudent.dtu.dk>
*
* Defend with all units (in range) if an enemy unit gets in a given range of the base  
*/
void CombatManager::defendBase(int range){
	//find min distance to defend base (commandcenter to closest enemy)
	if (BWAPI::Unit(*buildingManager->commandCenter)->getDistance(BWAPI::Unit(*buildingManager->commandCenter)->getClosestUnit(IsEnemy))<range) {
		Broodwar->sendText("DEFEND");
		for (auto &u : combatUnits) {
			if (BWAPI::Unit(*buildingManager->commandCenter)->getDistance(*u)<range) {
			attackNearestEnemy(u);
			}
		}
	}
}




void CombatManager::executeOrders() {

	defendBase(1000);

	for (auto &u : combatUnits) {
		if (shouldAttack) {
			if (!attackEnemyIfInRange(u, UnitTypes::Terran_Marine, 10)) {

				attackNearestEnemy(u);

			}
		}
	}
}


