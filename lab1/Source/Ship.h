#pragma once
#include "Actor.h"
#include "MoveComponent.h"

class Ship : public Actor
{
	DECL_ACTOR(Ship, Actor);
public:
	Ship(Game& mGame);
	MoveComponentPtr GetMoveComponent() { return moveShip; };
private:
	MoveComponentPtr moveShip;
};
DECL_PTR(Ship);