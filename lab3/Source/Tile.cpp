#include "Tile.h"
#include "Game.h"
#include "SphereCollision.h"

IMPL_ACTOR(Tile, Actor);

Tile::Tile(Game& game)
	:Actor(game)
	,mState(Default)
	,mIsOnPath(false)
{
	mMesh = MeshComponent::Create(*this);
	auto mesh = mGame.GetAssetCache().Load<Mesh>("Meshes/Tile.itpmesh2");
	mMesh->SetMesh(mesh);
}

void Tile::SetState(State state)
{
	mState = state;
	int value = static_cast<int>(mState);
	if (mIsOnPath)
	{
		value += 4;
	}
	mMesh->SetTextureIndex(value);
}


void Tile::SetOnPath(bool value)
{
	mIsOnPath = value;
	SetState(mState);
}

void Tile::AddRedSphereCol()
{
	SphereCollisionPtr redTileCol = SphereCollision::Create(*this);
	auto mesh = mGame.GetAssetCache().Load<Mesh>("Meshes/Tile.itpmesh2");
	redTileCol->RadiusFromMesh(mesh);
	redTileCol->SetScale(0.3f);
}
