#pragma once
#include "Actor.h"

class Asteroid : public Actor 
{
	DECL_ACTOR(Asteroid, Actor);
public:
	Asteroid(Game& mGame);
	
};
DECL_PTR(Asteroid);