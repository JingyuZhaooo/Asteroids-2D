#include "SpriteComponent.h"
#include "Actor.h"
#include <SDL/SDL.h>
#include "Renderer.h"

IMPL_COMPONENT(SpriteComponent, DrawComponent);

SpriteComponent::SpriteComponent(Actor& owner)
	:DrawComponent(owner)
{

}

void SpriteComponent::Draw(Renderer& render)
{
	// TODO
	if (mTexture != nullptr)
	{
		Matrix4 scaleMat = Matrix4::CreateScale(mTexture->GetWidth(), mTexture->GetHeight(), 1.0f);
		Matrix4 actualWorld = scaleMat * mOwner.GetWorldTransform();
		render.DrawSprite(mTexture, actualWorld);
	}
}

