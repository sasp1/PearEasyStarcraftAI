#pragma once
#include <BWAPI.h>
#include "CustomUnit.h"

class SiegeTank : public CustomUnit
{
public:
	SiegeTank(const BWAPI::Unit* u);
	~SiegeTank();
	bool SiegeTank::isUnitIdle();
	BWAPI::Unit SiegeTank::getUnit();
	const BWAPI::Unit* tank;
	bool SiegeTank::isSiege();
	bool isValid();
};