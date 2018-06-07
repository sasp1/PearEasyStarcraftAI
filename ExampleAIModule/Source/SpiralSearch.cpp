#include "SpiralSearch.h"

using namespace BWAPI;

SpiralSearch::SpiralSearch(int dist){
	maxDist = dist;
}

BWAPI::TilePosition SpiralSearch::getNextTilePos() {
	nextPoint(1);
	return BWAPI::TilePosition(x, y);
}
BWAPI::Position SpiralSearch::getNextPos() {
	nextPoint(30);
	//Broodwar->sendText("%d %d", x, y);
	return BWAPI::Position(x, y);
}

SpiralSearch::~SpiralSearch()
{

}

void SpiralSearch::nextPoint(int increment) {
		
	int res = attempt % 8;

	if (res == 0) {
		maxX += increment;
		maxY += increment;
		x = maxX;
		y = maxY;
	}

	else if (res == 1) x = 0;
	else if (res == 2) x = -maxX;
	else if (res == 3) y = 0;
	else if (res == 4) y = -maxY;
	else if (res == 5) x = 0;
	else if (res == 6) x = maxX;
	else if (res == 7) y = 0;

	attempt++;
}

void SpiralSearch::reset() {
	maxX = 0;
	maxY = 0;
	attempt = 6;
}