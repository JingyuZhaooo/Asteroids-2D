#include "MoveComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"

IMPL_COMPONENT(MoveComponent, Component);

MoveComponent::MoveComponent(Actor& owner)
	:Component(owner)
	,mLinearSpeed(0.0f)
	,mYawSpeed(0.0f)
	,mLinearAxis(0.0f)
	,mYawAxis(0.0f)
	,mPitchSpeed(0.0f)
	,mPitchAxis(0.0f)
{

}

void MoveComponent::Tick(float deltaTime)
{
	if (!Math::IsZero(mYawAxis) || !Math::IsZero(mPitchAxis))
	{
		Quaternion currentRot = mOwner.GetRotation(); //Get the current actor's rotation
		float yawAngle = mYawSpeed * mYawAxis * deltaTime;	// Get the Yaw angle
		float pitchAngle = mPitchSpeed * mPitchAxis * deltaTime; // Get the Pitch angle
		Vector3 ZAxis = mOwner.GetWorldTransform().GetZAxis();	//Get the Z-axis (for yaw)
		Vector3 YAxis = mOwner.GetWorldTransform().GetYAxis();	//Get the Y-axis (for pitch)
		Quaternion increment = Quaternion(ZAxis, yawAngle);	// create incremental Quaternion with yaw
		Quaternion increment2 = Quaternion(YAxis, pitchAngle); // create incremental Quaternion with yaw and pitch
		Quaternion rot = Concatenate(currentRot, increment);
		rot = Concatenate(rot, increment2);
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
	mOwner.SetPosition(newPosition);
	}
}

void MoveComponent::AddToLinearAxis(float delta)
{
	mLinearAxis += delta;
	mLinearAxis = Math::Clamp(mLinearAxis, -1.0f, 1.0f);
}

void MoveComponent::AddToAngularAxis(float delta)
{
	mYawAxis += delta;
	mYawAxis = Math::Clamp(mYawAxis, -1.0f, 1.0f);
}

void MoveComponent::SetLinearAxis(float axis)
{
	mLinearAxis = Math::Clamp(axis, -1.0f, 1.0f);
}

void MoveComponent::SetYawAxis(float axis)
{
	mYawAxis = Math::Clamp(axis, -1.0f, 1.0f);
}

void MoveComponent::AddToPitchAxis(float delta)
{
	mPitchAxis += delta;
	mPitchAxis = Math::Clamp(mPitchAxis, -1.0f, 1.0f);
}
