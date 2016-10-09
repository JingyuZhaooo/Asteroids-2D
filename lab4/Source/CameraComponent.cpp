#include "CameraComponent.h"
#include "Game.h"
#include "Renderer.h"

IMPL_COMPONENT(CameraComponent, Component);

CameraComponent::CameraComponent(Actor & owner) : Component(owner)
{
	mCamVelocity = Vector3(0, 0, 0);
	mHFollow = 200.0f;
	mVFollow = 100.0f;
	mTargetOffset = 150.0f;
	mHFollowInterpo = mTargetOffset;
	mSpringConstant = 200.0f;		// define spring constant
	mDampingConstant = 2.0f * sqrt(mSpringConstant);		// calculate damping constant from spring constant
	Initialize();
}

void CameraComponent::Tick(float deltaTime)
{
	CalculateIdeal(); //Scaling Horizontal Follow Distance

	Vector3 displacement = mActualCamPos - mIdealCamPos;
	Vector3 springAccel = (-mSpringConstant * displacement) - (mDampingConstant * mCamVelocity);
	mCamVelocity += springAccel * deltaTime;
	mActualCamPos += mCamVelocity * deltaTime;

	mCamForward = mBetterTargetPos - mActualCamPos;
	mCamForward.Normalize();
	mCamLeft = Cross(mOwner.GetWorldTransform().GetZAxis(), mCamForward);
	mCamLeft.Normalize();
	mCamUp = Cross(mCamForward, mCamLeft);
	mCamUp.Normalize();

	Matrix4 camMatrix = Matrix4::CreateLookAt(mActualCamPos, mBetterTargetPos, mCamUp);
	mOwner.GetGame().GetRenderer().UpdateViewMatrix(camMatrix);
}


void CameraComponent::CalculateIdeal()
{
	mHFollowInterpo = Math::Lerp(200.0f, 250.0f, mMoveComp->GetLinearAxis());
	Vector3 shipPos = mOwner.GetPosition();
	// calculate the ideal position of the camera
	mIdealCamPos = shipPos - mOwner.GetWorldTransform().GetXAxis() * mHFollowInterpo + mOwner.GetWorldTransform().GetZAxis() * mVFollow;
}


void CameraComponent::Initialize()
{
	Vector3 shipPos = mOwner.GetPosition();
	mActualCamPos = shipPos - mOwner.GetWorldTransform().GetXAxis() * mHFollow + mOwner.GetWorldTransform().GetZAxis() * mVFollow;
	mBetterTargetPos = Vector3(shipPos.x, shipPos.y + mTargetOffset, shipPos.z); // new target position adjusted for target offset
	mCamForward = mBetterTargetPos - mActualCamPos;
	mCamForward.Normalize();
	mCamLeft = Cross(mOwner.GetWorldTransform().GetZAxis(), mCamForward);
	mCamLeft.Normalize();
	mCamUp = Cross(mCamForward, mCamLeft);
	mCamUp.Normalize();

	Matrix4 camMatrix = Matrix4::CreateLookAt(mActualCamPos, mBetterTargetPos, mCamUp);
	mOwner.GetGame().GetRenderer().UpdateViewMatrix(camMatrix);

}
