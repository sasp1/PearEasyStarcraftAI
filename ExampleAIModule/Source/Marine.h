#pragma once
#include <BWAPI.h>
#include "CustomUnit.h"

class Marine : public CustomUnit
{
public: 
	Marine(BWAPI::UnitInterface* u); 
	bool isOcupied(); 
};