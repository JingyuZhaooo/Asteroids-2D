#include "Ship.h"
#include "Game.h"
#include "Random.h"
#include "Component.h"
#include "Sound.h"
#include "GameTimers.h"
#include "Asteroid.h"
#include "Checkpoint.h"
#include "GameMode.h"

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
	SetRotation(Quaternion(this->GetWorldTransform().GetZAxis(), Math::PiOver2));

	moveShip = InputComponent::Create(*this, Component::PreTick);
	moveShip->SetLinearSpeed(400.0f);
	moveShip->SetYawSpeed(Math::Pi);
	moveShip->SetPitchSpeed(Math::Pi);
	this->SetScale(1.0f);
	mCamComp = CameraComponent::Create(*this);
	mCamComp->SetMoveComp(moveShip);

	auto coll = SphereCollision::Create(*this);
	coll->RadiusFromMesh(mMesh);
	coll->SetScale(0.75f);
	// Load the Collecting sound
	mCollectSound = mAssetCache.Load<Sound>("Sounds/Checkpoint.wav");
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
	mGame.GetInput().BindAction("Recenter", IE_Pressed, this, &Ship::Recenter);
	moveShip->BindLinearAxis("Move");
	moveShip->BindYawAxis("Yaw");
	moveShip->BindPitchAxis("Pitch");
}

void Ship::OnRespawnShip()
{
	this->SetIsPaused(false);
	texture->SetIsVisible(true);
	soundCue.Resume();
	this->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	this->SetRotation(Quaternion(this->GetWorldTransform().GetZAxis(), Math::PiOver2));
}

void Ship::Recenter()
{
	this->SetRotation(Quaternion::Identity);
	mCamComp->Initialize();
}

void Ship::BeginTouch(Actor & other)
{
	Super::BeginTouch(other);
	if (IsA<Checkpoint>(other))
	{
		audioComPtr->PlaySound(mCollectSound); // play the collect sound
		mGame.GetGameMode()->CollectCheckpoint();
	}
}
