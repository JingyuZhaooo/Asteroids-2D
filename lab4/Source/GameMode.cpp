#include "GameMode.h"
#include "Game.h"
#include "SphereCollision.h"
#include "Random.h"

IMPL_ACTOR(GameMode, Actor);

GameMode::GameMode(Game& game)
	:Super(game)
{
	//mHUD = HUD::Spawn(mGame);
	SpawnCheckpoint();
}

void GameMode::BeginPlay()
{
	Super::BeginPlay();
	mArror = Arrow::Spawn(mGame);
	ActorPtr ship = mGame.GetShip();
	mArror->SetPlayer(ship);
	Vector3 position = mCheckpoint->GetPosition();
	mArror->SetCheckpointLoc(position);
}

void GameMode::EndPlay()
{
	//mHUD = nullptr;
	Super::EndPlay();
	
}

void GameMode::CollectCheckpoint()
{
	mCheckpoint->SetIsAlive(false);
	SpawnCheckpoint();
}

void GameMode::SpawnCheckpoint()
{
	mCheckpoint = Checkpoint::Spawn(mGame);
	Vector3 playerPos = mGame.GetShip()->GetPosition(); // get the player's position
	Vector3 minVec(playerPos.x - 1000, playerPos.y - 1000, playerPos.z - 1000); // min Vector
	Vector3 maxVec(playerPos.x + 1000, playerPos.y + 1000, playerPos.z + 1000); // max Vector
	mCheckpoint->SetPosition(Random::GetVector(minVec, maxVec));	// set the location of the Checkpoint


}
