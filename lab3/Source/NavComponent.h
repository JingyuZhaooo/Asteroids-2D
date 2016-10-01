#pragma once
#include "MoveComponent.h"
#include "PathNode.h"

class NavComponent : public MoveComponent
{
	DECL_COMPONENT(NavComponent, MoveComponent);
public:
	NavComponent(Actor& owner);
	void FollowPath(PathNode* currNode);
	void Tick(float deltaTime);
private:
	PathNode* mStart;
};
DECL_PTR(NavComponent);
