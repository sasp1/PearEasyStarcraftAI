#include "ExampleAIModule.h"
#include "GatheringManager.h"
#include "BuildingManager.h"
#include "UnitManager.h"
#include "ConstructionManager.h"
#include <iostream>

using namespace BWAPI;
using namespace Filter;


GatheringManager* gatheringManager;
BuildingManager* buildingManager;
UnitManager* unitManager;
ConstructionManager* constructionManager;

bool desireBuildingSupplyDepot;
bool desireBuildingBarracks;


void ExampleAIModule::buildConstruction(BWAPI::UnitType building)
{
	//Issue an order to build a construction
	constructionManager->createBuilding(building, gatheringManager->removeWorker());
}





void ExampleAIModule::onStart()
{
	//Create managers
	gatheringManager = new GatheringManager();
	buildingManager = new BuildingManager();
	unitManager = new UnitManager();
	constructionManager = new ConstructionManager();

	desireBuildingSupplyDepot = true;
	desireBuildingBarracks = true;
	
	//Make managers aware of each other
	unitManager->setManagers(buildingManager, gatheringManager, constructionManager);

  // HEJ 
  // Hello World!
  Broodwar->sendText("Test v1.0");

  // Enable the UserInput flag, which allows us to control the bot and type messages.
  Broodwar->enableFlag(Flag::UserInput);

  // Uncomment the following line and the bot will know about everything through the fog of war (cheat).
  //Broodwar->enableFlag(Flag::CompleteMapInformation);

  // Set the command optimization level so that common commands can be grouped
  // and reduce the bot's APM (Actions Per Minute).
  Broodwar->setCommandOptimizationLevel(2);
  
  //Assign startup units to their managers
  for (auto &u : Broodwar->self()->getUnits())
  {
	  if (u->getType().isWorker())
		  (*unitManager).newWorker(&u);

	  else if (u->getType().isResourceDepot())
		  (*buildingManager).addCommandCenter(&u);

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

	if (Broodwar->getFrameCount() > 2) {

		//Build strategy 1 
		int unusedSupplies = (Broodwar->self()->supplyTotal()) - Broodwar->self()->supplyUsed();

		//Spam supply depots when needed
		if (unusedSupplies <= 4 && desireBuildingSupplyDepot) {

			BWAPI::UnitType building = Broodwar->self()->getRace().getSupplyProvider();
			Broodwar->sendText("Want To build supply depot");

			if (Broodwar->self()->minerals() > building.mineralPrice()) {
				Broodwar->sendText("IsBuilding");
				//buildingManager->setIsDesiredToBuildWorkers(false);
				buildConstruction(building);
				desireBuildingSupplyDepot = false;
			}
		}

		//Build barracks
		if (Broodwar->self()->supplyUsed() >= 22 && desireBuildingBarracks){
			BWAPI::UnitType building = UnitTypes::Terran_Barracks;
			Broodwar->sendText("Want To build barracks %i", Broodwar->self()->supplyUsed());

			if (Broodwar->self()->minerals() > building.mineralPrice()) {
				Broodwar->sendText("Is Building barracks");
				//buildingManager->setIsDesiredToBuildWorkers(false);
				buildConstruction(building);
				desireBuildingBarracks = false;
			}
		}

		
		//End of strategy 1

		// Finally execute the strategy
		gatheringManager->executeOrders();
		buildingManager->executeOrders();
		unitManager->executeOrders();
	}

		
	
} // closure: unit iterator

void ExampleAIModule::onUnitComplete(BWAPI::Unit unit)
{//When a unit build is complete
	

	BWAPI::Unit* u = new Unit(unit);

	if (Broodwar->getFrameCount() > 10) {
		if ((*u)->getType().isWorker())
			(*gatheringManager).addWorker(u);

		else if ((*u)->getType().isBuilding()) {
			//unitManager->eventConstructionComplete();
			//Tjek at bygning er supplydepot!!
			if ((*u)->getType() == UnitTypes::Terran_Barracks) {
				Broodwar->sendText("%s", "Completed building barracks");
				buildingManager->addBarracks(u);

			}
			if ((*u)->getType() == UnitTypes::Terran_Supply_Depot) {
				desireBuildingSupplyDepot = true;
				Broodwar->sendText("%s", "Completed building supl. depot");
			}
			//Kan blive null!?
			//gatheringManager->addWorker(constructionManager->removeWorkersDoneConstructing);
			
			


		

		}

	}
}



void ExampleAIModule::onUnitCreate(BWAPI::Unit unit)
{
	if (Broodwar->isReplay())
	{
		// if we are in a replay, then we will print out the build order of the structures
		if (unit->getType().isBuilding() && !unit->getPlayer()->isNeutral())
		{
			int seconds = Broodwar->getFrameCount() / 24;
			int minutes = seconds / 60;
			seconds %= 60;
			Broodwar->sendText("%.2d:%.2d: %s createsssss a %s", minutes, seconds, unit->getPlayer()->getName().c_str(), unit->getType().c_str());
		}
	}
	Broodwar->sendText("Creatingsssss");

	//When construction of a unit has begun

	if (Broodwar->getFrameCount() > 10) {
		if (unit->getType().isBuilding()) {
			unitManager->eventConstructionInitiated();
		}
	}
}

void ExampleAIModule::onSendText(std::string text)
{

  // Send the text to the game if it is not being processed.
  Broodwar->sendText("%s", text.c_str());


  // Make sure to use %s and pass the text as a parameter,
  // otherwise you may run into problems when you use the %(percent) character!

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

