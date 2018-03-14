#pragma once
#include <BWAPI.h>
#include "ExecutionManager.h"

class StrategyManager
{
	ExecutionManager* executionManager;
public:

	StrategyManager();
	~StrategyManager();
	void StrategyManager::calculateOrders();
	void StrategyManager::referenceManagers(ExecutionManager* executionManager);
	void StrategyManager::calculateStrategy();
	void StrategyManager::unitComplete(const BWAPI::Unit* unit);
};

