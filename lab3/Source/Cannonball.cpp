#include "Cannonball.h"
#include "Game.h"

IMPL_ACTOR(Cannonball, Actor);

Cannonball::Cannonball(Game& mGame) : Actor(mGame)
{
	mMeshComp = MeshComponent::Create(*this);
	AssetCache& mAssetCache = mGame.GetAssetCache();
	MeshPtr mMesh = mAssetCache.Load<Mesh>("Meshes/Cannonball.itpmesh2");
	mMeshComp->SetMesh(mMesh);

	mMoveComp = MoveComponent::Create(*this, Component::PreTick);
	mMoveComp->SetLinearSpeed(300.0f);
	mMoveComp->SetLinearAxis(1.0f);
	
	mSphereCol = SphereCollision::Create(*this);
	mSphereCol->RadiusFromMesh(mMesh);
	mSphereCol->SetScale(1.0f);

	TimerHandle CannonballTimerHandle;
	mGame.GetGameTimers().SetTimer(CannonballTimerHandle, this, &Cannonball::DieOnTimer, 3.0f); // Automatically despawn after 3 seconds
}

void Cannonball::DieOnTimer()
{
	SetIsAlive(false);
}
