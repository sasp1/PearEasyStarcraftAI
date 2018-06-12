#pragma once
#include <BWAPI.h>

class SpiralSearch;

class CustomUnit 
{
public: 
	virtual bool isOcupied() = 0;
	virtual bool isValid(); 
	bool unitIsNewTarget(BWAPI::Unit unit);
	CustomUnit(const BWAPI::Unit* u); 
	const BWAPI::Unit* unit = NULL; 
	BWAPI::Unit targetEnemy;

};