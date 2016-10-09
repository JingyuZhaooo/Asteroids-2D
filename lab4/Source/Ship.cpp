#include "Ship.h"
#include "Game.h"
#include "Random.h"
#include "Component.h"
#include "Sound.h"
#include "GameTimers.h"
#include "Asteroid.h"
#include "GameTimers.h"


IMPL_ACTOR(Ship, Actor);
Ship::Ship(Game& mGame) : Actor(mGame) // Initializer list
{
	texture = MeshComponent::Create(*this);
	AssetCache& mAssetCache = mGame.GetAssetCache();

	audioComPtr = AudioComponent::Create(*this);
	fireSound = mAssetCache.Load<Sound>("Sounds/Laser.wav");
	engineSound = mAssetCache.Load<Sound>("Sounds/ShipEngine.wav");
	mShipDie = mAssetCache.Load<Sound>("Sounds/ShipDie.wav");
	soundCue = audioComPtr->PlaySound(engineSound, 1);
	soundCue.Pause();
	mMesh = mAssetCache.Load<Mesh>("Meshes/PlayerShip.itpmesh2");
	texture->SetMesh(mMesh);
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	moveShip = InputComponent::Create(*this, Component::PreTick);
	moveShip->SetLinearSpeed(400.0f);
	moveShip->SetAngularSpeed(Math::Pi);
	this->SetScale(1.0f);
	mCamComp = CameraComponent::Create(*this);
	mCamComp->SetMoveComp(moveShip);
}
void Ship::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	if (moveShip->GetLinearAxis() == 0)
	{
		soundCue.Pause();
	}
	else
	{
		soundCue.Resume();
	}
	return;
}

void Ship::BeginPlay()
{
	//mCamComp->Initialize();
	moveShip->BindLinearAxis("Move");
	moveShip->BindAngularAxis("Rotate");
}

void Ship::OnRespawnShip()
{
	this->SetIsPaused(false);
	texture->SetIsVisible(true);
	soundCue.Resume();
	this->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	this->SetRotation(Math::PiOver2);
}