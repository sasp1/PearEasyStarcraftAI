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
	bool SiegeTank::isSiege();
	bool isOcupied(); 
};