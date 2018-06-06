#pragma once
#include <BWAPI.h>
#include "CustomUnit.h"

class Worker : public CustomUnit
{
public:
	Worker(const BWAPI::Unit* u);
	~Worker();
	int time;
	int workState = 0;
	const BWAPI::Unit* center;
	const BWAPI::Unit* gas;
	const BWAPI::Unit* construct;
	BWAPI::UnitType buildOrder;
	BWAPI::Position pos;
	BWAPI::TilePosition tilePos;
	void Worker::collect();
	void Worker::stop();
	void Worker::replaceUnit(const BWAPI::Unit* worker);
	bool Worker::handleBuild();
	bool Worker::isUnitIdle();
	bool isOcupied(); 
	void Worker::addToSpiral();

};