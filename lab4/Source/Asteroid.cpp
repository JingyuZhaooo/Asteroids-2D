#include "Asteroid.h"
#include "Game.h"
#include "SpriteComponent.h"
#include "Random.h"
#include "MoveComponent.h"
#include "SphereCollision.h"
#include "MeshComponent.h"

IMPL_ACTOR(Asteroid, Actor);
Asteroid::Asteroid(Game& mGame) : Actor(mGame) // Initializer list
{
	MeshComponentPtr asteroid = MeshComponent::Create(*this);
	AssetCache& mAssetCache = mGame.GetAssetCache();
	MeshPtr texture = mAssetCache.Load<Mesh>("Meshes/AsteroidMesh.itpmesh2");
	asteroid->SetMesh(texture);

	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	auto move = MoveComponent::Create(*this, Component::PreTick);
	move->SetLinearSpeed(150.0f);
	move->SetLinearAxis(1.0f);
	asteroid->SetIsVisible(true);
}