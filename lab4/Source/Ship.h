#pragma once
#include "Actor.h"
#include "MoveComponent.h"
#include "SpriteComponent.h"
#include "AudioComponent.h"
#include "Sound.h"
#include "InputComponent.h"
#include "SphereCollision.h"
#include "MeshComponent.h"
#include "CameraComponent.h"

class Ship : public Actor
{
	DECL_ACTOR(Ship, Actor);
public:
	Ship(Game& mGame);
	MoveComponentPtr GetMoveComponent() { return moveShip; };
	void Tick(float deltaTime) override;
	void BeginPlay() override;
	void OnRespawnShip();
	void Recenter();
private:
	InputComponentPtr moveShip;
	MeshPtr mMesh;
	MeshComponentPtr texture;
	AudioComponentPtr audioComPtr;
	SoundPtr fireSound;
	SoundPtr engineSound;
	SoundCue soundCue;
	SoundPtr mShipDie;
	AudioComponentPtr mShipDieSound;
	CameraComponentPtr mCamComp;
};
DECL_PTR(Ship);