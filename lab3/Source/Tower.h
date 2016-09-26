#pragma once
#include "Actor.h"
#include "MeshComponent.h"
#include "AudioComponent.h"

class Tower : public Actor
{
	DECL_ACTOR(Tower, Actor);
public:
	Tower(Game& mGame);
private:
	MeshComponentPtr mMeshComp;
	SoundPtr mTowerBuiltSound;
	AudioComponentPtr mAudioComp;
};
DECL_PTR(Tower);