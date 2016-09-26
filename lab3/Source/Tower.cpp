#include "Tower.h"
#include "Game.h"

IMPL_ACTOR(Tower, Actor);

Tower::Tower(Game& mGame) : Actor(mGame)
{
	mMeshComp = MeshComponent::Create(*this);
	AssetCache& mAssetCache = mGame.GetAssetCache();
	MeshPtr mMesh = mAssetCache.Load<Mesh>("Meshes/TowerBase.itpmesh2");
	mMeshComp->SetMesh(mMesh);
	mTowerBuiltSound = mAssetCache.Load<Sound>("Sounds/Building.wav");
	mAudioComp->PlaySound(mTowerBuiltSound);
}
