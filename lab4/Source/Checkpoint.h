#pragma once
#include "Actor.h"
#include "CollisionComponent.h"
#include "Mesh.h"
#include "MeshComponent.h"

class Checkpoint : public Actor
{
	DECL_ACTOR(Checkpoint, Actor);
public:
	Checkpoint(Game& mGame);

private:
	MeshPtr mMesh;
	MeshComponentPtr texture;
};
DECL_PTR(Checkpoint)