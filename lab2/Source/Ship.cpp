#include "Ship.h"
#include "Game.h"
#include "Random.h"
#include "Laser.h"
#include "Component.h"

IMPL_ACTOR(Ship, Actor);
Ship::Ship(Game& mGame) : Actor(mGame) // Initializer list
{
	texture = SpriteComponent::Create(*this);
	AssetCache& mAssetCache = mGame.GetAssetCache();
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
	}
	else
	{
		texture->SetTexture(withThrust);
	}
	return;
}
void Ship::FireMissle()
{
	auto mLaser = Laser::Spawn(mGame);
	
	mLaser->SetPosition(GetPosition());
	mLaser->SetRotation(GetRotation());
}