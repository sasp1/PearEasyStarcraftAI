#pragma once
#include <BWAPI.h>
#include "C"

class Worker : public CustomUnit
{
public:
	Worker(const BWAPI::Unit* u);
	~Worker();
	bool isOverTime(int t);
	const BWAPI::Unit* unit;
	int time;
	bool Worker::isUnitIdle();
	bool Worker::isUnitValid();
	const BWAPI::Unit* center;
	const BWAPI::Unit* gas;
	int workState = 0;
	void Worker::findCommandCenter();
	void Worker::updateCommandCenter(const BWAPI::Unit cc);
	void Worker::collect();
};