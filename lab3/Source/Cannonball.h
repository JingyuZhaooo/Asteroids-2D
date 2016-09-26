#pragma once
#include "Actor.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "SphereCollision.h"

class Cannonball : public Actor
{
	DECL_ACTOR(Cannonball, Actor);
public:
	Cannonball(Game& mGame);
	void DieOnTimer();
private:
	MeshComponentPtr mMeshComp;
	MoveComponentPtr mMoveComp;
	SphereCollisionPtr mSphereCol;
};
DECL_PTR(Cannonball);