#include "CombatManager.h"
#include <BWAPI.h>
/**
* @author Asger Gr�sholt <s154099@dstudent.dtu.dk>
*
* The combat manager controls units in war - how they fight, who they
* prioritize to kill and how they do it. Furthermore it controls how
* a battle is initiated
*/
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

/**
* A method for selecting a prioritized enemy to attack. Uses attackEnemyIfInRange()
* @author Asger Gr�sholt <s154099@dstudent.dtu.dk>
* @param unit a BWAPI unit who is to attack a nearby enemy, if any
* @see attackEnemyIfInRange()
*/
void CombatManager::attackNearestEnemy(const BWAPI::Unit* unit) {

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

/**
* Attack with a unit at a given enemy type (target) if in range. Method returns an enemy of the specified type within range if found. NULL otherwise
* @author Asger Gr�sholt <s154099@dstudent.dtu.dk>
* @param unit
* @param target the target desired to attack if within a specified range
* @param range describes the maximum range we wish to attack an enemy within
* @see attackNearestEnemy()
*/
BWAPI::Unit CombatManager::attackEnemyIfInRange(const BWAPI::Unit* unit, BWAPI::UnitType target, int range) {
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
* method makes all units deffend the base if they are within "range" from the commandCenter
* @author Asger Gr�sholt <s154099@dstudent.dtu.dk>
* @param range integer specifing a range from the base
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



/**
* main method of every class. Makes the combatmanager execute orders/relevant computations in every frame. 
* @see attackNearestEnemy()
* @see Defendbase()
* @author Asger Gr�sholt <s154099@dstudent.dtu.dk>
*/
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


