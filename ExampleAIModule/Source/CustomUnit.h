#pragma once
#include <BWAPI.h>

class SpiralSearch;

class CustomUnit 
{
public: 
	virtual bool isValid(); 
	CustomUnit(const BWAPI::Unit* u); 
	const BWAPI::Unit* unit = NULL; 
	virtual bool isOcupied() = 0; 

	BWAPI::Unit targetEnemy;
	bool unitIsNewTarget(BWAPI::Unit unit);
};