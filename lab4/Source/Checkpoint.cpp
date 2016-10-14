#include "Checkpoint.h"
#include "Game.h"

IMPL_ACTOR(Checkpoint, Actor);

Checkpoint::Checkpoint(Game & mGame) : Actor(mGame)
{
	//Set up the mesh
	texture = MeshComponent::Create(*this);
	AssetCache& mAssetCache = mGame.GetAssetCache();
	mMesh = mAssetCache.Load<Mesh>("Meshes/Checkpoint.itpmesh2");
	texture->SetMesh(mMesh);

	// Set up the SphereCollision
	auto coll = SphereCollision::Create(*this);
	coll->RadiusFromMesh(mMesh);
	coll->SetScale(0.75f);
}
