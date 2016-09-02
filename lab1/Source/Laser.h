#pragma once
#include "SpriteComponent.h"
#include "Actor.h"
#include "MoveComponent.h"

class Laser : public Actor
{
	DECL_ACTOR(Laser, Actor);
public:
	Laser(Game& mGame);
	MoveComponentPtr getLaser();
	void Tick(float deltatime) override;
private:
	SpriteComponentPtr LaserTexture;
	MoveComponentPtr moveLaser;
	float lifeSpan;
};
DECL_PTR(Laser);