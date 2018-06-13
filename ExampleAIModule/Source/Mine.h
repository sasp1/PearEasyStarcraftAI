#pragma once
#include <BWAPI.h>
#include "CustomUnit.h"

class Mine : public CustomUnit
{
public:
	Mine(BWAPI::UnitInterface* u);
	bool isOcupied(); 
};