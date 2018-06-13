#pragma once
#include <BWAPI.h>
#include "CustomUnit.h"
using namespace BWAPI; 

class Vulture : public CustomUnit
{
public:
	Vulture(BWAPI::UnitInterface* u, BWAPI::Position basePosition);
	~Vulture();
	void putDownMineIfOutsideOfBase();
	bool isOcupied();
	bool canUseMine();
	bool Vulture::isUnitIdle();
	void Vulture::layDownMine(BWAPI::Position targetPosition, int frameCount);
	bool hasLayedDownDefensiveMine = false; 
	bool ocupiedLayingDownMine = false; 
	UnitInterface* nearestHydra(int radius); 
	BWAPI::Position basePos;
	int hasBeenOcupied = 0; 
	int startTime = 0;
	int time;

};