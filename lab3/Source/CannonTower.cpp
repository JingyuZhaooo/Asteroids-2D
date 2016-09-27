#include "CannonTower.h"
#include "Game.h"
#include "Cannonball.h"

IMPL_ACTOR(CannonTower, Tower);

CannonTower::CannonTower(Game& mGame) : Tower(mGame)
{
	AssetCache& mAssetCache = mGame.GetAssetCache();
	mFireSound = mAssetCache.Load<Sound>("Sounds/CannonFire.wav");
	mCannonChild = Tower::SpawnAttached(*this);	// make an actor that encapsulates the cannon mesh
	mCannonChild->LoadCannonMesh();
}

void CannonTower::FireCannon()
{
	auto target = mGame.GetWorld().GetClosestEnemy(mParent->GetWorldTransform().GetTranslation(), 150.0f);
	if (target != nullptr) //Enemy comes into range
	{
		Vector3 aim = target->GetWorldTransform().GetTranslation() - mParent->GetWorldTransform().GetTranslation(); //Make a vector from the cannon to the target
		aim.Normalize();												//normalize the vector
		auto angle = acos(Dot(aim, Vector3::UnitX)); 
		auto crossProduct = Cross(Vector3::UnitX, aim);
		if (crossProduct.z < 0)
		{
			angle *= -1;
		}
		this->GetCannonChild()->SetRotation(angle);
		
		CannonballPtr cannonBall = Cannonball::Spawn(mGame);
		cannonBall->SetPosition(mParent->GetWorldTransform().GetTranslation());
		cannonBall->SetRotation(angle);
		mAudioComp->PlaySound(mFireSound);

	}
	
	TimerHandle CannonTimeHandle;
	mGame.GetGameTimers().SetTimer(CannonTimeHandle, this, &CannonTower::FireCannon, 1.0f);
}
