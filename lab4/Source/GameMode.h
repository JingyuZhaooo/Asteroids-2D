#pragma once
#include "Actor.h"
#include "HUD.h"
#include "Checkpoint.h"
#include "Arrow.h"


class GameMode : public Actor
{
	DECL_ACTOR(GameMode, Actor);
public:
	GameMode(Game& game);

	void BeginPlay() override;
	void EndPlay() override;
	void CollectCheckpoint();
	CheckpointPtr GetCheckpoint() { return mCheckpoint; };
	HUDPtr GetHUD() { return mHUD; };
	int GetScore() { return mScore; };
	void TimeDecrement();
	int GetTime() { return mTimeLeft; };
private:
	void SpawnCheckpoint();
	CheckpointPtr mCheckpoint;
	ArrowPtr mArror;
	HUDPtr mHUD;
	int mScore;
	int mTimeLeft;
};

DECL_PTR(GameMode);
