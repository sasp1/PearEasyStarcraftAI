#pragma once
#include <BWAPI.h>

class TimedUnit
{
public:
	TimedUnit(const BWAPI::Unit* u, int t);
	~TimedUnit();
	bool isOverTime(int t);
	const BWAPI::Unit* unit;
	int time;
	bool TimedUnit::isUnitIdle();
};