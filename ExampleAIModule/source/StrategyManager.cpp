#include "StrategyManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;

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
	//Handle workers and supplies
	supplyUsed = Broodwar->self()->supplyUsed() / 2;
	unusedSupplies = (Broodwar->self()->supplyTotal()) - Broodwar->self()->supplyUsed();
	buildingManager->setIsDesiredToTrainWorkers(!(gatheringManager->workers.size() > numberOfWorkersLimit));
	tanksAreDesiredToBuild = false;

	 //Allow build of supply depots if long time since last build
	
	 if(!supplyDepotsAreNotUnderConstruction){ 
		supplyDepotsAreNotUnderConstruction = (lastSupply + 1500 < Broodwar->getFrameCount());
	 }
	 
	 if (unusedSupplies/2 <= (Broodwar->self()->supplyTotal()/2)*0.2 && supplyDepotsAreNotUnderConstruction) {
		 if (unitManager->requestSupply()) {
			 lastSupply = Broodwar->getFrameCount();
			 supplyDepotsAreNotUnderConstruction = false;
		 }
	 }

	//Set executionManager orders
	if (strategy == 1) executeTwoFactory();
	else if (strategy == 2) executeExpandWithOneFactory();

	executionManager->executeOrders();
}

void StrategyManager::executeTwoFactory() {
	//Build strategy 1 
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

	//Continue with next strategy with an extra factory STRATEGY // && Broodwar->enemy()->getRace() == Races::Protoss
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

	//Spam voltures when no cannons are discovered
	if (  ( ((tanksAreDesiredToBuild || EnemyHasAStructureMakingTanksRequired()) && combatManager->tanks._Mysize() <= 4 ) || 
		(Broodwar->self()->minerals() > mineralLimitOfWhenRessourcesAreFreeToUse && Broodwar->self()->gas() > gasLimitOfWhenRessourcesAreFreeToUse ) )
			&& combatManager->vultures._Mysize() >= 10) { 

		tanksAreDesiredToBuild = true;
		buildingManager->factoryBuild = UnitTypes::Terran_Siege_Tank_Tank_Mode;
	}
	else buildingManager->factoryBuild = UnitTypes::Terran_Vulture;


	//Train wraiths when starport
	/*
	if (starportsOrdered >= 1) {
		buildingManager->starportBuild = UnitTypes::Terran_Wraith;
	}
	*/

	
	//___________________________Building strategy________________________________
	//Maintain 3 factories  AND EXPAND BASE!!!!!!

	//command center
	if (Broodwar->self()->supplyUsed() >= 72 && !hasExpanded && Broodwar->self()->minerals() > 400 && factoriesOrdered >= 3 && (Broodwar->enemy()->getRace() != Races::Terran || retreats>0) ) {
		numberOfWorkersLimit *= 2;
		Broodwar->sendText("adding command center to priorityQueue");
		executionManager->addPriorityItem(UnitTypes::Terran_Command_Center);
		hasExpanded = true;
	}

	//Factories 
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

	//academy
	if (scoutingManager->enemyHasLurker && !academyOrdered) {
		Broodwar->sendText("Adding academy to priorityqueue because lurker was spotted"); 
		executionManager->addPriorityItem(UnitTypes::Terran_Academy);
		academyOrdered = true; 
	}

/*
	if (Broodwar->self()->minerals() > 700 && !builtArmory) {
		Broodwar->sendText("Adding armory and techs");
		executionManager->addPriorityItem(UnitTypes::Terran_Armory);
		builtArmory = true;
	}
	*/

	/*
	if ( Broodwar->enemy()->getRace() == Races::Terran && retreats>0 && starportsOrdered < 1) {
		Broodwar->sendText("adding starport to priorityQueue");
		executionManager->addPriorityItem(UnitTypes::Terran_Starport);
		starportsOrdered++;
		Broodwar->sendText("adding factory to priorityQueue");
		executionManager->addPriorityItem(UnitTypes::Terran_Factory);
		factoriesOrdered++;
	}
	*/

	//else if (scoutingManager->enemyHasLurker && scoutingManager->enemyLurker != NULL) {
	//	Broodwar->sendText("Enemylurker exists: %s", scoutingManager->enemyLurker->exists() ? "true" : "false"); 
	//}
	//else if (scoutingManager->enemyHasLurker) {
	//	Broodwar->sendText("enemylurker is NULL: %s", scoutingManager->enemyLurker == NULL ? "true" : "false");
	//}
	// Desire Siege Mode for tanks
	if (!hasResearchedSiegeMode && tanksAreDesiredToBuild) {
		Broodwar->sendText("adding SiegeMode to priorityQueue");
		buildingManager->desiredResearchs.push_back(TechTypes::Tank_Siege_Mode);
		hasResearchedSiegeMode = true;
	}

	//___________________________Attacking strategy________________________________

	if (Broodwar->enemy()->getRace() == Races::Protoss) {
		attackingStrategyProtoss();
	} else if (Broodwar->enemy()->getRace() == Races::Terran) {
		attackingStrategyTerran();
	} else if (Broodwar->enemy()->getRace() == Races::Zerg) {
		attackingStrategyZerg();
	}


}

void StrategyManager::attackingStrategyTerran() {

		//First attack
		if (combatManager->vultures._Mysize() >= 8 && scoutingManager->enemyBaseFound && !combatManager->shouldAttack && retreats < 1) {
			combatManager->attackEnemyBaseWhenVulturesAreGrouped(scoutingManager->lastEnemyBuildingPosition, 8);
		}

		//Second attack
		if (combatManager->vultures._Mysize() >= 1 && scoutingManager->enemyBaseFound && !combatManager->shouldAttack && retreats > 0) {
			combatManager->attackEnemyBaseWithAllCombatUnits(scoutingManager->lastEnemyBuildingPosition);
		}
	

		//retreat
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

	if (combatManager->vultures._Mysize() >= 1 ) {
		combatManager->attackEnemyBaseWithAllCombatUnits(scoutingManager->lastEnemyBuildingPosition);
	}
}
void StrategyManager::attackingStrategyProtoss() {

	if (combatManager->getAllCombatUnits()._Mysize() >= 2 && scoutingManager->enemyBaseFound) {
		combatManager->attackEnemyBaseWithAllCombatUnits(scoutingManager->lastEnemyBuildingPosition);
		if (combatManager->workers.size() < 1) unitManager->makeASCVHelpArmy();
	}
}

bool StrategyManager::EnemyHasAStructureMakingTanksRequired() {
	for (auto &eu : Broodwar->enemy()->getUnits()) {
		if ((*eu).getType() == UnitTypes::Protoss_Photon_Cannon) {
			return true;
		}
	}
	return false;
}


void StrategyManager::unitComplete(const BWAPI::Unit* unit) {

	if ((*unit)->getType() == UnitTypes::Terran_Supply_Depot) {
		supplyDepotsAreNotUnderConstruction = true;
	}
}

void StrategyManager::onUnitDestroy(BWAPI::Unit unit) {
	if (unit->getPlayer()->isEnemy(Broodwar->self())) {
		if (unit->getType() == UnitTypes::Protoss_Photon_Cannon ) {
			Broodwar->sendText("Cannon killed");
			tanksAreDesiredToBuild = false;
		}
	}
}

// Iniitial class setup
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