#include "Game.h"
#include <SDL/SDL.h>
#include "Texture.h"
#include "Random.h"
#include "SpriteComponent.h"
#include <SDL/SDL_mixer.h>
#include "FontComponent.h"

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
	Mix_CloseAudio();
	SDL_Quit();
	mGameModePtr = nullptr; //does't solve the crash on exit
	TTF_Quit();
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
	//Startup of SDL-mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0)
	{
		SDL_Log("Failed to initialize mixer");
		return false;
	}
	
	TTF_Init();

	// Initialize RNG
	Random::Init();

	// Start frame timer
	mTimer.Start();

	AddInputMappings();

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
	mGameModePtr = GameMode::Spawn(*this);
	mGameModePtr->SpawnNextEnemy();

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
		case SDL_KEYDOWN:
			if (event.key.repeat == 0)
			{
				HandleKeyPressed(event.key.keysym.sym);
			}
			break;
		case SDL_KEYUP:
			HandleKeyReleased(event.key.keysym.sym);
			break;
		case SDL_MOUSEBUTTONDOWN:
			HandleKeyPressed(event.button.button);
			break;
		case SDL_MOUSEBUTTONUP:
			HandleKeyReleased(event.button.button);
			break;
		}
	}
}

void Game::HandleKeyPressed(int key)
{
	mInput.HandleKeyPressed(key);
}

void Game::HandleKeyReleased(int key)
{
	mInput.HandleKeyReleased(key);
}

void Game::Tick()
{
	float deltaTime = mTimer.GetFrameTime(0.016666f);
	mGameTimer.Tick(deltaTime);
	mWorld.Tick(deltaTime);
	mPhysWorld.Tick(deltaTime);
}

void Game::GenerateOutput()
{
	mRenderer.RenderFrame();
}

void Game::AddInputMappings()
{
	mInput.AddActionMapping("Quit", SDLK_ESCAPE);
	mInput.BindAction("Quit", IE_Released, this, &Game::Quit);
	mInput.AddActionMapping("Select", SDL_BUTTON_LEFT);
	mInput.AddActionMapping("Build CannonTower", SDLK_1);
	mInput.AddActionMapping("Build FrostTower", SDLK_2);
}
