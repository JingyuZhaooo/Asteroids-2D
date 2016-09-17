#include "Ship.h"
#include "Game.h"
#include "Random.h"
#include "Laser.h"
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
	moveShip->SetAngularSpeed(Math::TwoPi);
	this->SetScale(0.5f);

	auto coll = SphereCollision::Create(*this);
	coll->RadiusFromMesh(mMesh);
	coll->SetScale(0.75f);
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
void Ship::FireMissle()
{
	if (this->GetIsPaused() != true)
	{
		auto mLaser = Laser::Spawn(mGame);
		audioComPtr->PlaySound(fireSound);
		mLaser->SetPosition(GetPosition());
		mLaser->SetRotation(GetRotation());
	}
}

void Ship::BeginPlay()
{
	mGame.GetInput().BindAction("Fire", IE_Pressed, this, &Ship::FireMissle);
	moveShip->BindLinearAxis("Move");
	moveShip->BindAngularAxis("Rotate");
}

void Ship::BeginTouch(Actor& other)
{
	Super::BeginTouch(other);
	if (this->GetIsPaused() == false && IsA<Asteroid>(other))
	{
		mShipDieSound->PlaySound(mShipDie);
		this->SetIsPaused(true);
		texture->SetIsVisible(false);
		soundCue.Pause();
		TimerHandle handle;
		mGame.GetGameTimers().SetTimer(handle, this, &Ship::OnRespawnShip, 1.0f);
	}
}

void Ship::OnRespawnShip()
{
	this->SetIsPaused(false);
	texture->SetIsVisible(true);
	soundCue.Resume();
	this->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	this->SetRotation(Math::PiOver2);
}