#pragma once
#include "Component.h"
#include "Math.h"
#include "Actor.h"
#include "MoveComponent.h"
//This component will allow us to track an actor with a follow camera, and then update the view matrix used by the Renderer.

class CameraComponent : public Component
{
	DECL_COMPONENT(CameraComponent, Component);
public:
	CameraComponent(Actor& owner);
	void Tick(float deltaTime);
	void SetMoveComp(MoveComponentPtr moveComp) { mMoveComp = moveComp; };
	void CalculateIdeal();
	void Initialize(); // initialize the actual camera position
private:
	float mHFollow; // horizontal distance between camera and ship
	float mVFollow;
	float mTargetOffset;	// distance between target and ship
	MoveComponentPtr mMoveComp;		// to track the status of ship's inputComponent
	float mHFollowInterpo;		// Interpolation of the horizontal distance between camera and ship
	Vector3 mActualCamPos;	// actual camera position
	Vector3 mCamVelocity;	// camera velocity
	Vector3 mIdealCamPos; // ideal camera position
	double mSpringConstant;
	double mDampingConstant;
	Vector3 mCamForward;
	Vector3 mCamLeft;
	Vector3 mCamUp;
	Vector3 mBetterTargetPos;
};

DECL_PTR(CameraComponent);