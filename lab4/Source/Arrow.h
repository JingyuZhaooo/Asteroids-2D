#pragma once
#include "Actor.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Math.h"


class Arrow : public Actor
{
	DECL_ACTOR(Arrow, Actor);
public:
	Arrow(Game& mGame);
	void SetPlayer(ActorPtr& player) { mPlayer = player; };
	void SetCheckpointLoc(Vector3& location) { mCheckpointLocation = location; };
	void UpdateWorldPosition();
	void Tick(float deltaTime) override;
	void BeginPlay() override;
private:
	MeshPtr mMesh;
	MeshComponentPtr texture;
	ActorPtr mPlayer;
	Vector3 mCheckpointLocation;
};
DECL_PTR(Arrow);