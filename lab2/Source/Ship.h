#pragma once
#include "Actor.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "AudioComponent.h"
#include "Sound.h"

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
	AudioComponentPtr audioComPtr;
	SoundPtr fireSound;
	SoundPtr engineSound;
	SoundCue soundCue;
};
DECL_PTR(Ship);