#pragma once
#include "Actor.h"
#include "HUD.h"
#include "Checkpoint.h"


class GameMode : public Actor
{
	DECL_ACTOR(GameMode, Actor);
public:
	GameMode(Game& game);

	void BeginPlay() override;
	void EndPlay() override;
	void CollectCheckpoint();
private:
	void SpawnCheckpoint();
	CheckpointPtr mCheckpoint;
	//HUDPtr mHUD;
};

DECL_PTR(GameMode);
