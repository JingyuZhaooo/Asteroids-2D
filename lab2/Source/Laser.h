#pragma once
#include "SpriteComponent.h"
#include "Actor.h"
#include "MoveComponent.h"
#include "AudioComponent.h"

class Laser : public Actor
{
	DECL_ACTOR(Laser, Actor);
public:
	Laser(Game& mGame);
	MoveComponentPtr getLaser();
	void Tick(float deltatime) override;
	void BeginTouch(Actor& other) override;
	void OnDieTimer();
	void BeginPlay() override;
private:
	SpriteComponentPtr LaserTexture;
	MoveComponentPtr moveLaser;
	SoundPtr asteroidDie;
	AudioComponentPtr collisionSound;
	
};
DECL_PTR(Laser);