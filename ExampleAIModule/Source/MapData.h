#pragma once
#include <BWAPI.h>
class MapData
{
public:
	MapData();
	~MapData();

	BWAPI::Position northwestChokePointMid;
	BWAPI::Position northwestChokePointTop;
	BWAPI::Position northwestChokePointBot;
	BWAPI::Position northwestChokePointLeft;
	BWAPI::Position northwestChokePointRight;
	BWAPI::Position northwestExpand;
	BWAPI::Position northwestDefend;
	BWAPI::Position northwestAttack;

	BWAPI::Position southwestChokePointMid;
	BWAPI::Position southwestChokePointTop;
	BWAPI::Position southwestChokePointBot;
	BWAPI::Position southwestChokePointLeft;
	BWAPI::Position southwestChokePointRight;
	BWAPI::Position southwestExpand;
	BWAPI::Position southwestDefend;
	BWAPI::Position southwestAttack;
	
	BWAPI::Position northeastChokePointMid;
	BWAPI::Position northeastChokePointTop;
	BWAPI::Position northeastChokePointBot;
	BWAPI::Position northeastChokePointLeft;
	BWAPI::Position northeastChokePointRight;
	BWAPI::Position northeastExpand;
	BWAPI::Position northeastDefend;
	BWAPI::Position northeastAttack;

	BWAPI::Position southeastChokePointMid;
	BWAPI::Position southeastChokePointTop;
	BWAPI::Position southeastChokePointBot;
	BWAPI::Position southeastChokePointLeft;
	BWAPI::Position southeastChokePointRight;
	BWAPI::Position southeastExpand;
	BWAPI::Position southeastDefend;
	BWAPI::Position southeastAttack;
};
