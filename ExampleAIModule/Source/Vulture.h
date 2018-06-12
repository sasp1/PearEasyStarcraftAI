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
	bool isOcupied();
	bool canUseMine();
	bool Vulture::isUnitIdle();
	void Vulture::layDownMine(BWAPI::Position targetPosition); 
	bool hasLayedDownDefensiveMine = false; 
	bool ocupiedLayingDownMine = false; 
	Unit* nearestHydra(int radius); 
	BWAPI::Position basePos;
	int hasBeenOcupied = 0; 
	int startTime = 0;
	int time;

};