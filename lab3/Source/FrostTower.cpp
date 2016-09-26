#include "FrostTower.h"
#include "Game.h"

IMPL_ACTOR(FrostTower, Tower);

FrostTower::FrostTower(Game& mGame) : Tower(mGame)
{
	mMeshComp = MeshComponent::Create(*this);
	AssetCache& mAssetCache = mGame.GetAssetCache();
	MeshPtr mMesh = mAssetCache.Load<Mesh>("Meshes/Frost.itpmesh2");
	mMeshComp->SetMesh(mMesh);
	mFreezeSound = mAssetCache.Load<Sound>("Sounds/Freeze.wav");
}

void FrostTower::Freeze()
{
	
	for (auto enemy : mGame.GetWorld().GetEnemiesInRange(mParent->GetWorldTransform().GetTranslation(), 150.0f))
	{
		enemy->Slow();
	}
	mAudioComp->PlaySound(mFreezeSound);
	TimerHandle enemyTimeHandle;
	mGame.GetGameTimers().SetTimer(enemyTimeHandle, this, &FrostTower::Freeze, 2.0f);

}
