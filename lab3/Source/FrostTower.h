#pragma once
#include "Tower.h"
#include "MeshComponent.h"
#include "Sound.h"

class FrostTower : public Tower
{
	DECL_ACTOR(FrostTower, Tower);
public:
	FrostTower(Game& mGame);
	void Freeze();
private:
	MeshComponentPtr mMeshComp;
	SoundPtr mFreezeSound;
	AudioComponentPtr mAudioComp;
};
DECL_PTR(FrostTower);