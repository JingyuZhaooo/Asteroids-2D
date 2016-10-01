#pragma once
#include "PathNode.h"


class NavWorld
{
public:
	NavWorld();
	~NavWorld();
	PathNode& GetNode(int row, int column);
	bool TryFindPath();
	PathNode* GetStartNode() { return mStartNode; };
private:
	PathNode mPathNodes[9][18]; // 2D array of the PathNodes
	PathNode* mStartNode; //Spawn Spot
	PathNode* mEndNode; // Base Location
	std::unordered_set<PathNode*> mOpenSet;
	std::unordered_set<PathNode*> mClosedSet;
};