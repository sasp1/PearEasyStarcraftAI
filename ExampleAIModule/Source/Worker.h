#pragma once
#include <BWAPI.h>
#include "CustomUnit.h"

class Worker : public CustomUnit
{
public:
	Worker(const BWAPI::Unit* u);
	~Worker();
	bool isOverTime(int t);
	int time;
	bool Worker::isUnitIdle();
	const BWAPI::Unit* center;
	BWAPI::UnitType buildOrder;
	const BWAPI::Unit* gas;
	int workState = 0;
	void Worker::findCommandCenter();
	void Worker::updateCommandCenter(const BWAPI::Unit cc);
	void Worker::collect();
	void Worker::stop();
	bool Worker::handleBuild();
	bool isOcupied(); 
};