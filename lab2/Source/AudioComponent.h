#pragma once
#include "Component.h"
#include "Sound.h"
#include <SDL/SDL_mixer.h>

class SoundCue
{
public:
	SoundCue() { mChannel = -1; };
	SoundCue(int in) { mChannel = in; };
	void Pause()
	{
		if (mChannel != 1)
		{
			Mix_Pause(mChannel);
		}
	};
	void Resume()
	{
		if (mChannel != 1)
		{
			Mix_Resume(mChannel);
		}
	};
	void Stop()
	{
		if (mChannel != 1)
		{
			Mix_HaltChannel(mChannel);
		}
	};
	bool IsPlaying()
	{
		if (Mix_Playing(mChannel) == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	};
	bool IsPaused()
	{
		if (Mix_Paused(mChannel) == 1)
		{
			return true;
		}
		else
		{
			return false;
		}
	};
private:
	int mChannel;
};

class AudioComponent : public Component
{
	DECL_COMPONENT(AudioComponent, Component);
public:
	AudioComponent(Actor& owner);
	SoundCue PlaySound(SoundPtr sound, bool looping = false);
private:


};
DECL_PTR(AudioComponent);