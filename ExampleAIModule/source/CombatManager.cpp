#include "CombatManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;


bool attack = false;
BWAPI::Position attackLoc;


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
	/*(*unit)->attack((*unit)->getClosestUnit((IsEnemy && IsAttacking)));
	(*unit)->attack((*unit)->getClosestUnit(IsEnemy));*/
}

void CombatManager::attackEnemy(const BWAPI::Unit* unit, const BWAPI::Unit target) {
	(*unit)->attack(target);
}

bool CombatManager::attackEnemyIfInRange(const BWAPI::Unit* unit, BWAPI::UnitType target, int range) {
	for (auto &e : (*unit)->getUnitsInRadius(range, IsEnemy)) {
		if (e->getType() == UnitTypes::Terran_Marine) {
			Broodwar->sendText("Is now attacking Marine"); 
			e->attack(*unit); 
			return true; 
		}
	}
	//for (auto &eu : (Broodwar->enemy()->getUnits())) {
	//	if (eu->getType() == target && (*unit)->getDistance(eu) < range) {
	//		(*unit)->attack(eu);
	//		Broodwar->sendText("Attacking marine"); 
	//		return true;
	//	}
	//}
	return false;
}

void CombatManager::attackEnemyBaseWithAllCombatUnits(BWAPI::Position pos) {
	//const BWAPI::Unit* combatLeader = combatUnits.back();
	//const BWAPI::Unit nearestEnemy = (*combatLeader)->getClosestUnit(IsEnemy);
	attackLoc = pos;
	attack = true;
	for (auto &u : combatUnits) {
		(*u)->move(pos, true);
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
	if (attack) {
		for (auto &u : combatUnits) {
			
			if (!attackEnemyIfInRange(u, UnitTypes::Terran_Marine, 100) ) { // && !attackEnemyIfInRange(u,UnitTypes::Terran_SCV, 50)
				attackNearestEnemy(u);
			}
		}
	}
}


