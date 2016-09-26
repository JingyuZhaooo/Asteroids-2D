#pragma once
#include "Tower.h"
#include "MeshComponent.h"
#include "AudioComponent.h"

class CannonTower : public Tower
{
	DECL_ACTOR(CannonTower, Actor);
public:
	CannonTower(Game& mGame);
	void FireCannon();
private:
	MeshComponentPtr mMeshComp;
	SoundPtr mFireSound;
	AudioComponentPtr mAudioComp;
};
DECL_PTR(CannonTower);