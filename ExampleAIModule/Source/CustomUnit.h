#pragma once
#include <BWAPI.h>

class CustomUnit 
{
public: 
	virtual bool isValid(); 
	CustomUnit(const BWAPI::Unit* u); 
	const BWAPI::Unit* unit; 
	virtual bool isOcupied() = 0; 
};