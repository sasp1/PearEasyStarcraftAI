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
	//(*unit)->attack((*unit)->getClosestUnit((IsEnemy && IsAttacking)));
	//(*unit)->attack((*unit)->getClosestUnit(IsEnemy));

	BWAPI::Unit desiredUnitToAttack = NULL;

	desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Terran_Siege_Tank_Siege_Mode, 300);

	if (desiredUnitToAttack == NULL) {
		desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Terran_Siege_Tank_Tank_Mode, 300);
	}
	
	if (desiredUnitToAttack == NULL) {
		desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Terran_Marine, 300);
	}

	if (desiredUnitToAttack == NULL) {
		desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Terran_Medic, 300);
	}

	if (desiredUnitToAttack == NULL) {
		desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Terran_SCV, 300);
	}

	if (desiredUnitToAttack == NULL) {
		desiredUnitToAttack = (*unit)->getClosestUnit(IsEnemy);
	}

	if (desiredUnitToAttack != NULL) {
		Broodwar->sendText("%s", desiredUnitToAttack->getType().c_str());
		(*unit)->attack(desiredUnitToAttack);
	}
	
}

//
BWAPI::Unit CombatManager::attackEnemyIfInRange(const BWAPI::Unit* unit, BWAPI::UnitType target, int range) {
	//Attack a given unit if in range and return whether or not this was possible
	BWAPI::Unit desiredUnitToAttack = NULL;

	//NEDENST�ENDE ER UNDERLIGT. B�r det ikke v�re alle enemies i units range?
	//Units.getunitsinradius(range, isenemy);
	for (auto &eu : (Broodwar->enemy()->getUnits().getUnitsInRadius(range))) {
		if ((eu)->getType() == target) {
			if ((*unit)->getDistance(desiredUnitToAttack) > (*unit)->getDistance(eu)) {
				desiredUnitToAttack = eu;
			}
		}
	}
	return desiredUnitToAttack;

}

void CombatManager::attackEnemyBaseWithAllCombatUnits(BWAPI::Position enemyBasePosition) {
	attackLocation = enemyBasePosition;
	shouldAttack = true;
	for (auto &u : combatUnits) {

		(*u)->move(enemyBasePosition);

	}
}

/**
* @author Asger Gr�sholt <s154099@dstudent.dtu.dk>
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

void CombatManager::returnAllUnitsToBase() {
	for (auto &u : combatUnits) {
		(*u)->move((*buildingManager->commandCenter)->getPosition());
	}
}




void CombatManager::executeOrders() {


	defendBase(1000);

	for (auto &u : combatUnits) {
		if (shouldAttack) {
			//if (!attackEnemyIfInRange(u, UnitTypes::Terran_Marine, 10)) {

				attackNearestEnemy(u);
			// }

			if ((*u)->isIdle()) {
				(*u)->move(attackLocation);
			}
		}
	}
}


