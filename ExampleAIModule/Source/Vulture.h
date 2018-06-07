#pragma once
#include <BWAPI.h>
#include "CustomUnit.h"
using namespace BWAPI; 

class Vulture : public CustomUnit
{
public:
	Vulture(const BWAPI::Unit* u, const BWAPI::Position basePosition);
	~Vulture();
	void putDownMineIfOutsideOfBase();
	BWAPI::Position basePos;
	int time;
	bool Vulture::isUnitIdle();
	void Vulture::layDownMine(BWAPI::Position targetPosition); 
	bool hasLayedDownDefensiveMine = false; 
	bool ocupiedLayingDownMine = false; 
	int startTime = 0; 
	Unit* nearestHydra(int radius); 
	int hasBeenOcupied = 0; 
	bool isOcupied();
	bool canUseMine(); 
};