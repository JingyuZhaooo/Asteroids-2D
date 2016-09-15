#include "Sound.h"
#include <SDL/SDL_mixer.h>
#include <SDL/SDL.h>

Sound::Sound()
{
	mData = nullptr;
}

Sound::~Sound()
{
	if (mData != nullptr)
	{
		Mix_FreeChunk(mData);
	}
}

struct Mix_Chunk* Sound::GetData()
{
	return mData;
}

bool Sound::Load(const char* fileName, class AssetCache* cache)
{
	mData = Mix_LoadWAV(fileName);
	if (mData == nullptr)
	{
		SDL_Log("Failed to load sound file.");
		return false;	
	}
	else
	{
		return true;
	}
}