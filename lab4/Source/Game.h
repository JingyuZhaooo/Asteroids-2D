// Game.h
// Contains the core game functionality
// such as the game loop

#pragma once
#include "Renderer.h"
#include "FrameTimer.h"
#include "World.h"
#include "AssetCache.h"
#include "PhysWorld.h"
#include "Ship.h"
#include "InputManager.h"
#include "GameTimers.h"
#include "CameraComponent.h"
#include "GameMode.h"

class Game
{
public:
	Game();
	~Game();
	bool Init();
	void RunLoop();
	void Quit();

	Renderer& GetRenderer() { return mRenderer; }
	World& GetWorld() { return mWorld; }
	AssetCache& GetAssetCache() { return mAssetCache; }
	PhysWorld& GetPhysWorld() { return mPhysWorld; }
	InputManager& GetInput() { return mInput; }
	void AddInputMappings();
	GameTimerManager& GetGameTimers() { return mGameTimer; }
	ShipPtr GetShip() { return myShip; };
	GameModePtr GetGameMode() { return mGameModePtr; };
private:
	void StartGame();
	
	void ProcessInput();
	void HandleKeyPressed(int key);
	void HandleKeyReleased(int key);

	void Tick();
	void GenerateOutput();

	Renderer mRenderer;
	FrameTimer mTimer;
	World mWorld;
	AssetCache mAssetCache;
	PhysWorld mPhysWorld;
	ShipPtr myShip;

	bool mShouldQuit;
	InputManager mInput;
	GameTimerManager mGameTimer;
	GameModePtr mGameModePtr;
};
