#include "Laser.h"
#include "Game.h"
#include "SpriteComponent.h"

IMPL_ACTOR(Laser, Actor);

Laser::Laser(Game& mGame) : Actor(mGame) // Initializer list
{
	LaserTexture = SpriteComponent::Create(*this);
	AssetCache& mAssetCache = mGame.GetAssetCache();
	LaserTexture->SetTexture(mAssetCache.Load<Texture>("Textures/Laser.png"));

	moveLaser = MoveComponent::Create(*this, Component::PreTick);
	moveLaser->SetLinearSpeed(600.0f);
	moveLaser->SetLinearAxis(1.0f);
	lifeSpan = 1.0f;
}
MoveComponentPtr Laser::getLaser()
{
	return moveLaser;

}
void Laser::Tick(float deltaTime)
{
	lifeSpan -= deltaTime;
	if (lifeSpan <= 0.0f)
	{
		SetIsAlive(false);
	}
}