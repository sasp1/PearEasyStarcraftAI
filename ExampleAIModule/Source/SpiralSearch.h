#pragma once
#include <BWAPI.h>

class SpiralSearch
{
public:
	SpiralSearch(int dist);
	~SpiralSearch();
	int x = 0;
	int y = 0;
	int maxX = 0;
	int maxY = 0;
	int maxDist;
	int attempt = 6;
	BWAPI::TilePosition SpiralSearch::getNextTilePos();
	BWAPI::Position SpiralSearch::getNextPos();
	void SpiralSearch::nextPoint(int increment);
	void SpiralSearch::reset();
};

