#include "CombatManager.h"
#include <BWAPI.h>
/**
* @file CombatManager.cpp
* @brief Controls the army, how it initiate combat and how units attack in combat.
* @author  Thomas Dahl Heshe <s164399@student.dtu.dk>
*/
using namespace BWAPI;
using namespace Filter;


bool shouldAttack = false;
BWAPI::Position attackLocation;
BWAPI::Position enemyPos;



CombatManager::CombatManager() {
	std::list<const BWAPI::Unit*> combatUnits;
}

CombatManager::~CombatManager() {
}

void CombatManager::addCombatUnit(const BWAPI::Unit* unit) {
	//Receive control of a new combatUnit
	if ((*unit)->getType() == BWAPI::UnitTypes::Terran_Vulture) {
		BWAPI::Position pos = (*buildingManager->commandCenter)->getPosition();
		Vulture* vulture = new Vulture(unit, pos); 
		vultures.push_back(vulture);
	}
	else {
		combatUnits.push_back(unit);
	}
	
	
}

/**
* A method for selecting a prioritized enemy to attack. Uses attackEnemyIfInRange()
* @author Asger Græsholt <s154099@dstudent.dtu.dk>
* @param unit a BWAPI unit who is to attack a nearby enemy, if any
* @see attackEnemyIfInRange()
*/
void CombatManager::attackNearestEnemy(const BWAPI::Unit* unit) {

	if (!(stayOutOfRange(unit, 80))) {

		BWAPI::Unit desiredUnitToAttack = NULL;

		//TERRAN V PROTOSS________________________________________________
		desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Protoss_Zealot, 300);

		if (desiredUnitToAttack == NULL) {
			desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Protoss_Dragoon, 300);
		}

		if (desiredUnitToAttack == NULL) {
			desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Protoss_Photon_Cannon, 1000);
		}

		if (desiredUnitToAttack == NULL) {
			desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Protoss_Probe, 300);
		}




		//TERRAN V TERRAN________________________________________________

		if (desiredUnitToAttack == NULL) {
			desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Terran_Siege_Tank_Siege_Mode, 300);
		}

		if (desiredUnitToAttack == NULL) {
			desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Terran_Vulture, 300);
		}

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

		if (desiredUnitToAttack != NULL && desiredUnitToAttack->getType() != UnitTypes::Protoss_Dark_Templar) {
			Broodwar->sendText("%s", desiredUnitToAttack->getType().c_str());
			(*unit)->attack(desiredUnitToAttack);
		}
	}
	
}

/**
* Attack with a unit at a given enemy type (target) if in range. Method returns an enemy of the specified type within range if found. NULL otherwise
* @author Asger Græsholt <s154099@dstudent.dtu.dk>
* @param unit
* @param target the target desired to attack if within a specified range
* @param range describes the maximum range we wish to attack an enemy within
* @see attackNearestEnemy()
*/


BWAPI::Unit CombatManager::attackEnemyIfInRange(const BWAPI::Unit* unit, BWAPI::UnitType target, int range) {
	BWAPI::Unit desiredUnitToAttack = NULL;


	for (auto &eu : (*unit)->getUnitsInRadius(range)) {
		if ((eu)->getType() == target && (eu)->getPlayer()->isEnemy(Broodwar->self())) {
			if ((*unit)->getDistance(desiredUnitToAttack) > (*unit)->getDistance(eu) ) {
				desiredUnitToAttack = eu;

			}
		}
	}
	return desiredUnitToAttack;

}

bool CombatManager::isInEnemyCriticalRange(const BWAPI::Unit* unit, const BWAPI::Unit* enemyUnit) {
	int enemyWeaponRange = (*unit)->getType().groundWeapon().maxRange(); 
	int distanceToEnemy= (*unit)->getPosition().getDistance((*enemyUnit)->getPosition()); 
	
	return distanceToEnemy < enemyWeaponRange + 100; 

}

bool CombatManager::stayOutOfRange(const BWAPI::Unit * unit, int range){
	bool enemiesInRange = false;

	BWAPI::Position centerOfMass = Position(0, 0); 
	for (auto &eu : (*unit)->getUnitsInRadius(range)) {

		centerOfMass = centerOfMass + ((*eu).getPosition() - (*unit)->getPosition()); 

		//bool enemyIsRanged = (eu->isInWeaponRange(*unit)) && (eu->getDistance(*unit) > 20); !enemyIsRanged && !(eu->getType().isBuilding()) &&
		if ((eu)->getPlayer()->isEnemy(Broodwar->self()) && isInEnemyCriticalRange(&eu, unit)) {
			enemiesInRange = true; 
			// enemyPos = (*eu).getPosition();
			//Broodwar->sendText("enemy was in range critical range");
			centerOfMass = centerOfMass + ((*eu).getPosition() - (*unit)->getPosition()); // Lægges til igen grundet dobbelt vægt

			/*BWAPI::Position movePosition = BWAPI::Unit(*buildingManager->commandCenter)->getPosition();
			(*unit)->move(movePosition);
			}*/
		}
	}

	if (enemiesInRange) {
		//Broodwar->sendText("Center of mass was: %d, %d", centerOfMass.x, centerOfMass.y);
		BWAPI::Position movePosition = (*unit)->getPosition() - centerOfMass; 
		(*unit)->move(movePosition); 
	}

	return enemiesInRange;

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
* @author Asger Græsholt <s154099@dstudent.dtu.dk>
* @param range integer specifing a range from the base
*/

void CombatManager::defendBase(int range){
	//find min distance to defend base (commandcenter to closest enemy)
	if (BWAPI::Unit(*buildingManager->commandCenter)->getDistance(BWAPI::Unit(*buildingManager->commandCenter)->getClosestUnit(IsEnemy))<range) {
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
* @author Asger Græsholt <s154099@dstudent.dtu.dk>
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

	
	for (auto &u : vultures) {
		if (shouldAttack) {
			attackNearestEnemy(u->unit); 
			
			//u->putDownMineIfOutsideOfBase(); 

			if ((*u->unit)->isIdle()) {
				(*u->unit)->move(attackLocation); 
			}
		}
	}
	
}


