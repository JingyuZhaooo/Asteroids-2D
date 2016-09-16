#pragma once
#include "Actor.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "AudioComponent.h"
#include "Sound.h"
#include "InputComponent.h"
#include "SphereCollision.h"

class Ship : public Actor
{
	DECL_ACTOR(Ship, Actor);
public:
	Ship(Game& mGame);
	MoveComponentPtr GetMoveComponent() { return moveShip; };
	void Tick(float deltaTime) override;
	void FireMissle();
	void BeginPlay() override;
	void BeginTouch(Actor& other) override;
	void OnRespawnShip();
private:
	InputComponentPtr moveShip;
	TexturePtr noThrust;
	TexturePtr withThrust;
	SpriteComponentPtr texture;
	AudioComponentPtr audioComPtr;
	SoundPtr fireSound;
	SoundPtr engineSound;
	SoundCue soundCue;
	SoundPtr mShipDie;
	AudioComponentPtr mShipDieSound;
};
DECL_PTR(Ship);