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
	TowerPtr GetCannonChild() { return mCannonChild; };
private:
	SoundPtr mFireSound;
	AudioComponentPtr mAudioComp;
	TowerPtr mCannonChild;
};
DECL_PTR(CannonTower);