#include "CombatManager.h"
#include <BWAPI.h>
#include "Worker.h"
#include "Wraith.h"

/**
* @file CombatManager.cpp
* @brief Handles units assigned to combat along with battle management.
* Assigns prioritized enemy targets, and unit specific actions, both individually and as a group
* @author Daniel Fjordhøj <s133198@student.dtu.dk>
*/
using namespace BWAPI;
using namespace Filter;


BWAPI::Position attackLocation;
BWAPI::Position enemyPos;
UnitInterface* nearestHydra = NULL;
int distanceToHydra = -1;
int startTime = 0;

CombatManager::CombatManager() {
}

CombatManager::~CombatManager() {
}

void CombatManager::addCombatUnit(BWAPI::UnitInterface* unit) {

	//Create class based on unittype
	if (unit->getType() == BWAPI::UnitTypes::Terran_Vulture) {
		Building* b = buildingManager->commandCenters.front();
		BWAPI::Position pos = b->unit->getPosition();
		vultures.push_back(new Vulture(unit, pos, Broodwar->getFrameCount()));
	}
	else if (unit->getType() == BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode)
		tanks.push_back(new SiegeTank(unit));

	else if (unit->getType() == BWAPI::UnitTypes::Terran_Marine)
		marines.push_back(new Marine(unit));

	else if (unit->getType() == BWAPI::UnitTypes::Terran_Vulture_Spider_Mine) {
		CustomUnit* mine = new Mine(unit);
		if (unit->getDistance(scoutingManager->startingChokePosition) < 300)
			minesInDefensiveChokePosition.push_back(mine);
		else minesAtEnemeyBase.push_back(mine);
	}
	else if (unit->getType() == BWAPI::UnitTypes::Terran_SCV)
		workers.push_back(new Worker(unit));

	else if (unit->getType() == BWAPI::UnitTypes::Terran_Wraith)
		wraiths.push_back(new Wraith(unit));
}

std::list<CustomUnit*> CombatManager::getAllCombatUnits() {

	//Compile lists of individual unittypes
	std::list<CustomUnit*> combatunits;

	for (auto &u : vultures) combatunits.push_back(u);
	for (auto &u : marines) combatunits.push_back(u);
	for (auto &u : tanks) combatunits.push_back(u);
	for (auto &u : workers)combatunits.push_back(u);
	for (auto &u : wraiths)combatunits.push_back(u);

	return combatunits;
}

/**
* A method for selecting a prioritized enemy to attack. Uses attackEnemyIfInRange()
* @author Asger Græsholt <s154099@dstudent.dtu.dk>
* @param unit a BWAPI unit who is to attack a nearby enemy, if any
* @see attackEnemyIfInRange()
*/
BWAPI::Unit CombatManager::findMostWantedEnemyToKill(BWAPI::UnitInterface* unit) {

	//Init target unit
	BWAPI::Unit desiredUnitToAttack = NULL;

	//Check if any unit in range is of following type.
	//TERRAN V PROTOSS________________________________________________
	desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Protoss_Dragoon, 300);

	if (desiredUnitToAttack == NULL)
		desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Protoss_Zealot, 300);

	if (desiredUnitToAttack == NULL && (unit->getType() == UnitTypes::Terran_Siege_Tank_Tank_Mode || unit->getType() == UnitTypes::Terran_Siege_Tank_Siege_Mode))
		desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Protoss_Photon_Cannon, UnitTypes::Terran_Siege_Tank_Siege_Mode.groundWeapon().maxRange());

	if (desiredUnitToAttack == NULL)
		desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Protoss_Probe, 300);

	//TERRAN V TERRAN________________________________________________
	if (desiredUnitToAttack == NULL)
		desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Terran_Siege_Tank_Siege_Mode, 300);

	if (desiredUnitToAttack == NULL)
		desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Terran_Vulture, 300);

	if (desiredUnitToAttack == NULL)
		desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Terran_Siege_Tank_Tank_Mode, 300);

	if (desiredUnitToAttack == NULL)
		desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Terran_Marine, 300);

	if (desiredUnitToAttack == NULL)
		desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Terran_Medic, 300);

	if (desiredUnitToAttack == NULL)
		desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Terran_SCV, 500);

	if (desiredUnitToAttack == NULL)
		desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Terran_Bunker, 300);

	//TERRAN V ZERG _________________________________________
	if (desiredUnitToAttack == NULL)
		desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Zerg_Lurker, 300);

	if (desiredUnitToAttack == NULL)
		desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Zerg_Lurker_Egg, 300);

	if (desiredUnitToAttack == NULL)
		desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Zerg_Hydralisk, 300);

	if (desiredUnitToAttack == NULL)
		desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Zerg_Zergling, 300);

	if (desiredUnitToAttack == NULL)
		desiredUnitToAttack = attackEnemyIfInRange(unit, UnitTypes::Zerg_Hydralisk_Den, 300);

	//If all fails: get nearest enemy ... and attack!
	if (desiredUnitToAttack == NULL)
		desiredUnitToAttack = unit->getClosestUnit(IsEnemy);

	return desiredUnitToAttack;
}

/**
* Attack with a unit at a given enemy type (target) if in range. Method returns an enemy of the specified type within range if found. NULL otherwise
* @author Asger Græsholt <s154099@dstudent.dtu.dk>
* @param unit
* @param target the target desired to attack if within a specified range
* @param range describes the maximum range we wish to attack an enemy within
* @see attackNearestEnemy()
*/
BWAPI::Unit CombatManager::attackEnemyIfInRange(BWAPI::UnitInterface* unit, BWAPI::UnitType target, int range) {
	BWAPI::Unit desiredUnitToAttack = NULL;

	//Loops through all enemies and checks if they are of the given type
	for (auto &eu : unit->getUnitsInRadius(range)) {
		if ((eu)->getType() == target && (eu)->getPlayer()->isEnemy(Broodwar->self())) {
			if (unit->getDistance(desiredUnitToAttack) > unit->getDistance(eu) && !(*eu).isBurrowed() && !(*eu).isCloaked()) {
				desiredUnitToAttack = eu;
			}
		}
	}
	return desiredUnitToAttack;
}

bool CombatManager::isInEnemyCriticalRange(BWAPI::UnitInterface* unit, BWAPI::UnitInterface* enemyUnit) {

	//Checks if enemy is too close to our unit.
	int enemyWeaponRange = enemyUnit->getType().groundWeapon().maxRange();
	int unitWeaponRangeMinus5Pct = unit->getType().groundWeapon().maxRange() - (unit->getType().groundWeapon().maxRange() / 20);
	int distanceToEnemy = unit->getPosition().getDistance(enemyUnit->getPosition());

	return (distanceToEnemy < unitWeaponRangeMinus5Pct);
}

bool CombatManager::isMelee(BWAPI::UnitInterface* unit) {
	//Checks if enemy uses melee attacks
	return (unit->getType().groundWeapon().damageAmount() > 2) && unit->getType().groundWeapon().maxRange() <= 15 && unit->getType() != UnitTypes::Terran_SCV;
}

bool CombatManager::shallMoveAwayFromEnemyInCriticalRange(BWAPI::UnitInterface* unit, int range) {
	bool enemiesInCriticalRange = false;

	//First check if unit are within critical range of a cannonn
	for (auto &eu : unit->getUnitsInRadius(UnitTypes::Protoss_Photon_Cannon.groundWeapon().maxRange() + UnitTypes::Protoss_Photon_Cannon.groundWeapon().maxRange() / 5)) {

		if ((*eu).getPlayer()->isEnemy(unit->getPlayer()) && (((*eu).getType() == UnitTypes::Protoss_Photon_Cannon || (*eu).getType() == UnitTypes::Zerg_Sunken_Colony) ||
			((eu)->getType() == UnitTypes::Terran_Bunker))) {

			BWAPI::Position movePosition = unit->getPosition() - (((*eu).getPosition() - unit->getPosition()));
			unit->move(movePosition);
			//Broodwar->drawCircleMap(movePosition, 20, Colors::Cyan, true);
			return true;
		}
	}

	//Otherwise evade as normal
	BWAPI::Position centerOfMass = Position(0, 0);
	for (auto &eu : unit->getUnitsInRadius(range)) {

		centerOfMass = centerOfMass + ((*eu).getPosition() - unit->getPosition());

		if ((eu)->getPlayer()->isEnemy(Broodwar->self()) && isInEnemyCriticalRange(unit, eu) && isMelee(eu) && !(*eu).getType().isBuilding()) {
			enemiesInCriticalRange = true;
			centerOfMass = centerOfMass + ((*eu).getPosition() - unit->getPosition());
		}
	}

	//Move away if enemy is too close.
	if (enemiesInCriticalRange) {

		int centerOfMassDistance = Position(0, 0).getDistance(centerOfMass);

		centerOfMass.x = (centerOfMass.x * 150 / centerOfMassDistance);
		centerOfMass.y = (centerOfMass.y * 150 / centerOfMassDistance);

		BWAPI::Position movePosition = unit->getPosition() - centerOfMass;
		unit->move(movePosition);
	}

	return enemiesInCriticalRange;
}


void CombatManager::attackEnemyBaseWithAllCombatUnits(BWAPI::Position enemyBasePosition) {
	attackLocation = enemyBasePosition;
	shouldAttack = true;
}

void CombatManager::attackEnemyBaseWhenVulturesAreGrouped(BWAPI::Position enemyBasePosition, int groupSize) {
	
	//Attack if vultures are grouped
	if (vultures.front()->unit->getUnitsInRadius(200).size() >= groupSize)
		attackEnemyBaseWithAllCombatUnits(enemyBasePosition);

	//Else move all units to first vulture location.
	else for (auto &u : vultures) u->unit->move(vultures.front()->unit->getPosition());
}

/**
* method makes all units deffend the base if they are within "range" from the commandCenter
* @author Asger Græsholt <s154099@dstudent.dtu.dk>
* @param range integer specifing a range from the base
*/
bool CombatManager::shouldDefendBase(int range, CustomUnit* unit) {
	bool defendingBase = false;

	//Get distance from closest enemy unit to command center
	if (buildingManager->commandCenter->getDistance(buildingManager->commandCenter->getClosestUnit(IsEnemy)) < range) {
		
		//If own unit is close to base, go and defend.
		if (buildingManager->commandCenter->getDistance(unit->unit) < range) {
			attackDesiredUnit(unit, findMostWantedEnemyToKill(unit->unit));
			defendingBase = true;
		}
	}
	return defendingBase;
}

void CombatManager::returnAllUnitsToBase() {
	//Return all units to base for defence
	for (auto &u : getAllCombatUnits()) 
		u->unit->move(buildingManager->commandCenter->getPosition());
}

bool tankCanMakeSiegeModeAttackOnStructure(BWAPI::UnitInterface* unit) {

	//If a tank is within attackrange of a building, enter siegemode
	for (auto &eu : unit->getUnitsInRadius(UnitTypes::Terran_Siege_Tank_Siege_Mode.groundWeapon().maxRange(), IsEnemy)) {

		if (eu->getType().isBuilding() && unit->getDistance(eu) > (UnitTypes::Terran_Siege_Tank_Siege_Mode.groundWeapon().maxRange()) / 2
			|| (Broodwar->enemy()->getRace() == Races::Terran && !eu->isFlying() )) {
			if (!unit->isSieged()) {
				unit->siege();
			}
			return true;
		}
	}
	return false;
}

bool CombatManager::fleeIfOutNumbered(Vulture* vulture, bool outNumbered) {
	//Stop fleeing if not outnumbered, or near hydralisk
	if (nearestHydra == NULL || outNumbered ) {
		return false;
	}
	//Flee if near hydralisk
	if (vulture->unit->getDistance(nearestHydra->getPosition()) < UnitTypes::Zerg_Hydralisk.groundWeapon().maxRange() * 2) {
		vulture->unit->move(buildingManager->commandCenter->getPosition());
		return true;
	}
	return false;
}

/**
* Deprecated method. Makes a worker unit repair any nearby damaged vehicles.
* @author Daniel Fjordhøj <s133198@dstudent.dtu.dk>
* @param worker Unit The worker assigned to repairs
*/
bool CombatManager::repairNearbyInjuredVehicles(BWAPI::Unit * worker) {
	//for (auto &umech : (*worker)->getUnitsInRadius(1000, IsAlly)) {
	//	//Broodwar->sendText("unit in radius: %s", umech->getType().c_str());

	//	if ((umech)->getType().isMechanical() && !(umech)->getType().isBuilding() && (umech)->getHitPoints() < (umech)->getType().maxHitPoints()) {
	//		Broodwar->sendText("REPAIRING %i", (umech)->getHitPoints());

	//		(*worker)->repair(umech);
	//		return true;
	//	}
	//}
	return false;
}

/**
* Takes a vulture unit, and evaluates if it should lay down a mine
* based on own state, enemy type and location.
* @author Daniel Fjordhøj <s133198@dstudent.dtu.dk>
* @param vulture Vulture The evaluated vulture
*/
bool CombatManager::shouldSetMine(Vulture* vulture, Race enemyRace, int frameCount) {
	//Place mines if not figting terrans
	if (!(enemyRace == Races::Terran) && vulture->canUseMine()) {
		if (vulture->hasBeenOcupied == 0 && minesInDefensiveChokePosition.size() < 3 && vulture->unit->getDistance(scoutingManager->startingChokePosition) < 50) {
			//Lay down mines is home base
			vulture->layDownMine(scoutingManager->startingChokePosition + Position(minesInDefensiveChokePosition.size() * 5, minesInDefensiveChokePosition.size() * 5), frameCount);
			return true;
		}
		else if (enemyRace == Races::Zerg && minesAtEnemeyBase.size() < 3 && vulture->unit->getDistance(scoutingManager->enemyChokePosition) < 100 && vulture->unit->getDistance(vulture->unit->getClosestUnit(Filter::GetType == UnitTypes::Terran_Vulture_Spider_Mine)) > 100) {
			//Lay down mines near enemy choke position 1
			vulture->layDownMine(vulture->unit->getPosition() + Position(2, 2), frameCount);
			return true;
		}
		else if (enemyRace == Races::Zerg && minesAtEnemeyBase.size() < 6 && vulture->unit->getDistance(scoutingManager->inEnemyBasePosition) < 150 && vulture->unit->getDistance(vulture->unit->getClosestUnit(Filter::GetType == UnitTypes::Terran_Vulture_Spider_Mine)) > 100) {
			//Lay down mines near enemy choke position 2
			vulture->layDownMine(vulture->unit->getPosition() + Position(2, 2), frameCount);
			return true;
		}
	}
	return false;
}

void CombatManager::attackDesiredUnit(CustomUnit* myUnit, BWAPI::Unit desiredUnitToAttack)
{
	//Attack target unit, if not a dark templar
	if (desiredUnitToAttack != NULL && desiredUnitToAttack->getType() != UnitTypes::Protoss_Dark_Templar
		&& myUnit->unitIsNewTarget(desiredUnitToAttack)) {
		myUnit->unit->attack(desiredUnitToAttack);
		myUnit->targetEnemy = (desiredUnitToAttack);
	}
	//Remove target if unit is not attacking
	else if (!myUnit->unit->isAttacking()) {
		myUnit->targetEnemy = NULL;
	}
}

bool CombatManager::calcOutNumbered(UnitInterface* nearestHydra) {
	if (nearestHydra != NULL && nearestHydra->isVisible()) {

		int numberOfEnemies = 1;
		int numberOfFriendlyUnits = 0;

		//Count all friendly and enemy units
		for (auto &u : nearestHydra->getUnitsInRadius(UnitTypes::Zerg_Hydralisk.groundWeapon().maxRange() * 2)) {
			if (u->getType() == UnitTypes::Terran_Vulture) numberOfFriendlyUnits++;
			else if (u->getType() == UnitTypes::Zerg_Hydralisk) numberOfEnemies++;
		}
		return numberOfEnemies + 3 > numberOfFriendlyUnits;
	}
	else {
		//If no hydralisk nearby, units are not outnumbered.
		distanceToHydra = -1;
		return false;
	}
}

void CombatManager::executeOrders() {
	//Evaluate if units are locally outnumbered by hydralisks
	
	bool outNumbered = calcOutNumbered(nearestHydra); 
	//Execute vulture actions
	for (auto &u : vultures) {

		Vulture* vulture = dynamic_cast<Vulture*>(u);
		UnitInterface* unit = (*vulture).nearestHydra(UnitTypes::Zerg_Hydralisk.groundWeapon().maxRange() * 2);

		//Find nearest hydralisk
		if (unit != NULL) {
			int vultureHydraDistance = unit->getDistance(vulture->unit->getPosition());
			if (vultureHydraDistance < distanceToHydra || distanceToHydra == -1) {
				nearestHydra = unit;
				distanceToHydra = vultureHydraDistance;
			}
		}
		//Attack if not on other task
		if (!shallMoveAwayFromEnemyInCriticalRange(u->unit, 120)) {
			if (!fleeIfOutNumbered(vulture, outNumbered)) {
				if (!vulture->isOcupied()) {
					if (!shouldSetMine(vulture, Broodwar->enemy()->getRace(), Broodwar->getFrameCount())) {
						if (!shouldDefendBase(1000, u) && shouldAttack) {
								attackDesiredUnit(u, findMostWantedEnemyToKill(u->unit));
						}
					}
				}
			}
		}
	}

	//Execute actions for all tanks
	for (auto &u : tanks) {
		//Siege mode attack 1. prio
		if (!tankCanMakeSiegeModeAttackOnStructure(u->unit)) {

			//If siege attack not possible => unsiege!
			if (u->unit->isSieged()) { u->unit->unsiege(); }

			//If the tank is not moving away from an enemy in critical range
			if (!shallMoveAwayFromEnemyInCriticalRange(u->unit, 120)) {

				//If the tank should not defend and we are attacking
				if (!shouldDefendBase(1000, u) && shouldAttack) {
					//find and attack the desired enemy
					attackDesiredUnit(u, findMostWantedEnemyToKill(u->unit));
				}
			}
		}
	}

	//Execute actions for combatunits
	for (auto &u : marines) if (!shouldDefendBase(1000, u) && shouldAttack) 
		attackDesiredUnit(u, findMostWantedEnemyToKill(u->unit));

	for (auto &u : wraiths) if (!shouldDefendBase(1000, u) && shouldAttack) 
		attackDesiredUnit(u, findMostWantedEnemyToKill(u->unit));

	
	for (auto &u : getAllCombatUnits()) {

		//Draw info on screen
		Broodwar->drawText(CoordinateType::Map, u->unit->getPosition().x, u->unit->getPosition().y, u->unit->getOrder().c_str());
		Broodwar->drawLineMap(u->unit->getPosition(), u->unit->getOrderTargetPosition(), Colors::Red);

		//If unit still is idle, move to attacklocation.
		if (u->unit->isIdle() && shouldAttack && !u->isOcupied()) {
			u->unit->move(attackLocation);
		}
		//And if still idle move to defencelocation
		else if (u->unit->isIdle() && !shouldAttack && !u->isOcupied()) {
			u->unit->move(scoutingManager->defendBasePosition);
		}

	}
}




