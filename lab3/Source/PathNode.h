#pragma once
#include <vector>
#include "Tile.h"


struct PathNode
{
	std::vector<PathNode*> mAdjacent;
	TilePtr mTile;
	Vector2 mGridPos;
	PathNode* mParent;
	float f;
	float g;
	float h;
	bool blocked;
};