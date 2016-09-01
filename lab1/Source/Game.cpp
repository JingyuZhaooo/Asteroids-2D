#include "Game.h"
#include <SDL/SDL.h>
#include "Texture.h"
#include "Random.h"
#include "SpriteComponent.h"
#include "Asteroid.h"

Game::Game()
	:mRenderer(*this)
	,mAssetCache(*this, "Assets/")
	,mShouldQuit(false)
{

}

Game::~Game()
{
	mAssetCache.Clear();
	mWorld.RemoveAllActors();
	SDL_Quit();
}

bool Game::Init()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Failed to initialize SDL.");
		return false;
	}

	// Initialize Renderer
	if (!mRenderer.Init(1024, 768))
	{
		SDL_Log("Failed to initialize renderer.");
		return false;
	}

	// Initialize RNG
	Random::Init();

	// Start frame timer
	mTimer.Start();

	// Run any code at game start
	StartGame();

	return true;
}

void Game::RunLoop()
{
	while (!mShouldQuit)
	{
		ProcessInput();
		Tick();
		GenerateOutput();
	}
}

void Game::Quit()
{

	mShouldQuit = true;
}

void Game::StartGame()
{
	/*
	// Testing SpriteComponents
	auto actor = Actor::Spawn(*this); 
	auto sprite = SpriteComponent::Create(*actor); 
	auto texture = mAssetCache.Load<Texture>("Textures/Spaceship.png"); 
	sprite->SetTexture(texture);
	*/

	const int NUM_ASTEROIDS = 10;
	Vector3 minVec(-512.0f, -384.0f, 0.0f); 
	Vector3 maxVec(512.f, 384.f, 0.0f); 
	for (int i = 0; i < NUM_ASTEROIDS; i++) 
	{
		auto ast = Asteroid::Spawn(*this); 
		ast->SetPosition(Random::GetVector(minVec, maxVec)); 
		ast->SetScale(0.75f); 
	}

}

void Game::ProcessInput()
{
	// Poll events from SDL
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mShouldQuit = true;
			break;
		default:
			//ignore other events for now
			break;
		}
	}
}

void Game::HandleKeyPressed(int key)
{
	// TODO
}

void Game::HandleKeyReleased(int key)
{
	// TODO
}

void Game::Tick()
{
	// TODO
	float deltaTime = mTimer.GetFrameTime(0.016666f);
	mWorld.Tick(deltaTime);
}

void Game::GenerateOutput()
{
	// TODO
	mRenderer.RenderFrame();
}
