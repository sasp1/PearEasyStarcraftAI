#pragma once
#include <BWAPI.h>

class SpiralSearch
{
public:
	SpiralSearch(int maxDist);
	~SpiralSearch();

	int x = 0;
	int y = 0;
	int maxX = 0;
	int maxY = 0;
	int attempt = 0;

	BWAPI::TilePosition SpiralSearch::getNextTilePos();
	BWAPI::Position SpiralSearch::getNextPos();
};

