#include "Ship.h"
#include "Game.h"
#include "Random.h"
#include "Laser.h"
#include "Component.h"
#include "Sound.h"

IMPL_ACTOR(Ship, Actor);
Ship::Ship(Game& mGame) : Actor(mGame) // Initializer list
{
	texture = SpriteComponent::Create(*this);
	AssetCache& mAssetCache = mGame.GetAssetCache();

	audioComPtr = AudioComponent::Create(*this);
	fireSound = mAssetCache.Load<Sound>("Sounds/Laser.wav");
	engineSound = mAssetCache.Load<Sound>("Sounds/ShipEngine.wav");
	soundCue = audioComPtr->PlaySound(engineSound, 1);
	soundCue.Pause();

	noThrust = mAssetCache.Load<Texture>("Textures/Spaceship.png");
	withThrust = mAssetCache.Load<Texture>("Textures/SpaceshipWithThrust.png");
	texture->SetTexture(noThrust);

	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	moveShip = MoveComponent::Create(*this, Component::PreTick);
	moveShip->SetLinearSpeed(400.0f);
	
	moveShip->SetAngularSpeed(Math::TwoPi);
	
}
void Ship::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
	if (moveShip->GetLinearAxis() == 0)
	{
		texture->SetTexture(noThrust);
		soundCue.Pause();
	}
	else
	{
		texture->SetTexture(withThrust);
		soundCue.Resume();
	}
	return;
}
void Ship::FireMissle()
{
	auto mLaser = Laser::Spawn(mGame);
	audioComPtr->PlaySound(fireSound);
	mLaser->SetPosition(GetPosition());
	mLaser->SetRotation(GetRotation());
}