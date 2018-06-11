#include "MapData.h"
#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;

MapData::MapData()
{
	northwestChokePointMid = BWAPI::Position(564, 927);
	northwestChokePointTop = BWAPI::Position(584, 874);
	northwestChokePointBot = BWAPI::Position(551, 973);
	northwestChokePointLeft = BWAPI::Position(467, 938);
	northwestChokePointRight = BWAPI::Position(659, 916);
	northwestExpand = BWAPI::Position(680, 668);
	northwestDefend = BWAPI::Position(398, 1017);
	northwestAttack = BWAPI::Position(764, 814);
	northwestMinePosition = BWAPI::Position(150, 825);
	northwestSimCityTilePositionBarracks = BWAPI::TilePosition(24, 31);
	northwestSimCityTilePositionSupplyDepots1 = BWAPI::TilePosition(27, 29);
	northwestSimCityTilePositionSupplyDepots2 = BWAPI::TilePosition(29, 27);

	southwestChokePointMid = BWAPI::Position(573, 3136);
	southwestChokePointTop = BWAPI::Position(558, 3097);
	southwestChokePointBot = BWAPI::Position(575, 3206);
	southwestChokePointLeft = BWAPI::Position(465, 3124);
	southwestChokePointRight = BWAPI::Position(655, 3177);
	southwestExpand = BWAPI::Position(669, 3356);
	southwestDefend = BWAPI::Position(420, 3019);
	southwestAttack = BWAPI::Position(717, 3250);
	southwestMinePosition = BWAPI::Position(150, 3300);
	southwestSimCityTilePositionBarracks = BWAPI::TilePosition(28, 99);
	southwestSimCityTilePositionSupplyDepots1 = BWAPI::TilePosition(26, 97);
	southwestSimCityTilePositionSupplyDepots2 = BWAPI::TilePosition(24, 95);


	northeastChokePointMid = BWAPI::Position(3531, 924);
	northeastChokePointTop = BWAPI::Position(3511, 858);
	northeastChokePointBot = BWAPI::Position(3538, 965);
	northeastChokePointLeft = BWAPI::Position(3434, 916);
	northeastChokePointRight = BWAPI::Position(3614, 942);
	northeastExpand = BWAPI::Position(3293, 679);
	northeastDefend = BWAPI::Position(3670, 1010);
	northeastAttack = BWAPI::Position(3335, 809);
	northeastMinePosition = BWAPI::Position(3900, 825);
	northeastSimCityTilePositionBarracks = BWAPI::TilePosition(102, 25);
	northeastSimCityTilePositionSupplyDepots1 = BWAPI::TilePosition(105, 24);
	northeastSimCityTilePositionSupplyDepots2 = BWAPI::TilePosition(107, 22);


	southeastChokePointMid = BWAPI::Position(3523, 3147);
	southeastChokePointTop = BWAPI::Position(3536, 3088);
	southeastChokePointBot = BWAPI::Position(3527, 3213);
	southeastChokePointLeft = BWAPI::Position(3442, 3178);
	southeastChokePointRight = BWAPI::Position(3631, 3123);
	southeastExpand = BWAPI::Position(3290, 3355);
	southeastDefend = BWAPI::Position(3659, 3035);
	southeastAttack = BWAPI::Position(3355, 3272);
	southeastMinePosition = BWAPI::Position(3900, 3300);
	southeastSimCityTilePositionBarracks = BWAPI::TilePosition(96, 99);
	southeastSimCityTilePositionSupplyDepots1 = BWAPI::TilePosition(99, 97);
	southeastSimCityTilePositionSupplyDepots2 = BWAPI::TilePosition(101, 95);

}

MapData::~MapData()
{
}
