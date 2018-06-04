#pragma once
#include <BWAPI.h>

class SiegeTank
{
public:
	SiegeTank(const BWAPI::Unit* u);
	~SiegeTank();
	bool SiegeTank::isUnitIdle();
	bool SiegeTank::isUnitValid();
	BWAPI::Unit SiegeTank::getUnit();
	const BWAPI::Unit* tank;
	bool SiegeTank::isSiege();
};