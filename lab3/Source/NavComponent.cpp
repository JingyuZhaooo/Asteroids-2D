#include "NavComponent.h"
#include "Game.h"

IMPL_COMPONENT(NavComponent, MoveComponent);

NavComponent::NavComponent(Actor& owner) : MoveComponent(owner)
{
	mStart = mOwner.GetGame().GetNavWorld().GetStartNode();
}

void NavComponent::FollowPath(PathNode * currNode)
{
	Vector3 dif = currNode->mParent->mTile->GetPosition() - mOwner.GetPosition();
	dif.Normalize();	//normalize the vector
	auto angle = acos(Dot(dif, Vector3::UnitX));
	auto crossProduct = Cross(Vector3::UnitX, dif);
	if (crossProduct.z < 0)
	{
		angle *= -1;
	}
	mOwner.SetRotation(angle);
}

void NavComponent::Tick(float deltaTime)
{
	if (mStart->mParent != nullptr)
	{
		float xDiff = (mStart->mTile->GetPosition().x - mOwner.GetPosition().x) * (mStart->mTile->GetPosition().x - mOwner.GetPosition().x);
		float yDiff = (mStart->mTile->GetPosition().y - mOwner.GetPosition().y) * (mStart->mTile->GetPosition().y - mOwner.GetPosition().y);
		if (sqrtf(xDiff + yDiff) < 1.0f)
		{
			FollowPath(mStart);
			mStart = mStart->mParent;
		}
	}
	Super::Tick(deltaTime);
}
