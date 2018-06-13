#pragma once
#include <BWAPI.h>
#include "CustomUnit.h"

class Worker : public CustomUnit
{
public:
	Worker(BWAPI::UnitInterface* u);
	~Worker();
	int time;
	int workState = 0;
	SpiralSearch* spiral;
	BWAPI::UnitInterface* center;
	BWAPI::UnitInterface* gas;
	BWAPI::UnitInterface* construct;
	BWAPI::UnitType buildOrder;
	BWAPI::Position originPos;
	BWAPI::Position buildPos;
	BWAPI::TilePosition tilePos;
	void Worker::collect();
	void Worker::stop();
	void Worker::replaceUnit(BWAPI::UnitInterface* worker);
	void Worker::initBuild(BWAPI::UnitType type, BWAPI::Position pos);
	bool Worker::handleBuild();
	bool Worker::isUnitIdle();
	bool Worker::isOcupied();
};