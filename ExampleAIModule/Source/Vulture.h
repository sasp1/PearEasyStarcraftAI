#pragma once
#include <BWAPI.h>

class Vulture
{
public:
	Vulture(const BWAPI::Unit* u, const BWAPI::Position basePosition);
	~Vulture();
	void putDownMineIfOutsideOfBase();
	const BWAPI::Unit* unit;
	BWAPI::Position basePos;
	int time;
	bool Vulture::isUnitIdle();
};