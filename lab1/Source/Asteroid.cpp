#include "Asteroid.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "Random.h"

IMPL_ACTOR(Asteroid, Actor);
Asteroid::Asteroid(Game& mGame) : Actor(mGame) // Initializer list
{
	auto asteroid = SpriteComponent::Create(*this);
	AssetCache& mAssetCache = mGame.GetAssetCache();
	auto texture = mAssetCache.Load<Texture>("Textures/Asteroid.png");
	asteroid->SetTexture(texture);

	//render.DrawSprite(mTexture, actualWorld);

	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));
}