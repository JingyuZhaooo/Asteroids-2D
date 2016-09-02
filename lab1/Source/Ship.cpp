#include "Ship.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "Random.h"


IMPL_ACTOR(Ship, Actor);
Ship::Ship(Game& mGame) : Actor(mGame) // Initializer list
{
	auto ship = SpriteComponent::Create(*this);
	AssetCache& mAssetCache = mGame.GetAssetCache();
	auto texture = mAssetCache.Load<Texture>("Textures/Spaceship.png");
	ship->SetTexture(texture);

	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	moveShip = MoveComponent::Create(*this, Component::PreTick);
	moveShip->SetLinearSpeed(400.0f);
	
}