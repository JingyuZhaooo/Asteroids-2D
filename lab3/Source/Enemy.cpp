#include "Enemy.h"
#include "Game.h"
#include "GameTimers.h"
#include "Cannonball.h"

IMPL_ACTOR(Enemy, Actor);
Enemy::Enemy(Game& mGame) : Actor(mGame)
{
	mMeshComp = MeshComponent::Create(*this);
	AssetCache& mAssetCache = mGame.GetAssetCache();
	MeshPtr mMesh = mAssetCache.Load<Mesh>("Meshes/Peasant.itpmesh2");
	mMeshComp->SetMesh(mMesh);

	mMoveComp = MoveComponent::Create(*this, Component::PreTick);
	mMoveComp->SetLinearSpeed(60.0f);
	mMoveComp->SetLinearAxis(1.0f);
	mMeshComp->SetIsVisible(true);
	auto coll = SphereCollision::Create(*this);
	coll->RadiusFromMesh(mMesh);
	coll->SetScale(0.3f);
	mGotHit = 0;
	mDieSound = mAssetCache.Load<Sound>("Sounds/WilhelmScream.wav");
	mNavComp = NavComponent::Create(*this, MoveComponent::PreTick);
}

void Enemy::Tick(float deltaTime)
{

}

void Enemy::BeginPlay()
{
	mGame.GetWorld().AddEnemy(this);
}

void Enemy::EndPlay()
{
	mGame.GetWorld().RemoveEnemy(this);
}

void Enemy::BeginTouch(Actor& other)
{
	Super::BeginTouch(other);
	if (IsAlive() == true && IsA<Tile>(other))
	{
		SetIsAlive(false);
		mGame.GetGameMode()->ReduceHP();
		if (mGame.GetGameMode()->GetHP() == 0)
		{
			std::string text = "You Lost!";
			mGame.GetGameMode()->GetHUD()->GetStatusMsg()->SetText(text, Color::LightPink);
			mGame.GetGameMode()->GetHUD()->GetStatusMsg()->SetIsVisible(true);
			mGame.SetGameEnd(true);
			for (auto i : mGame.GetWorld().GetAllEnemies())
			{
				i->GetMoveComp()->SetLinearAxis(0.0);
			}
		}
		else
		{
			std::string text = "Base Health: " + std::to_string(mGame.GetGameMode()->GetHP());
			mGame.GetGameMode()->GetHUD()->GetHitPoint()->SetText(text, Color::LightGreen);
		}
	}
	if (IsAlive() == true && IsA<Cannonball>(other))
	{
		other.SetIsAlive(false);
		mGotHit += 1;
		if (mGotHit == 3)
		{
			SetIsAlive(false);
			mAudioComp->PlaySound(mDieSound);
			mGame.GetGameMode()->AddMoney(10);
			std::string text = "Money: $" + std::to_string(mGame.GetGameMode()->GetMoney());
			mGame.GetGameMode()->GetHUD()->GetMoney()->SetText(text,Color::Yellow);
		}
	}
}

void Enemy::Slow()
{
	mMoveComp->SetLinearAxis(0.5f);
	mMeshComp->SetTextureIndex(1);
	TimerHandle enemyTimeHandle;
	mGame.GetGameTimers().SetTimer(enemyTimeHandle, this, &Enemy::Unslow, 1.0f);
}

void Enemy::Unslow()
{
	mMoveComp->SetLinearAxis(1.0f);
	mMeshComp->SetTextureIndex(0);
}

