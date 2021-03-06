#include "SpiralSearch.h"

using namespace BWAPI;

/**
* @file SpiralSearch.cpp
* @brief Adds 2D values in a outward griwing rectangular spiral shape, which is used to be added to an origin point
* to find a valid point as close to the origin as possible
* @author Daniel Fjordh�j <s133198@student.dtu.dk>
*/

SpiralSearch::SpiralSearch(int dist){
	maxDist = dist;
}

BWAPI::TilePosition SpiralSearch::getNextTilePos() {
	//Get next location as TilePosition
	nextPoint(1);
	return BWAPI::TilePosition(x, y);
}
BWAPI::Position SpiralSearch::getNextPos() {
	//Get next location as Position
	nextPoint(30);
	return BWAPI::Position(x, y);
}

SpiralSearch::~SpiralSearch()
{
}

/**
* Get next point in a outwards spiral shaped search
* @param increment int Distance to add pr. spiral
* @author Daniel Fjordh�j <s133198@dstudent.dtu.dk>
*/
void SpiralSearch::nextPoint(int increment) {
		
	//Get comparison value
	int res = attempt % 8;

	//Begin searhing in a wider spiral
	if (res == 0) {
		maxX += increment;
		maxY += increment;
		x = maxX;
		y = maxY;
	}

	//Move around in spiral
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
	//Reset spiral 
	maxX = 0;
	maxY = 0;
	attempt = 6;
}