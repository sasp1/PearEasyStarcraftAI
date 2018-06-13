#pragma once
#include <BWAPI.h>
#include "CustomUnit.h"

class SiegeTank : public CustomUnit
{
public:
	SiegeTank(BWAPI::UnitInterface* u);
	~SiegeTank();
	bool SiegeTank::isUnitIdle();
	BWAPI::UnitInterface* SiegeTank::getUnit();
	bool SiegeTank::isSiege();
	bool isOcupied(); 
};