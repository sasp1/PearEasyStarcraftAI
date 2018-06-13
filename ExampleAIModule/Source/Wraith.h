#pragma once
#include <BWAPI.h>
#include "CustomUnit.h"

class Wraith : public CustomUnit
{
public:
	Wraith(BWAPI::UnitInterface* u);
	bool isOcupied();
};
