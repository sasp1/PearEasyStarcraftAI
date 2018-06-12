#include "StrategyManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;

/**
* @file StrategyManager.cpp
* @brief Handles the overall strategy decision of the team.
* Keeps track of the state of the game, and thereby decides which building to construct,
* units to train, and actions to perform.
* @author Daniel Fjordhøj <s133198@student.dtu.dk>
*/

bool academyOrdered = false; 
bool supplyDepotsAreNotUnderConstruction = true;
bool desireBuildingBarracks = true;
bool hasResearchedSiegeMode = false;
bool builtArmory = false;
int refineriesOrdered = 0;
int factoriesOrdered = 0;
int starportsOrdered = 0; 
int basesOrdered = 0; 
int strategy = 1;
int numberOfWorkersLimit = 22;
int supplyUsed = 0; 
int unusedSupplies = 0;
int mineralLimitOfWhenRessourcesAreFreeToUse = 700;
int gasLimitOfWhenRessourcesAreFreeToUse = 500;
bool tanksAreDesiredToBuild;
bool hasExpanded = false;
int retreats = 0;


void StrategyManager::calculateOrders() {
	//Update supply count, and update if workers should be built
	supplyUsed = Broodwar->self()->supplyUsed() / 2;
	unusedSupplies = (Broodwar->self()->supplyTotal()) - Broodwar->self()->supplyUsed();
	buildingManager->setIsDesiredToTrainWorkers(!(gatheringManager->workers.size() > numberOfWorkersLimit));
	tanksAreDesiredToBuild = false;

	 //Allow build of supply depots if long time since last build
	 if(!supplyDepotsAreNotUnderConstruction)
		supplyDepotsAreNotUnderConstruction = (lastSupply + 1500 < Broodwar->getFrameCount());

	 //Request new supply depot if less than 20 % space for new units
	 if (unusedSupplies/2 <= (Broodwar->self()->supplyTotal()/2)*0.2 && supplyDepotsAreNotUnderConstruction) {
		 if (unitManager->requestSupply()) {
			 lastSupply = Broodwar->getFrameCount();
			 supplyDepotsAreNotUnderConstruction = false;
		 }
	 }

	//Set strategy to follow
	if (strategy == 1) executeTwoFactory();
	else if (strategy == 2) executeExpandWithOneFactory();

	//Activate executionManager
	executionManager->executeOrders();
}


void StrategyManager::executeTwoFactory() {

	//___________________________Moving units________________________________
	//Maintain 1 soldier for scouting
	if (scoutingManager->scoutingUnits._Mysize() > 0) buildingManager->barrackBuild = UnitTypes::None;
	else buildingManager->barrackBuild = UnitTypes::Terran_Marine;
	
	//___________________________Building strategy________________________________
	//Construct supply depots when needed (2 supplies left)

	//Build barracks
	if (Broodwar->self()->supplyUsed() >= 22 && desireBuildingBarracks) {
		Broodwar->sendText("adding barracks to priorityQueue");
		executionManager->addPriorityItem(UnitTypes::Terran_Barracks);
		desireBuildingBarracks = false;
	}

	//Order a refinery
	if (Broodwar->self()->supplyUsed() >= 22 && refineriesOrdered == 0) {
		Broodwar->sendText("adding refinery to priorityQueue");
		executionManager->addPriorityItem(UnitTypes::Terran_Refinery);
		refineriesOrdered++;
	}

	//Order two factories
	if (Broodwar->self()->supplyUsed() >= 30 && factoriesOrdered < 2) {
		Broodwar->sendText("adding factory to priorityQueue");
		executionManager->addPriorityItem(UnitTypes::Terran_Factory);
		factoriesOrdered++;
	}

	//Continue with next strategy with an extra factory
	if (!desireBuildingBarracks && factoriesOrdered == 2 ) {
		strategy = 2;
		Broodwar->sendText("Executing strategy: expandWithOneFactory");
	}
}


void StrategyManager::executeExpandWithOneFactory() {

	//___________________________Moving units________________________________
	//Maintain 1 soldier for scouting
	if ( (factoriesOrdered >=3 && Broodwar->self()->minerals() > mineralLimitOfWhenRessourcesAreFreeToUse || (scoutingManager->scoutingUnits._Mysize() < 1))) {
			buildingManager->barrackBuild = UnitTypes::Terran_Marine;
	}
	else buildingManager->barrackBuild = UnitTypes::None;

	//If cannons exist, build tanks, else spam vultures
	if (  ( ((tanksAreDesiredToBuild || EnemyHasAStructureMakingTanksRequired()) && combatManager->tanks._Mysize() <= 4 ) || 
		(Broodwar->self()->minerals() > mineralLimitOfWhenRessourcesAreFreeToUse && Broodwar->self()->gas() > gasLimitOfWhenRessourcesAreFreeToUse ) )
			&& combatManager->vultures._Mysize() >= 10) { 

		tanksAreDesiredToBuild = true;
		buildingManager->factoryBuild = UnitTypes::Terran_Siege_Tank_Tank_Mode;
	}
	else buildingManager->factoryBuild = UnitTypes::Terran_Vulture;

	//Train wraiths when starport exist
	if (starportsOrdered >= 1) {
		buildingManager->starportBuild = UnitTypes::Terran_Wraith;
	}
	
	//___________________________Building strategy________________________________
	//Maintain 3 factories  AND EXPAND BASE!!!!!!

	//Request command center
	if (Broodwar->self()->supplyUsed() >= 72 && !hasExpanded && Broodwar->self()->minerals() > 400 && factoriesOrdered >= 3 && (Broodwar->enemy()->getRace() != Races::Terran || retreats>0) ) {
		numberOfWorkersLimit *= 2;
		Broodwar->sendText("adding command center to priorityQueue");
		executionManager->addPriorityItem(UnitTypes::Terran_Command_Center);
		hasExpanded = true;
	}

	//Request Factories 
	if (Broodwar->self()->supplyUsed() >= 72 && factoriesOrdered < 3 && (Broodwar->enemy()->getRace() != Races::Terran || retreats>0)) {
		Broodwar->sendText("adding factory to priorityQueue");
		executionManager->addPriorityItem(UnitTypes::Terran_Factory);
		factoriesOrdered++;
	}

	if (Broodwar->self()->supplyUsed() >= 200 && factoriesOrdered < 5 && hasExpanded && (Broodwar->enemy()->getRace() != Races::Terran || retreats>0)) {
		Broodwar->sendText("adding factory to priorityQueue");
		executionManager->addPriorityItem(UnitTypes::Terran_Factory);
		factoriesOrdered++;
	}

	//Request academy
	if (scoutingManager->enemyHasLurker && !academyOrdered) {
		Broodwar->sendText("Adding academy to priorityqueue because lurker was spotted"); 
		executionManager->addPriorityItem(UnitTypes::Terran_Academy);
		academyOrdered = true; 
	}

	//Request armory
	if (Broodwar->self()->minerals() > 2500 && !builtArmory) {
		Broodwar->sendText("Adding armory and techs");
		executionManager->addPriorityItem(UnitTypes::Terran_Armory);
		builtArmory = true;
	}

	//Request starport
	if ( Broodwar->enemy()->getRace() == Races::Terran && retreats>0 && starportsOrdered < 1 && Broodwar->self()->minerals() > 2000 && Broodwar->self()->gas() > 700) {
		Broodwar->sendText("adding starport to priorityQueue");
		executionManager->addPriorityItem(UnitTypes::Terran_Starport);
		starportsOrdered++;
	}
	
	// Request Siege Mode research
	if (!hasResearchedSiegeMode && tanksAreDesiredToBuild) {
		Broodwar->sendText("adding SiegeMode to priorityQueue");
		buildingManager->desiredResearchs.push_back(TechTypes::Tank_Siege_Mode);
		hasResearchedSiegeMode = true;
	}

	//___________________________Attacking strategy________________________________

	//Execute attack strategy based on race
	if (Broodwar->enemy()->getRace() == Races::Protoss) {
		attackingStrategyProtoss();
	} else if (Broodwar->enemy()->getRace() == Races::Terran) {
		attackingStrategyTerran();
	} else if (Broodwar->enemy()->getRace() == Races::Zerg) {
		attackingStrategyZerg();
	}
}

void StrategyManager::attackingStrategyTerran() {

		//Execute initial vulture attack
		if (combatManager->vultures._Mysize() >= 8 && scoutingManager->enemyBaseFound && !combatManager->shouldAttack && retreats < 1)
			combatManager->attackEnemyBaseWhenVulturesAreGrouped(scoutingManager->lastEnemyBuildingPosition, 8);

		//Execute subsequent vulture attacks
		if (combatManager->vultures._Mysize() >= 1 && scoutingManager->enemyBaseFound && !combatManager->shouldAttack && retreats > 0)
			combatManager->attackEnemyBaseWithAllCombatUnits(scoutingManager->lastEnemyBuildingPosition);

		//Retreat if low on vultures
		else if (combatManager->shouldAttack && combatManager->vultures._Mysize() <= 4) {
			bool shouldRetreat = true;
			for (auto &u : combatManager->vultures) {
				if ((*u->unit)->getDistance(scoutingManager->lastEnemyBuildingPosition) < 1000) {
					shouldRetreat = false;
				}
			}
			combatManager->shouldAttack = !shouldRetreat;
			if (shouldRetreat) {
				Broodwar->sendText("Retreaaat");
				combatManager->returnAllUnitsToBase();
				retreats++;
			}
		}
}


void StrategyManager::attackingStrategyZerg() {
	//Attack constantly with all vultures if enemy base is fouund
	if (combatManager->vultures._Mysize() >= 1 )
		combatManager->attackEnemyBaseWithAllCombatUnits(scoutingManager->lastEnemyBuildingPosition);
}
void StrategyManager::attackingStrategyProtoss() {
	//Attack constantly with vultures if enemy base is found. Maintan one worker to repare units
	if (combatManager->getAllCombatUnits()._Mysize() >= 2 && scoutingManager->enemyBaseFound) {
		combatManager->attackEnemyBaseWithAllCombatUnits(scoutingManager->lastEnemyBuildingPosition);
		if (combatManager->workers.size() < 1) unitManager->makeASCVHelpArmy();
	}
}

bool StrategyManager::EnemyHasAStructureMakingTanksRequired() {
	//Evaluate if tanks are needed
	for (auto &eu : Broodwar->enemy()->getUnits()) {
		if ((*eu).getType() == UnitTypes::Protoss_Photon_Cannon) {
			return true;
		}
	}
	return false;
}


void StrategyManager::unitComplete(const BWAPI::Unit* unit) {
	//Allow construction of supply depots if one has been built
	if ((*unit)->getType() == UnitTypes::Terran_Supply_Depot) {
		supplyDepotsAreNotUnderConstruction = true;
	}
}

void StrategyManager::onUnitDestroy(BWAPI::Unit unit) {
	//Remove deisre for tanks if a cannon has been destroyed
	if (unit->getPlayer()->isEnemy(Broodwar->self())) {
		if (unit->getType() == UnitTypes::Protoss_Photon_Cannon ) {
			Broodwar->sendText("Cannon killed");
			tanksAreDesiredToBuild = false;
		}
	}
}

void StrategyManager::referenceManagers(ExecutionManager* executionManager, UnitManager* unitManager, BuildingManager* buildingManager, CombatManager* combatManager) {
	this->executionManager = executionManager;
	this->unitManager = unitManager;
	this->buildingManager = buildingManager;
	this->combatManager = combatManager;
}

StrategyManager::~StrategyManager()
{
}

StrategyManager::StrategyManager()
{
}