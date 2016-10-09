#include "AudioComponent.h"
#include "Actor.h"


IMPL_COMPONENT(AudioComponent, Component);

AudioComponent::AudioComponent(Actor& owner):Super(owner)
{

}

SoundCue AudioComponent::PlaySound(SoundPtr sound, bool looping)
{
	if (looping)
	{
		return SoundCue(Mix_PlayChannel(-1, sound->GetData(), -1));
	}
	else
	{
		return SoundCue(Mix_PlayChannel(-1, sound->GetData(), 0));
	}
}

