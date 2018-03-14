#pragma once
#include <BWAPI.h>
class ExecutionManager : public BWAPI::AIModule
{
public:
	ExecutionManager();
	~ExecutionManager();
	void ExecutionManager::handleCommand(const BWAPI::Unit* u);
	void ExecutionManager::handleWorker(const BWAPI::Unit* u);
	void ExecutionManager::addPriorityItem(BWAPI::UnitType unit);
};

