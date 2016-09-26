#include "CannonTower.h"
#include "Game.h"
#include "Cannonball.h"

IMPL_ACTOR(CannonTower, Tower);

CannonTower::CannonTower(Game& mGame) : Tower(mGame)
{
	mMeshComp = MeshComponent::Create(*this);
	AssetCache& mAssetCache = mGame.GetAssetCache();
	MeshPtr mMesh = mAssetCache.Load<Mesh>("Meshes/Cannon.itpmesh2");
	mMeshComp->SetMesh(mMesh);
	mFireSound = mAssetCache.Load<Sound>("Sounds/CannonFire.wav");
}

void CannonTower::FireCannon()
{
	auto target = mGame.GetWorld().GetClosestEnemy(mParent->GetWorldTransform().GetTranslation(), 150.0f);
	if (target != nullptr) //Enemy comes into range
	{
		Vector3 aim = target->GetWorldTransform().GetTranslation() - mParent->GetWorldTransform().GetTranslation(); //Make a vector from the cannon to the target
		aim.Normalize();												//normalize the vector
		auto angle = atan(Dot(aim, Vector3::UnitX)) - Math::PiOver2; // ???
		auto crossProduct = Cross(aim, Vector3::UnitX);
		if (crossProduct.z < 0)
		{
			angle *= -1;
		}
		this->SetRotation(angle);
		
		CannonballPtr cannonBall = Cannonball::Spawn(mGame);
		cannonBall->SetPosition(mParent->GetWorldTransform().GetTranslation());
		cannonBall->SetRotation(angle);
		mAudioComp->PlaySound(mFireSound);

	}
	
	TimerHandle CannonTimeHandle;
	mGame.GetGameTimers().SetTimer(CannonTimeHandle, this, &CannonTower::FireCannon, 1.0f);
}
