#include "Asteroid.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "Random.h"
#include "MoveComponent.h"
#include "SphereCollision.h"

IMPL_ACTOR(Asteroid, Actor);
Asteroid::Asteroid(Game& mGame) : Actor(mGame) // Initializer list
{
	auto asteroid = SpriteComponent::Create(*this);
	AssetCache& mAssetCache = mGame.GetAssetCache();
	auto texture = mAssetCache.Load<Texture>("Textures/Asteroid.png");
	asteroid->SetTexture(texture);

	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	auto move = MoveComponent::Create(*this, Component::PreTick);
	move->SetLinearSpeed(150.0f);
	move->SetLinearAxis(1.0f);

	auto coll = SphereCollision::Create(*this);
	coll->RadiusFromTexture(texture);
	coll->SetScale(0.9f);
}