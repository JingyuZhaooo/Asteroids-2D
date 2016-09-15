#pragma once
#include "Actor.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"

class Ship : public Actor
{
	DECL_ACTOR(Ship, Actor);
public:
	Ship(Game& mGame);
	MoveComponentPtr GetMoveComponent() { return moveShip; };
	void Tick(float deltaTime) override;
	void FireMissle();
private:
	MoveComponentPtr moveShip;
	TexturePtr noThrust;
	TexturePtr withThrust;
	SpriteComponentPtr texture;
};
DECL_PTR(Ship);