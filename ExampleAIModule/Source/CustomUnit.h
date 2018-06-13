#pragma once
#include <BWAPI.h>

class SpiralSearch;

class CustomUnit 
{
public: 
	virtual bool isOcupied() = 0;
	virtual bool isValid(); 
	bool unitIsNewTarget(BWAPI::UnitInterface* unit);
	CustomUnit(BWAPI::UnitInterface* u); 
	BWAPI::UnitInterface* unit = NULL; 
	BWAPI::Unit targetEnemy;

};