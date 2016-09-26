#include "MeshComponent.h"
#include "Game.h"

IMPL_COMPONENT(MeshComponent, DrawComponent);

MeshComponent::MeshComponent(Actor& owner):DrawComponent(owner)
{
	mTextureIndex = 0;
}
void MeshComponent::Draw(class Renderer& render)
{
	if (mMesh != nullptr)
	{
		
		render.DrawBasicMesh(mMesh->GetVertexArray(), mMesh->GetTexture(mTextureIndex), mOwner.GetWorldTransform());
	}
}