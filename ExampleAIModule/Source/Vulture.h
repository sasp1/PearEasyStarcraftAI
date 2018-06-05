#pragma once
#include <BWAPI.h>
#include "CustomUnit.h"

class Vulture : public CustomUnit
{
public:
	Vulture(const BWAPI::Unit* u, const BWAPI::Position basePosition);
	~Vulture();
	void putDownMineIfOutsideOfBase();
	const BWAPI::Unit* unit;
	BWAPI::Position basePos;
	int time;
	bool Vulture::isUnitIdle();
	bool isValid(); 
};