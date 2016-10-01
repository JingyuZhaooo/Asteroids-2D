#include "NavWorld.h"
#include "Math.h"
#include "Tile.h"
#include <iostream>

NavWorld::NavWorld()
{
	mStartNode = &mPathNodes[4][0];
	mEndNode = &mPathNodes[4][17];
}

NavWorld::~NavWorld()
{
}

PathNode& NavWorld::GetNode(int row, int column)
{
	return mPathNodes[row][column];
}

bool NavWorld::TryFindPath()
{
	mClosedSet.clear();
	mOpenSet.clear();
	PathNode* startNode = &mPathNodes[4][0];
	PathNode * endNode = &mPathNodes[4][17];
	
	for (int i = 0; i < 9; i++)		// set all Tiles to false
	{
		for (int j = 0; j < 18; j++)
		{
			mPathNodes[i][j].mTile->SetOnPath(false);
		}
	}
	PathNode* currentNode = endNode; // doing A* search in reverse
	mClosedSet.insert(currentNode);	// add currentNode to closedSet
	do
	{
		for (auto n : currentNode->mAdjacent)	//for each Node i adjacent to currentNode
		{
			if (mClosedSet.find(n) != mClosedSet.end())
			{
				continue;
			}
			else if (mOpenSet.find(n) != mOpenSet.end()) // check for adoption
			{
				float newG = currentNode->g + 1.0f;
				if (newG < n->g)
				{
					n->mParent = currentNode;
					n->g = newG;
					n->f = n->g + n->h;
				}
			}
			else if(n->blocked == false)
			
			{
				n->mParent = currentNode;
				n->h = fabs(n->mGridPos.x - endNode->mGridPos.x) + fabs(n->mGridPos.y - endNode->mGridPos.y);
				n->g = n->mParent->g + 1.0f;
				n->f = n->g + n->h;
				mOpenSet.insert(n);
				
			}
		}
		if (mOpenSet.empty())
		{
			return false;
		}
		float roof = 1000; // f value must be less than 1000
		for (auto i : mOpenSet)
		{
			if (i->f < roof)
			{
				roof = i->f;
				currentNode = i;
			}
		}
		mOpenSet.erase(currentNode);
		mClosedSet.insert(currentNode);
	} while (currentNode != startNode);
	// print all the x in the middle of the tiles
		PathNode* tempNode = startNode;
		while (tempNode != nullptr)
		{
			tempNode->mTile->SetOnPath(true);
			tempNode = tempNode->mParent;
		}
		return true;
}
