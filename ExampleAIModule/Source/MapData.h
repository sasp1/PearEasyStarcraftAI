#pragma once
#include <BWAPI.h>
class GatheringManager
{
public:
	BWAPI::Position northwestChokePointMid = BWAPI::Position(564,927);
	BWAPI::Position northwestChokePointTop = BWAPI::Position(584, 874);
	BWAPI::Position northwestChokePointBot = BWAPI::Position(551, 973);
	BWAPI::Position northwestChokePointLeft = BWAPI::Position(467, 938);
	BWAPI::Position northwestChokePointRight = BWAPI::Position(659, 916);
	BWAPI::Position northwestExpand = BWAPI::Position(680, 668);

	BWAPI::Position southhwestChokePointMid = BWAPI::Position(573, 3136);
	BWAPI::Position southwestChokePointTop = BWAPI::Position(558, 3097);
	BWAPI::Position southwestChokePointBot = BWAPI::Position(575, 3206);
	BWAPI::Position southwestChokePointLeft = BWAPI::Position(465, 3124);
	BWAPI::Position southwestChokePointRight = BWAPI::Position(655, 3177);
	BWAPI::Position southwestExpand = BWAPI::Position(669, 3356);

	BWAPI::Position northeastChokePointMid = BWAPI::Position(3531, 924);
	BWAPI::Position northeastChokePointTop = BWAPI::Position(3511, 858);
	BWAPI::Position northeastChokePointBot = BWAPI::Position(3538, 965);
	BWAPI::Position northeastChokePointLeft = BWAPI::Position(3434, 916);
	BWAPI::Position northeastChokePointRight = BWAPI::Position(3614, 942);
	BWAPI::Position northeastExpand = BWAPI::Position(3293, 679);

	BWAPI::Position southeastChokePointMid = BWAPI::Position(3523, 3147);
	BWAPI::Position southeastChokePointTop = BWAPI::Position(3536, 3088);
	BWAPI::Position southeastChokePointBot = BWAPI::Position(3527, 3213);
	BWAPI::Position southeastChokePointLeft = BWAPI::Position(3442, 3178);
	BWAPI::Position southeastChokePointRight = BWAPI::Position(3631, 3123);
	BWAPI::Position southeastExpand = BWAPI::Position(3290, 3355);

};
