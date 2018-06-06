#pragma once
#include <BWAPI.h>
#include "CustomUnit.h"

class Vulture : public CustomUnit
{
public:
	Vulture(const BWAPI::Unit* u, const BWAPI::Position basePosition);
	~Vulture();
	void putDownMineIfOutsideOfBase();
	BWAPI::Position basePos;
	int time;
	bool Vulture::isUnitIdle();
	void layDownDefensiveMine(BWAPI::Position targetPosition); 
	bool hasLayedDownDefensiveMine = false; 
	bool ocupiedLayingDownMine = false; 
	int startTime = 0; 
	int hasBeenOcupied = 0; 
	bool isOcupied();
	bool canUseMine(); 
};