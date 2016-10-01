#pragma once
#include "Actor.h"
#include "MeshComponent.h"
#include "MoveComponent.h"
#include "SphereCollision.h"
#include "AudioComponent.h"
#include "Sound.h"
#include "NavComponent.h"

class Enemy : public Actor
{
	DECL_ACTOR(Enemy, Actor);
public:
	Enemy(Game& mGame);
	void Tick(float deltaTime) override;
	void BeginPlay() override;
	void EndPlay() override;
	void BeginTouch(Actor& other) override;
	void Slow();
	void Unslow();
private:
	MeshComponentPtr mMeshComp;
	MoveComponentPtr mMoveComp;
	SphereCollisionPtr mSphereCol;
	int mGotHit;
	SoundPtr mDieSound;
	AudioComponentPtr mAudioComp;
	NavComponentPtr mNavComp;
};
DECL_PTR(Enemy);