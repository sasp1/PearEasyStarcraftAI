#include "StrategyManager.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;

bool academyOrdered = false; 
bool supplyDepotsAreNotUnderConstruction = true;
bool desireBuildingBarracks = true;
bool hasResearchedSiegeMode = false;
int refineriesOrdered = 0;
int factoriesOrdered = 0;
int starportsOrdered = 0; 
int basesOrdered = 0; 
int strategy = 1;
int numberOfWorkersLimit = 22;
int supplyUsed = 0; 
int mineralLimitOfWhenRessourcesAreFreeToUse = 700;
int gasLimitOfWhenRessourcesAreFreeToUse = 500;
bool tanksAreDesiredToBuild;
bool hasExpanded = false;

void StrategyManager::calculateOrders() {
	supplyUsed = Broodwar->self()->supplyUsed() / 2;
	tanksAreDesiredToBuild = false;

	//Set executionManager orders
	if (strategy == 1) {
		executeTwoFactory();
	}
	else if (strategy == 2) {
		executeExpandWithOneFactory();
	}


	executionManager->executeOrders();

}

void StrategyManager::executeTwoFactory() {
	//Build strategy 1 
	int unusedSupplies = (Broodwar->self()->supplyTotal()) - Broodwar->self()->supplyUsed();
	
	
	//___________________________Moving units________________________________
	//Maintain 1 soldier for scouting
	
	if (scoutingManager->scoutingUnits._Mysize() > 0) {
		buildingManager->barrackBuild = UnitTypes::None;
	} else {
		buildingManager->barrackBuild = UnitTypes::Terran_Marine;
	}
	

	//Maintain 22 workers

	if (gatheringManager->workers.size() > numberOfWorkersLimit) {

		buildingManager->setIsDesiredToTrainWorkers(false);
	}
	else {
		buildingManager->setIsDesiredToTrainWorkers(true);
	}
	
	
	//___________________________Building strategy________________________________


	//Construct supply depots when needed (2 supplies left)
	if (  unusedSupplies <= 4 && supplyDepotsAreNotUnderConstruction) {

		BWAPI::UnitType building = Broodwar->self()->getRace().getSupplyProvider();

			executionManager->addPriorityItem(building);
			supplyDepotsAreNotUnderConstruction = false;
	}



	//Order a refinery
	if (Broodwar->self()->supplyUsed() >= 22 && refineriesOrdered == 0) {
		Broodwar->sendText("adding refinery to priorityQueue");
		BWAPI::UnitType building = UnitTypes::Terran_Refinery;
		executionManager->addPriorityItem(building);
		refineriesOrdered++;
	}

	//Build barracks
	if (Broodwar->self()->supplyUsed() >= 22 && desireBuildingBarracks) {
		BWAPI::UnitType building = UnitTypes::Terran_Comsat_Station;

		Broodwar->sendText("adding barracks to priorityQueue");
		executionManager->addPriorityItem(building);
		desireBuildingBarracks = false;
	}

	//Order two factories
	if (Broodwar->self()->supplyUsed() >= 30 && factoriesOrdered < 2) {
		Broodwar->sendText("adding factory to priorityQueue");
		BWAPI::UnitType building = UnitTypes::Terran_Factory;
		executionManager->addPriorityItem(building);
		factoriesOrdered++;
	}


	//Continue with next strategy with an extra factory STRATEGY // && Broodwar->enemy()->getRace() == Races::Protoss
	if (!desireBuildingBarracks && factoriesOrdered == 2 ) {
		strategy = 2;
		Broodwar->sendText("Executing strategy: expandWithOneFactory");
	
	}

}


void StrategyManager::executeExpandWithOneFactory() {


	int unusedSupplies = (Broodwar->self()->supplyTotal()) - Broodwar->self()->supplyUsed();

	//___________________________Moving units________________________________
	//Maintain 1 soldier for scouting

	if ( (factoriesOrdered >=3  && Broodwar->self()->minerals() > mineralLimitOfWhenRessourcesAreFreeToUse || (scoutingManager->scoutingUnits._Mysize() < 1))) {
			buildingManager->barrackBuild = UnitTypes::Terran_Marine;
	}
	else {
		buildingManager->barrackBuild = UnitTypes::None;
	}

	//Maintain workers

	if (gatheringManager->workers.size() > numberOfWorkersLimit) {

		buildingManager->setIsDesiredToTrainWorkers(false);
	}
	else { 
		buildingManager->setIsDesiredToTrainWorkers(true);
	}

	//Spam voltures when no cannons are discovered
	if (((tanksAreDesiredToBuild || EnemyHasAStructureMakingTanksRequired()) && combatManager->tanks._Mysize() <= 4) || 
			(Broodwar->self()->minerals() > mineralLimitOfWhenRessourcesAreFreeToUse && Broodwar->self()->gas() > gasLimitOfWhenRessourcesAreFreeToUse && combatManager->vultures._Mysize() >= 10)) { // OR NumberOfTanks >=2
		tanksAreDesiredToBuild = true;
		buildingManager->factoryBuild = UnitTypes::Terran_Siege_Tank_Tank_Mode;
	}
	else {
		buildingManager->factoryBuild = UnitTypes::Terran_Vulture;
	}
	


	//___________________________Building strategy________________________________


	//Construct supply depots when needed (11 supplies left)
	if ((unusedSupplies <= 22)  && supplyDepotsAreNotUnderConstruction) {

		BWAPI::UnitType building = Broodwar->self()->getRace().getSupplyProvider();
		executionManager->addPriorityItem(building);
		supplyDepotsAreNotUnderConstruction = false;
	}


	//Maintain 3 factories  AND EXPAND BASE!!!!!!
	if (Broodwar->self()->supplyUsed() >= 72 && !hasExpanded && Broodwar->self()->minerals() > 400 && factoriesOrdered >= 3 && Broodwar->enemy()->getRace() != Races::Terran) {
		BWAPI::UnitType building = UnitTypes::Terran_Command_Center;
		numberOfWorkersLimit *= 2;
		Broodwar->sendText("adding command center to priorityQueue");
		executionManager->addPriorityItem(building);
		//executionManager->addPriorityItem(BWAPI::UnitTypes::Terran_Refinery);

		hasExpanded = true;
	}

	if (Broodwar->self()->supplyUsed() >= 72 && factoriesOrdered < 3) {
		Broodwar->sendText("adding factory to priorityQueue");
		BWAPI::UnitType building = UnitTypes::Terran_Factory;
		executionManager->addPriorityItem(building);
		factoriesOrdered++;
	}


	if (scoutingManager->enemyHasLurker && !academyOrdered) { //  && scoutingManager->enemyLurker != NULL && scoutingManager->enemyLurker->isVisible()
		Broodwar->sendText("Adding academy to priorityqueue because lurker was spotted"); 
		UnitType building = UnitTypes::Terran_Academy; 
		executionManager->addPriorityItem(building); 
		academyOrdered; 
	}
	//else if (scoutingManager->enemyHasLurker && scoutingManager->enemyLurker != NULL) {
	//	Broodwar->sendText("Enemylurker exists: %s", scoutingManager->enemyLurker->exists() ? "true" : "false"); 
	//}
	//else if (scoutingManager->enemyHasLurker) {
	//	Broodwar->sendText("enemylurker is NULL: %s", scoutingManager->enemyLurker == NULL ? "true" : "false");
	//}
	// Desire Siege Mode for tanks
	if (!hasResearchedSiegeMode && EnemyHasAStructureMakingTanksRequired()) {
		Broodwar->sendText("adding SiegeMode to priorityQueue");
		BWAPI::TechType research = TechTypes::Tank_Siege_Mode;
		buildingManager->desiredResearchs.push_back(research);
		hasResearchedSiegeMode = true;
	}

	
	

	//___________________________Attacking strategy________________________________
	
	if (combatManager->getAllCombatUnits()._Mysize() >= 2 && scoutingManager->enemyBaseFound && Broodwar->enemy()->getRace() == Races::Protoss) {
		combatManager->attackEnemyBaseWithAllCombatUnits(scoutingManager->lastEnemyBuildingPosition);
		if (combatManager->workers.size() < 1) {
			unitManager->makeASCVHelpArmy();
		}
	}
	else if (combatManager->vultures._Mysize() >= 8 && Broodwar->enemy()->getRace() == Races::Terran && scoutingManager->enemyBaseFound) {
		combatManager->attackEnemyBaseWithAllCombatUnits(scoutingManager->lastEnemyBuildingPosition);
	}
	else if (combatManager->vultures._Mysize() >= 1 && Broodwar->enemy()->getRace() == Races::Zerg) {
		combatManager->attackEnemyBaseWithAllCombatUnits(scoutingManager->lastEnemyBuildingPosition);
	}  //else if MySize = 1-2 ... set false... retreat...

}

bool StrategyManager::EnemyHasAStructureMakingTanksRequired() {
	for (auto &eu : Broodwar->enemy()->getUnits()) {
		if ((*eu).getType() == UnitTypes::Protoss_Photon_Cannon ) {
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