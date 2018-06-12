#include "ExampleAIModule.h"
#include "GatheringManager.h"
#include "BuildingManager.h"
#include "UnitManager.h"
#include "ConstructionManager.h"
#include "CombatManager.h"
#include "StrategyManager.h"
#include "ScoutingManager.h"
#include "MapData.h"
#include <iostream>

using namespace BWAPI;
using namespace Filter;


GatheringManager* gatheringManager;
BuildingManager* buildingManager;
UnitManager* unitManager;
ConstructionManager* constructionManager;
ExecutionManager* executionManager;
CombatManager* combatManager;
ScoutingManager* scoutingManager;
StrategyManager* strategyManager;
MapData* mapData;

/**
* @file ExampleAIModule.cpp
* @brief "Main" class of the program. This is where actions from Starcraft are called thorugh BWAPI.
* @author Daniel Fjordhøj <s133198@student.dtu.dk>
*/

void ExampleAIModule::onStart()
{
	//Create manager classes
	gatheringManager = new GatheringManager();
	buildingManager = new BuildingManager();
	unitManager = new UnitManager();
	constructionManager = new ConstructionManager();
	executionManager = new ExecutionManager();
	mapData = new MapData();
	scoutingManager = new ScoutingManager(BWAPI::Position(BWAPI::Broodwar->self()->getStartLocation()), mapData);
	strategyManager = new StrategyManager();
	combatManager = new CombatManager();

	// Setting cross-references:
	strategyManager->scoutingManager = scoutingManager;
	strategyManager->constructionManager = constructionManager; 
	constructionManager->buildingManager = buildingManager;
	constructionManager->unitManager = unitManager;
	constructionManager->scoutingManager = scoutingManager; 
	scoutingManager->buildingManager = buildingManager;
	buildingManager->scoutingManager = scoutingManager;
	combatManager->buildingManager = buildingManager;
	buildingManager->gatheringManager = gatheringManager;
	gatheringManager->buildingManager = buildingManager;
	strategyManager->gatheringManager = gatheringManager;
	combatManager->scoutingManager = scoutingManager; 
	constructionManager->gatheringManager = gatheringManager;

	//Set cross references (Old)
	unitManager->setManagers(combatManager, gatheringManager, constructionManager, scoutingManager);
	executionManager->referenceManagers(unitManager, buildingManager);
	strategyManager->referenceManagers(executionManager, unitManager, buildingManager, combatManager);

  // Enable the UserInput flag, which allows us to control the bot and type messages.
  Broodwar->enableFlag(Flag::UserInput);

  // Set the command optimization level so that common commands can be grouped
  // and reduce the bot's APM (Actions Per Minute).
  Broodwar->setCommandOptimizationLevel(2);
  
  //Assign startup units to their managers
  for (auto &u : Broodwar->self()->getUnits())
  {
	  if (u->getType().isWorker())
		  (*unitManager).newWorker(&u);

	  else if (u->getType().isResourceDepot())
		  (*buildingManager).buildingCreated(&u);
  }
}

void ExampleAIModule::onFrame()
{
	// Called once every game frame
	// Display the game frame rate as text in the upper left area of the screen
	Broodwar->drawTextScreen(200, 0, "FPS: %d", Broodwar->getFPS());
	Broodwar->drawTextScreen(200, 20, "Average FPS: %f", Broodwar->getAverageFPS());

	// Return if the game is a replay or is paused
	if (Broodwar->isReplay() || Broodwar->isPaused() || !Broodwar->self())
		return;

	// Prevent spamming by only running our onFrame once every number of latency frames.
	// Latency frames are the number of frames before commands are processed.
	if (Broodwar->getFrameCount() % Broodwar->getLatencyFrames() != 0)
		return;

	//Begin strategy evaluation
	if (Broodwar->getFrameCount() > 2) {
		strategyManager->calculateOrders();
	}
}

void ExampleAIModule::onUnitComplete(BWAPI::Unit unit)
{//When a unit build is complete
	BWAPI::Unit* u = new Unit(unit);

	// makes sure unit is ally unit, and not a startup game unit
	if (Broodwar->self()->isAlly((*u)->getPlayer()) && Broodwar->getFrameCount() > 10) {

		//Add unit to unitmanager
		if ((*u)->getType().isWorker()) 
			(*unitManager).newWorker(u);
		else if ((*u)->getType() == UnitTypes::Terran_Marine)
			(*unitManager).addUnit(u);
		else if ((*u)->getType() == UnitTypes::Terran_Vulture)
			(*unitManager).addUnit(u);
		else if ((*u)->getType() == UnitTypes::Terran_Siege_Tank_Tank_Mode)
			(*unitManager).addUnit(u);
		else if ((*u)->getType() == UnitTypes::Terran_Wraith)
			(*unitManager).addUnit(u);

		//Add building to building manager
		else if ((*u)->getType().isBuilding()) {
			buildingManager->buildingCreated(u);
			strategyManager->unitComplete(u);
			unitManager->eventConstructionComplete(u);
		}
	}
}

void ExampleAIModule::onUnitCreate(BWAPI::Unit unit)
{
	BWAPI::Unit* u = new Unit(unit);

	//Add mine to unit manager
	if ((*u)->getType() == UnitTypes::Terran_Vulture_Spider_Mine) {
		(*unitManager).addUnit(u);
	}
	if (Broodwar->isReplay())
	{
		// if we are in a replay, then we will print out the build order of the structures
		if (unit->getType().isBuilding() && !unit->getPlayer()->isNeutral())
		{
			int seconds = Broodwar->getFrameCount() / 24;
			int minutes = seconds / 60;
			seconds %= 60;
			Broodwar->sendText("%.2d:%.2d: %s creates a %s", minutes, seconds, unit->getPlayer()->getName().c_str(), unit->getType().c_str());
		}
	}

	//Notify managers of construction of building has begun
	if (Broodwar->getFrameCount() > 10) {
		if (unit->getType().isBuilding()) {
			executionManager->eventConstructionInitiated(unit);
			constructionManager->constructionBegun(unit);
			unitManager->newConstructionIsAvailable = true;
		}
	}
}

void ExampleAIModule::onSendText(std::string text)
{
  // Send the text to the game if it is not being processed.
  Broodwar->sendText("%s", text.c_str());
}

void ExampleAIModule::onReceiveText(BWAPI::Player player, std::string text)
{
  // Parse the received text
  Broodwar << player->getName() << " said \"" << text << "\"" << std::endl;
}

void ExampleAIModule::onPlayerLeft(BWAPI::Player player)
{
  // Interact verbally with the other players in the game by
  // announcing that the other player has left.
  Broodwar->sendText("Goodbye %s!", player->getName().c_str());
}

void ExampleAIModule::onNukeDetect(BWAPI::Position target)
{

  // Check if the target is a valid position
  if ( target )
  {
    // if so, print the location of the nuclear strike target
    Broodwar << "Nuclear Launch Detected at " << target << std::endl;
  }
  else 
  {
    // Otherwise, ask other players where the nuke is!
    Broodwar->sendText("Where's the nuke?");
  }

  // You can also retrieve all the nuclear missile targets using Broodwar->getNukeDots()!
}

void ExampleAIModule::onUnitDiscover(BWAPI::Unit unit)
{
	scoutingManager->onUnitDiscover(unit);
}

void ExampleAIModule::onUnitEvade(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitShow(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitHide(BWAPI::Unit unit)
{
}

void ExampleAIModule::onUnitDestroy(BWAPI::Unit unit)
{
	strategyManager->onUnitDestroy(unit);

}

void ExampleAIModule::onUnitMorph(BWAPI::Unit unit)
{
  if ( Broodwar->isReplay() )
  {
    // if we are in a replay, then we will print out the build order of the structures
    if ( unit->getType().isBuilding() && !unit->getPlayer()->isNeutral() )
    {
      int seconds = Broodwar->getFrameCount()/24;
      int minutes = seconds/60;
      seconds %= 60;
      Broodwar->sendText("%.2d:%.2d: %s morphs a %s", minutes, seconds, unit->getPlayer()->getName().c_str(), unit->getType().c_str());
    }
  }
}

void ExampleAIModule::onUnitRenegade(BWAPI::Unit unit)
{
}

void ExampleAIModule::onSaveGame(std::string gameName)
{
  Broodwar << "The game was saved to \"" << gameName << "\"" << std::endl;
}

void ExampleAIModule::onEnd(bool isWinner)
{
	// Called when the game ends
	if (isWinner)
	{
		Broodwar->sendText("You Win");
	}
}

