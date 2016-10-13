// MoveComponent.h
// Component that does basic velocity-based movement
// Generally used as a "pre-tick" component

#pragma once
#include "Component.h"
#include "Math.h"

class MoveComponent : public Component
{
	DECL_COMPONENT(MoveComponent, Component);
public:
	MoveComponent(Actor& owner);

	void Tick(float deltaTime) override;

	// Linear speed (in game units/s)
	void SetLinearSpeed(float speed) { mLinearSpeed = speed; }
	float GetLinearSpeed() const { return mLinearSpeed; }

	// Angular speed (in radians/s)
	void SetYawSpeed(float speed) { mYawSpeed = speed; }
	float GetYawSpeed() const { return mYawSpeed; }
	// AddTo calls should always be +1.0f or -1.0f
	void AddToLinearAxis(float delta);
	void AddToAngularAxis(float delta);

	void SetLinearAxis(float axis);
	float GetLinearAxis() const { return mLinearAxis; }

	void SetYawAxis(float axis);
	float GetYawAxis() const { return mYawAxis; }

	float GetPitchSpeed() const { return mPitchSpeed; };
	void SetPitchSpeed(float speed) { mPitchSpeed = speed; }; 
	void AddToPitchAxis(float delta);
	void SetPitchAxis(float axis) { mPitchAxis = axis; };
	float GetPitchAxis() { return mPitchAxis; };
private:
	Vector3 mVelocity;

	float mLinearSpeed;
	float mYawSpeed;

	float mLinearAxis;
	float mYawAxis;

	float mPitchSpeed;
	float mPitchAxis;
};

DECL_PTR(MoveComponent);
