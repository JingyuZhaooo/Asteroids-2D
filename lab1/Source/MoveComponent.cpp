#include "MoveComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"

IMPL_COMPONENT(MoveComponent, Component);

MoveComponent::MoveComponent(Actor& owner)
	:Component(owner)
	,mLinearSpeed(0.0f)
	,mAngularSpeed(0.0f)
	,mLinearAxis(0.0f)
	,mAngularAxis(0.0f)
{

}

void MoveComponent::Tick(float deltaTime)
{
	if (!Math::IsZero(mAngularAxis))
	{
		float rot = mOwner.GetRotation();
		rot += mAngularSpeed * mAngularAxis * deltaTime;
		mOwner.SetRotation(rot);
	}
	if (!Math::IsZero(mLinearAxis))
	{ 
	// Update velocity based on current forward
	auto mDirection = mOwner.GetForward();
	mVelocity = mDirection * mLinearSpeed * mLinearAxis;
	// Update position of owner based on velocity
	Vector3 oldPosition = mOwner.GetPosition();
	Vector3 newPosition = oldPosition + mVelocity * deltaTime;
	if (newPosition.x < -512)
		newPosition.x = 510;
	if (newPosition.x > 512)
		newPosition.x = -510;
	if (newPosition.y < -384)
		newPosition.y = 382;
	if (newPosition.y > 384)
		newPosition.y = -382;
	mOwner.SetPosition(newPosition);
	}
	if (Math::IsZero(mLinearAxis))
	{

	}
}

void MoveComponent::AddToLinearAxis(float delta)
{
	mLinearAxis += delta;
	mLinearAxis = Math::Clamp(mLinearAxis, -1.0f, 1.0f);
}

void MoveComponent::AddToAngularAxis(float delta)
{
	mAngularAxis += delta;
	mAngularAxis = Math::Clamp(mAngularAxis, -1.0f, 1.0f);
}

void MoveComponent::SetLinearAxis(float axis)
{
	mLinearAxis = Math::Clamp(axis, -1.0f, 1.0f);
}

void MoveComponent::SetAngularAxis(float axis)
{
	mAngularAxis = Math::Clamp(axis, -1.0f, 1.0f);
}
