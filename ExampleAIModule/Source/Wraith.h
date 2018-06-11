#pragma once
#include <BWAPI.h>
#include "CustomUnit.h"

class Wraith : public CustomUnit
{
public:
	Wraith(const BWAPI::Unit* u);
	bool isOcupied();
};
