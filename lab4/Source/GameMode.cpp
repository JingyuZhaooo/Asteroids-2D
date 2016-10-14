#include "GameMode.h"
#include "Game.h"
#include "SphereCollision.h"
#include "Random.h"

IMPL_ACTOR(GameMode, Actor);

GameMode::GameMode(Game& game)
	:Super(game)
{
	
	SpawnCheckpoint();
	mScore = 0;
	mTimeLeft = 15;
}

void GameMode::BeginPlay()
{
	Super::BeginPlay();
	mArrow = Arrow::Spawn(mGame);
	ActorPtr ship = mGame.GetShip();
	mArrow->SetPlayer(ship);
	Vector3 position = mCheckpoint->GetPosition();
	mArrow->SetCheckpointLoc(position);
	mHUD = HUD::Spawn(mGame);
	TimerHandle timeHandle;
	mGame.GetGameTimers().SetTimer(timeHandle, this, &GameMode::TimeDecrement, 1.0f);
}

void GameMode::EndPlay()
{
	mHUD = nullptr;
	mArrow = nullptr;
	mCheckpoint = nullptr;
	//Super::EndPlay();
}

void GameMode::CollectCheckpoint()
{
	mTimeLeft += 5;
	mCheckpoint->SetIsAlive(false);
	SpawnCheckpoint();
	mScore += 100;
	std::string text = "Score: " + std::to_string(mGame.GetGameMode()->GetScore());
	mGame.GetGameMode()->GetHUD()->GetScore()->SetText(text, Color::Yellow);
}

void GameMode::SpawnCheckpoint()
{
	float difficulty = 1.0;
	if (mScore >= 1000)
	{
		difficulty = static_cast<float>(mScore) / 1000.0;
	}
	
	mCheckpoint = Checkpoint::Spawn(mGame);
	Vector3 playerPos = mGame.GetShip()->GetPosition(); // get the player's position
	Vector3 minVec(playerPos.x - 1000, playerPos.y - 1000, playerPos.z - 1000); // min Vector
	Vector3 maxVec(playerPos.x + 1000 * difficulty, playerPos.y + 1000 * difficulty, playerPos.z + 1000 * difficulty); // max Vector, accounted for difficulty
	mCheckpoint->SetPosition(Random::GetVector(minVec, maxVec));	// set the location of the Checkpoint
}

void GameMode::TimeDecrement()
{
	if (mTimeLeft >= 1)
	{
		mTimeLeft -= 1;
	}
	std::string text = "Time: " + std::to_string(mGame.GetGameMode()->GetTime());
	mGame.GetGameMode()->GetHUD()->GetTime()->SetText(text, Color::LightGreen);
	TimerHandle timeHandle;
	mGame.GetGameTimers().SetTimer(timeHandle, this, &GameMode::TimeDecrement, 1.0f);
	if (mTimeLeft <= 0)
	{
		mGame.GetShip()->SetIsPaused(true);
		mHUD->ShowMessage();
	}

}