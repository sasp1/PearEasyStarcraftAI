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
	BWAPI::Position northwestMinePosition;
	BWAPI::TilePosition northwestSimCityTilePositionBarracks;
	BWAPI::TilePosition northwestSimCityTilePositionSupplyDepots1;
	BWAPI::TilePosition northwestSimCityTilePositionSupplyDepots2;

	BWAPI::Position southwestChokePointMid;
	BWAPI::Position southwestChokePointTop;
	BWAPI::Position southwestChokePointBot;
	BWAPI::Position southwestChokePointLeft;
	BWAPI::Position southwestChokePointRight;
	BWAPI::Position southwestExpand;
	BWAPI::Position southwestDefend;
	BWAPI::Position southwestAttack;
	BWAPI::Position southwestMinePosition;
	BWAPI::TilePosition southwestSimCityTilePositionBarracks;
	BWAPI::TilePosition southwestSimCityTilePositionSupplyDepots1;
	BWAPI::TilePosition southwestSimCityTilePositionSupplyDepots2;
	
	BWAPI::Position northeastChokePointMid;
	BWAPI::Position northeastChokePointTop;
	BWAPI::Position northeastChokePointBot;
	BWAPI::Position northeastChokePointLeft;
	BWAPI::Position northeastChokePointRight;
	BWAPI::Position northeastExpand;
	BWAPI::Position northeastDefend;
	BWAPI::Position northeastAttack;
	BWAPI::Position northeastMinePosition; 
	BWAPI::TilePosition northeastSimCityTilePositionBarracks;
	BWAPI::TilePosition northeastSimCityTilePositionSupplyDepots1;
	BWAPI::TilePosition northeastSimCityTilePositionSupplyDepots2;

	BWAPI::Position southeastChokePointMid;
	BWAPI::Position southeastChokePointTop;
	BWAPI::Position southeastChokePointBot;
	BWAPI::Position southeastChokePointLeft;
	BWAPI::Position southeastChokePointRight;
	BWAPI::Position southeastExpand;
	BWAPI::Position southeastDefend;
	BWAPI::Position southeastAttack;
	BWAPI::Position southeastMinePosition;
	BWAPI::TilePosition southeastSimCityTilePositionBarracks;
	BWAPI::TilePosition southeastSimCityTilePositionSupplyDepots1;
	BWAPI::TilePosition southeastSimCityTilePositionSupplyDepots2;

};
