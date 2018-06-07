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
	SpiralSearch* spiral;
	const BWAPI::Unit* center;
	const BWAPI::Unit* gas;
	const BWAPI::Unit* construct;
	BWAPI::UnitType buildOrder;
	BWAPI::Position originPos;
	BWAPI::Position buildPos;
	BWAPI::TilePosition tilePos;
	void Worker::collect();
	void Worker::stop();
	void Worker::replaceUnit(const BWAPI::Unit* worker);
	void Worker::initBuild(BWAPI::UnitType type, BWAPI::Position pos);
	bool Worker::handleBuild();
	bool Worker::isUnitIdle();
	bool Worker::isOcupied();
};