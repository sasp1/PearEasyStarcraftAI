#include "CombatManager.h"
#include <BWAPI.h>
#include "Worker.h"
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
Unit* nearestHydra = NULL;
int distanceToHydra = -1;
bool outNumbered = false;

CombatManager::CombatManager() {

}

CombatManager::~CombatManager() {
}

void CombatManager::addCombatUnit(const BWAPI::Unit* unit) {
	//Receive control of a new combatUnit
	if ((*unit)->getType() == BWAPI::UnitTypes::Terran_Vulture) {
		Building* b = buildingManager->commandCenters.front();
		BWAPI::Position pos = (*b->unit)->getPosition();
		CustomUnit* vulture = new Vulture(unit, pos);
		vultures.push_back(vulture);

	}
	else if ((*unit)->getType() == BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode) {
		CustomUnit* st = new SiegeTank(unit);
		tanks.push_back(st);

	}
	else if ((*unit)->getType() == BWAPI::UnitTypes::Terran_Marine) {
		CustomUnit* marine = new Marine(unit);
		marines.push_back(marine);
	}
	else if ((*unit)->getType() == BWAPI::UnitTypes::Terran_Vulture_Spider_Mine) {
		CustomUnit* mine = new Mine(unit);
		mines.push_back(mine);

	}
	else if ((*unit)->getType() == BWAPI::UnitTypes::Terran_SCV) {
		CustomUnit* worker = new Worker(unit);
		workers.push_back(worker);
		Broodwar->sendText("Worker added");

	}

	//combatUnits.push_back(unit);
}

std::list<CustomUnit*> CombatManager::getAllCombatUnits() {

	std::list<CustomUnit*> combatunits;

	for (auto &u : vultures) {
		combatunits.push_back(u);
	}

	for (auto &u : marines) {
		combatunits.push_back(u);
	}

	for (auto &u : tanks) {
		combatunits.push_back(u);
	}

	for (auto &u : workers) {
		combatunits.push_back(u);
	}

	return combatunits;
}

/**
* A method for selecting a prioritized enemy to attack. Uses attackEnemyIfInRange()
* @author Asger Græsholt <s154099@dstudent.dtu.dk>
* @param unit a BWAPI unit who is to attack a nearby enemy, if any
* @see attackEnemyIfInRange()
*/
void CombatManager::attackNearestEnemy(const BWAPI::Unit* unit) {

	BWAPI::Unit desiredUnitToAttack = NULL;

	//TERRAN V PROTOSS________________________________________________
	desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Protoss_Dragoon, 300);

	if (desiredUnitToAttack == NULL) {
		desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Protoss_Zealot, 300);
	}


	if (desiredUnitToAttack == NULL && ((*unit)->getType() == UnitTypes::Terran_Siege_Tank_Tank_Mode || (*unit)->getType() == UnitTypes::Terran_Siege_Tank_Siege_Mode)) {

		desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Protoss_Photon_Cannon, UnitTypes::Terran_Siege_Tank_Siege_Mode.groundWeapon().maxRange());
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


	//TERRAN V ZERG _________________________________________
	if (desiredUnitToAttack == NULL) {
		desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Zerg_Hydralisk, 300);
	}

	if (desiredUnitToAttack == NULL) {
		desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Zerg_Zergling, 300);
	}

	if (desiredUnitToAttack == NULL) {
		desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Zerg_Hydralisk_Den, 300);
	}
	//If all fails: get nearest enemy ... and attack!

	if (desiredUnitToAttack == NULL) {
		desiredUnitToAttack = (*unit)->getClosestUnit(IsEnemy);
	}

	if (desiredUnitToAttack != NULL && desiredUnitToAttack->getType() != UnitTypes::Protoss_Dark_Templar) {
		(*unit)->attack(desiredUnitToAttack);
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
			

			if ((*unit)->getDistance(desiredUnitToAttack) > (*unit)->getDistance(eu)) {
				desiredUnitToAttack = eu;

				


			}
		}
	}
	return desiredUnitToAttack;

}

bool CombatManager::isInEnemyCriticalRange(const BWAPI::Unit* unit, const BWAPI::Unit* enemyUnit) {
	int enemyWeaponRange = (*enemyUnit)->getType().groundWeapon().maxRange();
	int unitWeaponRangeMinus5Pct = (*unit)->getType().groundWeapon().maxRange() - ((*unit)->getType().groundWeapon().maxRange() / 20);
	int distanceToEnemy = (*unit)->getPosition().getDistance((*enemyUnit)->getPosition());

	return (distanceToEnemy < unitWeaponRangeMinus5Pct);

}

bool CombatManager::isMelee(const BWAPI::Unit* unit) {
	return (*unit)->getType().groundWeapon().damageAmount() > 2 && (*unit)->getType().groundWeapon().maxRange() <= UnitTypes::Protoss_Zealot.groundWeapon().maxRange() && (*unit)->getType() != UnitTypes::Terran_SCV;


}


bool CombatManager::shallMoveAwayFromEnemyInCriticalRange(const BWAPI::Unit * unit, int range) {
	bool enemiesInCriticalRange = false;

	//First check if unit are within critical range of a cannonn
	for (auto &eu : (*unit)->getUnitsInRadius(UnitTypes::Protoss_Photon_Cannon.groundWeapon().maxRange() + UnitTypes::Protoss_Photon_Cannon.groundWeapon().maxRange() / 5)) {


		if ((*eu).getPlayer()->isEnemy((*unit)->getPlayer()) && ((*eu).getType() == UnitTypes::Protoss_Photon_Cannon)) {

			BWAPI::Position movePosition = (*unit)->getPosition() - (((*eu).getPosition() - (*unit)->getPosition()));
			(*unit)->move(movePosition);
			

			return true;
		}
	}


	//otherwise juke as normal
	BWAPI::Position centerOfMass = Position(0, 0);
	for (auto &eu : (*unit)->getUnitsInRadius(range)) {

		centerOfMass = centerOfMass + ((*eu).getPosition() - (*unit)->getPosition());

		if ((eu)->getPlayer()->isEnemy(Broodwar->self()) && isInEnemyCriticalRange(unit, &eu) && isMelee(&eu) && !(*eu).getType().isBuilding()) {
			enemiesInCriticalRange = true;
			centerOfMass = centerOfMass + ((*eu).getPosition() - (*unit)->getPosition()); // Lægges til igen grundet dobbelt vægt

		}
	}

	if (enemiesInCriticalRange) {
		//Broodwar->sendText("Center of mass was: %d, %d", centerOfMass.x, centerOfMass.y);
		BWAPI::Position movePosition = (*unit)->getPosition() - centerOfMass;
		(*unit)->move(movePosition);
	}


	return enemiesInCriticalRange;

}


void CombatManager::attackEnemyBaseWithAllCombatUnits(BWAPI::Position enemyBasePosition) {
	attackLocation = enemyBasePosition;
	shouldAttack = true;
	//for (auto &u : getAllCombatUnits()) {

		//(*u->unit)->move(enemyBasePosition);

	//}
}


/**
* method makes all units deffend the base if they are within "range" from the commandCenter
* @author Asger Græsholt <s154099@dstudent.dtu.dk>
* @param range integer specifing a range from the base
*/

bool CombatManager::shouldDefendBase(int range, const BWAPI::Unit * unit) {
	//find min distance to defend base (commandcenter to closest enemy)

	bool defendingBase = false;

	if (BWAPI::Unit(*buildingManager->commandCenter)->getDistance(BWAPI::Unit(*buildingManager->commandCenter)->getClosestUnit(IsEnemy)) < range) {
		//Only units near base protects base
		if (BWAPI::Unit(*buildingManager->commandCenter)->getDistance(*unit) < range) {
			attackNearestEnemy(unit);
			defendingBase = true;
		}

	}
	
	return defendingBase;
}

void CombatManager::returnAllUnitsToBase() {
	for (auto &u : getAllCombatUnits()) {
		(*u->unit)->move((*buildingManager->commandCenter)->getPosition());
		
	}
}


bool tankCanMakeSiegeModeAttackOnStructure(const BWAPI::Unit * unit) {
	for (auto &eu : (*unit)->getUnitsInRadius(UnitTypes::Terran_Siege_Tank_Siege_Mode.groundWeapon().maxRange(), IsEnemy)) {
		if (eu->getType().isBuilding() && (*unit)->getDistance(eu) > (UnitTypes::Terran_Siege_Tank_Siege_Mode.groundWeapon().maxRange()) / 2) {
			if (!(*unit)->isSieged()) {
				(*unit)->siege();

			}
			return true;
		}
	}
	return false;
}

bool CombatManager::fleeIfOutNumbered(Vulture* vulture) {
	if (nearestHydra == NULL || outNumbered == false) {
		return false;
	}
	if ((*vulture->unit)->getDistance((*nearestHydra)->getPosition()) < UnitTypes::Zerg_Hydralisk.groundWeapon().maxRange() * 2) {
		(*vulture->unit)->move(scoutingManager->defendInBasePosition);
		
		return true;
	}
	return false;
}


bool CombatManager::repairNearbyInjuredVehicles(const BWAPI::Unit * worker) {
	for (auto &umech : (*worker)->getUnitsInRadius(1000, IsAlly)) {
		//Broodwar->sendText("unit in radius: %s", umech->getType().c_str());

		if ((umech)->getType().isMechanical() && !(umech)->getType().isBuilding() && (umech)->getHitPoints() < (umech)->getType().maxHitPoints()) {
			Broodwar->sendText("REPAIRING %i", (umech)->getHitPoints());

			(*worker)->repair(umech);
			return true;
		}
	}
	return false;

}

bool fleeFromLurker(const Unit* unit) {
	return false; 
}

bool attackingLurker(const Unit* unit) {
	//Unit* lurker = (*unit)->getUnitsInRadius()
	return false; 
}
/**
* main method of every class. Makes the combatmanager execute orders/relevant computations in every frame.
* @see attackNearestEnemy()
* @see Defendbase()
* @author Asger Græsholt <s154099@dstudent.dtu.dk>
*/
void CombatManager::executeOrders() {

	//Broodwar->sendText("%i", tanks._Mysize());

	//defendingBase(1000);


	if (nearestHydra != NULL && (*nearestHydra)->isVisible()) {

		int numberOfEnemies = 1;
		int numberOfFriendlyUnits = 0;

		for (auto &u : (*nearestHydra)->getUnitsInRadius(UnitTypes::Zerg_Hydralisk.groundWeapon().maxRange() * 2)) {
			if (u->getType() == UnitTypes::Terran_Vulture) {
				numberOfFriendlyUnits++;
			}
			else if (u->getType() == UnitTypes::Zerg_Hydralisk) {
				numberOfEnemies++;
			}
		}
		outNumbered = numberOfEnemies + 3 > numberOfFriendlyUnits;
		
	}
	else {
		distanceToHydra = -1;
	}

	for (auto &u : vultures) {


		Vulture* vulture = dynamic_cast<Vulture*>(u);
		Unit* unit = (*vulture).nearestHydra(UnitTypes::Zerg_Hydralisk.groundWeapon().maxRange() * 2);

		if (unit != NULL) {

			int vultureHydraDistance = (*unit)->getDistance((*vulture->unit)->getPosition());
			if (vultureHydraDistance < distanceToHydra || distanceToHydra == -1) {
				nearestHydra = unit;
				distanceToHydra = vultureHydraDistance;
				
			}
		}

		if (!(Broodwar->enemy()->getRace() == Races::Terran) &&
			vulture->canUseMine() && vulture->hasBeenOcupied == 0 && mines.size() < 10 && (*vulture->unit)->getDistance(scoutingManager->startingChokePosition) < 50) {

			vulture->layDownDefensiveMine(scoutingManager->startingChokePosition + Position(mines.size() * 5, mines.size() * 5));
		}
		else if (!vulture->isOcupied()) {	
			if (!shallMoveAwayFromEnemyInCriticalRange(u->unit, 120)) {
				if (!fleeIfOutNumbered(vulture)) {
					if (!attackingLurker(vulture->unit)) {
						if (!shouldDefendBase(1000, u->unit) && shouldAttack) {
							attackNearestEnemy(u->unit);
						}
					}
				}


			}
		}
	}

	for (auto &u : tanks) {
		//Siege mode attack 1. prio
		if (!tankCanMakeSiegeModeAttackOnStructure(u->unit)) {

			//If siege attack not possible => unsiege!
			if ((*u->unit)->isSieged()) { (*u->unit)->unsiege(); }

			//If the tank is not moving away from an enemy in critical range
			if (!shallMoveAwayFromEnemyInCriticalRange(u->unit, 120)) {

				//If the tank should not defend and we are attacking
				if (!shouldDefendBase(1000, u->unit) && shouldAttack) {
					attackNearestEnemy(u->unit);
				}
			}
		}
	}

	for (auto &u : marines) {
		if (!shouldDefendBase(1000, u->unit) && shouldAttack) {

			attackNearestEnemy(u->unit);

		}

	}
	for (auto &u : workers) {

		if (!repairNearbyInjuredVehicles(u->unit) && vultures.size() > 0) {
			(*u->unit)->move((*vultures.front()->unit)->getPosition());
			
			
		}
	}


	for (auto &u : getAllCombatUnits()) {
		if ((*u->unit)->isIdle() && shouldAttack && !u->isOcupied()) {
			/*if (!fleeFromLurker(u->unit)) {
				if (!attackingLurker(u->unit)) {*/
					(*u->unit)->move(attackLocation);
					
				//}
				
			//}
			
		} 

	}
}


